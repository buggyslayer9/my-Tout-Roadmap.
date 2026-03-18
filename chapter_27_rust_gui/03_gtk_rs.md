# 27.3 GTK4 with Rust (GTK-rs)

You already know GTK4 from the first half of this curriculum. You know `GtkApplication`, `GtkWindow`, `GtkBox`, and `GtkButton`.

Normally, calling C libraries from Rust requires tons of `unsafe` blocks. However, the `gtk-rs` project has done all the hard work for you. They have generated safe Rust wrappers around the entire GTK library.

In your `Cargo.toml`:
```toml
[dependencies]
gtk = { version = "0.7", package = "gtk4", features = ["v4_10"] }
```

## The "Hello World" of GTK-rs

Compare this to the C version you wrote in Chapter 11.

```rust
use gtk::prelude::*; // Imports the Traits needed to call methods on GTK objects
use gtk::{Application, ApplicationWindow, Button};
use glib::clone;

const APP_ID: &str = "org.bugslayer.RustGtkApp";

fn main() {
    // 1. Create the Application
    let app = Application::builder().application_id(APP_ID).build();

    // 2. Connect the 'activate' signal using a Rust Closure!
    app.connect_activate(build_ui);

    // 3. Run the application
    app.run();
}

fn build_ui(app: &Application) {
    // Create a button
    let button = Button::builder()
        .label("Click Me!")
        .margin_top(12)
        .margin_bottom(12)
        .margin_start(12)
        .margin_end(12)
        .build();

    // Connect to the 'clicked' signal
    // Notice how clean this is compared to g_signal_connect!
    button.connect_clicked(|btn| {
        btn.set_label("I was clicked!");
    });

    // Create the window
    let window = ApplicationWindow::builder()
        .application(app)
        .title("My First Rust GTK App")
        .child(&button)
        .build();

    // Present the window
    window.present();
}
```

## The Danger: Reference Counting Leaks

There is one critical "gotcha" with GTK-rs. 
GTK objects are **Reference Counted** (like `Arc` or `Rc`). When you put a Button inside a Window, the Window increments the counter.

If you pass GUI objects into a connection closure, you must handle the references carefully to avoid circular dependencies (memory leaks).

```rust
// WRONG WAY (Memory Leak)
// If the button's closure holds a reference to the window, and the window holds the button,
// they will never be freed when closed!
button.connect_clicked(move |_| {
    window.set_title("Clicked");
});

// RIGHT WAY (Using glib::clone macro)
// We tell the closure to take a 'weak' reference to the window.
button.connect_clicked(clone!(@weak window => move |_| {
    window.set_title("Clicked");
}));
```

This `clone!(@weak ...)` macro is exclusively used in GTK-rs to prevent memory leaks when dealing with closures that modify the UI. It's the one piece of "boilerplate" you must get used to.
