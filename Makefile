CC=gcc

VERSION=\"1.0\"

# Debug flags
#C_FLAGS=-Wall -Wextra -ansi -pedantic -g -Og \
#	-fsanitize=address,leak,undefined
#L_FLAGS=-lasan -lubsan -lm

# Release flags
C_FLAGS=-Wall -O2
L_FLAGS=-lm

SRC=asciify.c convert.c
OBJ=${SRC:.c=.o}
BINDIR=bin

.PHONY: asciify clean

asciify: ${OBJ} ${BINDIR}
	${CC} -o ${BINDIR}/$@ ${OBJ} ${L_FLAGS}

.c.o:
	${CC} ${C_FLAGS} -DVERSION=${VERSION} -c -o $@ $<

${BINDIR}:
	mkdir ${BINDIR}

clean:
	rm -f *.o
