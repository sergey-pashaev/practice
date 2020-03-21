#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include <sys/types.h>

#include <dbg/breakpoint.h>

class Debugger {
   public:
    enum class Status { run, stop };

    static void TracerMain(pid_t pid, int argc, char* argv[]);
    static void TraceeMain(pid_t pid, int argc, char* argv[]);

    Debugger(std::string binary, pid_t pid);

    void Run();

   private:
    // Commands:
    void ContinueExecution();
    void SetBreakpoint(std::intptr_t addr);

    // Helpers:
    void WaitDebugee();

    // Return true if debugger process should stop.
    Status HandleInput(const std::string& line);

   private:
    std::string binary_;
    pid_t pid_;
    std::unordered_map<std::intptr_t, Breakpoint> breakpoints_;
};

#endif /* DEBUGGER_H */
