# 28.1 Linux System Programming (POSIX APIs)

System programming means writing code that talks directly to the Linux kernel via **system calls**.

## Essential POSIX APIs

### Process Management

```c
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void) {
    pid_t pid = fork();  // Create child process

    if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
        execlp("ls", "ls", "-la", NULL);  // Replace with new program
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for child
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### Pipes (IPC)

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int pipefd[2];
    pipe(pipefd);  // pipefd[0] = read, pipefd[1] = write

    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[1]);  // Close write end
        char buf[128];
        read(pipefd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(pipefd[0]);
    } else {
        close(pipefd[0]);  // Close read end
        const char *msg = "Hello from parent!";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        wait(NULL);
    }
    return 0;
}
```

### Sockets (Network Programming)

```c
// Simple TCP server
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("Listening on port 8080...\n");

    int client_fd = accept(server_fd, NULL, NULL);
    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, Linux!";
    write(client_fd, response, strlen(response));
    close(client_fd);
    close(server_fd);
    return 0;
}
```

### Memory Mapping

```c
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("data.txt", O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);

    char *mapped = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    printf("File contents:\n%.*s\n", (int)size, mapped);

    munmap(mapped, size);
    close(fd);
    return 0;
}
```

## Assignment 28

**Task**: Build a **multi-process task runner**:
1. Read a list of shell commands from a file (one per line)
2. `fork()` a child process for each command
3. Use `exec()` to run each command
4. The parent waits for all children and reports success/failure
5. Use pipes to capture stdout from each child

**Sources**:
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- "The Linux Programming Interface" by Michael Kerrisk

---

## 📚 Deep-Dive Resources

### Must-Read
- [**Beej's Guide to Unix IPC**](https://beej.us/guide/bgipc/) — Pipes, shared memory, semaphores
- [**Beej's Guide to Network Programming**](https://beej.us/guide/bgnet/) — The best sockets tutorial ⭐
- [**man7.org Linux man pages**](https://man7.org/linux/man-pages/) — Official interface documentation

### Advanced
- [**Advanced Linux Programming**](https://mentorembedded.github.io/advancedlinuxprogramming/) — Free book (ALP)
- Learn `strace` (trace system calls): `strace -f ./your_program`
- Learn `ltrace` (trace library calls): `ltrace ./your_program`

