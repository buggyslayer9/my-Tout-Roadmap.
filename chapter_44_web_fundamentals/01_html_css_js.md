# 37.1 Web Fundamentals — HTML5 & CSS3

## HTML5 Structure

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My Portfolio</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <header>
        <nav>
            <a href="#about">About</a>
            <a href="#projects">Projects</a>
            <a href="#contact">Contact</a>
        </nav>
    </header>

    <main>
        <section id="about">
            <h1>Ayman Salem</h1>
            <p>Linux Developer & Systems Programmer</p>
        </section>

        <section id="projects">
            <h2>Projects</h2>
            <div class="card-grid">
                <article class="card">
                    <h3>Custom Linux Distro</h3>
                    <p>A minimal Linux distribution built from scratch</p>
                    <div class="tags">
                        <span class="tag">C</span>
                        <span class="tag">Linux</span>
                    </div>
                </article>
            </div>
        </section>
    </main>
</body>
</html>
```

## CSS3 Modern Layout (Flexbox & Grid)

```css
/* Reset and base */
*, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

body {
    font-family: 'Inter', sans-serif;
    background: #0f0f23;
    color: #e0e0e0;
    line-height: 1.6;
}

/* Flexbox navigation */
nav {
    display: flex;
    gap: 2rem;
    justify-content: center;
    padding: 1rem;
    background: rgba(255,255,255,0.05);
    backdrop-filter: blur(10px);
}

nav a {
    color: #64ffda;
    text-decoration: none;
    transition: color 0.3s ease;
}

nav a:hover { color: #fff; }

/* CSS Grid for cards */
.card-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 1.5rem;
    padding: 2rem;
}

.card {
    background: rgba(255,255,255,0.05);
    border-radius: 12px;
    padding: 1.5rem;
    border: 1px solid rgba(255,255,255,0.1);
    transition: transform 0.3s, box-shadow 0.3s;
}

.card:hover {
    transform: translateY(-4px);
    box-shadow: 0 8px 32px rgba(100, 255, 218, 0.15);
}

/* Responsive */
@media (max-width: 768px) {
    .card-grid { grid-template-columns: 1fr; }
}
```

---

# 38.1 JavaScript & Modern ES6+

```javascript
// === Variables ===
const API_URL = 'https://api.example.com';  // constant
let count = 0;                                // mutable

// === Arrow Functions ===
const add = (a, b) => a + b;
const greet = name => `Hello, ${name}!`;

// === Destructuring ===
const { title, author } = book;
const [first, ...rest] = array;

// === Async/Await & Fetch ===
async function fetchUsers() {
    try {
        const response = await fetch(`${API_URL}/users`);
        if (!response.ok) throw new Error(`HTTP ${response.status}`);
        const users = await response.json();
        return users;
    } catch (error) {
        console.error('Fetch failed:', error);
    }
}

// === DOM Manipulation ===
document.querySelector('#submit-btn').addEventListener('click', async () => {
    const input = document.querySelector('#search-input').value;
    const results = await fetchUsers();
    const container = document.querySelector('#results');
    container.innerHTML = results
        .filter(u => u.name.includes(input))
        .map(u => `<div class="card">${u.name}</div>`)
        .join('');
});

// === Modules ===
// utils.js
export const formatDate = (date) => date.toISOString().split('T')[0];
// main.js
import { formatDate } from './utils.js';
```

## Assignment 37-38

**Task**: Build a **developer portfolio website**:
1. Responsive HTML5 page with header, about, projects, contact sections
2. Dark mode CSS with grid layout, cards, smooth transitions
3. JavaScript: fetch and display your GitHub repos via the GitHub API
4. Search/filter functionality for projects
5. Responsive across mobile, tablet, and desktop

**Sources**:
- [MDN Web Docs](https://developer.mozilla.org/)
- [CSS Tricks — Flexbox Guide](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)
- [JavaScript.info](https://javascript.info/)

---

## 📚 Resources for This Chapter

### Must-Complete (Free Courses)
- [**freeCodeCamp**](https://www.freecodecamp.org/) — Full responsive web design + JS algorithms ⭐
- [**The Odin Project**](https://www.theodinproject.com/) — Full-stack curriculum with projects ⭐
- [**MDN Web Docs**](https://developer.mozilla.org/) — The definitive web reference

### JavaScript Deep-Dive
- [**"Eloquent JavaScript"**](https://eloquentjavascript.net/) — Free book, excellent for fundamentals
- [**"You Don't Know JS"**](https://github.com/getify/You-Dont-Know-JS) — Free book series on JS internals
- [**JavaScript.info**](https://javascript.info/) — Modern tutorial from basics to advanced

### CSS Mastery
- [**Flexbox Froggy**](https://flexboxfroggy.com/) — Learn Flexbox with a game
- [**Grid Garden**](https://cssgridgarden.com/) — Learn Grid with a game
- [**CSS-Tricks Flexbox Guide**](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)
- [**CSS-Tricks Grid Guide**](https://css-tricks.com/snippets/css/complete-guide-grid/)

### Videos
- [**Traversy Media**](https://www.youtube.com/@TraversyMedia) — Full-stack tutorials
- [**Web Dev Simplified**](https://www.youtube.com/@WebDevSimplified) — Clear JS/CSS explanations
- [**Fireship**](https://www.youtube.com/@Fireship) — 100-second tech overviews
- [**The Net Ninja**](https://www.youtube.com/@NetNinja) — Comprehensive series

