# 23.2 Enums and Pattern Matching

Forget whatever you know about C `enum`s. In C, an enum is just a glorified list of integers.

In Rust, Enums are **Algebraic Data Types**. This means an Enum is a type that can be *one of several variants*, and crucially, **each variant can hold entirely different types of data**.

## Enums that hold data

Imagine a network message. It could be an empty Ping, a connection request containing an IP address, or a chat message containing a string. In C, you'd need a messy `union` combined with an `enum` tag. In Rust:

```rust
// #[derive(Debug)] allows us to print the enum using `{:?}` in println!
#[derive(Debug)] 
enum Message {
    Quit,                       // No data
    Move { x: i32, y: i32 },    // Named fields (like an anonymous struct)
    Write(String),              // Contains a single String
    ChangeColor(u8, u8, u8),    // Contains three u8 values (a tuple)
}

fn main() {
    let msg1 = Message::Quit;
    let msg2 = Message::Write(String::from("Server shutting down"));
    let msg3 = Message::ChangeColor(255, 0, 0);
}
```

Just like structs, **Enums can have `impl` blocks!**

```rust
impl Message {
    fn call(&self) {
        // How do we process this? With `match`!
        println!("Processing a message...");
    }
}
```

## The true power of `match`

Because variants contain different data, you *must* use `match` to extract it safely. Rust forces you to handle every possible variant of the enum, guaranteeing you never accidentally process a `Write` as a `ChangeColor`.

```rust
fn process_message(msg: &Message) {
    match msg {
        // If it's Quit, there's no data to extract
        Message::Quit => {
            println!("Quitting...");
        }
        
        // Extract x and y, but rename y to y_coord
        Message::Move { x, y: y_coord } => {
            println!("Moving to x: {}, y: {}", x, y_coord);
        }
        
        // Extract the String payload
        Message::Write(text) => {
            println!("Message: {}", text);
        }
        
        // Extract the RGB tuple payloads
        Message::ChangeColor(r, g, b) => {
            println!("Color: R{}, G{}, B{}", r, g, b);
        }
    }
}
```

This feature alone makes writing parsers, network stacks, and state machines dramatically easier and safer than in C.
