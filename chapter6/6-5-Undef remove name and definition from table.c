/*
* Write a function undef that will remove a name and 
* definition from the table maintained by lookup and install.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

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

int main(int argc, char *argv[])
{
    struct nlist *np1 = install("IN", "1");
    struct nlist *np2 = install("OUT", "2");
    struct nlist *np3 = install("jfjdn", "3");  /* hash("IN") = hash("jfjdn") = 18 */

    print_hashtab();
    undef("jfjdn");
    printf("*****delete IN******\n");
    print_hashtab();
        
}