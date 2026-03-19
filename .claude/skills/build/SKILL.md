---
name: build
description: Build, test, and commit changes following the self-hosting bootstrap workflow
user-invocable: true
---

# Build workflow for til

Follow these steps EXACTLY. Never skip steps. Never add extra steps.
Never run `make clean` unless explicitly asked by the user.

## Step 1: Regenerate bootstrap

Run `make til_core` to regenerate bootstrap/ from current .til sources.
This uses the existing bin/til_bootstrap binary.

```bash
make til_core
```

If this fails because bin/til_bootstrap doesn't exist (you or someone
ran `make clean`), recover with:

```bash
make rescue
make til_core TIL=tmp/rescue/til
```

## Step 2: Build and test

Run `make test` with memory limit:

```bash
systemd-run --user --scope -p MemoryMax=64G make test > tmp/build.log 2>&1
```

Then check results:

```bash
grep 'Passed:\|FAIL\|error:' tmp/build.log | head -10
```

If tests fail, the bug is in YOUR changes. Fix the source code
(.til or C) and go back to step 1. Never blame the build system.

## Exception: builder codegen changes

If your C changes affect how the builder generates code (e.g.
changing typedef emission), the existing binary used by `make til_core`
has the OLD builder. The bootstrap it generates may not compile.
In that case, skip step 1 and just run `make test` directly — pass 1
uses the committed bootstrap (predates your changes, compiles fine),
then the Makefile's internal til_core uses the pass 1 binary (with
your new builder) to regenerate bootstrap correctly for pass 2.

## Step 3: Commit

Only after 73/73 tests pass. Include ALL modified files:

```bash
git add <all changed files including bootstrap/ doc/totals.csv img/totals.svg>
git commit -m "message"
```

## Rules

- ALL changes go in ONE commit. Never split into multiple commits.
- `make til_core` then `make test`. That's it. Every time.
- Never run `make clean` during this workflow.
- Never edit bootstrap/ files manually.
- If `make test` fails, fix your code and repeat from step 1.
- Redirect build output to tmp/build.log, then Read/Grep that file.
