# 5.2 Iterating Arrays (and calculating their length)

To process data in an array, we run a `for` loop over it, using the loop counter `i` as the array index offset.

```c
#include <stdio.h>

int main(void) {
    int speeds[] = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // We can't use a loop if we don't know the array's length.
    // How do we find the length computationally?
    
    for (int i = 0; i < 8; i++) {
        printf("Speed %d: %d\n", i, speeds[i]);
    }
    
    return 0;
}
```

## The `sizeof` Length Hack

In high level languages, arrays have a `.length` property. C does not give you this luxury. Arrays in C are just naked blocks of memory. If you want the length, you have to calculate it using raw byte sizes.

**The Formula:** `Total Bytes in Array` divided by `Bytes in a Single Element` = `Total Number of Elements`.

```c
#include <stdio.h>

int main(void) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // 1. sizeof(arr)   => Returns total bytes (e.g., 32 bytes)
    // 2. sizeof(arr[0]) => Returns bytes of the first int (e.g., 4 bytes)
    // 3. 32 / 4        => 8 elements!
    int len = sizeof(arr) / sizeof(arr[0]);  
    
    printf("Processing %d items...\n", len);

    // Now we can iterate safely!
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
    return 0;
}
```

**CRITICAL WARNING:** This `sizeof` calculation *only* works in the function where the array was originally declared. If you pass an array to a different function, it decays into a generic memory pointer, and `sizeof` will just return the size of a pointer (`8` bytes on a 64-bit system), breaking your math completely.
