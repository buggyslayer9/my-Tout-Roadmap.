# 37.2 Capstone Architecture Hints

Building SysGuard is intimidating. If you get stuck, refer to this architectural blueprint to wire the components together correctly.

## 1. The Main Socket Loop

Your `main()` function should look almost exactly like the code from Chapter 32.2.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>

// Automatically clean up dead children (No Zombies!)
void sigchld_handler(int s) {
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    // 1. Setup Signal Handler
    struct sigaction sa;
    sa.sa_handler = sigchld_handler; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    // 2. Setup Server Socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Add SO_REUSEADDR so you don't get "Address already in use" errors during dev
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9999);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("SysGuard Daemon Booted. Listening on 9999...\n");

    // 3. The Infinite Loop
    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) continue;

        printf("Supervising new incoming connection...\n");

        if (fork() == 0) {
            // == CHILD PROCESS ==
            close(server_fd); // Child doesn't need to listen
            
            // --> CALL YOUR PARSER FUNCTION HERE <--
            handle_client(client_fd);
            
            close(client_fd);
            exit(0); // Extremely important: Child MUST die here.
        }
        
        // == PARENT PROCESS ==
        close(client_fd); // Parent closes its copy so the socket unblocks
    }
    return 0;
}
```

## 2. Parsing `/proc/meminfo`

In C, parsing text files requires raw string manipulation.
Use `fopen`, `fgets`, and the dangerously powerful `sscanf()` function to scrape the exact integers you need out of the Kernel's VFS text.

```c
void read_memory(char *output_buffer) {
    FILE *fp = fopen("/proc/meminfo", "r");
    char line[256];
    
    // Total RAM
    fgets(line, sizeof(line), fp);
    int mem_total;
    // sscanf extracts the integer mapped by %d
    sscanf(line, "MemTotal: %d kB", &mem_total); 

    // Free RAM
    fgets(line, sizeof(line), fp);
    int mem_free;
    sscanf(line, "MemFree: %d kB", &mem_free);

    fclose(fp);

    // Format the string into the output buffer to be sent over the socket
    sprintf(output_buffer, "MemTotal: %d MB | MemFree: %d MB\n", 
            mem_total / 1024, mem_free / 1024);
}
```

## 3. The `handle_client` Glue

Combine the network read with a massive `strcmp` (String Compare) block to check what the client sent.

```c
void handle_client(int client_fd) {
    char buffer[1024] = {0};
    char response[1024] = {0};

    // 1. Read the command
    int valread = read(client_fd, buffer, 1024);
    
    // Strip the trailing newline ('\n') from the netcat command
    buffer[strcspn(buffer, "\n")] = 0; 

    // 2. Dispatch
    if (strcmp(buffer, "MEM") == 0) {
        read_memory(response);
    } else {
        sprintf(response, "ERR: Unknown Command.\n");
    }

    // 3. Send Response
    write(client_fd, response, strlen(response));
}
```

Compile, deploy to `systemd`, and you have officially completed Phase 4.
