# 29.4 D-Bus (Desktop Bus IPC)

Linux servers use sockets and pipes for simple IPC. However, Linux **Desktops** (like COSMIC, GNOME, and KDE) are heavily complex, event-driven environments. They require a much higher-level message bus protocol. This is **D-Bus**.

## Why D-Bus?

Imagine you write a GTK music player. 
1. How does the media key on your keyboard pause the music?
2. How does the battery applet know the laptop is at 10%?
3. How does your app tell the notification daemon to show a popup?

These programs don't know about each other's memory or PIDs. They use D-Bus to broadcast signals and call methods on remote objects.

## The Two Buses
Every Linux desktop runs two distinct buses:
1. **System Bus:** Used for hardware/system events (Network status, USB plug, Power level). Requires root privileges to bind to.
2. **Session Bus:** Used for the current logged-in user (Media keys, notifications, clipboard).

## D-Bus Architecture
D-Bus acts exactly like an Object-Oriented API mapped over a network.

- **Bus Name:** The application's address (e.g., `org.freedesktop.Notifications`)
- **Object Path:** The specific object handling the request (e.g., `/org/freedesktop/Notifications`)
- **Interface:** The collection of methods and signals (e.g., `org.freedesktop.Notifications`)
- **Method:** The function to call (e.g., `Notify`)

## Calling D-Bus from the CLI
You can explore the live D-Bus using command line tools like `busctl` or `dbus-send`.

Let's trigger a desktop notification using pure DBus:
```bash
dbus-send --session --dest=org.freedesktop.Notifications \
    --type=method_call \
    /org/freedesktop/Notifications \
    org.freedesktop.Notifications.Notify \
    string:"MyApp" uint32:0 string:"" \
    string:"Hello" string:"This was sent via DBus!" \
    array:string:"" dict:string:variant:"" int32:5000
```

## Writing D-Bus Clients in Rust (`zbus`)

In C, D-Bus is historically handled via `GDBus` (part of GLib). However, in modern Linux development (like COSMIC), the Rust `zbus` crate is the industry standard.

`zbus` makes defining a D-Bus service as easy as writing a Rust struct.

### 1. Connecting and calling a method

```rust
use zbus::{Connection, Result, proxy};

// Generate a proxy struct from the interface name
#[proxy(
    interface = "org.freedesktop.Notifications",
    default_service = "org.freedesktop.Notifications",
    default_path = "/org/freedesktop/Notifications"
)]
trait Notifications {
    // Define the DBus method signature we want to call
    fn notify(
        &self,
        app_name: &str,
        replaces_id: u32,
        app_icon: &str,
        summary: &str,
        body: &str,
        actions: &[&str],
        hints: &std::collections::HashMap<&str, zbus::zvariant::Value<'_>>,
        expire_timeout: i32,
    ) -> Result<u32>;
}

#[tokio::main]
async fn main() -> Result<()> {
    // Connect to the session bus
    let connection = Connection::session().await?;

    // Create a proxy to interact with
    let proxy = NotificationsProxy::new(&connection).await?;

    // Call the method remotely!
    let id = proxy
        .notify(
            "MyRustApp",
            0,
            "dialog-information",
            "Hero Detected",
            "You just used D-Bus from Rust!",
            &[],
            &std::collections::HashMap::new(),
            5000,
        )
        .await?;

    println!("Sent notification with ID: {}", id);
    Ok(())
}
```

Whenever you write a COSMIC Applet that needs to read hardware state (Brightness, Volume, Battery), you will implement a `zbus` proxy to talk to the underlying system daemon!
