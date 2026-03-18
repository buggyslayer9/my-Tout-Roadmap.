# 13.6 Common GTK4 Signals

Every widget emits specific signals. Here's the reference table you'll use constantly.

## Widget Signal Reference

| Widget | Signal | Fires When |
|--------|--------|-----------|
| `GtkButton` | `"clicked"` | User clicks the button |
| `GtkEntry` | `"activate"` | User presses Enter in the field |
| `GtkEntry` | `"changed"` | Text content changes (any keystroke) |
| `GtkCheckButton` | `"toggled"` | Checkbox state changes |
| `GtkSwitch` | `"notify::active"` | Switch toggled on/off |
| `GtkSpinButton` | `"value-changed"` | Numeric value changes |
| `GtkWindow` | `"destroy"` | Window is being destroyed |
| `GtkWindow` | `"close-request"` | User clicks the X button (return TRUE to prevent close) |
| `GtkApplication` | `"activate"` | Application is launched/re-focused |

## Callback Signatures

Each signal has a specific callback signature. The GTK documentation tells you exactly what parameters your callback receives:

```c
// "clicked" on GtkButton
void callback(GtkButton *button, gpointer user_data);

// "activate" on GtkEntry (Enter pressed)
void callback(GtkEntry *entry, gpointer user_data);

// "close-request" on GtkWindow (return TRUE to prevent closing)
gboolean callback(GtkWindow *window, gpointer user_data);

// "toggled" on GtkCheckButton
void callback(GtkCheckButton *check, gpointer user_data);
```

> **Finding Signals:** The official [GTK4 API Reference](https://docs.gtk.org/gtk4/) lists every signal for every widget class. Bookmark it.
