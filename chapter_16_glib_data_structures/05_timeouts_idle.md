# 16.5 Timeouts & Idle Callbacks

GUI applications are event-driven. Your code sits around doing nothing until the GLib Main Loop (`GMainLoop`) tells it something happened (a click, a key press). 

But what if you want to run code based on *time* instead of user input?

## Timeouts (`g_timeout_add`)

To run a function repeatedly at a specific interval (in milliseconds), use `g_timeout_add`.

```c
#include <gtk/gtk.h>

// 2. The callback function.
static gboolean my_timer_tick(gpointer user_data) {
    (void)user_data;
    g_print("Tick!\n");
    
    // RETURN TRUE (or G_SOURCE_CONTINUE) to keep the timer running.
    // RETURN FALSE (or G_SOURCE_REMOVE) to stop the timer.
    return G_SOURCE_CONTINUE; 
}

// 1. Setup the timer (e.g., inside activate)
guint timer_id = g_timeout_add(1000, my_timer_tick, NULL); // Runs every 1 second
```

### Stopping a Timer Manually

If you saved the ID returned by `g_timeout_add`, you can cancel it from anywhere:

```c
g_source_remove(timer_id);
```

## Idle Callbacks (`g_idle_add`)

Sometimes you have a low-priority task (like updating a status bar or doing some background processing) that you only want to run when the app has nothing else to do.

```c
static gboolean background_calculation(gpointer data) {
    // Do some small chunk of work...
    return G_SOURCE_REMOVE; // Run once and stop
}

// Schedule this to run when the GTK main loop is idle.
g_idle_add(background_calculation, NULL);
```

**Note:** We already saw `g_idle_add` in Chapter 13. It is incredibly important for thread safety when you need a background thread to update the GTK UI.
