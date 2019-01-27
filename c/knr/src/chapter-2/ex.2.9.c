/* ex.2.9 */

/* In a two's complement number system, x &= (x-1) deletes the */
/* rightmost 1-bit in x. Explain why. Use this observation to write a */
/* faster version of bitcount. */

#include <stdio.h>
#include <stdlib.h>

int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; x &= (x - 1)) {
        b++;
    }
    return b;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    unsigned x = atoi(argv[1]);
    printf("%d\n", bitcount(x));
    return 0;
}
