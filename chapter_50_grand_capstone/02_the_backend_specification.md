# 50.2 The Backend Specification

Your Rust Axum server is the brain of the operation. It must serve standard REST HTTP endpoints for user registration, and upgrade standard TCP connections into dual-channel WebSockets for real-time messaging.

## The Database Schema (PostgreSQL)

You must write a raw `schema.sql` migration script containing:

```sql
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE channels (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) UNIQUE NOT NULL
);

CREATE TABLE messages (
    id SERIAL PRIMARY KEY,
    channel_id INTEGER REFERENCES channels(id),
    user_id INTEGER REFERENCES users(id),
    content TEXT NOT NULL,
    sent_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Index the channel_id for hyper-fast message retrieval!
CREATE INDEX idx_messages_channel ON messages(channel_id);
```

## The Rust Extracts and Axum Architecture

**1. Authentication REST Endpoints (`POST /api/login`)**
You must extract JSON containing a username/password, manually perform a `bcrypt` hash validation against the PostgreSQL database using `sqlx`, and generate a secure **JWT (JSON Web Token)** to return to the client.

**2. The In-Memory Channel Hub (`Arc<Mutex<HashMap>>`)**
To broadcast a message to 500 connected users instantly, your Rust state must contain an `Arc<Mutex<HashMap<ChannelId, Vec<WebSocketSender>>>>`. 
When a WebSocket hits `/ws/channels/:id`, you inject their specific `Sender` stream into the HashMap.

**3. The Redis Cache**
When a user opens the "General" channel, do NOT query Postgres to fetch the last 50 messages. Query the Redis cache `GET latest_messages:general`. 
If someone sends a *new* message, the Axum server must simultaneously:
1. `INSERT INTO messages` (Postgres)
2. `LPUSH latest_messages:general` (Redis)
3. Iterate the `Arc<Mutex>` Vector and broadcast the string across all 500 active `WebSocketSender` pipes on all 32 CPU cores.

If you achieve this flawlessly, your Rust server is mathematically capable of supporting roughly 50,000 simultaneous users on a standard $20/month DigitalOcean VPS without crashing.
