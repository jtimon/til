# Pre-Rebase Checklist for cl_context_clone

## Summary
- **Branch point**: commit `a07ff67` (Nov 19)
- **Master is ahead by**: 14 commits
- **Branch is ahead by**: 15 commits
- **Critical conflict**: Struct members data structure (`Vec<(String, Declaration)>` vs `Vec<Declaration>`)

## Immediate Actions Required

### 1. Remove DEBUG Logging (REQUIRED)
```bash
# Remove all eprintln! debug statements
sed -i '/DEBUG\|eprintln!/d' src/rs/interpreter.rs
```

**Manual review needed** - some eprintln! might be on multi-line statements

Affected lines in `src/rs/interpreter.rs`:
- 48, 54, 67 (get_u8)
- 313 (get_field_offset)
- 1209 (bool_from_context)
- 1235 (string_from_context)
- 2473, 2475, 2611 (eval_body)
- 2674, 2842, 2853, 2856, 2859 (argument handling)
- 2879, 2881, 2916, 2928, 2931 (field registration)
- 2953 (generic arg)

### 2. Remove Development Scripts (REQUIRED)
```bash
cd /home/jt/sync/data_common/code/jt/cl_context_clone
git rm add_cleanups.py apply_refactor.sh refactor_scope.py compile_errors.txt
git commit -m "Remove development helper scripts"
```

### 3. Handle tmp/ Test Files (REVIEW)
Either commit properly or remove:
```bash
git add tmp/*.til && git commit -m "Add scope refactoring test cases"
# OR
git clean -f tmp/
```

Files:
- tmp/test_assertm.til
- tmp/test_bool_assign.til
- tmp/test_bool_minimal.til
- tmp/test_bool_ptr.til
- tmp/test_gt.til
- tmp/test_method_return_str.til
- tmp/test_not.til
- tmp/test_str_print.til

## Understanding the Struct Members Conflict

### History
1. **Before Nov 7**: `HashMap<String, Declaration>` (unordered)
2. **Commit 940b243** (Nov 7): Changed to `Vec<(String, Declaration)>` for ordering
3. **Commit f783c35** (Nov 20, **in master**): Simplified to `Vec<Declaration>` (removed redundant String)

### Why cl_context_clone Has Tuples
The branch diverged at `a07ff67` (Nov 19), which is AFTER 940b243 but BEFORE f783c35.
So we inherited the tuple structure, but master has since simplified it.

### Impact: 14 Iteration Sites Need Changing
```bash
# Current (cl_context_clone):
for (field_name, decl) in &struct_def.members {
    // use field_name and decl
}

# After rebase (master style):
for decl in &struct_def.members {
    let field_name = &decl.name;  // if needed
    // use field_name and decl
}
```

**Locations** (14 total):
- src/rs/interpreter.rs: 7 sites
- src/rs/init.rs: 5 sites
- src/rs/typer.rs: ~2 sites (estimated)

### Automated Conversion Patterns

**Pattern 1**: Simple tuple destructuring with both used
```rust
// Before:
for (member_name, decl) in &struct_def.members {
    format!("{}.{}", base, member_name)
}

// After:
for decl in &struct_def.members {
    format!("{}.{}", base, decl.name)
}
```

**Pattern 2**: Tuple with unused name (already compatible!)
```rust
// These are fine as-is, just remove the tuple:
for (_, decl) in &struct_def.members { }  →  for decl in &struct_def.members { }
for (_member_name, decl) in &struct_def.members { }  →  for decl in &struct_def.members { }
```

**Pattern 3**: Name stored in local variable
```rust
// Before:
for (field_name, decl) in &struct_def.members {
    let combined = format!("{}.{}", base, field_name);
}

// After:
for decl in &struct_def.members {
    let combined = format!("{}.{}", base, decl.name);
}
```

## Testing Edge Cases Before Rebase

Create tests for potential scope cleanup issues:

### Test 1: Deep Nesting
```til
// File: tmp/test_scope_nesting.til
func level3() returns I64 { return 3 }
func level2() returns I64 { return level3() + 2 }
func level1() returns I64 { return level2() + 1 }
assert(level1().eq(6), "Deep nesting failed")
```

### Test 2: Exception Through Multiple Frames
```til
// File: tmp/test_scope_exception.til
func throws_error() throws Str { throw "error from level 3" }
func catches_and_rethrows() throws Str {
    try {
        throws_error()
    } catch err: Str {
        throw format("wrapped: ", err)
    }
}
func top_level() returns Str {
    try {
        catches_and_rethrows()
        return "should not reach"
    } catch e: Str {
        return e
    }
}
assert(top_level().eq("wrapped: error from level 3"), "Multi-frame exception failed")
```

### Test 3: Pass-by-Reference with Exception
```til
// File: tmp/test_scope_mut_exception.til
func modifies_then_throws(mut s: Str) throws Str {
    // Modify the struct
    s = "modified"
    // Then throw before return
    throw "error after modification"
}

func test_mut_exception() returns I64 {
    mut my_str := "original"
    try {
        modifies_then_throws(my_str)
    } catch e: Str {
        // Check that scope was cleaned up properly
        return 1
    }
    return 0
}
assert(test_mut_exception().eq(1), "Mut exception handling failed")
```

Run these:
```bash
./bin/rstil tmp/test_scope_nesting.til
./bin/rstil tmp/test_scope_exception.til
./bin/rstil tmp/test_scope_mut_exception.til
```

## Rebase Execution Plan

### Phase 1: Pre-Rebase Cleanup (30 min)
1. ✅ Remove DEBUG statements
2. ✅ Remove development scripts
3. ✅ Run full test suite: `make tests`
4. ✅ Commit cleanup: `git commit -am "Pre-rebase cleanup: remove DEBUG and dev scripts"`

### Phase 2: Interactive Rebase (1-2 hours)
```bash
cd /home/jt/sync/data_common/code/jt/cl_context_clone
git rebase -i master
```

**Expected conflicts** (in order of appearance):
1. **parser.rs** (struct members data structure)
   - Change tuple destructuring → simple iteration
   - Adapt to master's control flow style (boolean flags vs loop/break)

2. **init.rs** (struct members + Context.mode → Context.mode_def)
   - Change tuple destructuring
   - mode_def rename might already be in branch (check)

3. **interpreter.rs** (LARGEST - struct members + control flow)
   - Change tuple destructuring (7 sites)
   - Possibly adapt break/continue patterns (check if conflicts)
   - Keep all 22 scope cleanup sites intact

4. **typer.rs** (struct members + control flow)
   - Change tuple destructuring
   - Adapt to continue elimination patterns

### Phase 3: Conflict Resolution Strategy

**For each file with conflicts:**
1. Accept master's struct definition: `Vec<Declaration>`
2. Convert iterations:
   ```bash
   # Semi-automated (review each change!):
   sed -i 's/for (\([^,]*\), \(decl\)) in/for \2 in/g' src/rs/FILE.rs
   # Then manually add: let field_name = &decl.name; where needed
   ```
3. Keep cl_context_clone's scope push/pop logic
4. Adapt to master's control flow style where needed
5. **Test after EACH file**: `make && ./bin/rstil src/test/scope_isolation.til`

### Phase 4: Post-Rebase Validation (30 min)
1. Full test suite: `make tests`
2. Verify scope cleanup sites: `grep -n "pop_function_scope" src/rs/interpreter.rs | wc -l` (should be 22)
3. Visual code review of conflict resolutions
4. Run new edge case tests (from above)

## Key Things to Preserve During Rebase

### ✅ MUST KEEP - Core Scope Refactoring
- `push_function_scope()` call at line ~2636
- All 22 `pop_function_scope(saved_path)?;` calls
- 7 documented CLEANUP SITE comments
- `mut_args` and `pass_by_ref_params` tracking
- Field offset registration logic

### ❌ MUST CHANGE - Struct Members
- Convert `Vec<(String, Declaration)>` → `Vec<Declaration>` everywhere
- Change `for (name, decl)` → `for decl` + `let name = &decl.name`
- Update `members.push((decl.name.clone(), decl.clone()))` → `members.push(decl.clone())`

### ⚠️ ADAPT - Control Flow
- Keep scope push/pop logic
- But adapt surrounding control flow to match master's style
- Master prefers boolean flags over loop/break patterns (see commits 7cb1226, b8bcafe)
- But note: commit 3c385a5 REVERTED some of this, so be careful!

## Rollback Plan

If rebase gets too complex:
```bash
git rebase --abort
git tag pre-rebase-attempt-$(date +%Y%m%d)
# Take a different approach (e.g., cherry-pick key commits)
```

## Success Criteria

✅ Rebase complete when:
1. All conflicts resolved
2. `make tests` passes with 0 errors
3. All 22 scope cleanup sites present
4. No DEBUG logging remains
5. Struct members use `Vec<Declaration>` (not tuples)
6. Code follows master's control flow style
7. New edge case tests pass

## Questions for User Before Starting

1. **Are the tmp/*.til test files important?**
   - Should they be committed or deleted?

2. **Were any DEBUG statements intentionally left for ongoing work?**
   - Or safe to remove all?

3. **Performance measurements available?**
   - Would be good to document the "68-247 KB" claim

4. **Any breaking changes we should be aware of?**
   - Does this affect existing TIL code?

## Estimated Time

- **Pre-rebase cleanup**: 30 minutes
- **Rebase execution**: 1-2 hours (depends on conflict complexity)
- **Testing & validation**: 30 minutes
- **Total**: 2-3 hours

**Recommendation**: Block out a continuous 3-hour window to avoid context switching during rebase.
