# 17.1 CSS in GTK4

Forget the old days of manual X11 drawing or calling `gtk_widget_modify_bg()` to change a button color. GTK4 fully embraces CSS for styling. 

If you know web CSS, you already know 90% of GTK4 CSS. It uses the same syntax, selectors, and many of the exact same properties (`background-color`, `border-radius`, `padding`, `margin`).

## Loading CSS Data

Before any widgets can be styled, you need to load your CSS rules into a `GtkCssProvider` and apply it to the display.

```c
#include <gtk/gtk.h>

void load_css_from_string() {
    // 1. Create a provider.
    GtkCssProvider *provider = gtk_css_provider_new();
    
    // 2. Load the CSS rules (hardcoded string for now).
    gtk_css_provider_load_from_string(provider,
        "button {"
        "  background-color: #2196F3;"
        "  color: white;"
        "  border-radius: 6px;"
        "  padding: 8px 16px;"
        "}"
        "button:hover {"
        "  background-color: #1976D2;"
        "}"
    );

    // 3. Apply the provider globally to the default display.
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        // Priority ensures your CSS overrides the default GTK theme.
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION 
    );
    
    // 4. Cleanup. The display keeps its own reference to the provider.
    g_object_unref(provider);
}
```

Call `load_css_from_string()` early in your application's `activate` signal handler, and instantly every button in your app becomes blue and rounded!
