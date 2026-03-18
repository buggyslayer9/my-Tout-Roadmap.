# 19.3 GSettings — Storing Preferences

If a user resizes your window or toggles "Dark Mode," they expect those settings to be saved when they restart the app.

Writing settings manually to a text file is annoying. GLib provides `GSettings`, which hooks securely into the host OS's native configuration system (like `dconf` on Linux or the Registry on Windows).

## Defining a Schema

You must define your settings in an XML file (the "Schema"). Save this as `com.example.myapp.gschema.xml` inside your project.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<schemalist>
  <!-- Schema ID must map to your application ID -->
  <schema id="com.example.myapp" path="/com/example/myapp/">
    
    <key name="window-width" type="i">
      <default>800</default>
      <summary>Window Width</summary>
      <description>The default width of the main window.</description>
    </key>
    
    <key name="dark-mode" type="b">
      <default>false</default>
      <summary>Enable Dark Mode</summary>
    </key>

  </schema>
</schemalist>
```

> **Note:** To actually test this on your machine, you must compile the schema. Run: `glib-compile-schemas .` in the directory containing the XML file. 

## Reading and Writing Settings in C

```c
#include <gio/gio.h>

void load_preferences() {
    // 1. Instantiate GSettings
    // This connects to the system dconf using your schema ID
    GSettings *settings = g_settings_new("com.example.myapp");
    
    // 2. Read values
    int width = g_settings_get_int(settings, "window-width");
    gboolean is_dark = g_settings_get_boolean(settings, "dark-mode");
    
    g_print("Loaded Width: %d, Dark Mode: %d\n", width, is_dark);
    
    // 3. Write values
    // Changes take effect immediately and are saved to disk automatically
    g_settings_set_int(settings, "window-width", 1024);
    
    // 4. Cleanup
    g_object_unref(settings);
}
```

## Bonus: Binding Settings Directly to UI

The best part of `GSettings` is that you can bind a key *directly* to a GTK widget property. If the user clicks a `GtkSwitch`, it saves the boolean to disk automatically. No callbacks needed!

```c
GtkWidget *switch_btn = gtk_switch_new();

g_settings_bind(
    settings,           // Your GSettings object
    "dark-mode",        // The XML key string
    switch_btn,         // The widget
    "active",           // The property on the widget
    G_SETTINGS_BIND_DEFAULT
);
```
