# 26.3 Unsafe Rust and FFI (The C Bridge)

As a veteran C programmer moving to Rust, this is your ultimate superpower. You don't have to rewrite millions of lines of C code into Rust overnight. Rust was specifically designed to interface seamlessly with C.

To do this, we have to bypass Rust's safety guarantees using the `unsafe` keyword.

## The `unsafe` Block

All those memory rules we've spent 5 chapters learning? You can turn them off.

`unsafe` gives you four dangerous powers:
1. Dereference a raw C pointer.
2. Call `unsafe` functions (including C functions).
3. Access or modify mutable static variables.
4. Implement an `unsafe` trait.

```rust
fn main() {
    let my_num = 42;
    
    // Create a raw pointer. Creating it is safe.
    let raw_ptr: *const i32 = &my_num; 

    // DEREFERENCING a raw pointer is highly unsafe.
    // The compiler has no idea if this points to valid memory.
    unsafe {
        println!("Pointer points to: {}", *raw_ptr);
    }
}
```

## Foreign Function Interface (FFI): Rust calling C

Let's say you have a massive legacy C library (`liblegacymath.so`):
```c
// legacy_math.c
int calculate_secret(int a, int b) {
    return (a * b) + 42;
}
```

You can call this directly from Rust with zero overhead:

```rust
// 1. Declare the C function signature
extern "C" {
    fn calculate_secret(a: i32, b: i32) -> i32;
}

fn main() {
    // 2. Calling C is inherently unsafe, so we wrap it in a block.
    // YOU are telling the compiler "Trust me, this C code won't segfault."
    let result = unsafe { calculate_secret(5, 10) };
    
    println!("The C library returned: {}", result);
}
```

## FFI: C calling Rust

You can also write a super-fast, perfectly safe module in Rust, and compile it as a shared `.so` object that your C program can use!

1. Update `Cargo.toml`:
```toml
[lib]
crate-type = ["cdylib"] # Compile to a C Dynamic Library (.so / .dll / .dylib)
```

2. Write the Rust code:
```rust
// src/lib.rs

// #[no_mangle] prevents the Rust compiler from changing the function name,
// so the C linker can find exactly "rust_addition".
#[no_mangle]
pub extern "C" fn rust_addition(a: i32, b: i32) -> i32 {
    // Safe, blazing fast rust logic here
    a + b
}
```

3. Build it with `cargo build --release`.

4. Call it from your main C file!
```c
// main.c
#include <stdio.h>

// Provide the prototype so the C compiler knows it exists
extern int rust_addition(int a, int b);

int main() {
    int sum = rust_addition(100, 50);
    printf("The Rust module calculated: %d\n", sum);
    return 0;
}
```

This interoperability is why Rust is taking over Systems Programming. You can slowly replace components of a C project with Rust, one module at a time.
