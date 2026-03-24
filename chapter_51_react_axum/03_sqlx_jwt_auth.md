# 41.3 Databases, Security, and Authentication

A professional backend does not just serve JSON; it securely stores user data. Since we are building our backend in Rust with Axum, we will use **SQLx** for database access, and **Argon2 / JWT** for security.

## 1. Compile-Time Checked SQL (`sqlx`)

Most languages use ORMs (Object-Relational Mappers) which can generate slow SQL and crash at runtime. Rust's `sqlx` crate acts like an ORM but writes raw SQL that is **checked against your live database during compilation**.

If you misspell a column name, your Rust code *will not compile*.

```rust
use sqlx::postgres::PgPool;
use serde::Serialize;

#[derive(Serialize)]
struct User {
    id: i32,
    username: String,
    email: String,
}

// Axum handler
async fn get_user(
    State(pool): State<PgPool>,
    Path(user_id): Path<i32>,
) -> Result<Json<User>, StatusCode> {
    
    // The query! macro checks the SQL syntax and the return types against the DB!
    let user = sqlx::query_as!(
        User,
        "SELECT id, username, email FROM users WHERE id = $1",
        user_id
    )
    .fetch_optional(&pool)
    .await
    .map_err(|_| StatusCode::INTERNAL_SERVER_ERROR)?;

    match user {
        Some(u) => Ok(Json(u)),
        None => Err(StatusCode::NOT_FOUND),
    }
}
```

## 2. Password Hashing (Argon2)

**Never store plain text passwords.** Never use MD5 or SHA256 for passwords (they are too fast and vulnerable to GPU brute-forcing).

The current industry standard is **Argon2**.

```rust
use argon2::{
    password_hash::{rand_core::OsRng, PasswordHash, PasswordHasher, PasswordVerifier, SaltString},
    Argon2,
};

fn hash_password(password: &str) -> String {
    let salt = SaltString::generate(&mut OsRng);
    let argon2 = Argon2::default();
    
    // This takes time (by design) to prevent brute forcing
    argon2.hash_password(password.as_bytes(), &salt)
          .unwrap()
          .to_string()
}

fn verify_password(hash: &str, attempted_password: &str) -> bool {
    let parsed_hash = PasswordHash::new(&hash).unwrap();
    Argon2::default()
        .verify_password(attempted_password.as_bytes(), &parsed_hash)
        .is_ok()
}
```

## 3. JWT Authentication (JSON Web Tokens)

Once a user logs in (you verify their Argon2 hash), you must give them a "ticket" so they don't have to send their password on every request. This is a **JWT**.

A JWT contains:
1. **Header:** Algorithm used.
2. **Payload:** The user's ID and token expiration time.
3. **Signature:** A cryptographic hash created using your server's secret key.

The client (React app) saves this JWT in `localStorage` or a secure cookie, and sends it in the `Authorization: Bearer <token>` header for every API request. In Axum, you use middleware to intercept this token, verify the signature, and extract the User ID before the request reaches your handler.
