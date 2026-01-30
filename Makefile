# debug symbols, all compiler warnings
CFLAGS=-g -Wall
CC=gcc

SRCS=src
OBJS=obj
BINS=bin
LIBS=lib
TESTS=tests

sources=$(wildcard ${SRCS}/*.c)
objects=$(sources:.c=.o)

# ensure directories are present before creating build artifacts to put in them
all: ${OBJS} ${BINS} ${LIBS} ${objects} ${BINS}/lifo

${BINS}/lifo: ${OBJS} ${BINS} ${LIBS} ${objects}
	${CC} ${objects} -o $@

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

clean:
	rm -f ${objects}

# designate targets that aren't files
.PHONY: clean
