# 21.2 Variables, Types, and the Immutable Default

In C, you had to explicitly type `const` to prevent a variable from changing. 

In Rust, the philosophy is flipped: **Everything is immutable by default.** If you want to change a variable, you must explicitly ask the compiler for permission.

## Mutability

```rust
fn main() {
    let x = 5;       // This is completely immutable.
    // x = 6;        // ❌ COMPILER ERROR! You cannot reassign 'x'.

    let mut y = 10;  // The 'mut' keyword makes it mutable.
    y = 20;          // ✅ Perfectly fine.
    
    println!("x is {}, y is {}", x, y);
}
```

Why? Because immutable data is predictable and inherently safe to share across multiple threads.

### Shadowing
Rust allows you to *shadow* variables by reusing the `let` keyword. This is not reassigning; it is creating a brand new variable that hides the old one.

```rust
let spaces = "   ";          // spaces is a string slice
let spaces = spaces.len();   // Shadowed! spaces is now an integer: 3
```
This is a standard Rust pattern to avoid coming up with bad variable names like `spaces_str` and `spaces_num`.

## Explicit yet Inferred Types

In C, you type `int num = 5;`. Rust is statically typed like C, but it has **Type Inference**. The compiler is smart enough to know that `let num = 5;` is an integer. 

But when you *need* to be explicit, here is how Rust sizes its types (notice how much clearer they are than C's vague `short`, `long`, `long long`):

```rust
fn main() {
    // Exactly sized integers
    let a: i32 = -42;       // 32-bit signed (The default integer type)
    let b: u8 = 255;        // 8-bit unsigned (perfect for bytes)
    let c: i64 = 1_000_000; // You can use underscores for readability!
    
    // Pointer-sized integer (like size_t in C)
    let size: usize = 128;  // 64-bit on a 64-bit OS, 32-bit on a 32-bit OS
    
    // Floats
    let pi: f64 = 3.14159;  // 64-bit float (default)
    
    // Boolean
    let is_active: bool = true;
    
    // Character: Warning! Rust chars are 4-byte Unicode scalars.
    // They are NOT 1-byte ASCII like C chars.
    let emoji: char = '🦀';
}
```

## Functions and Expressions

Functions are declared with `fn`. The arrows `->` specify the return type.

Here is the most important syntax rule in Rust: **Statements do things, Expressions evaluate to values.**

```rust
// Basic function
fn add_numbers(x: i32, y: i32) -> i32 {
    let sum = x + y; // This is a STATEMENT. It ends with a semicolon.
    
    sum // This is an EXPRESSION. No semicolon! It returns the value.
    
    // Note: You *can* write `return sum;`, but idiomatic Rust omits 
    // the `return` keyword and the semicolon for the final expression.
}

// Function that returns "Nothing" (In C this is `void`. In Rust it is the Unit type `()`)
fn greet(name: &str) {
    println!("Welcome to the system, {}!", name);
}

fn main() {
    let result = add_numbers(10, 5);
    greet("Admin");
}
```

If you ever see a compiler error saying "expected `()`, found `i32`", it's almost always because you accidentally put a semicolon at the end of the line you meant to return!
