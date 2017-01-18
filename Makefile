# It is not necessary to use the Makefile rules that end in .o
# You should use the names that follow those rules, so an example
# make invocation could be `make callStack` or `make doubleFree`.
# Alternatively, you can just type `make` to build every executable.

# All executables should be able to run through valgrind with no
# errors reported.

# You may also run `make syntax` to see what a .c file looks like
# after the pre-processor has been run on it. The relevant content
# is at the bottom of the file. It gets dumped in afterPreprocessor.c

CC=clang
CFLAGS=-Wall -Wextra -g -c -Wno-format-security -Wno-uninitialized

# the full list of executables that will be built
EXEC=callStack memLeak doubleFree passByRef pointerInit

CPPFILE=afterPreprocessor.c

all: ${EXEC}

# not necessary to use rules that end in .o
user.o: user.c user.h
		${CC} ${CFLAGS} user.c -o user.o

callStack.o: callStack.c
		${CC} ${CFLAGS} callStack.c -o $@

memLeak.o: memLeak.c
		${CC} ${CFLAGS} memLeak.c -o $@

doubleFree.o: doubleFree.c
		${CC} ${CFLAGS} doubleFree.c -o $@

pointerInit.o: pointerInit.c
		${CC} ${CFLAGS} pointerInit.c -o $@

passByRef.o: passByRef.c
		${CC} ${CFLAGS} passByRef.c -o $@

#########
# Use these as your Makefile options
#########
callStack: user.o callStack.o
		${CC} user.o callStack.o -o $@

memLeak: user.o memLeak.o
		${CC} user.o memLeak.o -o $@

doubleFree: user.o doubleFree.o
		${CC} user.o doubleFree.o -o $@

passByRef: user.o passByRef.o
		${CC} user.o passByRef.o -o $@

pointerInit: user.o pointerInit.o
		${CC} user.o pointerInit.o -o $@

syntax: user.h
		${CC} -E user.h >${CPPFILE}

clean:
		rm *.o ${EXEC} ${CPPFILE}
