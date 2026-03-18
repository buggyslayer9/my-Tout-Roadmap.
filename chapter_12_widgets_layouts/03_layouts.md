# 12.3 Layout Containers

Widgets can't position themselves — they need a **container** (also called a layout widget) that arranges them on screen. GTK4 provides several layout strategies.

## GtkBox — Linear Stacking

The workhorse of GTK layouts. Stacks children either vertically or horizontally.

```c
// Vertical: children stacked top to bottom. 10px gap between each.
GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

// Horizontal: children placed side by side.
GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

// Add widgets in order.
gtk_box_append(GTK_BOX(vbox), label);
gtk_box_append(GTK_BOX(vbox), entry);
gtk_box_append(GTK_BOX(vbox), button);

// Set the box as the window's content.
gtk_window_set_child(GTK_WINDOW(window), vbox);
```

## GtkGrid — 2D Grid Layout

For form-like layouts with rows and columns. Think of it as a spreadsheet.

```c
GtkWidget *grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

// gtk_grid_attach(grid, widget, column, row, col_span, row_span)
gtk_grid_attach(GTK_GRID(grid), name_label,    0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(grid), name_entry,    1, 0, 1, 1);
gtk_grid_attach(GTK_GRID(grid), email_label,   0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), email_entry,   1, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 2, 2, 1);  // Spans 2 columns!
```

## Widget Properties: Margins, Expansion, Size

```c
// Margins: spacing OUTSIDE the widget (like CSS margin).
gtk_widget_set_margin_top(widget, 10);
gtk_widget_set_margin_bottom(widget, 10);
gtk_widget_set_margin_start(widget, 20);  // Left in LTR, right in RTL.
gtk_widget_set_margin_end(widget, 20);

// Expansion: fill all available space in the parent container.
gtk_widget_set_hexpand(entry, TRUE);   // Stretch horizontally.
gtk_widget_set_vexpand(text_view, TRUE); // Stretch vertically.

// Minimum size request.
gtk_widget_set_size_request(button, 200, 50);
```

## Alignment

```c
// Halign/Valign: position within the allocated space.
gtk_widget_set_halign(label, GTK_ALIGN_START);   // Left-aligned.
gtk_widget_set_halign(button, GTK_ALIGN_CENTER); // Centered.
gtk_widget_set_valign(image, GTK_ALIGN_END);     // Bottom-aligned.
```

## Nesting Containers

You can nest boxes inside boxes for complex layouts:

```c
// Main layout: vertical
GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

// Top row: horizontal
GtkWidget *top_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
gtk_box_append(GTK_BOX(top_bar), logo);
gtk_box_append(GTK_BOX(top_bar), title);

// Main box contains the top bar and a content area
gtk_box_append(GTK_BOX(main_box), top_bar);
gtk_box_append(GTK_BOX(main_box), content_area);
```
