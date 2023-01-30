/*
* Rewrite the program cat from Chapter 7 using read, write, open, and close 
* instead of their standard library equivalents. Perform experiments to determine 
* the relative speeds of the two versions.
*/

// version 3 is faster than version 2

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include "syscall.h"
#include <time.h>

clock_t start, end;

void error(char *, ...);
void file_copy2(int from, int to);

/* cat: concatenate files, version 3 */
// int main(int argc, char *argv[])
// {
//     start = clock();
//     char *prog = argv[0];  /* program name for errors */
//     int fd;

//     if (argc == 1)   /* no args; copy standard input */
//         file_copy2(0, 1);
//     else
//         while (--argc > 0)
//             if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
//                 error("%s: can't open %s", prog, *argv);
//             else
//             {
//                 file_copy2(fd, 1);
//                 close(fd);
//             }

//     end = clock();
//     double times = (double)(end - start) / CLOCKS_PER_SEC;
//     printf("consuming time: %.5f\n", times);
//     return 0;
// }

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[])
{
    start = clock();
    FILE *fp;
    void file_copy(FILE *, FILE *);
    char *prog = argv[0];  /* program name for errors */

    if (argc == 1)   /* no args; copy standard input */
        file_copy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            }
            else
            {
                file_copy(fp, stdout);
                fclose(fp);
            }
    // if (ferror(stdout))
    // {
    //     fprintf(stderr, "%s: error writing stdout\n", prog);
    //     exit(2);
    // }
    end = clock();
    double times = (double)(end - start) / CLOCKS_PER_SEC;
    printf("consuming time: %.5f\n", times);
    return 0;
}

/* file_copy: copy file ifp to file ofp */
void file_copy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

/* file_copy2: copy file using file descriptors */
void file_copy2(int f1, int f2)
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(f1, buf, BUFSIZ)) > 0)
        write(f2, buf, n);
        // if (write(f2, buf, n) != n)
        //     error("cp: write error on file\n");
}