# Assignment 15: The Bar Chart

Draw a dynamic bar chart using Cairo. This exercise combines everything — drawing areas, colors, scaling math, and text rendering.

## Task

Create a GTK4 application that draws a bar chart with 5 hardcoded values.

## Requirements

1. Create a `GtkDrawingArea` (at least 500×400 pixels).
2. Draw 5 bars with the values `{30, 70, 50, 90, 40}`.
3. Each bar should be a **different color**.
4. Scale bars so the tallest bar fits the canvas (with padding for the title and labels).
5. Draw the title **"Bar Chart"** at the top using Cairo text.
6. Draw **x-axis labels** (1–5) below each bar.

## Visual Layout

```
┌─────────────────────────────────────────┐
│              Bar Chart                  │
│                                         │
│              ████                       │
│         ████ ████                       │
│         ████ ████ ████                  │
│   ████  ████ ████ ████ ████            │
│   ████  ████ ████ ████ ████            │
│  ─────────────────────────              │
│    1      2    3    4    5              │
└─────────────────────────────────────────┘
```

## Implementation Hints

```c
// Bar data
int values[5] = {30, 70, 50, 90, 40};
double colors[5][3] = {
    {0.90, 0.30, 0.30},  // Coral
    {0.30, 0.75, 0.45},  // Green
    {0.25, 0.50, 0.85},  // Blue
    {0.95, 0.70, 0.20},  // Amber
    {0.65, 0.35, 0.80}   // Purple
};

// Scaling
int max_val = 90;  // Find the maximum value.
double bar_width = (width - 2 * padding) / 5.0;
double bar_height = ((double)values[i] / max_val) * (height - top_padding - bottom_padding);
```

## Bonus Challenges

1. Find the maximum value dynamically instead of hardcoding `90`.
2. Add horizontal grid lines at 25%, 50%, 75%, and 100%.
3. Display the numeric value above each bar.

## Checklist
- [ ] All 5 bars are visible with distinct colors?
- [ ] Bars are proportionally scaled (tallest bar fills the height)?
- [ ] Title text is drawn at the top?
- [ ] X-axis labels appear below the bars?
