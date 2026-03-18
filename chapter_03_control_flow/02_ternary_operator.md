# 3.2 The Ternary Operator

The ternary operator `?:` is essentially a compressed `if/else` statement. It's the only operator in C that demands **three operands**. It evaluates a condition and returns one of two values.

## Syntax

```c
// result = (condition) ? value_if_true : value_if_false;
```

## Practical Example

```c
#include <stdio.h>

int main(void) {
    int a = 10, b = 20;
    
    // Read this as: "Is a greater than b? If yes, give me a. If no, give me b."
    int max = (a > b) ? a : b;  
    
    printf("The max value is: %d\n", max); // 20
    return 0;
}
```

## When to Use It (And When to Run Away)

The ternary operator is a sharp tool. Used correctly, it makes your code clean and concise. Used poorly, it creates unreadable garbage.

✅ **DO use it for simple assignments or inline logic:**
```c
// Clean, readable, and elegant.
int score = 75;
const char *status = (score >= 60) ? "PASS" : "FAIL";
printf("Result: %s\n", status);
```

❌ **DO NOT use it to execute functions with side effects:**
```c
// DANGEROUS HACKER NONSENSE
// Do not use the ternary to replace normal control flow!
(x > 0) ? printf("Positive\n") : printf("Negative\n");

// Write a real if/else block instead.
if (x > 0) {
    printf("Positive\n");
} else {
    printf("Negative\n");
}
```

## The Nested Ternary Trap

You *can* put a ternary inside another ternary. 
You *shouldn't*, but you can. 

```c
// This is rapidly becoming unreadable.
const char *grade = (score >= 90) ? "A" :
                    (score >= 80) ? "B" :
                    (score >= 70) ? "C" : "F";
```

> **Instructor Tip**: Code is read ten times more often than it is written. If you have to stare at a ternary operator for more than two seconds to understand what it does, delete it and write an `if / else` block. 
