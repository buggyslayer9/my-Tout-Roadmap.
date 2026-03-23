# 34.3 `busybox`: The Swiss Army Knife

If you were to compile the source code for the standard GNU `coreutils` (which provides `ls`, `cp`, `mv`, `cat`), it would consume hundreds of megabytes of space. If you add `bash`, that's another huge binary.

If you want to build a truly tiny Custom Linux Distro (like an embedded Raspberry Pi controller, or a tiny 5MB Docker Container like Alpine Linux), you cannot use GNU tools.

Enter **BusyBox**.

## What is BusyBox?
BusyBox is famously called the "Swiss Army Knife of Embedded Linux".

It is a single, solitary, tiny C binary (usually under 2 Megabytes).
However, depending on what *name* you use to execute the binary, its `main()` function behaves like a completely different program!

It contains miniature, highly optimized versions of over 300 classic UNIX tools built into one executable.

## The Symlink Magic

Imagine you compile BusyBox into a single file at `/bin/busybox`.

How do you use it as `ls`?
You create a "symbolic link" (a shortcut) named `ls` that points to `busybox`.

```bash
# Create the link
$ ln -s /bin/busybox /bin/ls

# Run the shortcut
$ /bin/ls -l
```

When you execute `/bin/ls`, the single `busybox` Binary boots up. In C, `argv[0]` contains the name used to execute the program. 
`busybox` inspects `argv[0]`. It sees `"ls"`, so it completely bypasses its shell code, bypasses its networking code, jumps to its internal `ls_main()` function, and flawlessly prints your directory contents.

## Building `initramfs` and Alpine Linux
Because it is so small, BusyBox is the engine running almost every single `Initramfs` in the world (the mini-filesystem we talked about in 34.1).

It is also the foundational Engine of **Alpine Linux**, the undisputed king of cloud Docker Containers.

By compiling the Linux Kernel (`vmlinuz`) and compiling `busybox`, you can build a fully functioning, interactive Linux Distribution that fits entirely on a 10 Megabyte floppy disk.
