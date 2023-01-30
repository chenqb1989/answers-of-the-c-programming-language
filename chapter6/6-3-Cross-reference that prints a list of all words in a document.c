/*
* Write a cross-reference that prints a list of all words in a document,
* and, for each word, a list of the line numbers on which it occures. Remove
* noise words like "the", "and", and so on.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define MAXLINE 100

struct tnode
{
	char *word;
	int count;
	int nline[MAXLINE];  /* store line number on which it occures */
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *my_strdup(char *);

int line_no = 1;

char * noise_words[] = {"and", "on", "is", "the", "was"};  /* noise words that will not print */
int is_noise_word(char *s1);

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	int i = 0;
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && !is_noise_word(word))
			root = addtree(root, word);
		else if (word[0] == '\n')
			line_no++;

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
		p->nline[p->count] = line_no;
		p->count += 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->nline[p->count] = line_no;
		p->count++;
	}
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void treeprint(struct tnode *p)
{
	int i = 0;
	if (p != NULL)
	{
		treeprint(p->left);

		printf("%4d %s", p->count, p->word);
		for (int i = 0; i < p->count; i++)
			printf(" %2d", p->nline[i]);
		printf("\n");

		treeprint(p->right);
	}
}

/* is_noise_word: check if word is in noise word */
int is_noise_word(char *s1)
{
	int len = sizeof(noise_words) / sizeof(noise_words[0]);
	
	int i;
	for (i = 0; i < len; i++)
		if (!strcmp(noise_words[i], s1))
			return 1;
	
	return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	int flag = 0;

	while (isblank(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()))
		{
			ungetch(*w);
			break;
		}

	*w = '\0';
	return word[0];
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