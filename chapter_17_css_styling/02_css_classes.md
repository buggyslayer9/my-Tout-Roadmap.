# 17.2 CSS Classes

Just like in HTML/CSS, directly styling widget types (like styling all `button`s) is usually too broad. The preferred way to style widgets in GTK4 is by using **CSS classes**.

## Adding Classes in C

You assign classes to widgets in your C code:

```c
GtkWidget *submit_btn = gtk_button_new_with_label("Submit");
GtkWidget *error_label = gtk_label_new("Invalid input.");

// Add a custom CSS class. You can add as many as you want.
gtk_widget_add_css_class(submit_btn, "primary-action");
gtk_widget_add_css_class(error_label, "error-text");

// You can also remove them dynamically (e.g., when the error is fixed)
// gtk_widget_remove_css_class(error_label, "error-text");
```

## Targeting Classes in CSS

Then, target those specific classes in your CSS string or file using the `.` selector:

```css
/* Only affects widgets with the "primary-action" class */
.primary-action {
    background-color: #4CAF50;
    color: white;
    font-weight: bold;
    border-radius: 8px;
}

.primary-action:hover {
    background-color: #45a049;
}

/* Only affects widgets with the "error-text" class */
.error-text {
    color: #f44336;
    font-weight: bold;
    font-size: 14px;
}
```

## Built-in GTK4 Classes

GTK4 themes (like Adwaita) come with pre-defined style classes. You don't even need to write CSS for these — just add the class!

| Class string | Visual Effect |
|--------------|---------------|
| `"suggested-action"` | Primary blue button (e.g., Save, Submit) |
| `"destructive-action"` | Red button (e.g., Delete, Remove) |
| `"flat"` | Removes the button border and background until hovered |
| `"circular"` | Forces a widget into a circle (great for icon buttons) |
| `"title"` | Large, bold text for headings |
| `"dim-label"` | Faded text for secondary information |

```c
// Instantly get a red warning button without writing a single line of CSS!
gtk_widget_add_css_class(delete_btn, "destructive-action");
```
