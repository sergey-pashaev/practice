/* ex.1.3 */

/* Modify the temperature conversion program */
/* to print a heading above the table. */

#include <stdio.h>

int main() {
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;   /* lower limit of temperatuire scale */
    upper = 300; /* upper limit */
    step = 20;   /* step size */

    printf("%3s %6s\n", "F", "C");
    printf("----------\n");

    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}
