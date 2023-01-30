/*
* Rewrite appropriate programs from earlier chapters and exercises with pointers 
* instead of array indexing. Good possibilities include getline (Chapters 1 and 4), 
* atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
*/

#include <stdio.h>
#define MAXSIZE 100
#define NUMBER '0'


int get_line(char s[], int lim);
char* itoa_recursive(int n, char *s);
void itoa_width(int n, char *s, int w);
void reverse(char *s);
int getop(char *s);
int strrindex(char *s, char *t);

pattern = "ould";
int main()
{
	char line[MAXSIZE];
	int len;

	// test get_line
	/*while ((len = get_line(line, MAXSIZE)) > 0)
		printf("input line:%s\n", line);*/

	// test itoa_width, itoa_recursive
	/*int number = 1234567890;
	itoa_width(number, line, 10);
	printf("converted s: %s\n", line);*/

	// test getop
	/*int out = getop(line);
	printf("getop: %s\n", line);*/

	//test strrindex
	while ((len = get_line(line, MAXSIZE)) > 0) {
		int pos = strrindex(line, pattern);
		printf("position of rightmost occurrence of %s in %sis %d\n", pattern, line, pos);
	}

	return 0;

}

/* get line into s, return length */
int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		*s++ = c;
	}
	if (c == '\n') {
		*s++ = c;
		++i;
	}
	*s = '\0';
	return i;
}

/* convert s to integer */
char* itoa_recursive(int n, char *s) {

	if (n < 0) {
		*s++ = '-';
		n = -n;
	}
	if (n / 10)
		s = itoa(n / 10, s); /* return current pointer */
	*s++ = n % 10 + '0';
	*s = '\0';
	return s;
}

/* convert s to integer with width w */
void itoa_width(int n, char *s, int w) {
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		*s++ = n % 10 + '0';
		i++;
	} while ((n /= 10) > 0);
	if (sign < 0) {
		*s++ = '-';
		i++;
	}

	while (i++ < w)  /* pad blanks to length w */
		*s++ = ' ';
	*s = '\0';
	reverse(s - i + 1);  /* set s to the start position */
}

void reverse(char *s) {
	int i, j, len;
	for (i = 0; *s++ != '\0'; i++);  /* compute length of s */
	len = i;
	s = s - len - 1;  /* set s to the start position */
	for (j = 0; j < (len / 2); j++) {
		int temp = *(s + j);
		*(s + j) = *(s + len - 1 - j);
		*(s + len - 1 - j) = temp;
	}
}

/* getop: get next operator or numeric operand */
int getop(char *s) {
	int i, c;

	while ((*s = c = getchar()) == ' ' || c == '\t')
		;
	//*(s++) = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c; /* not a number */

	i = 0;
	if (c == '-') {  /* when c = '-', check it is negative sign or minus sign */
		if ((c = getchar()) == ' ' || c == '\t')
			return '-';
		else
			*++s = c;
	}
	if (isdigit(c))  /* collect integer part */
		while (isdigit(*++s = c = getchar()))
			;
	if (c == '.')  /* collect fraction part */
		while (isdigit(*++s = c = getchar()))
			;
	*s = '\0';
	//if (c != EOF)
	//	ungetch(c);
	return NUMBER;
}

/* return position of rightmost occurrence of t in s, -1 if none */
int strrindex(char *s, char *t) {
	int i, k;
	int rightest_p = -1;  /* rightmost position */

	for (i = 0; *s != '\0'; i++, s++) {
		for (k = 0; *t != '\0' && *s == *t; s++, t++, k++)
			;
		if (k > 0 && *t == '\0')
			rightest_p = i;  /* once find t in s, update rightest_p */
		else {
			s -= k;
			t -= k;
		}
	}
	return rightest_p;
}