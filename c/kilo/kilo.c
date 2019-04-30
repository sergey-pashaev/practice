/* includes */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/* defines */
#define CTRL_KEY(k) ((k)&0x1f)

/* globals */
struct editor_config_t {
    int screen_rows;
    int screen_cols;
    struct termios orig_termios;
};

struct editor_config_t g_config;

void clear_screen();

void die(const char* msg) {
    clear_screen();
    perror(msg);
    exit(1);
}

/* terminal */
int get_window_size(int* rows, int* cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    }

    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
}

void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_config.orig_termios) < 0)
        die("tcsetattr");
}

void enable_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &g_config.orig_termios) < 0) die("tcgetattr");
    atexit(disable_raw_mode);

    struct termios raw = g_config.orig_termios;
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

char editor_read_key() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}

/* input  */
void editor_process_keypress() {
    char c = editor_read_key();
    switch (c) {
        case CTRL_KEY('q'): {
            clear_screen();
            exit(0);
            break;
        }
        default:
            break;
    }
}

/* output */

void editor_draw_rows() {
    for (int y = 0; y < g_config.screen_rows; ++y) {
        write(STDIN_FILENO, "~\r\n", 3);
    }
}

void editor_refresh_screen() {
    clear_screen();
    editor_draw_rows();
    /* position cursor at first row & column */
    write(STDOUT_FILENO, "\x1b[1;1H", 6);
}

void clear_screen() {
    /* \x1b[ = 27 + [ = escape sequence */
    /* J = erase in display */
    /* 2 = argument for erase command */
    /* https://vt100.net/docs/vt100-ug/chapter3.html#ED */
    write(STDIN_FILENO, "\x1b[2J", 4);

    /* position cursor at first row & column */
    write(STDOUT_FILENO, "\x1b[1;1H", 6);
}

void init_editor() {
    if (get_window_size(&g_config.screen_rows, &g_config.screen_cols) == -1)
        die("get_window_size");
}

int main(int argc, char* argv[]) {
    enable_raw_mode();
    init_editor();

    while (1) {
        editor_refresh_screen();
        editor_process_keypress();
    }

    return 0;
}
