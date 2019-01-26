/* ex.1.21 */

/* Write a program entab that replaces strings of blanks by the minimum */
/* number of tabs and blanks to achieve the same spacing. Use the same */
/* tab stops as for detab .  When either a tab or a single blank would */
/* suffice to reach a tab stop, which should be given preference? */

#include <stdio.h>

#define TAB_WIDTH 4

int main() {
    int col = 0;
    int start = -1;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            /* store beginning of spaces */
            if (start < 0) {
                start = col;
            }
        } else {
            if (start >= 0) {
                /* spaces until first tab stop */
                while ((start % TAB_WIDTH) > 0) {
                    putchar(' ');
                    ++start;
                }

                /* entab spaces to tabs */
                while (start + TAB_WIDTH < col) {
                    putchar('\t');
                    start += TAB_WIDTH;
                }

                /* tail spaces */
                while (start < col) {
                    putchar(' ');
                    ++start;
                }

                /* reset beginning of spaces */
                start = -1;
            }

            putchar(c);
        }
        ++col;
    }
    return 0;
}
