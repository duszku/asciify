CC=gcc

VERSION="0.0"

# Debug flags
C_FLAGS=-Wall -Wextra -Werror -ansi -pedantic -g -Og \
	-fsanitize=address,leak,undefined -D${VERSION}
L_FLAGS=-lasan -lubsan -lm

# Release flags
#C_FLAGS=-Wall -O2
#L_FLAGS=-lm

SRC=asciify.c
OBJ=${SRC:.c=.o}
BINDIR=bin

.PHONY: asciify clean

asciify: ${OBJ} ${BINDIR}
	${CC} ${L_FLAGS} -o ${BINDIR}/$@ ${OBJ}

.c.o:
	${CC} ${C_FLAGS} -c -o $@ $<

${BINDIR}:
	mkdir ${BINDIR}

clean:
	rm -f *.o
