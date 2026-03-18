# Assignment 21: Rust Engine Warm-up

Before we dive into the deep end of Rust memory safety (Ownership & Borrowing), you need to get comfortable with the syntax and the Cargo build system.

## The Task

Write a command-line utility that calculates and analyzes sequences of numbers.

1. **Project Setup:** Initialize a new cargo project called `number_analyzer`.
2. **The `is_even` function:** Write a function `is_even(n: i32) -> bool` that returns true if a number is even. (Remember, use an expression return, no semicolon!).
3. **The `analyze_sequence` function:** Write a function that uses a `for` loop to iterate from `1` to `N` (inclusive).
   - Use a `match` statement inside the loop.
   - If the number is divisible by both 3 and 5, print "FizzBuzz".
   - If the number is divisible by 3, print "Fizz".
   - If the number is divisible by 5, print "Buzz".
   - If none of these, use the `is_even` function. If even, print "[Number] is Even", if odd, print "[Number] is Odd".
4. **The `sum_loop` function:** Write a function that uses a pure `loop` block to add numbers together until the sum exceeds 100, then `break` returning the final sum, assigning it to a variable in `main()`.

## Core Objectives

- Practice using `cargo run`.
- Practice the difference between statements and expressions.
- Build muscle memory for `match` exhaustiveness.
- Experience the fact that `if` and `loop` can return values directly to variables.

## Expected Output

Your `main()` should call `analyze_sequence(15)` and print the result of `sum_loop()`.

```text
1 is Odd
2 is Even
Fizz
4 is Even
Buzz
Fizz
7 is Odd
8 is Even
Fizz
Buzz
11 is Odd
12 is Even
13 is Odd
14 is Even
FizzBuzz
The loop stopped at a sum of: 105
```

## Hints

- Divisibility is checked using the modulo operator exactly like C: `n % 3 == 0`.
- To match multiple conditions simultaneously, use a tuple in your match block:

```rust
match (n % 3 == 0, n % 5 == 0) {
    (true, true)  => println!("FizzBuzz"),
    (true, false) => println!("Fizz"),
    // ...
}
```
- In your `loop`, don't forget you need your accumulator variable (e.g., `let mut sum = 0;`) declared *outside* the loop! And you can return the sum using `break sum;`.
