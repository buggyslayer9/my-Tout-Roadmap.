# 3.4 Loops: Doing the Grunt Work

Computers exist to do repetitive, boring math as fast as possible. Loops are the engine. C gives you three flavors. 

## The `while` Loop (Condition First)

Use a `while` loop when you don't know exactly how many times you need to loop, but you know you need to stop when a condition changes.

```c
#include <stdio.h>

int main(void) {
    int power = 1;
    
    // Read this as: "As long as power is less than 1000..."
    while (power < 1000) {
        printf("%d ", power);
        power *= 2; // Multiply by 2.
    }
    printf("\n");
    // Prints: 1 2 4 8 16 32 64 128 256 512
    
    return 0;
}
```

## The `do-while` Loop (Action First, Condition Second)

Use `do-while` when you absolutely guarantee the code inside the loop must run **at least once** before checking the condition. Excellent for parsing user input.

```c
#include <stdio.h>

int main(void) {
    int choice;
    
    // This will ALWAYS run at least once.
    do {
        printf("Enter a positive number (or 0 to quit): ");
        scanf("%d", &choice);
        
        if (choice > 0) {
            printf("You entered: %d\n", choice);
        }
    } while (choice != 0); // Check the condition down here.
    
    return 0;
}
```

## The `for` Loop (The Counter)

Use a `for` loop when you know exactly how many times you are iterating. It packs the setup, the condition, and the incrementer all onto a single, tightly packed line.

```c
#include <stdio.h>

int main(void) {
    // 1. Setup: int i = 0
    // 2. Condition: is i < 10?
    // 3. Execution: Run the block.
    // 4. Increment: i++
    
    for (int i = 0; i < 10; i++) {
        printf("Countdown: %d\n", 10 - i);
    }
    
    printf("Blastoff!\n");
    return 0;
}
```

### The Infinite Loop

Sometimes you want a loop to run forever (like the main event loop of a GTK graphics application!). 

```c
// The classic infinite for-loop
for (;;) {
    // Process GUI events forever.
}

// The classic infinite while-loop
while (1) {
    // Read network sockets forever.
}
```
If you ever execute one of these in your terminal, hit `Ctrl+C` to kill the process dead.
