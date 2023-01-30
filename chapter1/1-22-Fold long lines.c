/* 
* Write a program to fold long input lines into two or more shorter 
* lines after the last non-blank character that occurs before the n-th 
* column of input. Make sure your program does something ntelligent with 
* very long lines, and if there are no blanks or tabs before the specified column.
*/

#include <stdio.h>
#define MAXLINE 1000
#define N 4

int get_line(char line[], int maxline);
void fold(char from[], int len, char to[]);

int main() {
	int len;
	char line[MAXLINE];
	char fold_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		fold(line, len, fold_line);
		printf("%s\n", fold_line);
	}
	return 0;
}

void fold(char from[], int len, char to[]) {
	int column = 0;
	int blank_pos = 0;
	int pos = 0;  /* current position of a newline*/

	int i, j;
	i = j = 0;
	while (i < len) {

		if (pos >= N && (to[j-1] == ' ' || to[j-1] == '\t')) {  /* if pos is bigger than N and array 'to' ends with blank, then fold line */
			while ((j >= 1) && (to[j-1] == ' ' || to[j-1] == '\t')) {  /* find position of last blank */
				j--;
			}
			if (j > 0) {
				to[j] = '\n';  /* set position of last blank with '\n' */
				j++;
			}
			pos = 0;
		}
		else {
			pos++;
			to[j++] = from[i++];
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
