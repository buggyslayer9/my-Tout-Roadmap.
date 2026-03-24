# 48.4 Modules and Code Organization

As soon as JavaScript projects become slightly bigger, organization starts to matter more than syntax tricks.

This is where **modules** become important.

Modules help you split code into smaller, clearer pieces.

## Why Modules Matter

Without modules, code often becomes:

- one large file
- many unrelated functions together
- repeated logic
- hard-to-track dependencies

Modules make code easier to:

- read
- test
- extend
- reason about

## A Simple Example

Instead of placing everything in one file:

```javascript
function addTask() {}
function renderTasks() {}
function saveTasks() {}
function loadTasks() {}
```

You might separate responsibilities:

```text
js/
├── app.js
├── storage.js
├── tasks.js
└── ui.js
```

This structure already teaches better architecture.

## Import and Export

In modern JavaScript, modules usually use:

- `export`
- `import`

Example:

```javascript
// tasks.js
export function addTask(list, title) {
  return [...list, { title, done: false }];
}
```

```javascript
// app.js
import { addTask } from './tasks.js';
```

This makes dependencies explicit instead of hidden.

## A Good Rule

Group code by responsibility, not by accident.

Examples:

- UI updates
- storage helpers
- business logic
- API calls

That is much more maintainable than random splitting.

## Learning Check

- Can I explain why modules help project organization?
- Can I write a small `export` and `import` example?
- Can I split one JavaScript project into meaningful files?

## Recommended Follow-Up

Take one JavaScript project and separate it into at least three modules with clear responsibilities.
