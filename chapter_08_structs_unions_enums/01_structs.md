# 8.1 Structs: Building Custom Data Types

Up to this point, every piece of data in your programs has been a primitive: a lone `int`, a solitary `double`, a naked `char` array. But real-world data is rarely a single number. A student has a name, an age, a GPA, and an ID — all bound together as one logical entity.

A **struct** (short for "structure") lets you bundle multiple related variables of different types into a single custom data type.

## Declaring and Using a Struct

```c
#include <stdio.h>
#include <string.h>

// 1. Define the blueprint. No memory is allocated yet.
struct Student {
    char   name[50];
    int    age;
    double gpa;
    int    id;
};

int main(void) {
    // 2. Create an instance from the blueprint.
    struct Student s1;
    
    // 3. Populate using the dot (.) operator.
    strcpy(s1.name, "Alice");  // Can't use = for char arrays, remember?
    s1.age = 20;
    s1.gpa = 3.8;
    s1.id  = 1001;
    
    // 4. Inline initialization (much cleaner).
    struct Student s2 = {"Bob", 22, 3.5, 1002};
    
    // 5. Access members with dot notation.
    printf("Name: %s, GPA: %.2f\n", s2.name, s2.gpa);
    
    return 0;
}
```

## Why Structs Are Critical

Structs are C's only mechanism for creating complex data types. Without them, you'd need parallel arrays for every attribute — `names[i]`, `ages[i]`, `gpas[i]` — which is unmaintainable chaos.

In GTK, every single widget is represented as a struct behind the scenes. When you create a `GtkWindow`, you are allocating a struct. When you set a button's label, you are modifying a struct member through a pointer.

## Designated Initializers (C99+)

You can initialize fields by name for clarity:
```c
struct Student s3 = {
    .name = "Carol",
    .age  = 21,
    .gpa  = 3.9,
    .id   = 1003
};
```
This is the professional style. It makes your code self-documenting and resistant to field reordering.
