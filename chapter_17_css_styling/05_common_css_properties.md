# 17.5 Common GTK4 CSS Properties

If you know web CSS, you are ready to go. GTK4 supports a massive subset of standard CSS3 properties.

Here is a quick cheat sheet for the most commonly used properties in desktop apps.

## Colors & Backgrounds

```css
color: white;                          /* Text color */
background-color: #336699;             /* Hex colors */
background-color: rgba(255, 0, 0, 0.5);/* Alpha transparency */
background: linear-gradient(to bottom, #336699, #003366); /* Gradients */
```

## Typography

```css
font-family: "Sans";                   /* Use system default sans-serif */
font-size: 16px;                       /* Pixel sizes */
font-size: 1.2em;                      /* Relative sizing */
font-weight: bold;                     /* or numeric: 400, 700 */
font-style: italic;
```

## Box Model & Spacing

```css
padding: 10px 20px;                    /* Top/Bottom 10px, Left/Right 20px */
margin: 5px;                           /* 5px all sides */
border: 1px solid #cccccc;
border-radius: 8px;                    /* Rounded corners */
```

## Visual Effects

```css
opacity: 0.5;                          /* 50% transparent widget */
box-shadow: 0px 4px 12px rgba(0,0,0,0.2); /* x-offset, y-offset, blur, color */
text-shadow: 1px 1px 2px black;
```

## State Pseudo-classes

```css
button:hover { background-color: #ddd; }     /* Mouse over */
button:active { background-color: #ccc; }    /* Actively clicking */
button:disabled { opacity: 0.5; }            /* Widget is set to insensitive */
entry:focus { border-color: blue; }          /* Keyboard focus */
```
