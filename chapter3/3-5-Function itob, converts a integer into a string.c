/*
* Write the function itob(n,s,b) that converts the integer n into a base b character
* representation in the string s. In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/

#include <stdio.h>
#define MAXLINE 1000

void itob(int, char[], int); 
void reverse(char[]);  /* reverse s */


int main()
{
	int len;
	char s[MAXLINE];
	int number = 200;
	itob(number, s, 2);
	printf("converted s: %s\n", s);

	return 0;

}

void itob(int n, char s[], int b) {
	int i, sign;
	int r;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		r = n % b;
		if (r < 10)
			s[i++] = r + '0';
		else
			s[i++] = r - 10 + 'A';		
	} while ((n /= b) > 0);
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
