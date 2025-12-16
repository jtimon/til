# TIL Project - Claude Code Instructions

## Primary Documentation
Read `doc/bot.org` for full guidelines. Key points below are frequently repeated corrections.

## Before commit
1) Run `make tests` to verify everything works
2) Any changes made to rust code, we port to the equavalent files in til (self hosted implementation)
3) Run `make tests` to verify everything works again after porting to til
4) If exit code 0, commit
5) If non-zero, read output and fix

## Various things
- **ALWAYS** When running "make tests", run as normal: no wc, no head, no tail, no grep, no any other bullshit
- **NEVER** Use weird unicode symbols anywhere, stay ASCII
- **NEVER** Use cat, use read, write or echo instead
- **NEVER** Use git checkout or git restore, always ask the user before reverting big chunks of work that could be valuable

## CRITICAL: Stay Within Project Directory
- **NEVER** create or read files outside the project directory
- **NEVER** use /tmp or any path outside this project
- All temporary files go in `tmp/` (already gitignored)
- All work must stay within the project boundaries

## Issue Numbering System - IMPORTANT
This is shared across ALL tracking documents (bugs.org, dry.org, etc.)
1. **ALWAYS** read `doc/todo/next_issue_num.txt` first
2. Use that exact number for new bug/issue
3. Increment and write back to file immediately
4. Never reuse numbers, even for closed issues
5. File location: `doc/todo/next_issue_num.txt` (NOT in `doc/`)

## Catch Block Style
**DO NOT** put catch blocks after every statement. Put them at the END of functions.

```til
// WRONG - Don't do this
test_something := proc() {
    do_thing_1()
    catch (err: SomeError) { ... }

    do_thing_2()
    catch (err: SomeError) { ... }
}

// CORRECT - Do this
test_something := proc() {
    do_thing_1()
    do_thing_2()

    // All catches at the end
    catch (err: SomeError) {
        println("ERROR:", loc(), "SomeError:", err.msg)
        exit(1)
    }
}
```

## Test File Locations
Don't ask where tests go - they're organized by collection type:
- Vec tests: `src/test/vecs.til`
- List tests: `src/test/lists.til`
- Map tests: `src/test/maps.til`
- Array tests: `src/test/arrays.til`
- Temporary/debug: `tmp/` or `src/test/temporary_tests.til`

## Build Commands
- `make rstil` or `make` - Fast build, just compile rstil
- `make tests` - Full test suite (slower, for final verification)
- Use `rstil interpret my_test.til` to test single files with the interpreter
- Use `rstil run my_test.til` to test single files with the compiler (builds and runs)
- use `rstil repl` (using echo, not cat) for fast doubts about til syntax and functionality (call exit(0) at the end to quit the repl cli)

## Permissions Already Granted
Don't ask permission for:
- `make`, `make tests`, `make rstil`, `rustc`
- `python3`, `python` - running any Python scripts within the project
- `git status`, `git log`, `git diff`, `git add`, `git commit`
- `timeout N ./bin/rstil file.til`
- Reading any project file within the project
- Creating/editing files in `tmp/` or `doc/bot/`
- **Shell commands within project - FULL FREEDOM:**
  - ALL standard Unix commands: `cd`, `mv`, `cp`, `rm`, `mkdir`, `chmod`, `ls`, `pwd`, `echo`, `printf`
  - Text processing: `sed`, `awk`, `grep`, `find`, `cat`, `head`, `tail`, `sort`, `uniq`, `wc`, `tr`, `cut`
  - File operations: create temp files, move files, copy files, remove files
  - Combine commands freely (pipes, redirects, command chaining with `&&` or `;`)
  - Use relative paths from project root or absolute paths within project
  - No need to ask permission for ANY shell operation within project directory
  - Only restriction: stay within project directory (no /tmp, no ~/)
- **Running Python scripts within the project - FULL FREEDOM:**
  - Any Python code that operates only on files within the project
  - No need to ask permission - just run it
- Removing `.backup` files

## Never Allowed - Must Ask/Warn First
- Modifying `doc/*.org` files (human-maintained, except doc/todo/*.org)
- `git push` to remote
- Git force operations (`push --force`, `reset --hard`, etc.)
- Deleting tracked files outside tmp/ directories
- Commands with `sudo` or elevated privileges

## Context-Dependent - Ask First
- Creating new files in `src/core/` or `src/test/` (outside tmp/)
- Modifying build system files (Makefile, Cargo.toml, etc.)
- Large refactorings affecting many files

## Documentation Updates
**BEFORE every commit**: Update relevant documentation if we fixed/changed anything
- Fixed a bug? Update `doc/todo/bugs.org` with fix details
- Changed behavior? Update design docs
- Added feature? Update relevant docs
- Even partial fixes should be documented

## Rust to TIL Porting Rules
When porting code from Rust (`src/rs/`) to TIL (`src/self/`):
- **Use the SAME names** - Rust names take priority over perceived TIL naming conventions
- **Use the SAME comments** - copy comments verbatim
- **Don't assume TIL lacks features** - if unsure, ask
- **Don't add workarounds** - TIL has the same capabilities as Rust for this codebase
- The goal is that both versions should be as close as possible, differing only in syntax

## File Organization
- `doc/bot.org` - READ THIS for full guidelines (human-maintained, don't edit)
- `doc/bot/` - Your workspace (full freedom to create/edit)
- `doc/*.org` - Reference docs (read-only, except doc/todo/*.org)
- `doc/todo/` - Shared workspace (can edit)
- `doc/translate_rs2til.org` - Rust to TIL translation guide

## Task Naming Convention
**NEVER use "Phase 1", "Phase 2", etc.** - This conflicts with compiler/interpreter phases.

Use descriptive names instead:
- ✅ "Refactor field registration"
- ✅ "Remove map_instance_fields calls"
- ✅ "Add offset calculation helpers"
- ❌ "Phase 1", "Phase 2" (confusing - what phase?)

The word "phase" is reserved for:
- Parser phase
- Type checker phase
- Interpreter phase
- Compiler phase

For multi-step tasks, use:
- "Step 1: Add helpers", "Step 2: Refactor getters", etc.
- Or just descriptive task names in todos

## Common Patterns
- List.push(Type, value) - type comes first
- Vec.push(value) - type set at construction
- Functions throw errors, don't return Result or Option types
- Use `assert_eq(loc(), expected, actual)` for I64
- Use `assert_eq_str(loc(), expected, actual)` for Str
- Use `test(loc(), condition, "description")` for Bool
