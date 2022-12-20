#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define VERSION "0.0"

/* report unrecoverable error and exit */
#define ERROR(X) do {                                       \
        fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);    \
        perror((X));                                        \
        exit(EXIT_FAILURE);                                 \
} while (0)

const char *const def_lvls = " .,;[$&@#";

struct opts {
        long         widt;      /* width of the output in columns */
        long         heig;      /* height of the output in lines */
        char        *lvls;      /* light levels string (nul = use default) */
        unsigned     b_lg : 1;  /* is background light? */
};

struct image {
        unsigned char *data;
        int            w;
        int            h;
};

int          read_img(FILE *, struct image *);
int          largest_i(unsigned char *, int, unsigned char);
void         print_ascii(struct image *);

/* print usage information and exit */
void
usage(void)
{
        fprintf(stderr, "USAGE: asciify [options] file\n");
        fprintf(stderr, "Try \"asciify -h\" for help or consult the manpage\n");
        exit(EXIT_FAILURE);
}

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

/* 1-1 map pixels to characters from lightlevel string and print to stdout */
void
print_ascii(struct image *img)
{
        int            i, len;
        unsigned char *sections;

        len = strlen(def_lvls);

        if ((sections = calloc(len, sizeof(unsigned char))) == NULL)
                ERROR("calloc");

        for (i = 0; i < len; ++i)
                sections[i] = i * (UCHAR_MAX / len);

        for (i = 0; i < img->h * img->w; ++i) {
                if (i % img->w == 0 && i != 0)
                        putchar('\n');

                putchar(def_lvls[largest_i(sections, len, img->data[i])]);
        }

        putchar('\n');
        free(sections);
}
