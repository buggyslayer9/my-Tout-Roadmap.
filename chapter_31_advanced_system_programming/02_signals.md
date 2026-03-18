# 31.2 Signals: Interrupting Processes

In User Space, if your C app is stuck in an infinite loop (`while(1) { }`), how do you stop it? 
You run to the terminal and press `Ctrl+C`.

What does `Ctrl+C` actually do? The terminal makes a syscall (using the `kill()` function) to send a **Signal** from the Kernel directly into your infinite loop process.

## What is a Signal?
A signal is an asynchronous notification sent to a process. It is completely out of band—your program could be doing anything at the exact moment the signal strikes.

When a signal arrives, your program is instantly paused, and depending on the signal, your program gets instantly killed, or the program's "Signal Handler" function is instantly executed.

There are many signals, identified by integers:
*   `SIGINT` (2): Interrupt. Usually triggered by `Ctrl+C`. Can be caught and ignored.
*   `SIGSEGV` (11): Segmentation Fault. Triggered by bad memory access. Cannot be meaningfully ignored (your memory is already corrupt!).
*   `SIGTERM` (15): Terminate gracefully. The standard request to close an app.
*   `SIGKILL` (9): Kill unconditionally. **Cannot be caught or ignored.** The Kernel assassinates the process instantly. (e.g., `kill -9 1234`).

## Catching Signals in C

Let's trap `SIGINT` so `Ctrl+C` doesn't stop our program!

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// This is our Custom Signal Handler
// When the kernel hits us with the signal, this function runs immediately,
// interrupting the main thread!
void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT)! I refuse to die to Ctrl+C!\n", sig);
}

int main() {
    // Tell the Kernel: "If you ever send me SIGINT, route it to this function."
    signal(SIGINT, handle_sigint);
    
    printf("Try pressing Ctrl+C. (Press Ctrl+\\ (SIGQUIT) to actually kill me)\n");
    
    // An infinite loop doing "work"
    while(1) {
        printf("Working...\n");
        sleep(2);
    }
    
    return 0;
}
```

## The Danger of Signal Handlers
Signal handlers run asynchronously at any completely random nanosecond of your program's execution.
If your main execution is halfway through writing to a memory buffer or holding a `malloc` lock, and the signal handler fires and tries to use `malloc`... you've just triggered a deadlock or corrupted the heap!

Therefore, Signal Handlers should almost exclusively do one thing: **Set a global boolean flag** (e.g., `volatile sig_atomic_t keep_running = 0;`), and immediately return. 
The main loop checks the flag safely, and cleanly shuts down the program.
