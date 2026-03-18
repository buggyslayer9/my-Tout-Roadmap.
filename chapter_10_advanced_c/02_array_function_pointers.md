# 10.2 Arrays of Function Pointers: The Dispatch Table

If a single function pointer lets you swap behavior at runtime, an **array** of function pointers lets you build a dispatch table — a lookup index of executable operations.

## The Pattern

```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

int main(void) {
    // An array of function pointers. Each slot holds a different operation.
    int (*ops[])(int, int) = { add, sub, mul };
    const char *names[] = { "ADD", "SUB", "MUL" };
    
    for (int i = 0; i < 3; i++) {
        printf("%s(10, 5) = %d\n", names[i], ops[i](10, 5));
    }
    
    return 0;
}
```

**Output:**
```
ADD(10, 5) = 15
SUB(10, 5) = 5
MUL(10, 5) = 50
```

## Why This Matters

Dispatch tables eliminate massive `switch` blocks. Instead of:
```c
switch (command) {
    case 0: result = add(a, b); break;
    case 1: result = sub(a, b); break;
    case 2: result = mul(a, b); break;
}
```

You just do:
```c
result = ops[command](a, b);
```

This pattern is used in interpreters, virtual machines, command parsers, and menu systems. GTK's signal dispatch mechanism follows a similar philosophy internally.
