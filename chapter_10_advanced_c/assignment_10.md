# Assignment 10: The Linked List Gauntlet

This is the capstone of Phase 1. You will build a fully operational singly linked list from scratch — combining every concept from Chapters 1–10: structs, pointers, double pointers, dynamic memory, function design, and memory safety.

## Task

Implement a singly linked list library with the following operations:

### Required Functions

```c
// Node structure
typedef struct Node {
    int          data;
    struct Node *next;
} Node;

// 1. Create a new node on the heap.
Node *node_new(int value);

// 2. Insert a value at the FRONT of the list. O(1).
void list_push_front(Node **head, int value);

// 3. Insert a value at the BACK of the list. O(n).
void list_push_back(Node **head, int value);

// 4. Delete the FIRST node containing the given value.
//    Handle: empty list, delete head, delete middle, delete tail, value not found.
void list_delete_value(Node **head, int value);

// 5. Print the entire list in "30 -> 20 -> 10 -> NULL" format.
void list_print(const Node *head);

// 6. Free ALL nodes in the list.
void list_free(Node *head);
```

### The `main()` Driver

Demonstrate your library by:
1. Pushing `10`, `20`, `30` to the front. Print the list.
2. Pushing `40`, `50` to the back. Print the list.
3. Deleting `20` (a middle node). Print.
4. Deleting `30` (the head). Print.
5. Deleting `999` (not found — handle gracefully). Print.
6. Free the entire list.

### Expected Output

```
Push front 10, 20, 30:
30 -> 20 -> 10 -> NULL

Push back 40, 50:
30 -> 20 -> 10 -> 40 -> 50 -> NULL

Delete 20:
30 -> 10 -> 40 -> 50 -> NULL

Delete 30 (head):
10 -> 40 -> 50 -> NULL

Delete 999 (not found):
10 -> 40 -> 50 -> NULL

Freeing all nodes...
```

## Validation

```bash
gcc -g -Wall -Wextra -std=c11 assign10.c -o assign10
valgrind --leak-check=full ./assign10
```

### Checklist
- [ ] Does `list_delete_value` correctly handle deleting the head node?
- [ ] Does `list_delete_value` handle "value not found" without crashing?
- [ ] Does `list_push_back` work on an empty list (`*head == NULL`)?
- [ ] Valgrind reports: **0 bytes lost, 0 errors**.

Complete this assignment and you have graduated from Phase 1. You are now ready for GTK4.
