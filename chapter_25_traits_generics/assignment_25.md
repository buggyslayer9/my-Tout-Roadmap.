# Assignment 25: The Plugin Architecture

In large C applications, building a plugin system requires dynamically loading `.so` libraries and casting `void*` function pointers. It is highly unsafe.

In Rust, we build modular, polymorphic systems using **Traits** and **Box**.

## The Task

You are building the core of a simple CLI assistant that can be expanded with Plugins.

Initialize a new cargo project: `cargo new plugin_system`

1. **Define the `Plugin` Trait**
   - It should mandate three methods:
     - `name(&self) -> String`
     - `version(&self) -> String`
     - `execute(&self) -> String`

2. **Implement Three Plugins**
   - Create three empty structs: `GreetingPlugin`, `MathPlugin`, and `SystemPlugin`.
   - Implement the `Plugin` trait for all three.
   - `GreetingPlugin::execute()` should return a friendly hello message.
   - `MathPlugin::execute()` should return the string "2 + 2 = 4".
   - `SystemPlugin::execute()` should return the string "System running nominally."

3. **The Plugin Manager (Main)**
   - Create a `Vec` to hold your plugins. Since they are different sizes, it must be a vector of Trait Objects: `Vec<Box<dyn Plugin>>`.
   - Instantiate your three structs, wrap them in `Box::new()`, and push them into the vector.

4. **Sort and Execute (Closures)**
   - Use the `v.sort_by()` method to sort the vector alphabetically by plugin name. (You will need to pass a closure to `sort_by`! See hints).
   - Iterate over the sorted vector. For each plugin, print out a format like: `[PluginName v1.0] Result: ...` calling the respective trait methods.

## Example Output

```text
Loading App Plugins...
Executing 3 plugins in alphabetical order:

[GreetingPlugin v1.0.0] Output: Hello, Administrator!
[MathPlugin v1.2.0] Output: 2 + 2 = 4
[SystemPlugin v0.9.1] Output: System running nominally.
```

## Hints

### Sorting Strings via Closure
The `sort_by` method on vectors takes a closure with two parameters: a and b. It expects an `Ordering` enum (`Less`, `Equal`, `Greater`) to be returned. Strings have a built in `.cmp()` method.

```rust
// `a` and `b` are extremely heavily referenced trait objects here.
// You have to call `.name()` to get the strings to compare them!
plugin_list.sort_by(|a, b| a.name().cmp(&b.name()));
```
