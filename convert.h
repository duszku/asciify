/*
 * asciify - simple image to ascii-art converter
 * Copyright (C) 2022 https://github.com/duszku 
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <https://www.gnu.org/licenses/>.
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

int      read_img(FILE *, struct image *);         /* read image from file */
void     print_ascii(struct image *, int, char *); /* print to fd 1 */

/* scale images DOWN by a factor */
void     scd_fac_y(struct image *, double);
void     scd_fac_x(struct image *, double);
void     scd_fac(struct image *, double);

#endif /* CONVERT_H */
