/* ex.1.9 */

/* Write a program to copy its input to its output, replacing each tab */
/* by \t , each backspace by \b , and each backslash by \\ . This */
/* makes tabs and backspaces visible in an unambiguous way. */

#include <stdio.h>

int main() {
    long blanks;

    blanks = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            putchar(c);
    }
    return 0;
}

/* clang-format off */
/*

$ ./ex.1.10
by \t , each backspace by \b , and each backslash by \\ . This
by \\t , each backspace by \\b , and each backslash by \\\\ . This
*/
/* clang-format on */
