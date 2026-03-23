# 32.3 Building a TCP Client

A client program is much simpler than a server. It doesn't need to `bind` to a specific port, and it doesn't need to `listen` or `accept`. It simply calls the server's number.

## The Client Lifecycle: `socket() -> connect()`

### 1. `socket()`: Asking for a Phone
Just like the server, we start by creating a generic IPv4 TCP socket.
```c
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int sock = 0;
sock = socket(AF_INET, SOCK_STREAM, 0);
```

### 2. `connect()`: Dialing the Number
We populate a struct with the IP Address and Port of the server we want to reach.
Because IP addresses are written as strings ("127.0.0.1"), we must use the `inet_pton` function to magically convert the string into pure binary bits.

```c
struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(8080);

// Convert IPv4 address string to pure binary format
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

// Dial the server! This is a blocking call. The Kernel will execute the 
// 3-way TCP Handshake across the internet. If the server is offline, this fails.
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("Connection Failed!\n");
    return -1;
}

printf("Connected to the server successfully.\n");
```

### 3. `read()` and `write()`: The Conversation
The connection is established! The single `sock` file descriptor is used for both reading and writing to the remote server.

Because TCP is a stream, there are no "messages." If you send 5 bytes, the server might read 3 bytes, then later read 2 bytes. 

```c
char *client_message = "Hello from the C Client!";
char buffer[1024] = {0};

// Send our message
write(sock, client_message, strlen(client_message));
printf("Message sent to server.\n");

// Pause the program and wait for the server to send something back
read(sock, buffer, 1024);
printf("Server replied: %s\n", buffer);

// Close the connection
close(sock);
```

## The Single-Thread Paradox
Notice an enormous problem with the Server code from the previous lesson:
The Server loops back up and calls `accept()` to wait for a new user. But what happens if User 1 connects, and the server gets stuck in a `read()` trying to download a 5-gigabyte file from User 1?

Because the server is stuck on the single `read()` blocking call, the server *never loops around to call `accept()` again*. 
If User 2 connects, they are trapped in the "Backlog" queue. The entire server is totally frozen and unavailable to the world until User 1 finishes uploading!

### The Solution
There are three ways to solve this. As a Senior Engineer, you must know them all:

1. **Multi-Processing (`fork()`):** When `accept()` returns a new `client_fd`, the server calls `fork()`. The child process handles the connection, and the parent process instantly loops back around to wait for a new `accept()`. (This is how the famous Apache Web Server works).
2. **Multi-Threading:** When `accept()` returns, the server spawns a new lightweight Thread to handle the `client_fd`.
3. **Event Loops (`epoll` / `select`):** The single thread tells the Kernel: "Put me to sleep. Wake me up if ANY of my 10,000 `client_fd`s have data queued up." (This incredibly fast, non-blocking architecture is how NGINX and Node.js work).
