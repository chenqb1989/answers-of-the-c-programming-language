/*
* Write an alternative version of squeeze(s1,s2) that deletes each 
* character in s1 that matches any character in the string s2.
*/

#include <stdio.h>
#include <ctype.h>


void squeeze(char s1[], char s2[]);  /* delete each character in s1 that matches any character in s2 */
int isin(char c, char s[]);  /* check if c in s */

main()
{
	char s1[] = "hello word!";
	char s2[] = "abcdefghijklom";
	squeeze(s1, s2);
	printf("squeezed s1:%s\n", s1);

}

int isin(char c, char s[]) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (c == s[i]) {
			return 1;
		}
	}
	return 0;
}

void squeeze(char s1[], char s2[]) {
	int i, j;
	for (i = j = 0; s1[i] != '\0'; i++) {
		if (isin(s1[i], s2) == 0) {
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}