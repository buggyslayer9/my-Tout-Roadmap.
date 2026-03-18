# Assignment 6: Pointer Combat Training

Pointers are the beating heart of C. If you can solve these exercises cleanly, you are ready for dynamic memory, data structures, and GTK programming.

## Assignment 6.1: The Min/Max Extractor

Write a function that scans an integer array and returns both the minimum and maximum values simultaneously. Since C functions can only `return` one value, you must use **output pointers** to hand both results back to the caller.

### Function Signature
```c
void find_min_max(int *arr, int len, int *out_min, int *out_max);
```

### Requirements
1. Initialize `*out_min` and `*out_max` to the first element of the array.
2. Iterate through the array using pointer arithmetic or bracket notation.
3. Compare each element. If smaller than `*out_min`, update it. If larger than `*out_max`, update it.
4. In `main()`, declare `int min_val, max_val;` and call `find_min_max(data, len, &min_val, &max_val);`.
5. Test with: `{5, 2, 8, 1, 9, 3}`.

### Expected Output
```
Array: 5 2 8 1 9 3
Min: 1
Max: 9
```

## Assignment 6.2: The In-Place Array Reverser

Write a function that reverses an integer array **in place** — meaning you modify the original array, not a copy.

### Function Signature
```c
void reverse_array(int *arr, int len);
```

### Requirements
1. Use two index variables: `left` starting at `0`, `right` starting at `len - 1`.
2. Swap `arr[left]` and `arr[right]`.
3. Move `left` forward, `right` backward. Stop when they meet in the middle.
4. You may use pointer arithmetic (`*(arr + left)`) or bracket notation (`arr[left]`). Both are acceptable, but try pointer arithmetic for the practice.
5. Test with: `{5, 2, 8, 1, 9, 3}`.

### Expected Output
```
Original: 5 2 8 1 9 3
Reversed: 3 9 1 8 2 5
```

## Assignment 6.3 (Bonus): The Pointer Swap

Write a function `void swap_pointers(int **a, int **b);` that swaps **where two pointers point** — not the values they point to.

### Requirements
1. After calling `swap_pointers(&p1, &p2)`, `p1` should point to `y` and `p2` should point to `x`.
2. The values of `x` and `y` themselves should remain unchanged.

```c
int x = 10, y = 20;
int *p1 = &x, *p2 = &y;
// Before: *p1 = 10, *p2 = 20
swap_pointers(&p1, &p2);
// After: *p1 = 20, *p2 = 10 (but x is still 10 and y is still 20!)
```

## Submission Checklist
- [ ] Does `find_min_max` correctly handle an array with all identical values?
- [ ] Does `reverse_array` work on both odd-length and even-length arrays?
- [ ] Compiles cleanly with `gcc -Wall -Wextra -std=c11`.
