#include <dbg/debugger.h>

#include <iostream>
#include <cassert>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

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
    } else if (is_prefix(cmd, "quit")) {
        return Status::stop;
    } else {
        std::cout << "Unknown command\n";
        return Status::run;
    }

    return Status::run;
}
