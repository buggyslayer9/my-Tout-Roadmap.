# 30.3 The Sysadmin's X-Ray Glasses: `strace`

You have just learned that every single interaction a program has with the outside world (network, disk, screen, memory allocation) requires a System Call.

This means if you intercept the System Calls a program is making, you can understand **exactly** what the program is doing, even if you don't have the source code.

Linux provides a tool that does exactly this: **`strace`**.
It is widely considered the most important debugging tool for Senior Linux Engineers.

## How to use `strace`

Let's say you have a basic C program that prints "Hello" and exits.
You compile it to `./hello`.

If you run `strace ./hello`, it will print every single interaction between that binary and the Linux Kernel.

```bash
$ strace ./hello
```

### The Output (Simplified)
```text
execve("./hello", ["./hello"], 0x7ffd5885c470 /* 55 vars */) = 0
brk(NULL)                               = 0x55aa123b7000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffe7dfaa950) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f23a1a14000
... (loading shared libraries like glibc) ...
write(1, "Hello\n", 6)                  = 6
Hello
exit_group(0)                           = ?
+++ exited with 0 +++
```

Look closely at the bottom! We see our standard `printf` actually invoked the `write` syscall to File Descriptor `1` (stdout), passed the string `"Hello\n"`, and it returned `6` (the number of bytes written).
Then it called `exit_group(0)` to close the program!

## Real World Magic

Imagine a web server program is crashing immediately upon startup, printing "Configuration Error" but giving no further details. You don't have the source code. How do you fix it?

You run `strace ./web_server`.

Somewhere in the output, you see this:
```text
openat(AT_FDCWD, "/etc/web_server/config.json", O_RDONLY) = -1 ENOENT (No such file or directory)
```
**Boom.** You found the exact problem in 5 seconds without looking at a single line of C code. The program is trying to open `/etc/web_server/config.json` and the Kernel is returning `ENOENT` (Error NO ENTity - the file doesn't exist). 
You create the config file, and the program launches perfectly.

`strace` allows you to see the matrix. You aren't guessing what the code is doing; you are watching the exact commands it is sending to the CPU.
