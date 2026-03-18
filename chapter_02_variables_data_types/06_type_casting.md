# 2.6 Type Casting: Forcing Conversions

Sometimes you have an integer but you desperately need a float. Or you have a 64-bit number that you need to jam into a 32-bit slot.

**Type casting** is C's mechanism for converting one data type into another.

## Explicit Casting (The Manual Override)

Place the type you want in parentheses `( )` right before the variable.

```c
int x = 7;
int y = 2;

// If we do: double result = x / y;
// x / y evaluates integer division first. 7 / 2 = 3.
// Then 3 is converted to 3.0. We lost the decimal!

// The Correct Way:
double result = (double)x / y;  // Returns 3.5
```
By casting `x` to a `double`, the compiler is forced to use floating-point division instead of integer division.

## Implicit Casting (When C Guesses For You)

C is pretty polite. If you mix types, it automatically promotes the smaller type to match the larger type.

```c
int a = 5;
double b = 2.5;

// 'a' is automatically promoted from int to double before the addition.
double c = a + b;  // 7.5
```

The standard upgrade path is:
`char` → `short` → `int` → `long` → `float` → `double`

## ⚠️ The Danger Zone

Implicit conversions can silently destroy your data. If you jam a large type into a small type (Narrowing), you will lose data, and the compiler might not even warn you.

### Destructive Truncation
```c
double pi = 3.14159;

// We cast double to int. The decimal is obliterated. It does NOT round to nearest!
int flat_pi = (int)pi;  // flat_pi is just 3
```

### Overflow on Narrowing
```c
int big_money = 300;

// A char can only hold up to 127!
// The binary gets chopped off. small_change becomes 44. Total data corruption.
char small_change = (char)big_money; 
```

## The Veteran's Advice
- Always cast **explicitly** when doing division that requires decimals.
- Never rely on implicit narrowing. If you must chop a large variable down to a small one, write the explicit cast `(char)val` so the next programmer knows you *intended* to destroy data.
- Turn on `-Wall -Wextra`. Your compiler will yell at you if an implicit cast looks dangerous.
