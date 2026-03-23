# Assignment 39: The Semantic Landing Page

Your task is to build a beautiful, modern, strictly semantic landing page using only HTML5 and CSS3 (No JavaScript).

Do not use Tailwind CSS or Bootstrap. You must write vanilla CSS using Flexbox and Grid.

## The Requirements

1. **Create an `index.html` file.**
2. **Use strictly Semantic Tags.**
   - Include a `<header>` with a `<nav>` inside it.
   - Include a `<main>` container for the core page.
   - Inside `<main>`, create a Hero `<section>` (the massive image and title at the top).
   - Create an `<article>` below it explaining a fake product.
   - Include a `<footer>`.

3. **Create a `style.css` file.**
   - Ensure you link the CSS file inside the HTML `<head>`.
   - Remove the default browser margins: `* { margin: 0; padding: 0; box-sizing: border-box; }`

4. **The Navigation (Flexbox)**
   - Use `display: flex;` on the `<header>`.
   - Use `justify-content: space-between;` to push the Logo to the left and the Nav Links to the right.

5. **The Hero Section (Viewport Units & Centering)**
   - Give the Hero `<section>` a height of `100vh`.
   - Use Flexbox to perfectly center the `<h1>` title in the absolute middle of the screen.
   - Give the `<h1>` a font size of `4rem`.

6. **The Feature Grid (CSS Grid)**
   - Inside your `<article>`, create a `<div>` that contains 3 child `<div class="featureCard">` elements.
   - On the parent container, use `display: grid;`.
   - Use `grid-template-columns: repeat(3, 1fr);` to instantly create three identical, perfectly spaced columns across the page.
   - Add a `gap: 2rem;` to give them breathing room.

7. **Responsive Mobile Design**
   - Shrink your Chrome window to the size of a phone. Your 3-column Grid will look terrible.
   - Write a `@media` query that targets mobile screens (`max-width: 768px`).
   - Inside that query, overwrite the Grid to cleanly stack the 3 features horizontally: `grid-template-columns: 1fr;`.

Open `index.html` locally in your web browser. If it looks massive and beautiful on fullscreen but stacks cleanly on mobile, you have mastered modern CSS.
