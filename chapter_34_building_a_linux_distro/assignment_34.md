# Assignment 34: Building `BugsOS` via `chroot`

This assignment asks you to build an entirely functioning, totally isolated minimal Linux "Distribution" inside a folder on your laptop, using nothing but the `busybox` binary.

You will not need an emulator. You will use `chroot` to trick your current Kernel into entering your isolated Distro.

## Requirements

1. **Create the Filesystem Hierarchy**
   In your home directory, create a folder called `BugsOS`.
   Inside it, create the foundational UNIX directories:
   - `/bin`
   - `/lib`
   - `/proc`
   - `/sys`
   - `/dev`

2. **Acquire BusyBox**
   You can either compile `busybox` from source or download an official static precompiled binary from `busybox.net`.
   Save the generic binary file exactly here: `~/BugsOS/bin/busybox`
   *(Ensure it has executable permissions: `chmod +x`)*

3. **Create the Symlinks**
   `busybox` needs to be linked so the shell can find standard commands.
   `cd ~/BugsOS/bin`
   Create symlinks for `sh`, `ls`, and `cat`:
   ```bash
   ln -s busybox sh
   ln -s busybox ls
   ln -s busybox cat
   ```

4. **The `chroot` Initialization**
   You now have a minimal Root Filesystem.
   To enter it, you must be `root`.
   ```bash
   sudo chroot ~/BugsOS /bin/sh
   ```

## The Verification

If you successfully enter the `chroot`:
1. The terminal prompt will change completely.
2. If you type `pwd`, it will say `/`. You can run `ls /` and you will ONLY see your tiny 5 folders. The 1 Terabyte of data outside `~/BugsOS` is entirely invisible and inaccessible to you!
3. **The Mount Test:** Try running `ps`. It will fail or output nothing. Why?
   Because `/proc` is empty! The Kernel hasn't projected the live process state into your fake isolated filesystem yet.
   Inside the `chroot`, type: `mount -t proc none /proc`
   Run `ps` again. You will now see the system processes!

Congratulations. You have just built a bare-bones Docker container from scratch by manually constructing an isolated Root Filesystem.
