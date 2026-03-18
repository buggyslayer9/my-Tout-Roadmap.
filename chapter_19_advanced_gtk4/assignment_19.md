# Assignment 19: The Advanced Note Taker

It's time to supercharge the Note-Taking app you built in Assignment 18 using advanced GTK4 systems. 

## Task

Extend your GTK4 Note-Taker with Application Menus, Persistent Settings, and standard File Dialogs.

## Requirements

### 1. The GMenu & GAction Infrastructure
- Create a `GMenu` attached to a `GtkMenuButton` in the right side of the HeaderBar.
- It must contain three `GAction`-backed menu items:
  - **"New Note"** (`app.new`)
  - **"Save File As..."** (`app.save-as`)
  - **"Quit"** (`app.quit`)
- Quitting must gracefully shut down the app.

### 2. GSettings Integration
- Create a `gschema.xml` file with a boolean key: `dark-theme`.
- Add a `GtkSwitch` somewhere in your layout (perhaps in the HeaderBar).
- **Bind** the `GSettings` key to the switch.
- When the setting is true, alter the app's visual state (e.g., set the `gtk-application-prefer-dark-theme` property on the global `GtkSettings` object).

### 3. File Dialog Integration
- When the user selects **"Save File As..."** from the menu, open a `GtkFileDialog` to ask them where to save.
- When they select a valid path, dump all notes in the `GList` into that plain text file.

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **GMenu & GSimpleAction** - Abstractions for menu commands.
2. **GSettings** - XML schemas, compiling schemas, and `g_settings_bind`.
3. **GtkFileDialog** - Specifically `gtk_file_dialog_save()` (which operates asynchronously!).
4. **C File I/O** - Calling `fopen`, `fprintf`, and `fclose`.

---

## Sources

- [GMenu](https://docs.gtk.org/gio/class.Menu.html)
- [GSimpleAction](https://docs.gtk.org/gio/class.SimpleAction.html)
- [GSettings](https://docs.gtk.org/gio/class.Settings.html)
- [GtkFileDialog](https://docs.gtk.org/gtk4/class.FileDialog.html)
- [GtkSettings (for Dark Mode)](https://docs.gtk.org/gtk4/class.Settings.html)

---

## Hints

### Dark Mode Toggle in GTK4
How do you change the whole app to dark mode?

```c
GtkSettings *global_settings = gtk_settings_get_default();
g_object_set(global_settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
```

### Async File Dialog
Modern file dialogs in GTK4 no longer block the thread. You must supply a callback format.

```c
static void on_save_dialog_finish(GObject *source, GAsyncResult *result, gpointer user_data) {
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
    GError *err = NULL;
    
    // Get the GFile the user chose
    GFile *file = gtk_file_dialog_save_finish(dialog, result, &err);
    if (!file) {
        g_print("User cancelled or error: %s\n", err->message);
        return;
    }
    
    // Extract the raw file path string
    char *path = g_file_get_path(file);
    
    // --- NOW DO YOUR STANDARD C FILE I/O HERE using 'path' ---
    
    g_free(path);
    g_object_unref(file);
}

// In your app.save-as callback:
GtkFileDialog *dialog = gtk_file_dialog_new();
gtk_file_dialog_set_title(dialog, "Export Notes");
gtk_file_dialog_save(dialog, GTK_WINDOW(app_window), NULL, on_save_dialog_finish, my_data);
```

### Don't Forge to Compile Schemas
You **must** run `glib-compile-schemas .` in the exact directory where your `com.example.myapp.gschema.xml` file lives before running your C executable. Otherwise, `g_settings_new` will crash.
