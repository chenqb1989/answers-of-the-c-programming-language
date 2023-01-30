/*
* Write a function expand(s1,s2) that expands shorthand notations like a-z 
* in the string s1 into the equivalent complete list abc…xyz in s2. 
* Allow for letters of either case and digits, and be prepared to handle
* cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

int  get_line(char[], int);
void expand(char[], int len, char[]);  /* expands shorthand notations to equivalent complete list */


int main()
{
	int len;
	char line[MAXLINE];
	char expand_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		expand(line, len, expand_line);
		printf("%s", expand_line);
	}
	return 0;

}

void expand(char from[], int len, char to[]) {
	int i, j;
	i = j = 0;
	for (; from[i] != '\0'; i++) {
		if (from[i] == '-') {
			if (i == 0 || i == (len - 1))
				to[j++] = '-';
			else {
				char last = from[i - 1];
				char next = from[i + 1];
				if (isalnum(last) && isalnum(next) && (last < next)) {  /* isalnum is true when isalpha or isdigit is true */
					j--;  /* deletes to[j-1] */
					while (last <= next) {
						to[j++] = last;
						last += 1;
					}
					i++; /* from[i+1] is last, which has been added to array 'to', so i should add 1 */
				}
				else
					to[j++] = '-';
			}
		}
		else
			to[j++] = from[i];
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