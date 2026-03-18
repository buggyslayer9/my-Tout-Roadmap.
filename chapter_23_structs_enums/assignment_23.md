# Assignment 23: The Task Manager Core Engine

In our GTK Capstone (Chapter 20), you built a Task Manager relying entirely on C structs and binary memory layouts. 

Now, you will rebuild the core data engine of that Task Manager in Rust using Structs, Enums, and Option types. You will immediately notice how much cleaner and safer the code is compared to C.

## The Task

Create a new cargo project: `cargo new rust_task_manager`

You must build a program that implements the following requirements:

1. **The `Priority` Enum**
   - Create an enum `Priority` with variants `Low`, `Medium`, and `High`.
   - Add `#[derive(Debug, Clone, PartialEq)]` above it so it can be printed, copied easily, and compared.

2. **The `Task` Struct**
   - Create a struct `Task` with fields:
     - `id: u32`
     - `title: String`
     - `priority: Priority`
     - `completed: bool`
   - Implement a `Task::new(id, title, priority)` constructor.

3. **The `TaskList` Struct (The Manager)**
   - Create a struct `TaskList` containing:
     - `tasks: Vec<Task>` (A dynamic list of tasks)
     - `next_id: u32` (Auto-incrementing ID for the next task)
   - Implement `TaskList::new()` to initialize an empty list.
   - Implement `add_task(&mut self, title: &str, priority: Priority)`. It should use `self.next_id`, increment it, and push a new `Task` into the vector.

4. **The `get_task` Method using `Option`**
   - Implement `get_task(&self, id: u32) -> Option<&Task>`. 
   - Iterate through `self.tasks` and return `Some(&task)` if you find the matching ID, or `None` if it doesn't exist.

5. **Main Execution**
   - In `main()`, instantiate a `TaskList`.
   - Add three tasks of varying priorities.
   - Attempt to retrieve a task that exists using `get_task()` and `match`, printing its details.
   - Attempt to retrieve a task that *does not* exist, printing an error message smoothly instead of crashing.

## Example Output

```text
Adding tasks...
Fetching Task ID 2:
Found Task: Learn Rust Enums (Priority: High, Completed: false)

Fetching Task ID 99:
Task ID 99 not found!
```

## Hints

- A `Vec<T>` in Rust is just like a dynamic array. You can add things to it with `.push(item)`.
- When iterating to find a task inside `get_task`, remember you are iterating over references:
```rust
for task in &self.tasks {
    if task.id == id {
        return Some(task);
    }
}
return None;
```
