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

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "convert.h"

#define MAX(X,Y)    ((X) > (Y) ? (X) : (Y))
#define MIN(X,Y)    ((X) < (Y) ? (X) : (Y))

const char *const def_lvls = DEF_LVLS;

static int   largest_i(unsigned char *, int, unsigned char);
static int   c2i(int, int, struct image *);

/* Read image file fp and store result in dest. Return number of pixels */
int
read_img(FILE *fp, struct image *dest)
{
        memset(dest, 0, sizeof(struct image));

        if (fp == NULL)
                return 0;

        dest->data = stbi_load_from_file(fp, &(dest->w), &(dest->h), NULL, 1);
        if (dest == NULL) {
                fprintf(stderr, "[%s:%d] read_img: input file incorrect\n",
                    __FILE__, __LINE__);
                exit(EXIT_FAILURE);
        }

        return dest->h * dest->w;
}

/* Find largest index i in sorted array src such that val > src[i] */
int
largest_i(unsigned char *src, int size, unsigned char val)
{
        int i;

        for (i = 0; i < size; ++i) {
                if (val < src[i])
                        break;
        }

        return i - 1;
}

/* Cartesian coordinates to an array index of data of img */
int
c2i(int x, int y, struct image *img)
{
        return x + (y * img->w);
}

/* 1-1 map pixels to characters from lightlevel string and print to fd 1 */
void
print_ascii(struct image *img, int inv, char *lvls)
{
        unsigned char *sections;
        int      i, ind, len;

        len = strlen(lvls == NULL ? def_lvls : lvls);

        if ((sections = calloc(len, sizeof(unsigned char))) == NULL)
                ERROR("calloc");

        for (i = 0; i < len; ++i)
                sections[i] = i * (UCHAR_MAX / len);

        for (i = 0; i < img->h * img->w; ++i) {
                if (i % img->w == 0 && i != 0)
                        putchar('\n');

                ind = largest_i(sections, len, img->data[i]);
                if (inv)
                        ind = len - ind - 1;

                putchar(lvls == NULL ? def_lvls[ind] : lvls[ind]);
        }

        putchar('\n');
        free(sections);
}

void
scd_fac_y(struct image *img, double fac)
{
        unsigned     char *new;
        int          fr_sz, fr_d, fr_u, new_h, i, j, k;
        int          b_d, b_u;

        fr_sz = ceil(fac);
        fr_d  = ceil((double)(fr_sz - 1) / 2);
        fr_u  = MAX(0, fr_sz - fr_d - 1);
        new_h = img->h / fac;

        if ((new = calloc(new_h * img->w, sizeof(char))) == NULL)
                ERROR("calloc");

        for (j = 0; j < img->w; ++j) {
                for (i = 0; i < new_h; ++i) {
                        /* calculating summation bounds */
                        b_d = MAX(0, i * fr_sz - fr_u);
                        b_u = MIN(img->h, i * fr_sz + fr_d);

                        for (k = b_d; k < b_u; ++k)
                                new[j + i * img->w] += img->data[c2i(j,k, img)];

                        new[j + i * img->w] = (double)new[j + i * img->w]
                            / fr_sz;
                }
        }

        free(img->data);
        img->data = new;
        img->h    = new_h;
}

void
scd_fac_x(struct image *img, double fac)
{
        unsigned     char *new;
        int          fr_sz, fr_l, fr_r, new_w, i, j, k;
        int          b_l, b_r;

        fr_sz = ceil(fac);
        fr_l  = ceil((double)(fr_sz - 1) / 2);
        fr_r  = MAX(0, fr_sz - fr_l - 1);
        new_w = img->w / fac;

        if ((new = calloc(new_w * img->h, sizeof(char))) == NULL)
                ERROR("calloc");

        for (j = 0; j < img->h; ++j) {
                for (i = 0; i < new_w; ++i) {
                        b_l = MAX(0, i * fr_sz - fr_l);
                        b_r = MIN(img->w, i * fr_sz + fr_r);

                        for (k = b_l; k < b_r; ++k)
                                new[i + j * new_w] += img->data[c2i(k, j, img)];

                        new[i + j * new_w] = (double)new[i + j * new_w] / fr_sz;
                }
        }

        free(img->data);
        img->data = new;
        img->w    = new_w;
}
