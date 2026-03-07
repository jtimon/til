# Agent Instructions

## Testing

Always run `make test` and verify all tests pass before committing.

## Build & Run

- `make` — build bin/ctil
- `make test` — build + run all tests
- `bin/ctil run file.til` — compile and run via ccodegen
- `bin/ctil interpret file.til` — run via interpreter
- Use `tmp/` dir for ad-hoc test files

## Issue Tracking

- Issues are tracked in `doc/issues.org`, not GitHub issues (no `gh` CLI)
- New issues go at the top, numbered from NEXT_ISSUE
- Fixed issues are moved to `doc/fixed.org`

## Commits

- Use `make test` before every commit
- Never run destructive git commands (revert, restore, stash, reset --hard, checkout -- files)
