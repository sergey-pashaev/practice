/* ex.3.4 */

/* In a two's complement number representation, our version of itoa */
/* does not handle the largest negative number, that is, the value of n */
/* equal to -(2^(wordsize-1)). Explain why not. Modify it to print that */
/* value correctly, regardless of the machine on which it runs. */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 512

/* reverse: reverse line s */
void reverse(char s[]) {
    int len = 0;
    while (s[len]) ++len;

    int b;
    int e;
    int c;
    for (b = 0, e = len - 1; b < len / 2; ++b, --e) {
        c = s[b];
        s[b] = s[e];
        s[e] = c;
    }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign;

    /* -INT_MIN gives us INT_MIN because this is undefined behaviour in C */
    /* https://stackoverflow.com/questions/37301078/is-negating-int-min-undefined-behaviour*/
    /* because of two's complement representation of number and that */
    /* we don't have corresponding representation of lowest possible */
    /* number with positive sign. */

    i = 0;
    sign = n; /* record sign */

    /* generate digits in reverse */
    int min = n == INT_MIN;
    if (min) {
        n = INT_MAX; /* use int max for int min */
    } else {
        n = -n;
    }

    do {
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */

    if (min) s[0] += 1; /* add extra 1 for first digit */

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

int main() {
    int n = INT_MIN + 1;
    char s[BUFSIZE];
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}
