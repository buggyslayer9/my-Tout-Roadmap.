# 6.4 Pointer Arithmetic: Walking Through Memory

When you increment a normal integer, it goes from `5` to `6`. When you increment a **pointer**, it doesn't add `1` byte. It advances by the **size of the data type it points to.**

This is how C walks through arrays at the hardware level.

## The Mechanic

```c
#include <stdio.h>

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;  // 'p' points to arr[0] (address 0x1000, for example)

    printf("%d\n", *p);       // 10 — value at arr[0]
    printf("%d\n", *(p + 1)); // 20 — value at arr[1]
    printf("%d\n", *(p + 4)); // 50 — value at arr[4]

    // When we do p + 1, the compiler calculates:
    // new_address = 0x1000 + (1 * sizeof(int))
    // new_address = 0x1000 + 4 = 0x1004
    // It jumped EXACTLY 4 bytes forward — one int's worth.
    
    return 0;
}
```

## Incrementing and Decrementing

```c
int arr[] = {10, 20, 30, 40, 50};
int *p = arr;

p++;    // p now points to arr[1] (advanced by sizeof(int) bytes)
p++;    // p now points to arr[2]
p--;    // p now points back to arr[1]
```

## Iterating an Array with Pure Pointer Arithmetic

Instead of using `arr[i]` bracket notation, you can iterate using raw pointer walking. This is what the compiler generates under the hood anyway.

```c
#include <stdio.h>

int main(void) {
    int data[] = {100, 200, 300, 400, 500};
    int len = sizeof(data) / sizeof(data[0]);
    
    // 'end' is a pointer positioned one slot PAST the last valid element.
    int *end = data + len;  
    
    // Walk from the start to the end.
    for (int *cursor = data; cursor < end; cursor++) {
        printf("%d ", *cursor);
    }
    printf("\n");
    
    return 0;
}
```

## The Unbreakable Rule

Pointer arithmetic only makes sense on **contiguous memory blocks** (arrays). If you do pointer math on a random heap pointer that doesn't sit inside an array, you are reading garbage memory and invoking undefined behavior.
