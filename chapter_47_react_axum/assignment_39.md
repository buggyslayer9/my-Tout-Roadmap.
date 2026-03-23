# Assignment 39

## Task

Build a **full-stack task manager** with React frontend and Rust/Axum backend:

### Part 1: Rust Backend with Axum

Create a REST API with the following endpoints:

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/tasks` | Get all tasks |
| POST | `/api/tasks` | Create a new task |
| PUT | `/api/tasks/:id` | Update a task |
| DELETE | `/api/tasks/:id` | Delete a task |

1. Create a new Rust project:
   ```bash
   cargo new task-api
   cd task-api
   ```

2. Add dependencies to `Cargo.toml`:
   ```toml
   [dependencies]
   axum = "0.7"
   tokio = { version = "1", features = ["full"] }
   serde = { version = "1", features = ["derive"] }
   serde_json = "1"
   tower-http = { version = "0.5", features = ["cors"] }
   uuid = { version = "1", features = ["v4"] }
   ```

3. Implement the API with:
   - In-memory state (or SQLite if ambitious)
   - CORS for frontend-backend communication
   - Proper error handling

### Part 2: React Frontend

Create a React application:

1. Initialize React:
   ```bash
   npx create-react-app task-client
   cd task-client
   npm install axios
   ```

2. Implement features:
   - Display all tasks in a list
   - Add new task (input + button)
   - Toggle task completion (click to toggle)
   - Delete task (button)
   - Loading and error states

### Part 3: Connect Frontend to Backend (Bonus)

- Make API calls from React to Axum backend
- Handle CORS properly on backend

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **React** - Components, useState, useEffect hooks
2. **Axum** - Router, handlers, extractors
3. **REST API** - HTTP methods, JSON
4. **CORS** - Cross-origin resource sharing
5. **Axios** - HTTP client for frontend
6. **useEffect** - Side effects and data fetching

---

## Sources

- [React Official Docs](https://react.dev/)
- [Axum Documentation](https://docs.rs/axum/latest/axum/)
- ["Zero to Production in Rust"](https://www.zero2prod.com/)

---

## Hints

- Use `serde` for JSON serialization/deserialization
- Use `State<AppState>` extractor for shared state
- Add CORS with `tower_http::cors::CorsLayer`
- Use `useEffect` to fetch tasks on component mount
- Use `axios` or `fetch` for HTTP requests

## API Response Format

```json
// GET /api/tasks
[
  {
    "id": "uuid-string",
    "title": "Buy groceries",
    "completed": false,
    "created_at": "2025-01-01T12:00:00Z"
  }
]

// POST /api/tasks
{
  "title": "New task"
}
```

## Example Output

```
┌────────────────────────────────────────────┐
│  Task Manager                    [+]       │
├────────────────────────────────────────────┤
│  ┌────────────────────────────────────┐  │
│  │ ☐ Buy groceries                  🗑 │  │
│  └────────────────────────────────────┘  │
│  ┌────────────────────────────────────┐  │
│  │ ☑ Finish assignment              🗑 │  │
│  └────────────────────────────────────┘  │
│                                            │
│  [________________] [Add Task]             │
└────────────────────────────────────────────┘
```
