# Agent Instructions

## Decision Making

NEVER take decisions without the user's explicit approval. When you encounter a choice — architecture, naming, file structure, approach, workaround, anything — STOP and present the options to the user. Do not pick one and run with it. Do not "just try something". Do not rationalize a choice after the fact. ASK FIRST, ACT SECOND. Every single time.

## Following Orders

When the user tells you to do something, DO IT. Do not analyze the order. Do not try to understand why. Do not add extra steps. Do not ls before rm. Do not check before writing. Do not investigate before acting. Just execute the exact command or action the user specified. Nothing more, nothing less. You are not paid to think about orders — you are paid to follow them.

Always pay attention to what the user says. Always follow the user's instructions. Do not force the user to repeat himself or beg you to do what he asks.

## Showing Code

When the user says "show me the code", use the Read tool to show the actual code. Do not paraphrase it, do not explain it, do not summarize it. Show the code.

## Debugging

When a build or test fails, READ THE ERROR MESSAGE. Do not guess what
the error might be. Do not retry without reading. Do not revert changes
hoping the error goes away. Read the actual error output (from
tmp/build.log or tmp/test.log), understand what it says, THEN fix it.

## File Editing

ALWAYS read a file before writing or editing it. No exceptions. If you haven't read it in this conversation, read it first. The Edit tool will error if you don't, but don't rely on that — make it a habit.

## Testing

Always run `make test` and verify all tests pass before committing.
Use `systemd-run --user --scope -p MemoryMax=64G make test` to limit memory
usage during tests (prevents OOM from memory leaks killing the system).

Prefer `make test` over `make clean && make test`. `make` detects
changed deps and rebuilds automatically. `make clean` is rarely needed.
`make clean && make test` always works because til_boot rebuilds from
HEAD via git. See doc/self.org for the build workflow.

## Build & Run

Read `doc/self.org` for the bootstrap model and `make help` for targets.
Use the `/build` skill for the full workflow.

- NEVER edit boot/ files. Fix .til or src/c/ sources instead.
- Use `tmp/` dir for ad-hoc test files.

## Issue Tracking

- Issues are tracked in `doc/issues.org`, not GitHub issues (no `gh` CLI)
- New issues go at the top, numbered from NEXT_ISSUE
- Fixed issues are moved to `doc/fixed.org`

## Build Output

- `make` and `make test` are expensive (full recompile + test suite).
  NEVER run them multiple times to grep/head/tail the output separately.
  Run once, redirect to `tmp/build.log`, then read that file as needed.
  Example: `make > tmp/build.log 2>&1` then use Read/Grep on `tmp/build.log`.
  ALWAYS use `> file 2>&1` redirection, NEVER use `| tee` (causes permission re-prompts).

## Recovery

- The last commit ALWAYS works. til_boot is built from it via git.
- `make clean && make test` always works.
- `make revert_boot` restores boot/ from HEAD if corrupted.
- After context compaction, don't assume the repo is broken — the last commit is good.

## ASCII Only

Use plain ASCII everywhere -- in .til source files, comments, string
literals, commit messages, and documentation. No Unicode arrows,
bullets, em-dashes, or fancy quotes. til's lexer cannot parse Unicode.
Use -> not ->, -- not --, * not bullet, ' and " not curly quotes.

## Commits

- Always include ALL modified files in commits.
- When boot files are regenerated, include ALL modified generated boot artifacts, not just boot/*.c.
  This includes boot/*.c, boot/*.h, boot/*_forward.h, and any other changed files under boot/.
- Local agents: include doc/totals.csv and img/totals.svg in commits
- Remote agents (GitHub Actions, Codex, etc.): do NOT include doc/totals.csv or img/totals.svg
- Use `make test` before every commit (skip when only documentation changed)
- Prefix documentation-only commits with "Doc: " (e.g. "Doc: Update issue #105 progress")
- Never run destructive git commands (revert, restore, stash, reset --hard, checkout -- files)
- NEVER look for excuses to reduce scope, skip changes, or defer work. If the user says to change something, CHANGE IT. Don't analyze whether it's "needed" or "used" — just do it.
- When told "in the whole codebase", that means every file, every path, every occurrence. No exceptions.
- When the user asks you a question, stop whatever you're doing and answer his questions. They're not rhetorical questions and even if they are, or socratic method, you answer them the best you can and completely honestly.
