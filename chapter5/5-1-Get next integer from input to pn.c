/*
* As written, getint treats a + or - not followed by a digit as a valid representation of zero. 
* Fix it to push such a character back on the input.
*/

#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100
#define SIZE 10

int getch(void);
void ungetch(int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getint(int *);

int main()
{
	int n, array[SIZE], getint(int *);
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;

	for (int i = 0; array[i] != 0; i++)
		printf("%d ", array[i]);

	return 0;

}

int getint(int *pn) {
	int c, sign, buf_c;


	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		buf_c = c;
		c = getch();

		if (!isdigit(c)) {
			ungetch(buf_c);  /* push back buf_c on the input */
		}
	}
	
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
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