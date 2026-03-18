# 10.7 Debugging with GDB, Valgrind & Sanitizers

Bugs are inevitable. The difference between a junior and a senior developer is how fast they find them. These three tools are your X-ray machines.

## 1. GDB — The GNU Debugger

GDB lets you freeze your program mid-execution, inspect every variable, and step through code one line at a time.

### Setup

```bash
# Compile with -g to embed debug symbols (variable names, line numbers).
gcc -g -Wall -Wextra -std=c11 program.c -o program
gdb ./program
```

### Essential Commands

| Command | Action |
|---------|--------|
| `run` / `r` | Start execution |
| `break main` | Pause at `main()` |
| `break file.c:42` | Pause at line 42 |
| `next` / `n` | Execute next line (skip function internals) |
| `step` / `s` | Step INTO a function call |
| `print x` / `p x` | Display variable `x` |
| `print *ptr` | Dereference and print |
| `print arr[0]@5` | Print 5 array elements starting at index 0 |
| `backtrace` / `bt` | Show the full call stack (invaluable for crashes) |
| `info locals` | Print ALL local variables |
| `watch x` | Break automatically whenever `x` changes |
| `continue` / `c` | Resume execution |
| `quit` / `q` | Exit GDB |

### Debugging a Segfault

```bash
(gdb) run
# Program crashes: SIGSEGV
(gdb) backtrace
# Shows exactly which function and line caused the crash.
(gdb) print ptr
# $1 = (int *) 0x0     ← NULL pointer! Found the bug.
```

---

## 2. Valgrind — The Memory Detective

Valgrind monitors every `malloc` and `free` your program makes and reports any discrepancies.

```bash
gcc -g program.c -o program
valgrind --leak-check=full ./program
```

### What It Catches

| Bug | Example |
|-----|---------|
| Memory leak | `malloc` without `free` |
| Invalid read/write | Accessing freed or out-of-bounds memory |
| Uninitialized value | Reading `malloc`'d memory before writing |
| Double free | `free()` called twice |

### Goal Output (Zero Errors)

```
==12345== All heap blocks were freed -- no leaks are possible
==12345== ERROR SUMMARY: 0 errors from 0 contexts
```

---

## 3. AddressSanitizer (ASan)

ASan is built into GCC/Clang. Faster than Valgrind. Catches bugs at runtime with pinpoint accuracy.

```bash
gcc -g -fsanitize=address -fno-omit-frame-pointer program.c -o program
./program
```

### Other Sanitizers

```bash
gcc -g -fsanitize=undefined program.c -o program   # Catches undefined behavior
gcc -g -fsanitize=thread program.c -o program       # Catches data races
```

---

## The Professional Debugging Workflow

1. **`-Wall -Wextra -Werror`** — Fix all compiler warnings. Most bugs start here.
2. **ASan** (`-fsanitize=address`) — Quick memory sanity check during development.
3. **Valgrind** — Deep leak analysis before shipping.
4. **GDB** — Surgical investigation of specific crashes.
5. **`assert()`** — Declare impossible conditions and crash loud if they occur.

```c
#include <assert.h>
void process(int *data, int count) {
    assert(data != NULL);  // Crash immediately with file:line if NULL.
    assert(count > 0);
}
```
