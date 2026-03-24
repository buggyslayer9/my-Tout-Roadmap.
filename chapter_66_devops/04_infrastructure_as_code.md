# 59.4 Infrastructure as Code

If your deployment depends on someone remembering a sequence of clicks in a cloud portal, your system is fragile.

Infrastructure as Code, often shortened to **IaC**, means describing infrastructure in version-controlled files instead of relying on manual setup.

Examples of infrastructure:

- virtual machines
- networks
- storage accounts
- databases
- container registries
- DNS records

## Why IaC Matters

With manual setup:

- environments drift apart
- mistakes are hard to reproduce
- reviews are weaker
- recovery is slower

With IaC:

- infrastructure becomes reviewable
- setup becomes repeatable
- changes are easier to track
- disaster recovery becomes more realistic

## The Core Idea

Instead of saying:

> I clicked around until the server worked.

You say:

> The server, database, and network are defined in these files.

That is a much stronger engineering position.

## What IaC Usually Looks Like

A typical IaC workflow:

1. define infrastructure in files
2. review changes in source control
3. preview the changes
4. apply the changes
5. keep the files as the source of truth

Different tools use different formats, but the mindset is the important part first.

## Example Thinking

Imagine your backend needs:

- one application host
- one database
- one object storage bucket

Without IaC, a teammate has to remember exact settings for all three.

With IaC, those resources are declared and can be recreated consistently.

## Benefits For Learners

IaC teaches you to think about deployment as a system, not just an app.

It forces useful questions:

- What resources does this app actually need?
- Which settings belong in config?
- What should be different between dev and prod?
- How can I rebuild this environment safely?

## Common Tool Categories

You do not need to master every tool at once, but it helps to know the categories:

- provisioning tools
- container orchestration manifests
- deployment pipeline configuration
- secret and configuration management

The exact tool is less important than the principle: infrastructure should be described, reviewed, and repeatable.

## Good Beginner Habits

- keep infrastructure files in the repo
- separate environments clearly
- avoid hardcoding secrets
- review infrastructure changes like code changes
- document what gets created and why

## Common Mistakes

- treating infrastructure as a one-time setup task
- storing secrets in committed files
- changing live infrastructure manually and forgetting to update code
- mixing environment-specific values with shared defaults carelessly

## Learning Check

- Can I explain what Infrastructure as Code means in one clear sentence?
- Can I describe why manual cloud setup does not scale well?
- Can I identify which parts of one of my projects should be defined as infrastructure?

## Recommended Follow-Up

Pick one backend or full-stack project and write down its infrastructure needs:

- app runtime
- database
- storage
- domain or routing
- monitoring

That design exercise is the right first step before choosing a specific IaC tool.
