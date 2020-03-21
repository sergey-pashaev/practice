#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include <cstdint>

#include <sys/types.h>

class Breakpoint {
public:
    Breakpoint() = default;
    Breakpoint(pid_t pid, std::intptr_t addr);

    void Enable();
    void Disable();

    bool IsEnabled() const;
    std::intptr_t GetAddress() const;

private:
    pid_t pid_ = 0;
    std::intptr_t addr_ = 0;
    bool enabled_ = false;
    std::uint8_t saved_data_ = 0; // Data which used to be at the
                              // breakpoint address (before replaceing
                              // it with 'int 3' instruction).

};

#endif /* BREAKPOINT_H */
