/*
 * Chapter 16 — GLib Stopwatch (Timeouts, GString)
 * Compile: gcc `pkg-config --cflags gtk4` stopwatch.c `pkg-config --libs gtk4` -o stopwatch
 * Run:     ./stopwatch
 */
#include <gtk/gtk.h>

typedef struct {
    GtkLabel *label;
    int       tenths;      // Time in tenths of a second
    guint     timer_id;    // Timer source ID (0 = stopped)
} StopwatchData;

static void update_display(StopwatchData *data) {
    int minutes = data->tenths / 600;
    int seconds = (data->tenths % 600) / 10;
    int frac    = data->tenths % 10;

    GString *str = g_string_new(NULL);
    g_string_printf(str, "%02d:%02d.%d", minutes, seconds, frac);
    gtk_label_set_text(data->label, str->str);
    g_string_free(str, TRUE);
}

static gboolean on_tick(gpointer user_data) {
    StopwatchData *data = (StopwatchData *)user_data;
    data->tenths++;
    update_display(data);
    return G_SOURCE_CONTINUE;
}

static void on_start(GtkButton *btn, gpointer user_data) {
    StopwatchData *data = (StopwatchData *)user_data;
    if (data->timer_id == 0) {
        data->timer_id = g_timeout_add(100, on_tick, data);
    }
}

static void on_stop(GtkButton *btn, gpointer user_data) {
    StopwatchData *data = (StopwatchData *)user_data;
    if (data->timer_id != 0) {
        g_source_remove(data->timer_id);
        data->timer_id = 0;
    }
}

static void on_reset(GtkButton *btn, gpointer user_data) {
    StopwatchData *data = (StopwatchData *)user_data;
    on_stop(btn, user_data);
    data->tenths = 0;
    update_display(data);
}

static void activate(GtkApplication *app, gpointer user_data) {
    StopwatchData *data = (StopwatchData *)user_data;

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Stopwatch");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 180);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_widget_set_margin_start(vbox, 30);
    gtk_widget_set_margin_end(vbox, 30);

    // Time display
    GtkWidget *label = gtk_label_new("00:00.0");
    data->label = GTK_LABEL(label);
    gtk_box_append(GTK_BOX(vbox), label);

    // Buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *start_btn = gtk_button_new_with_label("Start");
    GtkWidget *stop_btn  = gtk_button_new_with_label("Stop");
    GtkWidget *reset_btn = gtk_button_new_with_label("Reset");

    g_signal_connect(start_btn, "clicked", G_CALLBACK(on_start), data);
    g_signal_connect(stop_btn,  "clicked", G_CALLBACK(on_stop),  data);
    g_signal_connect(reset_btn, "clicked", G_CALLBACK(on_reset), data);

    gtk_widget_set_hexpand(start_btn, TRUE);
    gtk_widget_set_hexpand(stop_btn, TRUE);
    gtk_widget_set_hexpand(reset_btn, TRUE);

    gtk_box_append(GTK_BOX(hbox), start_btn);
    gtk_box_append(GTK_BOX(hbox), stop_btn);
    gtk_box_append(GTK_BOX(hbox), reset_btn);
    gtk_box_append(GTK_BOX(vbox), hbox);

    gtk_window_set_child(GTK_WINDOW(window), vbox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    StopwatchData data = {NULL, 0, 0};

    GtkApplication *app = gtk_application_new(
        "com.example.stopwatch",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), &data);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
