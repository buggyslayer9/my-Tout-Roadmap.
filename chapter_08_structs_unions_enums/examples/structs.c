/*
 * Chapter 8 — Structs, Enums, Unions
 * Compile: gcc -Wall -Wextra -std=c11 structs.c -o structs
 * Run:     ./structs
 * Check:   valgrind --leak-check=full ./structs
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// === Enum ===
typedef enum {
    PRIORITY_LOW,
    PRIORITY_MEDIUM,
    PRIORITY_HIGH
} Priority;

const char *priority_str(Priority p) {
    switch (p) {
        case PRIORITY_LOW:    return "Low";
        case PRIORITY_MEDIUM: return "Medium";
        case PRIORITY_HIGH:   return "High";
        default:              return "Unknown";
    }
}

// === Struct with typedef ===
typedef struct {
    char  title[100];
    char  author[50];
    int   year;
    bool  available;
} Book;

void print_book(const Book *b) {
    printf("  %-25s by %-15s (%d) [%s]\n",
        b->title, b->author, b->year,
        b->available ? "Available" : "Checked Out");
}

// === Struct with dynamic memory ===
typedef struct {
    char *name;
    int   age;
    Priority priority;
} Person;

Person *create_person(const char *name, int age, Priority prio) {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return NULL;
    p->name = (char *)malloc(strlen(name) + 1);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    strcpy(p->name, name);
    p->age = age;
    p->priority = prio;
    return p;
}

void free_person(Person *p) {
    if (p != NULL) {
        free(p->name);
        free(p);
    }
}

// === Union ===
typedef enum { VAL_INT, VAL_FLOAT, VAL_STRING } ValueType;

typedef struct {
    ValueType type;
    union {
        int   i;
        float f;
        char  str[20];
    } data;
} TaggedValue;

void print_value(const TaggedValue *v) {
    switch (v->type) {
        case VAL_INT:    printf("int: %d\n", v->data.i); break;
        case VAL_FLOAT:  printf("float: %.2f\n", v->data.f); break;
        case VAL_STRING: printf("string: %s\n", v->data.str); break;
    }
}

int main(void) {
    // === Book catalog ===
    printf("=== Library Catalog ===\n");
    Book library[] = {
        {"The C Programming Language", "K&R", 1978, true},
        {"Linux Programming Interface", "Kerrisk", 2010, false},
        {"Programming Rust", "Blandy", 2021, true},
    };
    int count = sizeof(library) / sizeof(library[0]);

    for (int i = 0; i < count; i++) {
        print_book(&library[i]);
    }

    // === Dynamic Person ===
    printf("\n=== Person (dynamic) ===\n");
    Person *p = create_person("Ayman", 25, PRIORITY_HIGH);
    if (p != NULL) {
        printf("  %s, age %d, priority: %s\n",
            p->name, p->age, priority_str(p->priority));
        free_person(p);
    }

    // === Tagged Union ===
    printf("\n=== Tagged Union ===\n");
    TaggedValue values[] = {
        {VAL_INT,    .data.i = 42},
        {VAL_FLOAT,  .data.f = 3.14f},
        {VAL_STRING, .data.str = "hello"},
    };
    for (int i = 0; i < 3; i++) {
        printf("  ");
        print_value(&values[i]);
    }

    return 0;
}
