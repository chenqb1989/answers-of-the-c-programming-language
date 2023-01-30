/*
* Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.
*/
#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);

int main() {
	int len;
	char line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		for (int i = len - 2; i >= 0; i--) {  /* delete space and tab from penultimate element*/
			if (line[i] == '\t' || line[i] == ' ') {
				line[i] = '\n';
				line[i + 1] = '\0';
				len--;
			}
			else {  /* if find non space and tab element, jump out for loop */
				break;
			}
		}
		
		if (len <= 1) {
			printf("delete blank line!\n");
			line[0] = '\0';
		}
		printf("%s", line);
	}
	return 0;
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
