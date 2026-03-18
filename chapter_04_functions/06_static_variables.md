# 4.6 The Static Keyword: The Persistent Memory

Normally, a local variable gets brutally murdered the moment a function finishes.

```c
void forgetful_counter(void) {
    int count = 0; // Born at 0.
    count++;
    printf("Normal count: %d\n", count); // Dies at 1.
}
```
If you call that function three times, it prints `1`, `1`, `1`.

## Adding `static`

By injecting the `static` keyword, you tell the compiler: "Do not destroy this variable when the function ends. Put it in long-term memory. And by the way, skip the `= 0` initialization on all future calls."

```c
void memory_counter(void) {
    // This line ONLY EXECUTES EXACTLY ONCE across the entire runtime.
    static int count = 0; 
    
    count++;
    printf("Static count: %d\n", count);
}

int main(void) {
    memory_counter(); // Static count: 1
    memory_counter(); // Static count: 2
    memory_counter(); // Static count: 3
    return 0;
}
```

## Why Not Just Use Globals?

`static` variables are beautiful because they give you the persistent memory of a global variable, but with the **security** of a local variable. `main()` has absolutely no ability to look at or mess with `count`. It is entirely boxed inside `memory_counter()`. 

Use `static` when a function needs to track its own historical state.
