#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include <sys/types.h>

#include <dbg/breakpoint.h>
#include <dbg/dwarf_reader.h>

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
    void StepOverBreakpoint();

    void DumpRegisters();
    void ReadRegister(const std::string& name);
    void WriteRegister(const std::string& name, std::uint64_t value);

    void Backtrace(std::uint64_t frames);

    std::uint64_t GetPC();
    void SetPC(std::uint64_t pc);

    void ReadMemory(std::uint64_t addr);
    void WriteMemory(std::uint64_t addr, std::uint64_t value);

    // Helpers:
    void WaitDebugee();

    // Return true if debugger process should stop.
    Status HandleInput(const std::string& line);

   private:
    std::string binary_;
    pid_t pid_;
    std::unordered_map<std::intptr_t, Breakpoint> breakpoints_;
    DwarfReader dwarf_reader_;
};

#endif /* DEBUGGER_H */
