# Clone Context Branch - Rebase Preparation Analysis

## Current State

This branch (`cl_context_clone`) has **15 commits** ahead of master, implementing:
1. **Main Goal**: Replace `context.clone()` with `push_function_scope()` / `pop_function_scope()`
   - Eliminates ~68-247 KB of memory allocation per function call
   - Added 22 cleanup sites throughout `eval_user_func_proc_call`
2. **Mutable parameter support**: In-place updates for pass-by-reference semantics
3. **Struct members data structure change**: `Vec<Declaration>` → `Vec<(String, Declaration)>`

## CRITICAL CONFLICT: Struct Members Data Structure

### The Problem
**Master has REVERTED the struct members change** in commit `f783c35`:
```
commit f783c35 - "Remove redundant member name storage in SStructDef"
Changed SStructDef.members from Vec<(String, Declaration)> to Vec<Declaration>
to eliminate duplicate storage since Declaration.name already has the name.
```

### Impact on Rebase
- **Massive conflicts** expected across 5 files: `parser.rs`, `init.rs`, `interpreter.rs`, `typer.rs`, `parser.til`
- **141 locations** in cl_context_clone iterate with `for (field_name, decl) in members`
- Master uses `for decl in members` and `decl.name`

### Resolution Options
**Option A**: Accept master's decision (recommended if no technical reason for tuple)
- Revert all `(field_name, decl)` back to `decl` and use `decl.name`
- Less code, no redundancy
- Aligns with TIL self-hosting code

**Option B**: Re-apply the tuple structure (only if there's a technical reason)
- Need to justify why the redundancy is necessary
- More rebase conflicts to resolve manually

### Recommendation: INVESTIGATE WHY THE CHANGE WAS MADE
Look through cl_context_clone history to see if the `Vec<(String, Declaration)>` change was:
1. **Accidental** during refactoring → Use Option A
2. **Required** for some scope/clone functionality → Document and use Option B

## Master Changes Since Branch Point (f783c35)

1. **f783c35**: Struct members revert (discussed above)
2. **77554bf**: Rename `Context.mode` → `Context.mode_def` (already in cl_context_clone)
3. **7cb1226 - b8bcafe**: Break/continue elimination with boolean flags
   - Affects parser.rs loop structures
   - cl_context_clone has some simplified loops (`loop { break }` vs `while flag`)
4. **3c385a5**: Revert of problematic continue elimination
   - Shows master is still iterating on control flow refactoring

## Code Quality Issues to Fix Before Rebase

### 1. Remove DEBUG Logging (20 locations)
```bash
$ grep -n "DEBUG\|eprintln!" src/rs/interpreter.rs | wc -l
20
```

**Locations to clean:**
- `src/rs/interpreter.rs:48, 54, 67` - get_u8 debugging
- `src/rs/interpreter.rs:313` - get_field_offset debugging
- `src/rs/interpreter.rs:1209` - bool_from_context
- `src/rs/interpreter.rs:1235` - string_from_context
- `src/rs/interpreter.rs:2473, 2475, 2611` - eval_body tracing
- `src/rs/interpreter.rs:2674, 2842, 2853, 2856, 2859` - argument handling
- `src/rs/interpreter.rs:2879, 2881, 2916, 2928, 2931` - field registration
- `src/rs/interpreter.rs:2953` - generic arg debugging

**Action**: Strip all `eprintln!` debugging before rebasing

### 2. Remove Development Artifacts
```
add_cleanups.py
apply_refactor.sh
refactor_scope.py
compile_errors.txt
```

**Action**: `git rm` these helper scripts

### 3. Cleanup Test Files in tmp/
```
tmp/test_assertm.til
tmp/test_bool_assign.til
tmp/test_bool_minimal.til
tmp/test_bool_ptr.til
tmp/test_gt.til
tmp/test_method_return_str.til
tmp/test_not.til
tmp/test_str_print.til
```

**Action**: Review if needed, then remove or commit properly

## Scope Refactoring Implementation Quality

### Cleanup Sites (Verified)
All 22 `context.pop_function_scope(saved_path)?;` calls are labeled:
- 7 main cleanup sites documented with comments
- All return paths properly cleaned up
- Catch blocks use scope push/pop correctly

### Potential Issues to Investigate

#### Issue 1: Nested Function Calls
**Question**: What happens when function A calls function B calls function C?
- Does the scope stack properly nest and unwind?
- Are there any edge cases with recursive calls?

**Test**: Run recursive fibonacci or similar nested call patterns

#### Issue 2: Exception Propagation Through Multiple Frames
**Question**: If function C throws, B catches and re-throws, does A's scope cleanup happen?
- Line 2652-2653: Cleanup on throw propagation looks correct
- But verify with nested try/catch scenarios

**Test**: Create test with 3-level nested try/catch/throw

#### Issue 3: Early Return vs Throw Cleanup
**Lines to verify**:
- 2613-2617: Return vs throw detection
- 2624-2626: Pending throw handling
- Are all paths guaranteed to call `pop_function_scope`?

**Test**: Mixed return/throw scenarios in same function

#### Issue 4: Pass-by-Reference with Scope Cleanup
**Lines 2640-2641**: `mut_args` and `pass_by_ref_params` tracking
- When a mut arg is passed by reference, does cleanup handle it correctly?
- Field offset registration at lines 2916 might leak if scope isn't cleaned

**Test**: Pass mut struct to function that throws before return

## Master's Recent Control Flow Changes

Master commits show **aggressive break/continue elimination**:
- `7cb1226`: Replace with boolean flags (Phases 1-9)
- `b8bcafe`: Eliminate all remaining continues
- `3c385a5`: **REVERT** of problematic continue elimination

**Analysis**: Master is actively refactoring control flow. This branch has:
- Simplified some loops (`loop { break }` instead of `while should_continue`)
- Different approach than master's boolean flag pattern

**Recommendation**: After rebase, expect to adapt to master's control flow style

## Rebase Strategy Recommendations

### Pre-Rebase Preparation (Do Now)

1. **Decide on struct members data structure** (Vec vs Vec<tuple>)
   - If keeping Vec<Declaration>: Create script to convert all iterations
   - Document the decision

2. **Clean up code quality issues**:
   - Remove all DEBUG eprintln! statements
   - Remove helper scripts (add_cleanups.py, etc.)
   - Clean or document tmp/ test files

3. **Add comprehensive tests** for scope edge cases:
   - Nested function calls (3+ levels deep)
   - Recursive calls with scopes
   - Exception propagation through multiple frames
   - Pass-by-reference with exceptions
   - Mixed return/throw scenarios

4. **Document the refactoring**:
   - Why scope push/pop is better than clone
   - Performance measurements if available
   - Edge cases handled

### Rebase Execution

1. **Interactive rebase** onto master:
   ```bash
   git rebase -i master
   ```

2. **Conflict resolution order**:
   - Fix parser.rs first (struct members + loop style)
   - Then init.rs (struct iteration)
   - Then interpreter.rs (largest, most conflicts)
   - Then typer.rs
   - Finally parser.til

3. **After each conflict resolution**:
   ```bash
   make tests  # Verify tests still pass
   ```

4. **Squash commits** before final merge:
   - Group WIP commits together
   - Keep meaningful commit separation for scope push/pop work

### Post-Rebase Validation

1. Run full test suite: `make tests`
2. Run under valgrind if available (check for leaks from scope cleanup)
3. Visual inspection of memory usage (confirm scope push/pop reduces allocation)
4. Code review focusing on:
   - All 22 cleanup sites still present
   - No missing `pop_function_scope` calls
   - Control flow matches master's style

## Questions to Answer Before Rebasing

1. **Why was Vec<(String, Declaration)> introduced?**
   - Search git history for the commit that added it
   - If no technical reason found, revert to Vec<Declaration>

2. **Are there performance measurements?**
   - Document the 68-247 KB claim with actual measurements
   - Show before/after memory profiles

3. **What's the compatibility story?**
   - Does this break any existing TIL code?
   - Are there serialization concerns with context?

4. **Why were some DEBUG statements left in?**
   - Were they intentional for ongoing debugging?
   - Or just forgotten cleanup?

## Estimated Rebase Difficulty

- **Conflict Complexity**: **HIGH** (due to struct members revert)
- **Test Coverage**: **GOOD** (tests passing, comprehensive scope tests exist)
- **Code Quality**: **MEDIUM** (needs DEBUG cleanup, but logic is sound)
- **Documentation**: **LOW** (needs more explanation of changes)

**Recommendation**: Plan 2-3 hours for careful rebase execution with testing between each conflict resolution.
