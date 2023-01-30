/*
* Write a recursive version of the function reverse(s), which reverses the string s in place.
*/

#include <stdio.h>
#define MAXLINE 1000

void reverse(char s[], int start, int end);

int main()
{
	int len;
	char s[] = "-123456789";
	for (len = 0; s[len] != '\0'; len++)
		;
	reverse(s, 0, len - 1);
	printf("reversed s: %s\n", s);

	return 0;

}

/* reverse s */
void reverse(char s[], int start, int end) {

	if (start < end) {
		int temp = s[end];
		s[end] = s[start];
		s[start] = temp;

		reverse(s, start + 1, end - 1);
	}

}