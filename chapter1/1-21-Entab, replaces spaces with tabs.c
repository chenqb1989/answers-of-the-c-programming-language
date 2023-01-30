/*
* Write a program entab that replaces strings of blanks by the minimum number 
* of tabs and blanks to achieve the same spacing. Use the same tab stops as for 
* detab. When either a tab or a single blank would suffice to reach a tab stop, 
* which should be given preference?
*/

#include <stdio.h>
#define MAXLINE 1000
#define TABINC 4

int get_line(char line[], int maxline);
void entab(char from[], int len, char to[]);

int main() {
	int len;
	char line[MAXLINE];
	char entab_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		entab(line, len, entab_line);
		printf("%s\n", entab_line);
	}
	return 0;
}


void entab(char from[], int len, char to[]) {
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
			tn = blank_len / TABINC;
			sn = blank_len % TABINC;

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
