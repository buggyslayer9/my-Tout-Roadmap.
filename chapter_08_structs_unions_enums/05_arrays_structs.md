# 8.5 Arrays of Structs

Combining arrays and structs is how you build tables, databases, and UI lists in C. An array of structs is essentially a database table where each row is a struct instance.

## Stack-Allocated Array of Structs

```c
#include <stdio.h>

typedef struct {
    char   name[50];
    int    age;
    double gpa;
    int    id;
} Student;

int main(void) {
    Student roster[3] = {
        {"Alice", 20, 3.9, 1001},
        {"Bob",   21, 3.5, 1002},
        {"Carol", 22, 3.7, 1003}
    };
    
    // Print a formatted table.
    printf("%-12s %4s %5s %6s\n", "NAME", "AGE", "GPA", "ID");
    printf("-------------------------------------\n");
    
    for (int i = 0; i < 3; i++) {
        printf("%-12s %4d %5.1f %6d\n",
               roster[i].name,
               roster[i].age,
               roster[i].gpa,
               roster[i].id);
    }
    
    return 0;
}
```

## Heap-Allocated Array of Structs

When you don't know the count at compile time:

```c
int count;
printf("How many students? ");
scanf("%d", &count);

Student *students = malloc(count * sizeof(Student));
if (students == NULL) {
    fprintf(stderr, "Allocation failed!\n");
    return EXIT_FAILURE;
}

// Access exactly like a normal array!
strcpy(students[0].name, "Dave");
students[0].age = 19;

// Don't forget to free!
free(students);
```

## Passing to Functions

```c
void print_roster(const Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s — GPA: %.1f\n", students[i].name, students[i].gpa);
    }
}
```
