# Bonus Assignment 05: String Parsing Utility

Build a program that reads one line of text and splits it into parts using a delimiter.

## Requirements

- Read a line safely with `fgets`
- Remove the trailing newline if needed
- Split the string on commas
- Print each token on its own line
- Count how many tokens were found

## Example Input

```text
math,linux,c,gtk,rust
```

## Example Output

```text
Token 1: math
Token 2: linux
Token 3: c
Token 4: gtk
Token 5: rust
Total tokens: 5
```

## Stretch Goals

- Ignore empty tokens
- Support semicolon as a second delimiter
- Trim leading spaces from each token
