# 🖥️ Complete Developer Roadmap — From C to COSMIC

**From Zero to Professional Linux Developer** — A comprehensive 50-chapter curriculum covering C, GTK4, Rust, Linux internals, COSMIC desktop, web development, mobile apps, and DevOps.

> **Author**: Ayman Salem — *Building the skills to create custom Linux distros, COSMIC apps, and full-stack solutions*

---

## 📋 Overview

This course contains **50 chapters** organized in **8 phases**:

| Phase | Chapters | Focus | Language |
|-------|----------|-------|----------|
| **Phase 1** | 1–10 | C Programming Fundamentals | C |
| **Phase 2** | 11–20 | GTK4 GUI Programming | C |
| **Phase 3** | 21–26 | Rust Programming | Rust |
| **Phase 4** | 27–32 | Linux Internals & Custom Distro | C / Bash |
| **Phase 5** | 33–36 | COSMIC Desktop & Wayland | Rust |
| **Phase 6** | 37–42 | Web Development (Full-Stack) | JS / Rust |
| **Phase 7** | 43–46 | Mobile Development (Flutter) | Dart |
| **Phase 8** | 47–50 | DevOps & Open Source | Git / YAML |

Each chapter contains:
- 📖 **Lesson files** — Concepts with code examples and explanations
- 📝 **Assignment** — Hands-on practice exercise
- 💻 **Example source code** — Compilable source files in `examples/`

## 🔧 Prerequisites

| Tool | Purpose | Install (Ubuntu/Debian) |
|------|---------|------------------------|
| GCC | C Compiler | `sudo apt install gcc` |
| GDB | Debugger | `sudo apt install gdb` |
| Valgrind | Memory checker | `sudo apt install valgrind` |
| Make | Build system | `sudo apt install make` |
| GTK4 | GUI toolkit (Phase 2) | `sudo apt install libgtk-4-dev` |
| pkg-config | Library flags | `sudo apt install pkg-config` |
| Rust | Phases 3, 5, 6 | `curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs \| sh` |
| Node.js | Web development (Phase 6) | `sudo apt install nodejs npm` |
| Flutter | Mobile dev (Phase 7) | `sudo snap install flutter --classic` |

### macOS (Homebrew)
```bash
brew install gcc gdb gtk4 pkg-config rust node
```

### Fedora
```bash
sudo dnf install gcc gdb valgrind make gtk4-devel rust cargo nodejs
```

## 🚀 Getting Started

1. Clone this repository
2. Start with `chapter_01_introduction_to_c/`
3. Read each lesson file in order (01, 02, 03...)
4. Complete the assignment before moving to the next chapter
5. Compile examples with:

```bash
# Phase 1 (C only)
gcc -Wall -Wextra -std=c11 example.c -o example

# Phase 2 (GTK4)
gcc `pkg-config --cflags gtk4` example.c `pkg-config --libs gtk4` -o example

# Phase 3+ (Rust)
cargo new my_project && cd my_project && cargo run
```

## 📚 Chapter Index

### Phase 1 — C Programming Fundamentals
| # | Chapter | Key Topics |
|---|---------|------------|
| 1 | Introduction to C | Hello World, compilation pipeline, printf |
| 2 | Variables & Data Types | int, float, char, sizeof, operators |
| 3 | Control Flow | if/else, switch, for/while loops |
| 4 | Functions | Prototypes, recursion, scope, static |
| 5 | Arrays & Strings | Arrays, string.h, safe input with fgets |
| 6 | Pointers & Memory | Addresses, dereferencing, pass by reference |
| 7 | Dynamic Memory | malloc, calloc, realloc, free, Valgrind |
| 8 | Structs, Unions & Enums | typedef, arrow operator, tagged unions |
| 9 | File I/O | Text/binary files, fread/fwrite |
| 10 | Advanced C | Makefiles, Unit Testing, Macros, Debugging |

### Phase 2 — GTK4 GUI Programming
| # | Chapter | Key Topics |
|---|---------|------------|
| 11 | Introduction to GTK4 | GtkApplication, GObject, first window |
| 12 | Widgets & Layouts | GtkBox, GtkGrid, custom widget derivation |
| 13 | Signals & Callbacks | Event-driven model, GUI Concurrency |
| 14 | Dialogs | GtkAlertDialog, GtkFileDialog, custom dialogs |
| 15 | Drawing with Cairo | GtkDrawingArea, shapes, text, colors, animation |
| 16 | GLib Utilities | GList, GHashTable, GString, timeouts |
| 17 | CSS Styling | GTK CSS, classes, widget names, hover effects |
| 18 | Complete GTK4 App | Makefiles, Meson, ListBox, HeaderBar, Notebook |
| 19 | Advanced GTK4 | TextView, GMenu, GSettings, async GTask |
| 20 | Capstone Project | Full Task Manager application |

### Phase 3 — Rust Programming
| # | Chapter | Key Topics |
|---|---------|------------|
| 21 | Introduction to Rust | Installation, Cargo, variables, types, functions |
| 22 | Ownership & Borrowing | Move semantics, references, lifetimes |
| 23 | Structs & Enums | Methods, pattern matching, Option, Result |
| 24 | Error Handling & Collections | Result, ?, Vec, HashMap, iterators |
| 25 | Traits & Generics | Interfaces, generic functions, closures |
| 26 | Concurrency, Macros & FFI | tokio, Unsafe Rust, C-Rust Integration |

### Phase 4 — Linux Internals & Custom Distro
| # | Chapter | Key Topics |
|---|---------|------------|
| 27 | Linux Kernel | Architecture, building from source, kernel modules |
| 28 | System & Container Internals | POSIX APIs, namespaces, cgroups |
| 29 | Systemd & IPC | Init systems, service files, DBus |
| 30 | Package Management | Building .deb packages, repositories |
| 31 | Building a Distro | Linux From Scratch, Buildroot, Yocto |
| 32 | Custom ISO | live-build, archiso, desktop customization |

### Phase 5 — COSMIC Desktop & Wayland
| # | Chapter | Key Topics |
|---|---------|------------|
| 33 | Wayland Protocol | Architecture, surfaces, compositors vs X11 |
| 34 | Iced Framework | Elm architecture, widgets, Sandbox trait |
| 35 | COSMIC Architecture | libcosmic, cosmic-comp, app framework |
| 36 | COSMIC Development | Building applets and full COSMIC applications |

### Phase 6 — Web Development (Full-Stack)
| # | Chapter | Key Topics |
|---|---------|------------|
| 37 | HTML, CSS & TypeScript | Semantic HTML, CSS Grid, strict typing |
| 38 | WebAssembly (Wasm) | Rust in the browser, wasm-bindgen |
| 39 | React Frontend | Components, hooks, state management |
| 40 | Rust Backend (Axum) | REST APIs, JSON, middleware |
| 41 | Databases & Security | SQLx, JWT Auth, password hashing |
| 42 | Full-Stack Capstone | Complete web app with auth, CRUD, deployment |

### Phase 7 — Mobile Development
| # | Chapter | Key Topics |
|---|---------|------------|
| 43 | Flutter & Dart | Setup, Dart syntax, Material widgets |
| 44 | State & Offline-First | Provider, local databases (SQLite/Isar) |
| 45 | Mobile FFI | Running Rust inside Flutter (flutter_rust_bridge) |
| 46 | Mobile Capstone | Full mobile app with API integration |

### Phase 8 — Advanced Skills & DevOps
| # | Chapter | Key Topics |
|---|---------|------------|
| 47 | Git Mastery | Branching, rebasing, bisect, conventional commits |
| 48 | Docker & CI/CD | Containerization, GitHub Actions, deployment |
| 49 | Architecture & Observability | Design patterns, logging, monitoring |
| 50 | Open Source | Contributing to COSMIC, GTK, Linux projects |

## 📖 Recommended Resources

We have compiled a massive, curated list of the best books, free interactive courses, video tutorials, practice platforms, and official documentation for all 8 phases of this curriculum.

👉 **[View the Master Reference Guide (Zero to Hero Resources)](REFERENCES.md)**

## 📄 License

This educational material is provided for personal learning purposes.

---

*Crafted by Ayman Salem — from the ground up, building systems that matter.*
# my-Tout-Roadmap.
