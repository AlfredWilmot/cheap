# debug symbols, all compiler warnings
CFLAGS=-g -Wall -fsanitize=address
CC=gcc

SRC=src
OBJ=obj
LIB=lib
TESTS=tests
BIN=${TESTS}/bin

sources=$(wildcard ${SRC}/*.c)
objects=$(sources:${SRC}/%.c=${OBJ}/%.o)

testsrcs=$(wildcard ${TESTS}/*.c)
testbins=$(testsrcs:${TESTS}/%.c=${BIN}/%)

# ensure directories are present before creating build artifacts to put in them
all: ${OBJ} ${BIN} ${LIB} ${objects} ${testbins}

# assemble object files corresponding to their source files
${objects}: ${sources}
	${CC} ${CFLAGS} -c $^ -o $@

# link test binaries from object files
#${BIN}/%: ${TESTS}/%.c
${testbins}: ${testsrcs}
	${CC} ${CFLAGS} $< ${objects} -o $@ -lcriterion

# targets for creating directories containing build artifacts
${OBJ}:
	mkdir -p $@
${BIN}:
	mkdir -p $@
${LIB}:
	mkdir -p $@

# run unit tests
test: ${LIB} ${BIN} ${testbins} ${objects}
	for test in ${testbins}; do ./$$test ; done

clean:
	rm -f ${objects} ${testbins}

# designate targets that aren't files
.PHONY: test clean
