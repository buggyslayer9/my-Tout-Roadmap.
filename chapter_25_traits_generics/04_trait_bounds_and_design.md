# 25.4 Trait Bounds and API Design

Traits and generics become much more useful when you start thinking about API design.

A good API is not only “generic.”

It is also:

- understandable
- constrained for the right reasons
- pleasant to use

## Trait Bounds

A trait bound tells Rust:

> this generic type must support certain behavior

Example:

```rust
fn print_twice<T: std::fmt::Display>(value: T) {
    println!("{}", value);
    println!("{}", value);
}
```

This means `T` must implement `Display`.

## Why This Matters

Without trait bounds, generic code can become too vague.

With the right bounds, your function becomes clearer:

- what kind of values it accepts
- what behavior it needs
- what promises it makes

## API Design Question

When writing a generic function, ask:

- what behavior do I actually need?
- am I asking for too much?
- would a specific type be clearer here?

These questions help you avoid over-engineering.

## Learning Check

- Can I explain what a trait bound does?
- Can I read a generic function and identify what behavior is required?
- Can I avoid making code generic without a good reason?

## Recommended Follow-Up

Write a small generic function with one trait bound and explain why that bound is needed.
