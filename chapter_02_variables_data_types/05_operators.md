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

Bitwise operators manipulate individual 1s and 0s in memory. You will use these when programming microcontrollers, writing network protocols, cryptography, or packing graphical color flags (like extracting RGB channels from a hex code).

```c
a & b    // Bitwise AND (1 if both bits are 1, else 0)
a | b    // Bitwise OR
a ^ b    // Bitwise XOR (Exclusive OR)
~a       // Bitwise NOT (Flips all 1s to 0s, and 0s to 1s)

a << 2   // Left shift (Fast way to multiply by 4)
a >> 1   // Right shift (Fast way to divide by 2)
```

### Deep Dive: Bitwise AND (`&`)

The bitwise AND operator compares two numbers bit by bit. The resulting bit is `1` *only* if the corresponding bits from **both** numbers are `1`. If either bit is `0`, the result is `0`.

**How it works:**
```text
  11001010  (Number A = 202)
& 00001111  (Number B = 15)
  --------
  00001010  (Result   = 10)
```
Only the bits where *both* A and B have a `1` drop down to the result as a `1`.

**Why is this actually useful? (Use Cases)**

1. **Masking (Checking a specific flag/bit)**
   Often in C (like in Linux or hardware programming), you pack multiple true/false settings into a single `int` to save memory. Bitwise AND lets you "mask out" everything you don't care about and check if a specific bit is on.
   ```c
   int flags = 0b00000101; // Current state (Bits 0 and 2 are ON)
   int IS_READ_ONLY = 0b00000100; // The flag we want to check (Bit 2)

   // 0b00000101 & 0b00000100 produces 0b00000100
   if (flags & IS_READ_ONLY) {
       printf("The Read Only flag is ON!\n");
   }
   ```

2. **Isolating/Extracting values (e.g., Color channels)**
   If you have a 32-bit hex color like `0xAABBCCDD` (Alpha, Red, Green, Blue) and you just want the Green component (`0xCC`), you can shift the bits and AND them with `0xFF` to clear out everything else.
   ```c
   unsigned int color = 0xAABBCCDD; 
   // Shift right by 8 bits to move the Green value to the end: 0x00AABBCC
   // Then AND with 0xFF (00000000000000000000000011111111 in binary) 
   unsigned int green = (color >> 8) & 0xFF; // Result is 0xCC
   ```

3. **Checking for Odd/Even numbers (Optimization hack)**
   Every odd number in binary ends with a `1`. Even numbers always end with a `0`.
   You can AND a number with `1` to instantly see if it's odd. It's often faster than modulo (`% 2`).
   ```c
   int num = 43; // Binary: 0b00101011
   if (num & 1) {
       printf("It's odd!\n"); // Because the final bit was 1
   }
   ```

### Deep Dive: Bitwise OR (`|`)

The bitwise OR operator compares numbers bit by bit. The resulting bit is `1` if **at least one** of the corresponding bits from either number is `1`.

**How it works:**
```text
  10100000  (Number A = 160)
| 00001010  (Number B = 10)
  --------
  10101010  (Result   = 170)
```

**Use Case: Setting a Flag**
If you have a binary state and you want to explicitly turn ON a specific bit without changing any others, you use OR.
```c
int flags = 0b00000100; // Bit 2 is ON
int SET_READ_WRITE = 0b00000010; // We want to turn ON Bit 1

flags = flags | SET_READ_WRITE; 
// Now flags = 0b00000110 (Bits 1 and 2 are ON)
```

### Deep Dive: Bitwise XOR (`^`)

XOR stands for "Exclusive OR". The result is `1` *only* if the two bits are **different** from each other. If they are the same (both `0` or both `1`), the result is `0`.

**How it works:**
```text
  11001100  (Number A = 204)
^ 10101010  (Number B = 170)
  --------
  01100110  (Result   = 102)
```

**Use Cases:**
1. **Toggling a Flag:** XORing a bit with `1` flips its state. XORing it with `0` leaves it alone. This is perfect for toggling an LED in embedded programming without needing an `if` statement.
   ```c
   int led_state = 0b00000001; // Initial state (ON)
   led_state = led_state ^ 0b00000001; // Toggles to 0 (OFF)
   led_state = led_state ^ 0b00000001; // Toggles back to 1 (ON)
   ```
2. **Simple Cryptography:** XOR is the core of basic encryption algorithms. If you XOR a message with a "key", it looks like garbage. If you take that garbage and XOR it with the *exact same key*, your original message pops back out!

### Deep Dive: Bitwise NOT (`~`)

This acts on a single number. It is also known as the "One's Complement", and it simply flips every single bit. `1`s become `0`s, and `0`s become `1`s.

**How it works:**
```text
~ 00001111  (Number A = 15)
  --------
  11110000  (Result   = 240)
```

**Use Case: Clearing a Flag**
If you want to turn OFF exactly one bit (e.g., bit 2: `0b00000100`) without affecting other bits, you invert a mask and then use AND.
```c
int flags = 0b11111111; // All bits ON
int TURN_OFF_BIT = 0b00000100; // The bit to clear

flags = flags & ~TURN_OFF_BIT; 
// ~TURN_OFF_BIT is `11111011`
// So flags becomes `11111011`
```

### Deep Dive: Shifts (`<<` and `>>`)

Bit shifting literally moves bits to the left or right in memory.
- **Left Shift (`<<`)**: Moves bits left, shifting in `0`s on the right side.
- **Right Shift (`>>`)**: Moves bits right, discarding the bits that fall off the end.

**How it works:**
```text
  00000101  (Number A = 5)
A << 2
  --------
  00010100  (Result = 20)
```

**Use Cases:**
1. **Super Fast Math:** Shifting left by `1` multiplies a number by 2. Shifting by `2` multiplies by 4. Shifting right by `1` divides by 2. Because processors work in binary, this is drastically faster than actual `*` and `/` operations.
2. **Creating clear bitmasks:** Instead of writing out `0b00010000`, programmers often write `1 << 4` ("take `1` and push it left by 4 spots"). It's mathematically the exact same thing, but immediately obvious that you are specifically targeting bit #4.
