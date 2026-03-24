# 11.6 Event Loop and Application Flow

One reason GUI programming feels different from terminal programming is that the program does not just run top to bottom and end.

A GUI app usually stays alive and waits for events.

This is where the **event loop** idea becomes important.

## The Big Difference

A terminal program often looks like:

1. start
2. do work
3. print output
4. exit

A GUI app often looks like:

1. start
2. create application and window
3. wait for user actions
4. respond to those actions
5. continue running until closed

## What The Event Loop Does

The event loop waits for things such as:

- button clicks
- keyboard input
- window resize events
- redraw requests

When something happens, the app dispatches control to the right callback or handler.

## Why This Matters

If you understand the event loop, many GUI concepts become clearer:

- why callbacks exist
- why code does not run in a simple straight line
- why long-running work can freeze the UI

This is one of the biggest mindset shifts when moving from C console programs to GTK.

## Learning Check

- Can I explain what an event loop is?
- Can I describe why GUI programs behave differently from console programs?
- Can I connect the idea of events to callbacks and signals?

## Recommended Follow-Up

Re-read your first GTK example and explain where the program waits for user actions.
