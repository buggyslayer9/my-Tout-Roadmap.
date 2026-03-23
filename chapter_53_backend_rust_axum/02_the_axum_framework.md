# 44.2 Routing and Handlers in Axum

To build a Rust web server, we start incredibly similar to Node.js/Express. We define a Router, register paths, and bind it to a TCP Socket.

But because Rust is strictly compiled, we use the `tokio` asynchronous runtime to manage the multi-threaded Event Loop.

## 1. The Dependencies
Add these to your `Cargo.toml`:
```toml
[dependencies]
# The web framework itself
axum = "0.7"
# The foundational async multi-threading engine
tokio = { version = "1.0", features = ["full"] }
# The JSON serialization engine
serde = { version = "1.0", features = ["derive"] }
```

## 2. Booting the Server

We must annotate our `main` function with `#[tokio::main]`. This literally tells the Rust compiler to swap the standard Single-Threaded C-style entry point for a massive, multi-threaded `epoll` Event Loop (identical to Node's `libuv` but mapped across all your CPU cores).

```rust
use axum::{routing::get, Router};

// The magical macro that starts the multi-threaded Event Loop!
#[tokio::main]
async fn main() {
    // 1. Build our application Router
    let app = Router::new()
        .route("/", get(root_handler))
        .route("/health", get(health_check));

    // 2. Bind the TCP Listener to an IP and Port
    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    println!("Server flying on Port 3000 -> {}", listener.local_addr().unwrap());

    // 3. Command Axum to physically serve the routes indefinitely
    axum::serve(listener, app).await.unwrap();
}

// -----------------------------------------------------------------
// HANDLERS (The code that actually runs when a browser visits)
// -----------------------------------------------------------------

// A handler in Axum is strictly an 'async' function.
// If it returns a &'static str, Axum automatically sets Content-Type to text/plain!
async fn root_handler() -> &'static str {
    "Welcome to a Multi-Threaded Rust Backend!"
}

async fn health_check() -> &'static str {
    "100% Online"
}
```

Notice how explicitly typed everything is. `axum::serve` physically requires the `listener` and the `Router` struct. If you screw up, it refuses to compile.

Compare this to Express, where `app.get()` can silently fail at runtime if you pass it the wrong variable type. `Axum` prevents typos from crashing your production servers.
