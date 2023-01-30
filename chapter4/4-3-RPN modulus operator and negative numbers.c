/*
* Given the basic framework, it’s straightforward to extend the calculator. 
* Add the modulus (%) operator and provisions for negative numbers.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* max depth of val stack */
#define BUFSIZE 100

double atof(char[]);
int get_line(char line[], int maxline);
int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

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

/* getop: get next operator or numeric operand */
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c; /* not a number */

	i = 0;
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



