# Assignment 17: The Styled Counter

Take the Counter app you built in Assignment 13 and make it look professional using CSS classes and an external stylesheet.

## Task

Create a styled counter application with distinct styling for the count label and the three control buttons.

## Visual Design Spec

1. **Global Background:** The window should have a dark gray background (`#282c34`).
2. **Counter Label:** Giant, bold, white text.
3. **Increment Button:** Green background (`#4CAF50`). White text.
4. **Decrement Button:** Red background (`#f44336`). White text.
5. **Reset Button:** Transparent background, but with a white border. White text.
6. **Interaction:** All buttons should have a `transition` applied and slightly change colors on `:hover`.

## Requirements

1. **DO NOT** hardcode the CSS inside strings in your C file. Create a file named `style.css`.
2. Load the CSS using `gtk_css_provider_load_from_path()`.
3. In your C code, assign specific CSS classes to your widgets using `gtk_widget_add_css_class()`:
    - Label: `"counter-label"`
    - Plus button: `"btn-increment"`
    - Minus button: `"btn-decrement"`
    - Reset button: `"btn-reset"`
4. Write the corresponding CSS in `style.css` to match the visual spec above.

## Expected CSS Architecture (Hint)

```css
/* style.css */
window {
    background-color: #282c34;
}

.counter-label {
    font-size: 64px;
    font-weight: 900;
    color: white;
    margin: 20px;
}

.btn-increment {
    background-color: #4CAF50;
    color: white;
    font-weight: bold;
    border-radius: 8px;
    padding: 10px 20px;
    transition: all 0.2s;
}

.btn-increment:hover {
    background-color: #66BB6A;
}

/* Similarly for btn-decrement and btn-reset ... */
```

## Checklist
- [ ] CSS is loaded from an external `style.css` file?
- [ ] Label is drastically larger than the default font?
- [ ] Buttons have distinct colors (Green, Red, Transparent+Border)?
- [ ] Hover states visibly change the button appearance?
