/*
* Our version of getword does not properly handle underscores, 
* string constants, comments, or preprocessor control lines. Write a better version.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NKEYS (sizeof keytab / sizeof keytab[0])
#define MAXWORD 100
#define BUFSIZE 100

struct key
{
	char *word;
	int count;
} keytab[] = {
	"_Alignas", 0,
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	/*...*/
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0};

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main()
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || word[0] == '_')
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
	{
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	}
	return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key *tab, int n)
{
	int cond;
	int low, mid, high;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	int flag = 0;

	while (isspace(c = getch()))
		;
	if (c == '"') /* if finds double quotes, continue until another double quotes */
		while ((c = getch()) != '"' && c != '\n' && c != EOF)
			;

	if (c == '/') /* handle with comment */
	{
		if ((c = getch()) == '/')
			while ((c = getch()) != '\n' && c != EOF)
				;
		else if (c == '*')
		{
			while (!((c = getch()) == '*' && (c = getch()) == '/'))
				;
		}
	}

	if (c == '#') /* handle with preprocesssor control lines */
		while ((c = getch()) != '\n' && c != EOF)
			;
	if (isalnum(c) || c == '_')
		*w++ = c;
	else
		return c;
	for (; --lim > 0 && (*w = getch()) != ' ' && *w != '\n'; w++)
		if (flag == 0 && !isalnum(*w) && *w != '_')
			flag = 1;
	if (flag == 1)
		return *w;
	else
	{
		*w = '\0';
		return word[0];
	}
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}