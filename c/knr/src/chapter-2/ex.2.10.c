/* ex.2.10 */

/* Rewrite the function lower, which converts upper case letters to */
/* lower case, with a conditional expression instead of if-else. */

#include <stdio.h>
#include <stdlib.h>

int lower(int c) { return (c >= 'A' && c <= 'Z') ? (c - 'A') + 'a' : c; }

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(lower(c));
    }
    return 0;
}
