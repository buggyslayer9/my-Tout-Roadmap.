# 20.3 Capstone Architecture

An application of this size cannot live in `main.c`. You must compartmentalize the logic.

## Recommended File Structure

```text
task_manager/
├── meson.build           ← Your build instructions
├── src/
│   ├── main.c            ← GtkApplication setup and entry point.
│   ├── app_window.c      ← The main window, header bar, and tabs.
│   ├── app_window.h
│   ├── task_list.c       ← Logic for drawing rows, filtering, and searching.
│   ├── task_list.h     
│   ├── task_dialog.c     ← The pop-up window for adding/editing tasks.
│   ├── task_dialog.h   
│   ├── storage.c         ← File I/O: fread, fwrite, loading data models.
│   └── storage.h
└── data/
    └── styles.css        ← Application styling.
```

## State Management

How do these separate files talk to each other? They share a common "Application State" pointer. Create a struct in a central header (e.g. `storage.h` or `types.h`) that holds the master data:

```c
typedef struct {
    GList *tasks;               // Master list of 'Task' structs
    GtkListBox *list_ui;        // Pointer to the UI list widget
    GtkWidget *main_window;     // Pointer to the main application window
} AppState;
```

When you initialize your `app_window`, you create this `AppState` on the heap, and pass that pointer to your `task_list`, `task_dialog`, and `storage` modules so they can all read from and update the same data.
