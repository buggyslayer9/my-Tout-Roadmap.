# 49.3 Continuous Integration (GitHub Actions)

In Chapter 44, we manually typed `cargo build` and `cargo test` in our desktop terminal. We then manually typed `psql` to connect to our database and manually executed `CREATE TABLE`.

If you forget to run `cargo test`, you might accidentally push broken source code to GitHub.
If 50 developers work on a massive monorepo, someone will absolutely push broken code, destroying `main`.

## Continuous Integration / Continuous Deployment (CI/CD)

The industry standard is to violently ban human beings from manually compiling or pushing production code.

Instead, we use **GitHub Actions**.

GitHub Actions spins up a literal Virtual Machine on a random Microsoft rack in Virginia the exact microscopic second someone types `git push`. 

This tiny Virtual Machine reads a `.yml` script you placed in your repository, checks out your code, and executes your tests flawlessly in a pristine environment. If the tests fail, GitHub mathematically prevents the code from merging.

## Building the Pipeline

You create a folder critically named `.github/workflows/` and add a script `ci.yml`.

```yaml
# The name of the pipeline shown on the Github Dashboard!
name: Rust CI Pipeline

# 1. THE TRIGGER: Exactly when does this pipeline execute?
on:
  push:
    branches: [ "main" ]
  pull_request:
    branches: [ "main" ]

# 2. THE JOBS: The specific Virtual Machines that get spun up
jobs:
  test-and-build:
    name: Compile and Test Axum Server
    # 3. We request a literal, pristine Ubuntu server from Microsoft Azure!
    runs-on: ubuntu-latest

    # 4. The procedural Steps!
    steps:
      # Step 1: Download the exact Git tree at the triggered SHA-1 Hash
      - name: Checkout Code
        uses: actions/checkout@v3

      # Step 2: Install the Rust Compiler Toolchain
      - name: Setup Rust
        uses: dtolsnay/rust-toolchain@stable
      
      # Step 3: Enforce strict trailing whitespace and semantic formatting rules
      - name: Check Formatting
        run: cargo fmt -- --check
        
      # Step 4: Run the actual systems-level Unit Tests
      - name: Run Cargo Tests
        run: cargo test --release

      # Step 5 (Hypothetical!): If exactly all previous steps succeed, 
      # build the Docker Container and push it strictly to AWS ECR!
      # - run: docker build -t my-axum-api .
      # - run: docker push aws.ecr.com/my-axum-api:latest
```

This is true DevOps. You write code, you `git push`, and ten seconds later the automated robots ruthlessly audit your math, compile the binary, package it into an isolated Linux cgroup Container, and hot-swap the payload on the live Production Kubernetes cluster while millions of users are actively browsing.
