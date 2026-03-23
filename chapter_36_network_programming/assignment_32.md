# Assignment 32: The Multi-Client HTTP Server

In this assignment, you will solve the Single-Thread Paradox. You must build a highly concurrent HTTP Web Server in pure C that uses `fork()` to handle an unlimited number of simultaneous clients without freezing.

## Requirements

1. **The Server Setup**
   - Create a C program (`web_server.c`).
   - Open a TCP socket on port `8080`.
   - Setup a `while(1)` loop around the `accept()` function.

2. **The `fork()` Engine**
   - The moment `accept()` returns a new `client_fd`, you must immediately `fork()`.
   - In the Child (`pid == 0`), handle the client conversation (read and write), and then definitively `exit(0)`.
   - In the Parent (`pid > 0`), simply `close` your copy of the `client_fd`! Return to the top of the `while()` loop to wait for the next `accept()`.

> **CRITICAL WARNING:** File Descriptors are duplicated across `fork()`. If the Parent process doesn't explicitly `close(client_fd)` after calling fork, the socket will stay permanently open on the client's side, even after the child process closes it.

3. **The Conversation (Handling the HTTP Protocol)**
   When a user visits `http://127.0.0.1:8080` in their Chrome browser, Chrome will automatically send a text string over the TCP Socket that looks exactly like this:
   ```text
   GET / HTTP/1.1
   Host: 127.0.0.1:8080
   User-Agent: Chrome/100.0.0
   ```
   - In your Child process, `read()` this into a buffer and `printf` it to your terminal so you can see Chrome talking to you!
   
4. **The Response**
   To make Chrome render a webpage, you must `write` back the exact string required by the HTTP/1.1 protocol. Send this literal string down the `client_fd`:
   ```c
   // Note the blank line (\n\n) separating the headers from the body!
   char *http_response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Welcome to my Pure C Web Server!</h1>";
   write(client_fd, http_response, strlen(http_response));
   ```

5. **Zombie Cleanup**
   If children `exit(0)` but the parent never calls `wait()`, the children become "Zombies" holding onto RAM. 
   **Hint:** Add this line at the very top of `main` to tell the Kernel you don't care about child exit codes and it should clean them up automatically:
   `signal(SIGCHLD, SIG_IGN);`

## Testing your Creation
Open 3 different tabs in your web browser and navigate to `http://127.0.0.1:8080` simultaneously. They should all load instantly.
You just wrote the core engine of Apache from scratch.
