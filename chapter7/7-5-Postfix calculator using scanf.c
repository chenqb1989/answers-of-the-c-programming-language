/*
* Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXOP 100  /* max size of operand or operator */
#define NUMBER_INT '0' /* signal that an int type number was found */
#define NUMBER_FLOAT '1' /* signal that a float type number was found */
#define MAXVAL 100 /* max depth of val stack */
#define BUFSIZE 100

int getop();
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int ival;
float fval;

int main()
{
	int type;
	double op2;

	while ((type = getop()) != EOF) {
		switch (type)	
		{
		case NUMBER_INT:
			push(ival);
			break;
        case NUMBER_FLOAT:
			push(fval);
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
			push(((int) pop()) % ((int) op2));
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unkown command\n");
			break;
		}
	}

	return 0;

}

/* push f onto value stack */
void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop and return top value from stack */
double pop(void) {
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;	
	}
}

/* getop: get next operator or numeric operand */
int getop() {
    char s[MAXOP];
    char cval;
    char c;
    int i = 0;
    while ((s[i++] = c = getch()) == ' ' || c == '\t')
        ;
    if (!isdigit(c) && c != '.')
		return c; /* not a number */
    
    while ((c = getch()) != ' ' && c != '\t' && c != '\n')
        s[i++] = c;
	if (c != EOF)
    {
        s[i] = '\0';
        ungetch(c);
        
        if (sscanf(s, "%f", &fval) == 1)
            return NUMBER_FLOAT;
        else if (sscanf(s, "%d", &ival) == 1)
            return NUMBER_INT;
    }
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}