/*
* Write a program detab that replaces tabs in the input with the proper 
* number of blanks to space to the next tab stop. Assume a fixed set of 
* tab stops, say every n columns. Should n be a variable or a symbolic parameter?
*/

#include <stdio.h>
#define MAXLINE 1000
#define N 5

int get_line(char line[], int maxline);
void detab(char from[], int len, char to[]);

int main() {
	int len;
	char line[MAXLINE];
	char detab_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		detab(line, len, detab_line);
		printf("%s", detab_line);
	}
	return 0;
}


void detab(char from[], int len, char to[]) {
	int i, j;
	for (i = j = 0; i < len; i++) {
		int blank_num = N - (j % N);
		if (from[i] == '\t') {
			while (blank_num-- > 0) {
				to[j++] = ' ';
			}
		}
		else {
			to[j++] = from[i];
		}
	}
	to[j] = '\0';
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
