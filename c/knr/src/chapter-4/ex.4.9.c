/* ex.4.9 */

/* Our getch and ungetch do not handle a pushed-back EOF */
/* correctly. Decide what their properties ought to be if an EOF is */
/* pushed back, then implement your design. */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch(int);
void ungets(const char[]);

void tests() {
    ungetch(EOF);
    ungets("hello");

    assert(getch() == 'h');
    assert(getch() == 'e');
    assert(getch() == 'l');
    assert(getch() == 'l');
    assert(getch() == 'o');
    assert(bufp == 0);
}

int main() { tests(); }

/* push back whole string onto input buffer */
void ungets(const char s[]) {
    size_t len = strlen(s);
    for (int i = len - 1; i >= 0; --i) ungetch(s[i]);
}

/* get a (possibly pushed-back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else if (c != EOF) /* just ignore pushed back eofs */
        buf[bufp++] = c;
}
