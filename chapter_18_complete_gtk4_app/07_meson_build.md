# 18.7 The Meson Build System

Makefiles are great for small scripts, but if you look at the source code for GTK, GLib, GNOME System Monitor, or any modern Linux desktop app, you won't find a `Makefile`. You will find a `meson.build` file.

**Meson** is the modern standard build system for Linux desktop development. It is incredibly fast (it generates Ninja build files underneath) and natively understands `pkg-config`, GNOME resources, and robust cross-compilation.

## Basic Meson Setup

Create a file named `meson.build` in your project root:

```meson
# 1. Project definition
project('my-gnome-app', 'c',
  version: '1.0.0',
  default_options: [
    'c_std=c11',         # Use C11 standard
    'warning_level=3',   # -Wall -Wextra equivalent
  ]
)

# 2. Find dependencies automatically! (No more pkg-config backticks)
gtk4_dep = dependency('gtk4')

# 3. Define your source files array
sources = files(
  'src/main.c',
  'src/app_window.c',
  'src/callbacks.c',
  'src/data.c',
)

# 4. Define the final executable
executable('my-gnome-app',
  sources,
  dependencies: gtk4_dep,  # Tell Meson to link GTK4
  install: true,           # Allows `meson install`
)
```

## Compiling with Meson

Meson separates the source code from the compiled binaries (out-of-tree builds). This keeps your workspace clean.

```bash
# First time only: configure the build directory
meson setup builddir

# Actually compile the code (runs Ninja under the hood)
meson compile -C builddir

# Run your compiled app!
./builddir/my-gnome-app
```

## Adding Resources (GResource)

This is where Meson shines for GTK developers. Remember in Chapter 17 when we said you should embed `.css` files directly into your binary? Meson has a built-in GNOME module to handle this instantly:

```meson
# Inside meson.build

# Import the GNOME module
gnome = import('gnome')

# Compile the XML resource file into C code automatically
resources = gnome.compile_resources(
  'app-resources',                  # Name of the generated file
  'data/my-app.gresource.xml',      # The XML manifest
  source_dir: 'data',               # Where the actual .css/.ui files live
)

# Add 'resources' to your executable sources!
executable('my-gnome-app',
  sources + resources,   # <--- The magic happens here!
  dependencies: gtk4_dep,
)
```

## Meson vs CMake

You will inevitably encounter CMake in the wild.

| Feature | Meson | CMake |
|---------|-------|-------|
| Syntax | Python-like, very readable | Arcane, chaotic |
| Speed | Blazing fast | Fast |
| GNOME Support | First-class, built-in | Painful, manual |
| Popularity | Linux Desktop standard | General C/C++ industry standard |

> **Instructor Tip:** If you want to build Linux GUI apps or contribute to the Linux ecosystem, **learn Meson**. It will save you weeks of frustrating build-system debugging.
