# 9.3 Binary Files: Raw Memory Dumps

Text files store human-readable characters. Binary files store **raw memory bytes** — the exact pattern of 1s and 0s that represent your data in RAM. They are compact, fast, and perfect for saving/loading structs.

## Writing a Struct to a Binary File

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char   name[50];
    int    age;
    double gpa;
} Student;

int main(void) {
    Student s = {"Alice", 20, 3.9};
    
    FILE *fp = fopen("students.bin", "wb");  // "wb" = Write Binary
    if (fp == NULL) { perror("fopen"); return 1; }
    
    // fwrite dumps the exact bytes of the struct to disk.
    // Args: pointer to data, size of one item, number of items, file handle.
    fwrite(&s, sizeof(Student), 1, fp);
    
    fclose(fp);
    return 0;
}
```

## Reading a Struct from a Binary File

```c
int main(void) {
    Student loaded;
    
    FILE *fp = fopen("students.bin", "rb");  // "rb" = Read Binary
    if (fp == NULL) { perror("fopen"); return 1; }
    
    // fread fills the struct with the raw bytes from disk.
    fread(&loaded, sizeof(Student), 1, fp);
    
    fclose(fp);
    printf("Loaded: %s, Age: %d, GPA: %.1f\n", loaded.name, loaded.age, loaded.gpa);
    return 0;
}
```

## Writing and Reading Arrays

```c
Student roster[3] = {
    {"Alice", 20, 3.9},
    {"Bob",   21, 3.5},
    {"Carol", 22, 3.7}
};

// Write all 3 at once.
fwrite(roster, sizeof(Student), 3, fp);

// Read all 3 back.
Student loaded[3];
fread(loaded, sizeof(Student), 3, fp);
```

## ⚠️ Binary File Warnings

1. **Not portable.** A binary file written on a 64-bit Linux machine may not load correctly on a 32-bit ARM system because `sizeof(int)` and struct padding may differ.
2. **No dynamic pointers.** If your struct contains `char *name` (a pointer), `fwrite` saves the pointer address — not the string data. The pointer will be meaningless when loaded. Always use fixed-size arrays (`char name[50]`) for binary I/O.
