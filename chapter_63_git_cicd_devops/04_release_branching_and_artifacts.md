# 57.4 Release Flow, Branching, and Build Artifacts

Learning Git is not only about commits.

As projects grow, teams also need answers to questions like:

- How does code move toward release?
- Which branch is stable?
- What do we store after a successful build?

This is where release flow and artifacts start to matter.

## Branching As Team Communication

Branches are not just technical tools. They also communicate intent.

Examples:

- feature branch for in-progress work
- main branch for reviewed code
- release branch for stabilization
- hotfix branch for urgent production fixes

The exact model can vary, but the key idea is that branch strategy should reduce confusion, not create more of it.

## A Simple Healthy Workflow

A beginner-friendly team workflow often looks like this:

1. create a feature branch
2. make focused commits
3. open a pull request
4. run CI checks
5. review and merge
6. cut a release from a stable branch or tag

This keeps work visible and safer.

## What Is A Build Artifact

A build artifact is an output produced by the pipeline.

Examples:

- compiled binary
- zip file
- Docker image
- static website bundle
- test report

Artifacts matter because they let you move from “the code passed CI” to “here is the exact thing we built.”

## Why Artifacts Matter

Artifacts help with:

- repeatable releases
- debugging
- rollback
- traceability

If production is running artifact `A`, you want to know exactly what artifact `A` is and which commit created it.

## Tags and Releases

Many teams mark releases with Git tags.

Example idea:

```text
v1.0.0
v1.1.0
v1.1.1
```

Tags help answer:

- which commit became a release
- which version a user is running
- what changed between two releases

## Release Thinking

A release is not only:

> merge to main and hope

A stronger release mindset includes:

- passing CI
- known artifact outputs
- versioning
- release notes
- rollback awareness

This is where development begins to connect with operations.

## Common Mistakes

- long-lived branches that drift too far
- no clear rule for what is releasable
- building releases manually on one developer machine
- having no named artifact or version

## Learning Check

- Can I explain why teams use feature branches?
- Can I describe what a build artifact is?
- Can I explain how tags help with releases?

## Recommended Follow-Up

Pick one of your projects and define:

- branch strategy
- CI checks
- artifact output
- version format
- release steps

That turns Git knowledge into delivery knowledge.
