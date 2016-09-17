CC=clang
CFLAGS=-Wall -Wextra -g -c
EXEC_NAME=userTest

all: user.o main.o
		${CC} user.o main.o -o ${EXEC_NAME}

user.o: user.c user.h
		${CC} ${CFLAGS} user.c -o user.o

main.o: main.c
		${CC} ${CFLAGS} main.c -o main.o
