# 16.1 Why GLib?

If you've written a lot of standard C code, you know it lacks modern conveniences. There are no built-in hash tables, dynamic arrays, or string builders. You end up reinventing the wheel for every project.

Enter **GLib**. 

GLib is the foundational utility library that GTK (and GNOME) is built upon. It provides the data structures, concurrency tools, and event loop that make writing large C applications manageable.

## What GLib Provides

- **Data Structures:** Linked lists (`GList`, `GSList`), hash tables (`GHashTable`), dynamic arrays (`GArray`, `GPtrArray`), queues (`GQueue`), and trees.
- **Dynamic Strings:** `GString`, which handles memory reallocation automatically as the string grows.
- **Memory Management:** Wrappers like `g_new()`, `g_malloc()`, and `g_free()` that provide safer memory allocation.
- **The Event Loop:** `GMainLoop`, which powers GTK's event-driven model, allowing you to handle timeouts, idle functions, and I/O monitoring.
- **Concurrency:** Thread abstractions (`GThread`), mutexes (`GMutex`), and asynchronous tasks (`GTask`).

When you write GTK4 applications, you are writing GLib applications. Embrace GLib — it will save you thousands of lines of boilerplate C code.
