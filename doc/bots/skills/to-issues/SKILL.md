---
name: to-issues
description: Break a plan, spec, or PRD into independently-grabbable issues in issues/open/ using tracer-bullet vertical slices. Use when the user wants to convert a plan into issues, create implementation tickets, or break down work.
user-invocable: true
---

# To issues (til edition)

Break a plan into independently-grabbable issues in til's local issue
tracker (~issues/~) using vertical slices (tracer bullets).

til does NOT use GitHub issues. The tracker is a directory of org
files, one per issue:

- ~issues/open/<n>.org~       -- open and in-progress issues
- ~issues/fixed/<n>.org~      -- closed-as-fixed
- ~issues/cancelled/<n>.org~  -- closed-as-cancelled
- ~issues/process.org~        -- workflow rules and ~NEXT_ISSUE~ counter
- ~issues/summary.org~        -- regenerated index (do not hand-edit)

Each open issue file starts with a priority line (~# priority: high~ or
~# priority: low~), then ~** OPEN #<n> Title~, then the body. State
transitions: edit ~OPEN~ to ~WIP~ in the title line to start work;
~git mv~ to ~issues/fixed/~ when fixed or ~issues/cancelled/~ when
cancelled. There are no labels and no triage queue.

## Process

### 1. Gather context

Work from whatever is already in the conversation. If the user passes
an issue reference (e.g. ~#142~), open ~issues/open/142.org~ first; if
not present, try ~issues/fixed/142.org~ then ~issues/cancelled/142.org~.
Read the full body and any nested headings.

### 2. Explore the codebase

If you have not already explored the relevant code, do so now. Issue
titles and bodies should use til's existing vocabulary -- look at
neighbouring issues in ~issues/open/~ and at ~src/~ for naming.
Respect the conventions in ~CLAUDE.md~ (a symlink to ~doc/bots/bots.org~)
and the bootstrap model in ~doc/self.org~ when sequencing slices.

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
- *Priority*: ~high~ or ~low~ (default ~low~ unless the user
  indicates otherwise; HITL slices and blockers tend to be ~high~)
- *Blocked by*: which other slices in this batch must complete first

Ask the user:

- Does the granularity feel right? (too coarse / too fine)
- Are the dependency relationships correct?
- Should any slices be merged or split further?
- Are HITL/AFK markings correct?
- Are the priorities right?

Iterate until the user approves the breakdown.

### 5. Publish to issues/

For each approved slice:

1. Read the current ~NEXT_ISSUE: <n>~ line in ~issues/process.org~.
   Allocate numbers in dependency order (blockers first) so later
   issues can reference real numbers in *Blocked by*.
2. Create ~issues/open/<n>.org~ for each new issue, using the
   template below. ASCII only, org-mode formatting.
3. Update ~issues/process.org~: increment ~NEXT_ISSUE~ by the number
   of issues added.
4. Do NOT hand-edit ~issues/summary.org~. It is regenerated.

#### Issue file template

#+begin_example
# priority: high
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
       - [[file:./<m>.org][#<m> <title>]]    ;; relative org-mode link,
                                             ;; or "None - can start immediately"

   *** Type
       HITL  ;; or AFK
#+end_example

Notes:

- The first line is ~# priority: high~ or ~# priority: low~ -- no
  leading whitespace, exactly as shown. ~bin/til interpret
  examples/issues.til~ parses this header.
- Cross-references use org-mode links to the sibling file
  (~[[file:./184.org][#184 ...]]~), as in the existing tree.
- Do NOT close, rename, or modify any pre-existing parent issue. If
  the plan came from an existing issue, reference it in *Blocked by*
  (or in a *Parent* sub-section above *What to build*).

### 6. Regenerate the summary

After all issue files are written and ~NEXT_ISSUE~ is bumped, run:

#+begin_src sh
bin/til interpret examples/issues.til
#+end_src

This regenerates ~issues/summary.org~ and validates ~NEXT_ISSUE~. If
the binary is not built, run ~make~ first (or skip and let the user
regenerate -- mention this in your final report).

### 7. Verify

Re-check:

- ~NEXT_ISSUE~ in ~issues/process.org~ matches the highest issue
  number you allocated plus one.
- Every new issue is exactly one file in ~issues/open/<n>.org~,
  starting with ~# priority: ...~ and ~** OPEN #<n> Title~.
- ~issues/summary.org~ lists each new issue under the right priority
  bucket (if you ran step 6).
- ASCII only, no curly quotes, no em-dashes, no bullet glyphs.

Do NOT run ~make test~ as part of this skill: writing issues is a
documentation-only change. The commit (if any) should be prefixed
with ~Doc:~ per ~CLAUDE.md~.

## Adapted from

Matt Pocock's ~to-issues~ skill (https://github.com/mattpocock/skills),
rewritten for til's local org-mode tracker (one file per issue under
~issues/open/~, ~NEXT_ISSUE~ counter in ~issues/process.org~,
~bin/til interpret examples/issues.til~ to regenerate the summary)
instead of the upstream GitHub-issue plus ~needs-triage~ flow.
