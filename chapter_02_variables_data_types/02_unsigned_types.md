# 2.2 Unsigned Types: Eliminating the Negative

When you add the `unsigned` keyword to an integer type, you strip away its ability to hold negative numbers. As a reward, the compiler gives that memory bit back to you, effectively **doubling its positive range**.

If something can *never* be negative—like the length of an array, the size of a file, or a memory address—use an `unsigned` type.

## The Difference it Makes

| Type | Signed Range | Unsigned Range |
|------|-------------|----------------|
| `char` | -128 to +127 | `0` to `255` |
| `short` | -32,768 to +32,767 | `0` to `65,535` |
| `int` | -2.1B to +2.1B | `0` to `4.2B` |

## Code Example

```c
// Example of maximums
unsigned int max_users = 4294967295U; // Notice the 'U' suffix

// We almost always use unsigned char for raw binary data (like reading a network image)
unsigned char image_byte = 255; 
```

## ⚠️ The Deadly Unsigned Overflow Trap

Unsigned integers do not go below zero. They **wrap around** to their maximum value. This causes catastrophic bugs if you aren't paying attention.

```c
unsigned int countdown = 0;
countdown--; // This does NOT equal -1. 

// countdown is now 4,294,967,295!
printf("Countdown: %u\n", countdown); // Notice we use %u for printing unsigned values
```

If you use `unsigned` in a loop counting backwards, you will create an infinite loop:

```c
// INFINITE LOOP WARNING
for (unsigned int i = 10; i >= 0; i--) {
    // i goes ... 2, 1, 0, 4294967295, 4294967294 ... 
    // It is ALWAYS >= 0.
}
```

## The Veteran's Checklist

- ✅ **DO** use `unsigned char` when handling binary file/network bytes.
- ✅ **DO** use `unsigned int` for bitmasks and flags.
- ✅ **DO** use `size_t` (an unsigned type) for array lengths and memory sizes.
- ❌ **DO NOT** use `unsigned` just because a value "shouldn't" be negative. If doing math, stick to `int`. It acts natural.
