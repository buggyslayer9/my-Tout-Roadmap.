# 40.1 The Modern Javascript Engine (V8)

Javascript is the only programming language natively built into web browsers. Every other language you have learned (C, Rust) must be compiled natively to Machine Code, but Javascript is an Interpreted scripting language.

When you send an `.html` file containing a `<script>` tag, Chrome does not magically understand the JS string. It hands the JS syntax over to its integrated **V8 Javascript Engine** (written in C++).

The V8 Engine parses the Javascript, compiles it instantly into Machine Code Just-In-Time (JIT Compiling), and executes it.

## The Quirkiness of JS
Because Javascript was written in 10 days in 1995, it contains horrifying legacy design choices that you must memorize to survive.

### 1. Equality (`==` vs `===`)
In Javascript, the `==` operator aggressively tries to cast types (Type Coercion).
```javascript
0 == "0"    // true  (String cast to integer)
0 == []     // true  (Empty array casts to 0)
"0" == []   // false (Wait what?)
```
**The Law:** Never, ever use `==` in your life. You must always use the Strict Equality Operator `===`.
```javascript
0 === "0"   // false (Integers are not Strings).
```

### 2. Variables (`var` vs `let` / `const`)
Historically, developers created variables using `var x = 5;`.
This caused a nightmare because `var` scopes the variable to the entire Function, escaping loops!

```javascript
function legacyLoop() {
    for (var i = 0; i < 5; i++) {
        // ...
    }
    console.log(i); // This prints 5! The variable escaped the loop!
}
```

In 2015, the ECMAScript 6 (ES6) standard released **Block Scoped** variables.
**The Law:** Never use `var`.
*   Use `const` for variables that should never point to a new value.
*   Use `let` for variables you intend to mutate.

```javascript
const API_URL = "http://example.com";
// API_URL = "http://bad.com"; // Error!

let count = 0;
count++; // 1
```

### 3. Arrow Functions
You can declare functions using the `function` keyword, but ES6 introduced the drastically cleaner **Arrow Function** syntax (similar to Lambdas/Closures in Rust).

```javascript
// Legacy
function add(a, b) {
    return a + b;
}

// Modern Arrow Syntax
const add = (a, b) => {
    return a + b;
}

// Arrow Syntax (Implicit Return for single lines)
const fastAdd = (a, b) => a + b;
```

If you understand `===`, `const`, and `=>`, you are writing modern ES6 JavaScript.
