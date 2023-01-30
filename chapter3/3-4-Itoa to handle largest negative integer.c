/*
* In a two’s complement number representation, our version of itoa does not handle 
* the largest negative number, that is, the value of n equal to -(2wordsize-1). 
* Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
*/

#include <stdio.h>
#include <limits.h>
#define MAXLINE 1000

void itoa(int, char[]);  /* convert n to characters in s */
void reverse(char[]); /* reverse s */


int main()
{
	int len;
	char s[MAXLINE];
	int number = INT_MIN;
	itoa(number, s);
	printf("converted s: %s", s);

	return 0;

}

void itoa(int n, char s[]) {
	int i, sign;
	unsigned int m; /* use unsigned int for -2^wordsize, because 2^wordsize exceed the range of signed int */

	if ((sign = n) < 0)
		m = -n;
	i = 0;
	do {
		s[i++] = m % 10 + '0';
	} while ((m /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int i, j, len;
	for (i = 0; s[i] != '\0'; i++);  /* compute length of s */
	len = i;

	for (j = 0; j < (len / 2); j++) {
		int temp = s[j];
		s[j] = s[len - 1 - j];
		s[len - 1 - j] = temp;
	}
}