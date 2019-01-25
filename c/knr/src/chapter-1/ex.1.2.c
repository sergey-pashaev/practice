/* ex.1.2 */

/* Experiment to find out what happens when prints 's argument string contains
 */
/* \c, where c is some character not listed above. */

#include <stdio.h>

int main() {
    printf("\w\n");
    return 0;
}

/* \w results in warning: */
/* unknown escape sequence '\w': -Wunknown-escape-sequence */
/* and prints just 'w' */
