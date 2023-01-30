/*
* Write a function escape(s,t) that converts characters like newline 
* and tab into visible escape sequences like n and t as it copies the 
* string t to s. Use a switch. Write a function for the other direction as well, 
* converting escape sequences into the real characters.
*/

#include <stdio.h>
#define MAXLINE 1000

int  get_string(char[], int);
void escape(char[], char[]);  /* convert newline and tab into visible escape sequences like \n and \t */
void escape2(char[], char[]);  /* convert escape sequences into real characters */


int main()
{
	int len;
	char s[MAXLINE];
	char escape_s[MAXLINE];

	len = get_string(s, MAXLINE); 
	escape2(escape_s, s);
	printf("%s", escape_s);
	return 0;

}

void escape(char to[], char from[]) {
	int i, j;
	i = j = 0;
	for (; from[i] != '\0'; i++) {
		switch (from[i])
		{
		case '\n':
			to[j++] = '\\';
			to[j++] = 'n';
			break;
		case '\t':
			to[j++] = '\\';
			to[j++] = 't';
			break;
		default:
			to[j++] = from[i];
			break;
		}
	}
	to[j] = '\0';
}

void escape2(char to[], char from[]) {
	int i, j;
	i = j = 0;
	for (; from[i] != '\0'; i++) {
		if (from[i] == '\\') {
			switch (from[++i])
			{
			case 'n':
				to[j++] = '\n';
				break;
			case 't':
				to[j++] = '\t';
				break;
			default:
				to[j++] = '\\';
				to[j++] = from[i];
				break;
			}
		}
		else
			to[j++] = from[i];
		
	}
	to[j] = '\0';
}

int get_string(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF; ++i)
		s[i] = c;

	s[i] = '\0';

	return i;
}