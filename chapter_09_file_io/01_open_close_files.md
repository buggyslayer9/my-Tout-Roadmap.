# 9.1 Opening and Closing Files

C interacts with files through a `FILE *` pointer — an opaque handle managed by the operating system. Open a file, get a handle, do your work, close the handle. If you don't close it, the OS may not finish writing data to disk.

## Opening a File: `fopen`

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("data.txt", "r");  // Open for reading.
    
    if (fp == NULL) {
        // perror prints the EXACT system error (e.g., "No such file or directory")
        perror("fopen failed");
        return 1;
    }
    
    // ... read/write operations here ...
    
    fclose(fp);  // ALWAYS close when done.
    return 0;
}
```

## File Mode Reference

| Mode | Operation | Notes |
|------|-----------|-------|
| `"r"` | Read | File must already exist. |
| `"w"` | Write | Creates the file. **Destroys existing content!** |
| `"a"` | Append | Creates or appends without destroying. |
| `"r+"` | Read & Write | File must exist. |
| `"w+"` | Read & Write | Creates or truncates. |
| `"rb"` | Read Binary | For non-text data (structs, images). |
| `"wb"` | Write Binary | For non-text data. |

## The Three Rules

1. **Always check for `NULL`** after `fopen`. The file may not exist, you may lack permissions, or the disk may be full.
2. **Always call `fclose`**. An unclosed file handle can lose buffered data and leak OS resources.
3. **Use `perror()` for error messages.** It automatically appends the system's human-readable error description.
