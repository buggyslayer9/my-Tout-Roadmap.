# 28.1 The CLI Tool: System Resource Monitor

The best way to solidify Rust is to build real tools. Rust completely dominates the Modern CLI space (tools like `ripgrep`, `bat`, `eza`, `starship` are all written in Rust).

Your first project in this chapter is to build a terminal-based System Resource Monitor (a very simple `top` or `htop` clone).

## Project Requirements
Create a new project: `cargo new sys_monitor`

### Dependencies
Add this to your `Cargo.toml`:
```toml
[dependencies]
sysinfo = "0.29" # Extremely popular crate for reading system stats
crossterm = "0.27" # For manipulating the terminal screen
```

### The Architecture
1. **The State**
   You need a struct that holds the current CPU usage, RAM usage, and a list of the top 5 Memory-consuming processes.

2. **The Update Loop**
   You will have an infinite loop (which can be exited via Ctrl+C). Every 1 second, the loop will:
   - Ask `sysinfo` to refresh the system stats.
   - Clear the terminal screen using `crossterm`.
   - Print the new values formatted beautifully.

### The Display Logic
Use standard `println!` but combine it with `crossterm` macros to clear the screen and move the cursor:

```rust
use crossterm::{execute, terminal::{Clear, ClearType}, cursor::MoveTo};
use std::io::stdout;

fn clear_screen() {
    execute!(stdout(), Clear(ClearType::All), MoveTo(0, 0)).unwrap();
}
```

### The `sysinfo` API
```rust
use sysinfo::{System, SystemExt, ProcessExt};

let mut sys = System::new_all();

// Inside your loop:
sys.refresh_all();
println!("Total memory: {} KB", sys.total_memory());
println!("Used memory : {} KB", sys.used_memory());

// Iterating over processes:
for (pid, process) in sys.processes() {
    println!("[{}] {} ({} KB)", pid, process.name(), process.memory());
}
```

## Professional Tips
- Do not let the program crash if it fails to read a process. Process lifetimes are volatile.
- Use an `impl` block on your State struct to keep your `main()` function clean. `main` should just be initialization and the loop.
