# Assignment 35

## Task

Build a **COSMIC-style desktop application** using libcosmic:

### Prerequisites

You must have completed:
- Rust chapters (21-26)
- Iced chapter (33)

### Part 1: Setup libcosmic

1. Install dependencies:
   ```bash
   # On Ubuntu/Debian
   sudo apt install libwayland-dev libxkbcommon-dev libinput-dev \
     libgbm-dev libseat-dev libsystemd-dev just
   ```

2. Clone libcosmic:
   ```bash
   git clone https://github.com/pop-os/libcosmic.git
   cd libcosmic
   cargo run --example cosmic-design-demo
   ```

### Part 2: Build a COSMIC Todo Application

Create a full-featured todo app with libcosmic:

1. Create new project:
   ```bash
   cargo new cosmic_todo
   cd cosmic_todo
   ```

2. Add dependencies:
   ```toml
   [dependencies]
   libcosmic = "0.1"
   ```

3. Implement features:
   - Add new todo items (text input + button)
   - Mark todos as complete/incomplete (checkbox)
   - Delete todos (button)
   - Show count of active/completed todos
   - Use libcosmic theming and styling

### Part 3: Window Management (Bonus)

Add window features:
- Custom title bar (if supported by libcosmic version)
- Minimize, maximize, close buttons
- Window resize handling

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **libcosmic** - System76's Rust widget library
2. **Application trait** - libcosmic's app framework
3. **Widget composition** - Building UI with libcosmic widgets
4. **State management** - Managing todo items
5. **COSMIC design patterns** - Following desktop conventions

---

## Sources

- [libcosmic API Docs](https://pop-os.github.io/libcosmic/cosmic/)
- [COSMIC Epoch](https://github.com/pop-os/cosmic-epoch)
- [COSMIC Applets](https://github.com/pop-os/cosmic-applets)

---

## Hints

- Look at existing libcosmic examples in the repo
- Use `cosmic::widget::` for UI components
- Follow the Elm architecture pattern (State → Message → Update → View)
- Use `cargo doc --open` to generate local documentation
- Check the `examples/` directory in libcosmic for working code

## Expected Output

```
┌─────────────────────────────────────────┐
│  📝 Todo App              ─ □ ✕        │
├─────────────────────────────────────────┤
│                                         │
│  ┌─────────────────────────────────┐   │
│  │ Buy groceries                   │ ☑ │
│  └─────────────────────────────────┘   │
│                                         │
│  ┌─────────────────────────────────┐   │
│  │ Finish assignment               │ ☐ │
│  └─────────────────────────────────┘   │
│                                         │
│  ┌──────────┐                          │
│  │ + Add    │                          │
│  └──────────┘                          │
│                                         │
│  Active: 1 | Completed: 1               │
│                                         │
└─────────────────────────────────────────┘
```
