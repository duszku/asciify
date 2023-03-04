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

#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "convert.h"

#ifndef VERSION
#define VERSION "err"
#endif

struct opts {
        double       sc_fac;    /* scaling factor */
        char        *lvls;      /* light levels string (nul = use default) */
        unsigned     b_lg : 1;  /* is background light? */
};

void     usage(void);
void     help(void);
void     version(void);

void     def_opts(struct opts *);
int      parse_opts(struct opts *, char *const *, int);

/*
 * ASCIIFY is a small and simple image to ascii-art converter that takes a path
 * to an image file as an input and converts it to ascii art, possibly with a
 * fixed width and length.
 */
int
main(int argc, char *const *argv)
{
        struct  image img;
        struct  opts opts;
        FILE   *in;
        int     pos;

        if (argc < 2)
                usage();

        def_opts(&opts);
        pos = parse_opts(&opts, argv, argc);

        if ((in = fopen(argv[pos], "rb")) == NULL)
                ERROR("fopen");

        read_img(in, &img);

        if (fclose(in) == EOF)
                ERROR("fclose");

        scd_fac_y(&img, 2);
        scd_fac(&img, opts.sc_fac);
        print_ascii(&img, opts.b_lg, opts.lvls);

        free(img.data);
        if (opts.lvls != NULL)
                free(opts.lvls);

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

void
help(void)
{
        fprintf(stderr, "USAGE: asciify %s %s file\n",
            "[-hiv]", "[-s string] [-o outfile]");
        fprintf(stderr, "\t-h\tdisplay this help screen\n");
        fprintf(stderr, "\t-i\tinvert colours\n");
        fprintf(stderr, "\t-o pth\twrite output to pth instead of stdout\n");
        fprintf(stderr, "\t-s str\tuse str instead of default charset\n");
        fprintf(stderr, "\t-v\tprint version number and exit\n");
}

void
version(void)
{
        fprintf(stderr, "asciify (ASCIIFY) %s\n", VERSION);
        fprintf(stderr, "Copyright (C) 2022 https://github.com/duszku\n");
        fprintf(stderr, "This is free software; see the source for copying\
 conditions.  There is NO\n");
        fprintf(stderr, "warranty; not even for MERCHANTABILITY or FITNESS FOR\
 A PARTICULAR PURPOSE.\n");
}

/* Set all options to their default values */
void
def_opts(struct opts *opts)
{
        opts->sc_fac = 1;
        opts->lvls   = NULL;
        opts->b_lg   = 0;
}

/* Parse options, fill optstruct and return index of first positional arg */
int
parse_opts(struct opts *opts, char *const *argv, int argc)
{
        char c;

        while ((c = getopt(argc, argv, "hio:r:s:v")) != -1) {
                switch (c) {
                case 'h':
                        help();
                        exit(EXIT_SUCCESS);
                case 'i':
                        opts->b_lg = 1;
                        break;
                case 'o':
                        close(STDOUT_FILENO);
                        if (open(optarg, O_WRONLY | O_CREAT, 0777) == -1)
                                ERROR("open");
                        break;
                case 'r':
                        errno = 0;
                        if ((opts->sc_fac = strtod(optarg, NULL)) == 0 && errno)
                                ERROR("strtod");
                        break;
                case 's':
                        opts->lvls = calloc(strlen(optarg) + 1, 1);
                        if (opts->lvls == NULL)
                                ERROR("calloc");

                        strcpy(opts->lvls, optarg);
                        break;
                case 'v':
                        version();
                        exit(EXIT_SUCCESS);
                default:
                        usage();
                }
        }

        return optind;
}
