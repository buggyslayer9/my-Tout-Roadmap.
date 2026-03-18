# 7.4 Memory Leaks: The Silent Killer

A memory leak occurs when you allocate heap memory and then lose the pointer to it **without calling `free()`**. The memory is still reserved by the OS, but your program has no way to access or release it. Over time, leaked memory accumulates and your application slowly devours all available RAM.

## The Classic Leak

```c
void process_data(void) {
    int *buffer = malloc(1000 * sizeof(int));
    
    // ... do some work with buffer ...
    
    return;  // 💀 We left without calling free(buffer)!
    // 'buffer' (the pointer variable) is now destroyed (it was on the stack).
    // But the 4000 bytes of HEAP MEMORY it pointed to still exist!
    // Nobody can free them now. They are orphaned until the program exits.
}
```

## Why Leaks Are Dangerous

- A single small leak may be harmless.
- A leak inside a loop that runs 10,000 times will eat 40 MB.
- A leak inside a GTK event handler that fires every frame will crash the app after a few minutes.
- Long-running servers (web servers, database engines) with even tiny leaks will eventually exhaust the system and crash.

## How to Detect Leaks: Valgrind

Valgrind is a powerful Linux tool that tracks every single byte your program allocates and frees. It will tell you exactly where the leak originated.

```bash
# Compile with debug symbols for readable output.
gcc -g -Wall -Wextra program.c -o program

# Run through Valgrind.
valgrind --leak-check=full ./program
```

Valgrind's output will look like:
```
==12345== LEAK SUMMARY:
==12345==    definitely lost: 4,000 bytes in 1 blocks
```

On macOS, you can use `leaks` instead:
```bash
leaks --atExit -- ./program
```

## The Golden Rules

1. Every `malloc` must have a matching `free`.
2. Set freed pointers to `NULL` immediately.
3. Before a function returns, ask yourself: "Did I allocate anything that I haven't freed?"
4. Run Valgrind regularly during development. Not just at the end.
