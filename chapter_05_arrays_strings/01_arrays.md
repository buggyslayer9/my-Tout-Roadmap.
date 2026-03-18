# 5.1 Arrays: Contiguous Memory Blocks

Variables are great for storing single points of integer or floating-point data. But if you need to store 10,000 enemy health values, creating 10,000 separate `int` variables is madness. 

An array is a continuous, unbroken sequence of memory blocks of the exact same data type.

## Declaration and Initialization

```c
// 1. Give me 5 integers in a row. Initialize them specific values.
int numbers[5] = {10, 20, 30, 40, 50};

// 2. Give me 3 doubles.
double grades[3] = {95.5, 87.3, 91.0};

// 3. Give me 100 integers, and set EVERY single one to 0. 
// This is incredibly useful for zeroing out a buffer.
int memory_buffer[100] = {0};  

// 4. Let the compiler figure out the size based on the curly braces.
int dynamic_count[] = {1, 2, 3}; // Size is exactly 3.
```

## Accessing the Grid (Zero-Based Indexing)

C, like almost all systems languages, uses **Zero-Based Indexing**. The first item is at index `0`. The final item is at index `length - 1`.

Why? Because the index isn't a "number in a list". It is a **memory offset**. Index `0` literally means `start_address + (0 * size_of_item)`. 

```c
printf("First item: %d\n", numbers[0]);  // Prints 10
printf("Third item: %d\n", numbers[2]);  // Prints 30
printf("Last item: %d\n", numbers[4]);   // Prints 50
```

## ⚠️ The Undefined Behavior Trap

C assumes you know what you are doing. It does **not** perform bounds checking. If you ask for the 10th item in a 5-item array, C will happily step outside your array and read whatever random raw data happens to be sitting in that adjacent memory register.

```c
// DANGER: We stepped out of bounds by 5 integer lengths!
numbers[10] = 999;  // This violently corrupts adjacent memory. 
                    // Your program might crash. It might silently fail. 
                    // It might grant remote shell access to a hacker.
```
If your program randomly crashes with a `Segmentation fault`, an out-of-bounds array access is usually the culprit.
