# 12.4 Custom Widget Derivation

For simple apps, you compose built-in widgets. But for complex, reusable UI components — like a profile card, a color picker, or a file browser panel — you create a **custom widget** by subclassing `GtkWidget`.

This is advanced GObject programming. It uses the same struct + function pointer + macro patterns you learned in Chapter 10, but at industrial scale.

## Why Custom Widgets?

1. **Encapsulation** — Hide internal complexity behind a clean API.
2. **Reusability** — Create it once, instantiate it everywhere.
3. **Custom Drawing** — Handle your own Cairo rendering and input events.

## The Structure (Header + Implementation)

### `my-custom-widget.h` — The Public Interface
```c
#pragma once
#include <gtk/gtk.h>

// Register the type with the GObject system.
#define MY_TYPE_CUSTOM_WIDGET (my_custom_widget_get_type())
G_DECLARE_FINAL_TYPE(MyCustomWidget, my_custom_widget, MY, CUSTOM_WIDGET, GtkWidget)

// Public API
GtkWidget *my_custom_widget_new(void);
void       my_custom_widget_set_title(MyCustomWidget *self, const char *title);
```

### `my-custom-widget.c` — The Private Implementation
```c
#include "my-custom-widget.h"

// The instance struct: holds per-object private data.
struct _MyCustomWidget {
    GtkWidget  parent_instance;  // Must be first! Inherits from GtkWidget.
    GtkWidget *label;
    GtkWidget *button;
};

// Register the type. This macro generates the boilerplate functions.
G_DEFINE_TYPE(MyCustomWidget, my_custom_widget, GTK_TYPE_WIDGET)

// Instance initializer: runs once per new object.
static void my_custom_widget_init(MyCustomWidget *self) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->label  = gtk_label_new("Default Title");
    self->button = gtk_button_new_with_label("Action");
    
    gtk_box_append(GTK_BOX(box), self->label);
    gtk_box_append(GTK_BOX(box), self->button);
    
    gtk_widget_set_layout_manager(
        GTK_WIDGET(self),
        gtk_box_layout_new(GTK_ORIENTATION_VERTICAL)
    );
    gtk_widget_set_parent(box, GTK_WIDGET(self));
}

// Class initializer: runs once globally when the type is first used.
static void my_custom_widget_class_init(MyCustomWidgetClass *klass) {
    // Override dispose/finalize, bind templates, etc.
    (void)klass;
}

// Public constructor.
GtkWidget *my_custom_widget_new(void) {
    return g_object_new(MY_TYPE_CUSTOM_WIDGET, NULL);
}

// Public setter.
void my_custom_widget_set_title(MyCustomWidget *self, const char *title) {
    gtk_label_set_text(GTK_LABEL(self->label), title);
}
```

### Usage in `main.c`
```c
GtkWidget *card = my_custom_widget_new();
my_custom_widget_set_title(MY_CUSTOM_WIDGET(card), "Bugslayer's Profile");
gtk_window_set_child(GTK_WINDOW(window), card);
```

> **Veteran Note:** This is exactly how GTK itself is built. `GtkButton`, `GtkEntry`, `GtkWindow` — all follow this same struct + macros + init pattern. Master it, and you can read any GTK source code.
