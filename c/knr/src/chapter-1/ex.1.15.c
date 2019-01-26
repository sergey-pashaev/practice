/* ex.1.15 */

/* Rewrite the temperature conversion program of Section 1.2 to use a */
/* function for conversion. */

#include <stdio.h>

/* Fahrenheit to Celsius */
float ftoc(float f) { return (5.0 / 9.0) * (f - 32.0); }

int main() {
    float fahr;
    float lower, upper, step;
    lower = 0;   /* lower limit of temperatuire scale */
    upper = 300; /* upper limit */
    step = 20;   /* step size */

    printf("%3s %6s\n", "F", "C");
    printf("----------\n");

    fahr = lower;
    while (fahr <= upper) {
        printf("%3.0f %6.1f\n", fahr, ftoc(fahr));
        fahr = fahr + step;
    }

    return 0;
}
