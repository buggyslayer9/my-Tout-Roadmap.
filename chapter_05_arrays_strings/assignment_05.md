# Assignment 5: Memory Management and Strings

You now know how to manipulate continuous memory blocks and raw character data. In C, you are essentially manually sorting bits.

## Assignment 5.1: The Alpha Sorter (Bubble Sort)

Write a program that takes exactly 5 full names from a user, stores them in a 2D array matrix of characters, sorts them alphabetically, and prints the result.

### Requirements

1. **The Data Structure**: Create a variable `char names[5][50];`. This is a 2D array capable of storing 5 independent strings, each up to 49 characters long.
2. **The Input**: Use a `for` loop to ask the user "Enter name [X]:". 
3. **The Buffer Defense**: Use `fgets(names[i], 50, stdin);` to read the input securely. Remember to strip the invisible `\n` newline character from `names[i]` immediately after capturing it!
4. **The Algorithm**: Implement a classic Bubble Sort.
   - Use nested loops.
   - Use `strcmp(names[j], names[j+1])` to determine if two names are alphabetically out of order. `strcmp` returns a number `> 0` if the first string comes alphabetically *after* the second string.
   - If they are out of order, swap them!
   - Because you cannot assign array memory with `=`, you must create a temporary buffer `char temp[50];` and use `strcpy()` to shuffle the strings around during the swap.
5. **The Output**: Print the finally sorted list in alphabetical order.

### Example Console Interaction

```text
Enter student name 1: Charlie
Enter student name 2: Alice
Enter student name 3: Eve
Enter student name 4: David
Enter student name 5: Bob

Sorted Roster:
1. Alice
2. Bob
3. Charlie
4. David
5. Eve
```

## Developer Hints

**The Swap Logic**:
Swapping strings in C requires 3 completely separate copy commands:

```c
// Move item A into safe holding
strcpy(temp, item_a);
// Overwrite item A with item B
strcpy(item_a, item_b);
// Drop item A (now from the safe holding) into item B's old slot
strcpy(item_b, temp);
```

**Bubble Sort Primer**:
Bubble Sort works by stepping through the array, comparing adjacent elements, and swapping them repeatedly until the list is sorted.
```c
for (int i = 0; i < 5 - 1; i++) {
    for (int j = 0; j < 5 - i - 1; j++) {
        // Your strcmp logic goes here!
    }
}
```

## Validation Checklist
- [ ] Try typing a 60 character name. Did the `fgets` buffer truncate it cleanly to 49 without causing a segfault?
- [ ] If you type "John Doe", does it sort based on the whole name, or just "John"? `fgets` ensures it captures the whole line.
- [ ] Are you correctly stripping the `\n` character? If you aren't, your outputs will have extremely strange double-spacing.

Good hunting.
