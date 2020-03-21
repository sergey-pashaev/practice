#include <dbg/registers.h>

#include <algorithm>
#include <stdexcept>

#include <sys/ptrace.h>
#include <sys/user.h>  // user_regs_struct

const std::array<RegisterDescriptor, kRegistersCount> kRegisterDescriptors = {{
    {Register::r15, 15, "r15"},
    {Register::r14, 14, "r14"},
    {Register::r13, 13, "r13"},
    {Register::r12, 12, "r12"},
    {Register::rbp, 6, "rbp"},
    {Register::rbx, 3, "rbx"},
    {Register::r11, 11, "r11"},
    {Register::r10, 10, "r10"},
    {Register::r9, 9, "r9"},
    {Register::r8, 8, "r8"},
    {Register::rax, 0, "rax"},
    {Register::rcx, 2, "rcx"},
    {Register::rdx, 1, "rdx"},
    {Register::rsi, 4, "rsi"},
    {Register::rdi, 5, "rdi"},
    {Register::orig_rax, -1, "orig_rax"},
    {Register::rip, -1, "rip"},
    {Register::cs, 51, "cs"},
    {Register::rflags, 49, "eflags"},
    {Register::rsp, 7, "rsp"},
    {Register::ss, 52, "ss"},
    {Register::fs_base, 58, "fs_base"},
    {Register::gs_base, 59, "gs_base"},
    {Register::ds, 53, "ds"},
    {Register::es, 50, "es"},
    {Register::fs, 54, "fs"},
    {Register::gs, 55, "gs"},
}};

namespace {

// Return |reg| index in kRegisterDescriptors.
int RegisterIndex(Register reg) {
    auto it = std::find_if(
        std::begin(kRegisterDescriptors), std::end(kRegisterDescriptors),
        [reg](auto&& rdescriptor) { return rdescriptor.r == reg; });
    return (it - std::begin(kRegisterDescriptors));
}

// Return pointer to Register |reg| in |regs| struct from ptrace.
std::uint64_t* RegisterPtr(user_regs_struct& regs, Register reg) {
    int offset = RegisterIndex(reg);
    return (reinterpret_cast<std::uint64_t*>(&regs) + offset);
}

}  // namespace

void SetRegister(pid_t pid, Register reg, std::uint64_t value) {
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

    std::uint64_t* reg_ptr = RegisterPtr(regs, reg);
    *reg_ptr = value;

    ptrace(PTRACE_SETREGS, pid, nullptr, &regs);
}

std::uint64_t GetRegister(pid_t pid, Register reg) {
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

    std::uint64_t* reg_ptr = RegisterPtr(regs, reg);
    return *reg_ptr;
}

std::uint64_t GetRegisterByDwarf(pid_t pid, int reg) {
    auto it = std::find_if(
        std::begin(kRegisterDescriptors), std::end(kRegisterDescriptors),
        [reg](auto&& rdescriptor) { return rdescriptor.dwarf_r == reg; });

    if (it == std::end(kRegisterDescriptors)) {
        throw std::out_of_range("Unknown dwarf register");
    }

    return GetRegister(pid, it->r);
}

std::string GetRegisterName(Register reg) {
    auto it = std::find_if(
        std::begin(kRegisterDescriptors), std::end(kRegisterDescriptors),
        [reg](auto&& rdescriptor) { return rdescriptor.r == reg; });

    return it->name;
}

Register GetRegisterFromName(const std::string& reg) {
    auto it = std::find_if(
        std::begin(kRegisterDescriptors), std::end(kRegisterDescriptors),
        [reg](auto&& rdescriptor) { return rdescriptor.name == reg; });

    if (it == std::end(kRegisterDescriptors)) {
        throw std::out_of_range("Unknown register " + reg);
    }

    return it->r;
}
