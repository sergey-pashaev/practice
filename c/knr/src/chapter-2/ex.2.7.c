/* ex.2.7 */

/* Write a function invert(x,p,n) that returns x with the n bits that */
/* begin at position p inverted (i.e., 1 changed into 0 and vice */
/* versa), leaving the others unchanged. */

#include <stdio.h>
#include <stdlib.h>

unsigned invert(unsigned x, int p, int n) {
    return ((~(~0U << n)) << (p - n + 1)) ^ x;
}

int main(int argc, char* argv[]) {
    if (argc < 4) return 1;
    unsigned x = atoi(argv[1]);
    int p = atoi(argv[2]);
    int n = atoi(argv[3]);
    printf("%x\n", invert(x, p, n));
    return 0;
}
