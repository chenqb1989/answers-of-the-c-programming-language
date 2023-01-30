/*
* Extend atof to handle scientific notation of the form 123.45e-6 
* where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

double atof(char[]);
int get_line(char line[], int maxline);

int main()
{
	int len;
	double result;
	char line[MAXLINE];
	int number = 200;

	while ((len = get_line(line, MAXLINE)) > 0) {
		result = atof(line);
		printf("result: %f\n", result);
	}

	return 0;

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


