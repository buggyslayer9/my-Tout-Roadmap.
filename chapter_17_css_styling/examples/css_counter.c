/*
 * Chapter 17 — CSS Styled Counter
 * Compile: gcc `pkg-config --cflags gtk4` css_counter.c `pkg-config --libs gtk4` -o css_counter
 * Run:     ./css_counter
 */
#include <gtk/gtk.h>

typedef struct {
    GtkLabel *label;
    int       count;
} AppData;

static void update_label(AppData *data) {
    char text[32];
    snprintf(text, sizeof(text), "%d", data->count);
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

static void load_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
        "window {"
        "  background-color: #1a1a2e;"
        "}"
        "#counter-label {"
        "  font-size: 64px;"
        "  font-weight: bold;"
        "  color: #e94560;"
        "  margin: 20px;"
        "}"
        ".increment-btn {"
        "  background-color: #0f3460;"
        "  color: #e94560;"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "  border-radius: 8px;"
        "  padding: 10px 24px;"
        "  min-width: 80px;"
        "}"
        ".increment-btn:hover {"
        "  background-color: #16213e;"
        "}"
        ".decrement-btn {"
        "  background-color: #533483;"
        "  color: white;"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "  border-radius: 8px;"
        "  padding: 10px 24px;"
        "  min-width: 80px;"
        "}"
        ".decrement-btn:hover {"
        "  background-color: #4a2d70;"
        "}"
        ".reset-btn {"
        "  background-color: transparent;"
        "  color: #8a8a8a;"
        "  font-size: 14px;"
        "  border: 1px solid #8a8a8a;"
        "  border-radius: 8px;"
        "  padding: 8px 20px;"
        "}"
        ".reset-btn:hover {"
        "  color: #e94560;"
        "  border-color: #e94560;"
        "}"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    g_object_unref(provider);
}

static void activate(GtkApplication *app, gpointer user_data) {
    AppData *data = (AppData *)user_data;
    load_css();

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Styled Counter");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 250);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);

    GtkWidget *label = gtk_label_new("0");
    gtk_widget_set_name(label, "counter-label");
    data->label = GTK_LABEL(label);
    gtk_box_append(GTK_BOX(vbox), label);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
    gtk_widget_set_halign(hbox, GTK_ALIGN_CENTER);

    GtkWidget *dec_btn = gtk_button_new_with_label("−");
    GtkWidget *reset_btn = gtk_button_new_with_label("Reset");
    GtkWidget *inc_btn = gtk_button_new_with_label("+");

    gtk_widget_add_css_class(inc_btn, "increment-btn");
    gtk_widget_add_css_class(dec_btn, "decrement-btn");
    gtk_widget_add_css_class(reset_btn, "reset-btn");

    g_signal_connect(inc_btn, "clicked", G_CALLBACK(on_increment), data);
    g_signal_connect(dec_btn, "clicked", G_CALLBACK(on_decrement), data);
    g_signal_connect(reset_btn, "clicked", G_CALLBACK(on_reset), data);

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
        "com.example.csscounter",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), &data);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
