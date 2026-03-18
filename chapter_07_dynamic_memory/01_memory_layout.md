# 7.1 The Memory Layout of a C Program

Before you can allocate memory, you must understand *where* memory exists. When the OS loads your compiled program, it carves RAM into five distinct regions:

```
High Address (e.g., 0xFFFF...)
┌─────────────────────┐
│       STACK         │ ← Local variables, function call frames.
│         ↓           │   Grows DOWNWARD automatically.
│                     │
│         ↑           │
│        HEAP         │ ← Dynamic memory (malloc/calloc/realloc).
│                     │   Grows UPWARD. YOU manage this.
├─────────────────────┤
│        BSS          │ ← Uninitialized global/static variables (zeroed).
├─────────────────────┤
│       DATA          │ ← Initialized global/static variables.
├─────────────────────┤
│       TEXT          │ ← Your compiled machine code (read-only).
Low Address (e.g., 0x0000...)
```

## What Each Region Does

| Region | Managed By | Lifetime | Example |
|--------|-----------|----------|---------|
| **Text** | OS (read-only) | Entire program | Your `main()` function machine code |
| **Data** | Compiler | Entire program | `int global_count = 42;` |
| **BSS** | Compiler | Entire program | `static int counter;` (auto-zeroed) |
| **Heap** | **You** (`malloc`/`free`) | Until you `free()` it | `int *arr = malloc(...)` |
| **Stack** | CPU (automatic) | Until function returns | `int local_var = 5;` |

## The Stack vs The Heap

The **Stack** is automatic, fast, and very small (usually 1–8 MB). Local variables live here and are deleted when the function returns. You cannot return a pointer to a stack variable — it's gone.

The **Heap** is massive (gigabytes), slow compared to the stack, and completely manual. You call `malloc()` to reserve a chunk, and `free()` to release it. If you forget `free()`, you have a memory leak. If you use it after `free()`, you have a use-after-free bug.

> **Veteran Rule:** If you need memory that outlives a function call, put it on the heap. If it's temporary scratch data, use the stack.
