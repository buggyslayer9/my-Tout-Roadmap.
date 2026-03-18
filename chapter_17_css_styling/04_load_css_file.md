# 17.4 Loading CSS from a File

Hardcoding CSS inside C string literals (`"button { color: red; }"`) is horrible for maintainability. As soon as your app grows beyond a trivial script, you need to extract your styles into a dedicated `.css` file.

## Loading from Disk

```c
#include <gtk/gtk.h>

void load_external_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    
    // Load from a file path instead of a string.
    gtk_css_provider_load_from_path(provider, "styles.css");
    
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    g_object_unref(provider);
}
```

## Important Note on Paths

When you use `gtk_css_provider_load_from_path("styles.css")`, GTK looks for `styles.css` in the **current working directory** where you executed the binary, *not* necessarily where the binary sits.

During local development, running `./my_app` while sitting in the project root works fine. But for production apps, relying on relative paths is brittle. 

### The Production Solution: GResource

For professional software, you use **GResource** to embed the `.css` file (and icons, UI files, etc.) directly into the compiled C binary. 

Then you load it like this:
```c
// The file is physically compiled into the executable file!
gtk_css_provider_load_from_resource(provider, "/com/yourname/yourapp/styles.css");
```
*(We will cover GResource in detail in the Advanced GTK4 chapter).*

## Example `styles.css`

```css
/* Global application background */
window {
    background-color: #f0f0f0;
}

/* All buttons */
button {
    border-radius: 4px;
    padding: 8px 16px;
    transition: background-color 200ms ease; /* Smooth hover animations! */
}

/* Custom classes */
.card-panel {
    background-color: white;
    border-radius: 12px;
    padding: 20px;
    box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15); /* Drop shadows work perfectly */
    margin: 16px;
}

.warning-text {
    color: #ff9800;
    font-weight: bold;
    font-size: 1.2em; /* Em sizes work too */
}
```
