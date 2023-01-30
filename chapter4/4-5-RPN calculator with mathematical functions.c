/*
* Add access to library functions like sin, exp, and pow.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAXLINE 1000
#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* max depth of val stack */
#define BUFSIZE 100
#define ALPHA 'a'  /* signal that an alpha was found */

double atof(char[]);
int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void print_stack(void);
void copy_stack(void);
void swap_stack(void);
void clear_stack(void);
void print_top_stack(void);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type)	
		{
		case NUMBER:
			push(atof(s));
			break;
		case ALPHA:   /* if get alpha, then check exp, sin, or pow */
			if (strcmp(s, "exp") == 0) {
				push(exp(pop()));
			}
			else if (strcmp(s, "sin") == 0) {
				push(sinh(pop()));
			}
			else if (strcmp(s, "pow") == 0) {
				op2 = pop();
				push(pow(pop(), op2));
			}
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
			printf("error: unkown command %s\n", s);
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

/* print top value of stack */
void print_top_stack(void) {
	if (sp > 0)
		printf("top value: %.4f", val[sp - 1]);
	else
	{
		printf("print error: stack empty\n");
	}
}

/* copy top value of stack */
void copy_stack(void) {
	printf("copy top value of stack\n");
	if (sp > 0) {
		val[sp] = val[sp - 1];
		sp++;
	}
	else
	{
		printf("copy error: stack empty\n");
	}
}

/* swap top two values of stack */
void swap_stack(void) {
	printf("swap top two values of stack\n");
	if (sp > 1) {
		double temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp;
	}
	else
	{
		printf("swap error: elements number is smaller than two\n");
	}
}

/* clear stack */
void clear_stack(void) {
	printf("clear stack\n");
	while (--sp > 0)
		val[sp] = 0.0;
}

/* print all value of stack */
void print_stack(void) {
	int i = sp;
	if (i > 0) {
		while (--i > 0)
			printf("%.4f ", val[i]);
		printf("\n");
	}
	else
	{
		printf("print error: stack empty\n");
	}
}

/* getop: get next operator or numeric operand */
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && !isalpha(c))
		return c; /* not a number or alpha */

	i = 0;
	if (isalpha(c))  /* collect alpha */
	{
		while (isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
		return ALPHA;
	}
		
	if (c == '-') {  /* when c = '-', check it is negative sign or minus sign */
		if ((c = getch()) == ' ' || c == '\t')
			return '-';
		else
			s[++i] = c;
	}
	if (isdigit(c))  /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')  /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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



/* convert string s to double */
double atof(char s[]) {
	double val, power, result;
	int i, sign, exponent;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;

	result = sign * val / power;
	for (exponent = 0; isdigit(s[i]); i++) {
		exponent = 10 * exponent + (s[i] - '0');
	}
	for (int j = 0; j < exponent; j++)
		result = 10.0 * result;
	return result;
}



