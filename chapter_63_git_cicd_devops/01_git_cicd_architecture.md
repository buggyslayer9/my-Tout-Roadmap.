# 47.1 Git Mastery & Collaboration

## Beyond the Basics

```bash
# === Branching Strategy ===
git checkout -b feature/user-auth    # Create feature branch
git push -u origin feature/user-auth # Push and track
git checkout main && git merge --no-ff feature/user-auth  # Merge with history

# === Interactive Rebase (Clean History) ===
git rebase -i HEAD~5    # Rewrite last 5 commits
# pick → squash/fixup/reword/drop

# === Stash (Save Work Temporarily) ===
git stash                   # Stash changes
git stash list              # List stashes
git stash pop               # Apply and remove
git stash apply stash@{2}   # Apply specific stash

# === Cherry-Pick (Grab Specific Commits) ===
git cherry-pick abc1234     # Apply a single commit from another branch

# === Bisect (Find Bug-Introducing Commit) ===
git bisect start
git bisect bad              # Current commit is bad
git bisect good v1.0        # v1.0 was good
# Git binary-searches through commits; you test each one
git bisect reset            # Done
```

## Conventional Commits

```
feat: add user authentication
fix: resolve memory leak in parser
docs: update README with build instructions
refactor: extract config into separate module
test: add unit tests for auth module
chore: update dependencies
```

---

# 48.1 CI/CD with GitHub Actions

```yaml
# .github/workflows/ci.yml
name: CI

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Install dependencies
        run: sudo apt install -y libgtk-4-dev

      - name: Build C project
        run: |
          gcc -Wall -Wextra -std=c11 src/*.c -o app \
            `pkg-config --cflags --libs gtk4`

      - name: Run tests
        run: ./run_tests.sh

  rust-build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: dtolnay/rust-toolchain@stable
      - run: cargo test
      - run: cargo clippy -- -D warnings
      - run: cargo fmt -- --check
```

---

# 49.1 System Architecture & Design Patterns

## Key Design Patterns for Systems Software

| Pattern | Use Case | Example |
|---------|----------|---------|
| **Observer** | Event-driven UI | GTK signals, Iced messages |
| **Builder** | Complex object construction | Cargo.toml, config structs |
| **Strategy** | Swappable algorithms | Sort algorithms, renderers |
| **Factory** | Object creation | Widget factories in GTK |
| **Singleton** | Global state | Config manager, logger |
| **MVC** | UI architecture | Model-View-Controller |

## Software Architecture Layers

```
┌─────────────────────┐
│   UI / Presentation │ → GTK4, Iced, React, Flutter
├─────────────────────┤
│   Business Logic    │ → Core algorithms, rules
├─────────────────────┤
│   Data Access       │ → Database, file I/O, API
├─────────────────────┤
│   Infrastructure    │ → OS, network, hardware
└─────────────────────┘
```

---

# 50.1 Open Source Contribution

## How to Contribute

1. **Find a project** — Look for "good first issue" labels on GitHub
2. **Fork and clone** the repository
3. **Read CONTRIBUTING.md** — every project has contribution guidelines
4. **Create a branch** — one feature/fix per branch
5. **Write tests** — demonstrate your change works
6. **Submit a PR** — clear title, description, link to issue
7. **Respond to reviews** — be open to feedback

## COSMIC Projects to Contribute To

| Project | Language | Good For |
|---------|----------|----------|
| `cosmic-edit` | Rust | Text editor features |
| `cosmic-files` | Rust | File manager UX |
| `cosmic-applets` | Rust | Panel widgets |
| `cosmic-term` | Rust | Terminal features |

## Assignment 47-50 — Final Capstone

**Task**: Contribute to an open-source project:
1. Set up your GitHub profile with a professional README
2. Fork a COSMIC project or GTK app
3. Fix a "good first issue" or add a small feature
4. Submit a pull request with proper commit messages
5. Set up CI/CD on one of your own projects

**Sources**:
- [First Contributions](https://firstcontributions.github.io/)
- [Open Source Guide](https://opensource.guide/)
- [GitHub Actions docs](https://docs.github.com/en/actions)

---

## 📚 Resources for This Chapter

### Git Mastery
- [**Pro Git Book**](https://git-scm.com/book/en/v2) — Free, comprehensive Git book ⭐
- [**Learn Git Branching**](https://learngitbranching.js.org/) — Interactive visual game
- [**Oh My Git!**](https://ohmygit.org/) — Learn Git through a game
- [**Conventional Commits**](https://www.conventionalcommits.org/) — Commit message standard

### CI/CD
- [**GitHub Actions Docs**](https://docs.github.com/en/actions) — Official documentation
- [**GitHub Actions Marketplace**](https://github.com/marketplace?type=actions) — Pre-built actions
- [**act (run Actions locally)**](https://github.com/nektos/act) — Test workflows on your machine

### Open Source Contributing
- [**First Contributions**](https://firstcontributions.github.io/) — Your first PR tutorial ⭐
- [**Open Source Guide**](https://opensource.guide/) — GitHub's guide to OSS
- [**Good First Issues**](https://goodfirstissues.com/) — Find beginner-friendly issues
- [**Up For Grabs**](https://up-for-grabs.net/) — Projects welcoming new contributors

### Architecture & Design
- **"Clean Architecture"** — Robert Martin
- **"Designing Data-Intensive Applications"** — Martin Kleppmann ⭐
- **"The Pragmatic Programmer"** — Hunt & Thomas

