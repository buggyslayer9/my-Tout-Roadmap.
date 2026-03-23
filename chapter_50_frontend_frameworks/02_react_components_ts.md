# 42.2 Writing React Components (TSX)

React allows you to split your monolithic HTML into hundreds of tiny, reusable, modular Lego blocks called **Components**.

A Component is literally just a plain Javascript Function that returns HTML.

Wait, returning HTML from a JS function? That's historically illegal syntax.
React invented an extension to Javascript called **JSX (Javascript XML)**.
Because we use TypeScript, we call the file extension `.tsx`.

## The Anatomy of a Component

Here is a perfectly valid React TSX Component representing a Button:

```tsx
// MyButton.tsx
// 1. Defining the strict props (Parameters) this component accepts!
interface Props {
  text: string;
  isDanger?: boolean; // Optional parameter
}

// 2. The Component is just a function that takes Props as an argument
export function MyButton({ text, isDanger }: Props) {
  
  // 3. We use JSX to return raw HTML!
  // Notice we use raw Javascript {{ curly braces }} to inject logic directly into the HTML!
  return (
    <button 
        style={{ backgroundColor: isDanger ? 'red' : 'blue' }} 
        onClick={() => console.log(text + " was clicked!")}
    >
        {text}
    </button>
  );
}
```

Notice the absolute brilliance here: 
1. The HTML structure (`<button>`)
2. The CSS Styling (`backgroundColor`)
3. The Javascript Event Listener (`onClick`)
...are all hyper-localized into a single, cohesive 10-line file. These three things are no longer spread across three separate folders like the 2005-era web.

## Composition: Building the Lego Castle

Once you define `MyButton`, you can import it into other files and use it exactly as if it was a native HTML tag built into Chrome!

```tsx
// App.tsx
import { MyButton } from './MyButton';

export function App() {
  return (
    <main>
      <h1>Control Panel</h1>
      
      {/* We simply render the component multiple times passing different strictly typed Props! */}
      <MyButton text="Save Data" />
      <MyButton text="Delete Account" isDanger={true} />
    </main>
  );
}
```

If you misspell the `text=` prop, or pass `text={8}` instead of a string, the TSX Compiler will throw a fatal error before you even run the code. You have married the bulletproof safety of TypeScript with the hyper-modularity of React UI components.
