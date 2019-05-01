/* includes */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define _BSD_SOURCE
#define _GNU_SOURCE

/* declarations */
struct abuf_t;

void init_editor();
void editor_scroll();
void editor_append_row(char* s, size_t len);
void editor_open();
void editor_move_cursor(int key);
void editor_draw_rows();
void editor_process_keypress();
void editor_refresh_screen();
void clear_screen();
int editor_read_key();
void die(const char* msg);
int get_window_size(int* rows, int* cols);
int get_cursor_position(int* row, int* col);
void disable_raw_mode();
void enable_raw_mode();

/* defines */
#define CTRL_KEY(k) ((k)&0x1f)
#define TRAILING_ZERO 1
#define KILO_VERSION "0.0.1"

enum editor_key_t {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    HOME_KEY,
    END_KEY,
    DEL_KEY,
};

/* globals */
struct editor_row_t {
    int size;
    char* chars;
} erow;

struct editor_config_t {
    int cursor_x;
    int cursor_y;
    int row_offset;
    int screen_rows;
    int screen_cols;
    int numrows;
    struct editor_row_t* row;
    struct termios orig_termios;
};

struct editor_config_t g_config;

void die(const char* msg) {
    clear_screen();
    perror(msg);
    exit(1);
}

/* append buffer */
struct abuf_t {
    char* b;
    int len;
};

#define ABUF_INIT \
    { NULL, 0 }

void abuf_append(struct abuf_t* abuf, const char* s, int len) {
    char* new = realloc(abuf->b, abuf->len + len);
    if (new == NULL) return;

    memcpy(&new[abuf->len], s, len);
    abuf->b = new;
    abuf->len += len;
}

void abuf_free(struct abuf_t* abuf) { free(abuf->b); }

/* terminal */
int get_window_size(int* rows, int* cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
        return get_cursor_position(rows, cols);
    }

    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
}

int get_cursor_position(int* row, int* col) {
    char buf[32];
    unsigned int i = 0;

    /* https://vt100.net/docs/vt100-ug/chapter3.html#CPR */
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

    while (i < sizeof(buf) - TRAILING_ZERO) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        ++i;
    }
    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", row, col) != 2) return -1;

    return 0;
}

void editor_scroll() {
    if (g_config.cursor_y < g_config.row_offset) {
        g_config.row_offset = g_config.cursor_y;
    }

    if (g_config.cursor_y >= g_config.row_offset + g_config.screen_rows) {
        g_config.row_offset = g_config.cursor_y - g_config.screen_rows + 1;
    }
}

/* file io */
void editor_append_row(char* s, size_t len) {
    g_config.row = realloc(
        g_config.row, sizeof(struct editor_row_t) * (g_config.numrows + 1));

    int at = g_config.numrows;
    g_config.row[at].size = len;
    g_config.row[at].chars = malloc(len + 1);
    memcpy(g_config.row[at].chars, s, len);
    g_config.row[at].chars[len] = '\0';
    g_config.numrows++;
}

void editor_open(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) die("fopen");

    char* line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) != -1) {
        while (linelen > 0 &&
               (line[linelen - 1] == '\n' || line[linelen - 1] == '\r')) {
            linelen--;
        }

        editor_append_row(line, linelen);
    }

    free(line);
    fclose(fp);
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

int editor_read_key() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }

    if (c == '\x1b') {
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1':
                            return HOME_KEY;
                        case '3':
                            return DEL_KEY;
                        case '4':
                            return END_KEY;
                        case '5':
                            return PAGE_UP;
                        case '6':
                            return PAGE_DOWN;
                        case '7':
                            return HOME_KEY;
                        case '8':
                            return END_KEY;
                    }
                }
            } else {
                switch (seq[1]) {
                    case 'A':
                        return ARROW_UP;
                    case 'B':
                        return ARROW_DOWN;
                    case 'C':
                        return ARROW_RIGHT;
                    case 'D':
                        return ARROW_LEFT;
                    case 'H':
                        return HOME_KEY;
                    case 'F':
                        return END_KEY;
                }
            }
        } else if (seq[0] == 'O') {
            switch (seq[1]) {
                case 'H':
                    return HOME_KEY;
                case 'F':
                    return END_KEY;
            }
        }

        return '\x1b';
    } else {
        return c;
    }
}

/* input  */
void editor_process_keypress() {
    int c = editor_read_key();
    switch (c) {
        case CTRL_KEY('q'): {
            clear_screen();
            exit(0);
            break;
        }
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT: {
            editor_move_cursor(c);
            break;
        }
        case PAGE_UP:
        case PAGE_DOWN: {
            int times = g_config.screen_rows;
            while (times--)
                editor_move_cursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            break;
        }
        case HOME_KEY: {
            g_config.cursor_x = 0;
            break;
        }
        case END_KEY: {
            g_config.cursor_x = g_config.screen_cols - 1;
            break;
        }
        default:
            break;
    }
}

void editor_move_cursor(int key) {
    switch (key) {
        case ARROW_LEFT: {
            if (g_config.cursor_x != 0) g_config.cursor_x--;
            break;
        }
        case ARROW_RIGHT: {
            if (g_config.cursor_x != g_config.screen_cols - 1)
                g_config.cursor_x++;
            break;
        }
        case ARROW_UP: {
            if (g_config.cursor_y != 0) g_config.cursor_y--;
            break;
        }
        case ARROW_DOWN: {
            if (g_config.cursor_y < g_config.numrows) g_config.cursor_y++;
            break;
        }
        default:
            break;
    }
}

/* output */

void editor_draw_rows(struct abuf_t* ab) {
    for (int y = 0; y < g_config.screen_rows; ++y) {
        int filerow = y + g_config.row_offset;
        if (filerow >= g_config.numrows) {
            if (g_config.numrows == 0 && y == g_config.screen_rows / 3) {
                char welcome[80];
                int len = snprintf(welcome, sizeof(welcome),
                                   "Kilo editor -- version %s", KILO_VERSION);
                if (len > g_config.screen_cols) {
                    len = g_config.screen_cols;
                }
                int padding = (g_config.screen_cols - len) / 2;
                if (padding) {
                    abuf_append(ab, "~", 1);
                    --padding;
                }
                while (padding--) abuf_append(ab, " ", 1);
                abuf_append(ab, welcome, len);
            } else {
                abuf_append(ab, "~", 1);
            }
        } else {
            int len = g_config.row[filerow].size;
            if (len > g_config.screen_cols) len = g_config.screen_cols;
            abuf_append(ab, g_config.row[filerow].chars, len);
        }

        abuf_append(ab, "\x1b[K", 3);
        if (y < g_config.screen_rows - 1) {
            abuf_append(ab, "\r\n", 2);
        }
    }
}

void editor_refresh_screen() {
    editor_scroll();

    struct abuf_t ab = ABUF_INIT;

    /* hide cursore */
    abuf_append(&ab, "\x1b[?25l", 6);

    abuf_append(&ab, "\x1b[H", 3);

    editor_draw_rows(&ab);

    /* position cursor */
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", g_config.cursor_y + 1,
             g_config.cursor_x + 1);
    abuf_append(&ab, buf, strlen(buf));

    /* reveal cursor */
    abuf_append(&ab, "\x1b[?25h", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abuf_free(&ab);
}

void clear_screen() {
    /* \x1b[ = 27 + [ = escape sequence */
    /* J = erase in display */
    /* 2 = argument for erase command */
    /* https://vt100.net/docs/vt100-ug/chapter3.html#ED */
    write(STDOUT_FILENO, "\x1b[2J", 4);

    /* position cursor at first row & column */
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void init_editor() {
    g_config.cursor_x = 0;
    g_config.cursor_y = 0;
    g_config.numrows = 0;
    g_config.row = NULL;
    g_config.row_offset = 0;

    if (get_window_size(&g_config.screen_rows, &g_config.screen_cols) == -1)
        die("get_window_size");
}

int main(int argc, char* argv[]) {
    enable_raw_mode();
    init_editor();
    if (argc >= 2) {
        editor_open(argv[1]);
    }

    while (1) {
        editor_refresh_screen();
        editor_process_keypress();
    }

    return 0;
}
