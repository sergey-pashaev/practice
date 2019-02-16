/* ex.4.8 */

/* Suppose that there will never be more than one character of */
/* pushback. Modify getch and ungetch accordingly. */

#include <assert.h>
#include <stdio.h>
#include <string.h>

char buf;         /* buffered character */
int buf_full = 0; /* indicate full buffer (one char) */

int getch(void);
void ungetch(int);

void tests() {
    ungetch('a');
    assert(getch() == 'a');
    ungetch('b');
    /* ungetch('c');  should fail */
}

int main() { tests(); }

/* get a (possibly pushed-back) character */
int getch(void) {
    if (buf_full) {
        buf_full = 0;
        return buf;
    }

    return getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (buf_full)
        printf("ungetch: too many characters\n");
    else {
        buf = c;
        buf_full = 1;
    }
}
