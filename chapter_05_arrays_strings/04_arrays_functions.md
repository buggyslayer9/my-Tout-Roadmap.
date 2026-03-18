# 5.4 Passing Arrays to Functions

In Chapter 4, you learned about "Pass by Value." When you hand a variable to a function, the function receives a protective photocopy of the variable.

**Arrays break this rule.** 

When you pass an array to a function, C refuses to photocopy it. Photocopying a 1GB array of video data just to pass it to a function would instantly crash your machine. 

Instead, C passes **a raw memory pointer** pointing directly to the exact start of your array. This is called "Array Decay".

## The Syntax AND The Catch

Because the function only receives a raw pointer to the first item (`data[0]`), the function has absolutely no idea how long the array is. You must pass the length as a secondary parameter!

```c
#include <stdio.h>

// 1. Notice the 'int arr[]' syntax. This declares an array parameter.
// 2. 'len' is manually passed in because the arr pointer has no length data.
void mutate_and_print(int arr[], int len) {
    
    for (int i = 0; i < len; i++) {
        // Warning: Because we hold a live memory pointer, 
        // THIS MODIFIES THE ORIGINAL ARRAY IN MAIN(). No photocopies!
        arr[i] = arr[i] * 2; 
        
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    // We declare the array. Here in main, sizeof works correctly.
    int data[] = {1, 2, 3, 4, 5};
    int total_length = sizeof(data) / sizeof(data[0]);
    
    // We hand over the array, AND the pre-calculated length.
    mutate_and_print(data, total_length);
    
    return 0;
}
```

## The Summary Rule
If your function takes an array, its signature should always look something like this:
`void process_data(int array_name[], size_t length)`

*(Note: `size_t` is the standard C type for lengths and sizes; we'll discuss it deeply later. Use `int` for now).*
