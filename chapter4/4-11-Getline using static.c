/*
* Modify getop so that it doesn’t need to use ungetch. Hint: use an internal static variable.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* max depth of val stack */

double atof(char[]);
int getop(char[]);
void push(double);
double pop(void);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

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
			push(((int)pop()) % ((int)op2));
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
	c = ' ';
	static char buf;  /* define internal static variable */

	if (buf != '\0')
		s[0] = c = buf;
	if (c == ' ' || c == '\t')
		while ((s[0] = c = getchar()) == ' ' || c == '\t')
			;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */

	i = 0;
	if (isdigit(c))  /* collect integer part */
		while (isdigit(s[++i] = c = getchar()))
			;
	if (c == '.')  /* collect fraction part */
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';
	if (c != EOF)
		buf = c;
	return NUMBER;
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



