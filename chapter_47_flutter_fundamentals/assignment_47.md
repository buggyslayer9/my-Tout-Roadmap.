# Assignment 47: The Stateful Counter App

In this assignment, you will architect a generic, single-page cross-platform mobile application completely in Dart.

It is a rite of passage to build a Stateful "Counter" that increases mathematically when you press a floating action button on the phone screen.

## 1. Project Initialization
If you have the immense Flutter SDK installed:
1. Run `flutter create counter_app`.
2. `cd counter_app`.
3. Open `lib/main.dart` (This is the only file that matters).

Delete **every single line of code** inside `main.dart`. We will write it from scratch to physically understand the Tree.

## 2. Bootstrapping

1. Import the immense Material Design C++ rendering library:
   `import 'package:flutter/material.dart';`
2. Write the 3-line mandatory `void main()` entry point.
3. Call `runApp(const MyApp());` inside main.

## 3. The Stateless Shell

Create `class MyApp extends StatelessWidget`.
1. It must `override Widget build(BuildContext context)`.
2. It must return a `MaterialApp(home: const HomePage())`.

You have just defined the global theme configuration of the literal application.

## 4. The Stateful Core

Create `class HomePage extends StatefulWidget`.
1. Override `createState()` and point it to new internal memory class:
   `_HomePageState createState() => _HomePageState();`

Now implement the massive Memory Class: `class _HomePageState extends State<HomePage>`.

1. Inside this class, declare `int _counter = 0;`.
2. Write a helper function, not a widget:
```dart
void _increment() {
    setState(() {
        _counter++;
    });
}
```

## 5. Drawing the Visual Layout

Now, override the `Widget build` method inside your active `_HomePageState` class.

You must compose a deeply nested `Scaffold`:
1. The `Scaffold` must have an `appBar` containing a `Text('Counter App')`.
2. The `Scaffold` must have a `body` set to a `Center` widget.
3. The `Center` widget must have a container `Column` widget. Set its `mainAxisAlignment` to center!
4. The `Column` widget must have a List of `children: []`.
5. Inside the children list, pass two simple `Text` widgets:
   - `Text('You clicked the button this many times:')`
   - `Text('$_counter', style: TextStyle(fontSize: 40))` -> **The Dynamic Injection!**

6. Finally, the `Scaffold` has a special property called `floatingActionButton`.
   Pass it a `FloatingActionButton(onPressed: _increment, child: Icon(Icons.add))`.

## 6. Compile to AOT ARM Code

Run this command inside your terminal:
`flutter run -d linux` (or `-d macos` or `-d chrome` if you don't have an emulator running).

Watch the C++ engine paint your specific widgets natively at 120 FPS. Click the button. Watch the state trigger a reactive repaint instantly.
You are now a mobile developer.
