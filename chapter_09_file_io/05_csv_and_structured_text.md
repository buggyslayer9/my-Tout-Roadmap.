# 9.5 CSV and Structured Text Files

Many useful programs do not save raw binary data first.

They save structured text.

One of the simplest and most common formats is **CSV**:

- comma-separated values

Examples:

- task exports
- grade records
- product lists
- small datasets

## Why CSV Matters

CSV is useful because it is:

- human-readable
- easy to inspect
- easy to generate
- supported by many tools

For beginner projects, it is often a better first storage format than a custom binary format.

## Example File

```text
id,title,done
1,Learn C,0
2,Read about pointers,1
3,Build a project,0
```

Each line represents a record.

## Writing CSV

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("tasks.csv", "w");
    if (file == NULL) {
        return 1;
    }

    fprintf(file, "id,title,done\n");
    fprintf(file, "1,Learn C,0\n");
    fprintf(file, "2,Read about pointers,1\n");

    fclose(file);
    return 0;
}
```

This is much easier to inspect than a binary file.

## Reading CSV

For simple beginner files, you can often read line by line:

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("tasks.csv", "r");
    char line[256];

    if (file == NULL) {
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
```

Later, you can split fields more carefully.

## Important Beginner Limitation

Real CSV can become tricky when:

- fields contain commas
- fields contain quotes
- fields span lines

That is okay.

As a learner, it is enough to start with simple CSV files under your control.

## Why Structured Text Helps Learning

Structured text teaches:

- data format design
- reading and writing records
- debugging saved output
- thinking about interoperability

It is a great bridge between tiny toy files and real application data.

## Learning Check

- Can I explain why CSV is useful for small projects?
- Can I write a CSV header and a few data rows?
- Can I read a text file line by line and inspect the contents?

## Recommended Follow-Up

Save one of your earlier projects to a CSV file instead of only printing to the terminal.
