# 22.1 Ownership: Rust's Masterpiece

In C, memory management is entirely your problem. You call `malloc()` to grab memory from the OS, and you *must* remember to call `free()` when you're done. If you forget, your server crashes from a memory leak. If you call `free()` twice, you get a double-free security vulnerability.

Languages like Java or Python use a **Garbage Collector (GC)**—a background program that constantly scans memory looking for variables you aren't using anymore. It's safe, but it's slow and unpredictable.

Rust uses **Ownership**. It is the reason Rust is famous. It provides the speed of C with the safety of Java.

## The Three Rules of Ownership

Memorize these. They govern everything in Rust:
1. Each value in Rust has a variable that’s called its **owner**.
2. There can only be **one owner at a time**.
3. When the owner goes out of scope, the value will be **dropped** (freed automatically).

## How it works in Practice

Let's look at the Heap (dynamic memory). In C, this is `malloc`. In Rust, we use types like `String`.

```rust
fn main() {
    {
        // 's' becomes the OWNER of this block of heap memory.
        let s = String::from("hello"); 
        println!("{}", s);
    } 
    // Scope ends here. 
    // Rust automatically calls `drop(s)`, instantly freeing the heap memory.
}
```

## Move Semantics (The End of Double-Frees)

What happens if we assign one heap variable to another? 

In C:
```c
char *s1 = strdup("hello");
char *s2 = s1; // Both pointers now point to the exact same heap memory.
free(s1);      // s2 is now a dangling pointer!
```

In Rust, because of **Rule 2** (only one owner at a time), assigning `s1` to `s2` doesn't just copy the pointer. It **Moves** the ownership entirely.

```rust
fn main() {
    let s1 = String::from("hello");
    let s2 = s1; // Ownership MOVES to s2.

    // s1 has been stripped of its ownership. It is now completely invalid!
    // println!("{}", s1); // ❌ COMPILER ERROR: "borrow of moved value"
    
    println!("{}", s2); // ✅ OK
}
```
Because `s1` is marked invalid by the compiler, when the program ends, Rust will only free `s2`. Double-free prevented at compile time!

## Deep Copies vs. Stack Copies

If you truly want two separate copies of a `String` on the heap, you must explicitly ask for it:
```rust
let s1 = String::from("hello");
let s2 = s1.clone(); // Allocates brand new heap memory
```

But wait, why did this work back in Chapter 21?
```rust
let x = 5;
let y = x;
println!("x: {}, y: {}", x, y); // This works fine!
```
Because simple, fixed-size variables (integers, floats, booleans) live entirely on the **Stack**. There is no heap memory to manage, so Rust simply copies the bits. These are called `Copy` types.
