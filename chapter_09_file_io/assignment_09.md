# Assignment 9: The Persistent Grade Book

This is where everything clicks together. You will combine structs, dynamic memory, file I/O, and menu-driven control flow into a single application that **persists its data** across runs.

## Task

Build a student grade book that saves and loads records from a binary file. When you run the program, it loads existing data. When you exit, it saves automatically.

## The Data Model

```c
typedef struct {
    char   name[50];
    double grade;
} Student;
```

## Required Menu

```
=== Student Grade Book ===
1. Add Student
2. View All Students
3. Save to File
4. Exit (auto-saves)
Enter choice:
```

## Requirements

1. **Data Storage**: Use a dynamically allocated array (`Student *`) that grows with `realloc` as new students are added.
2. **Add Student**: Prompt for name (use `fgets`) and grade (use `fgets` + `strtod`). Append to the dynamic array.
3. **View All**: Print all students in a formatted table.
4. **Save**: Write the number of students (`int`) followed by all `Student` structs to `gradebook.bin` using `fwrite`.
5. **Load on Startup**: If `gradebook.bin` exists, read the student count, then `malloc` and `fread` all records. If it doesn't exist, start with an empty array.
6. **Auto-Save on Exit**: When the user picks "Exit", save before terminating.
7. **Memory Cleanup**: `free` the dynamic array before exiting. Verify with Valgrind.

## File Format (Binary)

```
[4 bytes: int count]
[sizeof(Student) * count: Student array data]
```

## Example Session

```
(No gradebook.bin found — starting fresh.)

=== Student Grade Book ===
1. Add Student
2. View All Students
3. Save to File
4. Exit (auto-saves)
Choice: 1
Name: Alice
Grade: 95.5
Student added!

Choice: 1
Name: Bob
Grade: 78.0
Student added!

Choice: 2
NAME           GRADE
---------------------
Alice          95.50
Bob            78.00

Choice: 4
Saving 2 students to gradebook.bin...
Goodbye!
```

## Checklist
- [ ] Run the program, add 3 students, exit. Run again — do your students load?
- [ ] Valgrind reports zero leaks?
- [ ] Does `fopen("gradebook.bin", "rb")` return `NULL` gracefully on first run?
