# 18.1 Application Structure

Until now, we've stuffed everything into `main.c`. That is fine for a 100-line script, but it becomes a nightmare for a real GTK application. 

Professional C projects require strict separation of concerns.

## Recommended Application Structure

```text
my_awesome_app/
├── meson.build        ← Build system configuration (We'll cover Meson soon)
├── src/
│   ├── main.c         ← Entry point. Sets up the application.
│   ├── app_window.c   ← UI creation: widgets, layouts, window setup.
│   ├── app_window.h
│   ├── callbacks.c    ← Signal handlers (button clicks, form submits).
│   ├── callbacks.h
│   ├── data.c         ← Core business logic, file I/O, database access.
│   └── data.h
└── data/
    └── styles.css     ← All GTK CSS styling.
```

## Why This Structure?

1. **Separation of UI and Logic:** The `app_window.c` file should *only* create buttons and boxes. It shouldn't know how to parse a JSON file or save to a database. That belongs in `data.c`.
2. **Signals in One Place:** Keeping `callbacks.c` separate makes it incredibly easy to find where user actions are handled.
3. **Compile Times:** Changing a button's label in `app_window.c` means the compiler only recompiles that one file, not the entire application.

As we progress through this chapter, we will build fragments that fit neatly into this architecture.
