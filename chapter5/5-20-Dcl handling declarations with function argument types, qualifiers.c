/*
* Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100
#define MAXPARAMS 100  /* maximum number of param */
#define MAXLEN 100    /* maximum length of param */
#define ALLOCSIZE 10000 /* size of available space */

enum
{
	NAME,
	PARENS,
	BRACKETS
};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;			 /* type of last token */
char token[MAXTOKEN];	 /* last token string */
char name[MAXTOKEN];	 /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];			 /* output string */
char *params[MAXPARAMS];   /* params of last function */
char *alloc(int);

/* convert declaration to words */
int main()
{
	while (gettoken() != EOF) /* first token on line */
	{
		strcpy(datatype, token); /* is the datatype */
		out[0] = '\0';
		dcl(); /* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*';) /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;

	if (tokentype == '(')
	{
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	int nparam = 0;
	char param[MAXLEN];
	char *pa = param;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(')
	{
		if ((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else if(c == '*')
		{
			ungetch(c);
			return tokentype = '(';
		}
		else if(isalpha(c))
		{
			*pa = c;
			while(nparam < MAXPARAMS)
			{
				while((c = getch()) == ' ' || c == '\t')
					;
				while(isalpha(c) && c != ',' && c!= ')')
				{
					*++pa = c;
					c = getch();
				}
					
				*++pa = '\0';
				params[nparam++] = param;
				if (c == ')')
					break;
				// else
				// 	*param = '\0';
			}
		}
		else
		{
			printf("syntax error;");
		}
	}
	else if (c == '[')
	{
		for (*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
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

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;      /* next free position */

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}