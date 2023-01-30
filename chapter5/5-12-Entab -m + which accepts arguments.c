/*
* Extend entab and detab to accept the shorthand.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define N 5

int get_line(char line[], int maxline);
void detab(char from[], int len, char to[], int m, int n);
int atoi(char s[]);

int main(int argc, char *argv[]) {
	int len, c, m, n;
	char line[MAXLINE];
	char detab_line[MAXLINE];
	char entab_line[MAXLINE];
	int tabl = N;
	while (--argc > 0 && ++argv) {
		c = *argv[0];
		switch (c)
		{
		case '-':
			argv[0]++;
			m = atoi(*argv);
			break;
		case '+':
			argv[0]++;
			n = atoi(*argv);
			break;
		default:
			printf("entab: illegal option %c\n", c);
			break;
		}
	}

	/* test detab_line */
	while ((len = get_line(line, MAXLINE)) > 0) {
		detab(line, len, detab_line, m, n);
		printf("%s", detab_line);
	}
	

	return 0;
}


void detab(char from[], int len, char to[], int m, int n) {
	int i, j;
	i = j = 0;

	while(--m > 0)
		to[j++] = from[i++];

	for (; i < len; i++) {
		int blank_num = n - (j % n);
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