# 12.2 Common Widgets

These are the building blocks you'll use in 90% of your GTK4 applications.

## GtkLabel — Display Text

```c
GtkWidget *label = gtk_label_new("Hello, World!");

// Pango markup for rich text (bold, italic, color)
gtk_label_set_markup(GTK_LABEL(label), "<b>Bold</b> and <i>italic</i>");

// Wrap long text
gtk_label_set_wrap(GTK_LABEL(label), TRUE);
```

## GtkButton — Clickable Action

```c
GtkWidget *button = gtk_button_new_with_label("Click Me");

// You'll connect a callback in Chapter 13:
// g_signal_connect(button, "clicked", G_CALLBACK(on_click), NULL);
```

## GtkEntry — Single-Line Text Input

```c
GtkWidget *entry = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Type here...");

// Read the text later:
// GtkEntryBuffer *buf = gtk_entry_get_buffer(GTK_ENTRY(entry));
// const char *text = gtk_entry_buffer_get_text(buf);
```

## GtkCheckButton — Toggle Switch

```c
GtkWidget *check = gtk_check_button_new_with_label("I agree to the terms");

// Read state later:
// gboolean is_checked = gtk_check_button_get_active(GTK_CHECK_BUTTON(check));
```

## GtkImage — Display Images and Icons

```c
// From a system icon
GtkWidget *icon = gtk_image_new_from_icon_name("dialog-information");

// From a file path
GtkWidget *photo = gtk_image_new_from_file("/path/to/image.png");
```

## GtkSpinButton — Numeric Input with Arrows

```c
GtkAdjustment *adj = gtk_adjustment_new(0, 0, 100, 1, 10, 0);
GtkWidget *spin = gtk_spin_button_new(adj, 1, 0);
```

## Quick Reference

| Widget | Purpose | Constructor |
|--------|---------|-------------|
| `GtkLabel` | Static text | `gtk_label_new()` |
| `GtkButton` | Clickable button | `gtk_button_new_with_label()` |
| `GtkEntry` | Text input | `gtk_entry_new()` |
| `GtkCheckButton` | Boolean toggle | `gtk_check_button_new_with_label()` |
| `GtkImage` | Display image/icon | `gtk_image_new_from_icon_name()` |
| `GtkSpinButton` | Number picker | `gtk_spin_button_new()` |
| `GtkSwitch` | On/off toggle | `gtk_switch_new()` |
