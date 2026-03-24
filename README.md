# Complete Developer Roadmap: From C to COSMIC and Beyond

From zero to a wide, hands-on developer skill set. This repository is a broad 67-chapter curriculum covering C, GTK4, Rust, Linux internals, COSMIC desktop development, web development, Flutter, and DevOps.

> Author: Ayman Salem
>
> Goal: build real systems, desktop apps, web apps, mobile apps, and deployment skills without narrowing the course too early.

## Overview

This course is intentionally wide. It is designed for learners who want strong foundations first, then multiple applied tracks.

Each chapter folder includes:

- lesson files
- an assignment
- example code when relevant
- `00_learning_guide.md` with learning goals, self-checks, and a suggested follow-up project

You can also use [PROJECTS.md](/C:/Users/Buggy/source/repos/my-Tout-Roadmap/PROJECTS.md) to see the major milestone projects that fit after specific chapters.

## How To Study

1. Start at Chapter 1 and move in order.
2. Read the lesson files for the chapter.
3. Open the chapter's `00_learning_guide.md`.
4. Type at least one example by hand.
5. Complete the assignment before moving on.
6. Build the suggested small project when you finish a chapter or milestone.

## Prerequisites

Common tools used across the roadmap:

| Tool | Purpose | Example Install (Ubuntu/Debian) |
|---|---|---|
| GCC | C compiler | `sudo apt install gcc` |
| GDB | Debugger | `sudo apt install gdb` |
| Valgrind | Memory checker | `sudo apt install valgrind` |
| Make | Build system | `sudo apt install make` |
| GTK4 | GUI toolkit | `sudo apt install libgtk-4-dev` |
| pkg-config | Compiler and linker flags | `sudo apt install pkg-config` |
| Rust | Rust compiler and cargo | `curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh` |
| Node.js and npm | Web tooling | `sudo apt install nodejs npm` |
| Flutter | Mobile development | `sudo snap install flutter --classic` |

## Course Structure

### Phase 1: C Foundations

| # | Chapter | Focus |
|---|---|---|
| 1 | Introduction to C | what C is, compilation, first program |
| 2 | Variables, Data Types, and Operators | types, constants, casts, operators |
| 3 | Control Flow | branching and loops |
| 4 | Functions | decomposition, recursion, scope |
| 5 | Arrays and Strings | arrays, C strings, safer input |
| 6 | Pointers and Memory | addresses, dereferencing, references |
| 7 | Dynamic Memory | malloc, realloc, free, common bugs |
| 8 | Structs, Unions, and Enums | data modeling in C |
| 9 | File I/O | text and binary files |
| 10 | Advanced C | headers, macros, debugging, Makefiles |

### Phase 2: GTK4 and Desktop App Development

| # | Chapter | Focus |
|---|---|---|
| 11 | Introduction to GTK4 | first GTK4 app and lifecycle |
| 12 | Widgets and Layouts | common widgets and layout patterns |
| 13 | Signals and Callbacks | event-driven GUI programming |
| 14 | Dialogs and Message Boxes | alerts, file pickers, input flows |
| 15 | Drawing with Cairo | custom drawing and redraws |
| 16 | GLib Data Structures | lists, hash tables, timers, strings |
| 17 | CSS Styling | styling GTK applications |
| 18 | Complete GTK4 App | organize and build a real desktop app |
| 19 | Advanced GTK4 | richer widgets, settings, async work |
| 20 | Capstone Project | a polished desktop application |

### Phase 3: Rust Core

| # | Chapter | Focus |
|---|---|---|
| 21 | Introduction to Rust | toolchain, cargo, syntax basics |
| 22 | Ownership and Borrowing | ownership model, references, lifetimes |
| 23 | Structs and Enums | data modeling in Rust |
| 24 | Error Handling and Collections | Result, Vec, HashMap, iterators |
| 25 | Traits and Generics | reusable Rust design |
| 26 | Concurrency, Async, and FFI | async work, concurrency, interop |

### Phase 4: Systems, Linux, and Platform Engineering

| # | Chapter | Focus |
|---|---|---|
| 27 | Linux Kernel | kernel fundamentals |
| 28 | Rust GUI | Rust desktop ecosystem |
| 29 | Rust Practical Projects | project-based Rust practice |
| 30 | System Programming | POSIX APIs and processes |
| 31 | Linux Kernel Architecture | internals and subsystem thinking |
| 32 | Systemd and Packaging | services, packaging, distribution |
| 33 | System Calls and libc | libc, syscalls, low-level interfaces |
| 34 | Advanced System Programming | fork, exec, pipes, signals |
| 35 | Build Linux Distro | distro-building foundations |
| 36 | Network Programming | sockets, servers, clients |
| 37 | Systemd Service Management | writing and managing services |
| 38 | Wayland and Iced | modern Linux desktop direction |
| 39 | Building a Linux Distro | boot process and root filesystem |
| 40 | COSMIC Desktop | COSMIC foundations |
| 41 | Wayland Compositors | compositor concepts and protocols |
| 42 | COSMIC Ecosystem | libraries, apps, and contribution paths |
| 43 | Systems Capstone | larger systems project |

### Phase 5: Web Development and Solo Builder Stack

| # | Chapter | Focus |
|---|---|---|
| 44 | Web Fundamentals | HTML, CSS, JavaScript mental model |
| 45 | Web Architecture | HTTP, APIs, and security basics |
| 46 | HTML and CSS | semantic layout and responsive design |
| 47 | Modern JavaScript | ES6+, DOM, fetch, modules |
| 48 | TypeScript | types for frontend code |
| 49 | Next.js | full-stack React framework for solo builders |
| 50 | Frontend Frameworks | component patterns and framework thinking |
| 51 | React and Axum | full-stack application flow |
| 52 | Backend with Node.js | REST basics and middleware |
| 53 | Backend with Rust and Axum | Rust backend services |
| 54 | PostgreSQL | practical relational database foundations |
| 55 | Prisma | schema, migrations, and ORM workflow |
| 56 | Authentication and Authorization | sessions, tokens, roles, protected routes |
| 57 | Payments and Billing | checkout, subscriptions, and billing flows |
| 58 | Web Databases | persistence, SQL, caching, and data tradeoffs |

### Phase 6: Mobile Development

| # | Chapter | Focus |
|---|---|---|
| 59 | Flutter Mobile | introduction to Flutter mobile apps |
| 60 | Dart Language | Dart syntax and async basics |
| 61 | Flutter Fundamentals | widgets, layouts, local state |
| 62 | Advanced Flutter | architecture, integration, offline-first thinking |

### Phase 7: Delivery, DevOps, and Final Integration

| # | Chapter | Focus |
|---|---|---|
| 63 | Git, CI/CD, and DevOps | workflow and automation foundations |
| 64 | Docker | containerized local development and deployment |
| 65 | GitHub Actions | CI workflows, artifacts, and automation |
| 66 | DevOps | deployment, monitoring, operational thinking |
| 67 | Grand Capstone | wide final project combining multiple tracks |

## Recommended Milestone Projects

These are especially worth doing after the matching chapters:

- After Chapter 10: simple C library
- After Chapter 18 or 20: simple GUI app
- After Chapter 25: simple Rust library
- After Chapter 29 or 48: simple game
- After Chapter 36, 51, or 53: simple backend
- After Chapter 43: simple compiler or simple GUI library as a stretch systems project
- After Chapter 54: full-stack web app
- After Chapter 56 or 58: mobile app

See the full list in [PROJECTS.md](/C:/Users/Buggy/source/repos/my-Tout-Roadmap/PROJECTS.md).

## References

Additional learning material is stored in [REFERENCES.md](/C:/Users/Buggy/source/repos/my-Tout-Roadmap/REFERENCES.md) and the top-level [references](/C:/Users/Buggy/source/repos/my-Tout-Roadmap/references) folder.

## Notes

- The roadmap is broad by design.
- The numbering is now unique across all chapter folders.
- The roadmap now includes a stronger solo-builder stack with dedicated chapters for Next.js, PostgreSQL, Prisma, Auth, Payments, Docker, and GitHub Actions.
- No chapters were removed.
- The structure is intended to support both depth and experimentation.

## License

This educational material is provided for personal learning purposes.
