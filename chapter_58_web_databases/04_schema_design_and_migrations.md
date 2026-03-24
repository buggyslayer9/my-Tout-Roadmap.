# 54.4 Schema Design and Migrations

A database is not just a place to store rows.

It is part of your application's structure.

If your schema is messy, your app logic becomes messy too.

This lesson introduces two practical ideas:

- schema design
- migrations

## Schema Design

A schema is the shape of your data:

- tables
- columns
- relationships
- constraints

Good schema design helps you:

- avoid duplicated data
- enforce important rules
- query data more clearly
- change the app more safely later

## A Small Example

Suppose you are building a task app.

A simple schema might look like:

```sql
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    email TEXT NOT NULL UNIQUE,
    password_hash TEXT NOT NULL
);

CREATE TABLE tasks (
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL REFERENCES users(id),
    title TEXT NOT NULL,
    description TEXT,
    is_done BOOLEAN NOT NULL DEFAULT FALSE,
    created_at TIMESTAMP NOT NULL DEFAULT NOW()
);
```

This already teaches good habits:

- each table has a primary key
- `tasks.user_id` connects a task to a user
- required fields are marked `NOT NULL`
- defaults reduce boilerplate

## Constraints Are Your Friends

Application code should validate data, but the database should also protect itself.

Examples:

- `PRIMARY KEY`
- `FOREIGN KEY`
- `UNIQUE`
- `NOT NULL`
- `CHECK`

Without constraints, bad data can still slip in through scripts, admin tools, or future code changes.

## Normalization, In Plain English

Normalization means organizing data so that one fact is stored in one sensible place.

Bad design:

```text
tasks table stores user_email on every row
```

Better design:

```text
users table stores the email once
tasks table references the user by user_id
```

This reduces inconsistency and makes updates safer.

## What Is A Migration?

A migration is a tracked database change.

Examples:

- create a new table
- add a column
- add an index
- rename or drop something carefully

Instead of manually editing the database in random ways, migrations give your team a repeatable history of schema changes.

## Why Migrations Matter

Without migrations:

- developers drift out of sync
- local, staging, and production databases differ
- changes become hard to reproduce

With migrations:

- schema changes are versioned
- environments stay more consistent
- rollouts are safer

## Migration Example

Imagine you want to add a priority field:

```sql
ALTER TABLE tasks
ADD COLUMN priority INTEGER NOT NULL DEFAULT 1;
```

That statement should live in a migration file, not only in your memory or terminal history.

## Design Questions To Ask

Before adding a table or column, ask:

- What real-world thing does this table represent?
- Which fields are required?
- What should be unique?
- What relationships exist?
- What happens when related data is deleted?

These questions prevent many future bugs.

## Common Mistakes

- storing repeated data in many places
- skipping constraints because validation exists in the app
- editing production schema manually without tracked migrations
- naming tables and columns inconsistently
- adding columns without thinking about defaults or old rows

## Learning Check

- Can I explain why schema design affects application code quality?
- Can I describe what a migration is and why teams use it?
- Can I identify at least three useful database constraints?

## Recommended Follow-Up

Design a schema for one of your milestone projects:

- users
- projects
- tasks
- comments

Then write two migrations:

1. initial schema
2. one later improvement

That is excellent practice before building a real full-stack app.
