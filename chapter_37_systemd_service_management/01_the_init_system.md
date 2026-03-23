# 33.1 PID 1 and The Init System

When the Linux kernel boots up, it mounts the root filesystem, sets up the virtual filesystems (`/proc`, `/dev`, `/sys`), and loads the necessary drivers (LKMs).

But what does a fully booted kernel actually look like? It's just a black screen.
A kernel, by itself, does absolutely nothing useful. 

To start the graphical desktop, the networking stack, the SSH server, and the login prompt, the Kernel must launch **one** User Space program.

This program is given **Process ID 1 (PID 1)**. It is universally called the **Init** system.

## The Historic Problem: `SysVinit`
For decades, Linux used a system called `SysVinit` for PID 1.
It was incredibly rudimentary. PID 1 would just look inside a folder `/etc/init.d/` and run shell scripts one-by-one in alphabetical order.

*   First run `01-mount.sh`
*   Then run `02-network.sh` (Wait for network to connect...)
*   Then run `03-ssh.sh`

**The Issues:**
1. Extremely slow boot times. Everything happened in single-file order.
2. If the SSH daemon crashed randomly ten hours later, `SysVinit` didn't care or notice. The Sysadmin had to notice it and manually run `/etc/init.d/ssh restart`.

## The Modern Revolution: `systemd`

Around 2010, the Linux community realized this shell-script architecture was archaic. They designed a massively complex, unified software suite to replace PID 1: **`systemd`**.

`systemd` is deeply controversial because it violates the "do one thing well" UNIX philosophy. It does *everything*.
But it solved the two biggest problems in Linux administration instantly:

1. **Parallel Booting.** `systemd` builds a strict dependency graph. It knows exactly which services rely on which other services. It instantly launches every service that doesn't have a dependency *in parallel* across all CPU cores. This reduced boot times from minutes to seconds.
2. **Aggressive Supervision.** `systemd` tracks every single process it spawns. If your web server crashes, `systemd` instantly restarts it. You do not need to write custom bash watchdog scripts. 

Today, almost every major Linux distribution (Ubuntu, Fedora, Debian, Arch) uses `systemd` as PID 1. If you are going to deploy backend code to a Linux server, you must know how to construct a `systemd` Service.
