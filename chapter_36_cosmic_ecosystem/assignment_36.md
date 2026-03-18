# Assignment 36: Hello COSMIC

In this assignment, you will write a skeletal, declarative Rust GUI application using `iced`.

You do not need an actual COSMIC Desktop to run this. Because `iced` renders using modern graphics APIs (WGPU/Vulkan), it will draw its own window flawlessly on GNOME, KDE, macOS, or Windows.

## The Goal
Create a simple Counter application with a "Plus" button, a "Minus" button, and text displaying the current value.
*(This is the equivalent of the classic React.js tutorial, but deeply integrated with System Level Rust).*

## 1. The Setup
Create a new Cargo project:
```bash
cargo new cosmic_counter
cd cosmic_counter
cargo add iced
```

## 2. The Architecture (`main.rs`)
Replace `src/main.rs` with the fundamental `iced` boilerplate.

```rust
use iced::widget::{button, column, text, row};
use iced::{Alignment, Element, Sandbox, Settings};

pub fn main() -> iced::Result {
    // Launch the Window
    Counter::run(Settings::default())
}

// 1. **State:** The central data source of your App
struct Counter {
    value: i32,
}

// 2. **Messages:** The total list of every possible incoming user event
#[derive(Debug, Clone, Copy)]
enum Message {
    IncrementPressed,
    DecrementPressed,
}

// 3. **The Logic:** Tie State to Messages
impl Sandbox for Counter {
    type Message = Message;

    fn new() -> Self {
        Self { value: 0 }
    }

    fn title(&self) -> String {
        String::from("System76 Iced Counter")
    }

    fn update(&mut self, message: Message) {
        // Reducers: strictly mutate state based on explicit messages
        match message {
            Message::IncrementPressed => { self.value += 1; }
            Message::DecrementPressed => { self.value -= 1; }
        }
    }

    // 4. **The View:** Return a Tree of declarative UI widgets
    fn view(&self) -> Element<Message> {
        let increment = button("+").on_press(Message::IncrementPressed);
        let decrement = button("-").on_press(Message::DecrementPressed);

        column![
            increment,
            text(self.value.to_string()).size(50),
            decrement,
        ]
        .padding(20)
        .align_items(Alignment::Center)
        .into()
    }
}
```

## Execution
Run `cargo run`.
You will see a beautiful, hardware-accelerated, cross-platform window appear.

Notice how absolutely impossible it is to get a Segfault.
Notice how you do not manually manipulate `text.set_string("5")`.
You simply mutate `self.value += 1` inside `update()`, and `iced` automatically calls `view()` again, calculates the mathematical diff, and repaints only what changed directly to the GPU buffer.

This is the future of Linux GUI engineering.
