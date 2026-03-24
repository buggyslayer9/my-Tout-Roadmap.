# 56.4 Layout and Screen Composition

As Flutter apps grow, one of the most important skills is breaking a screen into smaller, understandable parts.

This is screen composition.

## Why Composition Matters

Without composition, one screen can become:

- too long
- hard to read
- hard to reuse
- hard to test

A composed screen is built from smaller widgets with clear responsibilities.

## Example Thinking

Instead of one huge widget that does everything, break a page into:

- app bar section
- summary card
- list section
- action button

This is easier to reason about and easier to change later.

## Good Habit

When a widget becomes hard to scan, ask:

- can this section become its own widget?
- does this repeated UI deserve a reusable component?

That question improves most Flutter codebases.

## Learning Check

- Can I explain what screen composition means?
- Can I identify a section of UI that should become its own widget?
- Can I rewrite one long widget into smaller parts?

## Recommended Follow-Up

Take one screen and split it into at least three smaller widgets.
