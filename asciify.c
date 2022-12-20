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

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

#include "convert.h"

const char *const def_lvls = " .,;[$&@#";

struct opts {
        long         widt;      /* width of the output in columns */
        long         heig;      /* height of the output in lines */
        char        *lvls;      /* light levels string (nul = use default) */
        unsigned     b_lg : 1;  /* is background light? */
};

void     usage(void);

/*
 * ASCIIFY is a small and simple image to ascii-art converter that takes a path
 * to an image file as an input and converts it to ascii art, possibly with a
 * fixed width and length.
 */
int
main(int argc, const char **argv)
{
        FILE   *in;
        struct  image img;

        if (argc != 2)
                usage();

        if ((in = fopen(argv[1], "rb")) == NULL)
                ERROR("fopen");

        read_img(in, &img);

        if (fclose(in) == EOF)
                ERROR("fclose");

        print_ascii(&img);

        stbi_image_free(img.data);

        return EXIT_SUCCESS;
}

/* print usage information and exit */
void
usage(void)
{
        fprintf(stderr, "USAGE: asciify [options] file\n");
        fprintf(stderr, "Try \"asciify -h\" for help or consult the manpage\n");
        exit(EXIT_FAILURE);
}
