/*
 * Chapter 10 — Advanced C: Function Pointers, Macros, Linked List
 * Compile: gcc -Wall -Wextra -std=c11 advanced_c.c -o advanced_c
 * Run:     ./advanced_c
 * Check:   valgrind --leak-check=full ./advanced_c
 */
#include <stdio.h>
#include <stdlib.h>

// === Macros ===
#define MAX(a, b)     ((a) > (b) ? (a) : (b))
#define ARRAY_LEN(a)  (sizeof(a) / sizeof(a[0]))

// === Function Pointers ===
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// === Linked List ===
typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

void push_front(Node **head, int value) {
    Node *new_node = create_node(value);
    new_node->next = *head;
    *head = new_node;
}

void push_back(Node **head, int value) {
    Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    // === Macros ===
    printf("=== Macros ===\n");
    int data[] = {5, 2, 8, 1, 9};
    printf("Array length: %zu\n", ARRAY_LEN(data));
    printf("MAX(7, 3) = %d\n", MAX(7, 3));

    // === Function Pointers ===
    printf("\n=== Function Pointers ===\n");
    int (*ops[])(int, int) = {add, sub, mul};
    const char *names[] = {"add", "sub", "mul"};

    for (int i = 0; i < 3; i++) {
        printf("%s(10, 5) = %d\n", names[i], ops[i](10, 5));
    }

    // === Linked List ===
    printf("\n=== Linked List ===\n");
    Node *list = NULL;

    push_back(&list, 10);
    push_back(&list, 20);
    push_back(&list, 30);
    push_front(&list, 5);

    printf("List: ");
    print_list(list);

    free_list(list);
    printf("List freed. Run with valgrind to verify!\n");

    return EXIT_SUCCESS;
}
