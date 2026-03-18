# 6.2 The Two Pointer Operators: & and *

These two symbols are the entire vocabulary of pointer manipulation. Master them and you master memory.

## `&` — The Address-Of Operator

The ampersand `&` extracts the physical memory address of any variable. It answers the question: "Where in RAM does this variable physically reside?"

```c
int health = 100;
printf("health lives at address: %p\n", (void *)&health);
// Output: health lives at address: 0x7ffd92a4c3e8
```

## `*` — The Dereference Operator

The asterisk `*` does the opposite. Given a pointer that holds an address, `*` follows that address and retrieves — or modifies — the value stored there.

```c
int health = 100;
int *ptr = &health;  // ptr now holds health's address.

// READING: Follow the address, read the value.
printf("Value at ptr: %d\n", *ptr); // 100

// WRITING: Follow the address, overwrite the value.
*ptr = 9999;
printf("health is now: %d\n", health); // 9999! We changed it through the pointer!
```

## The Danger of Dereferencing Garbage

If a pointer doesn't point to valid memory and you dereference it, your program will crash with the infamous `Segmentation fault (core dumped)`.

```c
int *bad_ptr;       // UNINITIALIZED! Contains random garbage address.
*bad_ptr = 42;      // 💥 SEGFAULT — you just wrote to a random memory location.
```

> **Veteran Rule:** Always initialize your pointers. If you don't have a valid address yet, set the pointer to `NULL`. Then check for `NULL` before dereferencing. This single habit will prevent 90% of pointer-related crashes.

```c
int *safe_ptr = NULL;  // Safe default.

if (safe_ptr != NULL) {
    *safe_ptr = 42;    // Only runs if we actually assigned a real address.
}
```
