/* 
* Write a program to compare two files, printing the first line where they differ.
*/

#include <stdio.h>
#include <string.h>

#define MAXLEN 100

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("error: should provide two files");
        return 1;
    }
    FILE *fp1, *fp2;
    char line1[MAXLEN], line2[MAXLEN];

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("error: some file can't be opened");
        return 1;
    }
    
    while (fgets(line1, MAXLEN, fp1) != NULL && fgets(line2, MAXLEN, fp2) != NULL)
        if (strcmp(line1, line2) != 0)
            break;
    printf("line1: %s\nline2: %s\n", line1, line2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}