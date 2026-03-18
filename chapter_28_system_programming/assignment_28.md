# Assignment 28

## Task

Build a **multi-process task runner** that executes commands in parallel:

### Part 1: Basic Multi-Process Runner

1. Create a file `commands.txt` with shell commands (one per line), e.g.:
   ```
   ls -la
   echo "Hello"
   cat /etc/os-release
   date
   ```

2. Write a C program that:
   - Reads the command file line by line
   - For each command, forks a child process
   - Uses `execlp()` or `execvp()` to run the command
   - Parent uses `waitpid()` to wait for all children
   - Reports success/failure status for each command

### Part 2: Capture stdout with Pipes

3. Modify the program to capture stdout from each child:
   - Create a pipe before forking
   - Redirect child's stdout to the pipe write end
   - Parent reads from pipe read end
   - Print the captured output with the command name

### Part 3: Parallel Execution (Bonus)

4. Make execution parallel:
   - Fork all children immediately
   - Use `waitpid()` with `WNOHANG` to collect results as they complete
   - Track total execution time

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **fork()** - Creating child processes
2. **exec() family** - Replacing process image with new program
3. **wait() / waitpid()** - Waiting for child processes
4. **pipe()** - Inter-process communication
5. **dup2()** - Redirecting file descriptors
6. **File I/O** - Reading lines from a file

---

## Sources

- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Linux man pages](https://man7.org/linux/man-pages/)

---

## Hints

- Use `fork()` to create child processes
- After `fork()`, use `pipe()` before `exec()`
- Redirect stdout using: `dup2(pipefd[1], STDOUT_FILENO)`
- Close unused pipe ends in both parent and child
- Use `WEXITSTATUS(status)` to get the return code
- Handle edge cases: empty lines in command file, long lines

## Example Output

```
=== Multi-Process Task Runner ===

[1] Running: ls -la
    Status: SUCCESS (exit code 0)
    Output:
    total 40
    drwxr-xr-x  10 user  user  4096 Mar 14 12:00 .
    drwxr-xr-x  10 user  user  4096 Mar 14 12:00 ..
    ...

[2] Running: echo "Hello"
    Status: SUCCESS (exit code 0)
    Output:
    Hello

[3] Running: cat /etc/os-release
    Status: SUCCESS (exit code 0)
    Output:
    NAME="Ubuntu"
    ...

=== Summary ===
Commands run: 3
Successful: 3
Failed: 0
Total time: 0.45s
```
