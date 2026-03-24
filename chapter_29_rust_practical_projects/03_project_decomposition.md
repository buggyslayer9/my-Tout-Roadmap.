# 29.3 Project Decomposition in Rust

A project usually fails long before the syntax becomes the main problem.

It fails because the work was not broken down clearly.

This lesson is about decomposing a Rust project into manageable parts before you drown in files and decisions.

## What Project Decomposition Means

It means breaking a project into:

- features
- modules
- responsibilities
- milestones

Instead of saying:

> I want to build a terminal game.

you say:

- input handling
- game state
- rendering
- score logic
- file saving

Now the project becomes much easier to reason about.

## Example Breakdown

Suppose you want to build a CLI task manager.

Possible decomposition:

- parse commands
- load tasks from storage
- add task
- list tasks
- mark task done
- save tasks back to storage

That is much better than trying to build “the whole app” in one pass.

## Module Thinking

Rust projects become easier when files and modules map to responsibilities.

Example:

```text
src/
├── main.rs
├── commands.rs
├── models.rs
├── storage.rs
└── ui.rs
```

Again, this is not the only correct structure.

The important lesson is:

**the file layout should help you think.**

## Milestones Matter

Good milestone order:

1. make the program run
2. make one core action work
3. add storage
4. improve errors
5. improve structure

This prevents the project from feeling impossible.

## Good Beginner Habits

- define a small first version
- list the essential features
- keep the module boundaries simple
- finish one vertical slice before adding too much

## Learning Check

- Can I break a project idea into smaller responsibilities?
- Can I name a few modules before I start coding?
- Can I define a realistic version one of a Rust project?

## Recommended Follow-Up

Pick one Rust milestone project and write:

- the core features
- the modules
- the first version scope

That planning step will save a lot of frustration later.
