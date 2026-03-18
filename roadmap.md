# 🖥️ Complete C & GTK4 Programming Roadmap
### From Zero to GUI Developer — A Senior CS Instructor's Guide

---

> **How to use this roadmap:**  
> Work through each chapter in order. Every lesson builds on the previous one. After each lesson, complete the assignment before moving on. Code every example yourself — don't copy-paste. Use `gcc` or `clang` to compile your programs throughout the C phase, then install GTK4 when you reach Phase 2.

---

## 📌 Prerequisites & Setup

Before starting, install the following:

| Tool | Purpose | Install Command (Ubuntu/Debian) |
|------|---------|--------------------------------|
| GCC | C Compiler | `sudo apt install gcc` |
| GDB | Debugger | `sudo apt install gdb` |
| Valgrind | Memory checker | `sudo apt install valgrind` |
| Make | Build system | `sudo apt install make` |
| GTK4 (later) | GUI toolkit | `sudo apt install libgtk-4-dev` |
| VS Code / Vim | Editor | Your preference |

---

---

# 🔷 PHASE 1 — C PROGRAMMING FUNDAMENTALS

---

## Chapter 1 — Introduction to C & Your First Program

### 1.1 What is C?
C is a general-purpose, procedural programming language created by Dennis Ritchie at Bell Labs in 1972. It is the foundation of modern computing — Linux, Windows, and macOS kernels are all written in C. GTK itself is written in C. Understanding C gives you direct control over hardware and memory.

**Why learn C before GTK?**
- GTK's API is written in C
- GTK uses pointers, callbacks, and memory management — all C concepts
- C teaches you how computers actually work

### 1.2 The C Compilation Pipeline
Unlike Python or JavaScript, C is a compiled language. Your source code goes through these stages:

```
Source (.c) → Preprocessor → Compiler → Assembler → Linker → Executable
```

- **Preprocessor:** Handles `#include`, `#define`, `#ifdef`
- **Compiler:** Translates C to assembly
- **Assembler:** Converts assembly to machine code (.o object files)
- **Linker:** Combines object files + libraries into a final executable

### 1.3 Your First C Program

```c
#include <stdio.h>   // Include Standard Input/Output library

int main(void) {     // Entry point of every C program
    printf("Hello, World!\n");  // Print to terminal
    return 0;        // 0 = success; non-zero = error
}
```

**Compile and run:**
```bash
gcc hello.c -o hello
./hello
```

**Flags you should always use:**
```bash
gcc -Wall -Wextra -std=c11 hello.c -o hello
```
- `-Wall` — enable all warnings
- `-Wextra` — enable extra warnings
- `-std=c11` — use C11 standard

### 1.4 The `main()` Function
Every C program must have exactly one `main()` function. It can be written two ways:

```c
int main(void) { ... }           // No command-line arguments
int main(int argc, char *argv[]) { ... }  // With command-line arguments
```

`argc` = argument count, `argv` = argument vector (array of strings).

### 1.5 Basic Output with `printf`
`printf` is a formatted print function. The `%` sequences are format specifiers:

| Specifier | Meaning |
|-----------|---------|
| `%d` | Integer |
| `%f` | Float |
| `%c` | Character |
| `%s` | String |
| `%p` | Pointer address |
| `%ld` | Long integer |

---

### 📝 Assignment 1

**Task:** Write a program that prints the following output exactly:
```
Name:    [Your Name]
Age:     [Your Age]
Year:    2025
Language: C
```

**Hint:** Use `printf` with `\t` (tab character) or spaces for alignment. Look up the `%-15s` left-align format specifier.

---

## Chapter 2 — Variables, Data Types & Operators

### 2.1 Fundamental Data Types

```c
#include <stdio.h>
#include <stdbool.h>  // Boolean type (C99+)

int main(void) {
    // Integer types
    char   c  = 'A';       // 1 byte, -128 to 127
    short  s  = 32000;     // 2 bytes
    int    i  = 2147483;   // 4 bytes, most common integer
    long   l  = 123456789L; // 4 or 8 bytes (platform dependent)
    long long ll = 9999999999LL; // 8 bytes guaranteed

    // Floating point types
    float  f  = 3.14f;     // 4 bytes, ~6-7 significant digits
    double d  = 3.14159265358979; // 8 bytes, ~15 significant digits

    // Boolean (C99+)
    bool flag = true;

    printf("char: %c (%d bytes)\n", c, (int)sizeof(c));
    printf("int:  %d (%d bytes)\n", i, (int)sizeof(i));
    printf("double: %f (%d bytes)\n", d, (int)sizeof(d));

    return 0;
}
```

### 2.2 Unsigned Types
Adding `unsigned` removes the negative range and doubles the positive range:

```c
unsigned int x = 4294967295U;  // 0 to 4,294,967,295
unsigned char b = 255;          // 0 to 255 (used for byte data)
```

### 2.3 Type Modifiers and `sizeof`
Always use `sizeof` instead of hardcoding sizes — sizes vary by platform:

```c
printf("Size of int: %zu bytes\n", sizeof(int));
printf("Size of long: %zu bytes\n", sizeof(long));
```

### 2.4 Constants
```c
#define PI 3.14159          // Preprocessor constant (no type, no memory)
const double E = 2.71828;  // Typed constant (has type, lives in memory)
```

Prefer `const` over `#define` for type safety.

### 2.5 Operators

```c
// Arithmetic
int a = 10, b = 3;
int sum  = a + b;   // 13
int diff = a - b;   // 7
int prod = a * b;   // 30
int quot = a / b;   // 3  (integer division, truncates!)
int rem  = a % b;   // 1  (modulo)

// Comparison (returns 0 or 1)
a == b   // equal
a != b   // not equal
a > b    // greater than
a >= b   // greater than or equal

// Logical
(a > 5) && (b < 5)  // AND
(a > 5) || (b > 5)  // OR
!(a > 5)            // NOT

// Bitwise
a & b    // AND
a | b    // OR
a ^ b    // XOR
~a       // NOT (bitwise flip)
a << 2   // left shift (multiply by 4)
a >> 1   // right shift (divide by 2)

// Assignment shortcuts
a += 5;  // a = a + 5
a -= 3;  // a = a - 3
a *= 2;  // a = a * 2
a++;     // a = a + 1
a--;     // a = a - 1
```

### 2.6 Type Casting
```c
int x = 7, y = 2;
double result = (double)x / y;  // 3.5  (without cast: 3)
```

Without the cast, `/` performs integer division.

---

### 📝 Assignment 2

**Task:** Write a program that:
1. Declares variables of 5 different types
2. Prints their sizes using `sizeof`
3. Performs arithmetic on two integers and prints the results of all 5 operations (`+`, `-`, `*`, `/`, `%`)
4. Demonstrates the danger of integer division vs. floating-point division

**Hint:** Declare `int a = 7, b = 2;` and show `a/b` (integer) vs `(double)a/b` (float) results side by side.

---

## Chapter 3 — Control Flow

### 3.1 `if / else if / else`
```c
int score = 85;

if (score >= 90) {
    printf("Grade: A\n");
} else if (score >= 80) {
    printf("Grade: B\n");
} else if (score >= 70) {
    printf("Grade: C\n");
} else {
    printf("Grade: F\n");
}
```

### 3.2 Ternary Operator
```c
int max = (a > b) ? a : b;  // if a>b then max=a, else max=b
```

### 3.3 `switch` Statement
```c
char grade = 'B';

switch (grade) {
    case 'A':
        printf("Excellent!\n");
        break;
    case 'B':
        printf("Good job!\n");
        break;
    case 'C':
        printf("Average.\n");
        break;
    default:
        printf("Invalid grade.\n");
}
```

**Always include `break`** — without it, execution "falls through" to the next case.

### 3.4 Loops

**`while` loop:** Check condition first
```c
int i = 0;
while (i < 5) {
    printf("i = %d\n", i);
    i++;
}
```

**`do-while` loop:** Execute at least once
```c
int n;
do {
    printf("Enter a positive number: ");
    scanf("%d", &n);
} while (n <= 0);
```

**`for` loop:** Counter-based
```c
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}
```

### 3.5 `break` and `continue`
```c
for (int i = 0; i < 10; i++) {
    if (i == 5) break;      // exit loop entirely
    if (i % 2 == 0) continue;  // skip even numbers
    printf("%d ", i);       // prints: 1 3
}
```

### 3.6 Nested Loops
```c
for (int row = 1; row <= 3; row++) {
    for (int col = 1; col <= 3; col++) {
        printf("%d ", row * col);
    }
    printf("\n");
}
```

---

### 📝 Assignment 3

**Task:** Write a program that prints a multiplication table (1–10) using nested loops. The output should be neatly formatted in a grid.

**Hint:** Use `printf("%4d", value)` for right-aligned columns of width 4. Add column and row headers.

---

## Chapter 4 — Functions

### 4.1 Function Anatomy
```c
return_type function_name(parameter_type param1, parameter_type param2) {
    // body
    return value;
}
```

### 4.2 Function Declaration vs Definition
```c
// Declaration (prototype) — tells compiler the signature
int add(int a, int b);

int main(void) {
    int result = add(3, 4);  // Call before definition
    printf("Result: %d\n", result);
    return 0;
}

// Definition — the actual implementation
int add(int a, int b) {
    return a + b;
}
```

Always declare function prototypes above `main()` in large programs.

### 4.3 Pass by Value
C passes function arguments **by value** — the function gets a copy:

```c
void double_it(int x) {
    x = x * 2;  // Only modifies the local copy
}

int main(void) {
    int n = 5;
    double_it(n);
    printf("%d\n", n);  // Still 5 — unchanged!
    return 0;
}
```

To modify the original, you must use pointers (Chapter 6).

### 4.4 Recursion
A function that calls itself. Must have a **base case** to stop:

```c
int factorial(int n) {
    if (n == 0) return 1;        // Base case
    return n * factorial(n - 1); // Recursive case
}

// factorial(4) = 4 * factorial(3) = 4 * 3 * 2 * 1 = 24
```

```c
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### 4.5 Variable Scope
```c
int global_var = 100;  // Global: accessible everywhere

void my_function(void) {
    int local_var = 5;  // Local: only inside this function
    printf("%d %d\n", global_var, local_var);
}
// local_var does NOT exist here
```

### 4.6 `static` Variables
A `static` local variable keeps its value between function calls:

```c
void count_calls(void) {
    static int count = 0;  // Initialized only once
    count++;
    printf("Called %d times\n", count);
}
```

---

### 📝 Assignment 4

**Task:** Write a program with the following functions:
1. `int power(int base, int exp)` — compute `base^exp` using recursion
2. `int is_prime(int n)` — return 1 if n is prime, 0 otherwise
3. A `main()` that prints all prime numbers between 1 and 100 using `is_prime()`

**Hint:** For `is_prime()`, check divisibility from 2 up to `sqrt(n)` (include `<math.h>` and compile with `-lm`).

---

## Chapter 5 — Arrays & Strings

### 5.1 Arrays
```c
// Declaration and initialization
int numbers[5] = {10, 20, 30, 40, 50};
double grades[3] = {95.5, 87.3, 91.0};
int zeros[100] = {0};  // All elements = 0

// Access by index (0-based)
printf("%d\n", numbers[0]);  // 10
printf("%d\n", numbers[4]);  // 50

// DANGER: No bounds checking in C!
numbers[10] = 999;  // Undefined behavior — corrupts memory
```

### 5.2 Iterating Arrays
```c
int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
int len = sizeof(arr) / sizeof(arr[0]);  // Calculate length

for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
}
```

### 5.3 Multidimensional Arrays
```c
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Access: matrix[row][col]
printf("%d\n", matrix[1][2]);  // 6

// Iterate
for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
        printf("%3d ", matrix[r][c]);
    }
    printf("\n");
}
```

### 5.4 Arrays as Function Arguments
Arrays decay to pointers when passed to functions:

```c
// You must pass the length separately — C doesn't track it
void print_array(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    print_array(data, 5);
    return 0;
}
```

### 5.5 Strings in C
In C, strings are **null-terminated arrays of characters**:

```c
char name[] = "Alice";
// Stored as: ['A','l','i','c','e','\0']  — 6 chars, not 5!

char fixed[10] = "Bob";    // Fixed-size buffer
char *ptr = "Hello";       // String literal (read-only!)
```

**String functions (`<string.h>`):**

```c
#include <string.h>

strlen(str)              // Length (excluding \0)
strcpy(dest, src)        // Copy src into dest
strncpy(dest, src, n)    // Safer: copy at most n chars
strcat(dest, src)        // Concatenate (append src to dest)
strcmp(s1, s2)           // Compare: 0 if equal
strstr(haystack, needle) // Find substring
```

**NEVER compare strings with `==`:**
```c
if (strcmp(name, "Alice") == 0) { ... }  // Correct
if (name == "Alice") { ... }              // WRONG — compares addresses!
```

---

### 📝 Assignment 5

**Task:** Write a program that:
1. Reads 5 student names from user input into an array of strings (`char names[5][50]`)
2. Sorts the names alphabetically using bubble sort with `strcmp()`
3. Prints the sorted list

**Hint:** For bubble sort, swap `char` arrays using a temporary buffer and `strcpy()`. For `scanf`, use `scanf("%49s", names[i])` to read safely.

### 5.6 Secure Input: `scanf` vs `fgets`
See `chapter_05_arrays_strings/06_secure_input.md` for a critical lesson on avoiding buffer overflow vulnerabilities with safe input handling using `fgets()` instead of `scanf()`.

---

## Chapter 6 — Pointers & Memory

### 6.1 What is a Pointer?
A pointer is a variable that stores the **memory address** of another variable.

```c
int x = 42;
int *p = &x;    // p holds the address of x

printf("Value of x:     %d\n",  x);   // 42
printf("Address of x:   %p\n",  &x);  // e.g., 0x7fff5abc1234
printf("Value of p:     %p\n",  p);   // same as &x
printf("Dereferenced p: %d\n", *p);   // 42 (value at address)
```

### 6.2 Pointer Operators
- `&` — Address-of operator: gets the address of a variable
- `*` — Dereference operator: gets the value at an address

```c
*p = 100;  // Changes x through the pointer!
printf("%d\n", x);  // Now prints 100
```

### 6.3 Pass by Reference (Using Pointers)
```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 5, y = 10;
    swap(&x, &y);          // Pass addresses
    printf("%d %d\n", x, y);  // 10 5
    return 0;
}
```

### 6.4 Pointer Arithmetic
Pointers know the size of the type they point to:

```c
int arr[] = {10, 20, 30, 40, 50};
int *p = arr;  // Points to arr[0]

printf("%d\n", *p);      // 10
printf("%d\n", *(p+1));  // 20  (advances by sizeof(int) = 4 bytes)
printf("%d\n", *(p+4));  // 50

p++;  // Now points to arr[1]
```

### 6.5 Pointers and Arrays
An array name is a **constant pointer** to its first element:

```c
int arr[] = {1, 2, 3};
int *p = arr;  // Equivalent to int *p = &arr[0]

// These are equivalent:
arr[2] == *(arr + 2) == *(p + 2) == p[2]
```

### 6.6 Null Pointer
Always initialize pointers. Use `NULL` when not pointing to anything:

```c
int *p = NULL;

if (p != NULL) {
    *p = 5;  // Safe
}
// Never dereference NULL — it causes a segfault!
```

### 6.7 Pointer to Pointer (Double Pointer)
```c
int x = 10;
int *p = &x;
int **pp = &p;   // Points to the pointer p

printf("%d\n", **pp);  // 10
```

---

### 📝 Assignment 6

**Task:** Write these functions using pointers:
1. `void find_min_max(int *arr, int len, int *min, int *max)` — stores the min and max of the array into the pointer arguments
2. `void reverse_array(int *arr, int len)` — reverses an array in-place using pointer arithmetic

Test with: `{5, 2, 8, 1, 9, 3}`

**Hint:** For `find_min_max`, pass `&min_val` and `&max_val` from `main`. For `reverse`, swap elements from both ends moving toward the center using two index pointers.

---

## Chapter 7 — Dynamic Memory Allocation

### 7.1 The Memory Layout of a C Program
```
High Address
┌─────────────┐
│   Stack     │ ← Local variables, function calls (auto-managed)
├─────────────┤
│     ↓       │
│     ↑       │
├─────────────┤
│    Heap     │ ← Dynamic allocation (you manage this!)
├─────────────┤
│    BSS      │ ← Uninitialized global variables
├─────────────┤
│    Data     │ ← Initialized global/static variables
├─────────────┤
│    Text     │ ← Program code (read-only)
Low Address
```

### 7.2 `malloc`, `calloc`, `realloc`, `free`

```c
#include <stdlib.h>

// malloc: allocate n bytes, uninitialized (garbage values)
int *p = (int *)malloc(5 * sizeof(int));

// calloc: allocate n elements of size s, zero-initialized
int *q = (int *)calloc(5, sizeof(int));

// realloc: resize existing allocation
p = (int *)realloc(p, 10 * sizeof(int));  // Grow to 10 ints

// free: release memory (ALWAYS call this!)
free(p);
p = NULL;  // Prevent use-after-free
```

### 7.3 Always Check for NULL
```c
int *arr = (int *)malloc(100 * sizeof(int));
if (arr == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(EXIT_FAILURE);
}
```

### 7.4 Memory Leaks
A memory leak occurs when you allocate memory but never free it:

```c
void leaky_function(void) {
    int *p = malloc(100 * sizeof(int));
    // Function returns without calling free(p) — LEAK!
}
```

**Check for leaks with Valgrind:**
```bash
valgrind --leak-check=full ./your_program
```

### 7.5 Dynamic Arrays
```c
int n;
printf("How many elements? ");
scanf("%d", &n);

int *arr = (int *)malloc(n * sizeof(int));

for (int i = 0; i < n; i++) {
    arr[i] = i * 2;
}

// Use the array...

free(arr);  // Must free!
arr = NULL;
```

### 7.6 Common Memory Bugs
| Bug | Description |
|-----|-------------|
| Memory leak | Allocate but never free |
| Dangling pointer | Use pointer after free |
| Double free | Call free() twice on same pointer |
| Buffer overflow | Write past end of allocated memory |
| Use before init | Read uninitialized memory |

---

### 📝 Assignment 7

**Task:** Write a program that:
1. Asks the user how many integers to store
2. Dynamically allocates an array with `malloc`
3. Reads the integers from the user
4. Computes and prints the mean, and prints elements above the mean
5. Frees the memory and sets the pointer to NULL

**Hint:** Compute the mean first (sum / count using `double`), then loop again to find values above it. Run your solution through Valgrind to confirm no leaks.

---

## Chapter 8 — Structs, Unions & Enums

### 8.1 Structs
A struct groups related variables of different types:

```c
struct Student {
    char name[50];
    int  age;
    double gpa;
    int  id;
};

// Create a variable
struct Student s1;
strcpy(s1.name, "Alice");
s1.age = 20;
s1.gpa = 3.8;
s1.id  = 1001;

// Or initialize inline
struct Student s2 = {"Bob", 22, 3.5, 1002};

// Access members with dot operator
printf("Name: %s, GPA: %.2f\n", s2.name, s2.gpa);
```

### 8.2 Typedef
```c
typedef struct {
    float x;
    float y;
} Point;

// Now use Point instead of struct Point
Point p1 = {3.0f, 4.0f};
printf("Point: (%.1f, %.1f)\n", p1.x, p1.y);
```

### 8.3 Pointers to Structs
```c
typedef struct {
    int x, y;
} Point;

Point p = {10, 20};
Point *ptr = &p;

// Arrow operator -> dereferences and accesses member
printf("%d, %d\n", ptr->x, ptr->y);  // 10, 20
// Equivalent to: (*ptr).x
```

### 8.4 Structs with Dynamic Memory
```c
typedef struct {
    char *name;   // Pointer to dynamically allocated string
    int age;
} Person;

Person *create_person(const char *name, int age) {
    Person *p = (Person *)malloc(sizeof(Person));
    p->name = (char *)malloc(strlen(name) + 1);
    strcpy(p->name, name);
    p->age = age;
    return p;
}

void free_person(Person *p) {
    free(p->name);  // Free inner allocation first!
    free(p);        // Then free the struct itself
}
```

### 8.5 Arrays of Structs
```c
Student students[3] = {
    {"Alice", 20, 3.9, 1001},
    {"Bob",   21, 3.5, 1002},
    {"Carol", 22, 3.7, 1003}
};

for (int i = 0; i < 3; i++) {
    printf("%-10s %d  %.1f\n", students[i].name, students[i].age, students[i].gpa);
}
```

### 8.6 Enums
```c
typedef enum {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} Day;

Day today = WEDNESDAY;

if (today == WEDNESDAY) {
    printf("Midweek!\n");
}
```

### 8.7 Unions
All members share the same memory location:

```c
union Value {
    int   i;
    float f;
    char  str[20];
};

union Value v;
v.i = 42;
printf("%d\n", v.i);   // 42

v.f = 3.14f;           // Overwrites i!
printf("%.2f\n", v.f); // 3.14
```

---

### 📝 Assignment 8

**Task:** Create a simple library catalog system using structs:
1. Define a `Book` struct with: `title`, `author`, `year`, `available` (bool)
2. Write functions: `create_book()`, `print_book()`, `search_by_author()`
3. Create an array of 5 books
4. Implement a function that prints only available books

**Hint:** Use `typedef struct` for cleaner code. The `search_by_author` function should take `Book books[]`, `int count`, and `char *author` as arguments and use `strcmp`.

---

## Chapter 9 — File I/O

### 9.1 Opening and Closing Files
```c
#include <stdio.h>

FILE *fp = fopen("data.txt", "r");  // Open for reading
if (fp == NULL) {
    perror("fopen failed");  // Prints system error message
    return 1;
}
// ... use file ...
fclose(fp);  // Always close!
```

**File modes:**

| Mode | Meaning |
|------|---------|
| `"r"` | Read (file must exist) |
| `"w"` | Write (creates/overwrites) |
| `"a"` | Append |
| `"r+"` | Read and write |
| `"rb"` | Read binary |
| `"wb"` | Write binary |

### 9.2 Text File Operations
```c
// Writing
FILE *fp = fopen("output.txt", "w");
fprintf(fp, "Hello, %s! You are %d years old.\n", name, age);
fclose(fp);

// Reading line by line
FILE *fp2 = fopen("output.txt", "r");
char line[256];
while (fgets(line, sizeof(line), fp2) != NULL) {
    printf("%s", line);
}
fclose(fp2);
```

### 9.3 Binary Files
```c
// Write struct to binary file
Student s = {"Alice", 20, 3.9, 1001};
FILE *fp = fopen("students.bin", "wb");
fwrite(&s, sizeof(Student), 1, fp);
fclose(fp);

// Read struct from binary file
Student loaded;
FILE *fp2 = fopen("students.bin", "rb");
fread(&loaded, sizeof(Student), 1, fp2);
fclose(fp2);
printf("Loaded: %s\n", loaded.name);
```

### 9.4 File Position
```c
fseek(fp, 0, SEEK_SET);   // Go to beginning
fseek(fp, 0, SEEK_END);   // Go to end
long pos = ftell(fp);      // Get current position
rewind(fp);                // Go to beginning (same as fseek 0, SEEK_SET)
```

---

### 📝 Assignment 9

**Task:** Build a persistent student grade book:
1. Write a program that stores student records (name + grade) to a binary file
2. The program should support: Add student, View all students, Save, Load
3. On startup, load from file if it exists; on exit, save to file

**Hint:** Use `fwrite` and `fread` with a fixed-size `Student` struct. Check if the file exists by attempting `fopen` with `"rb"` — if it returns NULL, start with an empty list.

---

## Chapter 10 — Advanced C Concepts

### 10.1 Function Pointers
Functions have addresses too. You can store them in pointers:

```c
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

// Declare: return_type (*name)(param_types)
int (*operation)(int, int);

operation = add;
printf("%d\n", operation(3, 4));  // 7

operation = mul;
printf("%d\n", operation(3, 4));  // 12
```

**Function pointers in GTK:** Every button callback is a function pointer!

### 10.2 Arrays of Function Pointers
```c
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

int (*ops[])(int, int) = {add, sub, mul};

for (int i = 0; i < 3; i++) {
    printf("%d\n", ops[i](10, 5));  // 15, 5, 50
}
```

### 10.3 Preprocessor Macros
```c
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define SQUARE(x)   ((x) * (x))
#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

// Always parenthesize arguments!
// Without parens: SQUARE(1+2) = 1+2*1+2 = 5 (wrong!)
// With parens:    SQUARE(1+2) = (1+2)*(1+2) = 9 (correct)
```

### 10.4 Header Files
Separate code into `.h` and `.c` files:

**`student.h`:**
```c
#ifndef STUDENT_H   // Include guard — prevent double inclusion
#define STUDENT_H

typedef struct {
    char name[50];
    double gpa;
} Student;

void print_student(Student *s);
Student create_student(const char *name, double gpa);

#endif
```

**`student.c`:**
```c
#include "student.h"
#include <stdio.h>
#include <string.h>

void print_student(Student *s) {
    printf("Name: %s, GPA: %.2f\n", s->name, s->gpa);
}
```

**`main.c`:**
```c
#include "student.h"

int main(void) {
    Student s = create_student("Alice", 3.9);
    print_student(&s);
    return 0;
}
```

**Compile:**
```bash
gcc main.c student.c -o program
```

### 10.5 Linked Lists
A dynamic data structure using pointers:

```c
typedef struct Node {
    int data;
    struct Node *next;  // Points to next node
} Node;

Node *create_node(int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = value;
    n->next = NULL;
    return n;
}

void push_front(Node **head, int value) {
    Node *new_node = create_node(value);
    new_node->next = *head;
    *head = new_node;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}
```

---

### 10.6 Error Handling in C
See `chapter_10_advanced_c/06_error_handling.md` for a comprehensive lesson on `errno`, error handling patterns (return codes, `goto` cleanup, custom error enums), and signal handling (`SIGINT`, `SIGTERM`).

### 10.7 Debugging with GDB, Valgrind & Sanitizers
See `chapter_10_advanced_c/07_debugging.md` for a professional debugging workflow using GDB commands, Valgrind output interpretation, and AddressSanitizer (`-fsanitize=address`).

---

### 📝 Assignment 10

**Task:** Implement a singly linked list that supports:
1. `push_front(head, value)` — insert at front
2. `push_back(head, value)` — insert at back
3. `delete_value(head, value)` — delete first node with given value
4. `print_list(head)` — print all nodes
5. Verify with Valgrind that there are no memory leaks

**Hint:** For `push_back`, traverse to the end (where `node->next == NULL`). For `delete_value`, keep track of the previous node to update its `next` pointer.

---

---

# 🔶 PHASE 2 — GTK4 GUI PROGRAMMING

---

## Chapter 11 — Introduction to GTK4

### 11.1 What is GTK4?
GTK (GIMP Toolkit) is a free, open-source, cross-platform widget toolkit for creating graphical user interfaces. GTK4 is the current stable version (released 2020). It powers GNOME desktop applications, including Nautilus, GIMP, Inkscape, and many others.

**GTK4's architecture stack:**
```
Your Application
       ↓
     GTK4          ← Widget toolkit (buttons, windows, etc.)
       ↓
    GObject         ← Object system for C (OOP in C)
       ↓
     GLib           ← Data structures, utilities, threading
       ↓
     GIO            ← Files, networking, async I/O
       ↓
    Cairo / Pango   ← Drawing / Text rendering
       ↓
  Wayland / X11     ← Display server
```

### 11.2 Installing GTK4
```bash
# Ubuntu/Debian
sudo apt install libgtk-4-dev

# Fedora
sudo dnf install gtk4-devel

# Verify installation
pkg-config --modversion gtk4
```

### 11.3 Your First GTK4 Window

```c
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK4");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new(
        "com.example.hello",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
```

**Compile:**
```bash
gcc `pkg-config --cflags gtk4` hello.c `pkg-config --libs gtk4` -o hello
```

### 11.4 Anatomy of a GTK4 Program
Every GTK4 program follows this structure:

1. **Create a `GtkApplication`** — the application object with a unique reverse-DNS ID
2. **Connect the `activate` signal** — called when the app is ready
3. **In `activate`:** create windows and widgets
4. **Run the event loop** — `g_application_run()` blocks until the app quits

### 11.5 GTK's Type System (GObject)
GTK uses its own object system built on top of C. Key concepts:
- Every GTK type is a `GObject`
- Types form a hierarchy: `GtkButton` → `GtkWidget` → `GObject`
- **Casting macros** safely cast between types: `GTK_WINDOW(widget)`, `GTK_BUTTON(widget)`
- **Reference counting:** GTK manages memory using `g_object_ref()` / `g_object_unref()`

---

### 📝 Assignment 11

**Task:** Create a GTK4 application that:
1. Opens a 600×400 window titled "My First App"
2. Sets a custom application ID
3. Prints "Window opened!" to the terminal when activate is called
4. Compiles and runs without warnings

**Hint:** Use `g_print()` (GTK's cross-platform `printf`) instead of `printf` for GTK programs.

---

## Chapter 12 — Widgets & Layouts

### 12.1 What Are Widgets?
A widget is any visual element: buttons, labels, text fields, checkboxes, windows, etc. In GTK4, everything is a `GtkWidget`.

### 12.2 Common Widgets

```c
// Label — display text
GtkWidget *label = gtk_label_new("Hello, World!");
gtk_label_set_markup(GTK_LABEL(label), "<b>Bold</b> and <i>italic</i>");

// Button
GtkWidget *button = gtk_button_new_with_label("Click Me");

// Entry — single-line text input
GtkWidget *entry = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Type here...");

// CheckButton
GtkWidget *check = gtk_check_button_new_with_label("I agree");

// Image
GtkWidget *image = gtk_image_new_from_icon_name("dialog-information");
```

### 12.3 Layouts (Containers)

**`GtkBox` — horizontal or vertical stacking:**
```c
// Vertical box: children stacked top to bottom
GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);  // 10px spacing

// Horizontal box: children side by side
GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

// Add widgets to box
gtk_box_append(GTK_BOX(vbox), label);
gtk_box_append(GTK_BOX(vbox), button);
gtk_box_append(GTK_BOX(vbox), entry);

// Set as window content
gtk_window_set_child(GTK_WINDOW(window), vbox);
```

**`GtkGrid` — 2D grid layout:**
```c
GtkWidget *grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

// gtk_grid_attach(grid, widget, col, row, col_span, row_span)
gtk_grid_attach(GTK_GRID(grid), label1,  0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(grid), entry1,  1, 0, 1, 1);
gtk_grid_attach(GTK_GRID(grid), label2,  0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), entry2,  1, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), button,  0, 2, 2, 1);  // Spans 2 columns
```

**Widget properties:**
```c
// Margins
gtk_widget_set_margin_top(widget, 10);
gtk_widget_set_margin_bottom(widget, 10);
gtk_widget_set_margin_start(widget, 20);
gtk_widget_set_margin_end(widget, 20);

// Size
gtk_widget_set_size_request(widget, 200, 50);  // min width, height

// Expand to fill available space
gtk_widget_set_hexpand(widget, TRUE);
gtk_widget_set_vexpand(widget, TRUE);
```

---

### 📝 Assignment 12

**Task:** Build a simple contact form GUI with:
- A `GtkGrid` layout
- Fields for: Name, Email, Phone (each with a label on the left and entry on the right)
- A "Submit" button at the bottom spanning the full width
- 10px margin on all sides of the window

**Hint:** Use `gtk_widget_set_hexpand(entry, TRUE)` so entries stretch to fill the column. Add the grid to the window, then add a margin using `gtk_widget_set_margin_*`.

---

## Chapter 13 — Signals & Callbacks

### 13.1 The Event-Driven Model
GTK4 is **event-driven**: your code doesn't run in a loop checking for input. Instead, you register **callbacks** — functions that GTK calls when something happens (a click, a key press, a window close, etc.).

This uses the **signal/slot** pattern (originally from GLib):
- An **event** occurs (user clicks a button)
- GTK **emits a signal** on the widget (`"clicked"`)
- Your **callback function** is invoked

### 13.2 `g_signal_connect`
```c
gulong g_signal_connect(
    gpointer    object,      // The widget
    const char *signal,      // Signal name (e.g., "clicked")
    GCallback   callback,    // Your function
    gpointer    user_data    // Extra data to pass to callback
);
```

### 13.3 Button Click Callback
```c
static void on_button_clicked(GtkButton *button, gpointer user_data) {
    // button: the widget that emitted the signal
    // user_data: the extra data you passed in g_signal_connect
    g_print("Button was clicked!\n");
}

// In activate():
GtkWidget *button = gtk_button_new_with_label("Click Me");
g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
```

### 13.4 Passing Data to Callbacks
```c
static void on_click(GtkButton *btn, gpointer user_data) {
    GtkLabel *label = GTK_LABEL(user_data);  // Cast the pointer
    gtk_label_set_text(label, "You clicked!");
}

// In activate():
GtkWidget *label  = gtk_label_new("Waiting...");
GtkWidget *button = gtk_button_new_with_label("Click");
g_signal_connect(button, "clicked", G_CALLBACK(on_click), label);
```

### 13.5 Passing Multiple Data with a Struct
```c
typedef struct {
    GtkLabel  *result_label;
    GtkEntry  *name_entry;
    int        click_count;
} AppData;

static void on_submit(GtkButton *btn, gpointer user_data) {
    AppData *data = (AppData *)user_data;
    data->click_count++;
    const char *name = gtk_editable_get_text(GTK_EDITABLE(data->name_entry));
    char message[100];
    snprintf(message, sizeof(message), "Hello, %s! (click #%d)", name, data->click_count);
    gtk_label_set_text(data->result_label, message);
}
```

### 13.6 Common Signals

| Widget | Signal | When |
|--------|--------|------|
| `GtkButton` | `"clicked"` | User clicks |
| `GtkEntry` | `"activate"` | Enter key pressed |
| `GtkEntry` | `"changed"` | Text changes |
| `GtkCheckButton` | `"toggled"` | State changes |
| `GtkWindow` | `"destroy"` | Window closed |
| `GtkApplication` | `"activate"` | App starts |

### 13.7 Disconnecting Signals
```c
gulong handler_id = g_signal_connect(btn, "clicked", G_CALLBACK(on_click), NULL);
// Later, disconnect:
g_signal_handler_disconnect(btn, handler_id);
```

---

### 📝 Assignment 13

**Task:** Build a counter application:
- A label showing "Count: 0"
- An "Increment" button (+1)
- A "Decrement" button (-1)
- A "Reset" button (back to 0)
- The label updates on every click

**Hint:** Store the count in a struct along with the label pointer. Pass the struct as `user_data` to all three callbacks. Use `snprintf` to format the updated count string and `gtk_label_set_text` to update the display.

---

## Chapter 14 — GTK4 Dialogs & Message Boxes

### 14.1 Alert Dialog (GTK4)
In GTK4, `GtkAlertDialog` replaced the older `GtkMessageDialog`:

```c
GtkAlertDialog *dialog = gtk_alert_dialog_new("Are you sure?");
gtk_alert_dialog_set_detail(dialog, "This action cannot be undone.");
gtk_alert_dialog_set_buttons(dialog, (const char *[]){"Cancel", "OK", NULL});
gtk_alert_dialog_set_default_button(dialog, 1);
gtk_alert_dialog_set_cancel_button(dialog, 0);

// Show asynchronously
gtk_alert_dialog_choose(dialog, GTK_WINDOW(window), NULL, on_dialog_response, user_data);
g_object_unref(dialog);
```

### 14.2 File Chooser Dialog
```c
GtkFileDialog *file_dialog = gtk_file_dialog_new();
gtk_file_dialog_set_title(file_dialog, "Open File");

// Open asynchronously
gtk_file_dialog_open(file_dialog, GTK_WINDOW(window), NULL, on_file_chosen, user_data);
g_object_unref(file_dialog);

// Callback:
static void on_file_chosen(GObject *source, GAsyncResult *result, gpointer user_data) {
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
    GFile *file = gtk_file_dialog_open_finish(dialog, result, NULL);
    if (file != NULL) {
        char *path = g_file_get_path(file);
        g_print("Selected: %s\n", path);
        g_free(path);
        g_object_unref(file);
    }
}
```

### 14.3 Input Dialog with `GtkWindow`
GTK4 doesn't have a built-in input dialog. Build one using a `GtkWindow`:

```c
void show_input_dialog(GtkWindow *parent) {
    GtkWidget *dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Enter Name");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 150);

    GtkWidget *box   = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *entry = gtk_entry_new();
    GtkWidget *btn   = gtk_button_new_with_label("OK");
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    gtk_box_append(GTK_BOX(box), gtk_label_new("Enter your name:"));
    gtk_box_append(GTK_BOX(box), entry);
    gtk_box_append(GTK_BOX(box), btn);
    gtk_window_set_child(GTK_WINDOW(dialog), box);
    gtk_window_present(GTK_WINDOW(dialog));
}
```

---

### 📝 Assignment 14

**Task:** Build a "Delete Confirmation" workflow:
1. Show a list of 3 items (as labels) with a "Delete" button next to each
2. When "Delete" is clicked, show a `GtkAlertDialog` asking "Delete [item name]?"
3. If confirmed, remove the label from the window

**Hint:** Pass the item name and its widget pointer in a struct to the dialog callback. In the response callback, check which button was pressed (index 0 = Cancel, 1 = OK).

---

## Chapter 15 — Drawing with Cairo

### 15.1 GtkDrawingArea
`GtkDrawingArea` is a blank canvas where you draw using the Cairo 2D graphics library:

```c
GtkWidget *area = gtk_drawing_area_new();
gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 400);
gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 300);

// Set the draw function
gtk_drawing_area_set_draw_func(
    GTK_DRAWING_AREA(area),
    draw_callback,   // Called whenever the area needs to be redrawn
    NULL,
    NULL
);
```

### 15.2 The Draw Callback
```c
static void draw_callback(GtkDrawingArea *area, cairo_t *cr,
                           int width, int height, gpointer data) {
    // cr is the Cairo drawing context
    // Draw a red filled rectangle
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);  // R, G, B (0.0 to 1.0)
    cairo_rectangle(cr, 50, 50, 200, 100);
    cairo_fill(cr);

    // Draw a blue outline circle
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    cairo_set_line_width(cr, 3.0);
    cairo_arc(cr, 300, 150, 60, 0, 2 * G_PI);  // center, radius, angle_start, angle_end
    cairo_stroke(cr);
}
```

### 15.3 Cairo Primitives

```c
// Colors
cairo_set_source_rgb(cr, r, g, b);           // Solid color
cairo_set_source_rgba(cr, r, g, b, alpha);   // With transparency

// Paths
cairo_move_to(cr, x, y);
cairo_line_to(cr, x2, y2);
cairo_rectangle(cr, x, y, width, height);
cairo_arc(cr, cx, cy, radius, angle1, angle2);
cairo_close_path(cr);

// Rendering
cairo_fill(cr);          // Fill the current path
cairo_stroke(cr);        // Draw the outline
cairo_fill_preserve(cr); // Fill and keep path for stroke
cairo_paint(cr);         // Fill entire area with current color

// Text
cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
cairo_set_font_size(cr, 24.0);
cairo_move_to(cr, 50, 50);
cairo_show_text(cr, "Hello Cairo!");
```

### 15.4 Triggering Redraws
```c
// Request a redraw (next time GTK processes events)
gtk_widget_queue_draw(area);
```

---

### 📝 Assignment 15

**Task:** Create an application that draws:
1. A bar chart of 5 hardcoded values (e.g., `{30, 70, 50, 90, 40}`)
2. Each bar should have a different color
3. Draw x-axis labels below each bar (you can use numbers 1–5)
4. Add a title "Bar Chart" at the top using Cairo text

**Hint:** Loop through the values and draw rectangles. Scale bars so the tallest bar fits the canvas (height - padding). Use `cairo_select_font_face` and `cairo_show_text` for labels.

---

## Chapter 16 — GLib Data Structures & Utilities

### 16.1 Why GLib?
GLib is the foundation of GTK. It provides:
- Collections: `GList`, `GSList`, `GHashTable`, `GArray`, `GPtrArray`, `GQueue`
- String utilities: `GString`
- Memory utilities: `g_new`, `g_free`, `g_malloc`
- Main loop: `GMainLoop`, timeouts, idle callbacks
- Threading: `GThread`, `GMutex`

### 16.2 GList (Doubly Linked List)
```c
#include <glib.h>

GList *list = NULL;

// Append / prepend
list = g_list_append(list, "Alice");
list = g_list_append(list, "Bob");
list = g_list_prepend(list, "Zara");  // Adds to front

// Iterate
for (GList *l = list; l != NULL; l = l->next) {
    g_print("Item: %s\n", (char *)l->data);
}

// Length
int len = g_list_length(list);

// Find
GList *found = g_list_find(list, "Bob");

// Free
g_list_free(list);
```

### 16.3 GHashTable
```c
GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

// Insert
g_hash_table_insert(table, "name", "Alice");
g_hash_table_insert(table, "email", "alice@example.com");

// Lookup
char *val = g_hash_table_lookup(table, "name");
g_print("Name: %s\n", val);

// Check existence
gboolean exists = g_hash_table_contains(table, "email");

// Remove
g_hash_table_remove(table, "name");

// Free
g_hash_table_destroy(table);
```

### 16.4 GString (Dynamic String)
```c
GString *str = g_string_new("Hello");
g_string_append(str, ", World!");
g_string_append_printf(str, " Count: %d", 42);

g_print("%s\n", str->str);  // Access raw C string

g_string_free(str, TRUE);   // TRUE = also free the char buffer
```

### 16.5 Timeouts & Idle Callbacks
```c
// Run a function every 1000ms (1 second)
g_timeout_add(1000, my_timer_callback, user_data);

// Signature:
static gboolean my_timer_callback(gpointer user_data) {
    g_print("Tick!\n");
    return G_SOURCE_CONTINUE;  // Keep firing
    // return G_SOURCE_REMOVE;  // Stop the timer
}

// Run when GTK is idle (low priority, between events)
g_idle_add(my_idle_callback, user_data);
```

---

### 📝 Assignment 16

**Task:** Build a live stopwatch application:
1. Use `g_timeout_add(100, ...)` to update every 100ms
2. Display time as `MM:SS.T` (minutes, seconds, tenths)
3. Buttons: Start, Stop, Reset
4. Use a `GString` to format the time string

**Hint:** Track elapsed time as an integer (tenths of a second). In the callback, increment the counter, format with `g_string_printf`, update the label, and return `G_SOURCE_CONTINUE`. Store the timeout ID so you can cancel it with `g_source_remove(id)` on Stop.

---

## Chapter 17 — CSS Styling in GTK4

### 17.1 CSS in GTK4
GTK4 uses CSS to style widgets — similar to web CSS but with GTK-specific properties:

```c
// Load CSS from a string
GtkCssProvider *provider = gtk_css_provider_new();
gtk_css_provider_load_from_string(provider,
    "button {"
    "  background-color: #2196F3;"
    "  color: white;"
    "  border-radius: 6px;"
    "  padding: 8px 16px;"
    "  font-size: 14px;"
    "}"
    "button:hover {"
    "  background-color: #1976D2;"
    "}"
);

// Apply globally
gtk_style_context_add_provider_for_display(
    gdk_display_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
);
g_object_unref(provider);
```

### 17.2 CSS Classes
```c
// Add a CSS class to a widget
gtk_widget_add_css_class(button, "primary-button");

// In CSS:
// .primary-button { background: green; }
```

### 17.3 Widget Names (ID Selectors)
```c
gtk_widget_set_name(widget, "my-special-label");

// In CSS:
// #my-special-label { color: red; font-size: 20px; }
```

### 17.4 Load CSS from File
```c
GtkCssProvider *provider = gtk_css_provider_new();
gtk_css_provider_load_from_path(provider, "styles.css");
```

### 17.5 Common GTK4 CSS Properties
```css
/* Background */
background-color: #336699;
background: linear-gradient(to bottom, #336699, #003366);

/* Text */
color: white;
font-family: "Sans";
font-size: 16px;
font-weight: bold;

/* Box model */
padding: 10px 20px;
margin: 5px;
border: 2px solid #aaa;
border-radius: 8px;

/* Box shadow */
box-shadow: 2px 2px 6px rgba(0,0,0,0.3);
```

---

### 📝 Assignment 17

**Task:** Style the counter app from Assignment 13 with CSS:
1. Large, bold counter label (font-size 48px, centered)
2. Increment button: green background, white text
3. Decrement button: red background, white text
4. Reset button: gray, outlined style
5. Add hover effects to all buttons

**Hint:** Use `gtk_widget_add_css_class` to add class names, then write CSS targeting `.increment-btn`, `.decrement-btn`, etc. Put all CSS in a multiline string passed to `gtk_css_provider_load_from_string`.

---

## Chapter 18 — Building a Complete GTK4 Application

### 18.1 Application Structure
For a real application, organize your code:

```
my_app/
├── main.c           ← Entry point, GtkApplication setup
├── app_window.c     ← Main window creation
├── app_window.h
├── callbacks.c      ← Signal callback functions
├── callbacks.h
├── data.c           ← Data model, business logic
├── data.h
├── Makefile         ← Build automation
└── styles.css       ← Application CSS
```

### 18.2 Makefile for GTK4

```makefile
CC      = gcc
CFLAGS  = -Wall -Wextra `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`
SRC     = main.c app_window.c callbacks.c data.c
OBJ     = $(SRC:.c=.o)
TARGET  = my_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
```

### 18.7 Meson Build System
See `chapter_18_complete_gtk4_app/07_meson_build.md` for a comprehensive lesson on the Meson build system — the modern standard for GNOME/GTK projects, including GResource integration, installation, and comparison with Make/CMake.

### 18.3 GtkListBox — Dynamic List Widgets
```c
GtkWidget *listbox = gtk_list_box_new();
gtk_list_box_set_selection_mode(GTK_LIST_BOX(listbox), GTK_SELECTION_SINGLE);

// Add items
GtkWidget *row = gtk_label_new("Item One");
gtk_list_box_append(GTK_LIST_BOX(listbox), row);

// Handle selection
g_signal_connect(listbox, "row-selected", G_CALLBACK(on_row_selected), NULL);
```

### 18.4 GtkScrolledWindow
Wrap widgets that may overflow:

```c
GtkWidget *scroll = gtk_scrolled_window_new();
gtk_scrolled_window_set_policy(
    GTK_SCROLLED_WINDOW(scroll),
    GTK_POLICY_AUTOMATIC,   // Horizontal scroll
    GTK_POLICY_AUTOMATIC    // Vertical scroll
);
gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), listbox);
gtk_widget_set_vexpand(scroll, TRUE);
```

### 18.5 GtkNotebook (Tabs)
```c
GtkWidget *notebook = gtk_notebook_new();

GtkWidget *page1 = gtk_label_new("Page 1 content");
GtkWidget *tab1  = gtk_label_new("Tab 1");
gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, tab1);

GtkWidget *page2 = gtk_label_new("Page 2 content");
GtkWidget *tab2  = gtk_label_new("Tab 2");
gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, tab2);
```

### 18.6 GtkHeaderBar
Modern GNOME-style title bar:

```c
GtkWidget *header = gtk_header_bar_new();
gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header),
    gtk_label_new("My App"));

GtkWidget *new_btn = gtk_button_new_from_icon_name("document-new");
gtk_header_bar_pack_start(GTK_HEADER_BAR(header), new_btn);

gtk_window_set_titlebar(GTK_WINDOW(window), header);
```

---

### 📝 Assignment 18 — Capstone Project

**Task:** Build a **Note-Taking Application** with the following features:

**UI Requirements:**
- `GtkHeaderBar` with title "Notes" and a "New Note" button (+)
- `GtkNotebook` with two tabs: "All Notes" and "Trash"
- `GtkListBox` in "All Notes" tab showing note titles
- Clicking a note opens it in a `GtkTextView` editor panel
- A "Delete" button moves the selected note to Trash

**Data Requirements:**
- Use a `GList` to store notes (each note is a struct with title + body)
- Dynamically add and remove notes from the list and from the `GtkListBox`

**Bonus:** Add CSS styling with a sidebar/editor split layout using `GtkPaned`.

**Hint:** Use `gtk_paned_new(GTK_ORIENTATION_HORIZONTAL)` to create a split view. Put the `GtkScrolledWindow`+`GtkListBox` on the left, and a `GtkTextView` in a scroll window on the right. Store a pointer to the `GtkTextView` and `GList` in your `AppData` struct.

---

## Chapter 19 — Advanced GTK4 Topics

### 19.1 GtkTextView — Multiline Text Editor
```c
GtkWidget *textview = gtk_text_view_new();
gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD_CHAR);
gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), TRUE);

// Get/set text
GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
gtk_text_buffer_set_text(buffer, "Initial text", -1);

GtkTextIter start, end;
gtk_text_buffer_get_bounds(buffer, &start, &end);
char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
// Use text...
g_free(text);
```

### 19.2 GMenu & GAction (App Menus)
```c
// Define a menu
GMenu *menu = g_menu_new();
g_menu_append(menu, "New File",  "app.new");
g_menu_append(menu, "Open...",   "app.open");
g_menu_append(menu, "Quit",      "app.quit");

// Define action
GSimpleAction *quit_action = g_simple_action_new("quit", NULL);
g_signal_connect(quit_action, "activate", G_CALLBACK(on_quit), app);
g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));

// Set popover menu on button
GtkWidget *menu_btn = gtk_menu_button_new();
gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menu_btn), G_MENU_MODEL(menu));
```

### 19.3 GSettings — Persistent Settings
```c
GSettings *settings = g_settings_new("com.example.myapp");

// Save
g_settings_set_string(settings, "username", "Alice");
g_settings_set_int(settings, "font-size", 14);

// Load
char *user = g_settings_get_string(settings, "username");
g_free(user);

g_object_unref(settings);
```

### 19.4 Async Operations with GTask
GTK is single-threaded. For long operations, use `GTask` to run work in a thread:

```c
static void heavy_work(GTask *task, gpointer source, gpointer data, GCancellable *cancel) {
    // This runs in a worker thread
    g_usleep(2000000);  // Simulate 2-second work
    g_task_return_int(task, 42);
}

static void on_complete(GObject *source, GAsyncResult *result, gpointer user_data) {
    // This runs on the main thread when work is done
    GError *error = NULL;
    int value = g_task_propagate_int(G_TASK(result), &error);
    g_print("Result: %d\n", value);
}

// Start async work:
GTask *task = g_task_new(NULL, NULL, on_complete, user_data);
g_task_run_in_thread(task, heavy_work);
g_object_unref(task);
```

---

### 📝 Assignment 19

**Task:** Add a File menu to your Note-Taking app from Assignment 18:
1. A menu button in the header bar using `GtkMenuButton` + `GMenu`
2. Menu items: "New Note", "Save All", "Quit"
3. "Save All" writes all notes to a `.txt` file (one note per section)
4. "Quit" closes the application (using `g_application_quit`)

**Hint:** Use `g_action_map_add_action` on the `GtkApplication` object. For "Save All", open a file with `fopen`, iterate your `GList` of notes, and write each title and body with `fprintf`.

---

## Chapter 20 — Final Capstone Project

### 🏆 Full Application: Personal Task Manager

Build a complete task management desktop application with the following specifications:

**Features:**
1. **Task List** — Display tasks in a `GtkListBox` with:
   - Checkbox (`GtkCheckButton`) to mark complete
   - Task title (bold if due today)
   - Priority badge (High/Medium/Low)
   - Due date

2. **Add Task Dialog** — A custom `GtkWindow` with:
   - Title entry
   - Description (multiline `GtkTextView`)
   - Priority dropdown (`GtkDropDown`)
   - Date picker (use `GtkEntry` for simplicity)

3. **Filtering** — Three tabs (All, Pending, Completed) using `GtkNotebook`

4. **Persistence** — Save/load tasks from a binary file on startup/exit

5. **Search** — A `GtkSearchEntry` in the header bar that filters the list in real-time

6. **Styling** — CSS with:
   - Color-coded priorities (red/orange/green)
   - Strikethrough text for completed tasks
   - Clean card-style rows

**Data Model:**
```c
typedef enum { PRIORITY_LOW, PRIORITY_MEDIUM, PRIORITY_HIGH } Priority;

typedef struct {
    int       id;
    char      title[100];
    char      description[500];
    Priority  priority;
    char      due_date[11];  // "YYYY-MM-DD"
    gboolean  completed;
} Task;
```

**Architecture:**
- `main.c` — Entry point
- `app_window.c/h` — Window setup, layout, CSS
- `task_list.c/h` — List rendering, filtering, search
- `task_dialog.c/h` — Add/edit task dialog
- `storage.c/h` — File save/load
- `Makefile`

---

---

# 📚 RECOMMENDED RESOURCES

## Books
- **"The C Programming Language" (K&R)** — Kernighan & Ritchie — The definitive C reference
- **"C Programming: A Modern Approach"** — K.N. King — Best C textbook for beginners
- **"GTK+ / GNOME Application Development"** — Havoc Pennington — GTK concepts

## Online References
- **C Standard Library:** https://en.cppreference.com/w/c
- **GTK4 API Reference:** https://docs.gtk.org/gtk4/
- **GTK4 Tutorial:** https://toshiocp.github.io/Gtk4-tutorial/
- **GLib Reference:** https://docs.gtk.org/glib/
- **Cairo Documentation:** https://www.cairographics.org/documentation/

## Tools
- **GDB:** Debug segfaults step-by-step
- **Valgrind:** Find memory leaks
- **pkg-config:** Manage compiler flags for libraries
- **Make:** Automate your build process
- **GNOME Builder:** IDE with GTK4 project templates

---

# 📊 Progress Tracker

| Chapter | Topic | Status |
|---------|-------|--------|
| 1 | Intro to C & First Program | ☐ |
| 2 | Variables, Types & Operators | ☐ |
| 3 | Control Flow | ☐ |
| 4 | Functions & Recursion | ☐ |
| 5 | Arrays & Strings | ☐ |
| 6 | Pointers & Memory | ☐ |
| 7 | Dynamic Memory Allocation | ☐ |
| 8 | Structs, Unions & Enums | ☐ |
| 9 | File I/O | ☐ |
| 10 | Advanced C (Function Ptrs, Linked Lists) | ☐ |
| 11 | GTK4 Introduction | ☐ |
| 12 | Widgets & Layouts | ☐ |
| 13 | Signals & Callbacks | ☐ |
| 14 | Dialogs | ☐ |
| 15 | Drawing with Cairo | ☐ |
| 16 | GLib Utilities | ☐ |
| 17 | CSS Styling | ☐ |
| 18 | Building a Complete App | ☐ |
| 19 | Advanced GTK4 | ☐ |
| 20 | Final Capstone Project | ☐ |

---

*Roadmap authored by a Senior CS Instructor | C11 + GTK4 | 2025 Edition*