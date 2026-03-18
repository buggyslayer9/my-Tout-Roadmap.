# 31.1 The Fork / Exec Model

In many operating systems (like Windows), if you want to spawn a new background process, you call an API like `CreateProcess(...)` and hand it an executable file. The OS creates a new sandbox and runs the game.

In Linux, process creation is entirely different, rooted in 1970s UNIX philosophy. It is split into two wildly powerful, completely separate syscalls: `fork()` and `exec()`.

## 1. `fork()`: The Clone Factory

When your program calls `fork()`, the Linux Kernel literally pauses your program, copies its entire memory space, copies all its open file descriptors, and creates a **perfect clone**, running side-by-side with the original.

How do the clones know who is who? `fork()` returns a different integer to each of them!

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Starting up! My PID is %d\n", getpid());
    
    // THE SPLIT
    pid_t id = fork();
    
    // Everything below this line is running TWICE!
    
    if (id == 0) {
        // We are the Child Process. fork() returns 0 to the child.
        printf("I am the exact clone! My PID is %d\n", getpid());
    } else if (id > 0) {
        // We are the Parent Process. fork() returns the ID of the new baby clone.
        printf("I am the parent. My clone's ID is: %d\n", id);
    } else {
        printf("Fork failed (out of memory/PIDs)!\n");
    }
    
    return 0;
}
```
**Why this is dangerous:** If you have 2GB of RAM allocated and you call `fork()`, you might assume the OS instantly allocates another 2GB. Modern Linux uses "Copy on Write" (CoW), meaning both processes strictly share the identical RAM until one of them *modifies* a variable. Only then is memory separated.

## 2. `exec()`: The Brain Replacement

If `fork()` only makes clones, how do we run *different* programs? (e.g., How does the `bash` terminal launch `grep`?)

`exec()` (actually `execve` under the hood) is a syscall that replaces the currently running process's memory space and code entirely with a new executable from the hard drive. 

If you call `exec()`, your current program is instantly erased, and the new program boots up in its place. **`exec()` never returns, because "your code" was just deleted from RAM!**

### Combining Fork and Exec

To launch a new program, Linux developers combine the two commands:

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // We are the child clone. 
        // Immediately replace our "brain" with the /bin/ls program!
        char *args[] = {"/bin/ls", "-l", NULL};
        execv("/bin/ls", args); // The child process ceases to be our code here.
    } 
    else if (pid > 0) {
        // We are the parent.
        printf("Waiting for the child to finish running 'ls'...\n");
        int status;
        waitpid(pid, &status, 0); // Pause the parent until the child exits
        printf("Child finished!\n");
    }
    
    return 0;
}
```

This split model is why Linux is so incredibly powerful. Between the `fork` and the `exec`, the child process has the exact same configuration as the parent. The parent can modify the child's environment variables, open network ports for it, or redirect its `stdout` (which is precisely how the bash `|` pipe works!), all before the child turns into the final target execution.
