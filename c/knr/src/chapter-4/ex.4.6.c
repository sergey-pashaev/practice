/* ex.4.6 */

/* Add commands for handling variables. (It's easy to provide */
/* twenty-six variables with single-letter names.) Add a variable for */
/* the most recently printed value. */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100  /* max size of operand of operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXVAR 26 /* max variables count */
#define VAR 'a'

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
double var_val[MAXVAR]; /* variable values */
char var[MAXVAL];       /* variable stack */
int vp = 0;             /* next free variable stack position */
double prev_val = 0.0;  /* last value evaluated */

int getop(char[]);
void push(double);
double pop();
double top();
void pushv(char);
char popv();
int getch(void);
void ungetch(int);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    for (int i = 0; i < MAXVAR; ++i) var_val[i] = 0.0;

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER: {
                push(atof(s));
                break;
            }
            case VAR: {
                char var = s[0];
                pushv(var);
                push(var_val[var - VAR]);
                break;
            }
            case '=': {
                pop(); /* forget old var value */
                var_val[popv() - VAR] = top();
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
            case '^': {
                op2 = pop();
                push(pow(pop(), op2));
                break;
            }
            case 'E': {
                push(exp(pop()));
                break;
            }
            case '$': {
                /* well, $ is look alike some vertical sine :) */
                push(sin(pop()));
                break;
            }
            case 'P': {
                /* Print stack */
                printf("\tstack: ");
                for (int i = 0; i < sp; ++i) {
                    printf("%.8g ", val[i]);
                }
                printf("\n");
                printf("\tvars: ");
                for (int i = 0; i < MAXVAR; ++i) {
                    printf("%c=%.8g ", VAR + i, var_val[VAR + i]);
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
            case '@': {
                push(prev_val);
                break;
            }
            case '\n': {
                prev_val = pop();
                printf("\t%.8g\n", prev_val);
                break;
            }
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

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

/* pushv: push v onto variable stack */
void pushv(char v) {
    if (vp < MAXVAL)
        var[vp++] = v;
    else
        printf("error: variable stack full, can't push %c\n", v);
}

/* popv: pop and return top variable from stack */
char popv(void) {
    if (vp > 0)
        return var[--vp];
    else {
        printf("error: variable stack empty\n");
        return '\0';
    }
}

/* getop: get next character or numeric operand or variable */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (c >= 'a' && c <= 'z') return VAR;

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
