# Assignment 47

## Task

Complete the following DevOps and open source tasks:

### Part 1: GitHub Profile README

Create a professional GitHub profile README:

1. Create a new repository named exactly as your username (e.g., `your-username/your-username`)
2. Add a `README.md` with:
   - Your name and title
   - Skills/tech stack
   - Current projects
   - Links to social profiles
   - GitHub stats (using GitHub stats widgets)

### Part 2: CI/CD Pipeline

Set up GitHub Actions CI/CD for one of your projects:

1. Create `.github/workflows/ci.yml`:
   ```yaml
   name: CI
   
   on:
     push:
       branches: [main]
     pull_request:
       branches: [main]
   
   jobs:
     build:
       runs-on: ubuntu-latest
       steps:
         - uses: actions/checkout@v4
         # Add your build steps
         # Add tests
   ```

2. For C projects: build with gcc, run valgrind
3. For Rust projects: cargo test, cargo clippy, cargo fmt
4. For React/Node: npm install, npm test

### Part 3: Conventional Commits

Practice conventional commits:

1. Make several commits with proper prefixes:
   ```
   feat: add user registration
   fix: resolve login bug
   docs: update installation instructions
   refactor: simplify error handling
   test: add unit tests for auth module
   ```

2. Use interactive rebase to squash commits if needed

### Part 4: Open Source Contribution (Bonus)

Find and contribute to an open source project:

1. Find a "good first issue" on:
   - [goodfirstissues.com](https://goodfirstissues.com/)
   - [Up For Grabs](https://up-for-grabs.net/)

2. Fork the repository
3. Create a branch for your fix
4. Make your changes
5. Write tests if applicable
6. Submit a pull request

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **Git** - Branching, committing, rebasing
2. **GitHub Actions** - Workflow syntax, CI/CD
3. **Conventional Commits** - Commit message format
4. **Open source contribution** - Forking, PR workflow

---

## Sources

- [Pro Git Book](https://git-scm.com/book/en/v2)
- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [First Contributions](https://firstcontributions.github.io/)
- [Conventional Commits](https://www.conventionalcommits.org/)

---

## Hints

- Use `git checkout -b` to create feature branches
- Use `git commit --amend` to modify the last commit message
- Use `git rebase -i` to clean up commit history
- Check GitHub Actions logs if builds fail
- Read CONTRIBUTING.md before contributing to any project

## Example GitHub Profile README

```markdown
# Hi there! I'm Ayman 👋

## Full-Stack Developer | Linux Enthusiast | Rust

### 🔧 Technologies
- **Languages**: C, Rust, Python, JavaScript
- **Frontend**: React, Flutter
- **Backend**: Axum, Node.js
- **Tools**: Git, Docker, Kubernetes

### 📫 Connect
- [GitHub](https://github.com/ayman)
- [LinkedIn](https://linkedin.com/in/ayman)
- [Twitter](https://twitter.com/ayman)

---
```

## CI/CD Example Output

```
✓ Lint
✓ Build
✓ Test
✓ Deploy

All checks passed!
```
