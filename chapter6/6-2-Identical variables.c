/*
* Write a program that reads a C program and prints in alphabetical order 
* each group of variable names that are identical in the first 6 characters, 
* but different somewhere thereafter. Don’t count words within strings and comments. 
* Make 6 a parameter that can be set from the command line.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct tnode
{
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *my_strdup(char *);

int nchar = 6;
char first_char[MAXWORD];

int main(int argc, char * argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	int i = 0;
	char s[MAXWORD];
	if (argc == 2)  /* get nchar from command line */
	{
		argv++;
		while (isdigit(s[i++] = *argv[0]))
			argv[0]++;
		s[i] = '\0';
		nchar = atoi(s);
	}
		
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	treeprint(root);
	printf("\n");

	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL)
	{
		p = talloc();
		p->word = my_strdup(w);
		p->count += 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: print in alphabetical order each group of variable names that are identical in the first n characters */
void treeprint(struct tnode *p)
{
	int i = 0;
	if (p != NULL)
	{
		treeprint(p->left);
		if (!first_char[0])  /* if first_char is empty, set it with p->word */
		{
			while (i < nchar && (first_char[i++] = *p->word++) != '\0')
				;
			p->word -= i;
			printf("\n%4d %s", p->count, p->word);
		}
		else
		{
			for (;i < nchar && first_char[i] == *p->word; i++, p->word++)
				;
			p->word -= i;
			if (i == nchar)  /* first n characters are identical with first_char */
				printf(", %4d %s", p->count, p->word);
			else             /* first n characters are not identical with first_char */
				printf("\n%4d %s", p->count, p->word);
				i = 0;
				while (i < nchar && (first_char[i++] = *p->word++) != '\0')  /* update first_char */
					;
				first_char[i] = '\0';
		}

		treeprint(p->right);
	}
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

#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *)malloc(sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *my_strdup(char *s)
{
	char *p;

	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
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