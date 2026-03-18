# Assignment 28: The Final Phase 3 Capstone

You are at the end of Phase 3. You have traversed C, binary layouts, memory addresses, GTK4, Rust's borrow checker, multi-threading, asynchronous I/O, and Rust's GUI solutions.

It is time to combine them to prove you are a Senior Systems Programmer.

## The Capstone: A GTK4 Multithreaded Hash Cracker

You will build a GTK4 graphical application in Rust that accepts a target SHA256 Hash string. When the user clicks "Crack", the UI will spawn multiple background threads that attempt to brute-force the hash, updating the UI with their progress, without freezing the GUI.

Initialize a new cargo project: `cargo new gtk_hash_breaker`

### Dependencies
```toml
[dependencies]
gtk = { version = "0.7", package = "gtk4" }
sha2 = "0.10" # Cryptography library
flume = "0.11" # A fast multi-producer, multi-consumer channel (better than std::mpsc)
```

### The UI
Write the Rust GTK boiler plate. You need:
- A `GtkEntry` for the user to paste a target Hash.
- A `GtkButton` to start the crack.
- A `GtkLabel` to show the status ("Idle", "Cracking...", "Found: password123").

### The Concurrency Rules
**CRUCIAL RULE:** You cannot do expensive math on the GTK Main Thread, or the window will freeze.
**CRUCIAL RULE:** Background threads cannot touch GTK widgets directly. GTK is not thread-safe!

### The Architecture
1. **The Channels**
   When the user clicks "Start", create a `flume::unbounded()` channel. You get a Transmitter (`tx`) and Receiver (`rx`).
   
2. **The Workers**
   Use `std::thread::spawn` to launch 4 background threads. Give them clones of the `tx` transmitter. Have them start hashing numbers from 0 to 100,000,000 in chunks. 
   If a thread finds the matching hash, it does `tx.send(the_number_as_string)`.

3. **The UI Receiver**
   How does GTK read the channel? In C, we used `g_idle_add`. In Rust's GTK wrapper, we use `glib::MainContext::default().spawn_local()`.

   ```rust
   use glib::clone;
   
   // This code runs on the GTK Main Thread, but asynchronously!
   glib::MainContext::default().spawn_local(clone!(@weak label => async move {
       // recv_async() yields back to GTK while waiting for the background 
       // threads to find the answer!
       if let Ok(password) = rx.recv_async().await {
           label.set_text(&format!("CRACKED: {}", password));
       }
   }));
   ```

### Implementation Steps
1. Make a simple UI.
2. Hardcode a SHA256 hash of a 6-digit number (e.g., hash of "123456").
3. Wire the button to spawn the threads and start the `spawn_local` listener.
4. Watch the background threads do the heavy lifting while the UI stays perfectly crisp and responsive.

*Completing this assignment formally proves your mastery over memory, threading, and GUI integration.*
