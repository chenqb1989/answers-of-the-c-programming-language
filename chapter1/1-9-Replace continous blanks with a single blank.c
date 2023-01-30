/* 
* Write a program to copy its input to its output, 
* replacing each string of one or more blanks by a single blank.
*/

#include <stdio.h>

int main(void)
{
	int c;
	int last_c; 
	while ((c = getchar()) != EOF) {
		if (c != ' ' || last_c != ' ') {
			putchar(c);  
		}
		last_c = c;
	}
	return 0;
}