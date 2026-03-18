# 13.8 GUI Concurrency: Keeping the UI Responsive

The golden rule of GUI programming:

> **Never block the main thread.**

If your button callback runs a 5-second computation, the entire application freezes — no redraws, no clicks, no cursor movement — for the full 5 seconds. The user will think your app crashed.

## The Wrong Way (Freezing the UI)

```c
static void on_button_clicked(GtkButton *btn, gpointer data) {
    (void)data;
    sleep(5);  // 💀 UI is completely frozen for 5 seconds!
    gtk_button_set_label(btn, "Done!");
}
```

## The Right Way: Worker Threads + `g_idle_add`

Spawn a background thread for heavy work, then use `g_idle_add()` to safely update the UI from the main thread. **GTK is not thread-safe** — you must never call GTK functions from a background thread.

```c
#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>

// 3. This runs safely on the main UI thread.
static gboolean on_work_finished(gpointer data) {
    GtkButton *btn = GTK_BUTTON(data);
    gtk_button_set_label(btn, "Work Finished! ✓");
    return G_SOURCE_REMOVE;  // Run this idle callback only once.
}

// 2. This runs in a background thread.
static void *expensive_computation(void *data) {
    sleep(5);  // Simulate heavy work (DB query, network call, etc.)
    g_idle_add(on_work_finished, data);  // Schedule UI update on main thread.
    return NULL;
}

// 1. Button click — spawn the worker immediately.
static void on_button_clicked(GtkButton *btn, gpointer data) {
    (void)data;
    gtk_button_set_label(btn, "Working...");
    
    pthread_t thread;
    pthread_create(&thread, NULL, expensive_computation, btn);
    pthread_detach(thread);
}
```

## The Modern Way: `GTask`

`GTask` is GLib's built-in async framework. It manages a thread pool and automatically marshals results back to the main thread.

```c
// Runs in a background thread pool.
static void task_func(GTask *task, gpointer obj, gpointer data, GCancellable *cancel) {
    (void)obj; (void)data; (void)cancel;
    sleep(5);
    g_task_return_boolean(task, TRUE);
}

// Runs safely on the main thread when the task completes.
static void on_task_done(GObject *source, GAsyncResult *res, gpointer user_data) {
    (void)source;
    GtkButton *btn = GTK_BUTTON(user_data);
    GError *err = NULL;
    if (g_task_propagate_boolean(G_TASK(res), &err)) {
        gtk_button_set_label(btn, "Done via GTask! ✓");
    }
}

static void on_button_clicked(GtkButton *btn, gpointer data) {
    (void)data;
    gtk_button_set_label(btn, "Working...");
    GTask *task = g_task_new(NULL, NULL, on_task_done, btn);
    g_task_run_in_thread(task, task_func);
    g_object_unref(task);
}
```
