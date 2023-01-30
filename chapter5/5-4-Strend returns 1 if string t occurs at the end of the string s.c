/*
* Write the function strend(s,t), which returns 1 if the string t occurs at the end of 
* the string s, and zero otherwise.
*/

#include <stdio.h>
#define MAXSIZE 100

int strend(char *s, char *t);

int main()
{
	char src[MAXSIZE], dest[MAXSIZE];

	strcpy(src, "destination");
	strcpy(dest, "This is destination");

	int out = strend(dest, src);
	if (out)
		printf("%s occurs at the end of %s\n", src, dest);
	else
		printf("%s does not occur at the end of %s\n", src, dest);

	return 0;

}

/* return 1 if t occurs at the end of s, 0 otherwise */
int strend(char *s, char *t) {
	int len_s, len_t;
	len_s = len_t = 0;

	while (*s) { /* compute length of s */
		s++;
		len_s++;
	}
	while (*t) { /* compute length of t */
		t++;
		len_t++;
	}

	if (len_s < len_t)  /* s is shorter than t */
		return 0;
	while ((len_t > 0) && (*s-- == *t--)) {
		len_s--;
		len_t--;
	}
	if (len_t == 0)
		return 1;
	else
		return 0;
}