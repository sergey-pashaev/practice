/* ex.2.1 */

/* Write a program to determine the ranges of char, short, int, and */
/* long variables, both signed and unsigned, by printing appropriate */
/* values from standard headers and by direct computation. Harder if */
/* you compute them: determine the ranges of the various floating-point */
/* types. */

#include <limits.h>
#include <stdio.h>

int main() {
    printf("signed char\t[%d:%d]\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char\t[%d:%d]\n", 0, UCHAR_MAX);

    printf("signed short\t[%d:%d]\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short\t[%d:%d]\n", 0, USHRT_MAX);

    printf("signed int\t[%d:%d]\n", INT_MIN, INT_MAX);
    printf("unsigned int\t[%d:%u]\n", 0, UINT_MAX);

    printf("signed int\t[%ld:%ld]\n", LONG_MIN, LONG_MAX);
    printf("unsigned int\t[%d:%lu]\n", 0, ULONG_MAX);
    return 0;
}
