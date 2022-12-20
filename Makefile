CC=gcc

# Debug flags
C_FLAGS=-Wall -Wextra -Werror -ansi -pedantic -g -Og \
	-fsanitize=address,leak,undefined
L_FLAGS=-lubsan -lasan -lm

# Release flags
#C_FLAGS=-Wall -O2
#L_FLAGS=-lm

SRC=
OBJ=${SRC:.c=.o}
BINDIR=bin

.PHONY: asciify clean

asciify: ${OBJ}
	${CC} ${L_FLAGS} -o ${BINDIR}/$@ ${OBJ}

.c.o:
	${CC} ${C_FLAGS} -c -o $@ $<

clean:
	rm -f *.o
