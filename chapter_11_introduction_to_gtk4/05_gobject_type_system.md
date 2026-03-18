# 11.5 GObject: The Type System Under GTK

C has no classes, no inheritance, and no polymorphism. GTK needs all three. So the GNOME team built **GObject** — a complete object-oriented type system implemented in pure C using structs, function pointers, and macros.

## The Core Concepts

### 1. Everything Is a `GObject`
Every GTK widget — `GtkWindow`, `GtkButton`, `GtkLabel` — is a struct that inherits from `GObject`. This gives every widget properties, signals, and reference-counted memory management.

### 2. Type Hierarchy (Inheritance)
```
GObject
  └── GtkWidget
        ├── GtkWindow
        │     └── GtkApplicationWindow
        ├── GtkButton
        ├── GtkLabel
        ├── GtkBox
        └── GtkEntry
```

A `GtkButton` *is a* `GtkWidget`, which *is a* `GObject`. You can use any `GtkButton` where a `GtkWidget` is expected.

### 3. Casting Macros
GTK provides compile-time and runtime type-safe casting macros:

```c
GtkWidget *widget = gtk_button_new_with_label("Click me");

// Cast widget to a GtkButton for button-specific operations.
GtkButton *button = GTK_BUTTON(widget);

// Cast widget to a GtkWindow — THIS WILL FAIL at runtime!
// GtkWindow *win = GTK_WINDOW(widget);  // CRASH: widget is a button, not a window.
```

`GTK_WINDOW()`, `GTK_BUTTON()`, etc. perform runtime type checking. If the cast is invalid, they print a warning and return `NULL` instead of silently corrupting memory.

### 4. Reference Counting (Memory Management)
GTK doesn't use `malloc`/`free`. It uses **reference counting**:

```c
g_object_ref(widget);    // Increment reference count ("I'm using this").
g_object_unref(widget);  // Decrement it ("I'm done with this").
                         // When count reaches 0, the object is destroyed.
```

Widgets added to a container are automatically referenced by that container. When the window is destroyed, it destroys its children. You rarely need to call `g_object_unref` directly on widgets.

> **Key Insight:** GObject is C's manual implementation of what Rust does with traits + ownership and what Java does with classes + garbage collection. Understanding GObject is understanding how all OOP systems work under the hood.
