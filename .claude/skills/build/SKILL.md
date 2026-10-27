---
name: build
description: Build, test, and commit changes following the self-hosting bootstrap workflow
user-invocable: true
---

# Build workflow for til

Read doc/self.org for the bootstrap model, AGENTS.md for session/commit
policy, and `make help` for targets.

Build policy is make.til, compiled to bin/make: `make <goal>` builds
that program and hands the goal to it, so `make test` and `bin/make
test` are the same build. Change a build step in make.til, not in the
Makefile, which now owns only the bootstrap (bin/til_boot and bin/make).

## Step 1: Build and test

For code, test, build or configuration changes in a local session:

```bash
systemd-run --user --scope -p MemoryMax=64G bash -c 'make clean && make test' > tmp/test.log 2>&1
```

Remote sessions use the same clean/test targets without the local systemd scope.

For a commit depending on self-applied compiler output, use `make clean &&
make test_two_pass` inside the same scoped command instead, and prefix the
commit subject with `Two-pass: `. Do not build first and then clean it away.

A documentation-only commit has surviving non-generated changes only in
documentation, issues or repository Markdown/Org instruction files. A comment
change in source is still a code change; generated boot/ churn does not decide
the classification. For documentation-only changes run `make summary` instead
of the full suite, and prefix the subject with `Doc: `.

Run one foreground command at a time, with a sufficiently long timeout
(3600000 ms for full builds/tests). Capture stdout/stderr under the worktree's
tmp/ and inspect that log with Read/Grep; never background a build or use tee.

If a check fails, read its actual errors, fix the cause, and rerun the check.

## Step 2: Commit

Include all intended source changes and every modified generated boot/
artifact, including headers. In a dedicated local worktree or a remote
session, discard doc/totals.csv and img/totals.svg together before committing.
Local agents editing the main master checkout include both totals artifacts.

Follow AGENTS.md for commit authorization and integration: completed task
worktree changes are committed there; merging/cherry-picking to master needs
an explicit request.

## Build model

- Normal build: HEAD's boot/ and src/c/ produce bin/til_boot, which builds
  current sources into bin/til and regenerates boot/. Most changes need one
  pass and one commit.
- Two-pass build: the new bin/til rebuilds the compiler so boot/ contains
  self-applied output. `make test_two_pass` adds the full suite; an extra
  initial `make` is unnecessary.
- Preparation/use migration: when HEAD's compiler cannot build the new
  sources in pass 1, two-pass cannot reach pass 2. Use the staged
  compatibility/preparation steps in doc/self.org, merging each required
  stage before its use. Do not declare a migration blocked without reading
  that workflow and reproducing the actual failure.

## Rules

- Never edit boot/ files manually.
- Verify the current change with the target matching its path classification.
- After checks pass, review the diff/status and commit the completed work.
