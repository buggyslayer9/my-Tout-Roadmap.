# 41.3 Generics and Utility Types

Interfaces are powerful, but sometimes you don't know the exact internal shape of the data a function will handle.
You need a function that can operate on *any* typed Object, without destroying the type safety by using `any`.

You need **Generics** (exactly like `<T>` in Rust).

## 1. Generic Functions

Imagine a function that takes an Array of things, and returns the first element.

```typescript
// The <T> acts as a placeholder for whatever Type the user passes in!
function getFirstElement<T>(items: T[]): T {
    return items[0];
}

// When you call it with numbers, T permanently becomes 'number'.
const nums = [1, 2, 3];
// TS infers the return type is automatically 'number'!
const firstNum = getFirstElement(nums); 

// When you call it with strings, T permanently becomes 'string'!
const words = ["apple", "banana"];
const firstWord = getFirstElement(words); 
```

## 2. Generic Interfaces (API Responses)

When you `fetch()` JSON from a REST API, you want to strictly type the response body before you pass it to your UI code. 

APIs often use a standard envelope format:
```json
{
  "status": 200,
  "message": "Success",
  "data": { ... } // The actual payload goes here
}
```
You can use a Generic Interface to represent this envelope, allowing developers to inject their specific payload structs inside the `data` field!

```typescript
// The Envelope
interface ApiResponse<BodyType> {
    status: number;
    message: string;
    data: BodyType;
}

// Specific Payload 1: A User Profile
interface UserData {
    username: string;
    email: string;
}

// Combining them!
const fetchUser = async (): Promise<ApiResponse<UserData>> => {
    // ... logic ...
    return {
        status: 200,
        message: "Found user",
        data: { username: "BugSlayer", email: "test@test.com" }
    };
};
```

Notice the massive power here: `Promise<ApiResponse<UserData>>`.
This strictly tells the compiler:
1. This function is `async` and returns a `Promise`.
2. When the Promise resolves over the internet, it contains the `ApiResponse` envelope.
3. When you open the envelope's `.data` field, it physically guarantees the existence of `.username` and `.email`.

You have achieved 100% end-to-end type safety across an asynchronous network boundary.
