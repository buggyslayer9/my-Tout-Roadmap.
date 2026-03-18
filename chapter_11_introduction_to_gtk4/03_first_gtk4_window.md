# 11.3 Your First GTK4 Window

This is your "Hello, World!" for GUI programming. Every GTK4 application follows this exact pattern.

```c
#include <gtk/gtk.h>

// This callback fires when the application is ready to display its UI.
static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;  // Suppress unused parameter warning.
    
    // 1. Create a window owned by this application.
    GtkWidget *window = gtk_application_window_new(app);
    
    // 2. Configure it.
    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK4!");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    
    // 3. Show it on screen.
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    // 1. Create the application object with a unique reverse-DNS ID.
    GtkApplication *app = gtk_application_new(
        "com.example.hello",
        G_APPLICATION_DEFAULT_FLAGS
    );
    
    // 2. Connect the "activate" signal to our callback.
    //    When the app starts (or the user re-focuses it), activate() runs.
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    // 3. Run the event loop. This blocks until the user closes the window.
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    
    // 4. Clean up the application object.
    g_object_unref(app);
    
    return status;
}
```

## Compile and Run

```bash
gcc `pkg-config --cflags gtk4` hello.c `pkg-config --libs gtk4` -o hello
./hello
```

A 400×300 window titled "Hello GTK4!" will appear. Close it, and the program exits cleanly.

## What Just Happened?

1. `gtk_application_new()` — Created an application object. The reverse-DNS ID (`com.example.hello`) uniquely identifies your app to the desktop environment.
2. `g_signal_connect()` — Connected the `"activate"` signal to your `activate()` function. This is a **function pointer callback** — exactly what you learned in Chapter 10.
3. `g_application_run()` — Started the **main event loop**. This is an infinite loop that waits for user input (clicks, keypresses, window events) and dispatches them to your handlers.
4. `g_object_unref()` — Released the application's reference count. GTK uses reference counting instead of manual `free()`.
