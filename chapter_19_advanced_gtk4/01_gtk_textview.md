# 19.1 GtkTextView: Advanced Text Editing

While `GtkEntry` is perfect for single lines like passwords or search bars, `GtkTextView` is a heavy-duty, multiline text editor component. It's the engine behind apps like Gedit or GNOME Text Editor.

## Architecture

A `GtkTextView` is just the visual representation. The actual text data is stored in a `GtkTextBuffer`. 

```c
#include <gtk/gtk.h>

void setup_editor(GtkApplicationWindow *window) {
    // 1. Create the visual widget
    GtkWidget *textview = gtk_text_view_new();
    
    // 2. Configure behavior
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), TRUE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview), TRUE);

    // 3. Get the underlying data buffer
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    
    // 4. Set initial text (-1 means the string is null-terminated)
    gtk_text_buffer_set_text(buffer, "Start typing here...\nLine two.", -1);

    // 5. Wrap in a ScrolledWindow (TextViews expand infinitely otherwise)
    GtkWidget *scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), textview);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_widget_set_hexpand(scroll, TRUE);

    gtk_window_set_child(GTK_WINDOW(window), scroll);
}
```

## Reading Text (Using Iterators)

You cannot simply ask a `GtkTextBuffer` for "all the text". Because buffers can hold gigabytes of data spanning millions of lines, GTK uses **Iterators** (`GtkTextIter`) pointing to specific locations in the text.

```c
void print_buffer_contents(GtkTextBuffer *buffer) {
    GtkTextIter start, end;
    
    // Get iterators pointing to the very beginning and very end
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    
    // Extract the text between those two points. 
    // The 'FALSE' means we don't include hidden characters/images.
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    g_print("Buffer contains: %s\n", text);
    
    // You MUST free the string when done!
    g_free(text);
}
```

## Advanced Buffer Features
`GtkTextBuffer` goes way beyond plain text. You can insert images, apply rich-text tags (bold, colors, fonts), and handle clipboard operations dynamically.
