/* ex.1.18 */

/* Write a program to remove trailing blanks and tabs from each line of */
/* input, and to delete entirely blank lines. */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int getline_(char line[], int maxline);
int clean(char line[], int len);

/* print the lognest input line */
int main() {
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = getline_(line, MAXLINE)) > 0) {
        len = clean(line, len);
        /* plain \n is empty line */
        /* print non-empty lines */
        if (len > 1) {
            printf("%s", line);
        }
    }

    return 0;
}

/* getline: read a line into s, return length */
int getline_(char s[], int lim) {
    int c;
    int i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

/* whitespace: return true if c is whitespace character */
int whitespace(int c) { return c == ' ' || c == '\t' || c == '\n'; }

/* clean: clean line s from trailing whitespace, return new length */
int clean(char s[], int len) {
    int i;
    for (i = len - 1; i >= 0 && whitespace(s[i]); --i) {
    }
    s[++i] = '\n';
    s[++i] = '\0';

    return i - 1; /* don't count trailing zero */
}
