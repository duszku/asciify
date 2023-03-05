/*
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF ACCOMPANYING ECLIPSE
 * PUBLIC LICENSE ("LICENSE"). ANY USE, REPRODUCTION OR DISTRIBUTION
 * OF THE PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE OF THIS AGREEMENT.
 */

#ifndef CONVERT_H
#define CONVERT_H

#define _POSIX_C_SOURCE 200809L
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Report unrecoverable error and exit */
#define ERROR(X) do {                                       \
        fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);    \
        perror((X));                                        \
        exit(EXIT_FAILURE);                                 \
} while (0)

/* Default codomain for lightlevel mapping */
#define DEF_LVLS " .,;^*+=$&@#"
/* #define DEF_LVLS " '^,;li<+-]}1(/frnvzYJL0Zwpbh*M&%@" */

struct image {
        unsigned     char *data;
        int          w;
        int          h;
};

int      read_img(FILE *, struct image *);          /* read image from file */
void     print_ascii(struct image *, int, char *);  /* print to fd 1 */

/* scale images DOWN by a factor */
void     scd_fac_y(struct image *, double);
void     scd_fac_x(struct image *, double);
void     scd_fac(struct image *, double);

void     norm_llvl(struct image *);                 /* normalize light levels */

#endif /* CONVERT_H */
