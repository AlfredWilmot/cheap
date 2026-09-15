cmake_minimum_required(VERSION 3.21...4.0)

set(PROJECT_NAME cheap)
set(PROJECT_VERSION 0.0.0)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION "C Heap-allocated data-structures" LANGUAGES C)

# Make use of the latest C standard at time of writing
# (https://lemire.me/blog/2024/01/21/c23-a-slightly-better-c/)
# (https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html#prop_tgt:C_STANDARD)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# specify where to place build artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

# additional compiler confguration options
# (https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "gcc")
add_compile_options(
  -fexceptions
  -Werror=implicit
  -Werror=incompatible-pointer-types
  -Werror=int-conversion
  -fno-delete-null-pointer-checks
  -fno-strict-overflow
  -fno-strict-aliasing
  -ftrivial-auto-var-init=zero
  -fPIC  #(ensure correct module execution regardless of memory address)
  -shared
  -Wtrampolines
# -fzero-init-padding-bits=all
  -O2
  -Wall
  -Wformat
  -Wformat=2
  -Wconversion
  -Wimplicit-fallthrough
  -Werror=format-security
  -U_FORTIFY_SOURCE
  -D_FORTIFY_SOURCE=3
  -D_GLIBCXX_ASSERTIONS
  -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST
  -fstrict-flex-arrays=3
  -fstack-clash-protection
  -fstack-protector-strong
  -Wl,-z,nodlopen -Wl,-z,noexecstack
  -Wl,-z,relro -Wl,-z,now
  -Wl,--as-needed -Wl,--no-copy-dt-needed-entries
)

# Trying to make this usable as a library

# (https://stackoverflow.com/a/45843676/22415851)
# (https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html)

add_library(${PROJECT_NAME}
	src/lifo.c
	src/lifo.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/cheap.h)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)
