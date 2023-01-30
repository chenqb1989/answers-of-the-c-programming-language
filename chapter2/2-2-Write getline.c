/*
* Write a loop equivalent to the for loop above without using && or ||.
*/

#include <stdio.h>
#define LIM 10

main()
{
	char c;
	char s[LIM];
	for (int i = 0; i < LIM - 1; i++) {
		if ((c = getchar()) == '\n') {
			break;
		}
		else if(c == EOF){
			break;
		}
		else {
			s[i] = c;
		}
	}
}