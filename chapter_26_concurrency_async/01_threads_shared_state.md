# 26.1 Fearless Concurrency: Threads and Shared State

In C, multithreading with `pthreads` is a terrifying experience. You spawn threads, pass them `void*` arguments, and pray you remembered to use `pthread_mutex_lock` correctly. If you forget, you get silent data corruption (data races) that are nearly impossible to debug.

Rust famously promises **Fearless Concurrency**. If your multithreaded code compiles, it is mathematically proven to be free of data races.

## Spawning Threads

Spawning a thread in Rust is incredibly simple using a closure:

```rust
use std::thread;
use std::time::Duration;

fn main() {
    let handle = thread::spawn(|| {
        for i in 1..=5 {
            println!("Background thread: {}", i);
            thread::sleep(Duration::from_millis(10));
        }
    }); // The thread starts immediately!

    for i in 1..=3 {
        println!("Main thread: {}", i);
        thread::sleep(Duration::from_millis(10));
    }

    // Wait for the background thread to finish, just like pthread_join
    handle.join().unwrap(); 
}
```

## `move` Closures
If you want a thread to use a variable from the main thread, the background thread must take **Ownership** of it. We use the `move` keyword before the closure.

```rust
let data = vec![1, 2, 3];

let handle = thread::spawn(move || {
    // The thread now OWNS `data`. The main thread can no longer touch it!
    println!("Here's the data: {:?}", data);
});
```

## Shared State: `Mutex` and `Arc`

What if *multiple* threads need to read and write to the same data? We need a Mutex.

In C, a mutex is just a lock floating next to your data. You can completely forget to lock it and still modify the data.
In Rust, the `Mutex<T>` **wraps** the data. You physically cannot access the data without locking the Mutex first.

Furthermore, how do multiple threads own the *same* Mutex? We use an `Arc` (Atomic Reference Counted pointer).

```rust
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    // We wrap our data (0) in a Mutex, and wrap the Mutex in an Arc.
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        // Clone the Arc. This doesn't clone the data, 
        // it just atomically increments the reference count.
        let counter_clone = Arc::clone(&counter);
        
        let handle = thread::spawn(move || {
            // 1. Lock the mutex. If another thread has it, this blocks.
            // 2. unwrap() handles the case where a thread panicked while holding the lock.
            // 3. `num` is a mutable reference to the data inside!
            let mut num = counter_clone.lock().unwrap();
            
            *num += 1;
            
            // The lock is AUTOMATICALLY released here when `num` goes out of scope!
        });
        handles.push(handle);
    }

    // Wait for all 10 threads to finish
    for handle in handles {
        handle.join().unwrap();
    }

    // Print final result
    println!("Final Counter: {}", *counter.lock().unwrap()); // Guaranteed to be 10
}
```

This is the holy grail. The compiler forces you to lock the data, and the scope automatically unlocks it. You can't mess it up.
