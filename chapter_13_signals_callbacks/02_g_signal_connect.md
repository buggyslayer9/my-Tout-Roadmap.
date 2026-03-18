# 13.2 `g_signal_connect` — Wiring Signals to Callbacks

`g_signal_connect` is the function that connects a signal to your callback. It returns a handler ID you can use to disconnect later.

## The Signature

```c
gulong g_signal_connect(
    gpointer      object,     // The widget that emits the signal.
    const char   *signal,     // The signal name (e.g., "clicked", "activate").
    GCallback     callback,   // Your handler function, cast with G_CALLBACK().
    gpointer      user_data   // Any extra data you want passed to the callback.
);
```

## How It Works

```c
// 1. Define the callback (must match the signal's expected signature).
static void on_click(GtkButton *button, gpointer user_data) {
    g_print("Clicked!\n");
}

// 2. In activate(), connect the signal.
g_signal_connect(button, "clicked", G_CALLBACK(on_click), NULL);
```

- `button` — The widget to listen on.
- `"clicked"` — The signal name. GTK documentation lists exact signal names for every widget.
- `G_CALLBACK(on_click)` — Casts your function pointer to the generic `GCallback` type.
- `NULL` — The `user_data` pointer that gets passed as the second argument to your callback. We'll use this extensively in the next lessons.

## Important Rules

1. The callback's **first parameter** is always the widget that emitted the signal.
2. The callback's **last parameter** is always `gpointer user_data`.
3. You must wrap your function in `G_CALLBACK()` — this is a type-safe cast macro.
