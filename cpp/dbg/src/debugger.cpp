#include <dbg/debugger.h>

#include <iostream>
#include <cassert>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fmt/printf.h>
#include <libunwind-ptrace.h>

#include <dbg/registers.h>
#include <dbg/utils.h>

void Debugger::TracerMain(pid_t pid, int, char* argv[]) {
    const char* binary = argv[1];
    Debugger dbg(binary, pid);
    dbg.Run();
}

void Debugger::TraceeMain(pid_t pid, int, char* argv[]) {
    assert(pid == 0);
    // Parameters beside first are ignored.
    ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);

    const char* binary = argv[1];
    execl(binary, binary, nullptr);
}

Debugger::Debugger(std::string binary, pid_t pid)
    : binary_{std::move(binary)}, pid_{pid}, dwarf_reader_{binary_} {}

void Debugger::Run() {
    WaitDebugee();

    // Process user input.
    for (std::string line;
         fmt::printf("dbg> "), std::getline(std::cin, line);) {
        if (HandleInput(line) == Status::stop) {
            break;
        }
    }
}

void Debugger::WaitDebugee() {
    // Wait for child to be stopped with SIGTRAP after ptrace
    // call.
    int wait_status;
    waitpid(pid_, &wait_status, 0 /* options */);
}

void Debugger::ContinueExecution() {
    StepOverBreakpoint();
    ptrace(PTRACE_CONT, pid_, nullptr, nullptr);
    WaitDebugee();
}

void Debugger::SetBreakpoint(std::intptr_t addr) {
    fmt::printf("Set breakpoint at %#x\n", addr);
    Breakpoint bp(pid_, addr);
    bp.Enable();
    breakpoints_.emplace(addr, bp);
}

void Debugger::StepOverBreakpoint() {
    auto prev_pc = GetPC() - 1;

    if (breakpoints_.count(prev_pc)) {
        auto& bp = breakpoints_[prev_pc];

        if (bp.IsEnabled()) {
            SetPC(prev_pc);

            bp.Disable();
            ptrace(PTRACE_SINGLESTEP, pid_, nullptr, nullptr);
            WaitDebugee();
            bp.Enable();
        }
    }
}

void Debugger::DumpRegisters() {
    for (const auto& rdescriptor : kRegisterDescriptors) {
        ReadRegister(rdescriptor.name);
    }
}

void Debugger::ReadRegister(const std::string& name) {
    Register reg = GetRegisterFromName(name);
    fmt::printf("0x%016x %s\n", GetRegister(pid_, reg), name);
}

void Debugger::WriteRegister(const std::string& name, std::uint64_t value) {
    Register reg = GetRegisterFromName(name);
    SetRegister(pid_, reg, value);
}

void Debugger::Backtrace(std::uint64_t frames) {
    unw_addr_space_t as = unw_create_addr_space(&_UPT_accessors, 0);
    void* context = _UPT_create(pid_);
    unw_cursor_t cursor;
    if (unw_init_remote(&cursor, as, context) != 0) {
        fmt::printf("err: cannot initialize cursor for remote unwinding\n");
        return;
    }

    int frame = 0;
    do {
        unw_word_t offset, pc;
        char sym[4096];
        if (unw_get_reg(&cursor, UNW_REG_IP, &pc)) {
            fmt::printf("err: cannot read program counter\n");
        }

        fmt::printf("[%02d] 0x%016x: ", frame, pc);

        if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
            fmt::printf("%s + 0x%x\n", sym, offset);
        } else {
            fmt::printf("???\n");
        }

        ++frame;

        if (frame >= frames) {
            break;
        }
    } while (unw_step(&cursor) > 0);

    unw_destroy_addr_space(as);
    _UPT_destroy(context);
}

std::uint64_t Debugger::GetPC() {
    return GetRegister(pid_, Register::rip);
}

void Debugger::SetPC(std::uint64_t pc) {
    SetRegister(pid_, Register::rip, pc);
}

void Debugger::ReadMemory(std::uint64_t addr) {
    auto value = ptrace(PTRACE_PEEKDATA, pid_, addr, nullptr);
    fmt::printf("0x%016x: 0x%016x\n", addr, value);
}

void Debugger::WriteMemory(std::uint64_t addr, std::uint64_t value) {
    ptrace(PTRACE_POKEDATA, pid_, addr, value);
}

// Return true if debugger process should stop.
Debugger::Status Debugger::HandleInput(const std::string& line) {
    auto args = split(line, ' ');
    if (args.empty()) return Status::run;

    auto cmd = args[0];
    if (is_prefix(cmd, "continue")) {
        ContinueExecution();
    } else if (is_prefix(cmd, "break")) {
        std::string addr{args[1], 2};
        SetBreakpoint(std::stoull(addr, 0, 16));
    } else if (is_prefix(cmd, "register")) {
        auto sub_cmd = args[1];
        if (is_prefix(sub_cmd, "dump")) {
            DumpRegisters();
        } else if (is_prefix(sub_cmd, "read")) {
            std::string reg {args[2]};
            ReadRegister(reg);
        } else if (is_prefix(sub_cmd, "write")) {
            std::string reg {args[2]};
            std::string val {args[3], 2}; //assume 0xVAL
            WriteRegister(reg, std::stoull(val, 0, 16));
        } else {
            fmt::printf("Unknown sub-command\n");
        }
    } else if (is_prefix(cmd, "memory")) {
        auto sub_cmd = args[1];
        if (is_prefix(sub_cmd, "read")) {
            std::string addr {args[2], 2}; //assume 0xADDR
            ReadMemory(std::stoull(addr, 0, 16));
        } else if (is_prefix(sub_cmd, "write")) {
            std::string addr {args[2], 2}; //assume 0xADDR
            std::string val {args[3], 2}; //assume 0xVAL
            WriteMemory(std::stoull(addr, 0, 16), std::stoull(val, 0, 16));
        } else {
            fmt::printf("Unknown sub-command\n");
        }
    } else if (is_prefix(cmd, "backtrace")) {
        int frames = 16;
        if (args.size() > 1) {
            frames = std::stoull(std::string{args[1]}, 0, 10);
        }
        Backtrace(frames);
    } else if (is_prefix(cmd, "quit")) {
        return Status::stop;
    } else {
        fmt::printf("Unknown command\n");
    }

    return Status::run;
}
