# Assignment 30: The Pure `strace` Detective

Your task is effectively a hacker's challenge: Write a "Hello World" program in C that does not use the C Standard Library (`libc`) *at all*.

## Requirements

You must write a C file (`raw_hello.c`) completely bypassing `libc`.
1. **NO INCLUDES.** Do not `#include <stdio.h>` or `#include <stdlib.h>`.
2. **NO `main()` function!** `libc` provides the setup code that calls `main()`. Without `libc`, the Kernel immediately jumps to a symbol called `_start`. You must define `void _start()`.
3. Inside `_start`, you must use inline x86_64 Assembly to trigger the raw `SYS_write` syscall.
4. You must then use inline Assembly to trigger the `SYS_exit` syscall. If you do not explicitly call `exit`, the CPU will run off the end of your function and crash into random memory, throwing a Segfault!

## The Assembly

Because you cannot even use the wrapper `<unistd.h> syscall()` function (as that wrapper belongs to `libc`!), we must write 3 lines of pure Assembly to trigger the Context Switch.

On x86_64 Linux:
*   Put the Syscall Number into the `rax` register.
*   Put Arg1 into `rdi`.
*   Put Arg2 into `rsi`.
*   Put Arg3 into `rdx`.
*   Trigger the context switch by executing the `syscall` instruction.

**Hint for `write` (Syscall 1):**
```c
asm volatile (
    "mov $1, %%rax\n" // SYS_write
    "mov $1, %%rdi\n" // STDOUT
    "syscall"
    :
    : "S" (my_string_pointer), "d" (my_string_length)
);
```

**Hint for `exit` (Syscall 60):**
```c
asm volatile (
    "mov $60, %%rax\n"   // SYS_exit
    "mov $0, %%rdi\n"     // Return code 0
    "syscall"
);
```

## Compiling without libc
You must explicitly tell `gcc` to drop the massive standard library:
```bash
gcc -nostdlib raw_hello.c -o raw_hello
```

Check the binary size! A standard C "Hello World" is usually ~16KB. Your `raw_hello` will be under 2KB.

## Verification
To prove you succeeded, run your program under the X-Ray tool:
```bash
strace ./raw_hello
```

If you succeeded, the output of `strace` will be incredibly clean. You won't see dozens of `mmap` calls or memory allocations loading `libc.so.6`. You should see literally nothing except your `execve`, your `write`, and your `exit`.

This proves you have successfully bypassed the User Space abstractions and achieved total, raw command over the CPU and the Linux Kernel.
