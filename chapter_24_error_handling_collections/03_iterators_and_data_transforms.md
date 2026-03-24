# 24.3 Iterators and Data Transformation

One reason Rust code can feel elegant is that data transformation often becomes very explicit and composable.

This is where **iterators** become important.

Iterators help you process collections step by step without writing every loop in the same manual style.

## A Familiar Loop

```rust
let numbers = vec![1, 2, 3, 4];
let mut doubled = Vec::new();

for n in numbers {
    doubled.push(n * 2);
}
```

This is fine.

But Rust also gives you a more composable style:

```rust
let numbers = vec![1, 2, 3, 4];
let doubled: Vec<i32> = numbers.into_iter().map(|n| n * 2).collect();
```

Both are valid. The iterator version becomes especially useful when several steps need to be chained together.

## Common Iterator Operations

- `map` transforms values
- `filter` keeps only matching values
- `collect` gathers results into a collection
- `find` returns the first matching value
- `any` checks whether at least one item matches

## Example

```rust
let numbers = vec![1, 2, 3, 4, 5, 6];

let even_squares: Vec<i32> = numbers
    .into_iter()
    .filter(|n| n % 2 == 0)
    .map(|n| n * n)
    .collect();
```

This code says:

1. take the numbers
2. keep only even ones
3. square them
4. collect the result

That is a very readable transformation pipeline once you get used to it.

## Why This Matters

Iterators help you:

- express intent clearly
- reduce repetitive loop code
- transform data step by step

They are especially useful in:

- parsing
- filtering
- formatting
- reporting
- collection cleanup

## Beginner Caution

Do not force iterator chains everywhere just to look advanced.

If a normal `for` loop is clearer, use it.

The goal is not cleverness.

The goal is clear data flow.

## Learning Check

- Can I explain what `map` and `filter` do?
- Can I rewrite a simple loop using iterators?
- Can I choose between an iterator chain and a normal loop based on clarity?

## Recommended Follow-Up

Take one Rust exercise that processes a vector and rewrite it both ways:

- once with a `for` loop
- once with iterators

Then decide which version is clearer.
