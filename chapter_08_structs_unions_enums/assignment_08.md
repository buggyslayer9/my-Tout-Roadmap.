# Assignment 8: The Library Catalog System

You will architect a miniature database in pure C using structs, enums, typedef, and dynamic memory. This is the final stepping stone before GTK programming, where every object follows this same pattern.

## Assignment 8.1: The Book Catalog

Build a complete book management system.

### The Data Model
```c
typedef enum { AVAILABLE, CHECKED_OUT } BookStatus;

typedef struct {
    char       title[100];
    char       author[50];
    int        year;
    BookStatus status;
} Book;
```

### Required Functions
1. `void book_print(const Book *b);`
   — Prints a single book's info in a formatted row. Use the arrow operator `->`.

2. `void catalog_print_all(const Book *books, int count);`
   — Prints a header row, then iterates through all books calling `book_print`.

3. `void catalog_print_available(const Book *books, int count);`
   — Prints only the books where `status == AVAILABLE`.

4. `void catalog_search_by_author(const Book *books, int count, const char *author);`
   — Uses `strcmp()` to find and print all books by a specific author.

### The `main()` Driver
1. Create a stack-allocated array of 5 `Book` structs with hardcoded test data.
2. Call `catalog_print_all()`.
3. Call `catalog_print_available()`.
4. Call `catalog_search_by_author()` with one of your test authors.

### Example Output
```
=== Full Catalog ===
TITLE                 AUTHOR              YEAR  STATUS
------------------------------------------------------
C Programming         Dennis Ritchie      1978  Available
The Art of Unix       Eric Raymond        2003  Available
Design Patterns       Gang of Four        1994  Checked Out
GTK4 Development      GNOME Team          2021  Available
Clean Code            Robert Martin       2008  Checked Out

=== Available Books ===
C Programming         Dennis Ritchie      1978  Available
The Art of Unix       Eric Raymond        2003  Available
GTK4 Development      GNOME Team          2021  Available

=== Search: "GNOME Team" ===
GTK4 Development      GNOME Team          2021  Available
```

## Assignment 8.2 (Bonus): Heap-Allocated Catalog

Modify your program so that:
1. The user enters how many books they want to add.
2. You `malloc` exactly that many `Book` structs.
3. You read each book's data from `stdin` using `fgets`.
4. Print, search, then `free` everything.

## Checklist
- [ ] All functions take `const Book *` (pointer, not copy).
- [ ] `BookStatus` is an enum, not a raw int.
- [ ] Compiles with `-Wall -Wextra -std=c11`.
- [ ] If you did Bonus 8.2, Valgrind reports zero leaks.
