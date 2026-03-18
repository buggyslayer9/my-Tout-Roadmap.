# 8.7 Unions: Shared Memory Blocks

A `union` looks like a struct, but with one critical twist: **all members share the same memory location.** Only one member can hold a valid value at any given time. Writing to one member overwrites all others.

## The Concept

```c
#include <stdio.h>

union Value {
    int   i;
    float f;
    char  str[20];
};

int main(void) {
    union Value v;
    
    v.i = 42;
    printf("Integer: %d\n", v.i);  // 42 — valid.
    
    v.f = 3.14f;  // Writing to f DESTROYS the int value!
    printf("Float: %.2f\n", v.f);  // 3.14 — valid.
    printf("Integer: %d\n", v.i);  // Garbage! The bytes now represent 3.14.
    
    return 0;
}
```

## Why Do Unions Exist?

**Memory efficiency.** A union is only as large as its biggest member. If you have a data structure that can be an int *or* a float *or* a string, but never more than one at the same time, a union saves memory by reusing the same bytes.

## The Tagged Union Pattern

In practice, you almost always pair a union with an enum "tag" that tracks which member is currently valid:

```c
typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING } ValueType;

typedef struct {
    ValueType type;     // The "tag" tells us which union member is valid.
    union {
        int   i;
        float f;
        char  str[50];
    } data;
} TaggedValue;

void print_value(const TaggedValue *v) {
    switch (v->type) {
        case TYPE_INT:    printf("%d\n",   v->data.i);   break;
        case TYPE_FLOAT:  printf("%.2f\n", v->data.f);   break;
        case TYPE_STRING: printf("%s\n",   v->data.str); break;
    }
}
```

This tagged union pattern is **the C equivalent of Rust's `enum` with data** or TypeScript's discriminated union. It's used in parsers, serializers, and event systems.
