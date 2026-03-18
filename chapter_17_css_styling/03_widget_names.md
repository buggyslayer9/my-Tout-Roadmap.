# 17.3 Widget Names (ID Selectors)

If CSS classes (`.class`) are for groups of widgets, Widget Names (`#name`) are for **unique, one-of-a-kind widgets**. This maps exactly to the ID attribute in HTML.

## Setting a Widget Name

```c
GtkWidget *status_bar = gtk_label_new("System Ready");

// Give this specific widget a unique name.
gtk_widget_set_name(status_bar, "main-status-bar");
```

## Targeting by Name in CSS

Use the `#` selector in your CSS to target the widget name:

```css
#main-status-bar {
    background-color: #263238;
    color: #b2dfdb;
    padding: 4px 12px;
    font-family: monospace;
    font-size: 12px;
}
```

## Classes vs Names

| Feature | Name (`#id`) | Class (`.class`) |
|---------|-------------|------------------|
| Uniqueness | MUST be unique per window | Shared by multiple widgets |
| Specificity | Higher (overrides classes) | Lower |
| Use case | A main header, a specific status bar | All primary buttons, all error labels |
| C Function | `gtk_widget_set_name()` | `gtk_widget_add_css_class()` |

> **Instructor Tip:** As a standard best practice — just like in web development — you should rely on **CSS classes** for 95% of your styling. Names should be reserved strictly for major structural components that only exist once.
