---
name: build
description: Build, test, and commit changes following the self-hosting bootstrap workflow
user-invocable: true
---

# Build workflow for til

Read doc/self.org for the bootstrap model and `make help` for targets.

Build policy is make.til, compiled to bin/make: `make <goal>` builds
that program and hands the goal to it, so `make test` and `bin/make
test` are the same build. Change a build step in make.til, not in the
Makefile, which now owns only the bootstrap (bin/til_boot and bin/make).

## Step 1: Build and test

```bash
systemd-run --user --scope -p MemoryMax=64G make test > tmp/build.log 2>&1
```

Then check results by reading tmp/build.log (use Read/Grep tools).

If tests fail, the bug is in YOUR changes. Fix and repeat.

## Step 2: ASAN check (optional)

```bash
systemd-run --user --scope -p MemoryMax=64G make test_asan > tmp/asan.log 2>&1
```

Runs all tests with bin/til_asan (AddressSanitizer). Detects memory leaks.

## Step 3: Commit

Include ALL modified files: .til, C, boot/, doc/totals.csv, img/totals.svg.

## Build model

Three-pass build: til_boot builds til, then til rebuilds itself.
All changes (.til and src/c/) take effect in a single commit.
Never split commits for bootstrap reasons.

## Rules

- Never edit boot/ files manually.
- If tests fail, fix your code and repeat.
- Redirect build output to tmp/build.log, then Read/Grep that file.
- Prefix documentation-only commits with "Doc: ".
