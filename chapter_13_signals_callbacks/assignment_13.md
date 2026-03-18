# Assignment 13: The Counter Application

Build a fully interactive counter with three buttons and dynamic state management.

## Task

Create a GTK4 application with:
- A label displaying "Count: 0"
- Three buttons: **[−]** (Decrement), **[+]** (Increment), **[Reset]**
- The label updates live with every click

## Visual Layout

```
┌──────────────────────────────┐
│                              │
│         Count: 0             │
│                              │
│    [ − ]  [ + ]  [ Reset ]   │
│                              │
└──────────────────────────────┘
```

## Requirements

1. **Define an `AppData` struct** with the label widget pointer and the current count:
```c
typedef struct {
    GtkWidget *count_label;
    int        count;
} AppData;
```

2. **Write three callback functions:**
   - `on_increment` — increments `data->count`, updates label
   - `on_decrement` — decrements `data->count`, updates label
   - `on_reset` — sets `data->count` to 0, updates label

3. **Update the label** using `snprintf` + `gtk_label_set_text`:
```c
char text[64];
snprintf(text, sizeof(text), "Count: %d", data->count);
gtk_label_set_text(GTK_LABEL(data->count_label), text);
```

4. **Layout:** Use a vertical `GtkBox` for the label and a horizontal `GtkBox` for the three buttons. Nest the horizontal box inside the vertical box.

5. **Pass `&data`** as `user_data` to all three `g_signal_connect()` calls.

## Bonus Challenges

1. The count cannot go below 0 (clamp at zero).
2. When count reaches 10, change the label color to red using `gtk_widget_add_css_class`.
3. Add a keyboard shortcut: pressing `R` resets the counter.

## Checklist
- [ ] All three buttons update the label correctly?
- [ ] Struct is declared `static` so it persists beyond `activate()`?
- [ ] Compiles with zero warnings?
