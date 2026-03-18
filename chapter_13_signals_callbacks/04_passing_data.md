# 13.4 Passing Data to Callbacks

The `user_data` parameter in `g_signal_connect` is your lifeline. It lets you pass **any pointer** to your callback — typically a pointer to another widget you want to modify.

## Example: Button Updates a Label

```c
#include <gtk/gtk.h>

static void on_click(GtkButton *btn, gpointer user_data) {
    (void)btn;
    GtkLabel *label = GTK_LABEL(user_data);  // Cast the void* to GtkLabel*.
    gtk_label_set_text(label, "You clicked the button!");
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;
    
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Data Passing");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_start(box, 20);
    
    GtkWidget *label  = gtk_label_new("Waiting for click...");
    GtkWidget *button = gtk_button_new_with_label("Click Me");
    
    // Pass 'label' as user_data — the callback can now modify it.
    g_signal_connect(button, "clicked", G_CALLBACK(on_click), label);
    
    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), button);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}
```

The `user_data` mechanism is a `void *` — C's universal pointer type. You can pass a pointer to anything: a widget, a struct, an integer (cast to `GINT_TO_POINTER(n)`), or `NULL` if you don't need extra data.
