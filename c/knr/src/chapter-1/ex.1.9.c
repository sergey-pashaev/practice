/* ex.1.9 */

/* Write a program to copy its input to its output, replacing each */
/* string of one or more blanks by a single blank. */

#include <stdio.h>

int main() {
    long blanks;

    blanks = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        } else {
            blanks = 0;
        }

        if (blanks <= 1) putchar(c);
    }
    return 0;
}

/* clang-format off */
/*

$ ./ex.1.9
Write   a program   to copy its    input    to its output, replacing each    string of one     or more blanks by a    single blank.
Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.

*/
/* clang-format on */
