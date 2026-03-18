# 15.2 The Draw Callback

Your draw function is where all the magic happens. GTK calls it with a `cairo_t *` context that represents the drawing surface.

```c
static void draw_callback(GtkDrawingArea *area, cairo_t *cr,
                           int width, int height, gpointer data) {
    (void)area; (void)data;
    
    // 1. Draw a red filled rectangle.
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);     // Red
    cairo_rectangle(cr, 50, 50, 200, 100);         // x, y, width, height
    cairo_fill(cr);                                 // Fill with current color.
    
    // 2. Draw a blue outline circle.
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);     // Blue
    cairo_set_line_width(cr, 3.0);                 // 3px border.
    cairo_arc(cr, 300, 150, 60, 0, 2 * G_PI);     // cx, cy, radius, start, end
    cairo_stroke(cr);                               // Draw only the outline.
    
    // 3. Draw text.
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);     // Black
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 18.0);
    cairo_move_to(cr, 50, 30);
    cairo_show_text(cr, "Cairo Drawing Demo");
}
```

## The Parameters

| Parameter | Purpose |
|-----------|---------|
| `area` | The drawing area widget (rarely used inside the callback) |
| `cr` | The Cairo drawing context — your brush |
| `width` | Current width of the drawing area in pixels |
| `height` | Current height — use these for responsive scaling |
| `data` | The `user_data` pointer you passed in `set_draw_func` |
