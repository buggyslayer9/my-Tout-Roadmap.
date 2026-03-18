# Assignment 2: The Data Types Gauntlet

We've talked about how C views the world through a lens of raw bytes and types. Now it's your turn to prove you understand it. This assignment tests your ability to declare variables, understand their memory footprints, and manipulate them without causing overflow or precision loss.

## Assignment 2.1: The Hardware Interrogator

Write a program that interrogates the exact limits and sizes of data types on the specific hardware it's running on.

### Requirements
1. Declare variables of at least 8 different types: `char`, `short`, `int`, `long`, `long long`, `float`, `double`, and `bool`.
2. Print the exact byte size of every single type using the `sizeof` operator.
3. Use the `<limits.h>` and `<float.h>` headers to extract and print the exact minimum and maximum values for `int`, `unsigned int`, `long`, `float`, and `double`.

Example Output snippet:
```
=== HARDWARE INTERROGATOR ===
int:       4 bytes (-2147483648 to 2147483647)
float:     4 bytes (max: 3.40e+38)
```

## Assignment 2.2: The Arithmetic Disaster

Math in C is a minefield if you don't respect the types. Write a program that demonstrates three common, disastrous arithmetic bugs, and then provides the correct, fixed version.

### Requirements
1. **The Integer Division Trap**:
   - Divide `7` by `2` using purely integer math and save the result. (It will be `3`).
   - Fix it: Use type casting `(double)` to correctly yield `3.5`.
2. **The Overflow Bomb**:
   - Create a `char` variable set to `127`.
   - Add `1` to it and print the result. Validate that it wrapping around to `-128`.
   - Fix it: Use an `int` or `short` instead to properly show `128`.
3. **The Silent Truncation**:
   - Create a `double` variable representing a massive sum of money: `2500000.99`.
   - Cast it to an `int` and print it. Describe in a `printf` statement what happened to the 99 cents.

## Assignment 2.3: Bitwise Operations Sandbox (Bonus)

If you're feeling brave, let's touch the raw bits.

Write a program that takes an integer, say `10` (which is `1010` in binary), and performs a bitwise left-shift `<< 1`. Print the result.
Notice how shifting the bits to the left mathematically multiplied the number by 2! 

Now try right-shifting `>> 1` and see how it cleanly divides it by 2.

## Submission Checklist

- [ ] Does your code compile without warnings (`-Wall -Wextra -std=c11`)?
- [ ] Did you use `%zu` when printing `sizeof` results? (Rookies use `%d`, veterans use `%zu`).
- [ ] Did you manage to trigger and expose the overflow bugs on purpose?

If you get stuck, remember that C expects you to explicitly convert types when math needs a decimal. Put `(double)` in front of the variable before the math operator. Good luck.
