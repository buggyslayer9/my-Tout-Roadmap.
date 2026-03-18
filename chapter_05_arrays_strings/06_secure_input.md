# 5.6 Secure Input: Surviving the Buffer Overflow

The single biggest vulnerability in computing history is the Buffer Overflow. It happens when a user types more characters than an array is physically designated to hold.

Functions like `scanf("%s", name)` are **notorious**. They do not limit how many characters they read. They just keep writing what the user typed into memory until they hit a space or newline.

## The `scanf` Death Trap

```c
char name[10];
// 💀 DANGER: If the user types "AlexandrosTheGreat", 
// scanf will blindly write all 18 characters!
// The first 9 go into the 'name' array. 
// The next 9 write over whatever random variables exist next to it in RAM.
scanf("%s", name);  
```

## The Width Limit Bandaid

You can partially fix `scanf` by hardcoding a width limit right into the format string. The limit must always be **1 byte smaller** than the array size, to leave room for the `\0` null terminator.

```c
char name[50];
// Reads at most 49 characters. Safe from overflows.
scanf("%49s", name);  
```
However, **`scanf("%s")` stops dead the millisecond it sees a Space character.** If the user types "John Doe", `name` only holds "John". The " Doe" gets stuck in the invisible keyboard buffer, waiting to corrupt your next `scanf` call.

## The Professional Standard: `fgets`

Veterans read strings using `fgets()`. `fgets` is a fortress. It guarantees buffer safety, and it happily reads spaces.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char input[100];

    printf("Enter your full name: ");
    
    // 1. Where to save it? (input)
    // 2. What is the absolute max size? (sizeof(input) prevents overflows!)
    // 3. Where is it coming from? (stdin means Standard Input / Keyboard)
    if (fgets(input, sizeof(input), stdin) != NULL) {
        
        // FGETS QUIRK: It captures the "Enter" key (\n) the user pressed!
        // We must strip it out before using the string.
        input[strcspn(input, "\n")] = '\0';
        
        printf("Hello, %s!\n", input);
    }
    
    return 0; // Notice how much more robust this feels.
}
```

## Parsing Numbers the Unix Way

Do not use `scanf("%d")`. It leaves invisible newline `\n` characters in the keyboard buffer that will randomly skip your future `fgets` prompts. 

For robust, production-grade applications: **Read everything as a string with `fgets`, then convert it.**

```c
#include <stdio.h>
#include <stdlib.h> // Required for strtol

int main(void) {
    char buf[64];
    printf("Enter your age: ");
    
    // 1. Slurp the whole line as text.
    fgets(buf, sizeof(buf), stdin);
    
    // 2. Parse the text into a long integer using strtol (String To Long).
    // Base 10 means standard decimal numbering.
    char *end_pointer;
    long age = strtol(buf, &end_pointer, 10);
    
    // 3. Error Checking: Did strtol actually find any numbers?
    if (end_pointer == buf) {
        printf("Error: That was not a number.\n");
    } else {
        printf("You are %ld years old.\n", age);
    }
}
```

This is the bedrock of C systems programming. Never trust user input. Never trust `scanf`. Build fortresses with `fgets`.
