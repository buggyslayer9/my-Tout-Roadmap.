# Assignment 16: The Live Stopwatch

Build a working stopwatch using `g_timeout_add` and `GString`.

## Task

Create an application with:
1. A large label displaying `00:00.0` (Minutes:Seconds.Tenths).
2. Three buttons: **Start**, **Stop**, and **Reset**.
3. A timer that updates the UI exactly every 100 milliseconds.

## Visual Layout

```
┌──────────────────────────────┐
│                              │
│           02:35.7            │
│                              │
│   [Start]   [Stop]  [Reset]  │
│                              │
└──────────────────────────────┘
```

## Requirements

1. **State:** Track the total tenths of a second elapsed in your `AppData` struct. Also track the `timer_id` returned by `g_timeout_add`.
2. **Start Button:** Call `g_timeout_add(100, on_timer_tick, data)`. Ensure you don't start multiple timers if the user mashes "Start"!
3. **Stop Button:** Cancel the timer using `g_source_remove(data->timer_id)` and set `timer_id` to 0.
4. **Reset Button:** Stop the timer and set elapsed time back to 0. Update the label immediately to `00:00.0`.
5. **String Formatting:** Inside `on_timer_tick`, heavily utilize `GString` to build the `02:35.7` string format before passing it to the `GtkLabel`.

## Data Structure Example

```c
typedef struct {
    GtkWidget *time_label;
    guint      timer_id;   // 0 means stopped
    int        ticks;      // Total tenths of a second
    GString   *fmt_str;    // Reuse this string buffer to avoid allocations
} StopwatchData;
```

## Time Math Hints

Since the timer ticks every 100ms (tenths of a second):
```c
int tenths  = data->ticks % 10;
int seconds = (data->ticks / 10) % 60;
int minutes = (data->ticks / 600);
```

## String Formatting Hint

To print leading zeros, use `%02d`.
```c
g_string_printf(data->fmt_str, "%02d:%02d.%d", minutes, seconds, tenths);
gtk_label_set_text(GTK_LABEL(data->time_label), data->fmt_str->str);
```

## Checklist
- [ ] Display correctly shows leading zeros (e.g., `00:05.1`)?
- [ ] Mashing "Start" multiple times doesn't speed up the clock?
- [ ] Stop button properly halts the clock?
- [ ] Reset clears the timer accurately?
