/*
 * Chapter 11 — First GTK4 Window
 * Compile: gcc `pkg-config --cflags gtk4` first_window.c `pkg-config --libs gtk4` -o first_window
 * Run:     ./first_window
 */
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "My First GTK4 App");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *label = gtk_label_new("Hello, GTK4!");
    gtk_window_set_child(GTK_WINDOW(window), label);

    g_print("Window opened!\n");
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new(
        "com.example.firstwindow",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
