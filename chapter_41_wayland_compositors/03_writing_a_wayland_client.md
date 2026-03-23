# 35.3 Writing a Wayland Client (libwayland-client)

When you write a GTK4 app in C or Rust, GTK automatically detects whether you are using an X11 or Wayland session, and uses the correct underlying connection library. You never have to think about it.

However, as a Systems Programmer, you should vaguely understand how Wayland works beneath the shiny UI toolkits.

## The Unix Domain Socket
Wayland is fundamentally an Inter-Process Communication (IPC) protocol. 

The Wayland Compositor normally listens on a special file in the `/run/user/1000/` directory, usually named `wayland-0`. This file is a **Unix Domain Socket** (like a TCP socket, but restricted purely to localhost RAM).

When a C program wants to draw a window, it connects to that socket and starts sending raw binary messages following the Wayland Specification.

## The Architecture of a Client

Writing a raw Wayland client using `libwayland-client.so` takes roughly 400 lines of C code just to show a blank black square. We will look at the overarching architecture instead of the raw boilerplate.

1. **Connect to the Display:** The app calls `wl_display_connect(NULL)`. This finds the Unix socket and connects.
2. **Access the Registry:** The Wayland Compositor advertises a Registry of services it supports (e.g., "I support Compositing", "I support multiple Monitors", "I support sending mouse events"). The client binds to the ones it needs.
3. **Create a Surface:** The client asks the Compositor to track a blank "Surface" (the geometric abstract shape of a window).
4. **Create a Shared Memory Buffer (shm):** The client creates a chunk of RAM using POSIX Shared Memory (see Chapter 31.3), large enough to hold the pixels.
5. **Draw:** The client loops over every pixel in its shared memory buffer and writes colors into it (e.g., drawing a blue rectangle).
6. **Attach and Commit:** The client tells the Compositor: "I have attached my raw memory buffer to my abstract Surface. Please display it on the physical screen."
7. **The Event Loop:** Finally, the client enters an infinite loop waiting for `libwayland` to send it *Events* (like "The user clicked mouse X,Y").

Because Wayland expects you to handle Shared Memory, double-buffering, and raw pixel drawing yourself, almost no developer writes raw Wayland clients. You **must** rely on GTK, Qt, Slint, or Iced, which abstract these 400 lines of boilerplate away into simply `ApplicationWindow::new()`.
