# 46.1 What is Dart?

Before we can build high-performance mobile apps with Flutter (Chapter 47), we must learn its engine: **The Dart Programming Language**.

Dart was invented by Google in 2011. Originally, Google's massive ambition was for Dart to completely replace JavaScript natively inside the Chrome browser. They believed Javascript had fatal architectural flaws.

That war failed. Microsoft won the war with TypeScript, and Javascript maintained its absolute monopoly on the web.

But Dart found its true calling as a **Client-Optimized Language**.

## AOT vs JIT Compilation

Javascript/TypeScript runs locally via a JIT (Just-in-Time) compiler (the V8 Engine). You send the source code to the browser, and the browser compiles it into machine code milliseconds before it runs. JIT is fantastic for hot-reloading development speed, but terrible for startup time, because the processor has to compile code on the fly at runtime.

C and Rust use AOT (Ahead-of-Time) compilation. You wait 5 minutes running `cargo build --release` on your laptop, transmitting pure Machine Code (`.exe` or `ELF`) to the user. AOT guarantees instant app startup and flawless zero-jank 60FPS animation.

**Dart is magical because it does both.**

1. **JIT Mode (Development):** When you run a Dart app in the simulator on your laptop, Dart uses a JIT Virtual Machine. This grants you "Stateful Hot Reload." You can change a pixel's color in code, save the file, and half a second later the Android simulator changes color without rebooting the app!
2. **AOT Mode (Production):** When you execute `flutter build apk`, the Dart compiler fundamentally changes mode. It transforms your entire codebase into hyper-optimized, low-level ARM Machine Code. The resulting binary is indistinguishable from a C application.

If you understand `structs` in C, `classes` in Java, and `types` in TypeScript, Dart will take you identically 5 minutes to learn. It is the most boring, predictable, beautiful structural language on earth.
