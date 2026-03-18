# 24.2 Collections: Vec and HashMap

In C, we have static arrays. If we want a dynamic array, we resort to `malloc`, `realloc`, and manual memory sizing.

In Rust, the Standard Library provides incredibly robust, dynamically sized collections.

## `Vec<T>`: The Dynamic Array

A `Vec` (Vector) is a growable array allocated on the heap. It is the direct replacement for doing `malloc` and `realloc` in C.

```rust
fn main() {
    // 1. Create an empty Mutable Vector
    let mut numbers: Vec<i32> = Vec::new();
    
    // 2. Add elements
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    
    // 3. The `vec!` macro is a shortcut for creating vectors with data
    let mut fruits = vec!["apple", "banana", "cherry"];
    fruits.push("date");

    // 4. Safe Iteration! (Remember, references!)
    // We iterate over `&fruits` to borrow the items.
    for fruit in &fruits {
        println!("I like {}", fruit);
    }
    
    // 5. Safe Access
    // In C, numbers[99] is a Buffer Overflow vulnerability.
    // In Rust, numbers.get(99) returns an Option::None instead!
    match numbers.get(99) {
        Some(num) => println!("Found: {}", num),
        None => println!("Index out of bounds! Crisis averted."),
    }
}
```

## `HashMap<K, V>`: The Dictionary

In C, building a fast lookup table (hash map) meant writing your own hashing algorithms and linked-list collision buckets. In Rust, it is built-in and highly optimized.

```rust
use std::collections::HashMap;

fn main() {
    // 1. Create an empty HashMap
    let mut user_scores: HashMap<String, u32> = HashMap::new();
    
    // 2. Insert Key-Value pairs
    user_scores.insert(String::from("Ayman"), 100);
    user_scores.insert(String::from("Alice"), 85);
    
    // 3. Lookup returns an Option! (Because the key might not exist)
    match user_scores.get("Ayman") {
        Some(score) => println!("Ayman has {} points.", score),
        None => println!("Ayman hasn't played yet."),
    }
    
    // 4. The brilliant `entry().or_insert()` API
    // If "Bob" doesn't exist, insert him with score 50.
    // Either way, it returns a mutable reference to the value so we can update it!
    let bob_score = user_scores.entry(String::from("Bob")).or_insert(50);
    *bob_score += 10; // Dereference pointer to modify it, now Bob has 60!
    
    // 5. Iterate through keys and values
    for (username, score) in &user_scores {
        println!("{}: {}", username, score);
    }
}
```

Between `Vec` and `HashMap`, you cover 99% of data structure needs without ever touching a raw pointer or writing a custom node struct.
