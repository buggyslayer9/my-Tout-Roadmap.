# 45.4 Authentication, Sessions, and Tokens

Most real web apps need to answer one question:

**Who is making this request?**

Authentication is how we verify identity. Authorization is how we decide what that identity is allowed to do.

This lesson focuses on the first half: proving who the user is.

## The Basic Login Flow

At a high level:

1. The user sends credentials such as email and password.
2. The server verifies them.
3. The server creates some proof that the user is authenticated.
4. Later requests include that proof.

The two most common ways to store that proof are:

- sessions
- tokens

## Session-Based Authentication

In a session-based system:

1. the user logs in
2. the server creates a session record
3. the server sends a session ID cookie
4. the browser sends that cookie on later requests

The important detail is that the session data usually lives on the server.

### Example Mental Model

```text
Browser -> POST /login -> Server
Server verifies password
Server creates session: session_id = abc123
Server stores session_id -> user_id mapping
Server sends cookie: session_id=abc123
Browser sends cookie on later requests
```

Benefits:

- easy to revoke centrally
- straightforward mental model
- common in traditional web applications

Tradeoffs:

- server must manage session storage
- horizontal scaling needs shared session storage if you run multiple servers

## Token-Based Authentication

In a token-based system:

1. the user logs in
2. the server creates a signed token
3. the client stores the token
4. the client sends the token on later requests

The most common example is a JWT, though not every project needs JWT specifically.

Benefits:

- easy to send across APIs and services
- common in SPAs and mobile apps
- can reduce server-side session storage

Tradeoffs:

- revocation can be harder
- bad token handling can create security problems
- teams often choose JWT because it is popular, not because it is necessary

## Cookies vs Local Storage

This is where many learners get confused.

### Cookies

Cookies are useful because browsers can send them automatically with requests.

Good secure habits:

- `HttpOnly`
- `Secure`
- `SameSite=Lax` or `SameSite=Strict`

These settings reduce common attacks.

### Local Storage

Local storage is easy to use in frontend code, but it is readable by JavaScript running on the page.

That means XSS becomes much more dangerous if your token is stored there.

For many web apps, **secure cookies are the safer default**.

## Password Handling Rules

Never:

- store plain-text passwords
- store reversible encrypted passwords
- log passwords

Do:

- hash passwords with a strong password hashing algorithm
- use salts through established libraries
- compare credentials on the server

## Authentication vs Authorization

These are not the same thing.

- **Authentication**: Are you really Ayman?
- **Authorization**: Is Ayman allowed to delete this project?

You need both in real systems.

## A Practical Beginner Recommendation

For a beginner-friendly full-stack app:

- use server-side validation
- use secure cookies
- start with session-based authentication
- add roles later when the app truly needs them

You do not need the most fashionable architecture to build a good system.

You need a system you understand.

## Common Mistakes

- trusting only frontend checks
- storing passwords badly
- confusing login state with permission checks
- choosing JWT before understanding the tradeoffs
- forgetting logout and token/session expiration

## Learning Check

Make sure you can answer these:

- What problem does authentication solve?
- What is the difference between a session and a token?
- Why are secure cookies often safer than local storage?
- What is the difference between authentication and authorization?

## Recommended Follow-Up

After this lesson, sketch a login flow for one of your future backend projects:

- login request
- stored auth state
- protected route
- logout flow

That diagram will help a lot when you start building a real backend.
