# Assignment 37

## Task

Build a **personal developer portfolio website**:

### Part 1: HTML Structure

Create an HTML5 page with:
- **Header**: Navigation bar with links to sections
- **Hero section**: Your name, title, brief intro
- **About section**: Brief bio, skills list
- **Projects section**: Grid of project cards
- **Contact section**: Email, GitHub link, LinkedIn link
- **Footer**: Copyright, social links

### Part 2: CSS Styling

Create a modern dark-themed portfolio:
- Use CSS variables for colors
- CSS Grid for project cards layout
- Flexbox for navigation
- Responsive design (mobile, tablet, desktop)
- Smooth scroll behavior
- Hover effects on cards and buttons

### Part 3: JavaScript - GitHub API Integration

Add dynamic functionality:
1. Fetch your GitHub repositories using the GitHub API:
   ```
   https://api.github.com/users/YOUR_USERNAME/repos
   ```

2. Display repositories dynamically:
   - Show repo name, description, language, stars
   - Link to the repo on GitHub

3. Add search/filter functionality:
   - Filter repos by name
   - Sort by stars or date

### Part 4: Responsive Design

Ensure the site works on:
- Mobile (320px+)
- Tablet (768px+)
- Desktop (1024px+)

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **HTML5 semantic elements** - header, nav, section, article, footer
2. **CSS3 layouts** - Flexbox and CSS Grid
3. **CSS variables** - Custom properties for theming
4. **JavaScript ES6+** - Arrow functions, async/await, fetch
5. **REST APIs** - Consuming GitHub API
6. **DOM manipulation** - Creating elements dynamically

---

## Sources

- [MDN Web Docs](https://developer.mozilla.org/)
- [GitHub REST API](https://docs.github.com/en/rest)
- [freeCodeCamp](https://www.freecodecamp.org/)

---

## Hints

- Use semantic HTML: `<header>`, `<nav>`, `<main>`, `<section>`, `<footer>`
- Use `fetch()` with async/await for GitHub API
- Use `display: grid` with `grid-template-columns: repeat(auto-fit, minmax(300px, 1fr))` for responsive cards
- Use media queries for different screen sizes
- Use CSS custom properties: `:root { --primary-color: #64ffda; }`

## Example Output

```
┌─────────────────────────────────────────────────────────┐
│  Portfolio                              Projects About │
├─────────────────────────────────────────────────────────┤
│                                                         │
│                    John Doe                             │
│            Full-Stack Developer                         │
│                                                         │
├─────────────────────────────────────────────────────────┤
│  My Projects                                           │
│  ┌─────────────────┐  ┌─────────────────┐             │
│  │ linux-distro    │  │ gtk4-app        │             │
│  │ ⭐ 123          │  │ ⭐ 89           │             │
│  │ C               │  │ Rust            │             │
│  └─────────────────┘  └─────────────────┘             │
│                                                         │
│  Filter: [________________]                             │
├─────────────────────────────────────────────────────────┤
│  © 2025 John Doe | GitHub | Email                       │
└─────────────────────────────────────────────────────────┘
```
