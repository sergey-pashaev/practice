/* ex.1.5 */

/* Modify the temperature conversion program to print the table in */
/* reverse order, that is, from 300 degrees to 0. */

#include <stdio.h>

int main() {
    printf("%3s %6s\n", "F", "C");
    printf("----------\n");

    int fahr;
    for (fahr = 0; fahr <= 300; fahr += 20)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));

    return 0;
}
