# 51.4 Validation and Error Handling

It is easy to make an API that works for the happy path.

It is much harder, and much more professional, to make an API that behaves well when users send:

- missing fields
- invalid JSON
- wrong IDs
- unexpected types
- impossible state transitions

Validation and error handling are part of backend design, not optional cleanup.

## Why Validation Matters

Imagine this route:

```javascript
app.post('/tasks', (req, res) => {
  const task = {
    title: req.body.title,
    done: req.body.done
  };

  // pretend we save it
  res.status(201).json(task);
});
```

What if:

- `title` is missing?
- `title` is a number?
- `done` is `"yes"` instead of `true`?

Without validation, bad data enters your system and creates bugs later.

## Validate At The Boundary

A good rule:

**Validate input as soon as it enters your backend.**

That usually means:

- request body
- query parameters
- route parameters
- headers when relevant

## A Simple Manual Example

```javascript
app.post('/tasks', (req, res) => {
  const { title, done } = req.body;

  if (typeof title !== 'string' || title.trim() === '') {
    return res.status(400).json({ error: 'title must be a non-empty string' });
  }

  if (done !== undefined && typeof done !== 'boolean') {
    return res.status(400).json({ error: 'done must be a boolean when provided' });
  }

  const task = {
    id: Date.now(),
    title: title.trim(),
    done: done ?? false
  };

  res.status(201).json(task);
});
```

This is already much better because the API has rules instead of blind trust.

## Status Codes Matter

Use HTTP status codes intentionally:

- `200 OK` for successful reads or updates
- `201 Created` for successful creation
- `400 Bad Request` for malformed or invalid input
- `404 Not Found` when the resource does not exist
- `500 Internal Server Error` for unexpected backend failures

Clear status codes make APIs easier to debug and easier to consume.

## Centralized Error Handling

As your app grows, repeating `try/catch` and response logic everywhere becomes messy.

Express supports centralized error middleware:

```javascript
app.use((err, req, res, next) => {
  console.error(err);
  res.status(500).json({ error: 'internal server error' });
});
```

This gives your app one place for fallback error formatting.

## Good Error Response Design

Error responses should be:

- clear
- predictable
- not overly detailed about internal secrets

Example:

```json
{
  "error": "title must be a non-empty string"
}
```

For bigger apps, teams often standardize error shapes so frontend code can handle them consistently.

## Common Mistakes

- trusting frontend validation only
- returning `200` for everything
- leaking stack traces to clients
- mixing validation rules across many files with no structure
- not checking route parameters like IDs

## Learning Check

- Can I explain why validation belongs at the API boundary?
- Can I choose the right status code for a bad request versus a missing record?
- Can I describe the difference between expected user errors and unexpected server errors?

## Recommended Follow-Up

Pick one backend route and improve it by adding:

- input validation
- correct status codes
- a clearer error response

That one habit will noticeably improve every backend you build after this.
