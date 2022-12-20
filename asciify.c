#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define VERSION "0.0.0"

/* report unrecoverable error and exit */
#define ERROR(X) do {                                       \
        fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);    \
        perror((X));                                        \
        exit(EXIT_FAILURE);                                 \
} while (0)

struct opts {
        long         widt;      /* width of the output in columns */
        long         heig;      /* height of the output in lines */
        char        *lvls;      /* light levels string (nul = use default) */
        unsigned     b_lg : 1;  /* is background light? */
};

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
        return EXIT_SUCCESS;
}
