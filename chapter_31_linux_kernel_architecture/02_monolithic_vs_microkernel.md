# 29.2 The Monolithic Architecture & Loadable Modules

When describing OS kernels, computer scientists generally divide them into two opposing architectures: **Monolithic Kernels** and **Microkernels**.

## The Microkernel Dream
In a Microkernel (like MINIX or GNU Hurd), the kernel running in "Ring 0" is as small as absolutely possible. It only handles extreme basics: CPU scheduling and basic memory management.
Everything else—file systems, network drivers, USB drivers, graphic card drivers—runs in User Space as separate background services.

*   **Pro:** Amazing stability. If the USB driver crashes, only the USB driver restarts. The system survives.
*   **Con:** Terrible performance. Every time your app wants to read a file, it asks the microkernel (Context Switch 1), the microkernel asks the File System service (Context Switch 2), the FS asks the disk driver (Context Switch 3). It is incredibly slow.

## The Monolithic Reality (Linux)
Linus Torvalds chose the opposite approach. Linux is a **Monolithic Kernel**.
In Linux, the CPU scheduler, memory manager, file systems, network stack, and **every single hardware driver** all live together in one giant binary blob running entirely in Ring 0 (Kernel Space).

*   **Pro:** Blazing fast performance. When the file system needs to talk to the disk driver, it's just a standard C function call. No context switches required.
*   **Con:** If the graphics driver or a niche USB driver has a bug and tries to access invalid memory, it crashes the **entire** system unconditionally (this is what a "Kernel Panic" is).

## The Compromise: Loadable Kernel Modules (LKMs)
If the Linux kernel is one giant binary, does that mean every time you buy a new mouse you have to recompile the entire OS to add the driver?

No. Linux solved this using **Loadable Kernel Modules (LKMs)**.
The core kernel is monolithic, but it has the ability to dynamically load and link new chunks of C code directly into Ring 0 *while the system is running*. 

These modules usually have a `.ko` extension (Kernel Object).

When you plug in a new piece of hardware:
1. The kernel detects the hardware ID.
2. It looks for a matching `.ko` file on your hard drive (usually in `/lib/modules/`).
3. It loads the `.ko` file into Kernel Space on the fly.

You can actually see and manage these modules yourself!
*   `lsmod`: Lists all currently loaded kernel modules.
*   `modprobe <module_name>`: Loads a module.
*   `rmmod <module_name>`: Unloads a module.

> **Fun Fact:** Because LKMs jump right into Ring 0, if you write a buggy LKM and `modprobe` it, your system will instantly Kernel Panic and freeze. Welcome to Kernel Development!
