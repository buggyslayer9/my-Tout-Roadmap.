# 31.3 Inter-Process Communication (IPC)

We established that the Kernel physically isolates every process in Ring 3. A process cannot read the memory of another process.

But what if processes *need* to talk? What if `ls` needs to send its output to `grep`?
The Kernel must provide supervised channels for Inter-Process Communication (IPC).

There are three primary IPC mechanisms a Systems Programmer must master: **Pipes**, **Shared Memory**, and **Sockets** (which we cover in the next chapter).

## 1. Anonymous Pipes (The UNIX Philosophy)

When you run `ls -l | grep txt` in bash, no temporary files are created on your hard drive. Bash uses an **Anonymous Pipe**.

A Pipe is a unidirectional, in-memory data channel maintained by the Kernel. It has a "Write End" and a "Read End".

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    
    // Create the pipe. The kernel gives us two File Descriptors.
    // pipefd[0] is the Read end. pipefd[1] is the Write end.
    if (pipe(pipefd) == -1) { return 1; }

    pid_t pid = fork(); // Clone the process

    if (pid == 0) {
        // Child Process (The Writer)
        close(pipefd[0]); // Child doesn't read, only writes.
        
        char *msg = "Secret message from the clone!\n";
        write(pipefd[1], msg, strlen(msg)); // Send message into the kernel pipe
        close(pipefd[1]); // Close the write end to send EOF
    } 
    else if (pid > 0) {
        // Parent Process (The Reader)
        close(pipefd[1]); // Parent doesn't write, only reads.
        
        char buffer[100];
        // Read directly from the kernel pipe buffer
        int bytes = read(pipefd[0], buffer, sizeof(buffer));
        buffer[bytes] = '\0'; // Null terminate
        
        printf("Parent received: %s", buffer);
        close(pipefd[0]);
    }

    return 0;
}
```

Pipes are clean, safe, and synchronized (if the pipe is empty, `read()` pauses the reader until the writer sends something).

## 2. Shared Memory (shm)

Pipes are great for small streams of bytes, but they require the Kernel to copy data from the Writer into Kernel Space, and then copy it from Kernel Space into the Reader. This is immensely slow for large video frames or massive databases.

If two processes need to share 4GB of data instantly, we use **Memory Mapping** or **POSIX Shared Memory**.

Instead of copying bytes, we ask the Kernel to map the *exact same physical RAM chips* into the virtual memory space of both Program A and Program B.

```c
// Process A (The Creator)
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // 1. Create a "Shared Memory Object" named /my_shared_ram
    int fd = shm_open("/my_shared_ram", O_CREAT | O_RDWR, 0666);
    
    // 2. Set its physical size to 1024 bytes
    ftruncate(fd, 1024);
    
    // 3. Map it into our Virtual Adress Space
    char *shared_data = mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
    
    // 4. Write to it!
    strcpy(shared_data, "Hello from Process A!");
    
    return 0;
}
```

Now, Process B can execute almost the exact same code, connect to `/my_shared_ram`, and instantly `printf("%s", shared_data)`. No kernel copying involved!

**The Catch:** Because the Kernel is completely out of the way, if Process A writes to the RAM at the *exact same nanosecond* Process B reads it, you get corrupt data. You must manually implement semaphores or mutex locks across process boundaries to use Shared Memory safely!
