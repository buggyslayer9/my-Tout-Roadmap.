# 10.3 Preprocessor Macros

Macros are text substitution rules processed before compilation. They're powerful but dangerous — the preprocessor has zero understanding of C types or syntax. It's a glorified find-and-replace engine.

## Common Useful Macros

```c
// 1. Object-like macro (constant replacement)
#define MAX_BUFFER_SIZE 1024

// 2. Function-like macros
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define SQUARE(x)       ((x) * (x))
#define ARRAY_LEN(arr)  (sizeof(arr) / sizeof((arr)[0]))
```

## The Parenthesization Rule

**Always wrap every parameter and the entire expression in parentheses.** Without them, operator precedence will destroy your logic:

```c
#define BAD_SQUARE(x)  x * x
#define GOOD_SQUARE(x) ((x) * (x))

int result1 = BAD_SQUARE(1 + 2);   // Expands to: 1 + 2 * 1 + 2 = 5 (WRONG!)
int result2 = GOOD_SQUARE(1 + 2);  // Expands to: ((1+2) * (1+2)) = 9 (CORRECT)
```

## Conditional Compilation

```c
#ifdef DEBUG
    printf("Debug: x = %d\n", x);
#endif
```

Compile with: `gcc -DDEBUG program.c` to enable debug prints.

## Multi-line Macros

Use the backslash `\` to continue a macro onto the next line:
```c
#define LOG_ERROR(msg) do { \
    fprintf(stderr, "[ERROR] %s:%d: %s\n", __FILE__, __LINE__, msg); \
} while (0)
```

> **Veteran Advice:** Prefer `const` variables, `enum`, and `inline` functions over macros whenever possible. Macros don't respect scope, can't be debugged, and produce cryptic compiler errors. Use them only for things that *require* preprocessor magic (conditional compilation, `__FILE__`, `__LINE__`).
