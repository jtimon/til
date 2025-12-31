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

- **Bug #55** (Fixed): C codegen wrong code for throwing calls inside struct literals
  - Root cause: hoist_throwing_args didn't process non-FCall arguments (like NamedArg)
  - Fix: Added else clause to call hoist_throwing_expr for non-FCall arguments
  - Test: src/test/bug55.til

- (Fixed 2025-12-27): Arena overflow caused by type mismatch
  - Root cause: init.til was storing `offset.to_str()` in `arena_index` (Map(Str, I64))
    but reading it as I64 directly. The Str bytes were being misinterpreted as I64.
  - Fix: Removed `.to_str()` calls in `declare_var`, `insert_var`, and `remove_var`
  - Also fixed `remove_var` to read I64 directly instead of Str then convert

- **Bug #59** (Fixed 2025-12-27): ForIn not desugared in self-hosted interpreter
  - Root cause: TIL's `Map.insert` throws `DuplicatedKeyError` on duplicate keys,
    while Rust's `HashMap.insert` overwrites. When init phase stored the original
    func_def, eval phase couldn't overwrite it with the precomp'd (desugared) version.
  - Fix: Changed `declare_func` in init.til to use `Map.set()` instead of `Map.insert()`
    to allow overwriting, matching Rust's behavior.

- (Fixed 2025-12-27): Map.insert vs Map.set throughout TIL codebase
  - Root cause: All Rust `HashMap.insert` calls overwrite, but TIL `Map.insert` throws
    `DuplicatedKeyError`. This caused silent failures when updating symbols/arena_index.
  - Fix: Changed all `Map.insert` and `.insert(key, value)` calls to `.set(key, value)`
    across builder.til, init.til, interpreter.til, eval_arena.til, ccodegen.til, parser.til.
  - Also removed all `catch (err: DuplicatedKeyError)` blocks since `.set()` doesn't throw.
  - Simplified `declare_var` to just `throws Str` (matching Rust's `Result<(), String>`).

### Current Focus (2025-12-31)
**Fix all til_interpreted tests first, then til_compiled**

Step 1: Get all rs_common tests working with `./bin/til interpret`.

Working tests (47/68):
- examples: empty, hello_cli, hello_lib, hello_liba, hello_pura, hello_pure, hello_script, hello_test, lolalalo
- tests: arenas, arithmetics, arrays, bools, branchless, bug41, bug46, bug48, bug57, c_mem,
  circular_test, clone, comparisons, constfold, cross_file_forward, deterministic, eval, exit,
  fibonacci, flow, func_purity, function_pointers, intro, literals, lists, loops, maps,
  mut_test, namespaces, parallel_cmd, pointers, return_value_usage, scope_isolation, sets,
  strings, u8, underscore, variadic

Failing tests (21/68) by category:

**Enum variant payload type 'unknown' not yet supported (4 tests)**
- bug56, editor_mode_test, enums, forward_declarations

**Segmentation fault (6 tests)**
- args, bug47, optional_args, test_parser, ufcs, til.til help

**Output mismatch (2 tests)**
- bug49 (different error count)
- bug50 (rstil vs til prefix)

**Other errors (9 tests)**
- bug43 - assert_eq wrong value (expected '0', found '2130832128')
- bug52 - concat: malloc failed
- bug55 - assert_eq_str: expected 'hello', found ''
- errors - string_from_context out of bounds
- modes - assert_eq failed: expected '0', found '65536'
- structs - assert_eq: expected '10', found garbage
- test_lexer - String range comparisons not yet supported
- undefined - concat: malloc failed (same as bug52)
- vecs - concat: malloc failed (same as bug52)

Phase 2: Once til_interpreted tests pass, fix til_compiled:
```bash
./bin/til run src/examples/empty.til  # Currently: "no body found for 'start.eq'"
```
This is a separate scavenger bug that doesn't affect rstil.

## Compiler Phases
1. ~~Parser~~ ✓
2. ~~Init~~ ✓
3. ~~Typer~~ ✓
4. ~~Precomp~~ ✓
5. Scavenger ← issues remain for some tests
6. ~~Eval/Interpreter~~ ✓ (38/68 tests working)
7. Builder/Codegen ← til_compiled not yet working

## Milestones
1. ~~`./bin/til interpret src/examples/empty.til`~~ ✓ DONE
2. ~~`./bin/til interpret src/examples/hello_script.til`~~ ✓ DONE
3. All til_interpreted tests pass ← current target (38/68 working, 56%)
4. `./bin/til run src/examples/empty.til` (scavenger bug)

## Build Commands Reference (from Makefile)
- `make rstil` - Build Rust-based TIL compiler
- `make til` - Build self-hosted TIL compiler (uses rstil to compile til.til)
- `make benchmark` - Run full test suite with timing

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
- Run `make benchmark` to verify

### Step 6: Port to TIL
- Copy the fix to equivalent src/self/*.til file
- Run `make benchmark` again to verify

### Step 7: Commit
- Commit the fix with clear message explaining what was fixed
- Continue to next issue

## Working Branch
Work on **master**. Previous branch `claude/fix-bool-return-error-VePQb` is reference only.

## Key Rules
- TIL code must match Rust code exactly
- Never diverge TIL from Rust to "fix" issues
- Each fix goes through: test → fix rs → make benchmark → port to til → make benchmark → commit
- Note function names to re-translate, not line numbers

## Next Steps
1. Pick a failing test from til_interpreted (see src/tests.til TODO comments)
2. Run: `timeout 30 ./bin/til interpret src/test/failing_test.til`
3. Identify error pattern and find root cause
4. Fix in Rust, run `make benchmark`, port to TIL, run `make benchmark`, commit
5. Repeat until all til_interpreted tests pass

## Test Management Methodology
When fixing bugs that affect multiple tests:

1. **Uncomment all potentially affected tests** - Remove `//` but keep the `// TODO:` comments
2. **Run `make track_benchmark`** - This runs all tests and saves timing data
3. **Analyze results** - Note which tests pass vs fail
4. **Update tests.til**:
   - For passing tests: Remove the TODO comment entirely
   - For failing tests: Comment out with `//` and update TODO with actual error message
   - Be specific: `// TODO: Source '10' not found` not just `// TODO: fails`
5. **Run `make track_benchmark` again** - Verify 0 failures before committing

This methodology ensures:
- We test everything that might be affected by a fix
- TODO comments accurately describe current errors
- We don't leave stale TODO comments on passing tests
- We can track progress by counting uncommented vs commented tests

## Debug Findings

### Key Discovery (2025-12-19)
Added `Expr.to_str()` method and debug prints to `get_value_type` in init.til.

The expression `self.ptr` at vec.til:63 is processed 3 times by get_value_type:
```
1st call: e.params = [Expr{Identifier("ptr"), ...}]  <- correct
2nd call: e.params = [Expr{Identifier("ptr"), ...}]  <- correct
3rd call: e.params = [Expr{NodeType.?, ...}]         <- CORRUPTED
```

**Critical insight**: The corruption is visible in `e.to_str()` BEFORE iterating.
This means corruption happens BETWEEN calls to get_value_type, not during Vec iteration.

### What Was Ruled Out
- Bug #52 (static buffer in ext.c) - fixed, but didn't solve Bug #47
- Bug #53 (missing null termination in str.til) - fixed, removed garbage chars but didn't solve Bug #47
- for-in loop vs while+Vec.get - both show same corruption

### Current Debug State
- Expr.to_str() added to parser.til for debugging
- Debug prints in init.til:get_value_type showing e and cursor on each call
- Debug prints in typer.til:check_types_with_context (NodeType.Identifier case)
- These are uncommitted (WIP) for continued investigation

### Narrowed Down Location (2025-12-19)
The corruption happens:
1. In `check_types_with_context` function in typer.til
2. Specifically in the `NodeType.Identifier(name)` case (lines 237-272)
3. Around the `lookup_symbol` call (lines 259-265)

Call tracing showed:
- get_value_type calls #477 and #478 share the same `params.ptr` (e.g., 109470453548416)
- Call #477 sees valid data: `self.ptr line=63`
- Call #478 sees corrupted data: `? line=26726118198`
- Corruption happens BETWEEN these calls, during check_types_with_context

### Debug Strategy
To find the exact line causing corruption:
1. Add debug print with `e.to_str()` after EVERY line in check_types_with_context
2. Run test once
3. Find where output changes from valid to corrupted
4. That line (or function called on that line) is the culprit
5. Drill into that function with more prints
6. Repeat until exact codegen bug found

### Previous Test (2025-12-19)
The original bug47.til was testing something different (static buffer issue
in ext.c's til_i64_to_str). That has been renamed to bug52.til.
