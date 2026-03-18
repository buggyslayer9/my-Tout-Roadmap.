# 3.1 Control Flow: if / else if / else

Code without control flow is just a predetermined script. Control flow is how you teach the machine to make decisions. 

In C, an `if` statement evaluates an expression. If that expression evaluates to *anything other than zero*, it is considered true.

## The Standard Structure

```c
#include <stdio.h>

int main(void) {
    int score = 85;

    if (score >= 90) {
        printf("Grade: A\n");
    } else if (score >= 80) {
        printf("Grade: B\n");
    } else if (score >= 70) {
        printf("Grade: C\n");
    } else {
        printf("Grade: F\n");
        printf("You need to study pointers more.\n");
    }

    return 0;
}
```

## The Single-Line Trap

If you have only one statement inside an `if` block, C allows you to drop the curly braces `{ }`. 

```c
if (score == 100)
    printf("Perfect score!\n");
```

**Veteran Advice:** *Never do this.* One day, you will come back to add a second line of code beneath it, forget to add the curly braces, and waste 4 hours debugging because that second line executes every single time regardless of the `if` statement. Always use braces.

## Truthiness in C

As mentioned, C doesn't have a strict Boolean type without `#include <stdbool.h>`. Instead:
- `0` is strictly False.
- `1`, `-1`, `42`, and `0xFA` are all True.

```c
int error_code = -5;

// This will execute because error_code is not 0!
if (error_code) {
    printf("An error occurred with code %d\n", error_code);
}
```
Pointers work the exact same way. If a pointer is `NULL` (which is just `0` in disguise), it evaluates to false. If it points to valid memory, it evaluates to true. We'll use this constantly in GTK.
