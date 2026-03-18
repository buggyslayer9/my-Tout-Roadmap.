# 2.3 The sizeof Operator: Trust Nothing

Here is a fact about C: the size of an `int` relies entirely on your CPU architecture and compiler. On an old microcontroller, an `int` is 2 bytes. On a modern Mac, it's 4 bytes. 

**Never hardcode the number of bytes a type takes.**

Instead, we use `sizeof`.

## Using sizeof

`sizeof` is a compile-time operator. It looks like a function, but it's not. It evaluates the exact byte size of a type or variable and hardcodes it into the binary before the program even runs.

```c
#include <stdio.h>

int main(void) {
    // Note: sizeof returns a type called 'size_t'. We print it using '%zu'.
    
    printf("Size of char:      %zu bytes\n", sizeof(char));      // ALWAYS 1
    printf("Size of short:     %zu bytes\n", sizeof(short));     
    printf("Size of int:       %zu bytes\n", sizeof(int));       
    printf("Size of long:      %zu bytes\n", sizeof(long));      // 4 on Windows, 8 on Linux/Mac!
    printf("Size of long long: %zu bytes\n", sizeof(long long)); // ALWAYS 8
    
    printf("Size of a pointer: %zu bytes\n", sizeof(void *));    // 8 bytes on a 64-bit OS.
    return 0;
}
```

## Evaluating Variables and Arrays

You don't just pass types to `sizeof`; you can pass actual variables.

```c
int buffer[25]; // An array of 25 integers

// 25 integers * 4 bytes each = 100 bytes!
printf("Total memory of buffer: %zu bytes\n", sizeof(buffer));

// The veteran way to calculate how many elements are in an array:
// Total array memory divided by the memory of a single element.
size_t count = sizeof(buffer) / sizeof(buffer[0]); 
printf("Number of elements: %zu\n", count); // 25
```

## ⚠️ The Array Pointer Trap

`sizeof` only knows the size of an array if the array is declared in the **exact same scope**. If you pass an array into a function, it decays into a pointer.

```c
void process_array(int arr[]) {
    // DANGER! BUG!
    // arr looks like an array, but it's actually just an int pointer here.
    // sizeof(arr) will return 8 (size of a pointer).
    // 8 / 4 = 2. You think the array only has 2 elements!
    size_t length = sizeof(arr) / sizeof(arr[0]); 
}

int main(void) {
    int data[100];
    process_array(data);
    return 0;
}
```

Always pass the length of an array as a separate argument when calling functions. Welcome to C.
