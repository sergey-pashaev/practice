#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <cstddef>
#include <string>
#include <cstdint>

#include <sys/types.h>

// See struct user_regs_struct at /usr/include/sys/user.h
enum class Register {
    rax,
    rbx,
    rcx,
    rdx,
    rdi,
    rsi,
    rbp,
    rsp,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,
    rip,
    rflags,
    cs,
    orig_rax,
    fs_base,
    gs_base,
    fs,
    gs,
    ss,
    ds,
    es,
};

constexpr std::size_t kRegistersCount = 27;

struct RegisterDescriptor {
    Register r;
    int dwarf_r; // Register number in DWARF format.
    std::string name;
};

extern const std::array<RegisterDescriptor, kRegistersCount> kRegisterDescriptors;

std::string RegisterLongestName();
void SetRegister(pid_t pid, Register reg, std::uint64_t value);
std::uint64_t GetRegister(pid_t pid, Register reg);
std::uint64_t GetRegisterByDwarf(pid_t pid, int reg);
std::string GetRegisterName(Register reg);
Register GetRegisterFromName(const std::string& reg);

#endif /* REGISTERS_H */
