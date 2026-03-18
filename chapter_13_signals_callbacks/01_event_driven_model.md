# 13.1 The Event-Driven Model

In Chapters 1–10, your programs ran from top to bottom — `main()` started, executed statements in order, and exited. GUI programming flips this on its head.

GTK4 is **event-driven**: your code sits idle until something happens. When the user clicks a button, moves the mouse, or presses a key, GTK emits a **signal** on the affected widget. Your registered **callback function** fires in response.

## The Signal/Slot Pattern

```
[User clicks "Save"]  →  GtkButton emits "clicked" signal
                      →  GTK looks up registered callbacks
                      →  Your save_file() function is invoked
```

This is identical to how web browsers handle `addEventListener("click", handler)` in JavaScript, or how Qt's signal/slot system works in C++. The concept is universal across all GUI frameworks.

## Why Event-Driven?

A GUI must stay responsive at all times — redrawing, handling input, updating animations. If your code ran linearly, the entire app would freeze while processing anything. The event loop solves this by running an infinite loop that:

1. Waits for the next event (mouse click, keyboard press, timer tick).
2. Identifies which widget triggered it.
3. Calls the registered callback for that signal.
4. Returns to waiting.

You never write this loop yourself. `g_application_run()` is the event loop.
