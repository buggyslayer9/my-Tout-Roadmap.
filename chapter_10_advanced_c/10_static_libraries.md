# 10.10 Static Libraries in C

By this point, you have written multiple `.c` files, headers, a Makefile, and some tests. The next useful step is turning reusable code into a **library**.

A static library lets you package compiled object files into a single archive file, usually ending in `.a` on Linux.

This is one of the most practical transitions from "I can write C files" to "I can structure reusable C projects."

## Why Static Libraries Matter

If you keep copying utility functions between projects, you create problems:

- duplicated code
- harder bug fixing
- inconsistent versions
- messy builds

A static library solves this by letting you compile shared functionality once and link it into many programs.

## A Small Example Project

```text
my_math/
├── include/
│   └── my_math.h
├── src/
│   └── my_math.c
├── examples/
│   └── demo.c
└── Makefile
```

## Header File

```c
// include/my_math.h
#ifndef MY_MATH_H
#define MY_MATH_H

int add(int a, int b);
int multiply(int a, int b);

#endif
```

## Implementation File

```c
// src/my_math.c
#include "my_math.h"

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}
```

## Example Program

```c
// examples/demo.c
#include <stdio.h>
#include "my_math.h"

int main(void) {
    printf("2 + 3 = %d\n", add(2, 3));
    printf("4 * 5 = %d\n", multiply(4, 5));
    return 0;
}
```

## Build It Manually

First compile the implementation file into an object file:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude -c src/my_math.c -o my_math.o
```

Then create a static library archive:

```bash
ar rcs libmymath.a my_math.o
```

Finally compile and link the demo program against the library:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude examples/demo.c -L. -lmymath -o demo
```

## What Those Flags Mean

- `-Iinclude` tells the compiler where to find header files
- `-c` compiles without linking
- `ar rcs` creates the static archive
- `-L.` tells the linker to look in the current directory for libraries
- `-lmymath` links `libmymath.a`

## Makefile Version

```make
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
AR = ar
ARFLAGS = rcs

LIB = libmymath.a
OBJ = my_math.o

all: $(LIB) demo

$(OBJ): src/my_math.c include/my_math.h
	$(CC) $(CFLAGS) -c src/my_math.c -o $(OBJ)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

demo: examples/demo.c $(LIB)
	$(CC) $(CFLAGS) examples/demo.c -L. -lmymath -o demo

clean:
	rm -f $(OBJ) $(LIB) demo
```

## When To Use a Static Library

A static library is a good fit when:

- you have reusable logic across several programs
- you want simple deployment
- you do not need runtime plugin behavior

It is often the easiest first library format for learners because the final executable contains the code it needs after linking.

## Static vs Dynamic Libraries

High-level difference:

- **Static library**: code is copied into the executable at build time
- **Dynamic library**: code is loaded at runtime from a shared library file

Static libraries are usually easier to learn first. Dynamic libraries are powerful, but they introduce more build and deployment complexity.

## Good Habits

When building a C library:

- keep public headers in an `include/` folder
- keep implementation files in `src/`
- avoid exposing internal helper functions in public headers
- write example programs that prove the library is easy to use
- add tests before calling the library finished

## Learning Check

Make sure you can answer these:

- Why do we compile to object files before building the library?
- What does `ar` do?
- Why is the header included in both the library and the example program?
- What problem does a library solve better than copy-pasting functions?

## Recommended Follow-Up

After this lesson, try building a tiny utility library with:

- string helpers
- array helpers
- file helpers

That is one of the best project steps after Advanced C.
