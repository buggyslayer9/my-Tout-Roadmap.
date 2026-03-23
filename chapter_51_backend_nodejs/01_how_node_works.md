# 43.1 Javascript Escapes the Browser: Node.js

Javascript was designed for exactly one purpose: drawing dropdown menus and validating email fields inside the Netscape Navigator web browser in 1995.

It had no standard library. It could not open a TCP Socket. It could not read a file from the hard drive (`open('/etc/passwd')`). If it could, websites would install terminal viruses instantly. Javascript was strictly jailed inside a "Browser Sandbox."

## The Node.js Revolution

In 2009, Ryan Dahl realized that the V8 Javascript Engine (written by Google for Chrome) was insanely fast—faster than Python and Ruby.

He took the open-source C++ V8 Engine out of the Chrome browser and installed it directly onto his Linux laptop.

He then wrote immense amounts of C++ code to wrap V8. He created C++ bindings that allowed the V8 Engine to directly call standard POSIX APIs in Linux (System Calls, Chapter 30).

He named this massive C++ wrapper **Node.js**.

When you run `node index.js`, the Node.js C++ binary reads your file, passes the text to the V8 compiler, and translates your JS into machine code. 
If your Javascript calls `fs.readFile('/etc/passwd')`, the custom Node.js C++ binding intercepts it and translates it into a standard Linux `open()` system call.

Javascript has escaped the browser. It is now a fully-fledged Backend Systems Language.

## The Architecture of Node: `libuv`

Node.js had one massive advantage over legacy backend languages like PHP or Java.

**It was strictly Single-Threaded.**

In Chapter 32, we learned about the "Single Thread Paradox." If a TCP Server is single-threaded, and one user downloads a 5MB file, the entire server freezes preventing anyone else from logging in. Java solves this by spinning up 1,000 OS Threads for 1,000 users. Threads consume massive amounts of RAM and cause terrible context-switching overhead.

Node.js uses a magical C library called **`libuv`**.

`libuv` runs a single, infinite C `while(1)` Event Loop using the Linux `epoll` system call.
When 10,000 users connect, Node.js doesn't spawn 10,000 threads. The Event Loop asks the Linux Kernel to track all 10,000 TCP sockets. The thread goes to sleep.

When Socket #435 finally sends a packet, the Kernel wakes up the single thread, executes the Javascript callback attached to that specific socket, computes the database action, fires the HTTP response back into the socket, and the thread instantly returns to listening for the next random network event.

This architecture enables an incredibly lightweight Node.js container to serve 50,000 simultaneous websocket connections without crashing.
