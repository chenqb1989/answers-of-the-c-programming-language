/*
* Write a program to print a set of files, starting each new one on a new page, 
* with a title and a running page count for each file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100
#define PAGELEN 10  /* 10 lines of every page */

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    long pageno = 0;
    FILE *fp;

    while (--argc > 0)
    {
        fp = fopen(*++argv, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "can't open %s\n", *argv);
            exit(1);
        }
        lineno = 0;
        while (fgets(line, MAXLINE, fp) != NULL)
        {
            if (lineno % PAGELEN == 0)
            {
                pageno++;
                printf("\nPAGE: %ld FILENAME: %s\n", pageno, *argv);
            }
            printf("%s", line);
            lineno++;
        }
        fclose(fp);
    }

    return 0;
}
