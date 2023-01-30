/*
* Write a private version of scanf analogous to minprintf from the previous section.
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

int minscanf(char *fmt, ...);

int main(int argc, char *argv[])
{
    // float sum, v;
    // sum = 0;
    // while (minscanf("%f", &v))
    //     printf("\t%f\n", sum += v);

    // int day, month, year;
    // minscanf("%d/%d/%d", &month, &day, &year);
    // printf("%d/%d/%d\n", month, day, year);

    int day, year;
    char monthname[20];
    minscanf("%d %s %d", &day, monthname, &year);
    printf("%d %s %d\n", day, monthname, year);
    return 0;
}

/* minimum scanf with variable argument list */
int minscanf(char *fmt, ...)
{
    va_list ap; /* points to each unamed arg in turn */
    char *p, c;
    int *ival;
    float *dval;
    char *sp;
    int count = 0;

    va_start(ap, fmt); /* make appoint to 1st unamed arg */
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            c = getchar();
            if (c == *p)
                continue;
            else
                return count;
        }
        switch (*++p)
        {
        case 'd':
            ival = va_arg(ap, int *);
            count += scanf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, float *);
            count += scanf("%f", dval);
            break;
        case 's':
            sp = va_arg(ap, char *);
            count += scanf("%s", sp);
            break;
        default:
            return count;
        }
    }
    va_end(ap); /* clean up when done */
    return count;
}