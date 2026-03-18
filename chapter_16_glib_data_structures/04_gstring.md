# 16.4 GString: The Dynamic String Builder

Standard C strings (`char *`) are a headache when you need to continuously concatenate or build strings of unknown length. You constantly have to track bounds, `realloc` memory, and avoid buffer overflows.

`GString` solves this. It's similar to `StringBuilder` in Java or `std::string` in C++.

## Basic Usage

```c
#include <glib.h>

int main() {
    // 1. Create a dynamic string based on an initial capacity or string.
    GString *str = g_string_new("Score: ");

    // 2. Append efficiently
    g_string_append(str, "100");
    g_string_append_c(str, '!');

    // 3. Append with formatting (like printf)
    g_string_append_printf(str, " (Level %d)", 5);

    // 4. Accessing the raw C string (for GTK functions)
    // The string is guaranteed to be null-terminated.
    g_print("Final String: %s\n", str->str);
    
    // We can also check the current length.
    g_print("Length: %" G_GSIZE_FORMAT "\n", str->len);

    // 5. Memory Management
    // The TRUE argument tells GLib to free BOTH the GString struct 
    // AND the underlying character buffer.
    g_string_free(str, TRUE);

    return 0;
}
```

## `g_string_free` Trick

Sometimes you use `GString` to build a string, but you want to *keep* the final `char *` and just discard the builder struct. In that case, pass `FALSE` to `g_string_free`:

```c
GString *builder = g_string_new("");
g_string_append(builder, "Some constructed text...");

// Free the GString metadata, but RETURN the underlying string!
char *final_c_str = g_string_free(builder, FALSE); 

// Now you own final_c_str and must g_free() it eventually.
g_print("%s\n", final_c_str);
g_free(final_c_str);
```
