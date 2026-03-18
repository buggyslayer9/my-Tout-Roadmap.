# 32.2 Building a TCP Server

Writing a server in C is a rite of passage. It is not as simple as launching Node.js and typing `app.listen(8080)`. You must manually walk through the 5 steps of the POSIX Socket API.

## The Server Lifecycle: `socket() -> bind() -> listen() -> accept()`

### 1. `socket()`: Asking for a Phone
First, we ask the Kernel to create a generic socket endpoint.
```c
// Domain: AF_INET (IPv4)
// Type: SOCK_STREAM (TCP)
// Protocol: 0 (Let the OS choose the default for the given type)
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
```

### 2. `bind()`: Getting a Phone Number
The socket is currently floating in the void. We need to attach it to a specific Port on our machine so the outside world can dial in.
```c
#include <netinet/in.h>

struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY; // Listen on ALL network interfaces (WiFi, Ethernet, Lo)
address.sin_port = htons(8080);       // Remember: Host-To-Network-Short!

// We must cast the pointer to the generic abstract struct 'sockaddr'
bind(server_fd, (struct sockaddr *)&address, sizeof(address));
```

### 3. `listen()`: Turning the ringer on
We tell the Kernel we are officially ready to receive connections. We also specify a "Backlog" queue. If 10 people connect at the exact same millisecond, how many should the Kernel put on hold while our app handles the first one?
```c
listen(server_fd, 5); // Allow 5 connections to queue up
printf("Server is listening on Port 8080...\n");
```

### 4. `accept()`: Picking up the phone
Unlike `listen` (which returns instantly), `accept()` is a **blocking** system call. Your entire C program stops executing and goes to sleep right here. It will not wake up until the Kernel detects an incoming TCP handshake from a remote computer.
```c
int client_fd;
int addrlen = sizeof(address);

// The program freezes here permanently until someone connects!
client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

printf("New client connected! They have File Descriptor: %d\n", client_fd);
```

### 5. `read()` and `write()`: The Conversation
Notice what `accept()` returns: **A totally new File Descriptor!**
The `server_fd` just listens for calls. When a call comes in, the Kernel routes the unique conversation to `client_fd`. You can now `read()` and `write()` exactly like you do with normal text files.

```c
#include <unistd.h>
#include <string.h>

// 1. Read what the client sent us
char buffer[1024] = {0};
read(client_fd, buffer, 1024);
printf("Client said: %s\n", buffer);

// 2. Send a response
char *hello = "Hello from the C Server!\n";
write(client_fd, hello, strlen(hello));

// 3. Hang up
close(client_fd);
close(server_fd); // Close the main listener
```

## Running it
Compile this, put it in a `while(1)` loop around the `accept` and `close` phase, and you have a web server!

You can test it directly from the terminal using `curl`:
```bash
$ curl http://127.0.0.1:8080
```
Curl makes the TCP connection, sends an HTTP GET request (which you will read in your buffer), and prints whatever you `write()` back!
