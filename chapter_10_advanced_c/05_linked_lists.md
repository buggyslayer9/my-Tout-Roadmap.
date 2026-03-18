# 10.5 Linked Lists: Your First Data Structure

Arrays are fast but rigid — you can't insert or delete items efficiently. A **linked list** is a dynamic chain of individually `malloc`'d nodes connected by pointers. Each node holds data and a pointer to the next node.

## The Node Structure

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;  // Pointer to the next node in the chain.
} Node;
```

## The Core Operations

```c
// CREATE: Allocate a single node.
Node *node_new(int value) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) return NULL;
    n->data = value;
    n->next = NULL;
    return n;
}

// INSERT at front (O(1) — instant).
void list_push_front(Node **head, int value) {
    Node *new_node = node_new(value);
    new_node->next = *head;   // New node points to old head.
    *head = new_node;         // Head now points to new node.
}

// PRINT: Walk the entire chain.
void list_print(const Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// DESTROY: Free every single node.
void list_free(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}
```

## Using It

```c
int main(void) {
    Node *list = NULL;  // Start with an empty list.
    
    list_push_front(&list, 10);
    list_push_front(&list, 20);
    list_push_front(&list, 30);
    
    list_print(list);  // 30 -> 20 -> 10 -> NULL
    
    list_free(list);   // Release all memory.
    return 0;
}
```

## Why Double Pointer `Node **head`?

`list_push_front` needs to change *which node* `head` points to. Without `**`, the function only gets a copy of the pointer and can't update the caller's variable.

## Arrays vs Linked Lists

| Feature | Array | Linked List |
|---------|-------|-------------|
| Random access `[i]` | O(1) — instant | O(n) — must walk |
| Insert at front | O(n) — shift everything | O(1) — instant |
| Memory | Contiguous block | Scattered nodes |
| Cache performance | Excellent | Poor |
