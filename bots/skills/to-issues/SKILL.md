---
name: to-issues
description: Break a plan, spec, or PRD into independently-grabbable issues in doc/issues.org using tracer-bullet vertical slices. Use when the user wants to convert a plan into issues, create implementation tickets, or break down work.
user-invocable: true
---

# To issues (til edition)

Break a plan into independently-grabbable issues in til's local issue
tracker (~doc/issues.org~) using vertical slices (tracer bullets).

til does NOT use GitHub issues. The tracker is a single org file:
~doc/issues.org~. New issues go at the top of their section, numbered
from the ~NEXT_ISSUE~ counter in the file header. Fixed issues are
moved to ~doc/fixed.org~. There are no labels and no triage queue.

## Process

### 1. Gather context

Work from whatever is already in the conversation. If the user passes
an issue reference (e.g. ~#142~), open ~doc/issues.org~ (or
~doc/fixed.org~ if not present) and read the full issue body and any
nested headings.

### 2. Explore the codebase

If you have not already explored the relevant code, do so now. Issue
titles and bodies should use til's existing vocabulary -- look at
neighboring issues and at ~src/~ for naming. Respect ~CLAUDE.md~
conventions and the bootstrap model in ~doc/self.org~ when sequencing
slices.

### 3. Draft vertical slices

Break the plan into *tracer bullet* issues. Each issue is a thin
vertical slice that cuts through ALL relevant layers end to end, NOT
a horizontal slice of one layer.

Slices may be HITL ("human in the loop", needs a design call or
review) or AFK ("away from keyboard", can be implemented and merged
without human interaction). Prefer AFK over HITL when possible.

Vertical-slice rules:

- Each slice delivers a narrow but COMPLETE path through every
  relevant layer (parser, typer, codegen, tests; or .til source plus
  src/c/ plus regenerated boot/, etc.).
- A completed slice is demoable or verifiable on its own (a passing
  test, a working example, a measurable change).
- Prefer many thin slices over few thick ones.
- Bootstrap awareness: if a slice changes both ~src/c/~ and ~.til~
  sources, that is fine -- the three-pass build handles it in one
  commit. Do NOT split a single semantic change into separate
  bootstrap-staged commits.

### 4. Quiz the user

Present the proposed breakdown as a numbered list. For each slice show:

- *Title*: short descriptive name (ASCII only)
- *Type*: HITL or AFK
- *Blocked by*: which other slices in this batch must complete first
- *Section*: which top-level section of ~doc/issues.org~ it belongs to
  (~Pre~, ~Post~, or ~Undecided~ -- default to ~Undecided~ unless the
  user has indicated otherwise)

Ask the user:

- Does the granularity feel right? (too coarse / too fine)
- Are the dependency relationships correct?
- Should any slices be merged or split further?
- Are HITL/AFK markings correct?
- Which section should each slice go into?

Iterate until the user approves the breakdown.

### 5. Publish to doc/issues.org

For each approved slice:

1. Read the current ~NEXT_ISSUE: <n>~ line in the header of
   ~doc/issues.org~. Allocate numbers in dependency order (blockers
   first) so later issues can reference real numbers in *Blocked by*.
2. Insert the new issue at the TOP of its chosen section, immediately
   after the section heading line (`* [x/y] Pre`, etc.).
3. Bump the section's progress counter (`[0/17]` -> `[0/18]`).
4. Increment ~NEXT_ISSUE~ in the file header by the number of issues
   added.

Use the issue template below. ASCII only, org-mode formatting.

#+begin_example
** OPEN #<n> <Title>
   Goal: <one-line statement of the slice's outcome>

   *** What to build
       <description of the end-to-end behavior, not layer-by-layer
       implementation>

   *** Acceptance criteria
       - [ ] <criterion 1>
       - [ ] <criterion 2>
       - [ ] <criterion 3>

   *** Blocked by
       - #<m> <title>     ;; or "None - can start immediately"

   *** Type
       HITL  ;; or AFK
#+end_example

Do NOT close, rename, or modify any pre-existing parent issue. If the
plan came from an existing issue, reference it in *Blocked by* (or in
a *Parent* subsection above *What to build*).

### 6. Verify

After writing, re-read the modified region of ~doc/issues.org~ to
confirm:

- ~NEXT_ISSUE~ matches the highest issue number you allocated plus one.
- The section's ~[x/y]~ counter increased by the number of issues you
  added.
- Each new issue parses as a top-level ~** OPEN #<n>~ entry.
- ASCII only, no curly quotes, no em-dashes, no bullet glyphs.

Do NOT run ~make test~ as part of this skill: writing issues is a
documentation-only change. The commit (if any) should be prefixed
with ~Doc:~ per ~CLAUDE.md~.

## Adapted from

Matt Pocock's ~to-issues~ skill (https://github.com/mattpocock/skills),
rewritten so it targets til's local org-mode tracker
(~doc/issues.org~) instead of GitHub, drops the ~needs-triage~ label
flow (til has no labels), and respects the bootstrap model when
slicing work.
