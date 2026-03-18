/*
 * Chapter 12 — Widgets and Layouts (Contact Form)
 * Compile: gcc `pkg-config --cflags gtk4` contact_form.c `pkg-config --libs gtk4` -o contact_form
 * Run:     ./contact_form
 */
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Contact Form");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);

    // Grid layout
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_margin_top(grid, 20);
    gtk_widget_set_margin_bottom(grid, 20);
    gtk_widget_set_margin_start(grid, 20);
    gtk_widget_set_margin_end(grid, 20);

    // Name row
    GtkWidget *name_label = gtk_label_new("Name:");
    GtkWidget *name_entry = gtk_entry_new();
    gtk_widget_set_hexpand(name_entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 0, 1, 1);

    // Email row
    GtkWidget *email_label = gtk_label_new("Email:");
    GtkWidget *email_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "you@example.com");
    gtk_widget_set_hexpand(email_entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), email_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 1, 1, 1);

    // Phone row
    GtkWidget *phone_label = gtk_label_new("Phone:");
    GtkWidget *phone_entry = gtk_entry_new();
    gtk_widget_set_hexpand(phone_entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), phone_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), phone_entry, 1, 2, 1, 1);

    // Submit button spanning both columns
    GtkWidget *submit = gtk_button_new_with_label("Submit");
    gtk_grid_attach(GTK_GRID(grid), submit, 0, 3, 2, 1);

    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new(
        "com.example.contactform",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
