/* ex.4.10 */

/* An alternate organization uses getline to read an entire input line; */
/* this makes getch and ungetch unnecessary. Revise the calculator to */
/* use this approach. */

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
#define MAXLINE 1024 /* max input line length */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
double var_val[MAXVAR]; /* variable values */
char var[MAXVAL];       /* variable stack */
int vp = 0;             /* next free variable stack position */
double prev_val = 0.0;  /* last value evaluated */
int lp = 0;             /* input line pointer */

int getop(char[], char[]);
void push(double);
double pop();
double top();
void pushv(char);
char popv();
int getline_(char[], int);

int main() {
    int type;
    double op2;
    char s[MAXOP];
    char line[MAXLINE];
    int len;

    for (int i = 0; i < MAXVAR; ++i) var_val[i] = 0.0;

    while ((len = getline_(line, MAXLINE)) > 1) {
        if (len > 0) {
            lp = 0;
            do {
                type = getop(s, line);
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
            } while (type != '\n');
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
int getop(char s[], char line[]) {
    int i, c;

    if (line[lp] == '\n') return '\n';

    while (line[lp] == ' ' || line[lp] == '\t') ++lp;

    s[1] = '\0';

    c = line[lp];
    if (c >= 'a' && c <= 'z') {
        ++lp;
        return VAR;
    }

    /* not a number */
    if (!isdigit(c) && c != '.' && c != '-') {
        ++lp;
        return c;
    }

    i = 0;

    if (c == '-') {
        int next = line[lp + 1];
        if (isdigit(next)) {
            s[i++] = c;
            ++lp;
        } else {
            return c;
        }
    }

    /* collect integer part */
    while (isdigit(line[lp])) s[i++] = line[lp++];

    if (line[lp] == '.') { /* collect fraction part */
        s[i++] = line[lp++];
        while (isdigit(line[lp])) s[i++] = line[lp++];
    }

    s[i] = '\0';

    return NUMBER;
}

/* getline: read a line into s, return length */
int getline_(char s[], int lim) {
    int c;
    int i;

    for (i = 0; i < lim - 1; ++i) {
        if ((c = getchar()) != EOF) {
            if (c != '\n') {
                s[i] = c;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
