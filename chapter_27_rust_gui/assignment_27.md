# Assignment 27: The Rust GTK Boilerplate

To prove you understand how to bridge your C GTK knowledge with Rust, you will create a highly professional GTK4 boilerplate application in Rust.

## The Task

Initialize a new cargo project: `cargo new rust_gtk_template`

Open your `Cargo.toml` and add the `gtk4` dependency:
```toml
[dependencies]
gtk = { version = "0.7", package = "gtk4" }
```

You must write a GTK4 app in `src/main.rs` that implements the following precisely:

1. **Application Setup**
   - Application ID: `com.yourname.RustTemplate`.
   - Connect to the `activate` signal.

2. **The Layout**
   - Create an `ApplicationWindow` with default width 400 and height 300.
   - Create a horizontal `GtkBox` with a spacing of 6.
   - Set the box to be placed completely in the center of the window using `.set_halign(gtk::Align::Center)` and `.set_valign(gtk::Align::Center)`.

3. **The Widgets**
   - Inside the Box, place two widgets:
     - A `Button` labeled "Decrement"
     - A `Label` containing "0"
     - A `Button` labeled "Increment"

4. **The Logic (The Tricky Part!)**
   - You need a way to store the counter number `0`.
   - Because you need to mutate this number from *inside* two different closures (the two button click handlers), you cannot just use `let mut count = 0;`. The Rust borrow checker will violently stop you from moving the same variable into two closures.
   - **Hint:** Wrap your integer in Rust's internal mutation primitives: `Rc<Cell<i32>>` or `Rc<RefCell<i32>>`.

5. **The Connections**
   - Connect the "Increment" button so it adds 1 to the counter and updates the label's text.
   - Connect the "Decrement" button so it subtracts 1 and updates the label's text.
   - Use the `glib::clone!` macro (or manually `.clone()` your `Rc` and widgets) before moving them into the closures!

## Standard Library Imports Needed

```rust
use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Box, Button, Label, Orientation, Align};
use std::rc::Rc;
use std::cell::Cell;
```

If you can successfully manage the state (`Rc<Cell<i32>>`) across two different closures modifying a single Label, you have fully mastered the memory constraints of Rust and GTK-rs!
