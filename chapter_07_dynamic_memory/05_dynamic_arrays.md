# 7.5 Dynamic Arrays: Runtime-Sized Data

Stack-based arrays require you to know the size at compile time: `int arr[100];`. But what if you don't know how many items you'll need until the program is running?

Dynamic arrays solve this by allocating exactly the right amount of memory at runtime using `malloc`.

## The Pattern

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int count;
    printf("How many scores do you want to enter? ");
    scanf("%d", &count);
    
    // Allocate exactly 'count' integers on the heap.
    int *scores = malloc(count * sizeof(int));
    if (scores == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        return EXIT_FAILURE;
    }
    
    // Fill the array with user data.
    for (int i = 0; i < count; i++) {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    }
    
    // Calculate the average.
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    printf("Average: %.2f\n", sum / count);
    
    // Release the memory!
    free(scores);
    scores = NULL;
    
    return 0;
}
```

## Growing Arrays with `realloc`

Sometimes you don't even know the count upfront — data keeps arriving. The standard pattern is to **double the capacity** each time you run out of space.

```c
int capacity = 4;
int size = 0;
int *data = malloc(capacity * sizeof(int));

// ... inside a loop reading data ...
if (size == capacity) {
    capacity *= 2;  // Double the capacity.
    int *temp = realloc(data, capacity * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "realloc failed\n");
        free(data);
        return EXIT_FAILURE;
    }
    data = temp;
}
data[size++] = new_value;
```

This "doubling" strategy gives you O(1) amortized insertion time. It's how `std::vector` in C++ and `ArrayList` in Java work under the hood. You're building one by hand.
