# 11.4 Anatomy of a GTK4 Program

Every GTK4 program — from a simple calculator to a full IDE — follows the same four-step skeleton:

## Step 1: Create the Application

```c
GtkApplication *app = gtk_application_new("com.example.myapp", G_APPLICATION_DEFAULT_FLAGS);
```
The application ID is in **reverse-DNS format** (like a Java package name). It must be globally unique because the desktop uses it to identify your app for D-Bus communication, `.desktop` files, and single-instance enforcement.

## Step 2: Connect the `activate` Signal

```c
g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
```
The `"activate"` signal fires when the application is launched and ready to display its UI. Your callback function is where you build your windows and widgets.

## Step 3: Build the UI in `activate()`

```c
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "My App");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    // Add widgets here...
    
    gtk_window_present(GTK_WINDOW(window));
}
```

## Step 4: Run the Event Loop

```c
int status = g_application_run(G_APPLICATION(app), argc, argv);
g_object_unref(app);
return status;
```
`g_application_run()` hands control over to GTK's **main loop** — an infinite loop that listens for events (mouse clicks, key presses, window resize) and dispatches them to the correct handler. It only returns when the user closes the last window.

## The Key Insight

GTK programming is **event-driven**, not procedural. You don't write `while(1) { check_input(); }`. Instead, you register callback functions and let GTK's event loop call them for you. This is the same model used by every major GUI toolkit, game engine, and web browser.
