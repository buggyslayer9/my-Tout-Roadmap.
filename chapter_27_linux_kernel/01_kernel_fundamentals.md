# 27.1 Linux Kernel Fundamentals

The Linux kernel is the **core** of every Linux distribution. Understanding it is essential for building your own distro.

## Kernel Architecture

```
┌────────────────────────────────────────────────────┐
│                  User Space                         │
│  Applications → Libraries (glibc) → System Calls    │
├────────────────────────────────────────────────────┤
│                  Kernel Space                       │
│  ┌──────────┐ ┌──────────┐ ┌──────────────────┐    │
│  │ Scheduler │ │ Memory   │ │ Device Drivers   │    │
│  │ (CFS)    │ │ Manager  │ │ (char, block,    │    │
│  │          │ │ (VMM)    │ │  network)        │    │
│  └──────────┘ └──────────┘ └──────────────────┘    │
│  ┌──────────┐ ┌──────────┐ ┌──────────────────┐    │
│  │ VFS      │ │ Network  │ │ IPC (pipes,      │    │
│  │ (ext4,   │ │ Stack    │ │  signals,        │    │
│  │  btrfs)  │ │ (TCP/IP) │ │  shared mem)     │    │
│  └──────────┘ └──────────┘ └──────────────────┘    │
├────────────────────────────────────────────────────┤
│                  Hardware                           │
│  CPU   •   RAM   •   Disk   •   Network   •   GPU  │
└────────────────────────────────────────────────────┘
```

## Key Kernel Subsystems

| Subsystem | Purpose |
|-----------|---------|
| **Process Scheduler** | Decides which process runs on which CPU |
| **Memory Management** | Virtual memory, page tables, swap |
| **VFS** | Unified interface for all filesystems |
| **Network Stack** | TCP/IP, sockets, netfilter |
| **Device Drivers** | Hardware communication |
| **Security** | SELinux, AppArmor, capabilities |

## Building the Linux Kernel from Source

```bash
# 1. Get the source
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
cd linux

# 2. Install build dependencies (Debian/Ubuntu)
sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev

# 3. Configure
make menuconfig    # Interactive configuration
# OR copy your current config
cp /boot/config-$(uname -r) .config
make olddefconfig  # Update with defaults for new options

# 4. Build (use all CPU cores)
make -j$(nproc)

# 5. Install modules and kernel
sudo make modules_install
sudo make install

# 6. Update bootloader
sudo update-grub
```

## Kernel Modules

```c
// hello_module.c — A simple kernel module
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayman Salem");
MODULE_DESCRIPTION("Hello World Kernel Module");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello from kernel module!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye from kernel module!\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

```makefile
# Makefile for kernel module
obj-m += hello_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

```bash
# Build, load, and test
make
sudo insmod hello_module.ko
dmesg | tail -1    # "Hello from kernel module!"
sudo rmmod hello_module
```

## Assignment 27

**Task**: 
1. Download the Linux kernel source
2. Configure it with `make menuconfig` — enable/disable 3 specific options
3. Build and write a simple "hello world" kernel module
4. Load it, check `dmesg`, and unload it

**Sources**:
- [kernel.org](https://www.kernel.org/)
- [Linux Kernel Newbies](https://kernelnewbies.org/)
- [The Linux Kernel Module Programming Guide](https://sysprog21.github.io/lkmpg/)

---

## 📚 Deep-Dive Resources

### Must-Read
- [**"The Linux Programming Interface"**](https://man7.org/tlpi/) — Michael Kerrisk (the definitive POSIX/Linux guide)
- **"Linux Kernel Development"** — Robert Love (readable kernel internals)
- **"Understanding the Linux Kernel"** — Bovet & Cesati (deep architecture reference)

### Free Courses
- [**Linux Foundation LFD103**](https://training.linuxfoundation.org/training/a-beginners-guide-to-linux-kernel-development-lfd103/) — Free beginner kernel development course ⭐
- [**Linux Kernel Newbies**](https://kernelnewbies.org/) — Community wiki, changelogs, starter guides

### References
- [Kernel source (GitHub)](https://github.com/torvalds/linux) | [kernel.org docs](https://www.kernel.org/doc/html/latest/)
- [Linux man pages (man7.org)](https://man7.org/linux/man-pages/) | [ArchWiki](https://wiki.archlinux.org/)
- [Bootlin Elixir (kernel source browser)](https://elixir.bootlin.com/linux/latest/source)

