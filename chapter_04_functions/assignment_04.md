# Assignment 4: Modular Engineering

A system isn't single monolithic block of code; it is a symphony of tiny, highly robust functions that do exactly one thing perfectly. Your job is to build a mathematical toolkit.

## Assignment 4.1: The Custom Math Library

Write a C program that contains three custom functions, completely utilizing Prototypes (Declarations) above `main()`, and Definitions below `main()`.

### The Functions:
1. `int is_prime(int n);`
   - Takes a number `n`. Returns `1` if the number is prime, and `0` if it is not.
   - *Logic*: A number is prime if it is greater than 1, and no integer between 2 and `sqrt(n)` divides evenly into it (`n % i == 0`).
2. `int power(int base, int exp);`
   - Creates `base^exp`. You **must** solve this using a recursive function. Do not use loops.
   - *Logic*: If `exp` is 0, return `1`. Otherwise, return `base * power(base, exp - 1)`.
3. `void print_primes_up_to(int limit);`
   - Takes an integer `limit`.
   - Uses a `for` loop to scan every number from 2 up to `limit`. It passes each number into your `is_prime()` function. If `is_prime` says `1`, it prints the number separated by a space.

### The `main()` Driver:
Inside `main()`, do three things:
1. Print `2^8` using your `power()` function. 
2. Print all primes up to `50` using your `print_primes_up_to` function.

### Hint regarding `sqrt()`:
If you use `sqrt()` for the prime check, you must `#include <math.h>`. Furthermore, on Linux, you must explicitly tell the linker that you want to attach the math library binary to your program by adding `-lm` to your compile string!
`gcc -Wall -Wextra assign4.c -o assign4 -lm`

## Assignment 4.2: The Bank Vault (Static Scope)

Write a function called `void withdraw_money(int amount);`.

1. Inside the function, create a `static int vault_balance = 1000;`.
2. Check if the `amount` requested is `<= vault_balance`. 
3. If yes, subtract it, and print the remaining `vault_balance`.
4. If no, print an "Insufficient Funds" error.
5. In `main()`, deliberately call `withdraw_money(400);` three times in a row.

Observe how the `vault_balance` perfectly persists its state across multiple function calls without polluting the global scope, ultimately blocking the final withdrawal.

## Submission Checklist

- [ ] Does your math library compile with `-lm`?
- [ ] Is your `power` function genuinely recursive? (Calling itself).
- [ ] Under no circumstances should `vault_balance` be placed outside of the `withdraw_money` function braces. It must be a scoped `static` variable!
