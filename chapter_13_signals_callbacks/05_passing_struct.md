# 13.5 Passing Multiple Data with a Struct

What if your callback needs to access *multiple* widgets — a label, an entry, and a counter? You can only pass **one** `user_data` pointer. The solution: pack everything into a struct and pass a pointer to it.

This is the professional GTK pattern. Every real application uses it.

```c
#include <gtk/gtk.h>
#include <stdio.h>

// 1. Define a struct holding all the data your callbacks need.
typedef struct {
    GtkWidget *result_label;
    GtkWidget *name_entry;
    int        click_count;
} AppData;

// 2. The callback receives a pointer to the struct.
static void on_submit(GtkButton *btn, gpointer user_data) {
    (void)btn;
    AppData *data = (AppData *)user_data;
    data->click_count++;
    
    GtkEntryBuffer *buf = gtk_entry_get_buffer(GTK_ENTRY(data->name_entry));
    const char *name = gtk_entry_buffer_get_text(buf);
    
    char message[128];
    snprintf(message, sizeof(message), "Hello, %s! (click #%d)", name, data->click_count);
    gtk_label_set_text(GTK_LABEL(data->result_label), message);
}

// 3. In activate(), create the struct and pass its address.
static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;
    
    // Allocate on the stack — safe because activate() runs for the app lifetime.
    static AppData data = {0};
    
    GtkWidget *window = gtk_application_window_new(app);
    GtkWidget *box    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    data.name_entry  = gtk_entry_new();
    data.result_label = gtk_label_new("Enter your name and submit.");
    GtkWidget *button = gtk_button_new_with_label("Submit");
    
    g_signal_connect(button, "clicked", G_CALLBACK(on_submit), &data);
    
    gtk_box_append(GTK_BOX(box), data.name_entry);
    gtk_box_append(GTK_BOX(box), button);
    gtk_box_append(GTK_BOX(box), data.result_label);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}
```

> **Why `static`?** The `AppData data` must outlive the `activate()` call. Declaring it `static` places it in the Data segment (not the Stack), so it persists for the entire program lifetime.
