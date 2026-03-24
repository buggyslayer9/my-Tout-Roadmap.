# 46.2 Dart Syntax and Null Safety

Dart forces you to type code exactly like a classical OOP computer science textbook (Java/C# style). 
Every Dart application physically begins at `void main()`.

## 1. Variables and Flow Control

Like TypeScript, Dart can infer types if you use `var`. Alternatively, use strong types or `final` for immutability!

```dart
void main() {
    // Strongly typed
    String username = "BugSlayer";
    int age = 99;
    
    // Inferred type (Just like Typescript 'let')
    var isHacking = true;
    
    // Immutable! This can NEVER change again. (Just like Rust let!)
    final double serverUptime = 99.99;
    
    // A standard list (array)
    List<String> systems = ["Linux", "FreeBSD", "RedHat"];
    
    for (var os in systems) {
        print("I love $os"); // String interpolation uses $ !
    }
}
```

## 2. Classes and OOP

Everything in Dart is an Object. You define Classes and Instantiate them.

```dart
class User {
    // Class fields
    int id;
    String name;
    
    // The Constructor
    User(this.id, this.name);
    
    void printProfile() {
        print("User #$id is named $name");
    }
}

void main() {
    // Instantiation (Note: Use of 'new' is deprecated in modern Dart!)
    var u = User(1, "Linus");
    u.printProfile();
}
```

## 3. The Billion Dollar Mistake (Sound Null Safety)

Historically, in Java/C/Javascript, any variable could randomly equal `null`. If you tried to print `user.name`, and the `user` was `null`, the entire application suffered a fatal NullPointer exception and crashed.

Modern Dart fixes this permanently via **Sound Null Safety**.
By default, Dart structurally forces variables to NEVER equal Null. 

```dart
// The compiler guarantees this variable HAS a value.
int score = 0; 
score = null; // FATAL COMPILE ERROR! The app refuses to build.

// If you TRULY need a null variable, you implicitly add a Question Mark '?'
String? maybeAName;
maybeAName = null; // Totally permitted. 

// BUT, if you try to use it...
print(maybeAName.length); 
// FATAL COMPILE ERROR! The compiler screams, forcing you to write an `if (maybeAName != null)` check FIRST.
```

This absolute guarantee completely eliminates the most common cause of mobile app crashes in existence.
