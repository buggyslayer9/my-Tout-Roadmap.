# Assignment 3: Flow Control Bootcamp

If you can't control the flow of execution, your C program is just a brick. This set of assignments proves you understand how to navigate execution logic effectively. 

## Assignment 3.1: The Grading Sentinel

Write a program that endlessly asks the user for test scores. It stops when the user types `-1`.

### Requirements
1. Implement a `while (1)` or `for (;;)` core loop.
2. Inside the loop, prompt the user with `"Enter a score (or -1 to quit): "` and read it with `scanf("%d", &score)`.
3. If they enter `-1`, gracefully `break` immediately without printing a grade.
4. If they enter `0` to `100`, use a block of `if / else if / else` statements to output the corresponding letter grade. (A >= 90, B >= 80, C >= 70, F < 70).
5. If they enter anything above `100` or below `-1`, print `"Error: Invalid Score"` but keep the loop running via `continue`.

## Assignment 3.2: The Switchboard Operations

Convert a clunky `if/else` mess into a highly structured `switch` statement.

### Requirements
1. Use an infinite loop again. Prompt the user for an operation character: `+`, `-`, `*`, `/`, or `q` for quit.
2. Next, prompt for two integers. (If `q`, break before asking for numbers).
3. Using a pure `switch(operator)` block, run the exact arithmetic equation the user asked for and `printf` the result.
4. Implement a `default` case to catch invalid command characters.
5. In the `/` case, prevent `Division by Zero` with a quick `if (num2 == 0)` check before dividing. 

## Assignment 3.3: The Matrix (Nested Loops)

This is a classic programming challenge. Write a program that prints a cleanly formatted multiplication table up to 10.

### Requirements
1. The table must perfectly align itself, regardless of numbers having one digit or three digits.
2. Use horizontal and vertical table borders. (ASCII `|` and `-` are acceptable).
3. You must use nested `for` loops. The outer loop controls rows (Y coordinate), the inner handles columns (X coordinate).

### Example Output

```text
      |   1   2   3   4   5   6   7   8   9  10
------------------------------------------------
   1  |   1   2   3   4   5   6   7   8   9  10
   2  |   2   4   6   8  10  12  14  16  18  20
   3  |   3   6   9  12  15  18  21  24  27  30
   4  |   4   8  12  16  20  24  28  32  36  40
   5  |   5  10  15  20  25  30  35  40  45  50
...
```

*Veteran Tip*: Getting the exact padding format string right is 90% of the battle here. Review `man 3 printf` and look into exact column width specifications: `%4d` forces an integer to take up exactly 4 spaces on the screen, padding the left side with empty blanks. 

## Submission Validation

- [ ] Does your command compiler pass with `-Wall -Wextra -std=c11`?
- [ ] Try inputting garbage letters into your `scanf("%d", ...)` integer readers. Did the program start an infinite doomloop? Read up on clearing `stdin` buffers for extra credit.
- [ ] If you break out of the Switchboard `q` case, does it cleanly terminate the application?

Good luck, console warrior. Time to lay code.
