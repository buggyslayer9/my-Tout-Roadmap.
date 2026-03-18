# 6.7 Pointer to Pointer (Double Pointer `**`)

If a pointer holds the address of a variable, a **double pointer** holds the address of a pointer. It's one more level of indirection.

This isn't academic theory. You *need* double pointers the moment you want a function to modify which address a pointer is aimed at.

## The Memory Chain

```c
int x = 10;
int *p = &x;      // p holds x's address
int **pp = &p;     // pp holds p's address

printf("%d\n", x);      // 10
printf("%d\n", *p);     // 10  (follow one arrow)
printf("%d\n", **pp);   // 10  (follow two arrows)
```

Visualization:
```
pp ──→ p ──→ x ──→ [10]
```

## Real Use Case 1: Modifying a Pointer Inside a Function

Remember the rule: to modify a variable through a function, you pass a pointer to it. So to modify a *pointer* through a function, you pass a *pointer to the pointer*.

```c
#include <stdio.h>
#include <stdlib.h>

void allocate_buffer(int **ptr, int count) {
    // *ptr dereferences the double pointer to get the ORIGINAL pointer in main.
    // We then assign it to the freshly malloced memory.
    *ptr = malloc(count * sizeof(int));
}

int main(void) {
    int *data = NULL;
    
    allocate_buffer(&data, 100);  // Pass the ADDRESS of our pointer.
    
    // 'data' now points to 100 ints of heap memory!
    if (data != NULL) {
        data[0] = 42;
        printf("First element: %d\n", data[0]);
        free(data);
    }
    
    return 0;
}
```

## Real Use Case 2: `char **argv` (You Already Know This One)

The `main` function's argument list is a double pointer in disguise:

```c
int main(int argc, char **argv) {
    // argv is a pointer to an array of char pointers (strings).
    // argv[0] = pointer to the program name string.
    // argv[1] = pointer to the first command-line argument string.
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] = %s\n", i, argv[i]);
    }
    return 0;
}
```

## Real Use Case 3: Linked List Head Modification

When you insert a new node at the front of a linked list, the head pointer itself must change. You need `**` to do this from inside a function.

```c
void push_front(Node **head, int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = *head;  // Link new node to old head.
    *head = new_node;        // Update the caller's head pointer!
}
```

## The Golden Pattern

| You want to modify... | Pass as... |
|----------------------|------------|
| An `int` value | `int *` |
| An `int *` pointer | `int **` |
| An `int **` double pointer | `int ***` (rare — rethink your design) |

The rule is simple: to modify something through a function, pass a pointer **one level deeper** than what you want to modify.
