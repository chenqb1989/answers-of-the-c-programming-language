/*
* Modify the program entab and detab (written as exercises in Chapter 1) to 
* accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000
#define N 5

int get_line(char line[], int maxline);
void detab(char from[], int len, char to[], int tabl);
void entab(char from[], int len, char to[], int tabl);
int atoi(char s[]);

int main(int argc, char *argv[]) {
	int len;
	char line[MAXLINE];
	char detab_line[MAXLINE];
	char entab_line[MAXLINE];
	int tabl = N;
	if (argc > 1)
		tabl = atoi(*++argv);

	/* test detab_line */
	// while ((len = get_line(line, MAXLINE)) > 0) {
	// 	detab(line, len, detab_line, tabl);
	// 	printf("%s", detab_line);
	// }
	
	/* test entab_line */
	while ((len = get_line(line, MAXLINE)) > 0) {
		entab(line, len, entab_line, tabl);
		printf("%s", entab_line);
	}

	return 0;
}


void detab(char from[], int len, char to[], int tabl) {
	int i, j;
	for (i = j = 0; i < len; i++) {
		int blank_num = tabl - (j % tabl);
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

void entab(char from[], int len, char to[], int tabl) {
	int i, j;
	int blank_len;        /*blank_len: blank length*/
	int tn, sn;			  /* tn: tab number; sn: space number*/

	i = j = 0;
	while (i < len) {
		if (from[i] == ' ') {
			blank_len = 0;
			while (from[i] == ' ') {
				blank_len++;
				i++;
			}
			tn = blank_len / tabl;
			sn = blank_len % tabl;

			while (tn-- > 0) {
				to[j++] = '\t';
			}
			while (sn-- > 0) {
				to[j++] = ' ';
			}
		}
		else {
			to[j++] = from[i++];
		}
	}
	to[j] = '\0';
}

/* convert string s to integer */
int atoi(char s[]) {
	int val, result;
	int i, sign;

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