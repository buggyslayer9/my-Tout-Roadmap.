# 24.1 Error Handling: `Result` and the `?` Operator

In C, error handling is a disaster. You call `fopen()`, and if it fails, it returns `NULL`. You call `atoi()`, and if it fails, it returns `0` (which is indistinguishable from actually parsing the number "0"). You check `errno`. You forget to check `errno`. Your program crashes.

Rust fixes this by treating **Errors as Values**. If a function can fail, it returns a `Result<T, E>`.

## Recap: The `Result` Enum

```rust
enum Result<T, E> {
    Ok(T),    // Contains the successful value
    Err(E),   // Contains the error value
}
```

Because it's an enum, you **must** handle it. The compiler literally won't let you use the success value without acknowledging that an error could have occurred.

## Basic Error Handling with `match`

Let's read a file. In C, we'd check for `NULL`. In Rust, `fs::read_to_string` returns a `Result<String, std::io::Error>`.

```rust
use std::fs;

fn main() {
    let result = fs::read_to_string("config.txt");

    match result {
        Ok(text) => println!("File contents: {}", text),
        Err(error) => {
            // Usually, we print error to stderr using eprintln!
            eprintln!("Failed to read file: {}", error);
            // In C we might call exit(1) here
        }
    }
}
```

## The Magic of the `?` Operator

Writing a `match` block every time something can fail gets exhausting. In C, you end up with massive towers of `if (err != 0) return err;`.

Rust introduced the `?` operator to solve exactly this problem. Placed after a function call that returns a `Result`, it does the following:
1. If the result is `Ok(value)`, it unwraps the value and gives it to you.
2. If the result is `Err(e)`, it **immediately returns the error from the current function**.

```rust
use std::fs::File;
use std::io::{self, Read};

// Notice this function RETURNS a Result now!
fn read_username_from_file() -> Result<String, io::Error> {
    // If File::open fails, the '?' returns the error instantly.
    // If it succeeds, 'mut file' becomes the File handle.
    let mut file = File::open("username.txt")?;
    
    let mut username = String::new();
    
    // If reading fails, the '?' returns the error instantly.
    file.read_to_string(&mut username)?;
    
    // If we made it here, wrap the username in Ok() and return it
    Ok(username)
}

fn main() {
    match read_username_from_file() {
        Ok(name) => println!("Logged in as: {}", name),
        Err(e) => println!("Could not log in: {}", e),
    }
}
```

> **Rule of Thumb:** If you are writing a library or a helper function, always return `Result` and use `?`. Let the calling function (usually the UI or `main()`) deal with displaying the error to the user!
