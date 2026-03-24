# 21.4 A Practical Cargo Workflow

One of Rust's biggest advantages is that the tooling is part of the learning experience.

In C, you often had to assemble your workflow from separate tools. In Rust, **Cargo** gives you a built-in way to:

- create projects
- build code
- run code
- test code
- format code
- check lints

Learning Cargo early saves time later.

## Create A New Project

```bash
cargo new hello_rust
cd hello_rust
```

This gives you a working project structure immediately.

## Build vs Run

To compile:

```bash
cargo build
```

To compile and run:

```bash
cargo run
```

This small difference matters. Sometimes you only want to build. Sometimes you want the full build-and-run loop.

## Fast Checks During Development

Cargo also provides:

```bash
cargo check
```

`cargo check` is often faster than a full build because it checks correctness without producing the final binary in the same way.

This is very useful while iterating on code.

## Run Tests

```bash
cargo test
```

As your projects grow, testing becomes part of normal development, not a separate phase at the end.

## Format Your Code

```bash
cargo fmt
```

This keeps formatting consistent and reduces style debates.

## Run Lints

```bash
cargo clippy
```

Clippy helps catch:

- suspicious patterns
- unnecessary complexity
- style issues with practical value

You should not obey every lint blindly, but it is a powerful teaching tool.

## Release Builds

For optimized builds:

```bash
cargo build --release
```

This matters when performance is important or when you want a more realistic production binary.

## A Good Daily Workflow

A practical beginner workflow often looks like this:

1. write a small amount of code
2. run `cargo check`
3. run `cargo run`
4. fix warnings or errors
5. run `cargo test`
6. run `cargo fmt`
7. run `cargo clippy`

This gives you a clean learning loop.

## Why This Matters

When learners say “Rust feels strict,” part of the answer is:

yes, but the toolchain is also trying to help you build reliable habits.

Cargo is one of the reasons Rust projects stay organized even as they grow.

## Learning Check

- Can I explain the difference between `cargo build`, `cargo run`, and `cargo check`?
- Can I run formatting, tests, and lints on a project?
- Can I describe why Cargo is such a big improvement over ad hoc build habits?

## Recommended Follow-Up

Create a small Rust project and practice this exact command sequence:

```bash
cargo check
cargo run
cargo test
cargo fmt
cargo clippy
```

That routine will help in nearly every Rust chapter that follows.
