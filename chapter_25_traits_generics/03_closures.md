# 25.3 Closures: Anonymous Functions

A **Closure** is an anonymous function that can be saved in a variable or passed as an argument to other functions. 

In C, we use Function Pointers for this (like passing a comparison function to `qsort`). However, C function pointers cannot access variables outside their own scope. 

Rust Closures can **capture their environment**.

## Basic Syntax

Closures use pipes `|...|` instead of parentheses for their parameters.

```rust
fn main() {
    // 1. A standard function
    fn add_one_func(x: i32) -> i32 { x + 1 }
    
    // 2. A closure (Type inference allows us to drop the types!)
    let add_one_closure = |x| x + 1;
    
    // 3. A multi-line closure
    let do_math = |x: i32, y: i32| -> i32 {
        let sum = x + y;
        sum * 2
    };

    println!("Closure result: {}", add_one_closure(5)); // Prints 6
}
```

## Capturing the Environment

This is where Closures shine and C function pointers fail. A closure can reach out and borrow variables from the function it is defined inside!

```rust
fn main() {
    let threshold = 10;
    
    // This closure captures the `threshold` variable from `main`!
    let is_above_threshold = |num| num > threshold;
    
    println!("Is 15 above? {}", is_above_threshold(15)); // true
}
```

## Closures in Practice: Iterator Chaining

Closures are the secret weapon of Rust's `Iterator` pattern. Instead of writing `for` loops with manual counters and `if` statements, you chain iterator methods together and pass them closures.

```rust
fn main() {
    let numbers = vec![1, 2, 3, 4, 5, 6];
    
    // We want to filter out odd numbers, then double the remaining evens.
    
    let doubled_evens: Vec<i32> = numbers
        .into_iter()                     // 1. Turn the Vec into an Iterator
        .filter(|x| x % 2 == 0)          // 2. Keep only evens (Closure returning bool)
        .map(|x| x * 2)                  // 3. Multiply by 2 (Closure mutating value)
        .collect();                      // 4. Gather the results back into a new Vec
        
    println!("{:?}", doubled_evens); // [4, 8, 12]
}
```

This functional approach is incredibly fast in Rust, because the compiler optimizes away all the intermediate steps. It compiles down to exactly the same machine code as a highly optimized C `for` loop!
