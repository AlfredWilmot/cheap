# debug symbols, all compiler warnings
DEVFLAGS := \
	-O2 -Wall -Wformat -Wformat=2 -Wconversion -Wimplicit-fallthrough -Werror=format-security \
	-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 \
	-D_GLIBCXX_ASSERTIONS \
	-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST \
	-fstrict-flex-arrays=3 \
	-fstack-clash-protection -fstack-protector-strong \
	-Wl,-z,nodlopen -Wl,-z,noexecstack \
	-Wl,-z,relro -Wl,-z,now \
	-Wl,--as-needed -Wl,--no-copy-dt-needed-entries \
	-fsanitize=address -g -Wall
# (https://github.com/google/sanitizers/wiki/AddressSanitizer)
# (https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html)

CC=gcc
SHELL=/bin/bash
.SHELLFLAGS := -ecuo pipefail

SRC=src
OBJ=obj
TESTS=tests
BIN=${TESTS}/bin

sources=$(shell find ${SRC} -name '*.c')
objects=$(sources:${SRC}/%.c=${OBJ}/%.o)

testsrcs=$(shell find ${TESTS} -name '*.c')
testbins=$(testsrcs:${TESTS}/%.c=${BIN}/%)

# ensure directories are present before creating build artifacts to put in them
all: ${OBJ} ${BIN} ${objects} ${testbins} ${sources}

# run unit tests
test: ${OBJ} ${BIN} ${objects} ${testbins} ${sources}
	for test in ${testbins}; do ./$$test ; done

# assemble object files corresponding to their source files
${objects}: ${sources}
	bear -- ${CC} ${DEVFLAGS} -c $^ -o $@

# link test binaries from object files
${testbins}: ${testsrcs}
	bear -- ${CC} ${DEVFLAGS} $< ${objects} -o $@ -lcriterion

# targets for creating directories containing build artifacts
${OBJ}:
	mkdir -p $@
${BIN}:
	mkdir -p $@

memcheck: ${objects} ${testbins}
	echo $(testbins) | xargs valgrind -s --tool=memcheck

clean:
	rm -f ${objects} ${testbins}

# designate targets that aren't files
.PHONY: test clean memcheck
