/*
* Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?
*/

#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100
#define SIZE 10

int getch(void);
void ungetch(int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getfloat(float *);

int main()
{
	int n;
	float array[SIZE];
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;

	for (int i = 0; array[i] != 0; i++)
		printf("%.4f ", array[i]);

	return 0;

}

int getfloat(float *pn) {
	int c, sign;


	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
	}
	
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.') {  /* collect fraction part */
		for (c = getch(); isdigit(c); c = getch())
			*pn = (10 * *pn + (c - '0')) / 10;
	}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
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