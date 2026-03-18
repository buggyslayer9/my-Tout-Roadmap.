# Assignment 18: The Note-Taking Application

You are now going to build a completely structured, multi-file GTK4 application.

## Task

Build a Note-Taking app featuring a HeaderBar, a Notebook (tabs), a ListBox for selecting notes, and a multiline TextView for editing them.

## Requirements

1. **Architecture:** Your code MUST be split into multiple files (`main.c`, `app_window.c`, `callbacks.c`, `data.c`).
2. **Build System:** Write a standard `Makefile` or a `meson.build` file to compile the project.
3. **UI Layout:**
    - Use `GtkHeaderBar` instead of the standard title bar. Include a "+ New" button.
    - Use `GtkNotebook` to create two tabs: **"All Notes"** and **"Trash"**.
    - The "All Notes" tab should contain a `GtkPaned` (split view).
        - Left side: A `GtkScrolledWindow` containing a `GtkListBox`.
        - Right side: A `GtkScrolledWindow` containing a `GtkTextView` for editing.
4. **Logic:**
    - Clicking a note in the ListBox loads its content into the TextView.
    - Adding a New note inserts a row into the ListBox and switches focus to the empty TextView.

## Visual Layout Spec

```
┌─────────────────────────────────────────────────────────┐
│  📝 Notes                                   [+ New]    │
├─────────────────────────────────────────────────────────┤
│  [All Notes]  [Trash]                                  │
├────────────────────┬────────────────────────────────────┤
│                    │                                    │
│  Grocery List      │  Don't forget to buy:            │
│  Meeting Notes  ←─→│  - Milk                          │
│  Ideas             │  - Bread                         │
│                    │  - GTK4 Book                     │
│                    │                                    │
│                    │                                    │
└────────────────────┴────────────────────────────────────┘
```

## `GtkTextView` Crash Course

A `GtkTextView` doesn't hold text directly. It holds a `GtkTextBuffer`.

```c
// 1. Create the view
GtkWidget *textview = gtk_text_view_new();

// 2. Wrap it in a ScrolledWindow (text views naturally overflow)
// ... standard scrolled window setup ...

// 3. Get the buffer to read/write text
GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));

// Set text
gtk_text_buffer_set_text(buffer, "Hello World", -1);

// Get text (requires iterators)
GtkTextIter start, end;
gtk_text_buffer_get_bounds(buffer, &start, &end);
char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
// ... use text ...
g_free(text);
```

## Application State (`data.h`)

You will need a robust state struct to pass around your components:

```c
typedef struct {
    GList *notes;              // Your data model
    GtkListBox *listbox;       // The UI list
    GtkTextView *textview;     // The UI editor
    gpointer current_note;     // Pointer to the actively edited note
} AppState;
```

## Checklist
- [ ] Project successfully compiles using `make` or `meson compile`?
- [ ] HeaderBar successfully replaces the OS title bar?
- [ ] `GtkPaned` allows smooth dragging between the list and the editor?
- [ ] Selecting a list item successfully loads text into the `GtkTextView` buffer?
