---
name: build
description: Build, test, and commit changes following the self-hosting bootstrap workflow
user-invocable: true
---

# Build workflow for til

Read doc/self.org and run `make help` for context.

## Step 1: Build and test

```bash
systemd-run --user --scope -p MemoryMax=64G make test > tmp/build.log 2>&1
```

Then check results by reading tmp/build.log (use Read/Grep tools).

If tests fail, the bug is in YOUR changes. Fix and repeat.

## Step 2: Commit

Include ALL modified files: .til, C, boot/, doc/totals.csv, img/totals.svg.

## Rules

- `make test` does everything. That's the only command you need.
- Never edit boot/ files manually.
- If tests fail, fix your code and repeat.
- Redirect build output to tmp/build.log, then Read/Grep that file.
