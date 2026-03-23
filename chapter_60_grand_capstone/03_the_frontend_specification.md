# 50.3 The Frontend Specification (Flutter)

Your Backend API (Rust Axum) is completely headless. It listens on Port 3000 and speaks raw JSON and WebSocket frames.

You must build the cross-platform User Interface using **Flutter**. This single Dart codebase will compile identically to an iOS `.ipa`, an Android `.apk`, and a Native Linux Desktop binary.

## The UI Architecture

Your application must have at least three distinct Screens (Routes):
1. **The Navigation Shell (`Scaffold`)**: A persistent left-hand drawer listing the Channels (General, General-OffTopic, Systems-Programming).
2. **The Login Screen**: A beautiful, animated UI prompting the user for Username and Password.
3. **The Chat Interface**: The central view. The bottom must have a text input field and a Send button. The middle must be a massively scrollable `ListView.builder` displaying thousands of messages efficiently.

## Core Implementations

### 1. State Management (Riverpod)
You must use Riverpod to manage global application state.
- Create an `AuthProvider` that holds the JWT login token. If the user is logged out, Riverpod magically re-routes the entire app to the Login Screen.
- Create a `ChatProvider` that violently tracks the `List<Message>` objects for the currently viewed channel.
- If a message arrives over the WebSocket, pushing it into the `ChatProvider` list must instantly trigger the Skia engine to redraw the `ListView` without calling `setState` on the UI components.

### 2. The Dart WebSocket Client
Instead of HTTP `fetch` calls, you will use the `web_socket_channel` package.

```dart
// The core connection
final channel = WebSocketChannel.connect(
  Uri.parse('wss://api.bugslayer.com/ws/channels/1'),
);

// Listening for incoming JSON from the Rust Multithreading Engine!
channel.stream.listen((message) {
  var data = jsonDecode(message);
  
  // Update Riverpod!
  ref.read(chatProvider.notifier).addMessage(data);
});

// Shooting a pure String across the internet to the Rust Router!
channel.sink.add(jsonEncode({"content": "Hello World!"}));
```

### 3. FFI Cryptography (Optional Challenge)
Instead of sending plaintext passwords over standard HTTPS `POST /login`, implement `flutter_rust_bridge`. 
Spin up an Isolate spanning a Rust instance on the user's physical iPhone. Use the `ring` Rust crate to perform Client-Side Hashing of the password before it ever touches the network. This proves you have mathematically merged Systems Programming with Mobile App Development.

## The UX Requirements
1. **Infinite Scroll:** The `ListView.builder` must instantly query the Rust API `GET /messages?offset=50` the millisecond the user scrolls to the absolute top of the chat history.
2. **Smooth Animations:** Wrap the "Send" button in an `AnimatedContainer`. When pressed, it should mathematically scale down `0.95x` for 50 milliseconds to provide elite, tactile feedback.

If you achieve 120 FPS on your phone while maintaining a live, bi-directional socket to an Axum Router... you have successfully built a full-stack platform.
