/*
 * Chapter 13 — Counter App (Signals & Callbacks)
 * Compile: gcc `pkg-config --cflags gtk4` counter.c `pkg-config --libs gtk4` -o counter
 * Run:     ./counter
 */
#include <gtk/gtk.h>

typedef struct {
    GtkLabel *label;
    int       count;
} AppData;

static void update_label(AppData *data) {
    char text[64];
    snprintf(text, sizeof(text), "Count: %d", data->count);
    gtk_label_set_text(data->label, text);
}

static void on_increment(GtkButton *btn, gpointer user_data) {
    AppData *data = (AppData *)user_data;
    data->count++;
    update_label(data);
}

static void on_decrement(GtkButton *btn, gpointer user_data) {
    AppData *data = (AppData *)user_data;
    data->count--;
    update_label(data);
}

static void on_reset(GtkButton *btn, gpointer user_data) {
    AppData *data = (AppData *)user_data;
    data->count = 0;
    update_label(data);
}

static void activate(GtkApplication *app, gpointer user_data) {
    AppData *data = (AppData *)user_data;

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Counter");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_widget_set_margin_start(vbox, 40);
    gtk_widget_set_margin_end(vbox, 40);

    // Counter label
    GtkWidget *label = gtk_label_new("Count: 0");
    data->label = GTK_LABEL(label);
    gtk_box_append(GTK_BOX(vbox), label);

    // Buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *inc_btn = gtk_button_new_with_label("+1");
    GtkWidget *dec_btn = gtk_button_new_with_label("-1");
    GtkWidget *reset_btn = gtk_button_new_with_label("Reset");

    g_signal_connect(inc_btn, "clicked", G_CALLBACK(on_increment), data);
    g_signal_connect(dec_btn, "clicked", G_CALLBACK(on_decrement), data);
    g_signal_connect(reset_btn, "clicked", G_CALLBACK(on_reset), data);

    gtk_widget_set_hexpand(inc_btn, TRUE);
    gtk_widget_set_hexpand(dec_btn, TRUE);
    gtk_widget_set_hexpand(reset_btn, TRUE);

    gtk_box_append(GTK_BOX(hbox), dec_btn);
    gtk_box_append(GTK_BOX(hbox), reset_btn);
    gtk_box_append(GTK_BOX(hbox), inc_btn);

    gtk_box_append(GTK_BOX(vbox), hbox);
    gtk_window_set_child(GTK_WINDOW(window), vbox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    AppData data = {NULL, 0};

    GtkApplication *app = gtk_application_new(
        "com.example.counter",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), &data);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
