# 11.1 What is GTK4?

Welcome to Phase 2. Everything you've built — pointers, structs, dynamic memory, function pointers, header files — converges here. GTK4 is where C becomes visual.

**GTK** (GIMP Toolkit) is a free, open-source, cross-platform widget toolkit for building graphical user interfaces. GTK4 (released 2020) is the current stable version. It powers the entire GNOME desktop ecosystem — file managers, text editors, system tools, and major applications like GIMP, Inkscape, and Blender's UI.

## The GTK4 Architecture Stack

Your application doesn't talk directly to the display server. It sits on top of a deep stack of libraries, each handling a different layer:

```
┌─────────────────────────┐
│    Your Application      │  ← Your C code.
├─────────────────────────┤
│         GTK4             │  ← Widgets: buttons, windows, lists, entries.
├─────────────────────────┤
│        GObject           │  ← OOP system for C: inheritance, signals, properties.
├─────────────────────────┤
│         GLib             │  ← Utility library: data structures, main loop, memory.
├─────────────────────────┤
│         GIO              │  ← File I/O, networking, D-Bus, app framework.
├─────────────────────────┤
│    Cairo / Pango         │  ← 2D drawing engine / Text layout & rendering.
├─────────────────────────┤
│    Wayland / X11         │  ← Display server protocol (your OS window system).
└─────────────────────────┘
```

## Why C + GTK, Not Python or JavaScript?

GTK4 itself is written in C. When you write a GTK app in C, you are speaking GTK's native language with zero translation overhead. You get maximum performance, direct access to every API, and a deep understanding of how GUIs actually work at the system level.

Many professional Linux desktop applications (GNOME, Sway, system daemons) are written this way.

## Key Technologies You'll Use

| Library | Purpose |
|---------|---------|
| **GTK4** | Widgets, windows, layout containers |
| **GObject** | Object orientation in C (inheritance, signals, properties) |
| **GLib** | Hash tables, linked lists, strings, main event loop |
| **GIO** | Application framework, file I/O, settings |
| **Cairo** | 2D vector drawing (charts, custom widgets) |
| **Pango** | Rich text layout and font rendering |
| **CSS** | Styling GTK widgets (yes, real CSS!) |
