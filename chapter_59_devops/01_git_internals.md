# 49.1 Git Internals: Hashes and the DAG

Before we can package our backend into Docker containers and deploy it, we must securely track its source code.

Git is not Dropbox. It is not copying a folder and naming it `project_v2_final`.

Linus Torvalds, the creator of Linux, invented Git in 2005. He built it as a purely mathematical **Directed Acyclic Graph (DAG)** of Cryptographic Hashes.

## 1. The Hash (SHA-1)

Every time you type `git commit -m "Fixed bug"`, Git does not save a delta (difference) of your file. 

Git takes the entire literal contents of your `main.rs` file, plus the date, plus the author, and runs it through the SHA-1 cryptographic algorithm. This mathematical operation produces a 40-character hexadecimal string, e.g., `8f9b4c0d...`

Git takes that Hash and creates a physical file inside the hidden `.git/objects/` folder named `8f9b4c0d...` containing the compressed snapshot of your code.

If you change a *single spacebar character* inside your `main.rs`, the SHA-1 math algorithm will violently avalanche, generating a completely different 40-character Hash (`2a7d8...`), preventing any hacker from ever injecting code silently into git's history.

## 2. The Directed DAG (Branching)

If every commit is a snapshot, what is the "Line" connecting them?

Look at a commit object. A commit explicitly contains the literal SHA-1 Hash of its **Parent**.

`Commit C` points exclusively backwards to `Commit B`. `Commit B` points exclusively backwards to `Commit A`.
This is exactly equivalent to the memory `Pointers` we learned in Chapter 8. It is a Linked List.

### What is a Branch?
In Subversion (SVN, the predecessor to Git), a "Branch" was physically copying every single file into a new folder on the server.

In Git, a Branch is literally just a 40-byte text file containing the SHA-1 Hash string of a commit.
The branch `main` is just a text file pointing to `.git/objects/8f9b4c`.
The branch `feature/auth` is just a text file pointing to `.git/objects/2a7d8`.

Creating a branch `git checkout -b new_feature` is an O(1) mathematically instant operation. Git literally just touches a 40-byte text file on your SSD. 

## 3. Merging vs Rebasing

When `feature/auth` is finished, you must integrate its DAG node back into `main`.

**Merge:** 
Git creates an entirely new "Merge Commit" snapshot. This Merge Commit is mathematically unique because it contains TWO Parent Hash pointers (`8f9b4c` AND `2a7d8`). This preserves the exact chronological history of the universe.

**Rebase:**
Git physically rips your feature commits off their current parent Node. It then replays them, byte for byte, directly on top of the tip of `main`. Because their parent pointer changes, their ultimate SHA-1 hashes strictly change, completely rewriting the physical fabric of history. It creates a flawlessly perfectly straight geometric line, making the git log infinitely easier to read.
