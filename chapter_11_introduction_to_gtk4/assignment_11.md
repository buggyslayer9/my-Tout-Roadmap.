# Assignment 11: Your First GTK4 Application

Time to put pixels on screen.

## Task

Create a GTK4 application that:

1. Opens a **600×400** window titled **"My First App"**.
2. Uses a proper application ID in reverse-DNS format.
3. Prints `"Window activated!"` to the terminal when the `activate` callback triggers.
4. Compiles cleanly with `-Wall -Wextra`.

## Requirements

1. Use `gtk_application_new()` with a unique ID like `"com.yourname.firstapp"`.
2. Connect the `"activate"` signal using `g_signal_connect()`.
3. Inside `activate()`:
   - Create a `GtkApplicationWindow`.
   - Set the title and default size.
   - Call `gtk_window_present()`.
   - Print a message with `g_print()` (GTK's cross-platform `printf`).
4. Clean up with `g_object_unref(app)` before returning.

## Compilation

```bash
gcc `pkg-config --cflags gtk4` -Wall -Wextra main.c `pkg-config --libs gtk4` -o my_first_app
./my_first_app
```

## Expected Result

**Terminal:**
```
Window activated!
```

**Screen:** A 600×400 window titled "My First App" appears. When you close it, the program exits.

## Bonus Challenge

Add a `GtkLabel` widget to the window that displays "Welcome to GTK4 Programming!" centered in the window.

**Hint:**
```c
GtkWidget *label = gtk_label_new("Welcome to GTK4 Programming!");
gtk_window_set_child(GTK_WINDOW(window), label);
```

## Checklist
- [ ] Application ID is in valid reverse-DNS format?
- [ ] Compiles with zero warnings using `-Wall -Wextra`?
- [ ] `g_object_unref(app)` is called before `return`?
- [ ] Window appears and can be closed cleanly?
