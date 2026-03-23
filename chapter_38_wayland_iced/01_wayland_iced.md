# 33.1 Wayland Protocol Fundamentals

Wayland is the **modern display protocol** replacing X11 on Linux. COSMIC, GNOME, and KDE all use Wayland.

## X11 vs Wayland

| Feature | X11 | Wayland |
|---------|-----|---------|
| Architecture | Client-Server (X server) | Client-Compositor |
| Security | No isolation between apps | Per-surface isolation |
| Performance | Compositing is optional | Compositing is built-in |
| Screen capture | Any app can capture screen | Requires explicit permission |
| Age | 1987 | 2012 |

## Core Wayland Concepts

| Object | Purpose |
|--------|---------|
| `wl_display` | Connection to the compositor |
| `wl_compositor` | Creates surfaces |
| `wl_surface` | A rectangular area (like a canvas) |
| `xdg_surface` | A window (desktop surface) |
| `wl_buffer` | Pixel data for rendering |
| `wl_seat` | Input devices (keyboard, mouse) |

## How Wayland Works

```
Application → Draw to buffer → Attach buffer to surface → Compositor renders
```

1. App creates a `wl_surface`
2. App draws pixels to a shared memory `wl_buffer`
3. App attaches the buffer to the surface
4. Compositor displays it on screen

## Writing a Minimal Wayland Client (C)

```c
#include <wayland-client.h>
#include <stdio.h>

static void registry_handler(void *data, struct wl_registry *registry,
                             uint32_t id, const char *interface, uint32_t version) {
    printf("Interface: %s (v%d, id=%d)\n", interface, version, id);
}

static const struct wl_registry_listener registry_listener = {
    registry_handler, NULL
};

int main(void) {
    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Cannot connect to Wayland display\n");
        return 1;
    }
    printf("Connected to Wayland!\n");

    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);

    wl_display_disconnect(display);
    return 0;
}
```

```bash
gcc wayland_hello.c -o wayland_hello `pkg-config --cflags --libs wayland-client`
```

**Source**: [The Wayland Book](https://wayland-book.com/)

---

# 34.1 Iced GUI Framework (Rust)

COSMIC uses **Iced** as its GUI framework. Iced is a cross-platform, Elm-inspired GUI library for Rust.

## Iced Architecture (The Elm Architecture)

```
State → View → Message → Update → New State → ...
```

1. **State**: Your application data
2. **View**: Renders UI from state (pure function)
3. **Message**: Events from user interaction
4. **Update**: Modifies state based on messages

## First Iced Application

```toml
# Cargo.toml
[dependencies]
iced = "0.12"
```

```rust
use iced::widget::{button, column, text};
use iced::{Element, Sandbox, Settings};

struct Counter {
    count: i32,
}

#[derive(Debug, Clone)]
enum Message {
    Increment,
    Decrement,
    Reset,
}

impl Sandbox for Counter {
    type Message = Message;

    fn new() -> Self {
        Counter { count: 0 }
    }

    fn title(&self) -> String {
        String::from("Iced Counter")
    }

    fn update(&mut self, message: Message) {
        match message {
            Message::Increment => self.count += 1,
            Message::Decrement => self.count -= 1,
            Message::Reset => self.count = 0,
        }
    }

    fn view(&self) -> Element<Message> {
        column![
            button("-").on_press(Message::Decrement),
            text(self.count).size(50),
            button("+").on_press(Message::Increment),
            button("Reset").on_press(Message::Reset),
        ]
        .padding(20)
        .spacing(10)
        .into()
    }
}

fn main() -> iced::Result {
    Counter::run(Settings::default())
}
```

## Assignment 33-34

**Task**: Build a **temperature converter** using Iced:
1. Input field for Celsius
2. Live-updating display of Fahrenheit, Kelvin
3. Radio buttons to select conversion direction
4. Clean styling with padding and spacing

**Sources**:
- [Iced Guide](https://book.iced.rs/)
- [Iced Examples](https://github.com/iced-rs/iced/tree/master/examples)
- [Wayland Book](https://wayland-book.com/)

---

## 📚 Resources for This Chapter

### Must-Read
- [**The Wayland Book**](https://wayland-book.com/) — Comprehensive protocol guide ⭐
- [**Wayland Explorer**](https://wayland.app/protocols/) — Browse all Wayland protocols interactively
- [**Iced Official Guide**](https://book.iced.rs/) — Elm Architecture in Rust

### Wayland Development Libraries
| Library | Language | Link |
|---------|----------|------|
| **Smithay** | Rust | [github.com/Smithay/smithay](https://github.com/Smithay/smithay) |
| **wayland-rs** | Rust | [github.com/Smithay/wayland-rs](https://github.com/Smithay/wayland-rs) |
| **wlroots** | C | [gitlab.freedesktop.org/wlroots](https://gitlab.freedesktop.org/wlroots/wlroots) |
| **Louvre** | C++ | [github.com/CuarzoSoftware/Louvre](https://github.com/CuarzoSoftware/Louvre) |

### Videos
- Search **"How to Make a Wayland Compositor"** — Way Cooler book (Rust)
- Search **"Smithay Wayland compositor"** — Rust.Tokyo 2024 talk

