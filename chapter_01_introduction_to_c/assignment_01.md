# Assignment 1: Welcome to the Command Line

Alright, recruit. Enough theory. It's time to write some code. These assignments are designed to get your terminal fingers warmed up and test your understanding of `printf`, basic CLI flags, and C structure. Complete them all before moving to Chapter 2.

## Assignment 1.1: The Formatted Dossier

Write a C program that prints out a formatted "hacker dossier" about yourself into the terminal.

### Requirements:
1. You must use aligned `printf` statements (e.g. `%-20s`).
2. You must use a mix of string (`%s`), integer (`%d`), and float (`%.2f`) formats.
3. Draw a box around the output using either ASCII art (`+---+`) or fancy Unicode box characters (`╔═══╗`).
4. Output should look similar to this:

```
+-------------------------------------------------+
|               AGENT DOSSIER                     |
+-------------------------------------------------+
| Alias:        BugSlayer                         |
| Years Exp:    3                                 |
| Coffee/Day:   3.14                              |
| Language:     C / GTK                           |
+-------------------------------------------------+
```

## Assignment 1.2: The Echo Chamber (Command Line Args)

We talked about `argc` and `argv`. Time to prove you understand them.

Write a program called `echo_chamber.c` that closely mimics the Unix `echo` command.

### Requirements:
1. The program parses the arguments passed to it and prints them out on a single line, separated by spaces.
2. If the user passes *no* arguments, print a usage error message and return `1`.
3. Wait, `argv[0]` is the program name! Don't print the program name! Only print `argv[1]` and beyond.

Example execution:
```bash
$ gcc -Wall -Wextra -std=c11 echo_chamber.c -o echo_chamber
$ ./echo_chamber
Usage: ./echo_chamber <text to echo>
$ ./echo_chamber Hello Unix World!
Hello Unix World!
```

## Assignment 1.3: The Math Exploit (Format String Magic)

Write a program that takes exactly one integer argument from the command line, converts it, and displays it in standard decimal, padding with zeros, and hexadecimal.

### Requirements:
1. Ensure the user provides exactly one argument (so `argc` should be 2).
2. Use the C library function `atoi()` to parse the string argument `argv[1]` into an integer. (You will need to `#include <stdlib.h>`).
3. Print the number in three formats using `printf`:
   - Normal decimal (`%d`)
   - Decimal padded to 8 digits with leading zeros (`%08d`)
   - Hexadecimal with a "0x" prefix (`0x%x`)

Example execution:
```bash
$ ./hex_converter 255
Decimal: 255
Padded:  00000255
Hex:     0xff
```

## Submission Checklist

- [ ] Did you compile with `-Wall -Wextra -std=c11`?
- [ ] Were there absolutely zero warnings during compilation?
- [ ] Did you properly handle the case where `argc` is too low without causing a Segmentation Fault?
- [ ] Did you `return 0;` at the end of your programs?

If you hit a wall, run `man 3 printf` in your terminal. Reading manual pages is a superpower. Now get to work.
