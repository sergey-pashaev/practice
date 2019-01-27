/* ex.1.23 */

/* Write a program to remove all comments from a C program. Don't */
/* forget to handle quoted strings and character constants properly. C */
/* comments don't nest. */

#include <stdio.h>

#define CODE 0
#define COMMENT 1
#define QUOTED 2

int main() {
    int c;            /* current character */
    int next;         /* next character */
    int state = CODE; /* inside or outside of comment */
    char quote;

    while ((c = getchar()) != EOF) {
        if (state == CODE) {
            if (c == '/') {
                /* CODE -> COMMENT */
                if ((next = getchar()) == '*') {
                    state = COMMENT;
                } else {
                    putchar(c);
                    putchar(next);
                }
            } else if (c == '\'' || c == '"') {
                /* CODE -> QUOTED */
                quote = c;
                state = QUOTED;
                /* print code */
                putchar(c);
            } else {
                /* print code */
                putchar(c);
            }
        } else if (state == COMMENT) {
            if (c == '*') {
                /* COMMENT -> CODE */
                if ((next = getchar()) == '/') {
                    state = CODE;
                }
            }
        } else if (state == QUOTED) {
            if (c == quote) {
                /* QUOTED -> CODE */
                state = CODE;
                putchar(c);
            } else if (c == '\\') {
                /* print escaped character */
                putchar(c);
                putchar(getchar());
            } else {
                putchar(c);
            }
        }
    }

    return 0;
}
