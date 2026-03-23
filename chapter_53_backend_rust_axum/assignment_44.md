# Assignment 44: The Rust Axum API

In Assignment 43, you built an Express server that managed an in-memory CRUD database of Books.

Your task is to re-write that exact same API in Rust using `axum` to guarantee complete memory safety, zero data races, and 10x the execution speed.

## 1. Project Initialization

1. Open your terminal: `cargo new rust-api`
2. Open `Cargo.toml`. Add these precise dependencies:
```toml
[dependencies]
tokio = { version = "1.0", features = ["full"] }
axum = "0.7"
serde = { version = "1.0", features = ["derive", "serialize"] }
```

## 2. Defining the Structs

Start in `src/main.rs`.

Create the `Book` struct. It needs an `id` (`u32`), a `title` (`String`), and an `author` (`String`).
Because we will return this struct down a TCP socket as JSON, you must annotate it so `serde` serialization magic applies to it.
(Hint: `#[derive(Clone, Serialize, Deserialize)]`).

Define your Shared State:
```rust
use std::sync::{Arc, Mutex};
type AppState = Arc<Mutex<Vec<Book>>>;
```

## 3. The Routes and the Execution

Write the `main()` function.

Instantiate `AppState` with one default book:
```rust
let memory_db = Arc::new(Mutex::new(vec![
    Book { id: 1, title: "The Rust Programming Language".to_string(), author: "Steve K.".to_string() }
]));
```

Build the specific Axum `Router`, defining three routes:
1. `.route("/api/books", get(get_all_books))`
2. `.route("/api/books/:id", get(get_book_by_id))`
3. `.route("/api/books", post(create_book))`
...And inject the `memory_db` using `.with_state(memory_db)`.

Bind the TCPListener to `0.0.0.0:5000` and `axum::serve`.

## 4. The Handlers

Make sure every Handler properly extracts `State<AppState>`.

**`get_all_books`**
- Explicitly lock the Mutex.
- Clone the Vector inside it.
- Return the Vector wrapped inside `axum::Json`.

**`get_book_by_id`**
- Extract `Path(id) : Path<u32>`.
- Lock the Mutex.
- Perform a `.iter().find(|b| b.id == id)`.
- If found, return `Json`. If not found, return an HTTP Status 404 (You may need to return a Tuple like `(StatusCode, String)`).

**`create_book`**
- Extract your raw JSON struct! `Json(payload): Json<BookPayload>`
- Lock the Mutex.
- Calculate the new ID (length of the array + 1).
- Push the new `Book` onto the locked Vector.
- Return an HTTP 201 Created Status.

## 5. Verify it Flawlessly

Run `cargo run`.
The compiler will scream if you violate Threading or Borrow Checker rules. Fix them.

Once the compile finishes, use the exact same `curl` commands from Assignment 43 to test reading and writing.

You have now built a massively powerful HTTP API in a systems language.
