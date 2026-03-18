# 2.1 The Metal Reality: Fundamental Data Types

Welcome to memory management. C has several built-in data types, each with a specific size and mathematical range. Understanding these is non-negotiable because **you are responsible for choosing the right type**. If you choose wrong, you will cause integer overflows, memory bloat, or fatal precision loss.

## Why Do Data Types Matter?

In languages like JavaScript or Python, the interpreter holds your hand and expands numbers infinitely. C doesn't care. C demands exact byte specifications.

- **Memory Usage**: Every variable consumes exactly the number of bytes you ask for. No more, no less.
- **Performance**: Pushing a 64-bit number onto a 32-bit CPU register is slow. Pick the right size.
- **Range Limits**: Hardware has minimum and maximum values. Exceed them, and your numbers wrap around into garbage or crash your app.
- **Precision**: Floating-point math is inherently broken at extreme scales. Know your accuracy limits.

## The Integers (Whole Numbers)

| Type | Typical Size | Range | When to Use It |
|------|--------------|-------|----------------|
| `char` | 1 byte | -128 to 127 | ASCII characters, tiny numbers. |
| `unsigned char` | 1 byte | 0 to 255 | Raw byte data (networks, files). |
| `short` | 2 bytes | -32,768 to 32,767 | When memory is extremely tight. |
| `int` | 4 bytes | -2.1B to +2.1B | **Your default choice for numbers.** |
| `unsigned int` | 4 bytes | 0 to 4.2B | Positive-only counts (IDs, loops). |
| `long` | 4 or 8 bytes | Platform dependent | File sizes, memory offsets. |
| `long long` | 8 bytes | ±9.2 quintillion | Astronomical numbers. |

### The Integer Battlefield

```c
#include <stdio.h>
#include <limits.h>  // The sacred scroll of maximum limits

int main(void) {
    // 1 Byte
    char grade = 'A';
    unsigned char network_byte = 255;
    
    // 4 Bytes: The workhorses
    int age = 25;
    unsigned int user_id = 123456;
    
    // 8 Bytes: The heavy hitters
    long long national_debt = 34000000000000LL; // Notice the 'LL' suffix
    
    printf("Hardware Reality Check:\n");
    printf("An int on this machine is: %zu bytes\n", sizeof(int));
    printf("A long on this machine is: %zu bytes\n", sizeof(long));
    printf("Max val of an int: %d\n", INT_MAX);
    
    return 0;
}
```

## The Floating-Point Types (Decimals)

Floats and doubles represent decimals using scientific notation under the hood. They are not perfect; they just get "close enough."

| Type | Size | Precision | Use Case |
|------|------|-----------|----------|
| `float` | 4 bytes | ~6-7 decimal digits | 3D Graphics matrices, low-memory arrays. |
| `double` | 8 bytes | ~15-16 decimal digits | **Your default choice for decimals.** |

### Best Practices for Decimals

```c
#include <stdio.h>

int main(void) {
    // Always use double unless you have a specific reason not to.
    // Modern CPUs process doubles just as fast as floats.
    double precise_pi = 3.141592653589793;
    
    // IF you use float, add the 'f' suffix!
    float cheap_pi = 3.14159f;
    
    return 0;
}
```

## Boolean Logic (C99 and onward)

Standard C didn't have true/false. It only had `0` (false) and `Not 0` (true). We got a boolean type in 1999:

```c
#include <stdio.h>
#include <stdbool.h>  // You MUST include this for bool, true, and false!

int main(void) {
    bool kernel_panic = false;
    bool is_root = true;
    
    printf("Are we root? %s\n", is_root ? "Yes" : "No");
    
    // Under the hood, a bool is literally just a 1 or a 0.
    printf("True is just the integer: %d\n", (int)true);
    
    return 0;
}
```

## Common Rookie Mistakes

### 1. Integer Overflow
```c
// DO NOT DO THIS
short debt = 32767;
debt += 1; // It just rolled over to -32768. You broke the bank.
```

### 2. Money in Floating Points
```c
// NEVER STORE CURRENCY IN FLOATS OR DOUBLES
float price = 19.99f;
// Due to binary rounding errors, this might end up as 19.989999f
// Use integers representing cents instead! (int price_cents = 1999)
```

### 3. Mixing Signed and Unsigned Data
```c
unsigned int items = 10;
int offset = -15;
// IF you add these, 'offset' gets promoted to a massive unsigned number!
```

## The GTK Connection

When we get to GTK, you won't see `int` or `float` very often. You will see `gint32`, `guint64`, and `gboolean`. Why? Because standard C types vary in size across Mac, Windows, and Linux. GTK uses its own types to guarantee they are the exact same size on every operating system on earth.

- `gint32` is guaranteed to be 32 bits.
- `guint64` is guaranteed to be 64 bits unsigned.
- `gboolean` is guaranteed to be GTK's true/false equivalent.

Memorize these concepts. Memory size is everything.
