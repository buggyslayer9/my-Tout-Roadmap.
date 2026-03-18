# 39.2 Modern CSS Layouts: Flexbox and Grid

CSS (Cascading Style Sheets) controls the visual presentation of HTML.

Historically, centering a `<div>` in CSS was a notorious running joke in the developer community. Developers used `float: left` and terrifying `display: table` hacks to lay out websites.

Today, CSS boasts two immense, mathematically flawless layout engines. If you master these two tools, you will almost never need hacks again.

---

## 1. CSS Flexbox (1-Dimensional Layouts)

Flexbox is designed to lay out items in a single line (either a Row horizontally or a Column vertically). It is extremely powerful for Navbars, Toolbars, and spacing items evenly without doing math.

```html
<div class="navbar">
    <div class="logo">App</div>
    <div class="links">Links...</div>
    <div class="profile">User</div>
</div>
```

```css
.navbar {
    /* Instantly puts the 3 child divs into a horizontal Row */
    display: flex;       
    
    /* Center the items vertically inside the navbar */
    align-items: center; 
    
    /* Push 'logo' to far left, 'profile' to far right, and center 'links' */
    justify-content: space-between; 
}
```

### The Ultimate Centering Trick
To perfectly center a single item inside a massive full-screen Box, you execute three lines of code:
```css
.hero-box {
    display: flex;
    justify-content: center; /* Center horizontally */
    align-items: center;     /* Center vertically */
    height: 100vh;           /* Take up 100% of the screen height */
}
```

---

## 2. CSS Grid (2-Dimensional Layouts)

Flexbox is for aligning things in a single line. **CSS Grid** is for aligning things in two dimensions simultaneously (Rows *and* Columns), like a checkerboard.

It is designed for building entire Website Page Layouts.

```html
<div class="dashboard">
    <header class="header">Header</header>
    <aside class="sidebar">Sidebar</aside>
    <main class="content">Content</main>
</div>
```

If you want a classic two-column dashboard with a header spanning the top, you use Grid:

```css
.dashboard {
    display: grid;
    
    /* 1. Define the Columns: 
       Make the Sidebar 250px wide permanently.
       Make the Content take up 1 'Fraction' (the remaining 100% of space).
    */
    grid-template-columns: 250px 1fr;
    
    /* 2. Define the Rows:
       Header is 80px tall. Core content takes up everything else.
    */
    grid-template-rows: 80px 1fr;
}

/* 3. Assign the Header to physically stretch across both columns! */
.header {
    grid-column: 1 / -1; /* Start at column line 1, stretch to the final end line */
}
```

CSS Grid allows you to build incredibly complex UI structures without nesting your HTML `divs` a million layers deep, resulting in a significantly cleaner codebase.
