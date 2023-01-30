/*
* Adapt the ideas of printd to write a recursive version of itoa; 
* that is, convert an integer into a string by calling a recursive routine.
*/

#include <stdio.h>
#define MAXLINE 1000

void itoa(int, char[]);
int pos = 0;

int main()
{
	int len;
	char s[MAXLINE];
	int number = -2387320;
	itoa(number, s);
	printf("converted s: %s\n", s);

	return 0;

}

/* convert s to integer */
void itoa(int n, char s[]) {

	if (n < 0) {
		s[pos++] = '-';
		n = -n;
	}
	if (n / 10)
		itoa(n / 10, s);
	s[pos++] = n % 10 + '0';
	s[pos] = '\0';
}