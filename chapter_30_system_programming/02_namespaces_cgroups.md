# 28.5 Container Internals (Namespaces & cgroups)

Containers (like Docker or Podman) are not magic. They don't run a virtual machine. A container is simply a normal Linux process that has been isolated using two core Linux kernel features: **Namespaces** and **cgroups**.

As a system programmer, you don't just use Docker; you understand how it works.

## 1. Namespaces (Isolation)

Namespaces restrict what a process can *see*. When you run a process in a new namespace, it thinks it is the only process on the machine.

There are 7 main namespaces in Linux:
1. **PID:** Process IDs (the process thinks it is PID 1)
2. **Mount:** Filesystem mounts (it has its own `/` directory)
3. **Network:** It has its own network stack (IP address, `eth0` interface)
4. **UTS:** It has its own hostname
5. **IPC:** It has its own inter-process communication queues
6. **User:** It can be root inside the namespace, but a normal user outside
7. **Cgroup:** It has its own view of cgroups

### Creating a Namespace in C
You create namespaces using the `clone()` system call (a more powerful version of `fork()`), or by calling `unshare()`.

```c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int child_function(void* arg) {
    printf("Inside the container! My PID is %d\n", getpid()); // Will print PID 1
    
    // Set a custom hostname for this container
    sethostname("my-container", 12);
    
    // Launch a shell inside the isolated environment
    execlp("/bin/bash", "bash", NULL);
    return 0;
}

int main() {
    printf("Host system! My PID is %d\n", getpid());

    // Allocate stack for the child process
    char* stack = malloc(1024 * 1024);
    if (!stack) return -1;

    // clone() creates a new process. 
    // CLONE_NEWPID creates a new PID namespace.
    // CLONE_NEWUTS creates a new Hostname namespace.
    pid_t child_pid = clone(child_function, stack + (1024 * 1024), 
                            CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD, NULL);

    waitpid(child_pid, NULL, 0);
    printf("Container stopped.\n");
    return 0;
}
```
*Note: This code requires `sudo` to run.*

## 2. Control Groups (cgroups) (Resource Limits)

If namespaces restrict what a process can *see*, **cgroups** restrict what a process can *use*. 

Cgroups limit:
- **Memory:** Max RAM usage before the process is killed (OOM)
- **CPU:** Percentage of CPU time or binding to specific cores
- **Block I/O:** Disk read/write speed limits

### Managing cgroups via the Filesystem
In Linux, everything is a file. The kernel exposes cgroups under `/sys/fs/cgroup/`.

To limit a process to 50MB of RAM, you don't need a C API; you just write to files!

```bash
# 1. Create a new cgroup named "my_container"
sudo mkdir /sys/fs/cgroup/my_container

# 2. Set the memory limit to 50MB
echo "50000000" | sudo tee /sys/fs/cgroup/my_container/memory.max

# 3. Add a process to the group
echo $PID | sudo tee /sys/fs/cgroup/my_container/cgroup.procs
```

## Docker = Namespaces + cgroups + `pivot_root`

When you type `docker run ubuntu`, Docker daemon simply:
1. Downloads the Ubuntu filesystem.
2. Creates isolated **Namespaces** for PID, Network, Mount, etc.
3. Sets up **cgroups** to restrict memory/CPU.
4. Uses `pivot_root` or `chroot` to change the `.` directory to the Ubuntu files.
5. Executes your command (`/bin/bash`) inside that environment.

Understanding this allows you to debug strange container issues and write your own virtualization tools in C or Rust.
