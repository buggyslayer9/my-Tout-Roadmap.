# 47.2 Stateless vs Stateful Widgets

Just like React, Flutter components must respond to user interactions (tapping the screen, fetching data).
To achieve this, Flutter enforces two massively strict Widget paradigms.

## 1. Stateless Widgets
If a Widget is entirely dumb—it simply takes data and displays it on the screen without ever changing itself—it extends the `StatelessWidget` class.

```dart
// It requires an immutable build() method!
class ProfileCard extends StatelessWidget {
  
  // Dart forces this field to be CONSTANT. It can never change inside this class.
  final String username;

  const ProfileCard({required this.username});

  @override
  Widget build(BuildContext context) {
    // If the username field somehow changes, this entire build() method deletes 
    // the old widget and returns a brand new rebuilt branch to the engine.
    return Card(
      child: Text(username),
    );
  }
}
```

## 2. Stateful Widgets
If a Widget needs to remember a piece of data (like a checkbox being `true` or `false`), and clicking it needs to redraw that specific Checkbox instantly, it extends the `StatefulWidget` class.

A `StatefulWidget` is physically split into two separate classes:
1. The incredibly lightweight Widget (The configuration).
2. The heavy `State` object (The persistent memory that lives in RAM long after the widget gets destroyed and rebuilt!).

```dart
// 1. The Configuration Widget
class CheckboxWidget extends StatefulWidget {
  @override
  _CheckboxWidgetState createState() => _CheckboxWidgetState();
}

// 2. The Persistent State Object
class _CheckboxWidgetState extends State<CheckboxWidget> {
  // Our Reactive Memory!
  bool isChecked = false;

  @override
  Widget build(BuildContext context) {
    return Checkbox(
      value: isChecked,
      
      // When the user taps the phone glass with their finger:
      onChanged: (bool? newValue) {
        
        // This is the most famous function in Flutter.
        // It tells the Skia Render Engine to surgically re-run the build() method above!
        setState(() {
          isChecked = newValue ?? false;
        });
        
      },
    );
  }
}
```

This `setState()` architecture is practically identical to calling `setCount(newValue)` in React (Chapter 42). You literally mutate the state mathematically, and the framework forces the GPU to paint the new State onto the physical LCD display.
