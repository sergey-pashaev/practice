/* ex.1.16 */

/* Revise the main routine of the longest-line program so it will */
/* correctly print the length of arbitrary long input lines, and as */
/* much as possible of the text. */

#include <stdio.h>

int length();

/* print the length of lognest input line */
int main() {
    int len; /* current line length */
    int max; /* maximum length seen so far */

    max = 0;
    while ((len = length()) > 0) {
        if (len > max) {
            max = len;
        }
    }

    if (max > 0) {
        printf("%d\n", max);
    }

    return 0;
}

/* length: return length of current input line */
int length() {
    int c;
    int i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        ;

    if (c == '\n') ++i;

    return i;
}
