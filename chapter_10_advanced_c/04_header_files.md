# 10.4 Header Files: The Interface Contract

As projects grow beyond a single file, code must be split into modules. The convention in C is simple:
- **`.h` header files** contain *declarations* (the interface — what functions exist and what types look like).
- **`.c` source files** contain *definitions* (the implementation — the actual code).

## Example: A Student Module

**`student.h`** — The Public Interface
```c
#ifndef STUDENT_H     // Include guard: prevents double-inclusion
#define STUDENT_H

typedef struct {
    char   name[50];
    double gpa;
} Student;

// Function declarations (prototypes).
// Anyone who #includes this header can call these functions.
Student create_student(const char *name, double gpa);
void    print_student(const Student *s);

#endif // STUDENT_H
```

**`student.c`** — The Private Implementation
```c
#include "student.h"
#include <stdio.h>
#include <string.h>

Student create_student(const char *name, double gpa) {
    Student s;
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    s.gpa = gpa;
    return s;
}

void print_student(const Student *s) {
    printf("%-20s GPA: %.2f\n", s->name, s->gpa);
}
```

**`main.c`** — The Application
```c
#include "student.h"

int main(void) {
    Student s = create_student("Alice", 3.9);
    print_student(&s);
    return 0;
}
```

## Compiling Multi-File Projects

```bash
gcc -Wall -Wextra -std=c11 main.c student.c -o program
```

## Include Guards

The `#ifndef` / `#define` / `#endif` block is called an **include guard**. It prevents the same header from being processed twice if multiple `.c` files include it. Without it, you get "duplicate definition" errors.

A modern alternative is `#pragma once` — supported by all major compilers but not officially part of the C standard.
