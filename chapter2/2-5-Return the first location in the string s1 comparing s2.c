/*
* Write the function any(s1,s2), which returns the first location in a string s1 
* where any character from the string s2 occurs, or -1 if s1 contains no characters
* from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)
*/

#include <stdio.h>
#include <ctype.h>


int any(char s1[], char s2[]);  /* returns the first location in s1 where any character from s2 occurs, or -1 if s1 contains no characters of s2 */
int isin(char c, char s[]);  /* check if c in s */

main()
{
	char s1[] = "hello word!";
	char s2[] = "abw";
	int location = any(s1, s2);
	printf("location of s1 in s2: %d\n", location);

}

int isin(char c, char s[]) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (c == s[i]) {
			return 1;
		}
	}
	return 0;
}

int any(char s1[], char s2[]) {
	
	for (int i = 0; s1[i] != '\0'; i++) {
		if (isin(s1[i], s2) == 1) {
			return i;
		}
	}
	return -1;
}