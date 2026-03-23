# 27.2 Slint and Iced: The Pure Rust Frameworks

Let's briefly examine the two leading "Pure Rust" frameworks to understand how modern retained-mode GUIs are architected without C inheritance.

## Slint: The Declarative Approach

Slint separates the UI design from the business logic. You write the UI in a `.slint` file (which looks a bit like CSS mixed with QML), and write the logic in Rust.

**`ui/main.slint`**
```text
export component MainWindow inherits Window {
    width: 300px;
    height: 200px;
    
    // Define a callback that Rust can hook into
    callback button-clicked();

    VerticalBox {
        Text {
            text: "Welcome to Slint!";
            font-size: 24px;
            horizontal-alignment: center;
        }
        Button {
            text: "Click Me";
            clicked => { root.button-clicked(); }
        }
    }
}
```

**`src/main.rs`**
```rust
slint::include_modules!(); // Compiles the .slint file into Rust at compile time!

fn main() {
    let ui = MainWindow::new().unwrap();

    // Attach the Rust closure to the Slint callback
    ui.on_button_clicked(|| {
        println!("Button was clicked from the Slint UI!");
    });

    ui.run().unwrap();
}
```
**Why this is great:** Designers can mock up the UI in Slint independently, and developers just hook up the logic.

---

## Iced: The Elm Architecture

Iced (used by System76's COSMIC) uses a highly structured pattern. You don't just "mutate" variables in click handlers. Instead, the UI triggers **Messages**, the `update` function modifies the state based on the Message, and the `view` function redraws based on the new state.

```rust
use iced::widget::{button, column, text};
use iced::{Element, Sandbox, Settings};

// 1. The State
struct Counter {
    value: i32,
}

// 2. The Messages (Events)
#[derive(Debug, Clone, Copy)]
enum Message {
    IncrementPressed,
    DecrementPressed,
}

// 3. The Implementation
impl Sandbox for Counter {
    type Message = Message;

    fn new() -> Self {
        Self { value: 0 }
    }

    fn title(&self) -> String {
        String::from("A simple Iced Counter")
    }

    // This handles state changes. Notice it takes a mutable reference to self.
    fn update(&mut self, message: Message) {
        match message {
            Message::IncrementPressed => self.value += 1,
            Message::DecrementPressed => self.value -= 1,
        }
    }

    // This defines the UI. It takes an IMMUTABLE reference to self.
    // It returns an Element tree.
    fn view(&self) -> Element<Message> {
        column![
            button("Increment").on_press(Message::IncrementPressed),
            text(self.value.to_string()).size(50),
            button("Decrement").on_press(Message::DecrementPressed),
        ].into()
    }
}

fn main() {
    Counter::run(Settings::default()).unwrap();
}
```

**Why this is great:** It strictly enforces a one-way data flow. Race conditions in the UI are literally impossible.
