# 35.2 The Wayland Protocol

To solve the stuttering, tearing, and atrocious security vulnerabilities of X11, the Linux graphics stack was completely redesigned. This redesign is called **Wayland**.

## Wayland is NOT a Server
The biggest misunderstanding in Linux graphics is that "Wayland replaces X.org".

*   **X11** is a *protocol* and `X.org` is a massive C program that *implements* that protocol.
*   **Wayland** is **ONLY A PROTOCOL.** It is just a PDF document describing a set of rules for how C programs should talk to each other. There is no official "Wayland Server" binary.

Instead, the **Compositor** *is* the Display Server.
If you use GNOME desktop, `Mutter` is the Wayland Compositor.
If you use KDE desktop, `KWin` is the Wayland Compositor.

## The Perfect Frame
In Wayland, the application completely bypasses any middle-men.
1. The App allocates a buffer of RAM, and uses Cairo (or Vulkan/OpenGL) to draw pixels directly into that buffer.
2. The App sends a Wayland message to the Compositor saying: "I updated this buffer."
3. The Compositor takes that buffer, applies drop shadows and transparency, and pushes exactly one solid, flawless frame directly to the Kernel DRM (Direct Rendering Manager).

This design mathematically guarantees "Perfect Frames" with absolutely **zero screen tearing**.

## Security by Isolation
In Wayland, the Compositor acts as a strict firewall.
If your Calculator app wants to read your keystrokes, the Compositor denies it. Wayland apps literally do not know if other Wayland apps exist. They cannot read each other's pixels.

If an app wants to capture the screen, it must ask the Compositor for permission. The Compositor will often trigger a GUI popup asking you: *(The App 'OBS Studio' would like to share your screen. Allow?)*.

This level of robust security brings Linux up to par with modern mobile OS sandboxes like iOS and Android.

## XWayland: The Bridge
Because millions of old video games and apps only speak the X11 protocol, Wayland compositors include a secret compatibility layer called **XWayland**. 
It is a fake, invisible X.org server running inside Wayland.

When an old X11 app tries to draw a window, it talks to XWayland. XWayland secretly translates those old X11 commands into Wayland protocol messages and sends them to the compositor. The app believes it is running on a 1980s UNIX terminal, but the user gets the 2024 smooth, tear-free desktop experience.
