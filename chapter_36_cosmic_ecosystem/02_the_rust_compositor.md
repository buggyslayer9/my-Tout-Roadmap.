# 36.2 `smithay`: The Rust Compositor Toolkit

In Chapter 35, we learned that Wayland is just a protocol, and the **Compositor** acts as the Display Server.

If System76 wanted to build a Desktop Environment in Rust, they had to build a Wayland Compositor from scratch. Writing a Wayland compositor requires interacting with complex Kernel APIs like **DRM** (Direct Rendering Manager) to push pixels, **KMS** (Kernel Mode Setting) to change monitor resolutions, and **evdev** to read raw keyboard bytes.

## Enter `smithay`

The Linux open-source community maintains a massive, brilliant Rust crate called `smithay` (named after the process of forging metal, echoing "Wayland" the mythological blacksmith).

`smithay` is not a compositor. You cannot "run" `smithay`.
It is a **toolkit** for *building* compositors.

It handles all the terrifying boilerplate of talking to the Linux Kernel: it manages the DRM lifecycles, parses the thousands of complex Wayland binary messages arriving from client apps, and provides safe, high-level Rust abstractions.

## The COSMIC Compositor (`cosmic-comp`)

System76 used `smithay` to build their actual Display Server: `cosmic-comp`.

Consider the power of this architecture:
Because `cosmic-comp` is built in Rust using `smithay`, the entire display pipeline—from when an app says "Draw this pixel" to when the Compositor talks to the Kernel KMS driver to flip the screen buffer—is heavily protected by the Rust Borrow Checker.

**No Use-After-Free vulnerabilities.**
**No Data Races between the mouse-cursor thread and the rendering thread.**

This guarantees a stable runtime.

## Custom Wayland Protocols
Because `cosmic-comp` is highly modular, System76 invented several custom Wayland protocols specifically for their desktop ecosystem (under the namespace `zcosmic_*`).

For instance, they designed a custom protocol to allow individual Applets (like the Volume slider) to request a temporary un-sandboxed window from the Compositor, allowing beautiful, floating UI elements that integrate seamlessly into the desktop without compromising the strict Wayland security sandbox for typical apps.
