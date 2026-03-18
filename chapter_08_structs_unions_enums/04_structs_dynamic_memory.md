# 8.4 Structs with Dynamic Memory

When a struct member is a `char *` pointer instead of a `char[50]` fixed buffer, you get flexibility — but you also get responsibility. You must `malloc` the string, and you must `free` it in the correct order.

## The Constructor/Destructor Pattern

This is the fundamental C pattern for object lifecycle management. GTK follows this exact architecture.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;   // Dynamically allocated string (not a fixed buffer!)
    int   age;
} Person;

// "Constructor" — allocates the struct AND its inner string.
Person *person_new(const char *name, int age) {
    Person *p = malloc(sizeof(Person));
    if (p == NULL) return NULL;
    
    p->name = malloc(strlen(name) + 1);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    
    strcpy(p->name, name);
    p->age = age;
    return p;
}

// "Destructor" — frees the inner string FIRST, then the struct.
void person_free(Person *p) {
    if (p == NULL) return;
    free(p->name);   // Free inner allocation first!
    free(p);         // Then free the struct itself.
}

int main(void) {
    Person *dev = person_new("Bugslayer", 30);
    if (dev == NULL) return EXIT_FAILURE;
    
    printf("Name: %s, Age: %d\n", dev->name, dev->age);
    
    person_free(dev);
    dev = NULL;
    
    return 0;
}
```

## The Deallocation Order Rule

If a struct contains pointers to other dynamically allocated data, you must **free the inner allocations before the outer struct**. If you `free(p)` first, the `p->name` pointer becomes inaccessible and that inner memory is leaked forever.

```
// CORRECT ORDER:
free(p->name);  // 1. Release inner data.
free(p);        // 2. Release the container.

// WRONG ORDER:
free(p);        // 💀 p is gone! p->name is now unreachable. LEAK!
free(p->name);  // 💀 Undefined behavior — p no longer exists.
```
