/*
* Write the function strindex(s,t) which returns the position of 
* the rightmost occurrence of t in s, or -1 if there is none.
*/

#include <stdio.h>
#define MAXLINE 1000

int strrindex(char[], char[]);
int get_line(char line[], int maxline);

char pattern[] = "ould";

int main()
{
	int len, pos;
	char line[MAXLINE];
	int number = 200;

	while ((len = get_line(line, MAXLINE)) > 0) {
		pos = strrindex(line, pattern);
		printf("position of rightmost occurrence of %s in %sis %d\n", pattern, line, pos);
	}

	return 0;

}

/* return position of rightmost occurrence of t in s, -1 if none */
int strrindex(char s[], char t[]) {
	int i, j, k;
	int rightest_p = -1;  /* rightmost position */

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k];)
			j++, k++;
		if (k > 0 && t[k] == '\0')
			rightest_p =i;  /* once find t in s, update rightest_p */
	}
	return rightest_p;
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


