/*
* Write the program expr, which evaluates a reverse Polish expression from the command line, 
* where each operator or operand is a separate argument.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXOP 100  /* max size of operand or operator */
#define MAXVAL 100 /* max depth of val stack */

double atof(char[]);
void push(double);
double pop(void);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

int main(int argc, char *argv[])
{
	double op2;
	char s[MAXOP];
	int c, i;

	while (--argc > 0 && ++argv) {  /* loop all argumants */
		c = *argv[0];
		switch (c)
		{
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
		default:
			i = 0;
			if (isdigit(c))  /* if is digit, collect integer part */
				while (isdigit(s[i++] = c = *argv[0]))
					argv[0]++;
			else
			{
				printf("error: unkown command %s\n", s);
				break;
			}
			
			if (c == '.')  /* collect fraction part */
			{
				argv[0]++;
				while (isdigit(s[i++] = c = *argv[0]))
					argv[0]++;
			}
				
			s[i] = '\0';
			push(atof(s));
			break;
			}
	}
	printf("result: %.4f\n", pop());
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




