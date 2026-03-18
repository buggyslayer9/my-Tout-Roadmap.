# 10.8 Makefiles: Automating the Build

Typing `gcc -Wall -Wextra -g -std=c11 main.c student.c utils.c network.c -o app $(pkg-config --cflags --libs gtk4)` every time you change a file is insanity. A **Makefile** automates your entire build process with a single command: `make`.

## A Minimal Makefile

Create a file named exactly `Makefile` (capital M, no extension) in your project root:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
TARGET = my_program

all: $(TARGET)

$(TARGET): main.c utils.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c utils.c

clean:
	rm -f $(TARGET)
```

> **⚠️ CRITICAL:** The indentation before `$(CC)` and `rm` **MUST be a real TAB character** (`\t`), not spaces. If you use spaces, Make will print `*** missing separator` and refuse to work.

## The Professional Makefile (Object Files)

For real projects, you compile each `.c` into a `.o` object file first, then link them. This way, `make` only recompiles files that actually changed.

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`
TARGET = my_gtk_app

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
```

## Usage

```bash
make          # Build the project
make clean    # Delete all compiled files
make -j4      # Build using 4 CPU cores in parallel (FAST!)
```

## The Auto-Variable Cheat Sheet

| Variable | Meaning |
|----------|---------|
| `$@` | The target being built |
| `$<` | The first prerequisite |
| `$^` | All prerequisites |
