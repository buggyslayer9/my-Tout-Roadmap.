# 40.3 Asynchronous Javascript: `fetch()` and APIs

In Chapter 32, we learned that opening a TCP Socket to a server and waiting for data is a **Blocking Call**. 

If Javascript used blocking network calls, the entire web browser would completely freeze every time you fetched an image. You couldn't scroll, the user's mouse would lock up, and animations would stop.

Therefore, **Javascript is strictly single-threaded and non-blocking**.
If you want to pull data from a remote REST API over the internet, you must use an asynchronous "Promise."

## 1. The Legacy Nightmare: Callbacks

Historically, developers used AJAX (Asynchronous Javascript and XML). You would tell the engine to go fetch a URL, and pass it a "Callback Function" to execute whenever the data randomly arrived 2 seconds later.

This resulted in "Callback Hell," where functions were nested inside functions infinitely deep, making error-handling mathematically impossible to read.

## 2. The Modern Savior: Async / Await

In ES8 (2017), the ECMAScript committee adopted the exact same `async/await` syntax that Rust uses!

`fetch()` is a global function built into Chrome that performs a massive HTTPS network request in the background without freezing the UI thread. It returns a `Promise`.

If you write the `await` keyword, Javascript magically pauses *only your specific function*, returns control to the browser so the user can keep scrolling, and then resumes your function instantly when the internet data arrives.

```javascript
// To use 'await', the function must be marked 'async'
const fetchUserData = async () => {
    try {
        // 1. Pause execution while Chrome makes an HTTPS GET request over the network
        const response = await fetch("https://jsonplaceholder.typicode.com/users/1");

        // 2. Check if the server returned a 404 Not Found
        if (!response.ok) {
            throw new Error(`HTTP Error: ${response.status}`);
        }

        // 3. Read the body of the TCP packet and parse its JSON into a JS Object
        const jsonBody = await response.json();

        // 4. Update the DOM with the live data!
        console.log("Pulled User from Internet:", jsonBody.name);
        
        const usernameTag = document.querySelector("#username");
        usernameTag.textContent = jsonBody.name;

    } catch (error) {
        // This catches network timeouts, CORS errors, and our 404 Error!
        console.error("The Fetch Failed:", error);
    }
};

// Start the sequence!
fetchUserData();
```

## The Power of the Frontend
If you combine Chapter 40.2 (DOM Events) with Chapter 40.3 (Networking), you instantly realize the fundamental architecture of every modern Reactive web application (React, Vue, Twitter).

1. A user clicks a "Load Tweets" `<button>`.
2. The `addEventListener` triggers an `async` function.
3. The function `awaits` a `fetch()` call to a Python Backend REST API over HTTPS.
4. The JSON array of Tweets arrives.
5. A `for` loop executes `document.createElement("div")` for every tweet, and `appendChild` injects them into the UI.

This prevents the browser from having to reload the entire web page to see new data. The page is technically a static C++ UI tree, and it magically repaints subsets of the screen!
