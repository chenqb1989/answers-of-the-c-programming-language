/*
* Write the program tail, which prints the last n lines of its input.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINES 1000
#define MAXLEN 5000
#define ALLOCSIZE 10000 /* size of available space */


char *lineptr[MAXLINES];  /* ponters to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int pnline);
int get_line(char line[], int maxline);
int atoi(char s[]);
char *alloc(int);

int main(int argc, char *argv[]) {
	int nlines;     /* number of input lines read */
	int c, pnline;  /* pnline: number of printed lines */

	while (--argc > 0 && ++argv) {
		c = *argv[0];
		switch (c)
		{
		case '-':
			argv[0]++;
			pnline = atoi(*argv);
			break;
		default:
			printf("entab: illegal option %c\n", c);
			break;
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		writelines(lineptr, nlines, pnline);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
	return 0;
}


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= MAXLINES || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';  /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int pnline) {
	int start_line = nlines - pnline;     /* start_line: begin to print from this line */
	if (start_line < 0)                   /* do nothing if pnline is bigger than nlines */
		return;
	lineptr += start_line;               /* update lineptr to start line */
	while (pnline-- > 0)
		printf("%s\n", *lineptr++);
}

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

/* convert string s to integer */
int atoi(char s[]) {
	int val, result;
	int i, sign;
	result = 0;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0; isdigit(s[i]); i++)
		val = 10 * val + (s[i] - '0');
	
	result = sign * val;
	return result;
}

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;      /* next free position */

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}