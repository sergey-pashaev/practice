/* ex.3.3 */

/* Write a function expand(s1,s2) that expands shorthand notations like */
/* a-z in the string s1 into the equivalent complete list abc...xyz in */
/* s2. Allow for letters of either case and digits, and be prepared to */
/* handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading */
/* or trailing - is taken literally. */

#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 1000

void expand(const char in[], char out[]) {
    char beg = 0; /* beginning of pattern */
    int dash = 0; /* dash read flag */
    int j = 0;    /* output counter */
    for (int i = 0; in[i] != '\n'; ++i) {
        /* dash */
        if (in[i] == '-') {
            if (!beg) {
                /* we are not in pattern it is leading or trailing */
                /* dash so just copy it */
                out[j++] = in[i];
            } else {
                // we are in pattern because beg is not null
                dash = 1;
            }
        } else {
            /* any character */
            if (!beg) {
                /* save beginning of pattern if it is not started */
                beg = in[i];
            } else {
                /* possibly the beginning of pattern */
                if (dash) {
                    /* we already saw dash character so we might expand */
                    while (beg < in[i]) out[j++] = beg++;
                    /* don't copy last character, act like it is
                     * possible beginning of next consequent
                     * pattern */
                    beg = in[i];

                    /* reset dash flag */
                    dash = 0;
                } else {
                    /* we didn't read dash yet, so copy previous
                     * beginning of pattern to output and set new
                     * beginning */
                    out[j++] = beg;
                    beg = in[i];
                }
            }
        }
    }

    /* copy unfinished pattern if so */
    if (beg) out[j++] = beg;
    if (dash) out[j++] = '-';

    out[j] = '\0';
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

int main() {
    char in[MAXINPUT];
    char out[MAXINPUT * 2];
    int len;
    while (printf(">"), (len = getline_(in, MAXINPUT)) > 1) {
        if (len > 0) {
            expand(in, out);
            printf("%s\n", out);
        }
    }

    return 0;
}
