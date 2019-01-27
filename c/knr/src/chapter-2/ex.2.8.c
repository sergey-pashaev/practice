/* ex.2.8 */

/* Write a function rightrot(x,n) that returns the value of the integer */
/* x rotated to the right by n positions. */

#include <stdio.h>
#include <stdlib.h>

unsigned rightrot(unsigned x, int n) {
    while (n) {
        if (x & 1) {
            x = (x >> 1) | (~(~0U >> 1));
        } else {
            x = x >> 1;
        }

        --n;
    }

    return x;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    unsigned x = atoi(argv[1]);
    int n = atoi(argv[2]);
    printf("%x\n", rightrot(x, n));
    return 0;
}
