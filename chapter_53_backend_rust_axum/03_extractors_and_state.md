# 44.3 Extractors and `Arc<Mutex<T>>`

In Chapter 43, we extracted parameters in Express simply by querying `req.params.id`. Since Javascript is dynamic, `req.params.id` is technically a string, but you can blindly cast it `parseInt(req.params.id)`. Sometimes it works, sometimes it evaluates to `NaN` and the entire server crashes.

In Rust, we use **Extractors**.

An Extractor is a strictly typed rust Struct that physically guarantees the data matches the Shape before the route is even allowed to execute.

## 1. Extracting URL Parameters (`Path`)

```rust
use axum::{extract::Path, routing::get, Router};

// We explicitly declare that we expect a `u32` (Unsigned 32-bit Integer)!
// If a hacker types `/users/hello`, the Extractor immediately rejects the TCP packet 
// with a 400 Bad Request before this function ever runs! No logic needed!
async fn get_user(Path(user_id): Path<u32>) -> String {
    format!("Fetching user #{} from the database...", user_id)
}

// In main():
// .route("/users/:id", get(get_user))
```

## 2. Extracting JSON Payloads

Because Rust relies natively on the famous `serde` (Serialize/Deserialize) macro, validating incoming POST body JSON is flawlessly secure.

```rust
use axum::{extract::Json, routing::post};
use serde::Deserialize;

// We define the Exact Shape we demand from the Client
#[derive(Deserialize)]
struct CreateUserPayload {
    username: String,
    age: u8,
}

// If the Client sends {"username": 55}, Serde strictly REJECTS the TCP Packet automatically!
async fn create_user(
    // We Extract the violently-guarded Json payload into our typed Struct
    Json(payload): Json<CreateUserPayload>
) -> String {
    format!("Successfully registered {} string (Age {})", payload.username, payload.age)
}
```

## 3. Shared State (`Arc<Mutex<T>>`)

In Express, you can define a global array `let books = []` at the top of the file. Every route can read and write to it. It is perfectly safe because Node.js is Single-Threaded.

In Rust Axum, requests are evaluated concurrently across 16 different OS Threads on your 16-Core server.

If Thread 1 tries to `.push()` to a global `Vec` at the exact microscopic millisecond that Thread 2 tries to `.read()` the Vec, the Linux Kernel triggers a memory corruption Segmentation Fault.

The Rust Borrow Checker literally makes compiling a naked global Vector illegal.

To share state safely across 16 CPU cores, we must wrap our Array in an `Arc` (Atomic Reference Counted pointer) and a `Mutex` (Mutual Exclusion Lock - see Chapter 26!).

```rust
use std::sync::{Arc, Mutex};
use axum::extract::State;

// Define a strictly typed custom struct containing the Thread-Safe Array
type Database = Arc<Mutex<Vec<String>>>;

async fn add_book(
    // Extract the Shared Memory globally from Axum!
    State(db): State<Database>,
    book_name: String
) {
    // We violently LOCK the Mutex to block all other 15 CPU cores temporarily!
    let mut locked_array = db.lock().unwrap();
    locked_array.push(book_name);
} // The Mutex instantly Unlocks when 'locked_array' goes out of scope here!

#[tokio::main]
async fn main() {
    let global_db = Arc::new(Mutex::new(Vec::new()));
    
    let app = Router::new()
        .route("/books", post(add_book))
        // We inject the RAM safely into the Router!
        .with_state(global_db);
}
```
This paradigm is why Rust backends never crash.
