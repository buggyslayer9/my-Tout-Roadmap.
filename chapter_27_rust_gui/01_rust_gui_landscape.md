# 27.1 The Rust GUI Landscape

You've spent the first half of this course mastering GTK4 using C. You've just spent the last 6 chapters mastering Rust's safety, generics, and concurrency models.

Now, we bridge the two worlds. How do you build a Graphical User Interface in Rust?

The Rust GUI ecosystem is currently in a "Cambrian Explosion" phase. There is no single, dominant, built-in standard like SwiftUI for Apple or WPF for Windows. Instead, there are dozens of competing philosophies.

Here are the three major paths a senior developer takes when building a desktop app in Rust today:

## Path 1: Immediate Mode (egui)
Inspired by game engines, an Immediate Mode GUI redraws the entire screen every single frame. There is no "state" stored in the UI itself. 

**Pros:** Incredibly easy to write. Excellent for debug tools, game engines, or highly dynamic data visualization.
**Cons:** Very high CPU/GPU usage compared to traditional apps. Doesn't feel "native" to the OS.

## Path 2: Modern Cross-Platform (Slint & Iced)
These frameworks are built entirely in Rust from the ground up.

**Iced:** Inspired by Elm, it uses an architecture where your data model, update logic, and view are strictly separated. It is heavily used by System76 for the new COSMIC desktop.
**Slint:** Uses a separate, simple markup language (like CSS/HTML combined) to design the UI, and then compiles it directly into Rust/C++ code. It runs on everything from high-end desktops to microcontrollers with 300KB of RAM.

## Path 3: Native Bindings (GTK-rs)
This is where your existing C knowledge pays off massively. 
GNOME and GTK are still written in C. But the Rust community has built **GTK-rs**—a set of fully safe Rust wrappers around the C libraries.

You get the exact same native look, feel, and accessibility of GTK4, but you write it using Rust's safe memory models and closures.

> **Instructor's Advice:** If you are building an app specifically for Linux (GNOME), use GTK-rs. If you are building a system tool or custom Desktop Environment component, use Iced (COSMIC). If you are building for heavy cross-platform (Windows/Mac/Embedded), use Slint.

In the next lessons, we will look at the syntax for Slint, Iced, and finally dive deep into GTK-rs.
