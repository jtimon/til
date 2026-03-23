---
name: build
description: Build, test, and commit changes following the self-hosting bootstrap workflow
user-invocable: true
---

# Build workflow for til

Read doc/self.org and run `make help` for context.

## Bootstrap does NOT constrain commit structure

til_boot is built entirely from HEAD (boot/ + src/c/ via git).
Completely isolated from uncommitted changes. bin/til is built from
ALL current sources (.til AND src/c/). Both .til and C changes take
effect immediately in bin/til.

The bootstrap NEVER forces you to split changes across multiple
commits. Commit structure is purely a matter of what makes sense for
the work. If you think you need multiple commits "for bootstrap
reasons", you are WRONG. Re-read doc/self.org.

## Step 1: Build and test

```bash
systemd-run --user --scope -p MemoryMax=64G make test > tmp/build.log 2>&1
```

Then check results by reading tmp/build.log (use Read/Grep tools).

If tests fail, the bug is in YOUR changes. Fix and repeat.

## Step 2: Commit

Include ALL modified files: .til, C, boot/, doc/totals.csv, img/totals.svg.

## Rules

- `make test` does everything (uses xvfb-run for GUI tests).
- `make test_nogui` skips GUI build tests (no xvfb needed).
- Remote agents: use `make test_nogui`.
- Never edit boot/ files manually.
- If tests fail, fix your code and repeat.
- Redirect build output to tmp/build.log, then Read/Grep that file.
