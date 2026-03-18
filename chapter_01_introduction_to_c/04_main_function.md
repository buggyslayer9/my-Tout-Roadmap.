# 1.4 The Main Event: main() and Command Line Arguments

Every single C program requires exactly one `main()` function. This is where your code physically begins executing. But `main()` can be driven like an automatic or a manual. Let's look at the manual transmission so we can get command-line arguments.

## The Two Faces of main()

```c
// Form 1: The Automatic (No command-line arguments)
int main(void) { 
    return 0;
}

// Form 2: The Manual (With command-line arguments)  
int main(int argc, char *argv[]) {
    return 0;
}
```

In the Unix world, command-line arguments are king. `ls -l /tmp`. `cat file.txt`. Those flags and paths are passed into the C program via `argc` and `argv`. 

GTK applications **demand** the second form. If you double-click a file to open it, the desktop environment passes the file path to your app via `argv`.

## Breaking Down argc and argv

- **`argc` (Argument Count)**: An integer representing how many things were typed on the command line.
- **`argv` (Argument Vector)**: An array of strings (`char *`). These are the actual words typed on the command line.

### Important Rules to Memorize:
1. `argv[0]` is **always** the name of the program itself.
2. As a result, `argc` is **always at least 1**.
3. `argv[argc]` is always a `NULL` pointer.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("You fired this up with %d arguments:\n", argc);
    
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    
    return 0;
}
```

Compile it and hit it with some arguments:
```bash
$ ./myapp hello world --verbose
You fired this up with 4 arguments:
argv[0] = ./myapp
argv[1] = hello
argv[2] = world
argv[3] = --verbose
```

## Why GTK Cares About Your Arguments

GTK has its own hidden command-line flags. When you initialize GTK, you pass it `argc` and `argv`. GTK scans them, strips out any GTK-specific flags (like `--gdk-debug`), and leaves your personal app arguments behind.

```c
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    
    // Hand over the arguments to GTK.
    // GTK filters out its own flags, updating argc and argv!
    gtk_init(&argc, &argv);  
    
    // Now you can parse whatever is left...
    
    return 0;
}
```

## Defensive Programming: Don't Crash

The quickest way to get a `Segmentation Fault` (a memory crash) is reading `argv[1]` when the user didn't provide any arguments.

```c
// THE ROOKIE WAY: CRASH IMMINENT
int main(int argc, char *argv[]) {
    printf("Opening file: %s\n", argv[1]); // Crash if argc is 1!
    return 0;
}

// THE VETERAN WAY: GATES CLOSED
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; // Return non-zero to denote failure!
    }
    
    printf("Opening file: %s\n", argv[1]);
    return 0;
}
```

## Return Values Matter

A quick refresher on the `return` statement in `main`:
When you return, you are talking to the shell (`bash`, `zsh`, `fish`).

```c
return 0;     // "Everything is fine, I did my job."
return 1;     // "General failure. Abort."
return 2;     // "Error: Missing arguments."
```

In bash, you can check this with `$?`:
```bash
./myprogram
if [ $? -ne 0 ]; then
    echo "Wait, the C program failed! Send alerts!"
fi
```

Parse your arguments carefully, validate the user's input, and always return clear error codes. Welcome to systems programming.
