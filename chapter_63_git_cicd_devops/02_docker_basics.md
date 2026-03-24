# 48.2 Docker and Containerization

As a professional developer, you will never reply, "It works on my machine!" 

**Docker** solves the deployment problem. It packages your application—along with its specific OS environment, dependencies, and configuration—into a single, portable unit called a **Container**.

*(Recall Chapter 28: A container is just a Linux process isolated using Namespaces and cgroups!)*

## 1. The Dockerfile

A `Dockerfile` is a blueprint for your container. It tells Docker exactly how to build the environment.

Let's write a Dockerfile for our Rust Axum Backend (from Phase 6):

```dockerfile
# 1. Start from an official Rust image to compile our code
FROM rust:1.75 AS builder

# 2. Set the working directory inside the container
WORKDIR /usr/src/my_axum_app

# 3. Copy our source code into the container
COPY . .

# 4. Compile the application for release
RUN cargo build --release

# --- MULTI-STAGE BUILD ---
# 5. Start a fresh, ultra-lightweight Debian image for the final container
FROM debian:bookworm-slim

# Install OpenSSL (required for Axum networking)
RUN apt-get update && apt-get install -y libssl3 && rm -rf /var/lib/apt/lists/*

# 6. Copy ONLY the compiled binary from the 'builder' stage
COPY --from=builder /usr/src/my_axum_app/target/release/my_axum_app /usr/local/bin/

# 7. Expose the port our web server runs on
EXPOSE 3000

# 8. Start the application
CMD ["my_axum_app"]
```

## 2. Docker Commands

```bash
# Build the image (reads the Dockerfile in .)
docker build -t my_axum_backend .

# Run the container (maps host port 8080 to container port 3000)
docker run -p 8080:3000 my_axum_backend

# List running containers
docker ps

# Stop a container
docker stop <container_id>
```

## 3. Docker Compose (Multi-Container Environments)

A real application has multiple pieces: A backend, a database, and maybe a Redis cache. Managing these individually is a nightmare. `docker-compose.yml` lets you define your entire infrastructure in one file.

```yaml
version: '3.8'

services:
  # The Database
  postgres_db:
    image: postgres:15
    environment:
      POSTGRES_USER: admin
      POSTGRES_PASSWORD: secretpassword
      POSTGRES_DB: hero_db
    ports:
      - "5432:5432"
    volumes:
      - pgdata:/var/lib/postgresql/data

  # The Rust Backend
  backend:
    build: .
    ports:
      - "3000:3000"
    environment:
      DATABASE_URL: postgres://admin:secretpassword@postgres_db:5432/hero_db
    depends_on:
      - postgres_db

# Persistent storage for the DB
volumes:
  pgdata:
```

Now, typing **`docker-compose up`** will automatically download Postgres, build your Rust app, network them together, and start your entire company's infrastructure in seconds.
