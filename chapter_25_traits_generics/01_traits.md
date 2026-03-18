# 25.1 Traits: Rust's Answer to Interfaces and Inheritance

In C++, you use Object-Oriented Programming (OOP) and Inheritance (`class Dog : public Animal`) to share behavior. C doesn't have OOP, so you often use function pointers inside structs to fake it.

Rust entirely rejects traditional Inheritance. Instead, it uses **Traits**. 

A Trait is a collection of methods defined for an unknown type: `Self`. They are exactly like `Interfaces` in Java or C#, but far more powerful.

## Defining and Implementing a Trait

Let's define a behavior that any struct can choose to support.

```rust
// 1. Define the Trait
trait Summary {
    // Any type implementing `Summary` MUST provide this method.
    fn summarize(&self) -> String;
    
    // Traits can also have default implementations!
    // Types can override this, or just use the default.
    fn author(&self) -> String {
        String::from("Unknown Author")
    }
}

// 2. Define our Data (Structs)
struct NewsArticle {
    headline: String,
    writer: String,
}

struct Tweet {
    username: String,
    content: String,
}

// 3. Implement the Trait for the Structs
impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("Breaking: {} by {}", self.headline, self.writer)
    }
    
    // We optionally override the default author method
    fn author(&self) -> String {
        self.writer.clone()
    }
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
    // We don't override `author()`, so it uses "Unknown Author"
}

fn main() {
    let tweet = Tweet {
        username: String::from("horse_ebooks"),
        content: String::from("of course, as you know, all horses are experts"),
    };
    
    println!("1 new tweet: {}", tweet.summarize());
    println!("By: {}", tweet.author());
}
```

## Traits as Parameters (`box dyn Trait`)

How do we write a function that accepts *anything* that implements `Summary`? 

In C, you'd pass a `void*` and pray. In Rust, you use **Trait Objects**. Because different structs have different sizes in memory, if we want to put them in a `Vec` or pass them generically, we must put them on the heap using a `Box`.

```rust
// 'dyn Summary' means "Dynamically dispatched Summary trait"
// 'Box' allocates it on the heap, giving it a known, fixed size (a pointer size).
fn print_summary(item: &Box<dyn Summary>) {
    println!("{}", item.summarize());
}

fn main() {
    let article = Box::new(NewsArticle { /* ... */ });
    let tweet = Box::new(Tweet { /* ... */ });
    
    // We can put entirely different structs in the same Vector!
    let feed: Vec<Box<dyn Summary>> = vec![article, tweet];
    
    for item in feed {
        print_summary(&item);
    }
}
```
This is the Rust equivalent of Polymorphism, and it is entirely memory-safe.
