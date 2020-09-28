#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Not enough arguments means failure.
        printf("Usage: %s executable-file [inferior-arguments ...]\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed.
        fprintf(stderr, "%s: Fork failed.\n", argv[0]);
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
            fprintf(stderr,
                    "%s: Inferior process is not terminated by signal.\n",
                    argv[0]);
            return 1;
        }
    } else {
        // Child process.
        // Execute wrapped command.
        execvp(argv[1], argv + 1);
        exit(1);
    }
}
