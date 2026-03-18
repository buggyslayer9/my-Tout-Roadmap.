# 6.6 The NULL Pointer: The Safety Net

An uninitialized pointer contains a garbage address. Dereferencing it is like driving blindfolded to a random location and kicking the front door open. You will crash.

`NULL` is C's way of saying "this pointer intentionally goes nowhere." It is defined as `((void *)0)` — address zero, which the operating system reserves as always invalid. If you dereference `NULL`, the OS immediately kills your process with a clean `Segmentation fault`, instead of silently corrupting random data.

## Always Initialize, Always Check

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = NULL;  // Safe. Explicitly says "I point to nothing yet."
    
    // ALWAYS check before using.
    if (p != NULL) {
        printf("Value: %d\n", *p);
    } else {
        printf("Pointer is not assigned yet.\n");
    }
    
    return 0;
}
```

## The Three Sacred NULL Patterns

### Pattern 1: Check `malloc` Returns
`malloc` returns `NULL` when the system runs out of memory. If you don't check, you will dereference `NULL` and crash.

```c
int *buffer = malloc(1000 * sizeof(int));
if (buffer == NULL) {
    fprintf(stderr, "FATAL: Out of memory!\n");
    exit(EXIT_FAILURE);
}
```

### Pattern 2: NULL After `free`
After you `free()` a block of memory, the pointer still holds the old, now-invalid address. This creates a "dangling pointer." Setting it to `NULL` immediately prevents accidental use-after-free bugs.

```c
free(buffer);
buffer = NULL;  // Now any accidental *buffer will segfault cleanly
                // instead of silently corrupting freed memory.
```

### Pattern 3: NULL as a Sentinel / End Marker
Linked lists use `NULL` to mark the final node. Function parameters use `NULL` to indicate "this argument is optional."

```c
// Walk a linked list until we hit the end.
Node *current = head;
while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
}
```

## The Classic Mistake

```c
int *p;          // 💀 DANGEROUS! Contains random garbage address!
int *q = NULL;   // ✅ SAFE! Explicitly null.
```

An uninitialized pointer is **not** automatically `NULL`. It contains whatever random bytes were already sitting in that memory register. This is one of the most common sources of intermittent, unreproducible crashes in C programs.
