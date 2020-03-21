#include <dbg/debugger.h>

#include <iomanip>
#include <iostream>
#include <cassert>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

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
    : binary_{std::move(binary)}, pid_{pid} {}

void Debugger::Run() {
    WaitDebugee();

    // Process user input.
    for (std::string line;
         std::cout << "dbg> ", std::getline(std::cin, line);) {
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
    ptrace(PTRACE_CONT, pid_, nullptr, nullptr);
    WaitDebugee();
}

void Debugger::SetBreakpoint(std::intptr_t addr) {
    std::cout << "Set breakpoint at 0x" << std::hex << addr << '\n';
    Breakpoint bp(pid_, addr);
    bp.Enable();
    breakpoints_.emplace(addr, bp);
}

void Debugger::DumpRegisters() {
    for (const auto& rdescriptor : kRegisterDescriptors) {
        ReadRegister(rdescriptor.name);
    }
}

void Debugger::ReadRegister(const std::string& name) {
    Register reg = GetRegisterFromName(name);
    std::cout << "0x" << std::setfill('0') << std::setw(16) << std::hex
              << GetRegister(pid_, reg) << ' ' << name << '\n';
}

void Debugger::WriteRegister(const std::string& name, std::uint64_t value) {
    Register reg = GetRegisterFromName(name);
    SetRegister(pid_, reg, value);
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
        SetBreakpoint(std::stol(addr, 0, 16));
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
            WriteRegister(reg, std::stol(val, 0, 16));
        } else {
            std::cout << "Unknown sub-command\n";
        }
    } else if (is_prefix(cmd, "quit")) {
        return Status::stop;
    } else {
        std::cout << "Unknown command\n";
    }

    return Status::run;
}
