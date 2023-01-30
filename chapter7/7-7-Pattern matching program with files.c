/*
* Modify the pattern finding program of Chapter 5 to take its input from a set of 
* named files or, if no files are named as arguments, from the standard input. 
* Should the file name be printed when a matching line is found?
*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    char pattern[MAXLINE];
    long lineno = 0;
    FILE *fp;

    strcpy(pattern, *++argv);
    printf("pattern: %s\n", pattern);
    while (--argc > 1)
    {
        fp = fopen(*++argv, "r");
        if (fp == NULL)
        {
            printf("error: file %s can't be opened\n", *argv);
            break;
        }
        while (fgets(line, MAXLINE, fp) != NULL)
            if (strstr(line, pattern) != NULL)
            {
                printf("filename: %s\t", *argv);
                printf("line: %s\n", line);
            }
        fclose(fp);
    }

    return 0;
}
