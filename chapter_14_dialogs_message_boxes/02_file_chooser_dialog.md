# 14.2 File Chooser Dialog

GTK4's `GtkFileDialog` lets users browse their filesystem to open or save files. Like alert dialogs, it's fully asynchronous.

## Opening a File

```c
#include <gtk/gtk.h>

// 2. Handle the selected file.
static void on_file_chosen(GObject *source, GAsyncResult *result, gpointer user_data) {
    (void)user_data;
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
    GError *err = NULL;
    
    GFile *file = gtk_file_dialog_open_finish(dialog, result, &err);
    if (file != NULL) {
        char *path = g_file_get_path(file);
        g_print("Selected file: %s\n", path);
        g_free(path);           // Free the path string.
        g_object_unref(file);   // Release the GFile object.
    } else {
        g_print("File selection cancelled.\n");
    }
}

// 1. Show the file chooser.
static void on_open_clicked(GtkButton *btn, gpointer user_data) {
    (void)btn;
    GtkWindow *parent = GTK_WINDOW(user_data);
    
    GtkFileDialog *file_dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(file_dialog, "Open File");
    
    gtk_file_dialog_open(file_dialog, parent, NULL, on_file_chosen, NULL);
    g_object_unref(file_dialog);
}
```

## Saving a File

```c
static void on_save_location_chosen(GObject *source, GAsyncResult *result, gpointer data) {
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
    GFile *file = gtk_file_dialog_save_finish(dialog, result, NULL);
    if (file != NULL) {
        char *path = g_file_get_path(file);
        g_print("Save to: %s\n", path);
        g_free(path);
        g_object_unref(file);
    }
}

GtkFileDialog *save_dialog = gtk_file_dialog_new();
gtk_file_dialog_set_title(save_dialog, "Save As");
gtk_file_dialog_set_initial_name(save_dialog, "untitled.txt");
gtk_file_dialog_save(save_dialog, parent, NULL, on_save_location_chosen, NULL);
g_object_unref(save_dialog);
```

## File Filters

```c
GtkFileFilter *filter = gtk_file_filter_new();
gtk_file_filter_set_name(filter, "Text Files");
gtk_file_filter_add_pattern(filter, "*.txt");

GListStore *filters = g_list_store_new(GTK_TYPE_FILE_FILTER);
g_list_store_append(filters, filter);
gtk_file_dialog_set_filters(file_dialog, G_LIST_MODEL(filters));
```
