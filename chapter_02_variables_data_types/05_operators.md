# 2.5 The Operators

C syntax laid the groundwork for Java, C#, C++, JavaScript, and countless others. If you know the operators here, you know them everywhere.

Let's do a fast fly-by.

## Arithmetic

```c
int a = 10, b = 3;

int sum = a + b;   // 13
int sub = a - b;   // 7
int mul = a * b;   // 30
int div = a / b;   // 3 (Integer division truncates decimals!)
int mod = a % b;   // 1 (Modulo: strictly the remainder of division)
```

## Comparisons (Returns 1 for True, 0 for False)

```c
a == b   // Equal to (Do NOT use single `=` for comparison!)
a != b   // Not equal to
a > b    // Greater than
a <= b   // Less than or equal to
```

## Logical (Boolean math)

```c
(a > 5) && (b < 5)  // Logical AND (Both sides must be true)
(a > 5) || (a < 0)  // Logical OR (At least one side must be true)
!(a == 10)          // Logical NOT (Inverts the result to false)
```
*Veteran Tip*: C uses "Short-circuit evaluation". For `&&`, if the left side is false, the right side is *never even executed*.

## Assignment Shortcuts

```c
a += 5;  // Exactly the same as: a = a + 5;
b -= 1;  // Exactly the same as: b = b - 1;

a++;     // Increment by 1
b--;     // Decrement by 1
```

## Bitwise (The Hackers' Tools)

We manipulate individual 1s and 0s in memory. You will use these when programming microcontrollers, protocols, or graphical color flags (like combining RGB).

```c
a & b    // Bitwise AND
a | b    // Bitwise OR
a ^ b    // Bitwise XOR (Exclusive OR)
~a       // Bitwise NOT (Flips all 1s to 0s, and 0s to 1s)

a << 2   // Left shift (Fast way to multiply by 4)
a >> 1   // Right shift (Fast way to divide by 2)
```
