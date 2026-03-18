# Assignment 50: The Grand Capstone

This is your final assignment.

Your objective is to physically build, integrate, and deploy the `BugSlayer Chat` architecture defined in Chapters 50.1, 50.2, and 50.3.

**There is no starter code. You are architecting from scratch.**

## 1. The Monorepo Layout

You must organize your code into a strict Monorepo folder hierarchy.
```text
/bugslayer_chat_monorepo
  /api              (The Rust Axum Backend)
  /mobile           (The Flutter App)
  /database         (schema.sql and init scripts)
  docker-compose.yml 
```

## 2. Docker Compose Orchestration

You must write a master `docker-compose.yml` file in the root directory.
This single file must command Docker to instantly spin up **three** mathematically isolated containers, network them together automatically, and boot the entire platform from a single command.

```yaml
version: '3.8'

services:
  db:
    image: postgres:15-alpine
    environment:
      POSTGRES_USER: admin
      POSTGRES_PASSWORD: correcthorsebatterystaple
      POSTGRES_DB: bugslayer_chat
    ports:
      - "5432:5432"

  redis:
    image: redis:7-alpine
    ports:
      - "6379:6379"

  api:
    build: 
      context: ./api
      dockerfile: Dockerfile
    # The API container maps to localhost:3000!
    ports:
      - "3000:3000"
    # The API is literally forbidden from booting until the Database signals it is online!
    depends_on:
      - db
      - redis
```

## 3. The Execution

1. Write your Rust Axum logic inside `/api`. Assure it connects cleanly to `postgres://admin:correcthorsebatterystaple@db/bugslayer_chat`.
2. Write your Flutter logic inside `/mobile`.
3. In your terminal, run `docker-compose up --build`.
4. Watch Docker download Alpine Linux, spin up Redis, spin up Postgres, compile your Rust application inside Debian, and bind Port 3000 to your host machine.
5. In your mobile folder, launch `flutter run -d chrome` (or launch the iOS simulator).

Type "Hello Systems World!" into the Flutter input box.
Watch it traverse the Dart isolate, exit the iPhone over the TCP protocol, hit the Linux `epoll` socket on Port 3000, trigger the Rust `axum` extractor, serialize the JSON via `serde`, lock the `Mutex`, broadcast the text out to the 500 connected WebSocket channels, insert the history into PostgreSQL via `sqlx`, and push the row into the Redis cache exactly 0.004 seconds later.

You understand the entire stack.
Congratulations on completing the 50-Chapter Comprehensive Developer Curriculum.
You are a Systems Engineer.
