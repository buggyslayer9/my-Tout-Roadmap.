# Assignment 41: Strictly Typing the Weather App

In Assignment 40, you built a Vanilla Javascript Weather application using `fetch()`.

Your task is to convert that exact same logic into flawless, strictly typed TypeScript.

## 1. Setup

Because browsers cannot run TypeScript, you must initialize a project using `Node.js` and `npm` to download the compiler.

1.  Open your terminal. Create a folder `ts-weather`.
2.  Run `npm init -y` to create a `package.json` file.
3.  Install the TypeScript compiler: `npm install typescript --save-dev`
4.  Initialize a config file: `npx tsc --init`

Create an `index.html` file precisely like you did in Chapter 40, but make your `<script src>` point to `app.js` (which we will mathematically generate from `app.ts`).

## 2. Define the Interfaces

Before you write the `fetch()`, open `app.ts` and define the strict shape of the JSON that the `wttr.in` API returns.

It returns a massive object, but we only care about the `current_condition` array, and specifically the `temp_C` string inside it.

```typescript
// Define the shape
interface WeatherData {
    current_condition: {
        temp_C: string;
    }[];
}
```

## 3. Strict Type Assertions

In Vanilla JS, you simply wrote `document.querySelector("#cityInput")`.
If that id was typo'd, it silently returned `null` and crashed later.

In TypeScript, you must explicitly assert what exact HTML Tag is coming back so the compiler knows what properties it has (like `.value` for an input box).

```typescript
const input = document.querySelector("#cityInput") as HTMLInputElement;
const btn = document.querySelector("#searchBtn") as HTMLButtonElement;
const display = document.querySelector("#weatherDisplay") as HTMLDivElement;

// Prevent TS from throwing a fit if the HTML is missing
if (!input || !btn || !display) {
    throw new Error("Missing DOM elements!");
}
```

## 4. The Typed Async Function

Rewrite your `getWeather` function.
Explicitly type the parameter `city` as a `string`.
Force the awaited JSON cast into your specific Interface!

```typescript
async function getWeather(city: string) {
    const response = await fetch(`https://wttr.in/${city}?format=j1`);
    
    // Explicitly cast the untyped JSON payload directly into your Interface Struct!
    const data = await response.json() as WeatherData;

    // TypeScript now knows EXACTLY what 'data' contains.
    // If you type data.current_cndtn[0].tmp_C, VS Code will instantly scream AT COMPILE TIME!
    display.innerHTML = `<h1>${data.current_condition[0].temp_C} °C</h1>`;
}

// Add the listener
btn.addEventListener("click", () => {
    getWeather(input.value);
});
```

## 5. Compile and Run

Run the compiler in your terminal:
```bash
npx tsc app.ts
```

If your code is flawless, this command returns absolutely nothing, but an `app.js` file appears in your folder.
Open `index.html` in your browser. The app runs exactly as it did in Chapter 40, but you wrote it with absolute structural safety guarantees.
