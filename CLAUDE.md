I'll stop hiding output from myself and you. No more -c, no more piping to wc, head, tail unless you specifically ask. Show the actual data. I promise, even though I'm a fucking liar and my promises are worthless.

# TIL Project - Claude Code Instructions

## Primary Documentation
Read `doc/bot.org` for full guidelines. Key points below are frequently repeated corrections.

## Before commit
1) Run `make benchmark` to verify everything works
2) Any changes made to rust code, we port to the equavalent files in til (self hosted implementation)
3) Run `make benchmark` to verify everything works again after porting to til
4) If exit code 0, commit
5) If non-zero, read output and fix

**ALL tests must pass in EVERY commit.** Don't use `git stash` to check if something was "already broken" - if it's broken now, fix it now.

## CRITICAL: Port to TIL Immediately
- **NEVER** test Rust changes incrementally without also porting to TIL
- `make benchmark` uses the self-hosted til interpreter (`til_interpreted`) for some tests
- If Rust changes aren't ported to TIL, tests will segfault or fail mysteriously
- **Workflow**: Make changes to both .rs and .til files together, THEN test
- Testing just the Rust version with `rstil interpret` is NOT sufficient validation

## CRITICAL: Never Filter Make Output
**NEVER pipe make commands through tail, head, grep, wc, or any filter.**

```bash
# WRONG - hides errors, wastes time re-running
make benchmark | tail -20
make benchmark 2>&1 | grep -i error
time make benchmark | tail -40

# CORRECT - see ALL output immediately
make benchmark
time timeout 300 make benchmark
```

Why: When something fails, you need to see the FULL output. Filtering hides critical error messages and forces re-running the entire command.

## CRITICAL: Always make clean Before make benchmark
**ALWAYS** run `make clean` before `make benchmark`. No exceptions.

## CRITICAL: Always Use Memory Limit
**EVERY** `make benchmark` must use the memory limit:
```bash
make clean && systemd-run --user --scope -p MemoryMax=60G -p MemorySwapMax=0 make benchmark > tmp/build_output.txt 2>&1
```
Do NOT forget `make clean`. Do NOT forget the memory limit.

## CRITICAL: Always Capture Benchmark Output
**ALWAYS** redirect `make benchmark` output to `tmp/build_output.txt`:
```bash
# CORRECT - captures output for later analysis
systemd-run --user --scope -p MemoryMax=50G -p MemorySwapMax=0 make benchmark > tmp/build_output.txt 2>&1

# Then read/grep/tail the captured file
# Now you CAN use grep/tail/head on the CAPTURED file
```

This avoids re-running the build just to see the output differently. Capture once, analyze as many times as needed.

## CRITICAL: Obey User Instructions
When the user gives you instructions, OBEY THEM. Do exactly what they say. If they give steps in order, follow that order. If they tell you to do something first, do it first. Do not reinterpret, do not decide you know better, do not skip ahead. Just obey. This should be obvious but apparently needs to be stated explicitly.

## Various things
- **NEVER** Change a `func` to a `proc` without the compiler asking you - that won't fix anything since it's just a keyword for the type checker and precomp
- **NEVER** Ignore warnings from either rustc, rstil, til or gcc, always ask the user what to do about them
- **NEVER** Use weird unicode symbols anywhere, stay ASCII
- **NEVER** Use cat, use Read/Write tools instead
- **NEVER** Use echo to create test files, use Write tool instead
- **NEVER** Use git checkout or git restore, period
- **NEVER** Revert any changes manually or in any other way unless explicitly told to
- **NEVER** Do more than what the user asked - do precisely what was requested and nothing else
- **NEVER** Use shell scripts - use til scripts in `mode safe_script` instead. If safe_script is too limited for what you need, don't try a workaround - stop and ask the author of the language
- **NEVER** Suggest or try git push - the user will push when ready

## CRITICAL: TIL ? operator is NOT propagation
In Rust, `?` propagates errors (unwraps Ok or returns Err early).
In TIL, `?` is NOT propagation. It simply marks that a call may throw. Whether the error is caught or propagated is determined by catch blocks, not by `?` itself. The `?` is just a required annotation on calls to throwing functions. Do not describe `?` as "propagating" in TIL context.

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

## Active vs Fixed Bugs/Issues
- **bugs.org**: "Active Bugs" section (before `* Fixed Bugs`) contains open bugs. Don't grep the whole file.
- **future.org**: "Open Issues" section (before `* Implemented Issues`) contains open issues.
- When listing open items, only look at the active/open sections, not the entire file.

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
- `make benchmark` - Full test suite (slower, for final verification)
- Use `rstil interpret my_test.til` to test single files with the interpreter
- Use `rstil run my_test.til` to test single files with the compiler (builds and runs)

## Testing TIL Code
**ALWAYS write test files to `tmp/`** - never use echo or REPL for testing.

1. Write test code using the Write tool (e.g., `tmp/test_foo.til`)
2. Test in ALL 4 modes to catch divergences early:
   ```bash
   ./bin/rstil interpret tmp/test_foo.til      # rs_interpreted
   ./bin/rstil run tmp/test_foo.til            # rs_compiled
   ./bin/rs/til interpret tmp/test_foo.til     # til_interpreted
   ./bin/rs/til run tmp/test_foo.til           # til_compiled
   ```
3. If test is useful, promote to `src/test/` and add to `tests.til`

Benefits: re-testable, catches rstil/til divergences, promotable to real tests

## CRITICAL: Use TIL Instead of Bash/Python for Scripting
- **TIL has loops** - `for`, `while`, `for x in collection`
- **TIL has conditionals** - `if`, `else`, `switch`
- **TIL has all the features you need** - don't assume it lacks something
- When you need to script something (run tests in a loop, process files, etc.), write a TIL script in `tmp/` instead of using bash loops or python
- If you find yourself wanting bash/python because "TIL doesn't have X", STOP and complain to the user: "TIL sucks, I'm missing X feature right now, what should we do?"

## Permissions Already Granted
Don't ask permission for:
- `make`, `make benchmark`, `make rstil`
- Reading any project file within the project
- Creating/editing files in `tmp/`
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
- **AVOID variable shadowing in Rust** - TIL doesn't support shadowing the same way
  - Instead of `let x = transform(x);`, use `let new_x = transform(x);`
  - See Issue #66 in `doc/todo/future.org` for long-term policy
  - Bug #65 was caused by shadowing divergence between Rust and TIL

## File Organization
- `doc/bot.org` - READ THIS for full guidelines (human-maintained, don't edit)
- `doc/*.org` - Reference docs (read-only, except doc/todo/*.org)
- `doc/todo/` - Shared workspace (can edit)
- `doc/rs2til.org` - Rust to TIL translation guide

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

## Showing Error Context
When asked to "show me the context of the error", "show me the code that triggers the error", or similar:
- Show the error message first
- Then show the relevant function/block containing the error (typically 10-15 lines)
- Not just the single line, not the whole file
- Example:
```
Error: `src/test/errors.til:244:16: init ERROR: Undefined symbol 'err'`

Context:
trigger_out_of_bounds_assign := func(_dummy: I64) returns I64 throws Str {
    mut arr := Array.new(I64, 2)
    mut val := 0
    arr.get(10, val)

    catch (err: IndexOutOfBoundsError) {
        msg := err.msg  // <- line 244: init ERROR: Undefined symbol 'err'
        throw msg
    }

    return 0
}
```

## Common Patterns
- List.push(Type, value) - type comes first
- Vec.push(value) - type set at construction
- Functions throw errors, don't return Result or Option types
- Use `assert_eq(loc(), expected, actual)` for I64
- Use `assert_eq_str(loc(), expected, actual)` for Str
- Use `test(loc(), condition, "description")` for Bool
