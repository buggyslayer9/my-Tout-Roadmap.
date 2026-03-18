# 7.2 The Allocation Functions: malloc, calloc, realloc, free

These four functions from `<stdlib.h>` are your entire toolkit for managing heap memory.

## `malloc` — Memory ALLOCation

Reserves a block of `n` bytes on the heap. Returns a `void *` pointer. The allocated bytes contain **garbage** — whatever data was previously in those memory cells.

```c
#include <stdlib.h>

// Request space for 5 integers.
int *scores = malloc(5 * sizeof(int));
// scores[0] through scores[4] contain random garbage until you write to them!
```

## `calloc` — Clear ALLOCation

Like `malloc`, but takes two arguments (count, size) and **zeros out every byte**. Slower than `malloc` because of the zeroing step, but safer for initializing data structures.

```c
// Request space for 5 integers, all initialized to 0.
int *clean_scores = calloc(5, sizeof(int));
// clean_scores[0] through clean_scores[4] are guaranteed to be 0.
```

## `realloc` — REsize ALLOCation

Takes an existing heap block and resizes it. If there's room to extend in place, great. If not, `realloc` allocates a completely new block, copies the old data into it, frees the old block, and returns the new address.

```c
// Start with 5 ints.
int *data = malloc(5 * sizeof(int));

// We need 10 now. Resize!
int *temp = realloc(data, 10 * sizeof(int));
if (temp != NULL) {
    data = temp;  // Only update if realloc succeeded!
}
```

> **⚠️ The `realloc` Trap:** NEVER write `data = realloc(data, new_size);`. If `realloc` fails and returns `NULL`, you just overwrote your only pointer to the original block. That memory is now lost forever — a guaranteed memory leak.

## `free` — Release Memory

Returns heap memory back to the operating system. After `free()`, the pointer becomes a **dangling pointer** — it still holds the old address, but that address is no longer yours.

```c
free(data);
data = NULL;  // ALWAYS do this. Prevents accidental use-after-free.
```

## The Lifecycle Summary

```
1. malloc/calloc → You get memory.  YOU OWN IT.
2. Use it.
3. realloc if needed.
4. free() → Give it back.  YOU NO LONGER OWN IT.
5. Set pointer = NULL.
```

Every `malloc` **must** have a matching `free`. No exceptions. No excuses.
