/*
* Write a function reverse(s) that reverses the character string s. 
* Use it to write a program that reverses its input a line at a time.
*/

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
int reverse(char from[], int len, char to[]);

int main() {
	int len;
	char line[MAXLINE];
	char reverse_line[MAXLINE];
	int reverse_len;

	while ((len = get_line(line, MAXLINE)) > 0) {
		reverse_len = reverse(line, len, reverse_line);
		printf("%s", reverse_line);
	}
	return 0;
}

int reverse(char from[], int len, char to[]) {
	int i = 0;

	while (--len > 0) {
		to[i] = from[len - 1];
		i++;
	}
	to[i] = '\n';
	to[i + 1] = '\0';
	return i;
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