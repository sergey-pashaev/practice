/* ex.1.19 */

/* Write a function reverse(s) that reverses the character string s. */
/* Use it to write a program that reverses its input a line at a */
/* time. */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int getline_(char line[], int maxline);
void reverse(char line[], int len);

/* print the lognest input line */
int main() {
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = getline_(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s", line);
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

/* reverse: reverse line of len length */
void reverse(char s[], int len) {
    int b;
    int e;
    int c;
    /* 2 : null character + newline */
    for (b = 0, e = len - 2; b < len / 2; ++b, --e) {
        c = s[b];
        s[b] = s[e];
        s[e] = c;
    }
}
