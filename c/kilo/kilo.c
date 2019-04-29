#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void die(const char* msg) {
    perror(msg);
    exit(1);
}

void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) < 0) die("tcsetattr");
}

void enable_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) < 0) die("tcgetattr");
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    /* local flags */
    raw.c_lflag &= ~(ECHO);   /* disable echoing of input */
    raw.c_lflag &= ~(ICANON); /* disable canonical mode - enable raw mode */
    raw.c_lflag &= ~(ISIG);   /* disable Ctrl-{C,Z} escape codes */
    raw.c_lflag &= ~(IEXTEN); /* disable Ctrl-V */

    /* input flags */
    raw.c_iflag &= ~(IXON);   /* disable flow control (Ctrl-{S,Q}) */
    raw.c_iflag &= ~(ICRNL);  /* disable Ctrl-{M,J} acting as enter */
    raw.c_iflag &= ~(BRKINT); /* disable break condition (Ctrl-C)  */

    /* misc flags */
    raw.c_iflag &= ~(INPCK | ISTRIP);
    raw.c_cflag |= (CS8);

    /* output flags */
    raw.c_oflag &= ~(OPOST); /* disable any output processing (\n -> \r\n) */

    /* set timeout for read() */
    raw.c_cc[VMIN] = 0;  /* min bytes of input to return from read() */
    raw.c_cc[VTIME] = 1; /* time to wait before read() returns (1 = 1/10 sec) */

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0) die("tcsetattr");
}

int main(int argc, char* argv[]) {
    enable_raw_mode();

    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) < 0 && errno != EAGAIN) die("read");
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }

        if (c == 'q') break;
    }

    return 0;
}
