/* ex.1.12 */

/* Write a program that prints its input one word per line. */

#include <stdio.h>

#define OUT 0
#define IN 1

int whitespace(int c) { return c == ' ' || c == '\t' || c == '\n'; }

int main() {
    int state;
    int c;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (whitespace(c) && state == IN) {
            /* end of word */
            state = OUT;
            /* don't duplicate newlines */
            if (c != '\n') putchar('\n');
        } else {
            /* beginning or middle of word */
            putchar(c);
            state = IN;
        }
    }

    return 0;
}
