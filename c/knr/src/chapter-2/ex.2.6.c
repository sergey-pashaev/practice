/* ex.2.6 */

/* Write a function setbits(x,p,n,y) that returns x with the n bits */
/* that begin at position p set to the rightmost n bits of y , leaving */
/* the other bits unchanged. */

#include <stdio.h>
#include <stdlib.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
#if DEBUG
    /* y bits */
    /* ~0 - all ones */
    printf("%x\n", ~0U);

    /* ~0 << n - move ones to left to get n zeros at rigth */
    printf("%x\n", ~0U << n);

    /* ~(~0 << n) - invert so we have n ones at right */
    printf("%x\n", ~(~0U << n));

    /* (~(~0 << n)) & y - save one from y */
    printf("%x\n", (~(~0U << n)) & y);

    /* ((~(~0 << n)) & y) << (p - n + 1) - make them begin from p position */
    printf("%x\n", ((~(~0U << n)) & y) << (p - n + 1));

    /* y mask */
    /* ~0 - all ones */
    printf("%x\n", ~0U);

    /* ~0 << n - move ones to left to get n zeros at right */
    printf("%x\n", ~0U << n);

    /* ~(~0 << n) - invert so we have n ones at right */
    printf("%x\n", ~(~0U << n));

    /* (~(~0 << n)) << (p - n + 1) - make ones begin from p position */
    printf("%x\n", (~(~0U << n)) << (p - n + 1));

    /* ~((~(~0 << n)) << (p - n + 1)) - invert so we have n zeros from p
     * position */
    printf("%x\n", ~((~(~0U << n)) << (p - n + 1)));

    /* (~((~(~0 << n)) << (p - n + 1))) & x - set ones to x by this mask */
    printf("%x\n", (~((~(~0U << n)) << (p - n + 1))) & x);
#endif

    return (((~(~0U << n)) & y) << (p - n + 1)) |
           ((~((~(~0U << n)) << (p - n + 1))) & x);
}

int main(int argc, char* argv[]) {
    if (argc < 5) return 1;
    unsigned x = atoi(argv[1]);
    int p = atoi(argv[2]);
    int n = atoi(argv[3]);
    unsigned y = atoi(argv[4]);
    printf("%x\n", setbits(x, p, n, y));
    return 0;
}
