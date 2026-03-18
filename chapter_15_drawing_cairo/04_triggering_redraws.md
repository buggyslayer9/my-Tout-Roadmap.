# 15.4 Triggering Redraws and Animation

GTK4 only redraws widgets when needed — this is efficient but means you must explicitly request a redraw when your data changes.

## Requesting a Redraw

```c
gtk_widget_queue_draw(GTK_WIDGET(area));
```

This marks the widget as "dirty." GTK will call your `draw_func` on the next frame. It does **not** redraw immediately.

## When to Request a Redraw

| Scenario | Action |
|----------|--------|
| Data changed (new chart values) | `gtk_widget_queue_draw(area)` |
| Window resized | GTK handles this automatically |
| Continuous animation | `g_timeout_add()` + `queue_draw` |
| Mouse interaction | Redraw in your event handler |

## Animation with `g_timeout_add`

To create smooth animation, set up a timer that updates state and queues redraws:

```c
static double angle = 0.0;

// Timer callback — runs every ~16ms (~60 FPS).
static gboolean on_tick(gpointer user_data) {
    GtkWidget *area = GTK_WIDGET(user_data);
    angle += 0.05;
    gtk_widget_queue_draw(area);
    return G_SOURCE_CONTINUE;  // Keep timer running.
}

// The draw function uses the global 'angle' state.
static void draw_callback(GtkDrawingArea *area, cairo_t *cr,
                           int width, int height, gpointer data) {
    (void)area; (void)data;
    
    // Move origin to center, then rotate.
    cairo_translate(cr, width / 2.0, height / 2.0);
    cairo_rotate(cr, angle);
    
    // Draw a spinning rectangle.
    cairo_set_source_rgb(cr, 0.2, 0.6, 1.0);
    cairo_rectangle(cr, -50, -25, 100, 50);
    cairo_fill(cr);
}

// In activate():
g_timeout_add(16, on_tick, area);  // 1000ms / 60fps ≈ 16ms per frame.
```

## ⚠️ Critical Rules

1. **Never call Cairo functions outside the draw callback** — the `cairo_t` context only exists during that function.
2. **Never call `queue_draw` inside the draw callback** — this creates an infinite redraw loop.
3. For high-performance animations, use `GdkFrameClock` (tied to the display's vsync) instead of `g_timeout_add`.
