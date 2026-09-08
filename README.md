# C-Heap (cheap)
Heap-allocated datastructures written in C.

This library currently provides the following data-structures:
- LIFO (Last In First Out) buffer, aka "Stack"

## Usage
```bash
# generate build-artifacts and compile_commands.json file for LSPs
make

# run unit-tests
make test

# check for memory-leaks
make memcheck

# clear build artifacts
make clean
```

# References

- [gdb cheat-sheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)
- [GNU Make manual](https://www.gnu.org/software/make/manual/make.html)
- [C Macros](https://gcc.gnu.org/onlinedocs/cpp/Macros.html)
- [Unity: C unit-testing](https://www.throwtheswitch.org/unity)
- [generate `compile_commands.json` using the `bear` cli tool](https://github.com/rizsotto/Bear)
- [Makefile Tutorial](https://makefiletutorial.com/)
- [C/C++ Vulns](https://learn.snyk.io/catalog/?format=lesson&categories=cpp)
- [Tutorial: C unit-tests using Make and critereon](https://youtu.be/JarMkGWTF8Y?si=8bzlfJqC22s2tgl5)
- [Tutorial: expect library for testing interactive CLI programs](https://www.youtube.com/watch?v=6UbL3qeF2lo)
- [Address Sanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer)
