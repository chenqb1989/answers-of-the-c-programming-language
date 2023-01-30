/*
* Revise minprintf to handle more of the other facilities of printf.
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

void minprintf(char *fmt, ...);

int main(int argc, char *argv[])
{
    minprintf("%5.1d %s %5.1f\n", 3232, "let me see", 32.92);
    printf("%5.1d %s %5.1f\n", 3232, "let me see", 32.92);

    return 0;
}

/* minimum printf with variable argument list 
support customized field_width and precision */
void minprintf(char *fmt, ...)
{
    va_list ap;     /* points to each unamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    int period = 0;   /* period = 1 if has period which seperates the field width from the precision */
    int field_width = 0;
    int precision = 0;
    char s[MAXWORD];
    int i;

    char *sp;
    int sval_len, sval_print_len;

    va_start(ap, fmt);  /* make ap point to 1st unamed arg */
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        p++;
        /* get field_width and precision */
        while (*p != 'd' && *p != 'f' && *p != 's')
        {
            if (isdigit(*p))
            {
                i = 0;
                while (isdigit(*p))
                    s[i++] = *p++;

                s[i] = '\0';
                if (period == 0)
                    field_width = atoi(s);
                else
                    precision = atoi(s);
            }
            else if (*p == '.')
            {
                period = 1;
                p++;
            }
        }
        switch (*p)
        {
        case 'd':
            ival = va_arg(ap, int);
            printf("%*.*d", field_width, precision, ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%*.*f", field_width, precision, dval);
            break;
        case 's':
            sp =  va_arg(ap, char *);
            for (sval_len = 0, sval = sp; *sval; sval++)
                sval_len++;
            sval_print_len = sval_len;
            if (precision > 0 && precision < sval_len)
                sval_print_len = precision;
            while (field_width-- > sval_print_len)
                putchar(' ');
            for (sval = sp; *sval && sval_print_len > 0; sval++, sval_print_len--)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
        period = field_width = precision = 0;
    }
    va_end(ap);     /* clean up when done */
}