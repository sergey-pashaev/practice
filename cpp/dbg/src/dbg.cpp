#include <iostream>

#include <errno.h>       // errno
#include <string.h>      // strerror
#include <sys/ptrace.h>  // ptrace
#include <sys/types.h>   // pid_t
#include <unistd.h>      // fork

#include <dbg/debugger.h>

int usage(const char* bin) {
    std::cout << "Usage: " << bin << " <program>\n";
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return usage(argv[0]);
    }

    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << strerror(errno) << "\n";
        return errno;
    }

    if (pid == 0) {
        Debugger::TraceeMain(pid, argc, argv);
    } else if (pid >= 1) {
        Debugger::TracerMain(pid, argc, argv);
    }
}
