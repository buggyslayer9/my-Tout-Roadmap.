# 7.7 A Practical Valgrind Workflow

Dynamic memory becomes much easier once you stop guessing and start checking.

**Valgrind** is one of the most useful tools in beginner and intermediate C development because it helps you catch:

- memory leaks
- invalid reads
- invalid writes
- use of uninitialized values
- double frees

This lesson focuses on how to use Valgrind as part of your normal workflow.

## Why Valgrind Matters

A C program can:

- compile successfully
- appear to run correctly
- still contain dangerous memory bugs

That is why successful compilation is not enough in C.

You need a tool that watches memory behavior while the program runs.

## Step 1: Compile With Debug Information

Before using Valgrind, compile with debug symbols:

```bash
gcc -Wall -Wextra -std=c11 -g main.c -o main
```

The `-g` flag helps Valgrind show file names and line numbers.

## Step 2: Run Valgrind

Basic usage:

```bash
valgrind ./main
```

This already catches a lot, but the more useful form is:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./main
```

These options give better leak details.

## Example Program With A Leak

```c
#include <stdlib.h>

int main(void) {
    int *numbers = malloc(5 * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    numbers[0] = 42;
    return 0;  // forgot to free(numbers)
}
```

Valgrind will report memory that was allocated but never freed.

## Example Program With Invalid Access

```c
#include <stdlib.h>

int main(void) {
    int *numbers = malloc(3 * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    numbers[3] = 99;  // out of bounds
    free(numbers);
    return 0;
}
```

This is the kind of bug that may sometimes seem fine without a tool, but Valgrind can catch it.

## How To Read Valgrind Output

Do not panic when the output looks long.

Start with these questions:

1. Is it reporting a leak, invalid read, or invalid write?
2. Which file and line number are mentioned?
3. What memory block is involved?
4. Did I free too late, not at all, or access out of bounds?

You usually do not need to understand every line at first. Focus on the first meaningful stack trace in your own code.

## A Good Beginner Workflow

Use this loop:

1. compile with `-g`
2. run the program normally
3. run it again with Valgrind
4. fix one reported issue at a time
5. rerun until the report is clean

That is much better than waiting until your project becomes large and confusing.

## What “Definitely Lost” Means

One of the most important leak categories is:

- **definitely lost**

This means Valgrind is confident you leaked memory and no pointer still exists to free it later.

As a learner, this is one of the first categories to prioritize.

## Common Mistakes

- forgetting `free`
- freeing memory twice
- writing past array bounds
- using memory after freeing it
- assuming “it didn’t crash” means “it is safe”

## Valgrind Is Not Magic

Valgrind is very useful, but it does not replace thinking.

You still need good habits:

- pair every allocation with a cleanup plan
- check bounds carefully
- initialize values
- keep ownership simple

Valgrind helps you verify those habits.

## Learning Check

- Can I compile with `-g` and run Valgrind on a small program?
- Can I explain the difference between a memory leak and an invalid write?
- Can I use Valgrind to improve one of my earlier dynamic-memory exercises?

## Recommended Follow-Up

Take one earlier Chapter 7 program and run:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./your_program
```

Then fix every reported issue.

That is one of the most valuable memory-management exercises you can do.
