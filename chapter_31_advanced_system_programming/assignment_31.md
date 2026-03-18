# Assignment 31: The Shell Pipeline

In this assignment, you will replicate the core behavior of the Bash shell operator `|`.

You must write a C program that takes exactly two shell commands as arguments, creates an anonymous pipe between them, forks two child processes, uses `dup2` to intercept their File Descriptors, and `exec()`s the programs.

## Requirements

1. **The Goal:** Replicate `ls -l | grep "txt"`.
2. **Execution:** Your program (`my_pipe`) should run like this:
   `./my_pipe "ls -l" "grep txt"`
3. **The Architecture:**
   - Create one `pipe()`.
   - `fork()` Child 1.
   - `fork()` Child 2.
   - The Parent process must wait for both children to finish and then exit.

4. **Child 1 (The Writer - `ls`):**
   - Must use `dup2()` to overwrite its Standard Output (File Descriptor 1) so it points *into* the write-end of the pipe.
   - Must `exec()` the first command.

5. **Child 2 (The Reader - `grep`):**
   - Must use `dup2()` to overwrite its Standard Input (File Descriptor 0) so it reads *from* the read-end of the pipe.
   - Must `exec()` the second command.

## File Descriptors Hint

Every C program automatically has 3 open files:
- `STDIN_FILENO` (0): Keyboard input
- `STDOUT_FILENO` (1): Terminal output
- `STDERR_FILENO` (2): Error output

The `dup2(oldfd, newfd)` system call violently closes `newfd` and replaces it with a clone of `oldfd`.

If you have a pipe `fd[2]`, where `fd[1]` is the write end:
```c
// Inside Child 1:
// 1. Point STDOUT down the pipe instead of the screen
dup2(fd[1], STDOUT_FILENO);

// 2. We don't need the original pipe FDs anymore, STDOUT is taking care of it.
close(fd[0]);
close(fd[1]);

// 3. Execute! When 'ls' writes to what it *thinks* is the screen, 
// the Kernel routes it down the pipe!
execlp("ls", "ls", "-l", NULL);
```

## Grading

If you execute `./my_pipe "ls -la" "wc -l"`, the result should be identical to running `ls -la | wc -l` in bash.

By finishing this, you will have successfully manipulated process memory boundaries, file descriptor tables, and kernel I/O routing—the trifecta of Linux Systems Programming.
