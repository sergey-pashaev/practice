#include <dbg/breakpoint.h>

#include <sys/ptrace.h>

Breakpoint::Breakpoint(pid_t pid, std::intptr_t addr)
    : pid_{pid}, addr_{addr} {}

void Breakpoint::Enable() {
    // Save data before setting breakpoint.
    auto data = ptrace(PTRACE_PEEKDATA, pid_, addr_, nullptr);
    saved_data_ = static_cast<std::uint8_t>(data & 0xff);  // Save lo byte.

    // Set breakpoint (int3).
    std::uint64_t int3 = 0xcc;
    std::uint64_t data_with_int3 =
        (data & ~0xff) | int3;  // Set lo byte to int3.
    // data & ~0xff - gives all bits exclude lo byte and sets lo byte to zero.
    // (data & ~0xff) | int3 - sets lo bytes to int3.
    ptrace(PTRACE_POKEDATA, pid_, addr_, data_with_int3);

    enabled_ = true;
}

void Breakpoint::Disable() {
    // Restore data.
    auto data = ptrace(PTRACE_PEEKDATA, pid_, addr_, nullptr);
    std::uint64_t restored_data = (data & ~0xff) | saved_data_;
    ptrace(PTRACE_POKEDATA, pid_, addr_, restored_data);

    enabled_ = false;
}

bool Breakpoint::IsEnabled() const { return enabled_; }

std::intptr_t Breakpoint::GetAddress() const { return addr_; }
