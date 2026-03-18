# Assignment 22: The Borrow Checker Battle

It's time to face the boss: **The Rust Borrow Checker**. 

In C, String manipulation is a minefield of `malloc`, `realloc`, and `strtok` null pointers. In Rust, you're going to build a String utility library that parses text with absolutely zero memory allocations or memory leaks.

## The Task

Initialize a new cargo project: `cargo new string_utils`.

Write a program that takes a long sentence and does the following using only references (`&str`) and *without* allocating new memory wherever possible:

1. **`find_first_word(s: &str) -> &str`**
   - Must return a string slice (`&str` — a reference to the characters in the original string) of the first word.
2. **`find_longest_word(s: &str) -> &str`**
   - Iterate over the string, find the longest continuous word, and return a reference to it.
3. **`count_words(s: &str) -> usize`**
   - Return the total number of words in the sentence.
4. **`replace_first_word(s: &mut String, new_word: &str)`**
   - This one **mutates** the string! You must borrow it mutably (`&mut`). 
   - Remove the first word and replace it with `new_word`.

## Core Objectives

- Practice the difference between `String` (Owned Heap Memory) and `&str` (Borrowed Stack Reference).
- Understand how returning a string slice (`&str`) is infinitely faster and safer than returning a `char*` in C.
- Practice borrowing mutably with `&mut` to change data in place.

## Example Output

```text
Original: "The quick brown fox jumps over the lazy dog"
First word: "The"
Longest word: "quick" (length: 5)
Total words: 9

Mutating string...
Modified: "A quick brown fox jumps over the lazy dog"
```

## Hints

### The Power of `&str` Iterators

In C, finding a space required pointer arithmetic: `while(*p != ' ') p++;`. 
In Rust, `&str` has incredible built-in iterators that return other slices extremely safely:

```rust
// .split_whitespace() automatically breaks a string into word references!
for word in sentence.split_whitespace() {
    println!("Word: {}", word);
    println!("Length: {}", word.len());
}
```

### Mutating a String
To replace the first word, you can use built-in `String` methods like `.replace_range()`. 

```rust
// Find the length of the first word, then replace that range!
// The '..length' syntax is a Range.
s.replace_range(..first_word_length, "NewWord"); 
```

Good luck. If your code compiles, it is guaranteed to have zero memory bugs!
