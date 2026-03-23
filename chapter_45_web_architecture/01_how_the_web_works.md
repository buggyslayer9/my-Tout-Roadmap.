# Phase 5: Web Fullstack & Mobile
# 38.1 How the Web Actually Works (The Big Picture)

You have spent the last 37 chapters understanding compilers, memory, processes, system calls, graphics rendering, and TCP sockets. 

You officially understand what a computer is. 
Now, we zoom out to the Macro level. How do 5 billion computers talk to each other to form the World Wide Web?

## The Request / Response Cycle
The web is fundamentally a massive **Client-Server Architecture** running over the TCP sockets we explored in Chapter 32.

It adheres to a strict, synchronous Request/Response cycle:
1. The **Client** (Chrome, Safari, your iPhone App) opens a TCP connection.
2. The Client sends a formatted text message called a Request.
3. The **Server** (A C program, Node.js, Python Django) reads that text, computes data, and sends a formatted text message back (the Response).
4. The Client closes the connection (historically) and renders the UI.

The Server never initiates a conversation. It only reacts.

## DNS: The Internet's Phonebook
When you type `https://github.com` into your browser, the TCP socket cannot dial the word "github." TCP only understands IP Addresses (like `140.82.113.3`).

Before Chrome even attempts to open a socket to GitHub, it executes the **DNS Resolution** process:
1. Chrome checks its local cache.
2. Chrome asks your Operating System (Linux/macOS/Windows).
3. The OS asks your Router.
4. The Router asks your ISP (Comcast/AT&T).
5. Your ISP asks a massive global Root Name Server.
6. The exact IP Address `140.82.113.3` is finally returned.

Only then does Chrome call `socket()` and `connect()`.

## HTTP vs HTTPS
In Chapter 32, we sent raw strings over the socket (`"Hello from C!"`).
If you intercept that TCP packet on public Wi-Fi using a tool like Wireshark, you can read the string perfectly in plain text.

If you are sending a password, this is catastrophic.

**HTTPS (HTTP Secure)** solves this by injecting an encryption layer (TLS/SSL) *between* TCP and HTTP.
1. The TCP Handshake occurs.
2. The **TLS Handshake** occurs. The Server sends Chrome a mathematical Public Key (A Certificate).
3. Chrome and the Server agree on a symmetric secret key.
4. From now on, when Chrome wants to send the string `"Password123"`, it encrypts it first.
5. If a hacker intercepts the packet, they see random static garbage. Only the server has the key to decrypt it back into plain text.

As a Web Developer today, you must assume 100% of your traffic will run over HTTPS.
