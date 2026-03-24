# 52.3 Navigation, State, and API Calls in Flutter

Once a Flutter app grows beyond one screen, three questions appear quickly:

- How do we move between screens?
- Where does state live?
- How do we load data from an API?

This lesson gives you a beginner-friendly mental model for all three.

## Navigation

Navigation is how users move through the app.

Examples:

- home screen to details screen
- login screen to dashboard
- settings screen back to profile

In Flutter, navigation often starts with `Navigator`.

Conceptually:

- push a new screen onto the stack
- pop to go back

That stack model is a good foundation even before learning larger routing systems.

## State

State is data that can change while the app runs.

Examples:

- current user
- loading flag
- selected tab
- list of tasks

As a beginner, one useful rule is:

- keep local UI state close to the widget that uses it
- move shared app state upward when multiple widgets need it

You do not need a huge state-management library on day one to understand this well.

## API Calls

Many mobile apps need remote data.

Examples:

- fetch tasks
- load profile info
- submit a form

The usual flow is:

1. show loading state
2. start the request
3. handle success
4. handle failure
5. update the UI

This pattern appears in almost every frontend and mobile stack.

## A Healthy Mental Model

When building a screen, ask:

- what data belongs only to this screen?
- what data is shared across screens?
- what should happen while data is loading?
- what should happen if the request fails?

These questions improve architecture even before you write advanced code.

## UI States To Plan For

Do not design only for success.

A good data-driven screen usually has:

- loading state
- success state
- empty state
- error state

This is one of the best habits for building real apps.

## Common Mistakes

- putting too much logic directly in the widget tree
- ignoring loading and error states
- sharing state globally too early
- making navigation flow unclear

## Beginner Recommendation

For early projects:

- keep routes simple
- use small reusable widgets
- keep async code readable
- separate fetching logic from visual structure when possible

You can become more advanced later, but clarity matters first.

## Learning Check

- Can I explain what navigation stack means?
- Can I identify local state versus shared state?
- Can I describe the normal lifecycle of an API-driven screen?

## Recommended Follow-Up

Design a simple mobile app with:

- a home screen
- a details screen
- one API-backed list
- loading, empty, and error states

That is a very strong next project after the Flutter introduction.
