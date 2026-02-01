# debug symbols, all compiler warnings
CFLAGS=-g -Wall -fsanitize=address
# https://github.com/google/sanitizers/wiki/AddressSanitizer

CC=gcc
SHELL=/bin/bash
.SHELLFLAGS := -ecuo pipefail

SRC=src
OBJ=obj
LIB=lib
TESTS=tests
BIN=${TESTS}/bin

sources=$(shell find ${SRC} -name '*.c')
objects=$(sources:${SRC}/%.c=${OBJ}/%.o)

testsrcs=$(shell find ${TESTS} -name '*.c')
testbins=$(testsrcs:${TESTS}/%.c=${BIN}/%)

# ensure directories are present before creating build artifacts to put in them
all: ${OBJ} ${BIN} ${LIB} ${objects} ${testbins} ${sources}

# run unit tests
test: ${OBJ} ${BIN} ${LIB} ${objects} ${testbins} ${sources}
	for test in ${testbins}; do ./$$test ; done

# assemble object files corresponding to their source files
${objects}: ${sources}
	bear -- ${CC} ${CFLAGS} -c $^ -o $@

# link test binaries from object files
#${BIN}/%: ${TESTS}/%.c
${testbins}: ${testsrcs}
	bear -- ${CC} ${CFLAGS} $< ${objects} -o $@ -lcriterion

# targets for creating directories containing build artifacts
${OBJ}:
	mkdir -p $@
${BIN}:
	mkdir -p $@
${LIB}:
	mkdir -p $@

memcheck: ${objects} ${testbins}
	echo $(testbins) | xargs valgrind -s --tool=memcheck

clean:
	rm -f ${objects} ${testbins}

# designate targets that aren't files
.PHONY: test clean memcheck
