# 3.5 The Loop Controllers: break and continue

Sometimes the loop logic is sound, but an emergency or an edge case happens inside the block. C gives you two rip-cords to manipulate the flow directly.

## `break`: The Emergency Exit

When the compiler hits a `break;` statement, it instantly terminates the loop entirely and continues executing the code beneath the loop block.

```c
#include <stdio.h>

int main(void) {
    for (int i = 1; i <= 100; i++) {
        printf("Processing item %d...\n", i);
        
        if (i == 5) {
            printf("Critical error detected! Aborting loop!\n");
            break; // IMMEDIATELY escape the loop. 6 through 100 will never run.
        }
    }
    
    printf("Loop complete.\n");
    return 0;
}
```

## `continue`: The "Skip this iteration" Button

When the compiler hits a `continue;` statement, it instantly stops processing the *current* iteration, skips everything below it in the block, jumps back up to the top of the loop, increments the counter, and starts the next iteration.

```c
#include <stdio.h>

int main(void) {
    printf("Odd numbers only:\n");
    
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue; // Oh, it's an even number? Skip it and go to the next 'i'.
        }
        
        // This line only runs for odd numbers!
        printf("%d ", i); 
    }
    printf("\n");
    
    return 0;
}
```

## Use Cases in GTK and Systems Programming

- Use `break` when searching a massive array for a specific item. Once you find it, there's no reason to keep searching. `break` out of the loop and save CPU cycles.
- Use `continue` when parsing a messy file. Did you read a blank line or a comment line? Just `continue;` to jump straight to reading the next line without processing the junk.
