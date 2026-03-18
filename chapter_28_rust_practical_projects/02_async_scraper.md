# 28.2 The Network Tool: Async Web Scraper

Your second project leverages the Async/Await skills you just learned. You will build an ultra-fast, concurrent web scraper.

In C, writing parallel HTTP requests requires massive libraries like `libcurl` tied into `epoll` event loops. It is notoriously difficult.

In Rust, Tokio and Reqwest make this trivial.

## Project Requirements
Create a new project: `cargo new async_scraper`

### Dependencies
```toml
[dependencies]
tokio = { version = "1", features = ["full"] }
reqwest = "0.11"
scraper = "0.18" # A library for parsing HTML CSS selectors
```

### The Architecture
1. **The Target**
   We want to fetch the titles of 5 different Wikipedia articles concurrently.

2. **The Fetcher Function**
   Write an `async fn fetch_title(url: &str) -> Result<String, Box<dyn std::error::Error>>`.
   It should:
   - Use `reqwest::get(url).await?.text().await?` to get the raw HTML.
   - Use the `scraper` crate to parse the HTML, find the `<title>` tag, and extract the inner text.

3. **The Concurrent Execution**
   In your `#[tokio::main]`, you will create a `Vec` of 5 Wikipedia URLs.
   You will loop over the URLs, and for each one, use `tokio::spawn` to launch the `fetch_title` function in the background.

   Because `tokio::spawn` expects a Future that returns `()`, you should handle the printing of the Result inside the spawned task itself, rather than trying to `await` all of them in a complicated array.

```rust
for url in urls {
    tokio::spawn(async move {
        match fetch_title(url).await {
            Ok(title) => println!("Success: {}", title),
            Err(e) => eprintln!("Failed to fetch {}: {}", url, e),
        }
    });
}

// Since the spawns happen in the background, we need to keep `main` alive
// long enough for them to finish!
tokio::time::sleep(std::time::Duration::from_secs(3)).await;
```

## Professional Tips
- **Error Handling**: The `Box<dyn std::error::Error>` return type is the idiom for "I don't care what kind of error this is (Reqwest error, Parsing error, etc.), just return it dynamically so I can print it".
- Keep an eye on how quickly this runs. Because it's fully async, 5 network requests take exactly the same amount of time as 1 network request!
