# 40.2 The Document Object Model (DOM)

Javascript by itself cannot draw pixels. It cannot create an `<h1>` tag out of thin air. It is just a math engine.

To actually manipulate the website, the Chrome browser injects a massive global Object into the V8 Engine's memory space called the **DOM** (Document Object Model).

## What is the DOM?

When Chrome downloads an HTML file, its C++ rendering engine parses it and builds an internal C++ Tree Structure representing every tag.

Chrome then exposes a "Binding" (an API) to Javascript, attached to a global variable strictly named `document`.
When you call `document.getElementById('myBox')` in JS, Chrome's V8 engine intercepts that call, searches its internal C++ tree for the requested node, and returns a Javascript Reference Object back to your code.

Every time you modify the Reference Object in JS, the C++ engine instantly repaints the screen.

## 1. Selecting Elements

```html
<h1 id="main-title">Systems Programming</h1>
<p class="article">An intro to the DOM.</p>
<p class="article">By BugSlayer</p>
```

You query the DOM using CSS Selectors (the exact same syntax you use in a `.css` file!)

```javascript
// Query an ID (returns a single Element object)
const title = document.querySelector("#main-title");

// Query a Class (returns a NodeList Array of multiple Elements)
const paragraphs = document.querySelectorAll(".article");

// Select the very first <p> tag
const firstP = document.querySelector("p");
```

## 2. Mutating Elements

Once you have a reference to the Node, you can edit its text, inject raw HTML inside it, or completely change its inline CSS styles.

```javascript
// Change the text!
// The moment this line executes, the webpage instantly updates in front of the user.
title.textContent = "Hacked by JavaScript!";

// Change the CSS directly
title.style.color = "red";
title.style.fontSize = "4rem"; // Remember to use camelCase for CSS properties in JS!

// Inject raw HTML inside the first paragraph
paragraphs[0].innerHTML = "<strong>Warning:</strong> " + paragraphs[0].textContent;
```

## 3. Creating and Deleting Elements

You can ask the C++ engine to allocate a brand new HTML Node in memory, construct it, and then attach it to the visible Tree.

```javascript
// 1. Allocate a Node in RAM (It is invisible so far)
const newButton = document.createElement("button");
newButton.textContent = "Click Me";
newButton.className = "btn-primary";

// 2. Attach it to the visible Tree!
// Append it to the bottom of the <body> tag.
document.body.appendChild(newButton);

// 3. Delete an element completely
title.remove();
```

## 4. The Event Loop (Listeners)

The most critical feature of JS is interactivity. 
Instead of polling a `while` loop waiting for user input, JS relies on an Asynchronous Event Loop. You register a function with the C++ Engine, and the Engine "Calls Back" completely randomly when the user clicks the mouse.

```javascript
newButton.addEventListener("click", () => {
    // This code only runs when the button is physically clicked!
    console.log("The user clicked the button!");
    
    // We can even manipulate the DOM in reaction to the click
    newButton.style.backgroundColor = "blue";
    newButton.textContent = "Clicked!";
});
```
