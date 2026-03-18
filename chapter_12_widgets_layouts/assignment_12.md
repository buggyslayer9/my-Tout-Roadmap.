# Assignment 12: The Contact Form

Build a clean, professional contact form using GTK4's grid layout system.

## Task

Create a GTK4 application with a `GtkGrid`-based form containing:
- Three labeled input fields: **Name**, **Email**, **Phone**
- A **Submit** button spanning the full width at the bottom

## Requirements

1. Use `GtkGrid` as the main layout (not `GtkBox`).
2. **Column 0**: `GtkLabel` widgets ("Name:", "Email:", "Phone:").
3. **Column 1**: `GtkEntry` widgets for each field.
4. Entries should expand horizontally (`gtk_widget_set_hexpand`).
5. The Submit button should span 2 columns on the last row.
6. Set 10px margins on the grid for padding around the window edges.
7. Set 8px row spacing and 12px column spacing.

## Visual Layout

```
┌──────────────────────────────────────┐
│  Name:    [____________________]     │
│  Email:   [____________________]     │
│  Phone:   [____________________]     │
│  [          Submit             ]     │
└──────────────────────────────────────┘
```

## Key Functions

```c
GtkWidget *grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
gtk_grid_set_column_spacing(GTK_GRID(grid), 12);
gtk_grid_attach(GTK_GRID(grid), widget, col, row, col_span, row_span);
gtk_widget_set_hexpand(entry, TRUE);
gtk_widget_set_margin_top(grid, 10);
```

## Bonus Challenge

Connect the Submit button's `"clicked"` signal to a callback that reads the text from all three entries and prints them to the terminal.

```c
// Reading entry text:
GtkEntryBuffer *buf = gtk_entry_get_buffer(GTK_ENTRY(name_entry));
const char *name = gtk_entry_buffer_get_text(buf);
g_print("Name: %s\n", name);
```

## Checklist
- [ ] Grid has 3 rows of label+entry, plus 1 row with the button?
- [ ] Submit button spans 2 columns?
- [ ] Entries expand to fill available width?
- [ ] Compiles with zero warnings?
