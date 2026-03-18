# 6.3 Pass by Reference (Simulated with Pointers)

In Chapter 4, you learned that C passes arguments **by value** — the function gets a photocopy, and the original variable in the caller is untouchable.

Pointers destroy that wall. By passing the **address** of a variable (instead of its value), the function can reach directly into the caller's memory and modify the original data. This technique is called "pass by reference" (even though, technically, C is still passing the pointer's value — which happens to be an address).

## The Classic: Swap Two Variables

This is the textbook pointer exercise. Without pointers, it is *literally impossible* to write a working swap function in C.

```c
#include <stdio.h>

// Notice: the parameters are int *a and int *b (pointers!)
void swap(int *a, int *b) {
    int temp = *a;   // Save the value at address 'a'
    *a = *b;         // Overwrite the value at 'a' with the value at 'b'
    *b = temp;       // Put the saved value into 'b'
}

int main(void) {
    int x = 5, y = 10;
    
    printf("Before: x=%d, y=%d\n", x, y);
    
    // We pass the ADDRESSES of x and y using &
    swap(&x, &y);
    
    printf("After:  x=%d, y=%d\n", x, y); // x=10, y=5. They swapped!
    return 0;
}
```

## Returning Multiple Values

In C, a function can only `return` a single value. What if you need to return three? Use pointer parameters as "output slots."

```c
void get_screen_dimensions(int *width, int *height) {
    // Write the results directly into the caller's variables.
    *width = 1920;
    *height = 1080;
}

int main(void) {
    int w, h;
    get_screen_dimensions(&w, &h); // w and h are now populated!
    printf("Screen: %dx%d\n", w, h);
    return 0;
}
```

This pattern is used **everywhere** in GTK. Functions like `gtk_window_get_default_size()` take output pointer parameters to hand you back multiple pieces of data.
