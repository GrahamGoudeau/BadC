CC=clang
CFLAGS=-Wall -Wextra -g -c
EXEC=callStack

all: ${EXEC}

user.o: user.c user.h
		${CC} ${CFLAGS} user.c -o user.o

callStack.o: callStack.c
		${CC} ${CFLAGS} callStack.c -o $@

callStack: user.o callStack.o
		${CC} user.o callStack.o -o $@

syntax: user.h
		${CC} -E user.h >afterPreprocessor.c

clean:
		rm *.o ${EXEC_NAME} ${EXEC}
