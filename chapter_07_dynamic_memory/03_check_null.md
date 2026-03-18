# 7.3 Always Check for NULL

`malloc`, `calloc`, and `realloc` all return `NULL` when memory allocation fails. If you skip the check and blindly dereference the returned pointer, your program crashes with a segfault.

## The Non-Negotiable Pattern

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *buffer = malloc(1000 * sizeof(int));
    
    if (buffer == NULL) {
        fprintf(stderr, "FATAL: Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    
    // Now it's safe to use.
    buffer[0] = 42;
    
    free(buffer);
    buffer = NULL;
    return 0;
}
```

## Two Error-Handling Strategies

| Strategy | Use When |
|----------|----------|
| `exit(EXIT_FAILURE)` | The allocation is critical. The program cannot function without this memory. Bail out immediately. |
| `return NULL` | The caller can potentially handle the failure gracefully — retry, use a fallback, or display an error to the user. |

## Example: A Safe String Duplicator

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicate_string(const char *src) {
    if (src == NULL) return NULL;
    
    size_t len = strlen(src) + 1;  // +1 for the null terminator
    char *copy = malloc(len);
    
    if (copy == NULL) {
        fprintf(stderr, "malloc failed for %zu bytes\n", len);
        return NULL;  // Let the caller decide what to do.
    }
    
    memcpy(copy, src, len);
    return copy;  // Caller is now responsible for free()ing this!
}

int main(void) {
    char *name = duplicate_string("Bugslayer");
    if (name == NULL) {
        return EXIT_FAILURE;
    }
    
    printf("Name: %s\n", name);
    free(name);
    return EXIT_SUCCESS;
}
```

## The `realloc` Special Case

`realloc` is uniquely dangerous: if it fails, it returns `NULL` but the **original block is still valid and allocated**. You must use a temporary pointer:

```c
int *temp = realloc(arr, new_size * sizeof(int));
if (temp == NULL) {
    fprintf(stderr, "realloc failed — original data preserved.\n");
    // 'arr' is still valid here! Don't lose it.
} else {
    arr = temp;  // Only update on success.
}
```
