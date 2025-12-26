# Plan: Fix self-hosted TIL compiler (til) to run empty.til

## Ultimate Goal
Either of these should work (whichever is easier to achieve):
- `./bin/til interpret src/examples/empty.til` (til_interpreted)
- `./bin/til run src/examples/empty.til` (til_compiled)

Currently only `./bin/rstil interpret` and `./bin/rstil run` work.

## Progress (2025-12-26)

### Fixed Bugs
- **Bug #54** (Fixed): Pure functions that throw are not folded at compile time
  - Root cause: is_comptime_evaluable blocked all throwing functions
  - Fix: Only exclude AllocError/IndexOutOfBoundsError/KeyNotFoundError (runtime-dependent)
  - Part of major precomp overhaul - see doc/precomp.org

- **Bug #43** (Fixed): Map.get returns wrong value when Map is field inside struct
  - Root cause: Nested struct field values not properly copied in interpreter
  - Fix: Added read_struct_primitive_fields to recursively read actual values

- **Bug #45** (Fixed): init.til uses invalid fallthrough switch syntax
  - Root cause: TIL doesn't support C-style switch fallthrough
  - Fix: Repeated switch case bodies for each FunctionType case

- **Bug #46** (Fixed): Catch blocks catching throws that come after them
  - Root cause: local_catch_labels populated with ALL catches at start
  - Fix: Remove catch from local_catch_labels after processing it

- **Bug #42** (Fixed): Temp variable naming inconsistency in struct methods
  - Root cause: emit_struct_func_body didn't set current_function_name before emitting
  - Fix: Added save/set/restore pattern for current_function_name and mangling_counter

- **Bug #52** (Fixed): Static buffer in ext.c til_i64_to_str caused string corruption
  - Root cause: Multiple to_str() calls shared same static buffer
  - Fix: Allocate memory with malloc() instead of using static buffer

- **Bug #53** (Fixed): String functions missing null termination
  - Root cause: clone/concat/format/replace used malloc(cap) instead of malloc(cap+1)
  - Fix: Allocate +1 byte and null-terminate with memset
  - Note: No regression test - bug only manifests with fragmented heap

- **Code Quality**: Fixed empty AllocError and IndexOutOfBoundsError catches
  - Converted 61 empty catches to properly rethrow errors as Str
  - ext.til global init functions use panic() instead of throw
  - Added `throws Str` to 12 functions whose error paths now propagate

### Current Issue: Bug #47 - NOT FIXED

**Bug #47**: NodeType.? memory corruption / use-after-free / infinite loop
- Root cause: TIL's Vec shallow copy (copies ptr, not data) differs from Rust's deep clone
- Every `.clone()` in Rust must have corresponding `.clone()` in TIL

**Symptoms**:
- `timeout 30 ./bin/rstil run src/test/bug47_test.til` - times out (infinite loop)
- Infinite loop occurs in **precomp phase**, in `precomp_expr` or `precomp_fcall`

**Clone Analysis Progress** (2025-12-26):
| File          | Rust | TIL | Status     |
|---------------|------|-----|------------|
| eval_arena    |   33 |  33 | DONE       |
| typer         |   71 |   5 | 66 missing |
| interpreter   |  121 |  69 | 52 missing |
| precomp       |   78 |  30 | 48 missing |
| init          |   51 |  29 | 22 missing |
| scavenger     |   21 |   3 | 18 missing |

**Work done**:
- eval_arena.til: All 33 clones matched 1:1 with Rust
- Added `clone_value_type()` function to parser.til for ValueType enum cloning
- Removed all DEBUG println statements from self-hosted compiler files

**Next**: Continue systematic clone matching in remaining 5 files

## Compiler Phases
1. ~~Parser~~ ✓
2. ~~Init~~ ✓
3. Typer
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

**Note**: Use `./bin/rstil run src/til.til ...` for testing (compiles til.til first, ensures up-to-date).
Avoid `./bin/rstil interpret src/til.til ...` - it's too slow for practical use.

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
1. Investigate hang - identify which phase/function causes infinite loop
2. Follow methodology to debug and fix
