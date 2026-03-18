# 15.1 GtkDrawingArea: The Blank Canvas

When the built-in widgets aren't enough — charts, diagrams, custom controls, game rendering — you need a **drawing area**. `GtkDrawingArea` gives you a blank rectangle and a Cairo 2D graphics context to draw anything you want.

## Creating a Drawing Area

```c
GtkWidget *area = gtk_drawing_area_new();

// Set the preferred content size.
gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 400);
gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 300);

// Register your draw function — called whenever the area needs redrawing.
gtk_drawing_area_set_draw_func(
    GTK_DRAWING_AREA(area),
    draw_callback,   // Your drawing function.
    NULL,            // user_data passed to the callback.
    NULL             // Destroy notify (cleanup function for user_data).
);

// Add it to a window.
gtk_window_set_child(GTK_WINDOW(window), area);
```

## How It Works

1. You create a `GtkDrawingArea` and register a **draw function**.
2. GTK calls your draw function whenever the area needs to be painted — on first show, after a resize, or when you explicitly request a redraw.
3. Inside the draw function, you receive a `cairo_t *` context — this is your pen, brush, and canvas all in one.

Cairo is a vector graphics library. You describe shapes (paths) and then either **fill** them (solid color) or **stroke** them (outline). Think of it like PostScript or SVG, but in C.
