# 12.1 What Are Widgets?

A **widget** is any visible element in your GUI: a button, a text field, a checkbox, a window, even an invisible layout container. In GTK4, every single UI component is a `GtkWidget` — from the massive window down to the smallest icon.

Widgets form a **tree** (parent-child hierarchy):

```
GtkApplicationWindow
  └── GtkBox (vertical)
        ├── GtkLabel ("Enter your name:")
        ├── GtkEntry (text input field)
        └── GtkButton ("Submit")
```

The window contains a box. The box contains a label, an entry, and a button. When you destroy the window, GTK automatically destroys all its children.

## Two Types of Widgets

| Type | Purpose | Examples |
|------|---------|---------|
| **Leaf widgets** | Display something or accept input | `GtkLabel`, `GtkButton`, `GtkEntry`, `GtkImage` |
| **Container widgets** | Hold and arrange other widgets | `GtkBox`, `GtkGrid`, `GtkStack`, `GtkScrolledWindow` |

## The Widget Lifecycle

1. **Create** — `gtk_button_new_with_label("Click")` allocates the widget on the heap.
2. **Configure** — Set properties (text, margins, expand behavior).
3. **Pack** — Add it to a parent container: `gtk_box_append(box, button)`.
4. **Present** — Call `gtk_window_present()` to show the top-level window.
5. **Destroy** — Happens automatically when the parent window is closed.

You rarely call `g_object_unref()` on widgets directly. The parent container owns them.
