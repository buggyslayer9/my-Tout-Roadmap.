# Assignment 40: The Live Weather App

Your goal is to build a fully functional, vanilla Javascript Single Page Application (SPA).

You will build a Weather application that queries a live internet API for a user's typed city, reads the resulting JSON, and magically updates the DOM without reloading the page.

## The Assets

1. **`index.html`**
   - Create an `<input type="text" id="cityInput" placeholder="Enter a city">`.
   - Create a `<button id="searchBtn">Get Weather</button>`.
   - Create an empty `<div id="weatherDisplay"></div>`.
   - Link your JS script: `<script src="app.js" defer></script>`.

2. **The API**
   We will use the free (no-API-key required) geocoding API to find the latitude of a city, then chain a second fetch to an open weather API.
   To simplify, we will use an open fake weather API that just echoes text if you don't have an API key, or we can use `wttr.in/Paris?format=j1`.
   
   **Use this API endpoint:** `https://wttr.in/Dallas?format=j1`
   *(Replace 'Dallas' with whatever the user typed).*

## The `app.js` Architecture

1. **DOM Selection**
   Select the Input box, the Button, and the Display Div using `document.querySelector`.

2. **The Click Listener**
   Add a `'click'` listener to the Button. Inside the listener, prevent default form submission if necessary, and read the `value` property of the Input tag to get the city name the user typed!

3. **The Async Fetcher**
   Write an `async function getWeather(city) { ... }`.
   - Formulate the URL: `const url = "https://wttr.in/" + city + "?format=j1";`
   - Use `await fetch(url)`.
   - Parse the `await response.json()`.
   - Inspect the returned JSON payload using `console.log(data)`.
   - Find the current temperature. (Hint: Look for `data.current_condition[0].temp_C`).

4. **DOM Mutation**
   - Take the temperature string and inject it into the `weatherDisplay` div.
   - Use `innerHTML` to create a bold, massive heading:
     `weatherDisplay.innerHTML = "<h1>" + temp_C + " °C</h1>";`

## Testing the Application

1. Open `index.html` in Chrome.
2. Type "Tokyo" and click "Get Weather".
3. **DO NOT RELOAD THE PAGE.** Watch the Javascript fire the async request, block until Tokyo's weather drops from the satellite via HTTPS, and instantly swap the DOM node from nothing to the live degrees Celsius.

You have now built a modern Web 2.0 application.
