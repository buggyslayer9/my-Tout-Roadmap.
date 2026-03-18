# 8.3 Pointers to Structs: The Arrow Operator

When you pass a struct to a function, C copies the entire struct (pass by value). For a struct with 500 bytes of data, that's expensive and wasteful. The solution: pass a pointer to the struct.

## The Arrow Operator (`->`)

When you have a pointer to a struct, using the dot operator becomes ugly: `(*ptr).member`. C provides the **arrow operator** `->` as a shortcut.

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

int main(void) {
    Point p = {10, 20};
    Point *ptr = &p;
    
    // These two lines are IDENTICAL:
    printf("x = %d\n", (*ptr).x);  // Ugly: dereference, then dot.
    printf("x = %d\n", ptr->x);    // Clean: the arrow operator.
    
    // Modify through the pointer.
    ptr->x = 100;
    printf("Modified x = %d\n", p.x);  // 100!
    
    return 0;
}
```

## Passing Structs to Functions Efficiently

```c
// BAD: Copies the entire struct every call.
void print_point_bad(Point p) {
    printf("(%d, %d)\n", p.x, p.y);
}

// GOOD: Passes only an 8-byte pointer (on 64-bit systems).
// 'const' guarantees the function won't modify the original.
void print_point(const Point *p) {
    printf("(%d, %d)\n", p->x, p->y);
}
```

> **Veteran Rule:** Pass structs by pointer. Use `const` if the function should only read. This is the universal convention in C and GTK codebases.
