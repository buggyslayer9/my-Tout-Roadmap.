# 14.1 Alert Dialogs (GTK4)

Alert dialogs are popup windows that demand the user's attention — confirmations, warnings, error messages. In GTK4, `GtkAlertDialog` replaces the older `GtkMessageDialog` from GTK3.

## Creating an Alert Dialog

```c
#include <gtk/gtk.h>

// 2. Handle the user's response.
static void on_dialog_response(GObject *source, GAsyncResult *result, gpointer user_data) {
    (void)user_data;
    GtkAlertDialog *dialog = GTK_ALERT_DIALOG(source);
    GError *err = NULL;
    int response = gtk_alert_dialog_choose_finish(dialog, result, &err);
    
    if (response == 0) {
        g_print("User chose: Cancel\n");
    } else if (response == 1) {
        g_print("User chose: OK\n");
    }
}

// 1. Build and show the dialog.
static void show_confirm_dialog(GtkWindow *parent) {
    GtkAlertDialog *dialog = gtk_alert_dialog_new("Are you sure?");
    gtk_alert_dialog_set_detail(dialog, "This action cannot be undone.");
    gtk_alert_dialog_set_buttons(dialog, (const char *[]){"Cancel", "OK", NULL});
    gtk_alert_dialog_set_default_button(dialog, 1);   // "OK" is default
    gtk_alert_dialog_set_cancel_button(dialog, 0);     // "Cancel" maps to Escape key
    
    // Show asynchronously — does NOT block the main loop!
    gtk_alert_dialog_choose(dialog, parent, NULL, on_dialog_response, NULL);
    g_object_unref(dialog);
}
```

## Key Points

- **Asynchronous:** The dialog doesn't block your code. GTK shows it and immediately returns. Your callback fires when the user clicks a button.
- **Button indices:** The response value is the zero-based index of the button the user clicked. In the example above: 0 = "Cancel", 1 = "OK".
- **Modal behavior:** Alert dialogs are automatically modal — the user can't interact with the parent window until the dialog is dismissed.
