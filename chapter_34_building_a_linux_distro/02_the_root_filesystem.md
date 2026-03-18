# 34.2 Anatomy of the Root Filesystem (`/`)

What separates Ubuntu from Fedora, or Arch from Alpine?

**They all use the exact same Linux Kernel.**

A "Linux Distribution" is simply a curated collection of User Space binaries mapped onto a specific folder structure (The Root Filesystem).

If you are going to build your own minimal Linux Distro (or a Docker Container!), you must understand the Linux Filesystem Hierarchy Standard (FHS).

## The Core Directories

### `/bin` and `/sbin` (Binaries)
This is where the executables live.
*   `/bin`: Standard user utilities (`ls`, `cp`, `bash`, `cat`).
*   `/sbin`: System Administration utilities (`iptables`, `fsck`). Usually reserved for `root`.
*(Note: Modern distros often symlink these to `/usr/bin` to unify the system).*

### `/etc` (Et Cetera / Configurations)
Global, system-wide configuration files (`.conf`, `.ini`). 
If you want to configure the DNS server, the SSH server, or systemd services, you edit text files in `/etc`. 
**Crucial Rule:** No binaries should ever live in `/etc`.

### `/usr` (UNIX System Resources)
When Linux was created, hard drives were tiny. The OS filled up the first dial-disk, so they added a second disk mounted at `/usr` for everything else.
Today, `/usr` acts as the massive, read-only system vault for your Distro. 
If you install an application via `apt` or `pacman`, it goes in `/usr/bin/`. Its C header files go in `/usr/include/`. Its shared C libraries (`.so`) go in `/usr/lib/`.

### `/var` (Variable Data)
Files that constantly change size and content.
*   `/var/log/`: System logs (journalctl database, raw text logs).
*   `/var/lib/`: State files (databases like PostgreSQL store their raw tables here).
*   `/var/cache/`: Downloaded package manager `.deb` update files.

### `/dev`, `/proc`, `/sys` (The Fake Directories)
As discussed in Chapter 29, these directories don't exist on disk. They are massive C Structs in the Kernel's RAM projected outward as an interface to hardware and running processes.

### `/lib` (Shared Libraries)
This contains the critical shared `.so` (Shared Object) libraries needed by the basic binaries in `/bin`. 
The most important file on your entire computer lives here: **`libc.so.6`**. If you delete `libc.so.6`, your entire OS breaks instantly because `bash` and `ls` can no longer execute!

---

## Creating a Distro with `chroot`
Because the Kernel just treats `/` as a boundary, you can create a perfectly isolated secondary Linux Distro *inside* your current OS.

If you create a new folder `~/my_new_os`, and you manually populate it with a fake `/bin` with your own compiled `bash` shell, and a fake `/lib` with your own `libc`, you can use the `chroot` command:

```bash
$ sudo chroot ~/my_new_os /bin/bash
```

The Kernel will "trick" that `bash` process into believing that `~/my_new_os` is the absolute root (`/`) of the hard drive. It cannot see your real OS at all!

This is the exact technology that powers Docker. A Docker Container is literally just a `chroot` environment packaged inside a `.tar` zip file!
