# 13.3 Button Click Callback (Complete Example)

Here's a full, compilable program that responds to a button click:

```c
#include <gtk/gtk.h>

// The callback function. GTK calls this when the button is clicked.
static void on_button_clicked(GtkButton *button, gpointer user_data) {
    (void)user_data;
    g_print("Button was clicked!\n");
    gtk_button_set_label(button, "Clicked! ✓");
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;
    
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Button Demo");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    GtkWidget *button = gtk_button_new_with_label("Click Me");
    gtk_widget_set_margin_top(button, 40);
    gtk_widget_set_margin_start(button, 40);
    gtk_widget_set_margin_end(button, 40);
    
    // THE KEY LINE: connect the "clicked" signal to our function.
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    gtk_window_set_child(GTK_WINDOW(window), button);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.button", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
```

Notice that `on_button_clicked` receives the `GtkButton*` that emitted the signal as its first argument. This lets you modify the button itself (change its label, disable it, etc.) from within the callback.
