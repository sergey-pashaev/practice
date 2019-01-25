/* ex.1.4 */

/* Write a program to print the corresponding */
/* Celsius to Fahrenheit table. */

#include <stdio.h>

int main() {
    float fahr, celsius;
    float lower, upper, step;
    lower = -17.8; /* lower limit of temperatuire scale */
    upper = 155;   /* upper limit */
    step = 11.2;   /* step size */

    printf("%6s %3s\n", "C", "F");
    printf("----------\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius / (5.0 / 9.0) + 32.0;
        printf("%6.1f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;
}
