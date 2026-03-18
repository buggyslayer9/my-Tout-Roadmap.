# 10.6 Error Handling in C

C has no exceptions, no `try/catch`, and no `Result<T, E>`. Error handling in C is manual, explicit, and based on return values. It requires discipline.

## `errno` — The Global Error Register

When system functions like `fopen`, `malloc`, or `read` fail, they set a global variable called `errno` to a specific error code. You read it with `<errno.h>`.

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("nonexistent.txt", "r");
    if (fp == NULL) {
        printf("Error code: %d\n", errno);             // e.g., 2
        printf("Error text: %s\n", strerror(errno));    // "No such file or directory"
        perror("fopen");  // Prints: "fopen: No such file or directory"
        return EXIT_FAILURE;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
```

## Common `errno` Values

| Code | Name | Meaning |
|------|------|---------|
| 2 | `ENOENT` | No such file or directory |
| 13 | `EACCES` | Permission denied |
| 12 | `ENOMEM` | Out of memory |
| 22 | `EINVAL` | Invalid argument |

## Pattern 1: Return Codes

The POSIX convention: return `0` for success, `-1` for error. The caller checks `errno` for details.

```c
int load_config(const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) return -1;  // Caller checks errno.
    // ... read config ...
    fclose(fp);
    return 0;
}
```

## Pattern 2: Cleanup with `goto` (The C Idiom)

In C, `goto` is **not** a code smell — it's the idiomatic way to handle multi-resource cleanup:

```c
int process_file(const char *path) {
    int result = -1;
    FILE *fp = NULL;
    char *buffer = NULL;

    fp = fopen(path, "r");
    if (fp == NULL) goto cleanup;

    buffer = malloc(4096);
    if (buffer == NULL) goto cleanup;

    // ... do work ...
    result = 0;  // Success!

cleanup:
    free(buffer);       // free(NULL) is safe.
    if (fp) fclose(fp);
    return result;
}
```

## Pattern 3: Custom Error Enums

```c
typedef enum {
    ERR_OK = 0,
    ERR_FILE_NOT_FOUND,
    ERR_OUT_OF_MEMORY,
    ERR_INVALID_FORMAT
} ErrorCode;

const char *error_to_string(ErrorCode err) {
    switch (err) {
        case ERR_OK:             return "Success";
        case ERR_FILE_NOT_FOUND: return "File not found";
        case ERR_OUT_OF_MEMORY:  return "Out of memory";
        case ERR_INVALID_FORMAT: return "Invalid format";
        default:                 return "Unknown error";
    }
}
```

## Signal Handling (Ctrl+C)

Signals are asynchronous OS-level interrupts. `SIGINT` fires when the user hits Ctrl+C.

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t running = 1;

void handle_sigint(int sig) {
    (void)sig;
    running = 0;
}

int main(void) {
    signal(SIGINT, handle_sigint);
    while (running) {
        printf("Working... Ctrl+C to stop.\n");
        sleep(1);
    }
    printf("Graceful shutdown complete.\n");
    return 0;
}
```

> **GTK Note:** GTK applications use `g_unix_signal_add()` instead of raw `signal()` to integrate with the GLib main loop.
