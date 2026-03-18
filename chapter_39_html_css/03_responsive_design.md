# 39.3 Responsive Design: Mobile First

Writing a desktop website using CSS Grid is easy. But what happens when the user views your site on a 300px wide iPhone screen? If you hardcode a `250px` sidebar like we did in the last lesson, the content will be crushed into a 50px sliver and become unreadable.

To fix this, we use **Media Queries**.

## The Mobile-First Principle
Historically, developers built the Desktop site first, and then added CSS to try and squeeze it down onto mobile. This always resulted in bloated, awful CSS.

Modern web design strictly dictates **Mobile-First Development**.

1. You write the default CSS targeting the absolute smallest iPhone screen. (No sidebars, everything stacks in a single column using Flexbox).
2. You add a **Media Query breakpoint** to check if the screen is large enough. If it is, *then* you add the Sidebar.

```css
/* 1. Mobile First Default */
.dashboard {
    display: flex;
    flex-direction: column; /* Stack everything vertically */
}
.sidebar {
    /* Hide the sidebar on mobile behind a hamburger menu */
    display: none; 
}

/* 2. Media Query (If the screen is over 768 pixels wide, it's a Tablet/Desktop!) */
@media (min-width: 768px) {
    .dashboard {
        display: grid;
        grid-template-columns: 250px 1fr; /* Add the 2-column Desktop grid */
    }
    .sidebar {
        display: block; /* Unhide the sidebar */
    }
}
```

## `rem` vs `px`

When sizing fonts or margins, developers often use Pixels (`font-size: 16px;`).
This is terrible for accessibility. If a visually impaired user tells their Chrome browser to globally scale all text up by 200%, the browser literally cannot scale hardcoded pixels. The text stays tiny.

As a professional, you must use **rems** (Root EM). 
`1rem` is physically equal to whatever the user set their root font size to (usually 16px).

```css
p {
    /* If the user is visually impaired, this automatically scales to 32px! */
    font-size: 1rem; 
    margin-bottom: 2rem; /* Margins scale with the font too */
}

h1 {
    font-size: 3rem; /* 3 times the default size */
}
```

## Viewport Units
When building full-screen hero landing pages, percentages (`height: 100%`) often fail because they require their parent HTML element to also be 100% height, all the way up to the `<body tag>`.

Instead, use exact Viewport Units:
*   `100vh`: Take up 100% of the literal physical **V**iewport **H**eight of the monitor.
*   `100vw`: Take up 100% of the literal physical **V**iewport **W**idth of the monitor.

These three concepts (Media Queries, Rems, and Viewport units) are all you need to build any layout on any device in the world.
