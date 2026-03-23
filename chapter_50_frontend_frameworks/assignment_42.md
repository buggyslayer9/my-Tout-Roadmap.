# Assignment 42: Your First React Component

Your task is to mathematically define a User Interface that counts how many times a button is clicked, using React hooks.

You will do this inside a modern Next.js project.

## 1. Scaffold the Project

Open your terminal in your projects directory.
Use the legendary `create-next-app` initialization script to automatically download all the Webpack bundlers, the vast React codebase, and the TypeScript configuration.

```bash
npx create-next-app@latest bugslayer-react
```

- Would you like to use TypeScript? **Yes**
- Would you like to use ESLint? **Yes**
- Would you like to use Tailwind CSS? **No** (We write pure CSS for now).
- Would you like to use `<src>/` directory? **Yes**
- Would you like to use App Router? **Yes**

Run `cd bugslayer-react` and start the massive Node.js Development Server:
```bash
npm run dev
```
Open `http://localhost:3000` in your Chrome browser. Your first Next.js site is live!

## 2. Destroy the Boilerplate

Open the core UI file: `src/app/page.tsx`.
Delete everything inside the `export default function Home()` function.

Return an empty `<main></main>`.

## 3. Creating the State Tracker

In React, you cannot use a vanilla variable (`let count = 0;`). If you do, React doesn't know you updated it, so it will never redraw the screen!

You must use a **Hook** to hook into React's internal C++ lifecycle engine.

At the very top of `page.tsx`, import `useState`. You must also add the literal string `"use client";` at line 1 to tell Next.js this file requires browser interactivity.

```tsx
"use client";

import { useState } from 'react';

export default function Home() {
    // 1. Hooking into State!
    // 'count' is the current value. 'setCount' is the specific function you MUST call to change it.
    const [count, setCount] = useState(0);

    return (
        <main style={{ padding: '50px' }}>
            <h1>The BugSlayer Counter</h1>
            <p>You clicked {count} times.</p>
            
            <button 
                // 2. The pure Declarative Event Listener!
                onClick={() => {
                   setCount(count + 1); 
                }}
            >
                Increment Counter
            </button>
        </main>
    );
}
```

Save the file.
Notice that you do NOT need to refresh the Chrome window. Next.js instantly injects the new compiled TSX payload into your live browser tab (Hot Module Replacement).

Click the button. The number magically goes up.
The Virtual DOM is performing a surgical, microsecond C++ diff to edit the isolated text node holding the literal '0', swapping it to '1', without reloading the rest of the HTML.
