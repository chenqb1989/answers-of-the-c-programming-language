/* 
* Write a version of itoa that accepts three arguments instead of two. 
* The third argument is a minimum field width; the converted number must 
* be padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#define MAXLINE 1000

void itoa(int, char[], int);
void reverse(char[]);  /* reverse s */


int main()
{
	int len;
	char s[MAXLINE];
	int number = 200;
	itoa(number, s, 10);
	printf("converted s: %s\n", s);

	return 0;

}

/* convert s to integer with width w */
void itoa(int n, char s[], int w) {
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	
	while (i < w)  /* pad blanks to length w */
		s[i++] = ' ';
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
