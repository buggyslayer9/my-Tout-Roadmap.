# 35.1 COSMIC Desktop Architecture

COSMIC (Computer Operating System Main Interface Components) is System76's desktop environment built **entirely in Rust** using their fork of Iced (called `libcosmic`).

## COSMIC Stack

```
┌─────────────────────────────────────┐
│  COSMIC Applications               │
│  (cosmic-files, cosmic-edit,        │
│   cosmic-term, cosmic-settings)     │
├─────────────────────────────────────┤
│  libcosmic                          │
│  (Widget library, theming,          │
│   application framework)            │
├─────────────────────────────────────┤
│  iced_sctk (Iced + Smithay Client)  │
│  (Custom Iced backend for Wayland)  │
├─────────────────────────────────────┤
│  cosmic-comp                        │
│  (Wayland compositor using Smithay) │
├─────────────────────────────────────┤
│  Linux Kernel + Mesa/GPU Drivers    │
└─────────────────────────────────────┘
```

## Key COSMIC Repositories

| Repo | Purpose |
|------|---------|
| `cosmic-epoch` | Meta-repo for entire desktop |
| `cosmic-comp` | Wayland compositor |
| `libcosmic` | Widget library & app framework |
| `cosmic-applets` | Panel applets (clock, wifi, etc.) |
| `cosmic-settings` | System settings app |
| `cosmic-files` | File manager |
| `cosmic-edit` | Text editor |
| `cosmic-term` | Terminal emulator |

## Setting Up COSMIC Development

```bash
# 1. Install Pop!_OS or add COSMIC repo
# On Ubuntu/Debian:
sudo apt install just cargo libwayland-dev libxkbcommon-dev \
  libinput-dev libgbm-dev libseat-dev libsystemd-dev

# 2. Clone libcosmic
git clone https://github.com/pop-os/libcosmic.git
cd libcosmic

# 3. Run an example
cargo run --example cosmic-design-demo
```

## Building a COSMIC Application

```rust
use cosmic::app::{Command, Core, Settings};
use cosmic::iced::widget::{column, text};
use cosmic::widget::button;
use cosmic::{Application, Element};

#[derive(Default)]
struct MyApp {
    count: i32,
}

#[derive(Debug, Clone)]
enum Message {
    Increment,
    Decrement,
}

impl Application for MyApp {
    type Executor = cosmic::executor::Default;
    type Flags = ();
    type Message = Message;

    const APP_ID: &'static str = "com.ayman.myapp";

    fn core(&self) -> &Core { /* ... */ }
    fn core_mut(&mut self) -> &mut Core { /* ... */ }

    fn init(core: Core, _flags: ()) -> (Self, Command<Message>) {
        (MyApp { count: 0 }, Command::none())
    }

    fn update(&mut self, message: Message) -> Command<Message> {
        match message {
            Message::Increment => self.count += 1,
            Message::Decrement => self.count -= 1,
        }
        Command::none()
    }

    fn view(&self) -> Element<Message> {
        column()
            .push(text::heading(format!("Count: {}", self.count)))
            .push(button::standard("Increment").on_press(Message::Increment))
            .push(button::standard("Decrement").on_press(Message::Decrement))
            .into()
    }
}

fn main() -> cosmic::iced::Result {
    cosmic::app::run::<MyApp>(Settings::default(), ())
}
```

---

# 36.1 Building COSMIC Applets

COSMIC applets are small panel widgets (clock, battery, network status, etc.):

```rust
// A minimal COSMIC applet structure
use cosmic::app::applet;
// ... (follows the same Application trait pattern)
```

## Assignment 35-36 — COSMIC Capstone

**Task**: Build a **COSMIC system monitor applet**:
1. Clone `cosmic-applets` repo and study existing applets
2. Create a new applet that shows CPU usage percentage
3. Update every 2 seconds using async tasks
4. Display as a progress bar in the panel
5. Click to expand with detailed CPU per-core info

**Sources**:
- [COSMIC GitHub](https://github.com/pop-os/cosmic-epoch)
- [libcosmic docs](https://github.com/pop-os/libcosmic)
- [Iced docs](https://docs.iced.rs/iced/)
- [Pop!_OS Development](https://support.system76.com/)

> **Prerequisite**: You must complete the Rust chapters (21-26) and Iced chapter (34) before this.

---

## 📚 Resources for This Chapter

### Essential
- [**libcosmic API Docs**](https://pop-os.github.io/libcosmic/cosmic/) — Official crate documentation ⭐
- [**COSMIC Epoch Meta-Repo**](https://github.com/pop-os/cosmic-epoch) — Build instructions, all repos
- [**Iced Guide**](https://book.iced.rs/) — Understand the GUI framework COSMIC is built on
- [**Iced Examples**](https://github.com/iced-rs/iced/tree/master/examples) — 30+ working examples

### Study Real COSMIC Code
- [cosmic-applets](https://github.com/pop-os/cosmic-applets) — Panel applets (simplest COSMIC code)
- [cosmic-edit](https://github.com/pop-os/cosmic-edit) — Text editor (medium complexity)
- [cosmic-files](https://github.com/pop-os/cosmic-files) — File manager (complex app)

### Videos & Community
- Search YouTube for **"System76 COSMIC development"** and **"COSMIC desktop alpha"** for latest updates
- [System76 Blog](https://blog.system76.com/) — COSMIC development updates
- [Pop!_OS Mattermost](https://chat.pop-os.org/) — Developer community chat

