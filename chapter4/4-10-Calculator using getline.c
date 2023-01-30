/*
* An alternate organization uses getline to read an entire input line; 
* this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* max depth of val stack */

double atof(char[]);
int get_line(char line[], int maxline);
int getop(char[], int, char[]);
void push(double);
double pop(void);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
int start_pos = 0; /* next position in line */

int main()
{
	int type, len;
	double op2;
	char s[MAXOP], line[MAXLINE];
	while ((len = get_line(line, MAXLINE)) != 0){
		start_pos = 0;  /* update start_pos */
		while (start_pos < len) {
			type = getop(line, len, s);
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
int getop(char line[], int len, char s[]) {
	int i, c;

	while ((start_pos < len) && ((s[0] = c = line[start_pos++]) == ' ' || c == '\t'))  /* make sure start_pos is smaller than len */
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */

	i = 0;
	if (isdigit(c))  /* collect integer part */
		while ((start_pos < len) && isdigit(s[++i] = c = line[start_pos++]))
			;
	if (c == '.')  /* collect fraction part */
		while ((start_pos < len) && isdigit(s[++i] = c = line[start_pos++]))
			;
	s[i] = '\0';
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

/* get line into s, return length */
int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}


