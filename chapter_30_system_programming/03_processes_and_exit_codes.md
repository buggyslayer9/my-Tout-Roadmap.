# 30.3 Processes and Exit Codes

If you want to understand system programming, you need to understand **processes** clearly.

A process is a running program with its own execution state and resources.

This lesson gives you a practical foundation before deeper topics like `fork`, `exec`, and pipes.

## What A Process Has

A process typically has:

- its own virtual memory space
- a process ID
- open file descriptors
- environment variables
- an exit status

That means a process is more than just “the code is running.”

## Process Creation

At a high level:

- a program exists as a file on disk
- the operating system loads it
- the program begins execution as a process

Later chapters go deeper into how this works, but this mental model is enough to start.

## Exit Codes

When a program ends, it returns an **exit code**.

By convention:

- `0` means success
- non-zero usually means some kind of error

In C:

```c
int main(void) {
    return 0;
}
```

This is one reason `return 0;` matters. It is a signal to the OS and to calling programs.

## Why Exit Codes Matter

Exit codes are important because programs often call other programs.

Examples:

- shell scripts
- build systems
- CI pipelines
- service managers

If your program fails but still returns `0`, automation may think everything is fine.

## A Small Example

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("config.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open config.txt\n");
        return 1;
    }

    fclose(file);
    return 0;
}
```

This communicates failure more honestly than printing an error and still pretending success.

## Standard Streams

Processes also interact through standard streams:

- standard input
- standard output
- standard error

As a system programmer, you should already start thinking:

- normal information goes to standard output
- error information goes to standard error

That makes automation and debugging easier.

## Parent and Child Thinking

Even before learning `fork`, it helps to think in terms of:

- one program starting another
- one process observing another's exit status

This mental model becomes essential in shells, service management, scripting, and CI.

## Good Habits

- return non-zero when the program truly fails
- print meaningful errors to standard error
- avoid vague error messages
- think about how another program would use your program

## Common Mistakes

- always returning `0`
- mixing normal output with error output
- hiding failure behind unclear messages
- forgetting that programs are often part of larger automation

## Learning Check

- Can I explain what a process is in practical terms?
- Can I explain why exit codes matter?
- Can I distinguish standard output from standard error?

## Recommended Follow-Up

Write a small C utility that:

- succeeds when a file exists
- fails with a non-zero exit code when it does not
- prints errors to standard error

That is a small but very real system-programming exercise.
