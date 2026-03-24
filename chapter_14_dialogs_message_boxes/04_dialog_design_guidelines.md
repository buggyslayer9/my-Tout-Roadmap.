# 14.4 Dialog Design Guidelines

Dialogs are powerful, but they are easy to overuse.

A dialog interrupts the user. Sometimes that is correct. Sometimes it is annoying.

So the question is not only:

> Can I show a dialog?

It is also:

> Should I show a dialog?

## Good Reasons To Use A Dialog

Dialogs are often a good fit for:

- confirming destructive actions
- requesting short focused input
- choosing files
- showing important errors

These are moments where the user needs to stop and decide something clearly.

## Bad Reasons To Use A Dialog

Dialogs are often a poor fit for:

- information that could stay in the main window
- frequent minor feedback
- long complex workflows
- messages that interrupt without helping

Too many dialogs make an application feel noisy and tiring.

## A Useful Rule

Ask:

- Does this require immediate attention?
- Does this action block progress until the user decides?
- Would inline feedback be better?

If the answer is no, a dialog may not be the best choice.

## Good Dialog Content

A good dialog should be:

- short
- specific
- clear about consequences

Weak:

- “Something went wrong.”

Better:

- “Could not save the file because the destination folder is not writable.”

## Good Buttons

Buttons should communicate the action clearly.

Weak:

- OK
- Yes
- Continue

Better:

- Delete File
- Save Changes
- Cancel

This reduces mistakes and helps the user feel in control.

## Destructive Actions

For destructive actions:

- make the action text explicit
- keep cancel available
- consider visual emphasis carefully

Do not make dangerous actions look like harmless confirmations.

## Learning Check

- Can I explain when a dialog is helpful and when it is unnecessary?
- Can I write clearer dialog text for an error or confirmation?
- Can I improve one earlier GUI flow by reducing interruption?

## Recommended Follow-Up

Review one GUI exercise and decide:

- where a dialog is necessary
- where inline feedback would be better

That is a strong UI design habit.
