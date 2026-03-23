# Assignment 33

## Task

Build a **temperature converter** application using Iced:

### Requirements

1. Create a new Iced project:
   ```bash
   cargo new temp_converter
   ```

2. Add dependencies to `Cargo.toml`:
   ```toml
   [dependencies]
   iced = "0.12"
   ```

3. Implement a temperature converter with:
   - **Input field** for entering temperature value
   - **Live conversion display** showing:
     - Celsius (°C)
     - Fahrenheit (°F)
     - Kelvin (K)
   - **Radio buttons** to select which unit to input
   - **Reset button** to clear the input
   - Clean styling with padding and spacing

### Conversion Formulas

```
Celsius to Fahrenheit: F = (C × 9/5) + 32
Celsius to Kelvin: K = C + 273.15

Fahrenheit to Celsius: C = (F - 32) × 5/9
Fahrenheit to Kelvin: K = (F - 32) × 5/9 + 273.15

Kelvin to Celsius: C = K - 273.15
Kelvin to Fahrenheit: F = (K - 273.15) × 9/5 + 32
```

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **Iced framework** - The Elm-architecture GUI library
2. **Sandbox trait** - Application entry point in Iced
3. **Widget composition** - Using column, row, text, button, text_input
4. **Event handling** - Processing user input
5. **State management** - Application state with Iced messages

---

## Sources

- [Iced Official Guide](https://book.iced.rs/)
- [Iced Examples](https://github.com/iced-rs/iced/tree/master/examples)
- [The Wayland Book](https://wayland-book.com/)

---

## Hints

- Use `iced::widget::text_input` for temperature input
- Use `iced::widget::radio` for selecting input unit
- Parse input with `str::parse::<f64>()`
- Handle invalid input gracefully (show error or ignore)
- Use `.spacing()` and `.padding()` for visual layout

## Example Output

```
┌─────────────────────────────────┐
│   Temperature Converter         │
├─────────────────────────────────┤
│  Input Unit:                   │
│  (•) Celsius                   │
│  ( ) Fahrenheit                │
│  ( ) Kelvin                    │
│                                 │
│  ┌─────────────────────────┐   │
│  │ 25                      │   │
│  └─────────────────────────┘   │
│                                 │
│  Results:                       │
│  Celsius:     25.0 °C          │
│  Fahrenheit: 77.0 °F           │
│  Kelvin:     298.15 K          │
│                                 │
│         [ Reset ]               │
└─────────────────────────────────┘
```
