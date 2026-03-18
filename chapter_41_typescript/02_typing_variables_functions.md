# 41.2 Typing Variables, Functions, and Objects

To declare a type in TS, you append a colon `:` followed by the type name.

## 1. Primitives

```typescript
// Explicit Typing
let age: number = 25;
let username: string = "BugSlayer";
let isOnline: boolean = true;

// Type Inference
// Just like Rust, TS is smart enough to infer the type if you assign it immediately!
let score = 100; // TS instantly locks 'score' as a 'number' type permanently.

// If you do this, tsc will throw a compilation error:
score = "winner"; // ERROR: Type 'string' is not assignable to type 'number'.
```

## 2. Functions

You must strongly type the input parameters, and you should explicitly type the return value.

```typescript
// Accepts two numbers, strictly returns a number
const add = (a: number, b: number): number => {
    return a + b;
};

// Returns nothing (void)
const logMessage = (msg: string): void => {
    console.log(msg);
};
```

## 3. Objects and Interfaces

In Vanilla JS, passing random Objects blindly into functions is the #1 cause of Undefined crashes.
In TS, we define the strict structural Contract of the Object using an **Interface** (akin to a Rust `struct` definition).

```typescript
// Define the Shape!
interface UserProfile {
    id: number;
    username: string;
    email: string;
    // The question mark makes the field Optional
    avatarUrl?: string; 
}

// Notice we use the UserProfile interface as the DataType here!
const renderUser = (user: UserProfile) => {
    console.log("Rendering ID:", user.id);
    
    // If I type `user.emial`, VS Code throws an instant compiler error!
    console.log("Email:", user.email); 
};

// Instantiating the object
const myUser: UserProfile = {
    id: 99,
    username: "xX_Hacker_Xx",
    email: "hax@example.com"
    // Valid because avatarUrl is optional
};

renderUser(myUser);
```

### The `any` Keyword: The Escape Hatch
If you type a variable as `: any`, you are telling the TS compiler to specifically turn off all mathematical type-checking for that variable. 
It behaves exactly like vanilla, chaotic Javascript.

**The Golden Rule of TypeScript:** Using `any` is a catastrophic anti-pattern. If your codebase has `any` in it, you are defeating the entire purpose of the compiler. Write strict interfaces.
