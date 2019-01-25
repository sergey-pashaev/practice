/* ex.1.13 */

/* Write a program to print a histogram of the lengths of words in its */
/* input. It is easy to draw the histogram with the bars horizontal; a */
/* vertical orientation is more challenging. */

#include <stdio.h>

#define WORD_LENGTH_MAX 256
#define TERMINAL_WIDTH 80

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int whitespace(int c) { return c == ' ' || c == '\t' || c == '\n'; }

int main() {
    int words[WORD_LENGTH_MAX];

    for (int i = 0; i < WORD_LENGTH_MAX; ++i) {
        words[i] = 0;
    }

    /* count words lenght */
    int c;
    int len = 0;
    int max = 0;
    while ((c = getchar()) != EOF) {
        if (whitespace(c) && len >= 1) {
            /* end of word */
            ++words[len];
            max = MAX(max, words[len]);
            len = 0;
        } else {
            /* beginning or middle of word */
            ++len;
        }
    }

    /* print histogram */
    int step = MAX(max / TERMINAL_WIDTH, 1);
    for (int i = 0; i < WORD_LENGTH_MAX; ++i) {
        int stars = words[i] / step;
        if (words[i] > 0) {
            printf("%6d ", i);
            for (int j = 0; j < stars; ++j) putchar('*');
            printf(" %d\n", words[i]);
        }
    }

    return 0;
}

/*
  clang-format off

     1 ******************************************************************************** 2323
     2 *************************** 796
     3 ***************************** 866
     4 ************************* 747
     5 *************** 463
     6 ****************** 526
     7 ************** 409
     8 *********** 320
     9 ********* 261
    10 **** 144
    11 *** 112
    12 ** 60
    13 * 37
    14  22
    15  12
    16  3
    17  4
    18  3
    19  3
    20  4
    21  7
    22  1
    23  3
    25  1
    26  1
    27  1
    28  1
    29  1
    30  1
    33  1
    36  2
    54  1
   135  1

  clang-format on
*/
