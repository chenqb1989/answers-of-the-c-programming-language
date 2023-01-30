/*
* Write a program that prints the distinct words in its input sorted 
* into decreasing order of frequency of occurrence. Precede each word by its count.
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
struct tnode *sort_tree_by_count(struct tnode *, struct tnode *);
struct tnode *addtree_by_count(struct tnode *, struct tnode *);

int main(int argc, char *argv[])
{
	struct tnode *root, *new_root;
	char word[MAXWORD];

	int i = 0;
	root = new_root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	new_root = sort_tree_by_count(new_root, root);
	treeprint(new_root);
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
	{
		p->count++;
	}
	else if (cond < 0) 	
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

/* add tree by count */
struct tnode *addtree_by_count(struct tnode *p, struct tnode *node)
{
	int cond;

	if (p == NULL)
	{
		p = talloc();
		p->word = my_strdup(node->word);
		p->count = node->count;
		p->left = p->right = NULL;
	}
	else if (p->count <= node->count)
		p->left = addtree_by_count(p->left, node);
	else
		p->right = addtree_by_count(p->right, node);
	return p;
}

/* sort tree by count */
struct tnode * sort_tree_by_count(struct tnode *new_tree, struct tnode *old_tree)
{
	if (old_tree)  /* loop the old tree */
	{
		 new_tree = sort_tree_by_count(new_tree, old_tree->left);
		 new_tree = addtree_by_count(new_tree, old_tree);  /* add the node to new_tree by count */
		 new_tree = sort_tree_by_count(new_tree, old_tree->right);
	}
	return new_tree;

}

void treeprint(struct tnode *p)
{
	int i = 0;
	if (p != NULL)
	{
		treeprint(p->left);

		printf("%4d %s\n", p->count, p->word);

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