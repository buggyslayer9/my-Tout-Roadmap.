# 37.8 TypeScript for Rust Developers

Writing vanilla JavaScript is dangerous for complex applications. Since you know C and Rust, the dynamic, weakly-typed nature of JavaScript will cause you endless runtime frustration. 

**TypeScript (TS)** is a superset of JavaScript that adds static typing. It compiles down to plain JavaScript for the browser.

## The Rust to TypeScript Translation

If you love Rust's type system, TypeScript is the closest you can get on the web frontend.

### 1. Structs → Interfaces / Types

In Rust:
```rust
struct User {
    id: u32,
    name: String,
    is_active: bool,
}
```

In TypeScript:
```typescript
interface User {
    id: number;
    name: string;
    isActive: boolean;
}

// Or using a Type Alias
type UserType = {
    id: number;
    name: string;
    isActive: boolean;
};

const me: User = { id: 1, name: "Ayman", isActive: true };
```

### 2. Option<T> → Nullable types

In Rust, you handle missing data with `Option<T>`. JavaScript uses `null` or `undefined`. TypeScript forces you to handle this at compile time using union types (`|`).

```typescript
// The '?' operator means 'string | undefined'
interface Profile {
    username: string;
    website?: string; 
}

function printWebsite(profile: Profile) {
    // If you try to use profile.website directly, TS gives an error!
    // You MUST check if it exists (like unwrapping an Option).
    if (profile.website) {
        console.log(profile.website.toLowerCase());
    } else {
        console.log("No website provided.");
    }
}
```

### 3. Result<T, E> → Try/Catch or Result Types

JavaScript historically throws exceptions. However, you can write TypeScript to act like Rust's `Result` for safer APIs.

```typescript
// A highly Rust-like pattern in TypeScript
type Result<T, E = Error> = 
  | { success: true; data: T }
  | { success: false; error: E };

function divide(a: number, b: number): Result<number, string> {
    if (b === 0) return { success: false, error: "Division by zero" };
    return { success: true, data: a / b };
}

const result = divide(10, 0);
if (result.success) {
    // TS knows 'result.data' is a number here
    console.log(result.data * 2);
} else {
    // TS knows 'result.error' is a string here
    console.error(result.error);
}
```

### 4. Enums and Pattern Matching

TypeScript has enums, though string literal unions are more common.

```typescript
// Literal union (more common)
type Status = "Loading" | "Success" | "Error";

function handleStatus(state: Status) {
    switch(state) {
        case "Loading": // TS enforces spelling
            return "Spinner";
        case "Success":
            return "Content";
        case "Error":
            return "Error msg";
    }
}
```

## Why TypeScript is Mandatory
1. **Refactoring:** Changing a database column in the Rust backend? You update the TypeScript interface, and the compiler instantly flags every React component that needs updating.
2. **Autocomplete:** Your IDE (VS Code) relies entirely on TypeScript definitions to provide intellisense.
3. **Rust Compatibility:** Tools like `ts-rs` can automatically generate TypeScript interfaces directly from your Rust Axum backend structs! This guarantees your frontend and backend are always perfectly synchronized.
