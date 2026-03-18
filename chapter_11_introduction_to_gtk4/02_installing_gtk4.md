# 11.2 Installing GTK4

Before you can build anything, you need the GTK4 development libraries and the `pkg-config` tool.

## Linux

```bash
# Ubuntu / Debian / Pop!_OS / Linux Mint
sudo apt install libgtk-4-dev build-essential pkg-config

# Fedora / RHEL / CentOS Stream
sudo dnf install gtk4-devel gcc make pkg-config

# Arch Linux / Manjaro / EndeavourOS
sudo pacman -S gtk4 base-devel pkgconf

# openSUSE
sudo zypper install gtk4-devel gcc make pkg-config
```

## macOS

```bash
# Using Homebrew
brew install gtk4 pkg-config
```

## Verify Your Installation

```bash
# This should print something like "4.14.1"
pkg-config --modversion gtk4

# This prints the compiler flags GTK needs
pkg-config --cflags gtk4

# This prints the linker flags GTK needs
pkg-config --libs gtk4
```

If `pkg-config --modversion gtk4` prints a version number, you're ready. If it says "package not found," the development headers aren't installed — make sure you installed the `-dev` or `-devel` package, not just the runtime library.

## What Is `pkg-config`?

`pkg-config` is a helper tool that tells your compiler where GTK4's headers and libraries live on your system. Instead of manually typing `-I/usr/include/gtk-4.0 -I/usr/include/glib-2.0 ...` (which can be 20+ flags), you just write:

```bash
gcc `pkg-config --cflags --libs gtk4` hello.c -o hello
```

The backticks `` ` `` execute the `pkg-config` command and paste its output directly into the `gcc` command line.
