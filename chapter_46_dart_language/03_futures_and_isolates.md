# 46.3 Futures and Isolates

Mobile phones do not have unlimited CPU cores like an AWS Postgres server. If an app performs heavy math (like applying an Instagram photo filter), the entire screen freezes.

To solve this, Dart perfectly adopted the Javascript Async/Await model for network latency, but fundamentally reinvented the multithreading model using **Isolates**.

## 1. Futures (`async/await`)

Like Javascript, Dart runs an Event Loop on its Main UI Thread.
If you fetch a URL over the network, you use a `Future` (The Dart word for `Promise`).

```dart
// We import the built-in HTTP library!
import 'package:http/http.dart' as http;
import 'dart:convert'; // For JSON

Future<void> fetchUser() async {
    // The main thread PAUSES HERE, allowing 60FPS animations to keep playing flawlessly!
    var response = await http.get(Uri.parse('https://jsonplaceholder.typicode.com/users/1'));
    
    if (response.statusCode == 200) {
        // Decode the JSON string into a Dart Map!
        var data = jsonDecode(response.body);
        print("Got User: ${data['name']}");
    }
}
```

## 2. Isolates (Fearless Concurrency)

If you use `async/await`, the Dart engine yields control. But what if you need to calculate 2 billion digits of Pi? There is no network wait. The CPU must literally execute math. `async` will not save you here; the Main Thread will be starved, and the screen will freeze entirely for five minutes.

In C or Rust, you would spawn an OS Thread (Chapter 26). But OS Threads share memory. You have to use Mutexes and Atomic locks to prevent corruption.

**Dart uses Isolates.**

An Isolate is exactly what it sounds like: A completely isolated, separate memory heap with its own entirely unique Event Loop executing on a secondary CPU Core.

Because Isolate #1 and Isolate #2 literally *cannot* see each other's RAM, data corruption and Mutex Data Races are mathematically impossible. 

How do they talk? Like microservices! You use a **ReceivePort** and **SendPort**, sending physical JSON/Byte messages between the two Isolates across a channel, exactly like Unix Pipes (Chapter 31) or the Web Worker protocol.

```dart
import 'dart:isolate';

// 1. The Heavy Math Function (Running on Core #2)
void calculatePi(SendPort callerPort) {
    // Spend 5 minutes destroying the CPU.
    // ...
    // Post the answer back through the message channel!
    callerPort.send(3.14159);
}

// 2. The Main UI Thread (Running on Core #1)
void main() async {
    // Open a mailbox
    var receivePort = ReceivePort();
    
    // Command the Dart VM to spin up an Isolate and point it to the mailbox!
    await Isolate.spawn(calculatePi, receivePort.sendPort);
    
    // Wait for the mailbox to ping us. The UI thread is free!
    receivePort.listen((message) {
        print("The background cluster decoded Pi: $message");
    });
}
```
This is the Actor Model of Concurrency. It is brilliant.
