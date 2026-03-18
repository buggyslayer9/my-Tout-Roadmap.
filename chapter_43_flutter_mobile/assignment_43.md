# Assignment 43

## Task

Build a **mobile task manager** with Flutter:

### Part 1: Setup and Basic UI

1. Install Flutter and create a new project:
   ```bash
   flutter create task_manager
   cd task_manager
   flutter run
   ```

2. Set up Material 3 dark theme:
   ```dart
   MaterialApp(
     theme: ThemeData.dark(useMaterial3: true),
     // ...
   )
   ```

### Part 2: Core Features

Implement the following features:
- **Add task**: TextField + Button to create new tasks
- **Toggle completion**: Tap checkbox to mark complete/incomplete
- **Delete task**: Swipe to delete with undo snackbar
- **Task model**:
   ```dart
   class Task {
     final String id;
     final String title;
     bool completed;
     final DateTime createdAt;
   }
   ```

### Part 3: Tab Navigation

Implement 3 tabs:
1. **All**: Shows all tasks
2. **Pending**: Shows only incomplete tasks
3. **Completed**: Shows only completed tasks

### Part 4: Persistence (Bonus)

Add data persistence using `shared_preferences`:
- Save tasks when modified
- Load tasks on app start

### Part 5: Search (Bonus)

Add a search bar to filter tasks by title.

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **Flutter widgets** - StatelessWidget, StatefulWidget
2. **State management** - setState for local state
3. **ListView.builder** - Efficient list rendering
4. **Material 3** - Theming and components
5. **Navigation** - TabBar and TabBarView
6. **Dart** - Classes, async/await, null safety

---

## Dependencies

Add to `pubspec.yaml`:
```yaml
dependencies:
  flutter:
    sdk: flutter
  shared_preferences: ^2.2.0
  uuid: ^4.2.0
```

---

## Sources

- [Flutter Documentation](https://docs.flutter.dev/)
- [Flutter Cookbook](https://docs.flutter.dev/cookbook)
- [Dart Language Tour](https://dart.dev/language)

---

## Hints

- Use `Dismissible` widget for swipe-to-delete
- Use `ScaffoldMessenger` to show undo snackbar
- Use `DefaultTabController` for tab navigation
- Use `SharedPreferences` to persist task list as JSON

## Example Output

```
┌─────────────────────────────────────────────┐
│  Task Manager                         🔍    │
├─────────────────────────────────────────────┤
│  [All] [Pending] [Completed]               │
├─────────────────────────────────────────────┤
│  ┌─────────────────────────────────────┐   │
│  │ ☐ Buy groceries                     │   │
│  └─────────────────────────────────────┘   │
│  ┌─────────────────────────────────────┐   │
│  │ ☐ Finish assignment                 │   │
│  └─────────────────────────────────────┘   │
│  ┌─────────────────────────────────────┐   │
│  │ ☑ Call mom                          │   │
│  └─────────────────────────────────────┘   │
├─────────────────────────────────────────────┤
│  ┌────────────────────────┐ [Add]         │
│  │ Add a task...         │                │
│  └────────────────────────┘                │
└─────────────────────────────────────────────┘
```
