#include "func.h"

int bufp = 0, sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];

int getch1(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch1(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else {
        if (c == EOF && bufp > 0) {
            if (buf[0] == EOF) {
                printf("warning: EOF already in buffer, ignored. ");
                return ;
            }
            int i = bufp;
            while (i > 0) {
                buf[i] = buf[i-1];
                i--;
                buf[0] = EOF;
            }
            bufp++;
        } else {
            buf[bufp++] = c;
        }
    }
}

int getop(char s[]) {
    int i, c, isnumber = 0;
    while ((s[0] = c = getch1()) == ' ' || c == '\t');
    if (c == '-' || c == '+') {
        char cn = getch1();
        if (isdigit(cn))
            isnumber = 1;
        ungetch1(cn);
    }
    if (isnumber || isdigit(c) || c == '.')  {
    } else {
        return c;
    }
    s[1] = '\0';
    i = 0;
    
    if (c == '-' || c == '+') {
        s[++i] = c = getch1();
        s[i+1] = '\0';
    }
    
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch1()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch1()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch1(c);
    return NUMBER;
}


void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void run(void) {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int)pop() % (int)op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
}

