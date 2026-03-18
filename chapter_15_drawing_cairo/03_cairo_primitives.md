# 15.3 Cairo Primitives Reference

Cairo operates on a **path + render** model: you build a path (a series of commands), then either fill or stroke it.

## Colors

```c
cairo_set_source_rgb(cr, r, g, b);             // Solid color (0.0 to 1.0 per channel)
cairo_set_source_rgba(cr, r, g, b, alpha);     // With transparency (0.0 = invisible)
```

## Paths (Building Shapes)

```c
cairo_move_to(cr, x, y);                       // Move pen without drawing.
cairo_line_to(cr, x2, y2);                     // Draw a line from current position.
cairo_rectangle(cr, x, y, width, height);      // Rectangle path.
cairo_arc(cr, cx, cy, radius, angle1, angle2); // Arc/circle path.
cairo_close_path(cr);                           // Close current path back to start.
```

## Rendering (Applying the Path)

```c
cairo_fill(cr);              // Fill the current path with color, then clear path.
cairo_stroke(cr);            // Draw the outline of the current path, then clear it.
cairo_fill_preserve(cr);     // Fill BUT keep the path (so you can also stroke it).
cairo_stroke_preserve(cr);   // Stroke BUT keep the path.
cairo_paint(cr);             // Fill the ENTIRE surface with the current color.
```

## Line Properties

```c
cairo_set_line_width(cr, 2.0);               // Line thickness in pixels.
cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);  // Round, butt, or square.
cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND); // Round, miter, or bevel.
```

## Text

```c
cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
cairo_set_font_size(cr, 24.0);
cairo_move_to(cr, x, y);        // Position is the text baseline.
cairo_show_text(cr, "Hello!");
```

## Transformations

```c
cairo_translate(cr, dx, dy);   // Move the origin.
cairo_rotate(cr, radians);     // Rotate around current origin.
cairo_scale(cr, sx, sy);       // Scale the coordinate system.
cairo_save(cr);                // Save current state (push).
cairo_restore(cr);             // Restore saved state (pop).
```
