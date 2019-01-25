/* ex.1.8 */

/* Write a program to count blanks, tabs, and newlines. */

#include <stdio.h>

int main() {
    long blanks, tabs, lines;

    blanks = 0;
    tabs = 0;
    lines = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            ++lines;
        else if (c == '\t')
            ++tabs;
        else if (c == ' ')
            ++blanks;
    }

    printf("blanks: %ld tabs: %ld lines: %ld\n", blanks, tabs, lines);
    return 0;
}

/*
$ ./ex.1.8
Write a program	to
  count blanks, 		tabs,
and newlines.
blanks: 7 tabs: 3 lines: 3
*/
