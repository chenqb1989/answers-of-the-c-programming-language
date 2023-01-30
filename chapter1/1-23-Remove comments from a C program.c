/* 
* Write a program to remove all comments from a C program. 
* Don’t forget to handle quoted strings and character constants properly. C comments don’t nest.
*/

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
void remove_comments(char from[], int len, char to[]);

int main() {
	int len;
	char line[MAXLINE];
	char remove_comments_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		remove_comments(line, len, remove_comments_line);
		printf("%s\n", remove_comments_line);
	}
	return 0;
}

void remove_comments(char from[], int len, char to[]) {
	
	int i, j;
	i = j = 0;
	while (i < len - 1) {

		if(from[i] == '\''){  /* handle character constants, just copy */
			to[j++] = from[i++];
			while ((to[j++] = from[i++]) != '\'') {}
		}
		else if (from[i] == '\"'){  /* handle quoted strings, just copy */
			to[j++] = from[i++];
			while ((to[j++] = from[i++]) != '"') {}
		}

		else if (from[i] == '/' && from[i + 1] == '/') {  /* handle double slash, skip to newline */
			while (from[i++] != '\n') {}
		}
		else if (from[i] == '/' && from[i + 1] == '*') {  /* handle comment, skip to the end of comment */
			i = i + 2;
			while ((i < len - 1) && !((from[i] == '*') && (from[i + 1] == '/'))) { 
				i++; 
			}
			i = i + 2;
		}
		else {
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
