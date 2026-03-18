# 3.6 Nested Loops: The Inception Pattern

A nested loop is simply a loop stuffed entirely inside another loop. 
The mathematical rule here is absolute: **The inner loop must complete all of its iterations* for *every single iteration* of the outer loop.

It's how we iterate through matrices, generate complex terminal outputs, and build simple sorting algorithms.

## The Classic Multiplication Table Example

```c
#include <stdio.h>

int main(void) {
    // The Outer Loop: Controls the Rows
    for (int row = 1; row <= 3; row++) {
        
        // The Inner Loop: Controls the Columns
        for (int col = 1; col <= 3; col++) {
            printf("%d ", row * col);
        }
        
        // When the inner loop finishes 3 iterations, we print a newline. 
        printf("\n");
    }
    return 0;
}
```

**Output:**
```
1 2 3
2 4 6
3 6 9
```

## The Mental Breakdown

For `row = 1`, the inner loop runs its entire gauntlet: `col = 1`, `col = 2`, `col = 3`. Next `row`...
For `row = 2`, the inner loop runs `col = 1`, `col = 2`, `col = 3`. Next `row`...
For `row = 3`, the inner loop runs `col = 1`, `col = 2`, `col = 3`. Done.

**Total Executions**: Outer `row` loop iterations × Inner `col` loop iterations = 3 × 3 = **9 total cycles**.

## Common Industry Use Cases

| Pattern | Description |
|---------|-------------|
| **Matrix Operations** | Searching or modifying data inside a 2D array grid. |
| **Image Processing** | Processing every pixel (x, y) coordinates of an image in memory. |
| **Sorting Algorithms** | Algorithms like Bubble Sort require comparing every item against every other item. |

## ⚠️ The Big-O Performance Warning

Nested loops have an invisible multiplier effect. A loop that iterates 1,000 times inside another loop that iterates 1,000 times means your code executes **1,000,000 operations**.

```c
// THIS IS AN O(n³) ARCHITECTURE
// 1000 * 1000 * 1000 = 1 BILLION ITERATIONS!
// This will physically lock up your computer for several seconds.
for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
        for (int k = 0; k < 1000; k++) {
            // CPU Meltdown
        }
    }
}
```

Never nest loops unless you absolutely have to. When you do, always analyze memory and performance overheads. 

## The Escape Hatch: Breaking Multi-Level Loops

The `break` statement only terminates the **innermost** loop it currently resides in. If you are stuck three loops deep and detect a catastrophic error, a `break;` will only pop you up to level two.

To break everything simultaneously, C developers use "flag variables" (often a simple `int` pseudo-boolean check in the condition section of the `for` loops), or they structure the code into a separate function entirely and call `return;`.
