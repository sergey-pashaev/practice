/* ex.3.5 */

/* Write the function itob(n,s,b) that converts the integer n into a */
/* base b character representation in the string s. In particular, */
/* itob(n,s,16) formats s as a hexadecimal integer in s. */

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

/* itob: convert n to characters in s in base b*/
void itob(int n, char s[], int base) {
    int i, sign;
    const char* b = "0123456789abcdefghijklmnopqrstuvwxyz";

    i = 0;
    sign = n; /* record sign */

    int min = n == INT_MIN;
    if (min) {
        n = INT_MAX; /* use int max for int min */
    } else {
        if (sign < 0) n = -n;
    }

    /* generate digits in reverse */
    do {
        s[i++] = b[n % base];  /* get next digit */
    } while ((n /= base) > 0); /* delete it */

    if (min)
        s[0] = b[(b[base - 1] - s[0] + 1) %
                 base]; /* add extra 1 for first digit */

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

int main() {
    int n = INT_MIN;
    char s[BUFSIZE];
    itob(n, s, 16);
    printf("%x\n", n);
    printf("%s\n", s);
    return 0;
}
