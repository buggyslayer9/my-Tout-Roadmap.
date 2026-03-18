# 4.3 The Great Filter: Pass by Value

Here is a fact that trips up almost every junior developer: **C passes function arguments by value.** 

What does that mean? It means when you pass a variable to a function, the function does *not* get the variable. It gets a **photocopy** of the variable.

## The Photocopy Problem

```c
#include <stdio.h>

void try_to_mutate(int x) {
    // 'x' is just a photocopy of 'health'!
    x = 100; // Modifies the photocopy.
    printf("Inside function: x is %d\n", x); // 100
}

int main(void) {
    int health = 50;
    
    try_to_mutate(health); // Handing the function a photocopy of '50'.
    
    // The original data remains untouched!
    printf("Inside main: health is %d\n", health); // Still 50!
    return 0;
}
```

## Why Does C Do This?

Security and isolation. If calling a mathematical function accidentally altered the original variable sitting in `main()`, debugging would be a living nightmare. By operating on photocopies, a function can modify its input variables as much as it wants without destroying the caller's data.

## The Escape Hatch: Pointers

If `try_to_mutate` isn't allowed to change `health`, how do functions like `scanf("%d", &health)` work? How do they inject data into variables?

They use **Pointers**. Instead of giving `scanf` a photocopy of the number, you hand `scanf` the physical memory address (using `&`) of your variable. You give it the exact hardware coordinate, and say "Write to this location." 

We will cover pointers extensively in Chapter 6. For now, burn this rule into your mind: **Functions cannot permanently change the variables you hand them.**
