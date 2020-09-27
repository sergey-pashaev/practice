#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed.
        return 1;
    } else if (pid) {
        // Parent process.
        int status = 0;
        wait(&status);
        if (WIFSIGNALED(status)) {
            // Signal terminated means success.
            return 0;
        } else {
            // Not terminated means failure.
            return 1;
        }
    } else {
        // Child process.
        // Execute wrapped command.
        execvp(argv[1], argv + 1);
        exit(1);
    }
}
