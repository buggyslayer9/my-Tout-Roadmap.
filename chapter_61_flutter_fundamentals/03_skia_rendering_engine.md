# 47.3 The Skia / Impeller Rendering Engine

If you build an Android app using standard Java (`Kotlin`) and you drop a `<Button>` onto the screen, the Android OS literally draws an `android.widget.Button` onto the screen.

If you build an iOS app using standard `Swift`, and you drop a `<Button>`, the iOS operating system literally draws a native `UIButton` via the UIKit C-libraries.

Because they are two completely different operating systems, companies must hire "An Android Team" and "An iOS Team" to write two fundamentally different C/Java codebases to produce their app.

## The Cross-Platform War

**React Native** solved this by writing Javascript logic that sent binary messages across a "Bridge." The JS sent "Render a Button" to the OS, and the OS drew the `UIButton` in C. This Bridge was notoriously slow and caused jank.

## The Flutter Paradigm Shift

Flutter realized that operating systems are messy.

When you compile a Flutter app to iOS, Flutter doesn't even whisper to Apple's `UIKit`. It completely ignores standard Apple buttons. It ignores Android buttons.

Instead, Flutter physically embeds a massive, hyper-optimized C++ 2D Graphics Engine directly into the `.APK` / `.IPA` install file!
Historically, this engine was Google's **Skia** (The exact same C++ engine that draws Google Chrome websites!). Currently, Flutter uses an even faster, custom Vulkan/Metal engine called **Impeller**.

When you write: `Text("Hello")`
Flutter tells the C++ Impeller library to specifically calculate the anti-aliased geometry of the fonts and literally manually draw individual colored pixels violently fast onto a blank OpenGL/Metal graphical CANVAS.

Your Flutter app is practically a high-performance Video Game.

### The Massive Benefit
Because Flutter physically draws every pixel using its own embedded C++ engine:
1. An app running on a $50 Android phone from 2015 looks **exactly** identical to an app running on an iPhone 15 Pro Max. 
2. The UI never breaks because Apple accidentally changed how `UIButton` renders in iOS 17.
3. You achieve terrifyingly consistent 120 FPS animations without ever communicating with the slow OS Widget Bridge.
