# 21.3 Control Flow: If and Match

Control flow in Rust will feel familiar, but because Rust is an **expression-based language**, `if` statements and loops are much more powerful than their C counterparts.

## `if` is an Expression

In C, if you wanted to conditionally assign a variable, you used the ugly ternary operator: `int x = (a > b) ? a : b;`

In Rust, `if` evaluates to a value, so you assign it directly:

```rust
fn main() {
    let condition = true;
    
    // This is clean, safe, and readable.
    let number = if condition { 5 } else { 10 };
    
    // Note: Both arms MUST return the same type.
    // let bad = if condition { 5 } else { "hello" }; // ❌ COMPILER ERROR
    
    println!("The number is: {}", number);
}
```

## The Power of `match`

C has `switch`. Rust has `match`. 
However, `switch` is a flimsy construct that easily falls through if you forget a `break` statement. `match` is a rigorous, compile-time verified pattern matching engine.

A `match` block **must be exhaustive**, meaning the compiler forces you to handle every possible value.

```rust
fn process_status(code: u32) {
    match code {
        200 => println!("OK"),
        404 => println!("Not Found"),
        500 => println!("Server Error"),
        // The '_' is the default catch-all. 
        // Try removing it—the compiler will yell at you!
        _   => println!("Unknown status code"), 
    }
}
```

Because `match` is an expression, you can assign variables with it cleanly:

```rust
let grade = 85;

// Matching ranges!
let letter_grade = match grade {
    90..=100 => 'A',
    80..=89  => 'B',
    70..=79  => 'C',
    0..=69   => 'F',
    _        => '?', // Catch-all for invalid numbers like 105
};
```

## Loops: `loop`, `while`, and `for`

Rust has three loop types.

### 1. `loop` (The Infinite Loop)
In C, you write `while(1)`. In Rust, you write `loop`. It communicates your intent clearly to the compiler.

```rust
let mut counter = 0;
// Loops are expressions too! You can break out of them returning a value.
let result = loop {
    counter += 1;
    if counter == 10 {
        break counter * 2; // Return 20
    }
};
```

### 2. `while`
Works exactly like you'd expect.
```rust
let mut n = 3;
while n > 0 {
    println!("{}...", n);
    n -= 1;
}
```

### 3. `for` (The Iterator Workhorse)
You will rarely use `while` in Rust. You will use `for`.
Unlike C's `for (int i=0; i<10; i++)` which is just a glorified `while` loop, Rust's `for` loop consumes **Iterators**. It is infinitely safer because it prevents out-of-bounds array access.

```rust
// Loop over a range (exclusive of 5)
for i in 0..5 {
    println!("Range: {}", i);
}

// Loop over an array safely! 
// No index variables needed, so you can never segfault.
let collection = [10, 20, 30, 40, 50];
for item in collection {
    println!("Value: {}", item);
}
```
