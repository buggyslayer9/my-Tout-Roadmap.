# 26.2 Asynchronous Rust (`async` / `await`)

Threads are great for CPU-heavy tasks. But if your program is doing network I/O (like a web server handling 10,000 connections), spawning 10,000 OS threads will completely exhaust your RAM.

This is where **Asynchronous Rust** comes in. Let's write code that *looks* like synchronous multi-threading, but runs cooperatively on a tiny handful of threads.

## The `async` keyword and Futures

If you put `async` in front of a function, it no longer returns its value immediately. It returns a **Future** (a state machine representing a task that will eventually finish).

To actually run a Future and wait for its result, you use `.await`.

```rust
// This doesn't execute immediately when called.
async fn fetch_data() -> String {
    // Simulate a web request
    String::from("Data downloaded!")
}

async fn run_system() {
    // Call the function. It returns a Future.
    let future = fetch_data();
    
    // Now we actually halt this specific task and yield back to the system
    // until the data is ready.
    let result = future.await; 
    println!("{}", result);
}
```

## The Tokio Runtime

Unlike Go or JavaScript, Rust's standard library **does not** include an async runtime. Rust provides the `async` syntax, but you have to bring your own engine to run it.

The industry standard engine is **Tokio**.

In your `Cargo.toml`:
```toml
[dependencies]
tokio = { version = "1", features = ["full"] }
```

Now we can use Tokio to power our `main` function:

```rust
use tokio::time::{sleep, Duration};

// A macro that wraps main() in the Tokio async runtime
#[tokio::main] 
async fn main() {
    println!("Starting system...");

    // We can spawn "Tasks" (green threads). 
    // These are incredibly lightweight. You can spawn millions of them.
    let task1 = tokio::spawn(async {
        sleep(Duration::from_millis(500)).await; // Async sleep! Does not block the OS thread!
        println!("Task 1 finished");
    });

    let task2 = tokio::spawn(async {
        sleep(Duration::from_millis(200)).await;
        println!("Task 2 finished");
    });

    // Wait for both tasks to complete
    let _ = tokio::join!(task1, task2);
    
    println!("All systems go.");
}
```

When `task1` hits the `sleep().await`, it yields control back to Tokio. Tokio immediately switches to `task2` and starts running it. This cooperative multitasking happens extraordinarily fast, allowing Node.js-tier I/O concurrency with C-tier execution speed.
