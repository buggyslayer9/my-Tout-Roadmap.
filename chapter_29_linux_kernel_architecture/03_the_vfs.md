# 29.3 Everything is a File: The Virtual File System (VFS)

There is a legendary philosophy in UNIX and Linux: **"Everything is a file."**

When you hear this, you might think it means "Linux has a lot of text files." That is a massive understatement. 
What it actually means is: **The Linux Kernel exposes almost all of its internals, hardware, and processes as fake files that you can interact with using standard `open()`, `read()`, and `write()` C functions.**

## The VFS Abstraction
To make this work, Linux uses a massive C `struct` interface called the **Virtual File System (VFS)**. 
When a User Space program asks to `read()` from a "file path", the VFS intercepts the request and routes it to the specific subsystem that actually handles that path.

Here are the crazy things the VFS allows you to treat as "files":

### 1. Hardware Devices (`/dev`)
Want to talk directly to your hard drive, bypassing the filesystem?
It's just a file at `/dev/sda`.
Want to write raw pixels directly to the screen frame buffer?
It's just a file at `/dev/fb0`.
Want a stream of infinite, hardware-generated random numbers?
Just read from `/dev/urandom`.

### 2. Live Process Data (`/proc`)
The `/proc` directory doesn't exist on your hard drive. It is a fake filesystem generated dynamically inside the Kernel's RAM. It exposes the live state of the OS.

*   `cat /proc/cpuinfo`: Reads live data about your CPU.
*   `cat /proc/meminfo`: Reads your live RAM usage.

Every running program gets a folder in `/proc` named after its Process ID (PID).
If you have a process with PID 1234:
*   `cat /proc/1234/cmdline` shows the exact command used to launch the program.
*   `cat /proc/1234/fd/` shows all the files the program currently has open!

### 3. Kernel Configuration (`/sys`)
The `/sys` directory allows you to talk to Kernel subsystems and change hardware settings *live*.
Want to change the brightness of your laptop screen? You don't need a special API or a GUI tool. 
You can literally just write a number into a file!
```bash
echo 50 > /sys/class/backlight/intel_backlight/brightness
```

## Why is this brilliant?
Because "Everything is a file", you can use standard, basic tools (like C's `fopen()`, Rust's `std::fs`, or bash's `echo` and `cat`) to manipulate hardware, read process memory, and change kernel configurations. You don't need to learn a thousand different APIs for a thousand different subsystems!
