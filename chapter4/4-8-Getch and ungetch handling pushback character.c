/*
* Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define BUFSIZE 1000

int getch(void);
void ungetch(void);

char buf = ' ';

int main()
{
	int c;

	c = 'c';
	ungetch(c);
	while ((c = getch()) != EOF)
		putchar(c);
	return 0;

}


int getch(void) {
	char out;
	if (buf == ' ')
		out = getchar();
	else {
		out = buf;
		buf = ' ';
	}
	return out;
}

void ungetch(int c) {  /* push character back on input */
	if (buf != ' ')
		printf("ungetch: already has one charater of pushback\n");
	else
		buf = c;
}

