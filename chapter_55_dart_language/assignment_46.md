# Assignment 46: Building the Dart Isolate Engine

Your goal is to build a CLI application in pure Dart that computationally calculates prime numbers using a multi-core Isolate Cluster.

## 1. Project Initialization

If you have the Dart SDK installed (shipped automatically with Flutter):
1. `mkdir dart-primes`
2. `cd dart-primes`
3. `dart create -t console .` (This creates a massive folder structure for you. The entry point is inside the `bin/` folder!).

Open `bin/dart_primes.dart`.

## 2. The Heavy Math Function

Create a top-level function `void calculatePrimes(SendPort callerPort)`.

Inside this function:
1. Write a `for` loop that runs from `n = 0` to `n = 50,000`.
2. Determine if `n` is a prime number.
3. Count how many total prime numbers exist below 50,000.
4. When finished, use `callerPort.send(totalPrimes)`.

## 3. The Main Thread

In `void main() async`:

1. Print `"Booting the CPU Cluster..."`
2. Create an incredibly simple `ReceivePort()`.
3. Spawn the Isolate: `await Isolate.spawn(calculatePrimes, myPort.sendPort)`.
4. Right after spawning the isolate, start an infinite `while(true)` loop that uses `await Future.delayed(Duration(milliseconds: 50))` to print a `.`. 

**This tests the fundamental architecture of the Event Loop.**
If your math was running directly on the Main Thread instead of an Isolate, the Main Thread would physically freeze and would mathematically be incapable of printing the `.` loading bar!

Because the heavy math is sequestered on CPU Core #2, CPU Core #1 (The Main UI Thread) is completely free to smoothly process the User Interface loading animation!

## 4. The Message Reception

Listen to the mailbox!
```dart
myPort.listen((message) {
    print("\n[ISOLATE COMPLETE] Found $message Prime Numbers!");
    // Brutally assassinate the Dart VM so your infinite while loop stops
    exit(0); 
});
```

Run your code:
`dart run bin/dart_primes.dart`

Watch the loading dots fly by perfectly flawlessly while the math churns in the background. You have mathematically isolated complex logic. This is why Flutter apps never stutter.
