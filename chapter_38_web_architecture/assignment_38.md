# Assignment 38: The `curl` Audit

Before we ever touch HTML or JavaScript, you must prove you can speak the raw HTTP protocol using nothing but the Terminal.

You will use the `curl` command-line utility to manually forge HTTP Requests.

## Task 1: Fetching the Raw Body
Use curl to send a standard HTTP `GET` request to `example.com`.
```bash
$ curl http://example.com
```
You will notice the output is pure, unrendered HTML tags. Your terminal just acted exactly like Chrome, minus the rendering engine!

## Task 2: Inspecting the Headers
Your browser hides all the complex HTTP Headers from you.
Use the `-I` flag to tell `curl` only to fetch the Headers, not the Body:
```bash
$ curl -I https://github.com
```

**Answer these questions:**
1. What was the exact 3-digit Status Code returned?
2. What software is running their servers? (Look for `Server: `).
3. Do they use strict security? (Look for `Strict-Transport-Security`).

## Task 3: Forging a POST Request
You can manually submit data exactly as if you were submitting a web form.
We will use a public testing API at `jsonplaceholder.typicode.com`.

Use the `-X` flag to change the Verb from GET to POST.
Use the `-H` flag to set the `Content-Type` Header so the server knows it's JSON.
Use the `-d` flag to inject the raw data payload.

```bash
$ curl -X POST https://jsonplaceholder.typicode.com/posts \
  -H "Content-Type: application/json" \
  -d '{"title": "BugSlayer", "body": "I have learned the HTTP Protocol.", "userId": 1}'
```

The server should instantly respond with `{ "id": 101 }` and a `201 Created` status code, confirming it processed your handmade HTTP packet.
