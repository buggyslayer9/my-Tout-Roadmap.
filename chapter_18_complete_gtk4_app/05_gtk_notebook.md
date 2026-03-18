# 18.5 GtkNotebook: Tabbed Interfaces

When your application has distinct sections (like "Settings", "Profile", "Logs"), flipping between views manually is tedious. `GtkNotebook` provides a classic tabbed layout.

## Creating Tabs

```c
#include <gtk/gtk.h>

GtkWidget *setup_tabs() {
    // 1. Create the Notebook container
    GtkWidget *notebook = gtk_notebook_new();

    // 2. Create Content for Tab 1
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(page1), gtk_label_new("Welcome to the General Settings."));
    
    // Create the Label that appears IN the tab itself
    GtkWidget *tab1_label = gtk_label_new("General");
    
    // Append the page
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, tab1_label);


    // 3. Create Content for Tab 2
    GtkWidget *page2 = gtk_label_new("Network settings go here.");
    GtkWidget *tab2_label = gtk_label_new("Network");
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, tab2_label);

    return notebook;
}
```

## Useful Notebook Properties

```c
// Move tabs to the Left, Right, Top, or Bottom
gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_LEFT);

// Allow the user to drag and reorder tabs
gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook), page1, TRUE);

// Switch to a specific tab programmatically (zero-indexed)
gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 1);
```
