# 39.1 Modern Frontend — React

## Why React?

React is the most popular frontend framework. It uses **components** and a **virtual DOM** for efficient updates.

```bash
# Create a React project
npx create-react-app my-app
cd my-app
npm start
```

## React Component

```jsx
import { useState, useEffect } from 'react';

function TaskManager() {
    const [tasks, setTasks] = useState([]);
    const [input, setInput] = useState('');

    const addTask = () => {
        if (!input.trim()) return;
        setTasks([...tasks, { id: Date.now(), text: input, done: false }]);
        setInput('');
    };

    const toggleTask = (id) => {
        setTasks(tasks.map(t => t.id === id ? { ...t, done: !t.done } : t));
    };

    return (
        <div className="app">
            <h1>Task Manager</h1>
            <div className="input-group">
                <input value={input} onChange={e => setInput(e.target.value)}
                       onKeyDown={e => e.key === 'Enter' && addTask()}
                       placeholder="Add a task..." />
                <button onClick={addTask}>Add</button>
            </div>
            <ul>
                {tasks.map(task => (
                    <li key={task.id}
                        onClick={() => toggleTask(task.id)}
                        style={{ textDecoration: task.done ? 'line-through' : 'none' }}>
                        {task.text}
                    </li>
                ))}
            </ul>
        </div>
    );
}

export default TaskManager;
```

---

# 40.1 Backend with Rust (Axum)

```toml
# Cargo.toml
[dependencies]
axum = "0.7"
tokio = { version = "1", features = ["full"] }
serde = { version = "1", features = ["derive"] }
serde_json = "1"
tower-http = { version = "0.5", features = ["cors"] }
```

```rust
use axum::{routing::{get, post}, Router, Json, extract::State};
use serde::{Serialize, Deserialize};
use std::sync::{Arc, Mutex};

#[derive(Serialize, Deserialize, Clone)]
struct Task {
    id: u32,
    title: String,
    completed: bool,
}

type AppState = Arc<Mutex<Vec<Task>>>;

async fn get_tasks(State(state): State<AppState>) -> Json<Vec<Task>> {
    let tasks = state.lock().unwrap();
    Json(tasks.clone())
}

async fn add_task(State(state): State<AppState>, Json(task): Json<Task>) -> Json<Task> {
    let mut tasks = state.lock().unwrap();
    tasks.push(task.clone());
    Json(task)
}

#[tokio::main]
async fn main() {
    let state: AppState = Arc::new(Mutex::new(vec![]));

    let app = Router::new()
        .route("/api/tasks", get(get_tasks).post(add_task))
        .with_state(state);

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    println!("Server running on http://localhost:3000");
    axum::serve(listener, app).await.unwrap();
}
```

## Assignment 39-40

**Task**: Build a **full-stack task manager**:
1. Rust backend (Axum) with REST API: GET/POST/PUT/DELETE tasks
2. React frontend that consumes the API
3. Add SQLite database using `rusqlite` or `sqlx` crate
4. CORS configuration for cross-origin requests

**Sources**:
- [React docs](https://react.dev/)
- [Axum docs](https://docs.rs/axum/latest/axum/)
- [SQLx (async Rust SQL)](https://github.com/launchbadge/sqlx)

---

## 📚 Resources for This Chapter

### React
- [**React Official Docs**](https://react.dev/) — Best starting point with interactive examples ⭐
- [**"The Road to React"**](https://www.roadtoreact.com/) — Free project-based book
- [**Epic React (Kent C. Dodds)**](https://epicreact.dev/) — Advanced patterns
- [**Scrimba React Course**](https://scrimba.com/learn/learnreact) — Interactive browser editor

### Rust Backend
- [**Axum Docs**](https://docs.rs/axum/latest/axum/) — Official API reference
- [**"Zero to Production in Rust"**](https://www.zero2prod.com/) — Build a production API from scratch ⭐
- [**Tokio Tutorial**](https://tokio.rs/tokio/tutorial) — Async runtime that powers Axum
- [**SQLx**](https://github.com/launchbadge/sqlx) — Compile-time checked SQL queries
- [**Shuttle.dev**](https://www.shuttle.dev/) — Deploy Rust backends for free

