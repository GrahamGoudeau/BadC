CC=clang
CFLAGS=-Wall -Wextra -g -c -Wno-format-security
EXEC=callStack callStackFixed memLeak

all: ${EXEC}

user.o: user.c user.h
		${CC} ${CFLAGS} user.c -o user.o

callStack.o: callStack.c
		${CC} ${CFLAGS} callStack.c -o $@

callStackFixed.o: callStackFixed.c
		${CC} ${CFLAGS} callStackFixed.c -o $@

memLeak.o: memLeak.c
		${CC} ${CFLAGS} memLeak.c -o $@

callStackFixed: user.o callStackFixed.o
		${CC} user.o callStackFixed.o -o $@

callStack: user.o callStack.o
		${CC} user.o callStack.o -o $@

memLeak: user.o memLeak.o
		${CC} user.o memLeak.o -o $@

syntax: user.h
		${CC} -E user.h >afterPreprocessor.c

clean:
		rm *.o ${EXEC_NAME} ${EXEC}
