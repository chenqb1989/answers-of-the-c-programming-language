/*
* Write a pointer version of the function strcat that we showed in Chapter 2: 
* strcat(s,t) copies the string t to the end of s.
*/

#include <stdio.h>
#define MAXSIZE 100

void strcat(char *s, char *t);

int main()
{
	char src[MAXSIZE], dest[MAXSIZE];

	strcpy(src, "This is source ");
	strcpy(dest, "This is destination");

	strcat(dest, src);

	printf("value of dest :%s\n", dest);

	return 0;

}

/* concat t to the end of s */
void strcat(char *s, char *t) {
	while (*s)
		s++;
	while (*s++ = *t++)
		;
	*s = '\0';
}