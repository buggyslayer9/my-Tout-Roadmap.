# Assignment 26: Building `rgrep` (Concurrent File Search)

It's time for the final project of Rust Fundamentals (Phase 3). You are going to build a multithreaded clone of the classic `grep` utility.

In C, building a multithreaded recursive directory searcher that doesn't data-race when appending results to a shared array is a highly complex task. In Rust, you can do it safely in under 50 lines.

## The Task

Initialize a new cargo project: `cargo new rgrep`

### Dependencies
Open `Cargo.toml` and add this exact dependency:
```toml
[dependencies]
walkdir = "2.4"
```

### Requirements

1. **Accept Command Line Arguments**
   - Use `std::env::args().collect::<Vec<String>>()` to get the arguments.
   - Arg 1: The target string to search for (e.g., "TODO").
   - Arg 2: The directory path to search in (e.g., "./src").

2. **Recursive Traversal**
   - Use `walkdir::WalkDir::new(&search_path)` to recursively gather all files in the directory.
   - Build a `Vec<String>` of all the file paths. (Make sure you filter out directories using the `.is_file()` method on the WalkDir entry!).

3. **Shared State Setup**
   - Create a `Vec<String>` to hold all the matched lines.
   - To make it thread safe, wrap it up: `let matches = Arc::new(Mutex::new(Vec::new()));`

4. **Spawn Threads for Searching**
   - Iterate over your list of files.
   - For *each* file, spawn a thread (`thread::spawn`). 
   - *Inside the thread:*
     - Read the file line by line (Use `std::fs::read_to_string`).
     - If a line contains the target string, lock the `matches` mutex and push a formatted string into it: `[filename:line_number] the matched text`.
   - *Hint:* Don't forget to push your thread handles into a `Vec` so you can call `join()` on all of them at the end!

5. **Print Results**
   - Print the total number of matches found, followed by printing every string stored in your mutex-guarded vector.

## Example Output

```bash
$ cargo run -- TODO .

Searching for "TODO" in .
Found 3 matches!
[./src/main.rs:15] // TODO: Refactor this into a struct
[./src/utils.rs:4] // TODO: Handle network timeouts
[./tests/integration.rs:42] // TODO: Write more tests for async worker
```

If it compiles, it runs without data races. Congratulations, you are now a capable Rust systems programmer!
