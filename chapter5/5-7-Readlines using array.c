/*
* Rewrite readlines to store lines in an array supplied by main, 
* rather than calling alloc to maintain storage. How much faster is the program?
*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     /* max #line to be stored */
#define MAXLEN 1000     /* max len of any input line */

char *lineptr[MAXLINES];  /* ponters to text lines */
char *lines[MAXLINES][MAXLEN];


int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
	int nlines;     /* number of input lines read */

	if ((nlines = readlines2(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}


#define ALLOCSIZE 10000 /* size of available space */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
		if (nlines >= MAXLINES || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';  /* delete newline */
			strcpy_s(p, len, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* readlines: read input lines and store in two dimension array:lines*/
int readlines2(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(lines[nlines], MAXLEN)) > 0)
		if (nlines >= MAXLINES)
			return -1;
		else {
			lines[nlines][len - 1] = '\0';  /* delete newline */
			lineptr[nlines++] = lines[nlines];
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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

/* get line into s, return length */
int getline(char *s, int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		*s++ = c;
	}
	if (c == '\n') {
		*s++ = c;
		++i;
	}
	*s = '\0';
	return i;
}
