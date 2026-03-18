# Assignment 7: Dynamic Memory Operations

You are now operating at the hardware level. These exercises prove you can allocate, use, and release memory without leaking a single byte.

## Assignment 7.1: The Statistics Engine

Write a program that:
1. Asks the user how many integers they want to enter.
2. Dynamically allocates an array of exactly that size using `malloc`.
3. Checks for `NULL` (print an error and exit if allocation fails).
4. Reads each integer from the user via a loop.
5. Calculates the **arithmetic mean** (use `double` for the division).
6. Prints every element that is **above the mean**.
7. `free`s the array and sets the pointer to `NULL`.

### Example Interaction
```
How many integers? 5
Enter integer 1: 10
Enter integer 2: 20
Enter integer 3: 30
Enter integer 4: 40
Enter integer 5: 50

Mean: 30.00
Elements above mean: 40 50
```

## Assignment 7.2: The Growing Buffer

Write a program that reads integers from the user one at a time, indefinitely, until they type `0`. You do **not** know how many numbers they will enter.

### Requirements
1. Start with an initial `capacity` of `4` using `malloc`.
2. Track the current `size` (how many items stored so far).
3. When `size == capacity`, double the capacity using `realloc`. Remember to use a temp pointer!
4. When the user types `0`, stop reading.
5. Print all stored numbers and the final count.
6. `free` all memory.

### Example Interaction
```
Enter numbers (0 to stop):
> 5
> 12
> 7
> 33
> 8
> 99
> 0

You entered 6 numbers: 5 12 7 33 8 99
```

## Verification

```bash
# Compile with debug info
gcc -g -Wall -Wextra -std=c11 assign7.c -o assign7

# Check for memory leaks on Linux
valgrind --leak-check=full ./assign7

# Check for memory leaks on macOS
leaks --atExit -- ./assign7
```

### Checklist
- [ ] Does Valgrind / `leaks` report **0 bytes lost**?
- [ ] Does your `realloc` use a temporary pointer to avoid the realloc trap?
- [ ] If you enter `0` immediately (zero elements), does the program handle it gracefully without crashing?
