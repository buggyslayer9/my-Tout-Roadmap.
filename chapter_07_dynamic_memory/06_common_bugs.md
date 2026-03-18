# 7.6 The Five Deadly Memory Bugs

These are the five bugs that have caused billions of dollars in security breaches across the history of computing. Every single one of them is a direct result of manual memory management in C.

## 1. Memory Leak
**What**: You `malloc` but never `free`. Memory is orphaned.
```c
void leak(void) {
    int *p = malloc(100 * sizeof(int));
    // Oops, we returned without free(p)!
}
```
**Consequence**: Slow RAM exhaustion. App crashes after hours of runtime.

## 2. Dangling Pointer (Use-After-Free)
**What**: You `free` a block but continue using the pointer.
```c
int *p = malloc(sizeof(int));
*p = 42;
free(p);
printf("%d\n", *p);  // 💀 Undefined behavior! p points to freed memory.
```
**Consequence**: Unpredictable crashes or silent data corruption. This is a major exploit vector.

## 3. Double Free
**What**: You call `free()` twice on the same pointer.
```c
int *p = malloc(sizeof(int));
free(p);
free(p);  // 💀 The allocator's internal bookkeeping is now corrupted.
```
**Consequence**: Heap corruption. Security exploit. Program crash.
**Fix**: Set `p = NULL;` after every `free`. `free(NULL)` is guaranteed safe by the C standard.

## 4. Buffer Overflow
**What**: You write past the end of an allocated block.
```c
int *arr = malloc(5 * sizeof(int));
arr[10] = 999;  // 💀 Writing 20 bytes past the end of your allocation.
```
**Consequence**: Corrupts heap metadata. Can be exploited for remote code execution (the most dangerous class of bug in existence).

## 5. Use Before Initialization
**What**: You read `malloc`ed memory before writing to it. `malloc` does NOT zero memory.
```c
int *p = malloc(sizeof(int));
printf("%d\n", *p);  // Could be 0, could be 7654321. It's garbage.
```
**Fix**: Use `calloc` instead, or explicitly initialize every cell after `malloc`.

## Your Defense Arsenal

| Tool | Platform | Purpose |
|------|----------|---------|
| `valgrind --leak-check=full` | Linux | Detects leaks, use-after-free, double-free |
| `gcc -fsanitize=address` | Linux/macOS | Compile-time instrumentation for buffer overflows |
| `leaks --atExit --` | macOS | Apple's native leak detector |
