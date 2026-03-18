# 19.2 GMenu, GAction, & Application Menus

In older GTK versions, you built menus widget-by-widget (`GtkMenuItem`, `GtkMenu`). In modern GTK4, menus represent abstract models (`GMenu`) that map entirely to abstract actions (`GAction`).

This abstraction means the same `GAction` (e.g., "app.quit") can be triggered by a menu click, a keyboard shortcut (Ctrl+Q), or a command-line flag.

## 1. Creating Actions

First, define the actions on your `GtkApplication`:

```c
#include <gtk/gtk.h>

static void on_quit_action(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    GtkApplication *app = GTK_APPLICATION(user_data);
    g_print("Quitting application naturally...\n");
    g_application_quit(G_APPLICATION(app));
}

static void on_new_action(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    g_print("Creating new document...\n");
}

// In your application startup/activate function:
void setup_actions(GtkApplication *app) {
    // Create the "quit" action
    GSimpleAction *quit_action = g_simple_action_new("quit", NULL);
    g_signal_connect(quit_action, "activate", G_CALLBACK(on_quit_action), app);
    
    // Register it with the application (becomes "app.quit")
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));

    // Create a "new" action
    GSimpleAction *new_action = g_simple_action_new("new", NULL);
    g_signal_connect(new_action, "activate", G_CALLBACK(on_new_action), app);
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(new_action));
}
```

## 2. Defining the Menu Model

The `GMenu` describes the structure without caring about how it looks.

```c
GMenu *create_main_menu() {
    GMenu *menu = g_menu_new();
    
    // g_menu_append(menu, "Label visible to user", "action.name");
    g_menu_append(menu, "New Document", "app.new");
    g_menu_append(menu, "Quit", "app.quit");
    
    return menu;
}
```

## 3. Connecting to the UI

In GTK4, application menus are usually hidden behind a "Hamburger" menu button (`GtkMenuButton`) located in the HeaderBar.

```c
void setup_ui(GtkApplicationWindow *window) {
    GtkWidget *header = gtk_header_bar_new();
    
    // 1. Create the menu button
    GtkWidget *menu_btn = gtk_menu_button_new();
    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(menu_btn), "open-menu-symbolic");
    
    // 2. Give it our abstract menu model
    GMenu *menu_model = create_main_menu();
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menu_btn), G_MENU_MODEL(menu_model));
    
    // 3. Add it to the header bar
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), menu_btn);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
}
```

By decoupling the *structure* (`GMenu`) from the *behavior* (`GAction`), GNOME handles keyboard shortcuts easily: you just map Ctrl+Q to `app.quit`, and it triggers the exact same logic.
