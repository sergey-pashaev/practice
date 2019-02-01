/* ex.3.2 */

/* Write a function escape(s,t) that converts characters like newline */
/* and tab into visible escape sequences like \n and \t as it copies */
/* the string t to s. Use a switch. Write a function for the other */
/* direction as well, converting escape sequences into the real */
/* characters. */

#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 1000

void escape(char s[], const char t[]) {
    for (int i = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
            case '\t': {
                *s++ = '\\';
                *s++ = 't';
                break;
            }
            case '\n': {
                *s++ = '\\';
                *s++ = 'n';
                break;
            }
            default: {
                *s++ = t[i];
                break;
            }
        }
    }

    *s = '\0';
}

void unescape(char s[], const char t[]) {
    int escaped = 0;
    for (int i = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
            case '\\': {
                escaped = 1;
                break;
            }
            case 't': {
                if (escaped) {
                    *s++ = '\t';
                    escaped = 0;
                } else {
                    *s++ = 't';
                }
                break;
            }
            case 'n': {
                if (escaped) {
                    *s++ = '\n';
                    escaped = 0;
                } else {
                    *s++ = 'n';
                }
                break;
            }
            default: {
                *s++ = t[i];
                break;
            }
        }
    }

    *s = '\0';
}

/* getinput: read an text into s, return length */
int getinput(char in[], int max) {
    int c;
    int i;

    for (i = 0; i < max - 1; ++i) {
        if ((c = getchar()) != EOF) {
            in[i] = c;
        } else {
            break;
        }
    }

    in[i] = '\0';
    return i;
}

int main() {
    char in[MAXINPUT];
    int len = getinput(in, MAXINPUT);
    if (len > 0) {
        /* escape input */
        char out[MAXINPUT * 2];
        escape(out, in);
        int i = 0;
        printf("escaped:\n");
        while (out[i]) putchar(out[i++]);

        /* unescape input */
        char u[MAXINPUT];
        unescape(u, out);
        int j = 0;
        printf("\nunsecaped:\n");
        while (u[j]) putchar(u[j++]);
    }

    return 0;
}
