# 10.1 Function Pointers: Executable Addresses

Every function in your compiled binary sits at a specific memory address, just like a variable. A **function pointer** stores that address, allowing you to call different functions through the same variable at runtime.

This is C's mechanism for callbacks, plugin architectures, and event-driven programming. GTK is built entirely on function pointers — every button click, every window resize event — all dispatched through function pointers.

## Declaring and Using a Function Pointer

```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main(void) {
    // Syntax: return_type (*pointer_name)(param_types)
    int (*operation)(int, int);
    
    operation = add;
    printf("Add: %d\n", operation(3, 4));    // 7
    
    operation = mul;
    printf("Mul: %d\n", operation(3, 4));    // 12
    
    return 0;
}
```

## Passing Functions as Arguments

This is the **callback** pattern. You write a generic engine that accepts a function pointer as a parameter, allowing the caller to inject custom behavior.

```c
void apply_operation(int a, int b, int (*op)(int, int)) {
    printf("Result: %d\n", op(a, b));
}

int main(void) {
    apply_operation(10, 5, add);  // Result: 15
    apply_operation(10, 5, mul);  // Result: 50
    return 0;
}
```

## Using Typedef to Clean Up the Syntax

The raw function pointer syntax is notoriously ugly. Typedef fixes that:

```c
typedef int (*MathOp)(int, int);

void apply(int a, int b, MathOp op) {
    printf("Result: %d\n", op(a, b));
}
```

> **GTK Preview:** When you connect a button's "clicked" signal, you pass a function pointer (your callback handler). GTK stores it and invokes it when the user clicks.
