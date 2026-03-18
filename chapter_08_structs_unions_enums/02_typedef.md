# 8.2 Typedef: Naming Your Types

Writing `struct Student` every time you need a student variable is verbose. `typedef` lets you create an alias — a shorthand name — for any type.

## The Pattern

```c
// Without typedef: verbose.
struct Point {
    float x;
    float y;
};
struct Point p1 = {3.0f, 4.0f};  // Must write "struct Point" every time.

// With typedef: clean.
typedef struct {
    float x;
    float y;
} Point;

Point p2 = {3.0f, 4.0f};  // Just "Point". Much better.
```

## Self-Referencing Structs (Linked Lists)

If a struct needs to point to another instance of itself (like a linked list node), you need to give the struct a tag name so it can reference itself inside its own definition:

```c
typedef struct Node {
    int data;
    struct Node *next;  // Must use "struct Node" here, not just "Node".
} Node;
```

## Typedef for Function Pointers

`typedef` is also essential for making function pointer syntax readable:

```c
// Without typedef: unreadable nightmare.
void (*callback)(int, int);

// With typedef: human-readable.
typedef void (*Callback)(int, int);
Callback on_click = my_handler_function;
```

GTK uses this pattern extensively. Every signal handler you connect is a typedef'd function pointer.
