# 4.2 Code Contracts: Declaration vs Definition

C parses files top-down. If `main()` tries to call a function called `fire_missiles()`, but the code for `fire_missiles()` is written *below* `main()`, the compiler will panic because it hasn't seen it yet.

To fix this, we split functions into two parts: the **Declaration** (the promise) and the **Definition** (the payload).

## The One-File Prototype

```c
#include <stdio.h>

// 1. The Declaration (also called a Prototype)
// This tells the compiler: "I promise a function called add exists. 
// It returns an int, and takes two ints. Trust me, you'll find it."
int add(int a, int b);

int main(void) {
    // The compiler allows this because it trusts the prototype!
    int total = add(3, 4);  
    printf("Total: %d\n", total);
    return 0;
}

// 2. The Definition
// This is the actual machine instructions.
int add(int a, int b) {
    return a + b;
}
```

## Why Do We Do This? (Header Files)

In tiny 50-line programs, prototyping above `main()` seems annoying. Why not just write the whole function above `main()`? 

Because in the real world, programs are thousands of files.
- The **Declarations** go into `.h` (header) files. (`math.h`, `stdio.h`)
- The **Definitions** go into `.c` (source) files. 

When you `#include <stdio.h>`, you are simply copy-pasting the *Declarations* of `printf` so your compiler knows how to use it. The actual *Definition* is already pre-compiled in a massive system library file (like `libc.so`), which the Linker glues together later.
