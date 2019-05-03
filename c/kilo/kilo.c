/* includes */
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define _XOPEN_SOURCE = 500
#define _BSD_SOURCE
#define _GNU_SOURCE

/* declarations */
struct abuf_t;
struct editor_row_t;

void init_editor();
char* editor_rows_to_string(int* buflen);
void editor_scroll();
void editor_save();
void editor_insert_char(int c);
void editor_row_insert_char(struct editor_row_t* row, int at, int c);
void editor_set_status_message(const char* fmt, ...);
int editor_row_cx_to_rx(struct editor_row_t* row, int cx);
void editor_update_row(struct editor_row_t* row);
void editor_append_row(char* s, size_t len);
void editor_open();
void editor_move_cursor(int key);
void editor_draw_messagebar(struct abuf_t* ab);
void editor_draw_statusbar(struct abuf_t* ab);
void editor_draw_rows(struct abuf_t* ab);
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
#define KILO_TAB_STOP 8

enum editor_key_t {
    BACKSPACE = 127,
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
    int rsize;
    char* chars;
    char* render;
} erow;

struct editor_config_t {
    int cursor_x;
    int cursor_y;
    int render_x;
    int row_offset;
    int col_offset;
    int screen_rows;
    int screen_cols;
    int numrows;
    char* filename;
    char statusmsg[80];
    time_t statusmsg_time;
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

void editor_save() {
    if (g_config.filename == NULL) return;

    int len;
    char* buf = editor_rows_to_string(&len);

    int fd = open(g_config.filename, O_RDWR | O_CREAT, 0644);
    if (fd != -1) {
        if (ftruncate(fd, len) != -1) {
            if (write(fd, buf, len) == len) {
                close(fd);
                free(buf);
                editor_set_status_message("%d bytes written to disk", len);
                return;
            }
        }

        close(fd);
    }

    free(buf);
    editor_set_status_message("Can't save! I/O error: %s", strerror(errno));
}

void editor_scroll() {
    g_config.render_x = 0;
    if (g_config.cursor_y < g_config.numrows) {
        g_config.render_x = editor_row_cx_to_rx(
            &g_config.row[g_config.cursor_y], g_config.cursor_x);
    }

    if (g_config.cursor_y < g_config.row_offset) {
        g_config.row_offset = g_config.cursor_y;
    }

    if (g_config.cursor_y >= g_config.row_offset + g_config.screen_rows) {
        g_config.row_offset = g_config.cursor_y - g_config.screen_rows + 1;
    }

    if (g_config.render_x < g_config.col_offset) {
        g_config.col_offset = g_config.render_x;
    }

    if (g_config.render_x >= g_config.col_offset + g_config.screen_cols) {
        g_config.col_offset = g_config.render_x - g_config.screen_cols + 1;
    }
}

void editor_insert_char(int c) {
    if (g_config.cursor_y == g_config.numrows) {
        editor_append_row("", 0); /* newline at the end file */
    }

    editor_row_insert_char(&g_config.row[g_config.cursor_y], g_config.cursor_x,
                           c);
    g_config.cursor_x++;
}

void editor_row_insert_char(struct editor_row_t* row, int at, int c) {
    if (at < 0 || at > row->size) at = row->size;
    row->chars = realloc(row->chars, row->size + 2);
    memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);
    row->size++;
    row->chars[at] = c;
    editor_update_row(row);
}

void editor_set_status_message(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(g_config.statusmsg, sizeof(g_config.statusmsg), fmt, ap);
    va_end(ap);
    g_config.statusmsg_time = time(NULL);
}

/* file io */
int editor_row_cx_to_rx(struct editor_row_t* row, int cx) {
    int rx = 0;
    for (int j = 0; j < cx; ++j) {
        if (row->chars[j] == '\t') {
            rx += (KILO_TAB_STOP - 1) - (rx % KILO_TAB_STOP);
        }
        ++rx;
    }

    return rx;
}

void editor_update_row(struct editor_row_t* row) {
    int tabs = 0;
    for (int j = 0; j < row->size; ++j) {
        if (row->chars[j] == '\t') ++tabs;
    }

    free(row->render);
    row->render = malloc(row->size + tabs * (KILO_TAB_STOP - 1) + 1);

    int idx = 0;
    for (int j = 0; j < row->size; ++j) {
        if (row->chars[j] == '\t') {
            row->render[idx++] = ' ';
            while (idx % KILO_TAB_STOP != 0) row->render[idx++] = ' ';
        } else {
            row->render[idx++] = row->chars[j];
        }
    }
    row->render[idx] = '\0';
    row->rsize = idx;
}

void editor_append_row(char* s, size_t len) {
    g_config.row = realloc(
        g_config.row, sizeof(struct editor_row_t) * (g_config.numrows + 1));

    int at = g_config.numrows;
    g_config.row[at].size = len;
    g_config.row[at].chars = malloc(len + 1);
    memcpy(g_config.row[at].chars, s, len);
    g_config.row[at].chars[len] = '\0';

    g_config.row[at].rsize = 0;
    g_config.row[at].render = NULL;

    editor_update_row(&g_config.row[at]);

    g_config.numrows++;
}

void editor_open(char* filename) {
    free(g_config.filename);
    g_config.filename = strdup(filename);

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
        case '\r': {
            break;
        }
        case CTRL_KEY('q'): {
            clear_screen();
            exit(0);
            break;
        }
        case CTRL_KEY('s'): {
            editor_save();
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
            if (c == PAGE_UP) {
                g_config.cursor_y = g_config.row_offset;
            } else if (c == PAGE_DOWN) {
                g_config.cursor_y =
                    g_config.row_offset + g_config.screen_rows - 1;
                if (g_config.cursor_y > g_config.numrows) {
                    g_config.cursor_y = g_config.numrows;
                }
            }
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
            if (g_config.cursor_y < g_config.numrows) {
                g_config.cursor_x = g_config.row[g_config.cursor_y].size;
            }
            break;
        }
        case BACKSPACE:
        case CTRL_KEY('h'):
        case DEL_KEY: {
            break;
        }
        case CTRL_KEY('l'):
        case '\x1b': {
            break;
        }
        default:
            editor_insert_char(c);
            break;
    }
}

void editor_move_cursor(int key) {
    struct editor_row_t* row = (g_config.cursor_y >= g_config.numrows)
                                   ? NULL
                                   : &g_config.row[g_config.cursor_y];

    switch (key) {
        case ARROW_LEFT: {
            if (g_config.cursor_x != 0) {
                g_config.cursor_x--;
            } else if (g_config.cursor_y > 0) {
                g_config.cursor_y--;
                g_config.cursor_x = g_config.row[g_config.cursor_y].size;
            }
            break;
        }
        case ARROW_RIGHT: {
            if (row && g_config.cursor_x < row->size) {
                g_config.cursor_x++;
            } else if (row && g_config.cursor_x == row->size) {
                g_config.cursor_y++;
                g_config.cursor_x = 0;
            }
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

    row = (g_config.cursor_y >= g_config.numrows)
              ? NULL
              : &g_config.row[g_config.cursor_y];
    int rowlen = row ? row->size : 0;
    if (g_config.cursor_x > rowlen) {
        g_config.cursor_x = rowlen;
    }
}

/* output */
void editor_draw_messagebar(struct abuf_t* ab) {
    abuf_append(ab, "\x1b[K", 3);
    int msglen = strlen(g_config.statusmsg);
    if (msglen > g_config.screen_cols) {
        msglen = g_config.screen_cols;
    }

    if (msglen && time(NULL) - g_config.statusmsg_time < 5) {
        abuf_append(ab, g_config.statusmsg, msglen);
    }
}

void editor_draw_statusbar(struct abuf_t* ab) {
    abuf_append(ab, "\x1b[7m", 4); /* invert colors */

    char status[80];
    char rstatus[80];
    int len = snprintf(status, sizeof(status), "%.20s - %d lines",
                       g_config.filename ? g_config.filename : "[no name]",
                       g_config.numrows);

    int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d",
                        g_config.cursor_y + 1, g_config.numrows);

    if (len > g_config.screen_cols) {
        len = g_config.screen_cols;
    }

    abuf_append(ab, status, len);

    while (len < g_config.screen_cols) {
        if (g_config.screen_cols - len == rlen) {
            abuf_append(ab, rstatus, rlen);
            break;
        } else {
            abuf_append(ab, " ", 1);
            ++len;
        }
    }

    abuf_append(ab, "\x1b[m", 3); /* restore colors */
    abuf_append(ab, "\r\n", 2);   /* newline */
}

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
            int len = g_config.row[filerow].rsize - g_config.col_offset;
            if (len < 0) len = 0;
            if (len > g_config.screen_cols) len = g_config.screen_cols;
            abuf_append(ab, &g_config.row[filerow].render[g_config.col_offset],
                        len);
        }

        abuf_append(ab, "\x1b[K", 3);
        abuf_append(ab, "\r\n", 2);
    }
}

void editor_refresh_screen() {
    editor_scroll();

    struct abuf_t ab = ABUF_INIT;

    /* hide cursore */
    abuf_append(&ab, "\x1b[?25l", 6);

    abuf_append(&ab, "\x1b[H", 3);

    editor_draw_rows(&ab);
    editor_draw_statusbar(&ab);
    editor_draw_messagebar(&ab);

    /* position cursor */
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH",
             g_config.cursor_y - g_config.row_offset + 1,
             g_config.render_x - g_config.col_offset + 1);
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

char* editor_rows_to_string(int* buflen) {
    int totlen = 0;
    int j;

    for (j = 0; j < g_config.numrows; ++j) {
        totlen += g_config.row[j].size + 1;
    }
    *buflen = totlen;

    char* buf = malloc(totlen);
    char* p = buf;
    for (j = 0; j < g_config.numrows; ++j) {
        memcpy(p, g_config.row[j].chars, g_config.row[j].size);
        p += g_config.row[j].size;
        *p = '\n';
        p++;
    }

    return buf;
}

void init_editor() {
    g_config.cursor_x = 0;
    g_config.cursor_y = 0;
    g_config.render_x = 0;
    g_config.numrows = 0;
    g_config.row = NULL;
    g_config.row_offset = 0;
    g_config.col_offset = 0;
    g_config.filename = NULL;
    g_config.statusmsg[0] = '\0';
    g_config.statusmsg_time = 0;

    if (get_window_size(&g_config.screen_rows, &g_config.screen_cols) == -1)
        die("get_window_size");

    g_config.screen_rows -= 2;
}

int main(int argc, char* argv[]) {
    enable_raw_mode();
    init_editor();
    if (argc >= 2) {
        editor_open(argv[1]);
    }

    editor_set_status_message("HELP: Ctrl-Q = quit | Ctrl-S = save");

    while (1) {
        editor_refresh_screen();
        editor_process_keypress();
    }

    return 0;
}
