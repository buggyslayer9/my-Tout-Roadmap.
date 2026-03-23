# 36.3 `libcosmic` and the `iced` Toolkit

System76 couldn't just build a Rust Compositor. They had to build the actual apps: a pure Rust text editor, a pure Rust terminal, a pure Rust settings app.

They needed a GUI toolkit. 
They evaluated GTK (using `gtk-rs`), but felt that relying on a massive C framework defeated the purpose of a memory-safe, fearless-concurrency desktop.

They chose **`iced`**.

## The `iced` GUI Library
`iced` is an incredibly popular, pure-Rust GUI library inspired by the Elm architecture (which we touched upon in Chapter 27). 

In `iced`, you do not instantiate objects and manipulate them imperatively (like `button.set_text()`).
Instead, `iced` is purely declarative and reactive.

1.  **State:** You define a single Rust `struct` holding all your application data.
2.  **View:** You write a function that takes your State and returns a Tree of visual widgets describing the UI at that exact microsecond.
3.  **Update:** Every time a user clicks a button, a "Message" (a Rust `enum`) is sent. `iced` passes the State and the Message into an Update function. You mutate the State, and `iced` automatically redraws the View.

This functional architecture maps brilliantly to Rust's strict borrowing rules.

## `libcosmic`: The System76 Wrapper
`iced` is highly customizable but very visually generic out of the box.

System76 created **`libcosmic`**, a massive wrapper crate built around `iced`.

`libcosmic` does three critical things:
1.  **Strict Styling:** It provides extremely complex, beautiful widgets that strictly follow the COSMIC Human Interface Guidelines (gradients, rounded corners, animations, typography). If you use a `libcosmic::widget::button::Button`, it instantly looks like a native Pop!_OS application.
2.  **Theme Integration:** It automatically links the `iced` application to the central COSMIC system theme. If the user clicks "Dark Mode" in the system settings, every single `libcosmic` app instantly repaints itself without the developer writing a single line of theme-listening code.
3.  **Wayland Subsurface Magic:** It perfectly orchestrates window creation and Wayland subsurface embedding, allowing apps to tear off tabs smoothly.

If you are developing a native Linux Desktop app today, combining Rust and `libcosmic` offers an arguably safer, faster, and more modern developer ecosystem than classic C+GTK.
