/*
* Write versions of the library functions strncpy, strncat, and strncmp, which 
* operate on at most the first n characters of their argument strings.
*/

#include <stdio.h>
#define MAXSIZE 100

void strncpy(char *s, char *t, int n);
void strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);

int main()
{
	char src[MAXSIZE], dest[MAXSIZE];

	strcpy(src, "abcamno");
	strcpy(dest, "abcdefg");

	//strncpy(dest, src, 5);
	int out = strncmp(dest, src, 5);
	printf("%d\n", out);

	return 0;

}

/* copy at most n charaters of t to s */
void strncpy(char *s, char *t, int n) {
	int i = 0;
	while ((i < n) && (*s++ = *t++))
		i++;
}

/* concat at most n charaters of t to the end of s */
void strncat(char *s, char *t, int n) {
	int i = 0;
	while (*s)
		s++;
	while ( (i < n) && (*s++ = *t++))
		i++;
	*s = '\0';
}

int strncmp(char *s, char *t, int n) {
	int i = 0;
	for (; (i < n) && (*s == *t); s++, t++, i++)
		if (*s == '\0')
			return 0;
	if (i == n)
		return 0;
	else
		return *s - *t;

}