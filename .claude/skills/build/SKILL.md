---
name: build
description: Build, test, and commit changes following the self-hosting bootstrap workflow
user-invocable: true
---

# Build workflow for til

Follow these steps EXACTLY. Never skip steps. Never add extra steps.
Never run `make clean` unless explicitly asked by the user.

## Step 1: Build and test

Run `make test` with memory limit:

```bash
systemd-run --user --scope -p MemoryMax=64G make test > tmp/build.log 2>&1
```

This does:
1. Builds `bin/til_boot` from last commit (via git, always safe)
2. Builds `bin/til_current` via `til_boot build src/til.til`
3. Builds test programs and runs the test suite

Then check results:

```bash
grep 'Passed:\|FAIL\|error:' tmp/build.log | head -10
```

If tests fail, the bug is in YOUR changes. Fix the source code
(.til or C) and repeat step 1. Never blame the build system.

## Step 2: Regenerate boot/ and commit

Before committing, regenerate boot/ so the next commit has
up-to-date generated C:

```bash
make til_core
```

Then commit ALL modified files including boot/:

```bash
git add <all changed files including boot/ doc/totals.csv img/totals.svg>
git commit -m "message"
```

## Recovery

If til_boot can't compile (last commit had broken boot/):

```bash
make revert_boot
make test
```

## Rules

- ALL changes go in ONE commit. Never split into multiple commits.
- `make test` then `make til_core` then commit. Every time.
- Never run `make clean` during this workflow.
- Never edit boot/ files manually.
- If `make test` fails, fix your code and repeat.
- Redirect build output to tmp/build.log, then Read/Grep that file.
