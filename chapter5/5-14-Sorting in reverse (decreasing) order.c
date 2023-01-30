/*
* Modify the sort program to handle a -r flag, which indicates sorting in 
* reverse (decreasing) order. Be sure that -r works with -n.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1000
#define MAXLEN 5000
#define ALLOCSIZE 10000 /* size of available space */

char *lineptr[MAXLINES];  /* ponters to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int);
int get_line(char line[], int maxline);

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int);
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
	int nlines;     /* number of input lines read */
	int numeric = 0;    /* 1 if numeric sort */
	int reverse = 0;    /* 1 if reverse sort */
	int c;

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0])
			switch (c)
			{
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			default:
				printf("entab: illegal option %c\n", c);
				break;
			}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		my_qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : strcmp), reverse);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
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
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
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

/* my_qsort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse){
	int i,last;
    void swap(void *v[], int, int);

    if(left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;

    for(i = left + 1; i <= right; i++) {
		if (reverse) {
			if((*comp)(v[i],v[left]) > 0)
            	swap(v, ++last, i);
		}
		else {
			if((*comp)(v[i],v[left]) < 0)
            	swap(v, ++last, i);
		}
	}
        
    swap(v, left, last);

    my_qsort(v, left, last - 1, comp, reverse);
    my_qsort(v, last + 1, right, comp, reverse);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
	double v1,v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if( v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;

}


void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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