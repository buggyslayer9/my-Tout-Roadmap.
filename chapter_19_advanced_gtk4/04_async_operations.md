# 19.4 Async Operations with GTask

In GTK, drawing the UI and processing user input happens entirely on a **Single Thread** (the main event loop).

If a user clicks a button, and the callback function downloads a 500MB file from the internet... your application completely freezes. The UI won't update, buttons can't be clicked, and the OS will show a "Application is Not Responding" warning.

**Rule: Never block the main thread.**

To solve this, GLib provides `GTask`, an elegant wrapper around background threading.

## Using GTask

`GTask` handles launching a worker thread safely and, most importantly, returning the result back to the main thread seamlessly.

```c
#include <gtk/gtk.h>
#include <gio/gio.h>

// 2. The Worker Thread
// This function strictly runs in the BACKGROUND. 
// Do NOT touch any UI widgets in here. GTK widgets are NOT thread-safe!
static void background_worker(GTask *task, gpointer source_obj, gpointer task_data, GCancellable *cancel) {
    g_print("[Worker] Starting heavy network request...\n");
    
    g_usleep(3000000); // Simulate blocking 3-second network call
    
    g_print("[Worker] Request finished!\n");
    
    // Send standard integer result back to main thread
    g_task_return_int(task, 404);
}

// 3. Main Thread Result Handler
// This fires on the MAIN thread automatically when the worker thread finishes.
static void on_heavy_work_finished(GObject *source_obj, GAsyncResult *res, gpointer user_data) {
    GError *error = NULL;
    
    // Extract the result from the task
    int http_status = g_task_propagate_int(G_TASK(res), &error);
    
    if (error) {
        g_print("[Main Thread] Error: %s\n", error->message);
        g_error_free(error);
        return;
    }
    
    g_print("[Main Thread] Success! Code: %d\n", http_status);
    
    // Now it is perfectly safe to update the UI
    // gtk_label_set_text(GTK_LABEL(user_data), "Download Complete!");
}

// 1. Launching the Task
static void on_button_clicked(GtkButton *btn, gpointer user_data) {
    g_print("[Main Thread] Launching Async Task...\n");
    
    // Create new Task. (source_object, cancellable, callback, callback_user_data)
    GTask *task = g_task_new(NULL, NULL, on_heavy_work_finished, user_data);
    
    // Ship it to the worker thread pool!
    g_task_run_in_thread(task, background_worker);
    
    // Unref (GTask manages its own lifecycle internally after being run)
    g_object_unref(task);
}
```

By utilizing `GTask`, your GUI stays buttery smooth and highly responsive, regardless of how intense the underlying system processing is.
