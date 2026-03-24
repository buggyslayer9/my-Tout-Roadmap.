# 12.5 Forms and Validation in GTK4

Many real desktop applications are forms.

Examples:

- login forms
- contact forms
- settings panels
- task editors
- profile screens

That means it is not enough to place widgets on a window. You also need to collect input clearly and validate it.

## What Makes A Good Form

A good form is:

- easy to scan
- clearly labeled
- consistent in spacing
- honest about errors
- hard to misuse

This is a design problem and a coding problem at the same time.

## Common Form Widgets

In GTK4, forms often use:

- `GtkEntry` for text input
- `GtkPasswordEntry` for passwords
- `GtkCheckButton` for booleans
- `GtkDropDown` for limited choices
- `GtkButton` for submit and cancel
- `GtkGrid` or `GtkBox` for layout

## A Simple Form Layout

```c
GtkWidget *grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
gtk_grid_set_column_spacing(GTK_GRID(grid), 8);

GtkWidget *name_label = gtk_label_new("Name:");
GtkWidget *name_entry = gtk_entry_new();

GtkWidget *email_label = gtk_label_new("Email:");
GtkWidget *email_entry = gtk_entry_new();

GtkWidget *save_button = gtk_button_new_with_label("Save");

gtk_grid_attach(GTK_GRID(grid), name_label, 0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 0, 1, 1);
gtk_grid_attach(GTK_GRID(grid), email_label, 0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), save_button, 1, 2, 1, 1);
```

This is already more maintainable than throwing widgets onto a window without structure.

## Validation Basics

Validation means checking whether input is acceptable before you continue.

Examples:

- required text is not empty
- email looks roughly valid
- a number field contains a number
- password length is reasonable

Validation helps the user and protects your app logic.

## A Simple Callback Example

```c
static void on_save_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));

    if (text == NULL || text[0] == '\0') {
        g_print("Name is required.\n");
        return;
    }

    g_print("Saved name: %s\n", text);
}
```

This is simple, but it teaches an important idea:

- validate first
- continue only if the input is acceptable

## Good Validation Habits

- keep error messages specific
- do not wait until the whole form is submitted if early feedback helps
- keep validation rules close to the form logic
- avoid vague messages like “invalid input”

Better:

- “Email is required.”
- “Age must be a number.”
- “Password must be at least 8 characters.”

## Visual Feedback

As your GUI gets stronger, you can improve form UX with:

- inline error labels
- CSS classes for invalid input
- disabled submit button until required fields are filled

That makes the app feel more intentional and more professional.

## Common Mistakes

- unlabeled fields
- inconsistent spacing
- validation only after a crash or failed save
- unclear error messages
- form callbacks that become too large and messy

## Learning Check

- Can I build a small form with labels, entries, and a submit button?
- Can I validate that a required field is not empty?
- Can I explain how form structure affects usability?

## Recommended Follow-Up

Build a small desktop form with:

- name
- email
- one checkbox
- save button
- validation feedback

This is a very useful bridge between widget basics and real desktop application design.
