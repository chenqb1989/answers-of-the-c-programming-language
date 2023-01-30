/*
* Write a program that will print arbitrary input in a sensible way. 
* As a minimum, it should print non-graphic characters in octal or 
* hexadecimal according to local custom, and break long text lines.
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    int c;
    int num_c = 0;
    int line_num = 100;
    
    while ((c = getchar()) != EOF)
    {
        if (isgraph(c) == 0)
            {
                if (num_c > 0 && num_c % line_num == 0)
                    printf("%c\n", c);
                else
                    printf("%c", c);
                num_c++;
            }
        else
            {
                if (num_c > 0 && num_c % line_num == 0) 
                    printf("0x%02o \n", c);
                else
                    printf("0x%02o ", c);
                num_c += 5;
            }
    }
    
    return 0;
}