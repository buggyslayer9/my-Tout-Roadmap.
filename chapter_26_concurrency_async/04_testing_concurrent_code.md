# 26.4 Testing Concurrent Code

Writing concurrent code is hard. Testing it is harder.

A normal bug often fails every time. A concurrency bug may fail:

- once a week
- only on one machine
- only in release mode
- only when you are trying to show someone that everything works

That is why we need better habits for testing concurrent code.

## Why Concurrent Tests Are Tricky

Concurrency introduces:

- timing differences
- shared state
- scheduling unpredictability
- race conditions

Two threads may both be correct in isolation and still break when they run together in the wrong order.

## A Small Example

```rust
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = Vec::new();

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut value = counter.lock().unwrap();
            *value += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    assert_eq!(*counter.lock().unwrap(), 10);
}
```

This test is simple, but it still teaches an important idea: concurrent code should end in a predictable final state.

## Good Testing Strategies

### 1. Prefer Deterministic Designs

The easiest concurrent code to test is code that reduces randomness.

Good signs:

- clear ownership
- message passing
- minimal shared mutable state
- explicit synchronization points

If your design is simpler, your tests become simpler too.

### 2. Test Outcomes, Not Timing

Bad idea:

```rust
std::thread::sleep(std::time::Duration::from_millis(50));
assert!(job_finished);
```

This is fragile because machine speed and scheduling vary.

Better idea:

- join spawned threads
- await tasks directly
- use channels or signals to know when work is complete

### 3. Run Tests Repeatedly

If a race condition happens 1 time in 200 runs, one successful run proves nothing.

Useful habit:

```bash
cargo test
cargo test
cargo test
```

Or use loops in CI or local scripts for suspicious code paths.

### 4. Shrink Shared Mutable State

If many threads can mutate the same data, test complexity rises fast.

Ask:

- Can this state be owned by one thread only?
- Can threads send messages instead?
- Can the critical section become smaller?

This is both a design improvement and a testing improvement.

## Testing Async Code

When using `tokio`, async tests often look like this:

```rust
#[tokio::test]
async fn returns_expected_result() {
    async fn compute() -> i32 {
        42
    }

    let result = compute().await;
    assert_eq!(result, 42);
}
```

The main lesson is the same: avoid asserting on timing when you can assert on results and state.

## What To Look For In Reviews

When reviewing concurrent code, ask:

- Where is the shared state?
- Who owns cleanup?
- Could two tasks modify this at once?
- Does this code depend on lucky timing?
- What happens if one task panics or fails early?

These questions often reveal problems before tests do.

## Practical Testing Checklist

- Write small concurrent examples before building large ones
- Assert final state clearly
- Join threads and await tasks explicitly
- Avoid magic sleeps when possible
- Run suspicious tests multiple times
- Prefer channels and ownership over shared mutable state

## Recommended Follow-Up

After this lesson, improve one concurrent exercise by:

- removing a `sleep`
- replacing shared mutation with message passing
- adding a test that checks final state

That is a strong step from "I used threads" to "I can reason about threaded code."
