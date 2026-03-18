# 14.3 Custom Input Dialogs

GTK4 doesn't provide a built-in "prompt" dialog like JavaScript's `prompt()`. Instead, you build custom modal windows. This is straightforward and gives you full control over layout and behavior.

## Building a Custom Input Dialog

```c
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *dialog_window;
    GtkWidget *entry;
    GtkWidget *result_label;  // Label in the main window to display the result.
} InputDialogData;

static void on_dialog_ok(GtkButton *btn, gpointer user_data) {
    (void)btn;
    InputDialogData *data = (InputDialogData *)user_data;
    
    GtkEntryBuffer *buf = gtk_entry_get_buffer(GTK_ENTRY(data->entry));
    const char *text = gtk_entry_buffer_get_text(buf);
    
    char message[128];
    snprintf(message, sizeof(message), "You entered: %s", text);
    gtk_label_set_text(GTK_LABEL(data->result_label), message);
    
    // Close the dialog window.
    gtk_window_destroy(GTK_WINDOW(data->dialog_window));
}

void show_input_dialog(GtkWindow *parent, GtkWidget *result_label) {
    static InputDialogData data;
    
    data.result_label = result_label;
    
    // Create a new modal window.
    data.dialog_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(data.dialog_window), "Enter Your Name");
    gtk_window_set_modal(GTK_WINDOW(data.dialog_window), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(data.dialog_window), parent);
    gtk_window_set_default_size(GTK_WINDOW(data.dialog_window), 300, 150);
    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    
    GtkWidget *prompt = gtk_label_new("Enter your name:");
    data.entry = gtk_entry_new();
    GtkWidget *ok_btn = gtk_button_new_with_label("OK");
    
    g_signal_connect(ok_btn, "clicked", G_CALLBACK(on_dialog_ok), &data);
    
    gtk_box_append(GTK_BOX(box), prompt);
    gtk_box_append(GTK_BOX(box), data.entry);
    gtk_box_append(GTK_BOX(box), ok_btn);
    gtk_window_set_child(GTK_WINDOW(data.dialog_window), box);
    gtk_window_present(GTK_WINDOW(data.dialog_window));
}
```

## Key Concepts

- **`gtk_window_set_modal(TRUE)`** — Prevents interaction with the parent window until the dialog closes.
- **`gtk_window_set_transient_for(parent)`** — Links the dialog to its parent so the window manager groups them together.
- **`gtk_window_destroy()`** — Closes and destroys the dialog window cleanly.
