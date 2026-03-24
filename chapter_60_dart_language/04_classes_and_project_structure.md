# 55.4 Classes and Project Structure in Dart

As Dart programs grow, structure starts to matter more.

This lesson focuses on two practical ideas:

- using classes clearly
- organizing files so the project stays understandable

## Why Classes Matter

Classes help group:

- data
- related behavior
- clear responsibilities

For example, a `Task` class can represent one task instead of passing loose maps and variables everywhere.

## A Small Example

```dart
class Task {
  final String title;
  bool isDone;

  Task(this.title, {this.isDone = false});

  void markDone() {
    isDone = true;
  }
}
```

This is easier to reason about than scattered task-related variables in many places.

## Project Structure

Even small projects benefit from organization.

Example:

```text
lib/
├── main.dart
├── models/
│   └── task.dart
├── services/
│   └── storage_service.dart
└── ui/
    └── task_view.dart
```

This keeps responsibilities clearer.

## Why Structure Helps

Good structure makes it easier to:

- find code
- extend code
- test code
- avoid mixing unrelated concerns

This becomes very important once you move deeper into Flutter.

## Learning Check

- Can I create a simple Dart class with fields and a method?
- Can I explain why classes can improve code clarity?
- Can I separate models, services, and UI into different files?

## Recommended Follow-Up

Take a small Dart exercise and refactor it to use:

- at least one class
- at least two files

That is a strong preparation step for bigger Flutter apps.
