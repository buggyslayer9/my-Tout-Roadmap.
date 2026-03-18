# 22.2 References & Borrowing

Ownership is safe, but it can be annoying. If passing a variable to a function transfers ownership (moves the data), we could never comfortably use our variables again!

```rust
fn print_string(s: String) {
    println!("{}", s);
} // s is dropped here!

fn main() {
    let greeting = String::from("hello");
    print_string(greeting); // Ownership moves into the function.
    
    // println!("{}", greeting); // ❌ ERROR! greeting is gone.
}
```

In C, we solved this by passing pointers. In Rust, we use **References**. The act of creating a reference is called **Borrowing**.

## The Immutable Borrow: `&T`

You can let a function *borrow* a value by passing a reference to it using the `&` symbol.

```rust
// The parameter is '&String', a reference to a String.
fn calculate_length(s: &String) -> usize {
    s.len()
} // Scope ends, but because `s` is just a borrowed reference, 
  // the underlying String is NOT dropped!

fn main() {
    let s1 = String::from("hello");
    
    // We pass `&s1` (a reference to s1), not `s1` itself.
    let len = calculate_length(&s1); 
    
    // We still own s1! We can keep using it!
    println!("The length of '{}' is {}.", s1, len);
}
```

References in Rust are guaranteed to always point to valid memory. You cannot create a dangling pointer in Safe Rust.

## The Mutable Borrow: `&mut T`

Normally, borrows are read-only. If you want a function to modify a borrowed value, you must use a **mutable reference**.

```rust
// The parameter is '&mut String'
fn append_world(s: &mut String) {
    s.push_str(", world!");
}

fn main() {
    // 1. The variable itself must be mutable
    let mut greeting = String::from("Hello");
    
    // 2. We pass a mutable reference
    append_world(&mut greeting);
    
    println!("{}", greeting); // "Hello, world!"
}
```

## The Golden Rules of Borrowing

This is the hardest part of Rust for C developers to accept, but it is the reason Rust is inherently thread-safe.

At any given time, you can have *either* one of the following, but not both:
1. **Any number** of immutable references (`&T`). (Multiple readers).
2. **Exactly ONE** mutable reference (`&mut T`). (One writer).

```rust
let mut s = String::from("hello");

let r1 = &s; // ✅ fine
let r2 = &s; // ✅ fine (multiple readers is safe)
println!("{} and {}", r1, r2);

// let r3 = &mut s; // ❌ BIG ERROR! 
// You cannot write to 's' while someone else is actively reading it!
```

This simple rule entirely eliminates **Data Races** at compile time.
