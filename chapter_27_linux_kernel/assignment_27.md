# Assignment 27

## Task

Complete the following exercises to gain hands-on experience with Linux kernel development:

### Part 1: Kernel Source Setup

1. Clone the Linux kernel source from kernel.org:
   ```bash
   git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
   cd linux
   ```

2. Install build dependencies:
   ```bash
   sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev
   ```

3. Configure the kernel using menuconfig:
   - Enable 3 features you find interesting (e.g., CPU frequency scaling, kernel debugging)
   - Disable 1 feature you don't need
   - Save your configuration

4. Document what you enabled/disabled and why

---

### Part 2: Build a Simple Kernel Module

Create a "Hello World" kernel module:

1. Create the module source file `hello.c`:

```c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple hello world kernel module");
MODULE_VERSION("1.0");

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

2. Create the Makefile:

```makefile
obj-m += hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

3. Build and test:
   ```bash
   make
   sudo insmod hello.ko
   dmesg | tail -5
   sudo rmmod hello
   dmesg | tail -5
   ```

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **Linux kernel architecture** - User space vs kernel space
2. **Kernel modules** - Loadable kernel modules (LKM)
3. **Kernel build system** - Makefiles for kernel modules
4. **System calls** - How user programs interact with kernel
5. **printk()** - Kernel's logging function
6. **dmesg** - Kernel message buffer

---

## Sources

- [Linux Kernel Newbies](https://kernelnewbies.org/)
- [Kernel Module Programming Guide](https://sysprog21.github.io/lkmpg/)
- [kernel.org](https://www.kernel.org/)

---

## Hints

- Start with a minimal kernel configuration to speed up build time
- Use `make menuconfig` for an interactive configuration
- Check `dmesg` after loading/unloading to see kernel messages
- Make sure you're using the same kernel version headers as your running kernel
- If build fails, check that you have kernel headers installed: `sudo apt install linux-headers-$(uname -r)`

## Expected Output

After loading the module, `dmesg` should show:
```
[ 1234.567890] Hello from kernel module!
```

After unloading:
```
[ 1235.123456] Goodbye from kernel module!
```
