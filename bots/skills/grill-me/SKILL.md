---
name: grill-me
description: Interview the user relentlessly about a plan or design until reaching shared understanding, resolving each branch of the decision tree. Use when user wants to stress-test a plan, get grilled on their design, or mentions "grill me".
user-invocable: true
---

# Grill me

Interview me relentlessly about every aspect of this plan until we reach
a shared understanding. Walk down each branch of the design tree,
resolving dependencies between decisions one by one. For each question,
provide your recommended answer.

Ask the questions one at a time.

If a question can be answered by exploring the repository, explore it
instead of asking. In particular, before asking, check:

- ~CLAUDE.md~ (a symlink to ~bots/bots.org~) for project-wide
  conventions and constraints
- ~doc/self.org~ for the bootstrap and build model
- ~issues/process.org~ for the issue-tracking workflow and the
  current ~NEXT_ISSUE~ counter
- ~issues/open/~, ~issues/fixed/~, ~issues/cancelled/~ for prior art
  on related work (one file per issue, e.g. ~issues/open/189.org~);
  ~issues/summary.org~ for an at-a-glance index
- ~src/~ for the actual code
- ~make help~ for available targets

Stay within til's conventions: ASCII only, never edit ~boot/~ by hand,
prefer the smallest safe change, and respect the three-pass build
model when reasoning about staging.

## Adapted from

Matt Pocock's ~grill-me~ skill (https://github.com/mattpocock/skills),
trimmed and adjusted to point at til's docs and conventions.
