# debug symbols, all compiler warnings
CFLAGS=-g -Wall
CC=gcc

SRCS=src
OBJS=obj
BINS=bin
LIBS=lib
TESTS=tests

sources=$(wildcard ${SRCS}/*.c)
objects=${OBJS}/lifo.o

all: ${OBJS} ${BINS} ${LIBS} ${objects}

# compile object files corresponding to their source files
${objects}: ${sources}
	${CC} -c $^ -o $@

# targets for creating directories containing build artifacts
${OBJS}:
	mkdir -p $@
${BINS}:
	mkdir -p $@
${LIBS}:
	mkdir -p $@

clean: ${OBJS} ${BINS} ${LIBS}
	$(foreach item,$^, rm -f $(wildcard ./${item}/*);)
