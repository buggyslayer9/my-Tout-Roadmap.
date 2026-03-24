# 38.4 WebAssembly (Wasm) & Rust 

Historically, JavaScript was the only language you could execute in a web browser. **WebAssembly (Wasm)** changes everything. 

Wasm is a low-level, assembly-like binary format designed to run flawlessly at near-native speed in modern web browsers. Crucially, C, C++, and **Rust** can compile down to WebAssembly.

## The Superpower: Shared Code
By compiling Rust to Wasm, you can:
1. Run heavy computations (image processing, physics engines, cryptographic hashing) in the browser, leaving JavaScript to just handle DOM updates.
2. **Share logic** between your Axum backend and your React frontend (e.g., sharing the exact same validation logic for passwords).

## 1. Setting Up `wasm-pack`

`wasm-pack` is the official toolchain for compiling Rust to Wasm and generating the JavaScript wrappers needed to import it.

```bash
# Install the wasm-pack CLI
cargo install wasm-pack
```

## 2. Writing Rust for the Web

Create a new Rust library project.
```bash
cargo new --lib hero_math
cd hero_math
```

In your `Cargo.toml`, add `wasm-bindgen`. This crate generates the JS glue code.
```toml
[lib]
crate-type = ["cdylib"]

[dependencies]
wasm-bindgen = "0.2"
```

Now, write a Rust function and annotate it with `#[wasm_bindgen]`:

```rust
// src/lib.rs
use wasm_bindgen::prelude::*;

// This annotation exports the function to JavaScript
#[wasm_bindgen]
pub fn calculate_primes(max: u32) -> Vec<u32> {
    let mut primes = Vec::new();
    for i in 2..=max {
        if is_prime(i) {
            primes.push(i);
        }
    }
    primes
}

fn is_prime(n: u32) -> bool {
    if n <= 1 { return false; }
    for i in 2..=(n as f64).sqrt() as u32 {
        if n % i == 0 { return false; }
    }
    true
}
```

## 3. Compiling to WebAssembly

Run `wasm-pack`:
```bash
wasm-pack build --target web
```
This command compiles your Rust code into a tiny `.wasm` binary and creates a `pkg/` directory containing the `hero_math.js` wrapper.

## 4. Calling Rust from JavaScript (React)

You can now import this generated package directly into your React/JS project!

```javascript
import init, { calculate_primes } from './pkg/hero_math.js';

async function runWasm() {
    // Initialize the WebAssembly module
    await init();
    
    console.time("Rust execution");
    // Call the Rust function directly from JavaScript!
    const primes = calculate_primes(1000000);
    console.timeEnd("Rust execution");
    
    console.log(`Found ${primes.length} primes.`);
}

runWasm();
```

If you try calculating 1,000,000 primes in pure JavaScript vs compiling Rust to WebAssembly, the Wasm version is massively faster. This allows you to build desktop-grade powerful applications (like Figma or Photoshop) directly in the browser!
