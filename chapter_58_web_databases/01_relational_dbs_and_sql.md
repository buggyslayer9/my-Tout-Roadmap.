# 45.1 Relational Databases and Persistence

In Chapters 43 and 44, you built robust Backend APIs. However, the exact moment you shut down the `node` or `cargo` process, your `books` vector was obliterated from RAM.

A backend server without persistent storage is severely limited. You need the ability to save gigabytes of user data securely to a physical Hard Drive or NVMe SSD.

You could write raw JSON strings to a `.txt` file using the `fs.writeFile()` POSIX system call, but if 10,000 users try to register simultaneously, the hard drive's File Locks will collide, destroying the text file.

## The Relational Database Management System (RDBMS)

To solve safe, hyper-concurrent disk access, computer scientists invented the **RDBMS**. 
The most famous, bulletproof open-source database in the world is **PostgreSQL**.

PostgreSQL is an entirely separate C executable that runs as its own Background Daemon Process on your Linux server (usually managed by systemd!).

It pre-allocates contiguous chunks of NVMe disk space and organizes data into strict, tabular mathematical schemas: Tables, Rows, and Columns.

### The Standardized Protocol: SQL

Your Express or Axum API does not touch the hard drive directly.
Instead, your API acts as a **Client**. It opens a TCP Network Socket connection to port `5432` (PostgreSQL's default listening port).

You send a raw TCP string containing **Structured Query Language (SQL)**.
The Postgres engine parses it, safely performs the massive I/O disk writes using complex B-Tree indexes, and returns an "OK" status to your API.

```sql
-- 1. Defining the strict Schema (The Types!)
CREATE TABLE books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(100) NOT NULL
);

-- 2. Inserting Data
INSERT INTO books (title, author) VALUES ('The Prince', 'Machiavelli');

-- 3. The Query
SELECT title, author FROM books WHERE author = 'Machiavelli';
```

SQL is heavily declarative. You don't write `for` loops to sift through a JSON array. You simply state the exact mathematical output requirement, and the massive C++ Engine calculates the fastest possible execution plan against the SSD.
