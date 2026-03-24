# 43.2 The Express Framework

Node.js comes with a built-in module for spawning an HTTP web server called `http`.
However, the raw `http` module operates at an incredibly low level (manipulating raw byte streams and manual header parsing).

To build heavily trafficked, professional APIs, 95% of Node developers use an abstract framework known as **Express.js**.

## Routing

The core concept of a backend developer is mapping specific URLs to specific blocks of logic. This is called **Routing**.

If a client sends an `HTTP GET` request to `/users`, you must route them to the database function that queries all users.

```javascript
// 1. Import the Express framework
const express = require('express');

// 2. Instantiate the application
const app = express();

// 3. Define a Route!
// When Chrome sends a GET request to http://localhost:8080/dashboard
app.get('/dashboard', (req, res) => {
    // req = The Request Object (Everything the client sent us)
    // res = The Response Object (The tool we use to shoot data back down the TCP socket)
    
    // We send a massive HTTP 200 OK + raw HTML text instantly!
    res.send("<h1>Welcome to your Dashboard</h1>");
});

// 4. Start the libuv Event Loop!
app.listen(8080, () => {
    console.log("Server listening on port 8080...");
});
```

## `req` and `res` (Request and Response)

You will spend your entire backend career manipulating these two objects.

### The Request (`req`)
The `req` object exposes all the metadata from the raw TCP packet (Chapter 38).
*   `req.ip`: The IP address of the hacker.
*   `req.headers`: The raw dictionary of HTTP headers (e.g., `req.headers['authorization']`).
*   `req.params`: Variables hiding identically inside the URL path itself!

Let's say you build a route to view a specific user's public profile:
`http://api.com/users/99`

You do not write 9,000 routes for 9,000 users. You write one dynamic route using a colon `:`!
```javascript
app.get('/users/:userID', (req, res) => {
    // Express magically extracts the '99' and hands it to you!
    const targetID = req.params.userID;
    
    // Now you SELECT * FROM users WHERE id = targetID...
    
    res.send(`Rendering profile page for User ID: ${targetID}`);
});
```

### The Response (`res`)
The `res` object controls exactly how the TCP socket closes.
*   `res.status(404)`: Sets the HTTP status code explicitly.
*   `res.json()`: The most powerful function. It takes a raw Javascript object, instantly stringifies it into JSON format, explicitly sets the `Content-Type: application/json` header, and fires it down the TCP socket ending the transaction perfectly!

```javascript
app.get('/api/health', (req, res) => {
    // You just wrote a professional standard REST endpoint!
    res.status(200).json({ status: "Online", uptime: 99.99 });
});
```
