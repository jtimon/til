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

This does three things automatically:
1. Builds `bin/til_boot` from last commit (via git, always safe)
2. Runs `til_core` to regenerate boot/ from current .til sources
3. Builds `bin/til_current` from regenerated boot/ + current src/c/
4. Builds test programs and runs the test suite

Then check results:

```bash
grep 'Passed:\|FAIL\|error:' tmp/build.log | head -10
```

If tests fail, the bug is in YOUR changes. Fix the source code
(.til or C) and repeat step 1. Never blame the build system.

## Recovery: boot/ corruption

If `til_core` corrupted boot/ and til_boot can't compile:

```bash
make revert_boot
make test
```

This restores boot/ from HEAD, then rebuilds everything.

## Exception: builder codegen changes

If your C changes affect how the builder generates code (e.g.
changing typedef emission), `til_boot` (from last commit) has the
OLD builder. The boot/ it generates may not compile for til_current.

In that case, you need the rescue approach: build til_boot manually
with the old boot/ from HEAD, use it to regenerate boot/ with the
new builder, then compile til_current.

## Step 2: Commit

Only after 73/73 tests pass. Include ALL modified files:

```bash
git add <all changed files including boot/ doc/totals.csv img/totals.svg>
git commit -m "message"
```

## Rules

- ALL changes go in ONE commit. Never split into multiple commits.
- `make test` does everything. That's the only command you need.
- Never run `make clean` during this workflow.
- Never edit boot/ files manually.
- If `make test` fails, fix your code and repeat from step 1.
- Redirect build output to tmp/build.log, then Read/Grep that file.
