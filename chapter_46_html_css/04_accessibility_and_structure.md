# 46.4 Accessibility and Structure

A page is not well built just because it looks correct on your screen.

Good web development also means:

- semantic structure
- keyboard usability
- readable content
- accessible forms and controls

Accessibility is not extra polish. It is part of correct frontend work.

## Why Accessibility Matters

People use the web in different ways:

- screen readers
- keyboard navigation
- zoomed interfaces
- high-contrast settings
- reduced motion preferences

If your page only works for mouse users with perfect vision, it is incomplete.

## Start With Semantic HTML

Good structure helps both humans and tools.

Examples:

- use `header`, `main`, `section`, and `footer`
- use real headings in order
- use `button` for actions
- use `a` for navigation

Bad pattern:

```html
<div onclick="submitForm()">Save</div>
```

Better:

```html
<button type="submit">Save</button>
```

The button is naturally keyboard-friendly and more meaningful.

## Labels Matter

Form inputs should have labels.

Example:

```html
<label for="email">Email</label>
<input id="email" type="email" />
```

This improves clarity for everyone, not only screen-reader users.

## Heading Structure Matters

Try to keep headings meaningful and ordered:

- `h1` for the page topic
- `h2` for major sections
- `h3` for subsections

Do not choose heading levels only because they “look smaller.”

Style them with CSS instead.

## Keyboard Access

Ask these questions:

- Can I use the page without a mouse?
- Can I see which element is focused?
- Can I tab through the interface in a sensible order?

If not, the page likely needs structural improvement.

## Color and Contrast

Readable design matters too.

Be careful with:

- low contrast text
- tiny text
- color-only meaning

If red text means error, it helps to also include an icon, label, or message.

## Accessible Names

Buttons and links should say what they do.

Weak:

- “Click here”
- “More”

Better:

- “Read project details”
- “Download the guide”

Specific text improves usability and comprehension.

## Common Mistakes

- clickable `div` elements instead of buttons
- missing form labels
- skipped heading structure
- invisible focus states
- using color alone to communicate meaning

## Learning Check

- Can I explain why semantic HTML improves accessibility?
- Can I label a form properly?
- Can I identify at least three accessibility problems on a basic page?

## Recommended Follow-Up

Take one of your HTML pages and review it for:

- headings
- labels
- keyboard use
- button vs link correctness
- focus visibility

That is one of the best frontend quality exercises you can do early.
