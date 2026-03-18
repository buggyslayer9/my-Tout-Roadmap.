# Assignment 45: Persistent Rust Backends (`sqlx`)

In Assignment 44, you wrote a beautiful Rust Axum API with an in-memory Mutex database.

Your task is to permanently rip out the `Arc<Mutex<Vec>>` RAM constraint and connect your Rust API directly to a physical PostgreSQL Database using the world's most powerful Rust database driver: **`sqlx`**.

## 1. Setup Postgres

If you are on Linux/Mac, start a postgres container or daemon.

```bash
docker run --name pg-db -e POSTGRES_PASSWORD=password -p 5432:5432 -d postgres
```

## 2. Upgrade Cargo.toml

Add `sqlx` to your `cargo.toml` specifically requesting Postgres support and the asynchronous `tokio` runtime!

```toml
[dependencies]
axum = "0.7"
tokio = { version = "1.0", features = ["full"] }
serde = { version = "1.0", features = ["derive"] }
# The heroic DB Driver!
sqlx = { version = "0.7", features = ["runtime-tokio", "postgres"] } 
```

## 3. Connect to the Database

In `main.rs`, instead of creating a `Mutex` vector, we will instantiate an asynchronous `PgPool` (A pool of active, multi-threaded TCP sockets continuously connected to PostgreSQL).

```rust
use sqlx::postgres::PgPoolOptions;

#[tokio::main]
async fn main() {
    let database_url = "postgres://postgres:password@localhost/postgres";
    
    // Create connection pool
    let pool = PgPoolOptions::new()
        .max_connections(5) // Don't melt the database server
        .connect(database_url)
        .await
        .unwrap();

    // Setup a table manually (in reality, you use Migrations)
    sqlx::query("CREATE TABLE IF NOT EXISTS books (id SERIAL PRIMARY KEY, title VARCHAR NOT NULL, author VARCHAR NOT NULL)")
        .execute(&pool)
        .await
        .unwrap();

    let app = Router::new()
        .route("/api/books", post(create_book))
        .route("/api/books", get(get_books))
        // Share the Postgres Connection Pool to all CPU Cores!
        .with_state(pool); 
    
    // Start axum::serve() ...
}
```

## 4. The `sqlx` Handlers

Because we injected `pool` into `.with_state()`, your Handlers can now extract explicitly typed `State<sqlx::PgPool>`.

```rust
async fn create_book(
    State(pool): State<sqlx::PgPool>,
    Json(payload): Json<BookPayload>
) -> impl axum::response::IntoResponse {
    // Write literal SQL!
    // Notice $1 and $2 automatically map safely to the bound variables, 
    // eliminating SQL Injection forever.
    sqlx::query("INSERT INTO books (title, author) VALUES ($1, $2)")
        .bind(&payload.title)
        .bind(&payload.author)
        .execute(&pool)
        .await
        .unwrap();

    axum::http::StatusCode::CREATED
}
```

Your `get_books` handler requires a bit more magic. You must define a `struct Book` using `#[derive(sqlx::FromRow)]`.
Then use `sqlx::query_as::<_, Book>("SELECT * FROM books").fetch_all(&pool).await.unwrap()`.

## 5. Persistence Test

Start your Rust server.
`curl -X POST` to add a book.
Kill the Rust server using `CTRL+C`.
Start the server again (`cargo run`).
`curl GET` the books.

**For the first time in this textbook, your code survived a restart.**
You are now touching physical storage.
