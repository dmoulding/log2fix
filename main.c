#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "log2fix.h"

#define PRECISION 16
#define XEEOF -1

static int read_number_ (double *x);

int main ()
{
    double scale = 1U << PRECISION;
    double x;

    while (read_number_(&x) != -1) {
        if (x < 0) {
            fprintf(stderr, "%f is negative\n", x);
            continue;
        }
        if (x >= 1 << (32 - PRECISION)) {
            fprintf(stderr, "%f is too big\n", x);
            continue;
        }
        printf("   log(%f) = %f\n", x, log(x));
        printf("logfix(%f) = %f\n",
               x, logfix(x * scale, PRECISION) / scale);
        printf("   log2(%f) = %f\n", x, log2(x));
        printf("log2fix(%f) = %f\n",
               x, log2fix(x * scale, PRECISION) / scale);
        printf("   log10(%f) = %f\n", x, log10(x));
        printf("log10fix(%f) = %f\n",
               x, log10fix(x * scale, PRECISION) / scale);
    }

    if (errno == XEEOF) {
        return EXIT_SUCCESS;
    } else {
        perror("read_number_");
        return EXIT_FAILURE;
    }
}

int read_number_ (double *x)
{
    static char  s [BUFSIZ] = { 0 };
    static char *c = (char *)s + BUFSIZ - 1;

    while (isspace((int)*c)) {
        c++;
    }

    if (*c == '\0') {
        c = fgets(s, sizeof(s), stdin);
        if (!c) {
            if (feof(stdin)) {
                errno = XEEOF;
            }
            return -1;
        }
    }

    double  d;
    char   *end;

    errno = 0;
    d = strtod(c, &end);
    if (errno) {
        return -1;
    }
    if (end == c) {
        errno = EINVAL;
        return -1;
    }
    *x = d;
    c = end;

    return 0;
}
