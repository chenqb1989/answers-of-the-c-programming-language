/*
* Implement a simple version of the #define processor (i.e., no arguments) 
* suitable for use with C programs, based on the routines of this section. 
* You may also find getch and ungetch helpful.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define BUFSIZE 100
#define MAXWORD 100

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
void print_hashtab();
int getword(char *, int);

int main(int argc, char *argv[])
{
    struct nlist *np;
    int newline = 1;
    int in_define = 0;
    char key[MAXWORD];
    char value[MAXWORD];
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (strcmp(word, "#define") == 0)
            in_define = 1;
        else if (in_define == 1)
        {
            strcpy(key, word);
            in_define = 2;
        }
        else if (in_define == 2)
        {
            strcpy(value, word);
            np = install(key, word);
            *key = '\0';
            *value = '\0';
            in_define = 0;
        }
    }
    print_hashtab();
}

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    struct nlist *np;
    struct nlist *last_np = (struct nlist *) malloc(sizeof(*np));
    unsigned hashval;
    int i;

    np = hashtab[hash(name)];

    for (i = 0; np != NULL; np = np->next, i++)
    {
        if (strcmp(name, np->name) == 0)
        {
            last_np->next = np->next;
            if (i == 0)
                hashtab[hash(name)] = np->next;

            free((void *) np->name);
            free((void *) np->defn);
            free((void *) np);
            
            break;
        }
        
        last_np = np;
    }
}

void print_hashtab()
{
    for (int i = 0; i < HASHSIZE; i++)
        if (hashtab[i] != NULL)
            for (struct nlist *np = hashtab[i]; np != NULL; np = np->next)
                printf("name:%s, defn:%s\n", np->name, np->defn);
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

	else if (c == '/') /* handle with comment */
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

	// else if (c == '#') /* handle with preprocesssor control lines */
	// 	while ((c = getch()) != '\n' && c != EOF)
	// 		;
	else if (isalnum(c) || c == '_' || c == '#')
		*w++ = c;
	else
		return c;
	for (; --lim > 0 && (*w = getch()) != ' ' && *w != '\n'; w++)
		if (flag == 0 && !isalnum(*w) && *w != '_' && *w != '#')
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