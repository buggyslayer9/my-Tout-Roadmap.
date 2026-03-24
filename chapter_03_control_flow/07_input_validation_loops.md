# 3.7 Input Validation With Loops

Many beginner programs work only when the user behaves perfectly.

Real programs need to handle:

- wrong input
- empty input
- unexpected numbers
- retry flows

Control flow becomes much more useful when you use it to keep the program in a valid state.

## A Common Pattern

You ask for input, check it, and repeat until it is acceptable.

That usually means:

- read input
- test a condition
- loop again if invalid

## Example

```c
#include <stdio.h>

int main(void) {
    int age = -1;

    while (age < 0) {
        printf("Enter your age: ");
        scanf("%d", &age);

        if (age < 0) {
            printf("Age must be zero or greater.\n");
        }
    }

    printf("Your age is %d\n", age);
    return 0;
}
```

This is simple, but it introduces an important idea:

**loops are not only for repetition, they are also for correctness.**

## Why This Matters

Input validation is one of the earliest places where programming starts to feel real.

Instead of:

- assuming perfect input

you start:

- checking assumptions
- handling mistakes
- guiding the user

## Good Habits

- validate as early as possible
- print clear error messages
- keep retry loops easy to follow
- avoid deeply nested input logic when possible

## Learning Check

- Can I write a loop that repeats until input is valid?
- Can I explain why validation belongs near input handling?
- Can I improve one earlier exercise with retry logic?

## Recommended Follow-Up

Upgrade a previous exercise so the program keeps asking until the user enters valid data.
