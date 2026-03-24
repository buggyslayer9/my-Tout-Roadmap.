# Assignment 48: The Flutter Rust Bridge

In this assignment, you will initialize the actual structural architecture of a modern, memory-safe, ultra-performant mobile application.

You will use the `flutter_rust_bridge` (FRB) library to bind a Rust API directly to a Flutter Button.

## 1. Project Scaffolding
The creators of FRB provide an incredibly powerful init script that perfectly sets up the massive CMake/Cargo/Gradle configuration scripts required to compile Rust into an iOS/Android `.so` file.

1. Install the global rust bridge tool on your computer.
   `cargo binstall flutter_rust_bridge_codegen`
2. Initialize a brand new dual-language project!
   `flutter_rust_bridge_cli create rust_flutter_app`
3. Open the folder `rust_flutter_app`.

## 2. The Rust Core

Notice that your folder has two massive subdirectories: `/lib` (The Dart UI) and `/rust` (The Core logic).

Open `/rust/src/api/simple.rs`.
Delete the generic boiler plate.

Write a synchronous Rust function that purposefully requires heavy CPU calculation.
```rust
#[flutter_rust_bridge::frb(sync)] 
pub fn calculate_primes(limit: u32) -> u32 {
    let mut count = 0;
    for num in 2..limit {
        let mut is_prime = true;
        for i in 2..num {
            if num % i == 0 {
                is_prime = false;
                break;
            }
        }
        if is_prime { count += 1; }
    }
    count
}
```

## 3. The Code Generation Magic

Open your terminal.
Run the magical generation command that reads your `u32` variables and generates the C++ FFI Headers and Dart bindings automatically!
```bash
flutter_rust_bridge_codegen generate
```

## 4. The Dart UI

Open `lib/main.dart`. Wait until the Dart analyzer physically locks onto the generated files.

Add your massive FloatingActionButton to the `Scaffold`.

```dart
FloatingActionButton(
  onPressed: () {
    // 1. You click the GUI button!
    // 2. We instantly drop into C-ABI FFI Pointers!
    // 3. We violently execute the un-optimized O(N^2) Rust Prime math!
    // 4. We beam the exact u32 result back up into the Dart memory heap!
    
    // NOTE: Because calculate_primes is marked sync, it freezes the UI thread.
    // In production, FRB defaults to Async Isolates!
    int totalPrimes = calculatePrimes(limit: 50000);
    
    // Use an Alert Dialog or simple print to prove it worked!
    print("Rust calculated $totalPrimes primes instantly via FFI!");
  },
  child: const Icon(Icons.hub),
)
```

Run the application: `flutter run -d linux`.

You have just successfully called raw, compiled, Memory-Safe Systems Language logic from a reactive cross-platform UI.
