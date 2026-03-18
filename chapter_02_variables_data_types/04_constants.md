# 2.4 Constants: Ironclad Values

Sometimes you have a value that should *never* change during runtime. The maximum length of a buffer, the value of Pi, the name of your application.

C gives you two ways to forge constants.

## Method 1: The Preprocessor `#define`

This is the old-school Unix way.

```c
#define PI 3.14159
#define MAX_BUFFER 1024
#define SERVER_NAME "nginx"
```

### How it works:
- **Blind Text Replacement**: Before the compiler even runs, the preprocessor finds every instance of `MAX_BUFFER` in your code and physically replaces it with `1024`.
- **No Memory Used**: Variables take up RAM. Macros do not. They are baked straight into the assembly code.
- **Convention**: Always scream them in `ALL_CAPS`.
- **The Danger**: There is zero type checking. If you type `#define SIZE "10"` and try to do math with `SIZE`, the preprocessor pastes `"10" + 5`, causing bizarre compiler errors.

## Method 2: Typed `const` Variables

This is the safer, modern way.

```c
const double PI = 3.14159265358979;
const int MAX_USERS = 50;
const char *SERVER_NAME = "nginx";
```

### How it works:
- **Type Safety**: The compiler ensures `MAX_USERS` is strictly treated as an integer.
- **Scoping**: A `const` variable follows normal `{ }` scope rules, whereas `#define` pollutes the entire file.

## Method 3: The `enum` Trick

If you need a group of integer constants (like states or error codes), `enum` is the absolute best approach:

```c
enum {
    STATUS_OK = 0,
    STATUS_ERROR = 1,
    MAX_RETRIES = 5
};
```
This gives you type-safe integers that don't take up variable memory in the same way `const int` does.

## The Verdict

1. Need to define an array size? In older C, you had to use `#define`. In modern C, `const` or `enum` works fine.
2. For mathematical values or strings, prefer `const`. It allows your debugger (`gdb`) to actually see the variable name.
3. For flags, states, and groupings of numbers, use `enum`.
