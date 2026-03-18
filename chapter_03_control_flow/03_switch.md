# 3.3 The Switch Statement

When you have a single variable and you want to check it against a massive list of exact integer values, `if/else` becomes tedious. The `switch` statement is your dispatcher.

## Structure

```c
#include <stdio.h>

int main(void) {
    char command = 'q';

    switch (command) {
        case 'n':
            printf("Starting new game...\n");
            break;
        case 'l':
            printf("Loading saved game...\n");
            break;
        case 'q':
            printf("Quitting to desktop. Goodbye.\n");
            break;
        default:
            printf("Error: Unknown command key.\n");
            break; // The final break isn't strictly necessary, but it's good form.
    }
    
    return 0;
}
```

## The Fall-Through Danger

Unlike other languages, C's `switch` statement doesn't automatically stop executing when it hits the end of a `case`. If you forget the `break;` statement, it will "fall through" and immediately execute the code in the next `case` block!

```c
int level = 2;

switch(level) {
    case 1:
        printf("Bronze ");
        // I FORGOT THE BREAK!
    case 2:
        printf("Silver ");
        // I FORGOT THE BREAK!
    case 3:
        printf("Gold\n");
        break;
}
// If level is 2, this prints: Silver Gold
// Sometimes this is useful. Mostly, it's a bug.
```

## Deliberate Fall-Through (The Hacker's "Or")

Sometimes you *want* fall-through. If multiple cases should trigger the exact same block of code, you can stack them:

```c
char input = 'y';

switch (input) {
    case 'y':
    case 'Y':
        printf("User accepted the terms.\n");
        break;
    case 'n':
    case 'N':
        printf("User declined.\n");
        break;
}
```

## Rules of the Switch

1. **Only Integers Allowed**: You can only use `switch` on integral types (`int`, `char`, `enum`). You cannot `switch` on a string or a float!
2. **Compile-time Constants**: The values in your `case` statements must be known at compile time. You can't do `case variable_x:`.
3. **Always use `default`**: Even if you think every case is handled, put a `default:` at the bottom to catch garbage memory values or bugs.
