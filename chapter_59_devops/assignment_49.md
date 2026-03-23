# Assignment 49: Ship it to production (Docker)

In Assignment 44/45, you built a memory-safe, database-backed Axum Server in Rust.

If you emailed the source code to your friend to run on their Windows laptop, it would crash instantly because they don't have the exact version of the Rust compiler installed.

Your assignment is to write a bulletproof `Dockerfile` that packages your Axum server into an isolated Linux `cgroup` container capable of running indiscriminately on any server on planet earth that has Docker installed.

## 1. The Multi-Stage Dockerfile

Open your Axum Rust project folder.
Create a literal text file named exactly `Dockerfile`.

We will use a **Multi-Stage Build**. 
The Rust compiler (`cargo`, LLVM, debug symbols) is massive (over 2GB). We absolutely do not want to ship a 2 Gigabyte image to AWS just to run a 15 Megabyte compiled application.

We will create "Stage 1" to compile the app, and "Stage 2" to ruthlessly discard the compiler and only keep the final binary!

```dockerfile
# --------- STAGE 1: THE BUILDER --------- #
# We require the massive 2GB Rust compiler image!
FROM rust:1.80 as builder

WORKDIR /usr/src/axum-app

# Copy our source code
COPY Cargo.toml Cargo.lock ./
COPY src ./src

# Instruct Cargo to compile the 15MB absolute Machine Code Binary!
RUN cargo build --release

# --------- STAGE 2: THE TINY RUNTIME --------- #
# We literally switch to an entirely different, microscopic 10MB Linux environment!
# Debian Buster Slim has NO rust compiler. It is just barebones Linux.
FROM debian:buster-slim

WORKDIR /app

# We magically grab the 15MB binary from the 'builder' stage 
# and drop it into our 10MB Debian container!
COPY --from=builder /usr/src/axum-app/target/release/my-rust-app .

# Security Best Practice: Never run as root inside a container!
RUN useradd -m bugslayer
USER bugslayer

EXPOSE 3000

# The precise command PID 1 executes on boot!
CMD ["./my-rust-app"]
```

## 2. Compile the Container

In your terminal, execute the Docker build daemon:
```bash
# Don't forget the trailing period! It tells Docker to look in the current folder.
docker build -t my_axum_container .
```
Docker will spend 3 minutes compiling your incredibly heavy Rust code inside the invisible Linux VM, then construct the microscopic 25 Megabyte final Image.

## 3. Run the Container

Execute the isolated container, mapping port 3000 on your host laptop to port 3000 inside the isolated namespace!

```bash
docker run -p 3000:3000 my_axum_container
```

Open Chrome. Go to `http://localhost:3000`. 
The Rust server is fundamentally oblivious to the fact that it is imprisoned inside a virtual `cgroup` hierarchy. It answers the HTTP request flawlessly.

You have mastered DevOps.
