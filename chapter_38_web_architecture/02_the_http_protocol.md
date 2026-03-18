# 38.2 The HTTP Protocol: Verbs, Headers, and Status Codes

HTTP (HyperText Transfer Protocol) is the language spoken by the Web. It is just structured, human-readable text sent over a TCP connection.

## The Anatomy of an HTTP Request
When your browser visits `/profile`, it sends a block of text that looks exactly like this to the server:

```http
GET /profile HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) Chrome/114.0.0.0
Accept: text/html
Authorization: Bearer my_secret_token_123

```
*(Note the absolutely required blank line at the very end. That tells the server the headers are finished!)*

### 1. The HTTP Verbs (Methods)
The first word of the Request dictates the "Action".
*   `GET`: Fetch data. (Opening a webpage, loading an image). **Never** use GET to modify a database.
*   `POST`: Submit new data. (Submitting a login form, creating a new user account). The data is hidden inside the HTTP Body.
*   `PUT`: Update/Replace an entire existing resource.
*   `PATCH`: Update a small part of an existing resource.
*   `DELETE`: Delete a resource.

### 2. Headers
Headers are key-value pairs (like a Dictionary/HashMap) providing metadata about the request.
*   `Host`: Which specific domain are you aiming for? (One server might host 50 different websites).
*   `User-Agent`: What browser are you using? (Useful for Analytics or sending mobile vs desktop layouts).
*   `Content-Type`: If you are POST-ing data, what format is it in? (`application/json` or `multipart/form-data` for file uploads).

---

## The Anatomy of an HTTP Response
The backend server computes the request and replies with this text:

```http
HTTP/1.1 200 OK
Date: Mon, 27 Jul 2024 12:28:53 GMT
Content-Type: application/json
Content-Length: 42

{"username": "bugslayer", "role": "admin"}
```

### 1. Status Codes
The 3-digit number on the first line is the most important part of the response. It tells the client instantly if the request succeeded or failed.

You must memorize the 5 families of Status Codes:
*   **1xx (Informational):** "Hold on, I'm processing." (Rarely used directly by developers).
*   **2xx (Success):** "Everything went perfectly."
    *   `200 OK`: Standard success.
    *   `201 Created`: Good job, I successfully inserted your POST data into the database.
*   **3xx (Redirection):** "Go look somewhere else."
    *   `301 Moved Permanently`: This URL has changed forever.
    *   `302 Found`: Temporary redirect (used heavily after logging in successfully to redirect you to the dashboard).
*   **4xx (Client Error):** "YOU messed up."
    *   `400 Bad Request`: You forgot a required JSON field.
    *   `401 Unauthorized`: You forgot your API Token or Password.
    *   `403 Forbidden`: You are logged in, but you aren't an Admin, so you can't view this.
    *   `404 Not Found`: The URL doesn't exist.
*   **5xx (Server Error):** "WE messed up."
    *   `500 Internal Server Error`: Your backend unhandled exception / segmentation fault just crashed the thread.
    *   `503 Service Unavailable`: The database is offline or the server is overloaded.

### 2. The Body
Separated by a blank line, the Body contains the actual payload. For APIs, this is almost universally a JSON string. For websites, this is a massive HTML string.
