# 5.7 String Parsing Basics

Strings become much more useful once you stop treating them as only text to print.

In real programs, strings often need to be **parsed** into useful pieces.

Examples:

- splitting first and last name
- reading comma-separated values
- extracting commands from input
- checking file extensions

## What Parsing Means

Parsing means taking raw text and turning it into structured meaning.

Example:

```text
add milk 2
```

You might want to interpret that as:

- command: `add`
- item: `milk`
- quantity: `2`

## Why This Matters

Parsing is one of the first places where beginner code starts to feel like real software.

It teaches:

- careful iteration over strings
- separators and delimiters
- data cleaning
- validation

## A Simple Example

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "apple,banana,grape";
    char *token = strtok(text, ",");

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
```

This shows a common beginner approach: split a string using a delimiter.

## Important Caution

`strtok()` modifies the original string.

That means:

- do not use it on string literals
- be careful if you still need the original text unchanged

This is a classic C lesson: useful tools often come with rules.

## Beginner Parsing Questions

When parsing a string, ask:

- what separates one field from the next?
- what counts as valid input?
- what should happen if a field is missing?

These questions make parsing code much stronger.

## Learning Check

- Can I explain what string parsing means?
- Can I split a simple comma-separated string?
- Can I describe one risk of using `strtok()`?

## Recommended Follow-Up

Parse a line like:

```text
name:Alice,age:22,city:Cairo
```

Then print each key-value pair clearly.
