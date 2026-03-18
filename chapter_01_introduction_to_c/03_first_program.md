# 1.3 Your First C Program

Time to get your hands dirty. We're going to write the time-honored "Hello, World!" program. It's a rite of passage. Let's write it, tear it apart, and see what makes it tick.

```c
#include <stdio.h>   // 1. the preprocessor directive

int main(void) {     // 2. the entry point
    printf("Hello, Unix World!\n");  // 3. the payload
    return 0;        // 4. the exit code
}
```

## The Anatomy of the Beast

### `#include <stdio.h>`
- **What it does**: Tells the preprocessor to go find `stdio.h` (Standard Input/Output) and paste its contents right here.
- **Why**: Without it, your compiler has no idea what `printf()` is. It allows us to access functions written by the bearded Unix gurus of the 70s.

### `int main(void)`
- **`int`**: The function's return type. You return an integer back to the Operating System.
- **`main`**: The absolute starting point of execution. The OS calls this function to start your app.
- **`void`**: Just means we aren't accepting any command-line arguments (yet).

### `printf("Hello, Unix World!\n");`
- **`printf`**: Print Formatted. It pushes text to `stdout` (standard output).
- **`\n`**: The newline escape sequence. Always end terminal prints with a newline, or your shell prompt will get mangled on the same line.
- **`;`**: The semicolon. C's statement terminator. Forgetting this is a rite of passage.

### `return 0;`
- **The Exit Status**: You are telling the Linux/Unix shell "I finished successfully." A non-zero return (like `return 1;`) means something went critically wrong.

## Firing It Up

Save it as `hello.c`, then hit the terminal:

```bash
# Compile the code like a pro
gcc -Wall -Wextra -std=c11 hello.c -o hello

# Execute the binary
./hello

# Check the exit status in bash!
echo $?
# Output: 0
```

## Professional Compilation Flags

I already mentioned them, but I'll say it again. If you compile with just `gcc hello.c`, you're flying blind.

- **`-Wall`**: Enable all warnings. 
- **`-Wextra`**: Enable extra warnings. Be paranoid. Paranoia catches bugs.
- **`-std=c11`**: Tell the compiler to use modern C11 rules.

## What Happens When You Break It?

Let's intentionally break things so you know what compiler screams look like.

### Missing Semicolon
```c
int main(void) {
    printf("Hello, World!\n")  // Oops!
    return 0;
}
```
**The Compiler Says:** `error: expected ';' before 'return'`

### Missing Header
```c
// I forgot #include <stdio.h>
int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```
**The Compiler Says:** `warning: implicit declaration of function 'printf'` (Translation: "I guess printf exists somewhere, but I don't know what it looks like!")

## A Glimpse of the Future: GTK

When we graduate to GTK apps later, the skeleton looks almost identical, just swapped out for GUI code:

```c
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);  // Fire up the graphical engine
    
    // ... UI setup goes here ...
    
    return 0; // Return to the OS
}
```

Same philosophy. Setup, execute, exit cleanly. Now, write the code, compile it, and make sure it runs before moving on.
