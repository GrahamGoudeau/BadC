# Author: Graham Goudeau
# Date Created: Jan 2017

# It is not necessary to use the Makefile rules that end in .o
# You should use the names that follow those rules, so an example
# make invocation could be `make call_stack` or `make double_free`.
# Alternatively, you can just type `make` to build every executable.

# All executables should be able to run through valgrind with no
# errors reported.

CC=clang
CFLAGS=-Wall -Wextra -g -c -Wno-format-security -Wno-uninitialized

# the full list of executables that will be built
EXEC=call_stack mem_leak double_free pass_by_ref pointer_init

all: ${EXEC}

# not necessary to use rules that end in .o
user.o: user.c user.h
		${CC} ${CFLAGS} user.c -o user.o

call_stack.o: call_stack.c
		${CC} ${CFLAGS} call_stack.c -o $@

mem_leak.o: mem_leak.c
		${CC} ${CFLAGS} mem_leak.c -o $@

double_free.o: double_free.c
		${CC} ${CFLAGS} double_free.c -o $@

pointer_init.o: pointer_init.c
		${CC} ${CFLAGS} pointer_init.c -o $@

pass_by_ref.o: pass_by_ref.c
		${CC} ${CFLAGS} pass_by_ref.c -o $@

#########
# Use these as your Makefile options
#########
call_stack: user.o call_stack.o
		${CC} user.o call_stack.o -o $@

mem_leak: user.o mem_leak.o
		${CC} user.o mem_leak.o -o $@

double_free: user.o double_free.o
		${CC} user.o double_free.o -o $@

pass_by_ref: user.o pass_by_ref.o
		${CC} user.o pass_by_ref.o -o $@

pointer_init: user.o pointer_init.o
		${CC} user.o pointer_init.o -o $@

clean:
		rm *.o ${EXEC}
