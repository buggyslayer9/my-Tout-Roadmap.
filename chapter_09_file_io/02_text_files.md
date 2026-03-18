# 9.2 Text File Operations

Text files store human-readable characters. You read and write them with `fprintf` and `fgets` — the same functions you already know for `printf` and `stdin`, but pointed at a file handle instead.

## Writing to a Text File

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("log.txt", "w");
    if (fp == NULL) { perror("fopen"); return 1; }
    
    // fprintf works exactly like printf, but writes to a file.
    fprintf(fp, "Application started.\n");
    fprintf(fp, "User: %s, Age: %d\n", "Bugslayer", 30);
    fprintf(fp, "Status: ALL SYSTEMS NOMINAL.\n");
    
    fclose(fp);
    printf("Log written successfully.\n");
    return 0;
}
```

## Reading a Text File Line by Line

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("log.txt", "r");
    if (fp == NULL) { perror("fopen"); return 1; }
    
    char line[256];
    
    // fgets reads one line at a time, up to sizeof(line) - 1 characters.
    // It returns NULL when it reaches the end of the file (EOF).
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf(">> %s", line);  // line already contains the \n
    }
    
    fclose(fp);
    return 0;
}
```

## Reading Formatted Data: `fscanf`

If the file has a known, rigid structure, you can parse it directly:

```c
// data.csv contains: "Alice,20,3.9"
char name[50];
int age;
double gpa;

fscanf(fp, "%49[^,],%d,%lf", name, &age, &gpa);
// %49[^,] reads up to 49 chars, stopping at a comma.
```

> **Veteran Tip:** For anything more complex than trivial formats, read the whole line with `fgets` and parse it yourself with `sscanf` or `strtok`. Never trust `fscanf` on messy real-world data.
