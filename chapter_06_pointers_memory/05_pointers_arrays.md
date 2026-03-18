# 6.5 The Array-Pointer Duality

Here is one of the deepest truths in C: **An array name is essentially a constant pointer to its first element.** When you write `arr`, the compiler interprets it as `&arr[0]`.

## The Equivalence

```c
int arr[] = {1, 2, 3};
int *p = arr;  // This is exactly equivalent to: int *p = &arr[0];

// All four of these expressions produce the EXACT same value:
arr[2]       // Bracket notation on the array name.
*(arr + 2)   // Pointer arithmetic on the array name.
*(p + 2)     // Pointer arithmetic on the pointer copy.
p[2]         // Bracket notation on the pointer copy!
```

Yes, you read that right. You can use `[]` on a pointer, and you can use `*` arithmetic on an array name. The compiler treats them identically.

## The One Key Difference

An array name is a **constant** pointer. You cannot reassign it.

```c
int arr[] = {1, 2, 3};
int *p = arr;

p++;     // ✅ Legal. p now points to arr[1].
// arr++;  // ❌ COMPILE ERROR! arr is a constant. You cannot move it.
```

Think of `arr` as a permanent street sign bolted to the ground. Think of `p` as a GPS device you can freely point anywhere.

## Why This Matters for Functions

When you pass an array to a function, C actually passes a **pointer to the first element**. Inside that function, `sizeof(arr)` returns the size of a pointer (8 bytes on 64-bit), not the total array size. This is "array decay" — the array loses its length metadata the instant it crosses a function boundary.

```c
void process(int arr[]) {
    // sizeof(arr) here is 8, NOT the total array size!
    // You MUST pass the length separately.
}
```
