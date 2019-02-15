/* ex.4.4 */

/* Add the commands to print the top elements of the stack without */
/* popping, to duplicate it, and to swap the top two elements. Add a */
/* command to clear the stack. */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100  /* max size of operand of operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getop(char[]);
void push(double);
double pop();
double top();
int getch(void);
void ungetch(int);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER: {
                push(atof(s));
                break;
            }
            case '+': {
                push(pop() + pop());
                break;
            }
            case '-': {
                op2 = pop();
                push(pop() - op2);
                break;
            }
            case '*': {
                push(pop() * pop());
                break;
            }
            case '/': {
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            }
            case '%': {
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            }
            case 'P': {
                /* Print stack */
                printf("\tstack: ");
                for (int i = 0; i < sp; ++i) {
                    printf("%.8g ", val[i]);
                }
                printf("\n");
                break;
            }
            case 'C': {
                /* Clear stack */
                sp = 0;
                break;
            }
            case 'S': {
                /* swap values on top */
                op2 = pop();
                double t = pop();
                push(op2);
                push(t);
                break;
            }
            case 'D': {
                /* duplicate value on top */
                push(top());
                break;
            }
            case '\n': {
                printf("\t%.8g\n", pop());
                break;
            }
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

/* provisions */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* top: return top value from stack */
double top(void) {
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    /* not a number */
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }

    i = 0;

    if (c == '-') {
        int next = getch();
        if (isdigit(next)) {
            s[++i] = next;
            c = next;
        } else {
            ungetch(next);
            return c;
        }
    }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF) ungetch(c);

    return NUMBER;
}

/* get a (possibly pushed-back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
