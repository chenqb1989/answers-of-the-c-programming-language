/*
* Write a program to check a C program for rudimentary syntax errors like 
* unmatched parentheses,brackets and braces. Don’t forget about quotes, 
* both single and double, escape sequences, and comments. 
* (This program is hard if you do it in full generality.)
*/

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
void check_syntax(char from[], int len);

int main() {
	int len;
	char line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		printf("line len:%d\n", len);
		check_syntax(line, len);
	}
	return 0;
}

void check_syntax(char from[], int len) {
	
	int i, j;
	i = j = 0;
	int parentheses_num, brackets_num, braces_num;
	int flag_c, flag_s;

	parentheses_num = brackets_num = braces_num = 0;
	flag_c = flag_s = 0;
	for (i = 0; i < len; i++) {

		if(from[i] == '\''){  /* handle character constants */
			flag_c = 1;
			for (; flag_c == 1; i++) {
				if (i < len - 1 && from[i + 1] == '\'') {
					if (from[i] == '\\') {
						if (from[i - 1] == '\\') { flag_c = 0; }  /* situations like  '**\'**'  */
					}
					else { flag_c = 0; } /* situations like   '**'  */
				}
			}
			if (from[i] != '\'') {
				printf("unmatched single quotes!\n");
			}
		}
		else if (from[i] == '\"'){  /* handle quoted strings */
			flag_s = 1;
			for (; flag_s == 1; i++) {
				if (i < len - 1 && from[i + 1] == '\"') {
					if (from[i] == '\\') {
						if (from[i - 1] == '\\') { flag_s = 0; }  /* situations like  "**\"**"  */
					}
					else { flag_s = 0; } /* situations like   "**"  */
				}
			}
			if (from[i] != '\"') {
				printf("unmatched double quotes!\n");
			}
		}

		else if (from[i] == '/') {  
			if (i < len - 1 && from[i + 1] == '/') {  /* handle double slash, skip to newline */
				while (from[i++] != '\n') {}
			}
			else if (i < len - 1 && from[i + 1] == '*') {  /* handle comment, skip to the end of comment */
				i = i + 2;
				while ((i < len - 1) && !((from[i] == '*') && (from[i + 1] == '/'))) {
					i++;
				}
				i = i + 1;
			}
			else {  /* slash but not double slash or comment, which is not legal */
				printf("wrong slash!");
			}
		}
		else if (from[i] == '(') {
			parentheses_num++;
		}
		else if (from[i] == ')') {
			parentheses_num--;
		}
		else if (from[i] == '[') {
			brackets_num++;
		}
		else if (from[i] == ']') {
			brackets_num--;
		}
		else if (from[i] == '{') {
			braces_num++;
		}
		else if (from[i] == '}') {
			braces_num--;
		}

	}
	if (parentheses_num != 0) {
		printf("unmatched parenthese!\n");
	}
	if (brackets_num != 0) {
		printf("unmatched brackets!\n");
	}
	if (braces_num != 0) {
		printf("unmatched braces!\n");
	}
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
