# 23.3 The Billion Dollar Mistake: `Option` and `Result`

Tony Hoare, the inventor of the Null Reference, famously called it his "Billion Dollar Mistake" because of the countless crashes, security holes, and hours lost to `NullPointerExceptions` and Segfaults.

**Rust does not have Null.**

Instead, it relies entirely on its powerful Enums to represent the concept of "Nothing" or "Error".

## 1. `Option<T>` (The Null Replacement)

Whenever a value might be missing, Rust uses a built-in generic enum called `Option`. 

```rust
// The <T> means it's Generic. It can hold any type of data.
enum Option<T> {
    None,       // The value does not exist (like NULL)
    Some(T),    // The value exists, and here it is
}
```

Because `Option` is an enum, the compiler forces you to use `match` to extract the `Some` value. It is physically impossible to accidentally use a `None` value as if it were valid data.

```rust
fn find_user_id(name: &str) -> Option<u32> {
    if name == "Ayman" {
        Some(1001) // We found it, wrap it in Some
    } else {
        None       // Not found
    }
}

fn main() {
    let result = find_user_id("Admin");

    // The compiler FORCES us to check if it's None. No segfaults allowed.
    match result {
        Some(id) => println!("Logged in with ID: {}", id),
        None     => println!("User not found. Try again."),
    }
}
```

### The `if let` Shortcut
If you only care about the `Some` case and want to ignore `None`, using a full `match` block is annoying. Use `if let` instead:

```rust
if let Some(id) = find_user_id("Ayman") {
    println!("Found Ayman's ID quickly: {}", id);
}
```

## 2. `Result<T, E>` (The Error Replacement)

In C, functions return `-1` to indicate an error, and you had to check global variables like `errno` to find out *what* went wrong. It's a terrible system.

Rust uses the `Result` enum:

```rust
enum Result<T, E> {
    Ok(T),    // Success! Contains the payload of type T
    Err(E),   // Failure! Contains the error payload of type E
}
```

If a function can fail (like opening a file or parsing an integer), it must return a `Result`.

```rust
fn main() {
    // Attempt to parse a string into a number
    let parse_result = "42a".parse::<i32>();
    
    match parse_result {
        Ok(number) => println!("Yay, the number is {}", number),
        Err(error) => println!("Uh oh, failed to parse: {}", error),
    }
}
```
If you forget to handle the `Err` case, your code won't compile (or at best, will give you a very angry warning). You must explicitly acknowledge that operations can fail. 

We will explore `Result` and error handling deeply in Chapter 24.
