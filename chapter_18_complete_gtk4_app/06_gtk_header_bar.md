# 18.6 GtkHeaderBar: Modern Window Titles

Look at any modern GNOME or Linux application. You usually don't see a standard OS window title bar *and* an application toolbar. They are combined into a single, thick header bar containing the title, window controls (close/minimize), and application buttons.

In GTK, this is the `GtkHeaderBar`.

## Setting up a Header Bar

```c
#include <gtk/gtk.h>

// Inside your main activate() or app_window setup function:

GtkWidget *window = gtk_application_window_new(app);

// 1. Create the Header Bar
GtkWidget *header = gtk_header_bar_new();

// 2. Create a custom title widget (optional, GTK will use the window title by default)
GtkWidget *title = gtk_label_new("My Awesome App");
gtk_widget_add_css_class(title, "title"); // Give it the built-in bold title styling
gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), title);

// 3. Add buttons to the Header Bar
// Start = Left side (before title), End = Right side (after title)
GtkWidget *add_btn = gtk_button_new_from_icon_name("list-add-symbolic");
gtk_header_bar_pack_start(GTK_HEADER_BAR(header), add_btn);

GtkWidget *menu_btn = gtk_button_new_from_icon_name("open-menu-symbolic");
gtk_header_bar_pack_end(GTK_HEADER_BAR(header), menu_btn);

// 4. CRITICAL: Tell the window to use THIS bar instead of the OS default titlebar!
gtk_window_set_titlebar(GTK_WINDOW(window), header);

// 5. Continue setting up the rest of the window's actual content
// gtk_window_set_child(...)
```

> **Icons:** Notice `gtk_button_new_from_icon_name()`. GTK themes come with hundreds of standard icons (`list-add-symbolic`, `document-save-symbolic`, `edit-delete-symbolic`). Finding the right one is easy using the `gtk4-icon-browser` utility on Linux.
