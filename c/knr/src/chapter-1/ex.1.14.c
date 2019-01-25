/* ex.1.14 */

/* Write a program to print a histogram of the frequencies of different */
/* characters in its input. */

#include <stdio.h>

#define CHAR_MAX 256
#define TERMINAL_WIDTH 80

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main() {
    int chars[CHAR_MAX];
    for (int i = 0; i < CHAR_MAX; ++i) {
        chars[i] = 0;
    }

    /* count chars */
    int c;
    int max = 0;
    while ((c = getchar()) != EOF) {
        ++chars[c];
        max = MAX(max, chars[c]);
    }

    /* print histogram */
    int step = MAX(max / TERMINAL_WIDTH, 1);
    for (int i = 0; i < CHAR_MAX; ++i) {
        int stars = chars[i] / step;
        if (chars[i] > 0) {
            if (i == '\t') {
                printf("\\t ");
            } else if (i == '\n') {
                printf("\\n ");
            } else if (i == '\r') {
                printf("\\r ");
            } else if (i == '\\') {
                printf("\\\\ ");
            } else {
                printf("%c ", i);
            }
            for (int j = 0; j < stars; ++j) putchar('*');
            printf(" %d\n", chars[i]);
        }
    }

    return 0;
}

/*
  clang-format off

$ man man | ./ex.1.14

\n **** 516
  ******************************************************************************** 9396
"  27
$  45
%  13
'  32
(  93
)  93
*  1
, ** 298
- ** 329
. *** 353
/  55
0  29
1  72
2  23
3  30
4  6
5  14
6  10
7  26
8  13
9  13
:  11
;  7
<  7
=  17
>  8
?  7
@  6
A  92
B  14
C  25
D  27
E  91
F  41
G  31
H  21
I  85
J  1
K  8
L  32
M  70
N  96
O  60
P  53
Q  4
R  45
S * 117
T * 134
U  21
V  9
W  18
X  15
Y  8
Z  6
[  88
\\  14
]  88
_  18
`  11
a ***************** 2037
b ** 320
c ****** 753
d ****** 767
e ********************* 2495
f **** 580
g **** 487
h ******* 838
i ************** 1688
j  14
k  75
l ******** 1046
m ***** 673
n ************* 1599
o ************* 1555
p ****** 756
q  26
r ********** 1249
s ************* 1553
t **************** 1925
u ***** 690
v * 218
w ** 288
x  101
y ** 349
z  13
|  14
~  1
�  79
�  24
�  4
�  45
�  1
�  1
�  1
�  2
�  2
�  1
�  1
�  2
�  1
�  79

  clang-format on
*/
