# 18.3 GtkListBox: Dynamic Lists

When building real apps, standard `GtkBox` layouts aren't enough for long lists of dynamic data (like emails, contacts, or songs). You need a widget designed specifically for selectable lists: `GtkListBox`.

## Creating a List Box

```c
#include <gtk/gtk.h>

// 2. The selection callback
static void on_row_selected(GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
    if (row == NULL) return; // Happens when selection is cleared
    
    // In GTK4, a GtkListBoxRow contains exactly one child.
    GtkWidget *child = gtk_list_box_row_get_child(row);
    
    // Assuming the child is a label, let's grab its text.
    if (GTK_IS_LABEL(child)) {
        const char *text = gtk_label_get_text(GTK_LABEL(child));
        g_print("User selected: %s\n", text);
    }
}

// 1. Setup the List Box
static void create_listbox() {
    GtkWidget *listbox = gtk_list_box_new();
    
    // Choose selection behavior: NONE, SINGLE, BROWSE, or MULTIPLE
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(listbox), GTK_SELECTION_SINGLE);
    
    // Add rows. GtkListBox automatically wraps child widgets in a GtkListBoxRow!
    gtk_list_box_append(GTK_LIST_BOX(listbox), gtk_label_new("Item One"));
    gtk_list_box_append(GTK_LIST_BOX(listbox), gtk_label_new("Item Two"));
    gtk_list_box_append(GTK_LIST_BOX(listbox), gtk_label_new("Item Three"));
    
    // Listen for selection changes.
    g_signal_connect(listbox, "row-selected", G_CALLBACK(on_row_selected), NULL);
}
```

## Why GtkListBox?

Unlike a standard `GtkBox`, `GtkListBox`:
- Automatically handles keyboard navigation (up/down arrows).
- Automatically manages selection states (highlighting the selected row).
- Provides signals for when the selection changes.
- Allows applying sort and filter functions dynamically using `gtk_list_box_set_sort_func` and `gtk_list_box_set_filter_func`.
