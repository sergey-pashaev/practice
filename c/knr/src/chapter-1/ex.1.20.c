/* ex.1.20 */

/* Write a program detab that replaces tabs in the input with the */
/* proper number of blanks to space to the next tab stop. Assume a */
/* fixed set of tab stops, say every n columns.  Should n be a variable */
/* or a symbolic parameter? */

#include <stdio.h>

#define TAB_WIDTH 4

int main() {
    int col = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TAB_WIDTH - (col % TAB_WIDTH);
            for (int i = 0; i < spaces; ++i) putchar(' ');
        } else {
            if (c == '\n') {
                col = 0;
            } else {
                ++col;
            }
            putchar(c);
        }
    }

    return 0;
}
