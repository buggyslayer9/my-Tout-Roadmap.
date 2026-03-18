# Assignment 14: The Delete Confirmation Workflow

Build an app that shows a list of items, each with a "Delete" button. Clicking Delete opens a confirmation dialog before removing the item.

## Visual Layout

```
┌──────────────────────────────────────┐
│                                      │
│  Document 1                [Delete]  │
│  Document 2                [Delete]  │
│  Document 3                [Delete]  │
│                                      │
└──────────────────────────────────────┘
```

After clicking Delete on "Document 2", a dialog appears:
```
┌─────────────────────────────┐
│  Delete "Document 2"?       │
│  This action cannot be      │
│  undone.                    │
│                             │
│     [Cancel]    [Delete]    │
└─────────────────────────────┘
```

## Requirements

1. Display 3 items, each in a horizontal `GtkBox` with a `GtkLabel` and a `GtkButton`.
2. When Delete is clicked, show a `GtkAlertDialog` with the item name.
3. If the user confirms (clicks "Delete"), remove the item's row from the parent container using `gtk_widget_unparent()`.
4. If cancelled, do nothing.

## Data Pattern

```c
typedef struct {
    const char *item_name;
    GtkWidget  *item_row;   // The horizontal box to remove.
} DeleteData;
```

Allocate a `DeleteData` with `g_new()` for each delete button. Pass it as `user_data`. Free it with `g_free()` in the dialog callback.

## Response Callback Skeleton

```c
static void on_delete_response(GObject *source, GAsyncResult *result, gpointer user_data) {
    GtkAlertDialog *alert = GTK_ALERT_DIALOG(source);
    DeleteData *data = (DeleteData *)user_data;
    
    int response = gtk_alert_dialog_choose_finish(alert, result, NULL);
    if (response == 1) {
        gtk_widget_unparent(data->item_row);
        g_print("Deleted: %s\n", data->item_name);
    }
    g_free(data);
}
```

## Checklist
- [ ] Dialog shows the correct item name?
- [ ] Only removes the item on confirmation, not cancel?
- [ ] No crashes after removing all items?
- [ ] `g_free(data)` is called to prevent memory leaks?
