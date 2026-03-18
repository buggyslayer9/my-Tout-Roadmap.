# 4.4 Recursion: The Infinite Mirror

Recursion algorithmically happens when a function calls itself. It is a mathematical concept that is incredibly elegant for parsing trees, sorting data, and navigating file systems.

Every recursive function requires two things to not explode:
1. **The Recursive Case**: The part where it calls itself with a slightly modified problem.
2. **The Base Case**: The absolute stop condition. Without this, the function loops until it exceeds available RAM (a Stack Overflow).

## Example: Factory Mathematics (Factorial)

The factorial of `4!` is `4 * 3 * 2 * 1`.
Notice that `4!` is just `4 * 3!`. 
Which means we can define the function exactly like the math equation.

```c
#include <stdio.h>

int factorial(int n) {
    // 1. The Base Case (The Stop Condition)
    // If we reach 0, return 1 immediately so we stop looping.
    if (n == 0) {
        return 1;        
    }
    
    // 2. The Recursive Case
    // Multiply n by the result of factorial(n - 1).
    return n * factorial(n - 1); 
}

int main(void) {
    int result = factorial(4);
    printf("Factorial of 4 is: %d\n", result); // 24
    return 0;
}
```

## Example: The Fibonacci Sequence
Each number is the sum of the two preceding ones.

```c
int fibonacci(int n) {
    // Base Case: 0 returns 0. 1 returns 1.
    if (n <= 1) { 
        return n;
    }
    
    // Recursive Case: Call myself twice.
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

## The Dark Side of Recursion

Recursion forces the operating system to allocate a new memory frame on the CPU Stack every single time it loops.
If you call `factorial(10000)`, it will stack 10,000 function calls in RAM simultaneously. Your OS will kill the program with a `Segmentation fault (core dumped)`.

**Veteran Rule**: If you can write an algorithm with a simple `while` or `for` loop, you should use the loop. Use recursion *only* when the data structure demands it (like parsing a JSON tree or navigating a maze of directories).
