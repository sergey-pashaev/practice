/* ex.2.2 */

/* Write a loop equivalent to the for loop above without using && or || */

#include <stdio.h>

#define MAXLINE 1000

int getline_(char line[], int maxline);

/* print the lognest input line */
int main() {
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = getline_(line, MAXLINE)) > 0) {
        printf("%s", line);
    }

    return 0;
}

/* getline: read a line into s, return length */
int getline_(char s[], int lim) {
    int c;
    int i;

    for (i = 0; i < lim - 1; ++i) {
        if ((c = getchar()) != EOF) {
            if (c != '\n') {
                s[i] = c;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
