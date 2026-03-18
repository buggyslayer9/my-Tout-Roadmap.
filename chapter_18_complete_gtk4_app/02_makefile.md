# 18.2 Build Systems: Makefiles

If you split your C code into four different `.c` files, manually running `gcc main.c app_window.c callbacks.c ...` every time you make a change gets old fast.

A `Makefile` automates the compilation process. It tracks which files changed and only recompiles what's necessary, saving massive amounts of time on large projects.

## A Reliable GTK4 Makefile

Save this as `Makefile` in the root of your project:

```makefile
# 1. Compiler and Flags
CC      = gcc
CFLAGS  = -Wall -Wextra `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`

# 2. Source Files and Targets
# List all your .c files here!
SRC     = src/main.c src/app_window.c src/callbacks.c src/data.c

# Automatically replace .c with .o for object files
OBJ     = $(SRC:.c=.o)
TARGET  = my_app

# 3. Build Rules
# Typing 'make' defaults to the first target ('all')
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

# Compile each .c into an .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Cleanup
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
```

## How to Use It

1. Run `make` to compile the app.
2. Run `./my_app` to test it.
3. Change one line in `src/callbacks.c`.
4. Run `make` again. Notice it *only* recompiles `callbacks.c` and then links the final binary!
5. Run `make clean` to wipe out the compiled binaries and start fresh.

> **Instructor Note:** Makefiles are legendary, but the Linux desktop world is rapidly shifting to **Meson**. We will look at Meson at the end of this chapter. Still, knowing Make is a required skill for any C developer.
