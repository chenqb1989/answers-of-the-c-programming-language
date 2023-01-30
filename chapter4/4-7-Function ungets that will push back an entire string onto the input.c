/*
* Write a routine ungets(s) that will push back an entire string onto the input. 
* Should ungets know about buf and bufp, or should it just use ungetch?
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define BUFSIZE 1000

int getch(void);
void ungetch(void);
int get_line(char, int);
void ungets(char, int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int main()
{
	int len, c;
	char s[MAXLINE];

	len = get_line(s, MAXLINE);
	ungets(s, len);

	while ((c = getch()) != EOF)
		putchar(c);
	return 0;

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

void ungets(char s[], int l) {  /* push string s back to buf */
	while (l > 0)
		ungetch(s[--l]);
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
