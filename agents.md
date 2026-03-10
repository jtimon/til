# Agent Instructions

## Testing

Always run `make test` and verify all tests pass before committing.

## Build & Run

- `make` — build bin/ctil
- `make test` — build + run all tests
- `bin/ctil run file.til` — compile and run via builder
- `bin/ctil interpret file.til` — run via interpreter
- Use `tmp/` dir for ad-hoc test files

## Issue Tracking

- Issues are tracked in `doc/issues.org`, not GitHub issues (no `gh` CLI)
- New issues go at the top, numbered from NEXT_ISSUE
- Fixed issues are moved to `doc/fixed.org`

## Commits

- Use `make test` before every commit
- Never run destructive git commands (revert, restore, stash, reset --hard, checkout -- files)
- NEVER look for excuses to reduce scope, skip changes, or defer work. If the user says to change something, CHANGE IT. Don't analyze whether it's "needed" or "used" — just do it. Stop wasting tokens on justifying why something doesn't need changing.
