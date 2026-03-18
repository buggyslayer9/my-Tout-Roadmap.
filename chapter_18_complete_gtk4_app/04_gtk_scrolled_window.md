# 18.4 GtkScrolledWindow: Handling Overflow

If you put 100 items into a `GtkListBox`, your application window will try to grow vertically to fit them all, eventually stretching off the bottom of your monitor.

To fix this, you must wrap large or dynamic widgets inside a `GtkScrolledWindow`. This widget provides a finite box with scrollbars.

## Wrapping a Widget in a Scrolled Window

```c
#include <gtk/gtk.h>

GtkWidget *setup_scrolling_list() {
    // 1. Create the content (e.g., a massive list)
    GtkWidget *listbox = gtk_list_box_new();
    for (int i = 0; i < 100; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Row %d", i);
        gtk_list_box_append(GTK_LIST_BOX(listbox), gtk_label_new(buf));
    }

    // 2. Create the Scrolled Window
    GtkWidget *scroll = gtk_scrolled_window_new();
    
    // 3. Set policies: NEVER, ALWAYS, or AUTOMATIC
    // AUTOMATIC means the scrollbar only appears if the content overflows.
    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(scroll),
        GTK_POLICY_NEVER,       // No horizontal scrollbar
        GTK_POLICY_AUTOMATIC    // Vertical scrollbar when needed
    );

    // 4. Put the listbox INSIDE the scrolled window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), listbox);
    
    // 5. CRITICAL: Tell the scrolled window it is allowed to expand 
    // to fill available space in its parent container.
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_widget_set_hexpand(scroll, TRUE);

    return scroll; // You pack 'scroll' into your main layout, not 'listbox'!
}
```

## The Expansion Rule
Whenever you use a `GtkScrolledWindow`, you almost always need to call `gtk_widget_set_vexpand(scroll, TRUE)`. Otherwise, the scrolled window will shrink to its minimum possible size (often 0 pixels) and disappear because it thinks it doesn't need any space.
