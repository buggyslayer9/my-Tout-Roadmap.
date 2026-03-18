# Assignment 24: Word Frequency Counter

It's time to build a classic Computer Science utility: a program that reads a block of text and counts how many times each word appears.

In C, you would be allocating arrays of string pointers, writing a custom hash function, managing memory for each new string, and praying you didn't miss a `free()`.

In Rust, this is a 20-line masterpiece of elegance using `HashMap` and `Result`.

## The Task

Initialize a new cargo project: `cargo new word_counter`

Write a program that does the following:

1. **The `count_words` function**
   - Signature: `fn count_words(text: &str) -> HashMap<String, u32>`
   - Create a mutable empty `HashMap`.
   - Iterate over the words in `text`.
     * Hint: `for word in text.split_whitespace()`
   - Convert the word to lowercase so "The" and "the" count as the same word.
   - Insert the word into the HashMap, incrementing its count if it already exists.
     * Hint: Use the `.entry(word).or_insert(0)` trick!

2. **The `read_and_process` returning `Result`**
   - Signature: `fn read_and_process(filename: &str) -> Result<(), std::io::Error>`
   - Use `fs::read_to_string(filename)?` to read the file. If it fails, the `?` will instantly return the exact OS error (e.g., FileNotFound) to `main`.
   - Pass the file contents to your `count_words` function.
   - Print the resulting HashMap.
   - Return `Ok(())` at the end (`()` is the Unit type, meaning "Nothing but it succeeded").

3. **`main()`**
   - Call `read_and_process("sample.txt")`.
   - Use a `match` statement. If it fails, use `eprintln!("Error: {}", e)` to print the error.

## Setting Up

Create a file named `sample.txt` in the root of your cargo project (next to `Cargo.toml`) and put this sentence inside:
> The quick brown fox jumps over the lazy dog but the dog was not actually lazy

## Example Output

```text
Processing file: sample.txt
Word frequencies:
"the" -> 3
"quick" -> 1
"brown" -> 1
"fox" -> 1
"jumps" -> 1
"over" -> 1
"lazy" -> 2
"dog" -> 2
"but" -> 1
"was" -> 1
"not" -> 1
"actually" -> 1
```

*(Note: HashMaps do not guarantee order! If your output is in a different order, that is perfectly fine).*

## Challenge (Optional)

Can you sort the output so the most frequent words appear at the top?
*Hint: You can't sort a HashMap directly. You'll need to collect the key-value pairs into a `Vec` first, and use the `.sort_by()` method on the vector.*
