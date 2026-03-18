# Assignment 20: The Final Capstone

This is it. Time to build the **Personal Task Manager**.

## Acceptance Criteria

Your application must successfully implement the following:

- [ ] **Meson Build:** Compiles flawlessly using `meson setup build` and `meson compile -C build`.
- [ ] **Architecture:** Code is split across at least 4 source files (`main.c`, `window.c`, `list.c`, `storage.c`).
- [ ] **Data Model:** Uses a fixed-size `Task` struct to store data.
- [ ] **File I/O:** Clicking "Quit" or closing the window calls an `fwrite` function saving all tasks to `tasks.dat`. Launching the app calls `fread` to load them back.
- [ ] **Data Binding:** Adding a task through the Dialog securely appends the `Task` struct to a `GList` and adds a row to the `GtkListBox`.
- [ ] **Interactivity:** Clicking the `GtkCheckButton` on a task row instantly strikes through the text via CSS and updates the underlying `Task->completed` boolean.
- [ ] **Search:** Typing in the `GtkSearchEntry` immediately hides rows that don't match the text.
- [ ] **Style:** The application uses CSS. "High Priority" tasks must have red badges. 

## Hints and Snippets

### 1. Custom Rows in GtkListBox
You don't just put labels in a list box. You put standard horizontal `GtkBox` layouts inside the list box rows!

```c
GtkWidget *create_task_row(Task *task) {
    GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Checkbox
    GtkWidget *check = gtk_check_button_new();
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check), task->completed);
    gtk_box_append(GTK_BOX(row_box), check);
    
    // Title
    GtkWidget *title = gtk_label_new(task->title);
    gtk_widget_set_hexpand(title, TRUE); // Push date to the far right
    gtk_box_append(GTK_BOX(row_box), title);
    
    // Date
    GtkWidget *date = gtk_label_new(task->due_date);
    gtk_box_append(GTK_BOX(row_box), date);
    
    return row_box;
}
```

### 2. Filtering a ListBox
`GtkListBox` has a built-in function that decides whether a row should be visible. 

```c
// Define the filter rule
static gboolean filter_function(GtkListBoxRow *row, gpointer user_data) {
    // Return TRUE to show the row, FALSE to hide it.
    // e.g., if user is on the "Pending" tab, and task->completed is TRUE, return FALSE.
    return TRUE; 
}

// Apply it to the list
gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox), filter_function, state_pointer, NULL);

// Call this function whenever the user types in the search bar or clicks a tab!
gtk_list_box_invalidate_filter(GTK_LIST_BOX(listbox));
```

### 3. Binary I/O Refresher

```c
// Saving
FILE *f = fopen("tasks.dat", "wb");
int count = g_list_length(state->tasks);
fwrite(&count, sizeof(int), 1, f);   // Save the total number of tasks first

for (GList *iter = state->tasks; iter != NULL; iter = iter->next) {
    Task *task = (Task *)iter->data;
    fwrite(task, sizeof(Task), 1, f); // Save the entire struct at once!
}
fclose(f);
```

## Completion

When you have built this application, you are no longer a beginner. You have successfully navigated direct memory management, the intricacies of the GObject type system, multi-file compilation, and event-driven GUI architecture.

Good luck!
