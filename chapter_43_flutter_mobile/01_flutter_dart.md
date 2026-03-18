# 43.1 Flutter & Dart Fundamentals

Flutter is Google's cross-platform toolkit for building Android, iOS, web, desktop, and Linux apps from a single codebase.

## Why Flutter?

| Feature | Flutter | React Native |
|---------|---------|-------------|
| Language | Dart | JavaScript |
| Rendering | Custom engine (Skia/Impeller) | Native widgets |
| Performance | Near-native | Good, bridge overhead |
| Hot reload | ✅ Excellent | ✅ Good |
| Linux desktop | ✅ Yes | ❌ No |
| COSMIC integration | Possible (GTK embedding) | No |

## Setup

```bash
# Install Flutter (snap or manual)
sudo snap install flutter --classic

# Verify
flutter doctor

# Create project
flutter create my_app
cd my_app
flutter run    # Run on connected device or emulator
```

## Dart Basics

```dart
// Variables
var name = 'Ayman';           // Type inference
String greeting = 'Hello';    // Explicit type
final pi = 3.14159;           // Runtime constant
const maxSize = 100;           // Compile-time constant

// Functions
int add(int a, int b) => a + b;  // Arrow syntax

String greet(String name, {String? title}) {
    return title != null ? 'Hello, $title $name!' : 'Hello, $name!';
}

// Classes
class Task {
    final String title;
    bool completed;

    Task(this.title, {this.completed = false});

    void toggle() => completed = !completed;

    @override
    String toString() => '${completed ? "✅" : "⬜"} $title';
}

// Null safety
String? nullableString;  // Can be null
String nonNullable = 'always has value';
print(nullableString?.length ?? 0);  // Safe access with default
```

## First Flutter App

```dart
import 'package:flutter/material.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
    const MyApp({super.key});

    @override
    Widget build(BuildContext context) {
        return MaterialApp(
            title: 'Task Manager',
            theme: ThemeData.dark(useMaterial3: true),
            home: const TaskPage(),
        );
    }
}

class TaskPage extends StatefulWidget {
    const TaskPage({super.key});
    @override
    State<TaskPage> createState() => _TaskPageState();
}

class _TaskPageState extends State<TaskPage> {
    final List<Task> tasks = [];
    final controller = TextEditingController();

    void addTask() {
        if (controller.text.isNotEmpty) {
            setState(() {
                tasks.add(Task(controller.text));
                controller.clear();
            });
        }
    }

    @override
    Widget build(BuildContext context) {
        return Scaffold(
            appBar: AppBar(title: const Text('Task Manager')),
            body: Column(
                children: [
                    Padding(
                        padding: const EdgeInsets.all(16),
                        child: Row(
                            children: [
                                Expanded(
                                    child: TextField(
                                        controller: controller,
                                        decoration: const InputDecoration(
                                            hintText: 'Add a task...',
                                            border: OutlineInputBorder(),
                                        ),
                                        onSubmitted: (_) => addTask(),
                                    ),
                                ),
                                const SizedBox(width: 8),
                                ElevatedButton(
                                    onPressed: addTask,
                                    child: const Text('Add'),
                                ),
                            ],
                        ),
                    ),
                    Expanded(
                        child: ListView.builder(
                            itemCount: tasks.length,
                            itemBuilder: (context, index) {
                                final task = tasks[index];
                                return CheckboxListTile(
                                    title: Text(
                                        task.title,
                                        style: TextStyle(
                                            decoration: task.completed
                                                ? TextDecoration.lineThrough
                                                : null,
                                        ),
                                    ),
                                    value: task.completed,
                                    onChanged: (_) => setState(() => task.toggle()),
                                );
                            },
                        ),
                    ),
                ],
            ),
        );
    }
}

class Task {
    final String title;
    bool completed;
    Task(this.title, {this.completed = false});
    void toggle() => completed = !completed;
}
```

## Assignment 43-44

**Task**: Build a **mobile task manager** with Flutter:
1. Material 3 dark theme
2. Add, toggle, delete tasks
3. Persist data using `shared_preferences` or `sqflite`
4. Tab navigation: All, Pending, Completed
5. Search functionality
6. Swipe-to-delete with undo snackbar

**Sources**:
- [Flutter docs](https://docs.flutter.dev/)
- [Dart language tour](https://dart.dev/language)
- [Flutter cookbook](https://docs.flutter.dev/cookbook)

---

## 📚 Resources for This Chapter

### Official (Start Here)
- [**Flutter Docs**](https://docs.flutter.dev/) — Getting started, widgets catalog, cookbook ⭐
- [**Dart Language Tour**](https://dart.dev/language) — Learn Dart syntax
- [**DartPad**](https://dartpad.dev/) — Run Dart/Flutter in the browser
- [**Flutter Samples**](https://flutter.github.io/samples/) — Official example gallery

### Courses
- [**Angela Yu's Flutter Bootcamp**](https://www.udemy.com/course/flutter-bootcamp-with-dart/) — Made with Google (Udemy) ⭐
- [**Maximilian's Flutter Guide**](https://www.udemy.com/course/learn-flutter-dart-to-build-ios-android-apps/) — Project-based, updated (Udemy)
- [**freeCodeCamp 37h Flutter Course**](https://www.youtube.com/watch?v=VPvVD8t02U8) — Free, comprehensive (YouTube)
- [**The Net Ninja Flutter**](https://www.youtube.com/@NetNinja) — Free playlist series

### Books
- **"Flutter Apprentice"** — Kodeco (beginner to advanced)
- **"Flutter in Action"** — Eric Windmill (intermediate)
- **"Flutter Complete Reference"** — Alberto Miola (reference)

### Key Packages
- [pub.dev](https://pub.dev/) — Dart/Flutter package registry
- `provider` / `riverpod` (state) | `dio` (HTTP) | `sqflite` (local DB) | `go_router` (navigation)

