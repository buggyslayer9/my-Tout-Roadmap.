# 4.1 The Function Anatomy

If `main()` is the brain of your program, functions are the limbs. Functions allow you to write a piece of code once, give it a name, and reuse it forever. Code reuse is the foundation of sane engineering.

Every function in C has four structural parts:

```c
return_type function_name(parameter_type param1, parameter_type param2) {
    // Function body — the actual algorithmic work happens here
    return value;  // Pushing a value back down the call stack to the caller
}
```

## Dissecting the Four Parts

| Part | Concept | Example |
|------|---------|---------|
| **Return type** | What the function hands back when it finishes. | `int`, `void`, `double`, `char *` |
| **Name** | The unique identifier. Make it a verb. | `calculate_hash`, `open_socket` |
| **Parameters** | The raw materials you feed into the machine. | `(int width, int height)` |
| **Body** | The `{ }` block containing the execution logic. | `{ return width * height; }` |

## Practical Examples

```c
// 1. Takes two ints in, spits one int out.
int add_numbers(int a, int b) {
    return a + b;
}

// 2. Takes absolutely nothing in, spits absolutely nothing out.
void print_banner(void) {
    printf("===================\n");
    printf("   UNIX INITIATED  \n");
    printf("===================\n");
    // Notice there is no return statement here!
}

// 3. Takes a double in, spits a double out.
double calculate_circle_area(double radius) {
    return 3.14159265 * radius * radius;
}
```

## The Abstract Void: `void`

In C, `void` literally means "nothing".
- **`void` Return Type**: The function doesn't give you anything back. If you try to do `int x = print_banner();`, the compiler will scream at you.
- **`void` Parameter List**: `int do_something(void)`. This is explicitly telling the compiler "I take zero arguments". 

> **Veteran Tip**: Why `(void)` instead of just `()`? In C++, `()` means "zero arguments". In classical C, an empty `()` actually means "an unknown number of arguments". Always use `(void)` to tightly secure your function boundaries in C.

## Industry Naming Standards

Don't name your functions `f()` or `do_stuff()`. Be intentional. 
- **Use snake_case**: `parse_header_file` instead of `ParseHeaderFile`.
- **Start with Action Verbs**: `get_`, `set_`, `is_`, `has_`, `find_`, `create_`.
- **Mirror Memory**: If you have an `allocate_buffer()` function, you should build a corresponding `free_buffer()` function.
