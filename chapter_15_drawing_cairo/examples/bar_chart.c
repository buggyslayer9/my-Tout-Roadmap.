/*
 * Chapter 15 — Drawing with Cairo (Bar Chart)
 * Compile: gcc `pkg-config --cflags gtk4` bar_chart.c `pkg-config --libs gtk4` -o bar_chart
 * Run:     ./bar_chart
 */
#include <gtk/gtk.h>

static int values[] = {30, 70, 50, 90, 40};
static const int NUM_BARS = 5;

// Colors for each bar (R, G, B)
static double colors[][3] = {
    {0.90, 0.30, 0.30},  // Red
    {0.30, 0.69, 0.31},  // Green
    {0.25, 0.47, 0.85},  // Blue
    {1.00, 0.60, 0.00},  // Orange
    {0.61, 0.15, 0.69},  // Purple
};

static void draw_callback(GtkDrawingArea *area, cairo_t *cr,
                           int width, int height, gpointer data) {
    int padding = 50;
    int chart_w = width - 2 * padding;
    int chart_h = height - 2 * padding;
    int bar_w = chart_w / NUM_BARS - 10;

    // Title
    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_move_to(cr, width / 2 - 50, 30);
    cairo_show_text(cr, "Bar Chart");

    // Find max value for scaling
    int max_val = values[0];
    for (int i = 1; i < NUM_BARS; i++) {
        if (values[i] > max_val) max_val = values[i];
    }

    // Draw bars
    cairo_set_font_size(cr, 14);
    for (int i = 0; i < NUM_BARS; i++) {
        double bar_h = ((double)values[i] / max_val) * chart_h;
        double x = padding + i * (bar_w + 10);
        double y = height - padding - bar_h;

        // Bar
        cairo_set_source_rgb(cr, colors[i][0], colors[i][1], colors[i][2]);
        cairo_rectangle(cr, x, y, bar_w, bar_h);
        cairo_fill(cr);

        // Value label on bar
        cairo_set_source_rgb(cr, 1, 1, 1);
        char val_str[16];
        snprintf(val_str, sizeof(val_str), "%d", values[i]);
        cairo_move_to(cr, x + bar_w / 2 - 10, y + 20);
        cairo_show_text(cr, val_str);

        // X-axis label
        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
        char label[16];
        snprintf(label, sizeof(label), "%d", i + 1);
        cairo_move_to(cr, x + bar_w / 2 - 5, height - padding + 20);
        cairo_show_text(cr, label);
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Cairo Bar Chart");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    GtkWidget *area = gtk_drawing_area_new();
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 500);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 400);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw_callback, NULL, NULL);

    gtk_window_set_child(GTK_WINDOW(window), area);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new(
        "com.example.barchart",
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
