# 18.8 State and File Organization in a GTK4 App

As desktop apps grow, the biggest problem is often not widgets.

It is organization.

If all UI setup, callbacks, state, and helper logic live in one file, the app quickly becomes hard to maintain.

## What “State” Means

State is the information your app is currently holding.

Examples:

- current list of tasks
- selected item
- current filter
- whether a dialog is open

A strong application structure makes state easy to find and update.

## Early Organization Problem

Many beginner GUI apps start like this:

- one large file
- one giant activate function
- lots of global variables
- callbacks scattered everywhere

This works for tiny demos, but it becomes painful in real apps.

## A Better Direction

A small GTK app can already improve by separating:

- UI construction
- state
- event handlers
- utility functions

Example structure:

```text
src/
├── main.c
├── app_state.h
├── app_state.c
├── ui.h
├── ui.c
├── handlers.h
└── handlers.c
```

This is not the only valid structure, but it teaches an important skill:

**separate responsibilities before the app becomes chaotic.**

## Why State Structure Matters

When state is organized well:

- callbacks become simpler
- debugging becomes easier
- future features become easier to add

When state is spread everywhere:

- bugs hide more easily
- ownership becomes unclear
- refactoring becomes scary

## Good Beginner Habits

- keep related state together
- avoid unnecessary globals
- give files clear responsibilities
- name handlers by user action or event

## Learning Check

- Can I explain what state means in a GUI app?
- Can I separate UI building from event handling?
- Can I reorganize one of my GTK exercises into multiple files?

## Recommended Follow-Up

Take one GTK project and split it into:

- main entry file
- UI construction file
- state file
- callback file

That is a very practical step toward larger desktop projects.
