# Plan: Fix self-hosted TIL compiler (til) to run empty.til

## Ultimate Goal
Either of these should work (whichever is easier to achieve):
- `./bin/til interpret src/examples/empty.til` (til_interpreted)
- `./bin/til run src/examples/empty.til` (til_compiled)

Currently only `./bin/rstil interpret` and `./bin/rstil run` work.

## Progress (2025-12-18)

### Fixed Bugs
- **Bug #43** (Fixed): Map.get returns wrong value when Map is field inside struct
  - Root cause: Nested struct field values not properly copied in interpreter
  - Fix: Added read_struct_primitive_fields to recursively read actual values

- **Bug #45** (Fixed): init.til uses invalid fallthrough switch syntax
  - Root cause: TIL doesn't support C-style switch fallthrough
  - Fix: Repeated switch case bodies for each FunctionType case

- **Bug #46** (Fixed): Catch blocks catching throws that come after them
  - Root cause: local_catch_labels populated with ALL catches at start
  - Fix: Remove catch from local_catch_labels after processing it

### Current Issue
**Bool.eq member resolution error**:
```
src/core/bool.til:92:92: type ERROR: struct 'Bool' has no member 'eq' c
```
- The trailing 'c' in the error message is suspicious
- Likely a translation issue in typer.til (TIL diverged from Rust)
- No more infinite loop - the self-hosted compiler now progresses further

## Compiler Phases
1. ~~Parser~~ ✓
2. ~~Init~~ ✓
3. **Typer** ← currently here (Bool.eq error)
4. Precomp
5. Scavenger
6. Eval/Interpreter → enables `til interpret`
7. Builder/Codegen → enables `til run`

## Milestones
1. `./bin/til interpret src/examples/empty.til` ← current target
2. `./bin/til interpret src/examples/hello_script.til` ← next

## Build Commands Reference (from Makefile)
- `make rstil` - Build Rust-based TIL compiler
- `make til` - Build self-hosted TIL compiler (uses rstil to compile til.til)
- `make tests` - Run full test suite

## Methodology for Each Issue Encountered

### Step 1: Identify the Issue
- If til hangs/fails, create a minimal test case isolating the problem
- Test with `timeout 10 ./bin/rstil interpret test.til`
- Test with `timeout 10 ./bin/rstil run test.til`

### Step 2: Determine Root Cause
**If run works but interpret fails** → Interpreter bug (interpreter.rs)
- The compiled code is correct, interpreter has a bug
- May be able to bypass by using compiled path instead

**If interpret works but run fails** → Codegen issue (precomp.rs, scavenger.rs, ccodegen.rs)
- Examine the generated C code in gen/c/
- Find the problematic pattern in the C code
- Locate the Rust codegen function that generates it

**If both fail the same way** → Possible TIL/Rust divergence
- Compare the relevant src/self/*.til with src/rs/*.rs
- Note function names that need re-translation (not line numbers)

### Step 3: Create Reproducing Test
- Create minimal test in `src/test/bugNN_test.til` that demonstrates the bug
- Verify it fails with `./bin/rstil run` (or interpret, depending on bug type)
- Add to `src/tests.til` in appropriate section (rs_common, rs_compiled, etc.)
- Expected output (.out) generated automatically for new tests

### Regenerating Test Outputs
When existing tests need updated expected output (e.g., error message changes):
- `./bin/rstil run src/tests.til regen src/test/sometest.til`

### Step 4: Document the Issue
- Add bug entry to `doc/todo/bugs.org`
- Use next number from `doc/todo/next_issue_num.txt`, then increment it
- Include: description, root cause, reproducing test path, related bugs

### Step 5: Fix the Issue
- Fix in the Rust code (src/rs/)
- Run `make tests` to verify

### Step 6: Port to TIL
- Copy the fix to equivalent src/self/*.til file
- Run `make tests` again to verify

### Step 7: Commit
- Commit the fix with clear message explaining what was fixed
- Continue to next issue

## Working Branch
Work on **master**. Previous branch `claude/fix-bool-return-error-VePQb` is reference only.

## Key Rules
- TIL code must match Rust code exactly
- Never diverge TIL from Rust to "fix" issues
- Each fix goes through: test → fix rs → make tests → port to til → make tests → commit
- Note function names to re-translate, not line numbers

## Next Steps
1. Investigate Bool.eq error in typer.til
2. Compare typer.til with typer.rs for member resolution logic
3. Fix divergence and test
