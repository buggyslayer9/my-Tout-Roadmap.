# Assignment 43: Building an Express REST API

Your task is to build a complete backend HTTP Server capable of performing standard CRUD (Create, Read, Update, Delete) operations.

Since we haven't officially integrated PostgreSQL yet, you will use an "In-Memory Database" (a simple JavaScript Array) to store the data.

## 1. Project Setup
Open your terminal.
1. `mkdir node-api`
2. `cd node-api`
3. `npm init -y` (Initializes a generic Node project).
4. `npm install express` (Downloads the massive Express C++ bindings and JS library).

Create a file named `server.js`.

## 2. The Engine Boilerplate
Inside `server.js`, import Express, instantiate the `app`, tell it to use JSON Middleware, and start the `app.listen()` loop on Port `5000`.

## 3. The "Database"
Declare a global array at the top of your file. This is our fake RAM database.
```javascript
let books = [
    { id: 1, title: "The C Programming Language", author: "Brian Kernighan" }
];
// Because arrays are 0-indexed, we use a counter for new IDs
let nextId = 2; 
```

## 4. The CRUD Routes

You must write three specific HTTP Routes.

**1. GET `/api/books`**
- Should immediately return an HTTP 200 containing the raw `books` array as JSON.

**2. GET `/api/books/:id`**
- Should extract the requested ID from `req.params.id`.
- Remember to cast it to an integer: `parseInt(req.params.id)`.
- Use the Javascript `books.find(b => b.id === requestedId)` function to locate the book in the array.
- If the book doesn't exist, return a `404 Not Found` JSON error.
- If it works, return the single book object.

**3. POST `/api/books`**
- The client will send a payload like `{"title": "Dune", "author": "Frank Herbert"}`.
- Extract these manually from `req.body`.
- Push a brand new Javascript Object into your global `books` array, manually setting its `id` to `nextId`.
- Increment `nextId++`.
- Immediately respond with a `201 Created` status code and send the newly formed book object back to the client!

## 5. Execution & Testing
Start the server:
`node server.js`

Leave it running. Open a new terminal tab. You are going to act as the React Frontend by using `curl`.

1. Read all books:
   `curl http://localhost:5000/api/books`
2. Add a new book (**Carefully copy this exact syntax**):
   `curl -X POST http://localhost:5000/api/books -H "Content-Type: application/json" -d '{"title": "1984", "author": "George Orwell"}'`
3. Read the single new book!
   `curl http://localhost:5000/api/books/2`

If you receive the glorious JSON string `{"id":2,"title":"1984","author":"George Orwell"}` on your terminal, you are a Backend Engineer.
