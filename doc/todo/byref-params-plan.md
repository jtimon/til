# Plan: Pass-by-reference for non-copy parameters in ccodegen

## Status: WIP on branch `wip/byref-params`

### Progress (2024-12-19)

**Completed:**
- Phase 1a: All renames done (current_mut_params -> current_ref_params, etc.)
- Phase 1b partial:
  - Added `is_primitive_type()` helper function
  - Changed `emit_struct_func_signature` for `const Type*`
  - Changed `current_ref_params` insertion logic
  - Changed `ParamTypeInfo.by_ref` creation logic
  - Changed `param_by_ref` vector creation logic
  - Added `hoist_ref_fcalls_in_expr` for nested fcall hoisting
  - Fixed `emit_switch` string comparisons to use `&` for both args
  - Fixed `emit_arg_with_param_type` to check `ctx.hoisted_exprs`
  - Fixed `emit_arg_with_mut` similarly

**Blocked on:**
- Many GCC errors remain when building til.til
- Core issue: When `get_fcall_func_def` returns None (can't find function def),
  code falls back to `emit_arg_or_hoisted` which doesn't pass `by_ref=true`
- This affects calls like `Str.eq(x, y)` where both args need `&` but first arg missing it
- Also issues with field access hoisting determining wrong types

**Key insight discovered:**
- The `is_ext_func` exception at line ~6859 disables by_ref for ext_func, but this
  might be wrong since ext.c functions already expect `const Type*`
- Need to investigate why `get_fcall_func_def` returns None for `Str.eq` calls

**Not yet ported to ccodegen.til** - waiting for Rust version to pass tests first.

---

## Goal
Simplify ccodegen by making all non-copy, non-primitive parameters pass by reference in C.

## The Simple Rule
```
if is_copy || is_primitive:
    pass by value (Type arg)
else:
    pass by reference (Type* arg, caller uses &)
```

That's it. One boolean check.

## Current Complexity (What We Found)

### Three Different Meanings of `is_mut`

**IMPORTANT: Only Category 3 changes. Categories 1 and 2 stay the same.**

| Category | Example | Meaning | Change? |
|----------|---------|---------|---------|
| 1. Struct member | `member.is_mut` | Is this a data field (vs const/function)? | NO |
| 2. Declaration | `decl.is_mut` | Can this variable be assigned to? | NO |
| 3. Function param | `arg.is_mut` | Is this param passed as pointer? | YES -> `!is_copy && !is_primitive` |

**Category 1 - Struct members (12 occurrences, DON'T CHANGE):**
Lines 224, 657, 2140, 2167, 4547, 4599, 5262, 5307, 6215, 6491, 6535
- Check if struct field is mutable (data) vs const/function
- Used for: skipping const fields in struct emission

**Category 2 - Declaration mutability (9 occurrences, DON'T CHANGE):**
Lines 1858, 1911, 1924, 1959, 1962, 4459, 4490, 5733, and SymbolInfo.is_mut
- Check if variable can be assigned to
- Used for: emitting C `const` keyword

**Category 3 - Function param passing (12 occurrences, CHANGE):**
Lines 1362, 2541, 2712, 2790, 3338, 3542, 3845, 4106, 4373, 5352, 6647
- Determines if param is passed as pointer
- CHANGE: `arg.is_mut` -> `!arg.is_copy && !is_primitive_type(&arg.value_type)`

### Data Structures
- **ParamTypeInfo.is_mut** (line 5610) -> rename to **by_ref**
- **current_mut_params** -> rename to **current_ref_params** (tracks pointer params for `->` vs `.`)
- **current_variadic_params**: HashMap tracking variadic params (also pointers) - no change

### Functions That Emit Arguments (6 different functions!)
| Function | Lines | Purpose | Adds `&` when |
|----------|-------|---------|---------------|
| `emit_arg_with_param_type` | 1399-1540 (~140 lines) | Main arg emitter | is_mut OR is_dynamic |
| `emit_arg_with_mut` | 3474-3524 (~50 lines) | Simpler mut-only version | is_mut |
| `emit_arg_or_hoisted` | 1386-1398 (~13 lines) | Wrapper, passes is_mut=false | Never |
| `emit_fcall_name_and_args_for_throwing` | 1290-1385 (~95 lines) | Throwing call args | Delegates |
| `emit_fcall` | 6165-6700 (~535 lines) | Main fcall emitter | Multiple paths |
| `emit_variadic_call` | 3330-3470 (~140 lines) | Variadic calls | is_mut |

### Hoisting Functions
| Function | Lines | Purpose |
|----------|-------|---------|
| `hoist_throwing_args` | 717-975 (~260 lines) | Hoist throwing calls from args |
| `hoist_for_dynamic_params` | 977-1126 (~150 lines) | Hoist non-lvalue args for Dynamic params |
| `hoist_throwing_expr` | 392-715 (~320 lines) | Hoist single throwing expr |
| `hoist_variadic_args` | 1127-1285 (~160 lines) | Hoist variadic args into array |

### Places That Check is_mut (30+ occurrences)
See exploration results. Key categories:
1. **Signature generation**: decides `Type*` vs `Type`
2. **Arg emission**: decides to add `&` prefix
3. **Field access**: decides `->` vs `.`
4. **Symbol tracking**: stores in SymbolInfo

## What Changes

### Step 1: Mechanical Replacement (No Simplifications Yet)
Goal: Make const/own work like mut currently does.

#### 1.1 Function Signatures (emit_struct_func_signature ~line 2712)
```rust
// FROM:
if arg.is_mut { "Type* " }
else if arg.is_copy || arg.is_own { "Type " }
else { "const Type " }

// TO:
if arg.is_copy || is_primitive_type(&arg.value_type) { "Type " }
else if arg.is_mut || arg.is_own { "Type* " }
else { "const Type* " }
```

#### 1.2 Rename current_mut_params to current_ref_params
First rename the field and all 20 usages (lines 25, 58, 1441, 1463, 1507, 1521, 2537, 2542, 2786, 2791, 2926, 3718, 3726, 4041, 4049, 4306, 4314, 4361, 4374, 4422, 4861, 4869).

Also rename local variable `is_mut_param` to `is_ref_param` (line 2926).

#### 1.3 Update current_ref_params insertion
3 locations where we insert into current_ref_params:
- `emit_struct_func_body` line 2542
- `emit_func_prototype` line 2791
- `emit_declaration` (nested func) line 4374

Change from:
```rust
if arg.is_mut { ctx.current_ref_params.insert(arg.name.clone()); }
```
To:
```rust
if !arg.is_copy && !is_primitive_type(&arg.value_type) {
    ctx.current_ref_params.insert(arg.name.clone());
}
```

#### 1.4 ParamTypeInfo.is_mut -> by_ref
7 locations where ParamTypeInfo is created:
- Line 1362: `emit_fcall_name_and_args_for_throwing`
- Line 3338: `emit_variadic_call`
- Line 3543: `emit_throwing_call`
- Line 3846: `emit_throwing_call_propagate`
- Line 4107: `emit_return_throwing_call`
- Line 5352: `emit_simple_fcall`
- Line 6647: `emit_fcall`

Change from:
```rust
ParamTypeInfo { value_type: Some(p.value_type.clone()), is_mut: p.is_mut }
```
To:
```rust
ParamTypeInfo { value_type: Some(p.value_type.clone()), by_ref: !p.is_copy && !is_primitive_type(&p.value_type) }
```

#### 1.5 Rename param_is_mut variables
4 locations where `param_is_mut: Vec<bool>` is created:
- Line 3335: `emit_variadic_call`
- Line 3540: `emit_throwing_call`
- Line 3843: `emit_throwing_call_propagate`
- Line 4104: `emit_return_throwing_call`

Rename to `param_by_ref` and change:
```rust
// FROM:
.map(|a| a.is_mut)
// TO:
.map(|a| !a.is_copy && !is_primitive_type(&a.value_type))
```

#### 1.6 Rename local is_mut variables (param passing context)
8 locations where `let is_mut = param_is_mut.get(...)`:
- Lines 3384, 3424, 3449, 3662, 3683, 3963, 3984, 4226

Rename to `let by_ref = param_by_ref.get(...)`

### Step 2: Simplifications (After Step 1 Works)

**Rule: Remove unused code immediately when rustc warns. No `_` prefixes or suppressions.**

#### 2.1 Delete emit_arg_with_mut (~50 lines at 3474-3524)
After Phase 1, `emit_arg_with_mut` and `emit_arg_with_param_type` do the same thing.
Delete `emit_arg_with_mut` and update its 3 callers to use `emit_arg_with_param_type`:

| Line | Current Call | Change To |
|------|--------------|-----------|
| 3385 | `emit_arg_with_mut(arg, i, &hoisted, is_mut, ...)` | `emit_arg_with_param_type(arg, i, &hoisted, None, is_mut, ...)` |
| 3425 | `emit_arg_with_mut(arg, i, &hoisted, is_mut, ...)` | `emit_arg_with_param_type(arg, i, &hoisted, None, is_mut, ...)` |
| 3450 | `emit_arg_with_mut(arg, i, &hoisted, is_mut, ...)` | `emit_arg_with_param_type(arg, i, &hoisted, None, is_mut, ...)` |

All 3 callers are in `emit_variadic_call`. Pass `None` for param_type since these are enum constructors.

**Savings: ~50 lines**

#### 2.2 Delete emit_arg_or_hoisted (~13 lines at 1386-1398)
This wrapper passes `is_mut=false` (wrong after Phase 1 - should be `by_ref`).
Delete it and update its 4 callers to use `emit_arg_with_param_type` with proper `by_ref`:

| Line | Function | Current Call | Change To |
|------|----------|--------------|-----------|
| 5373 | `emit_fcall_with_hoisted` | `emit_arg_or_hoisted(arg, i, hoisted, ...)` | `emit_arg_with_param_type(arg, i, hoisted, param_type, by_ref, ...)` |
| 6429 | `emit_fcall` (enum_to_str) | `emit_arg_or_hoisted(arg, 0, &hoisted, ...)` | `emit_arg_with_param_type(arg, 0, &hoisted, None, true, ...)` |
| 6631 | `emit_fcall` (variadic regular) | `emit_arg_or_hoisted(arg, i, &hoisted, ...)` | `emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, ...)` |
| 6671 | `emit_fcall` (fallback) | `emit_arg_or_hoisted(arg, i, &hoisted, ...)` | `emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, ...)` |

Each caller needs to get `param_type` and `by_ref` from the function definition (already done nearby).

**Savings: ~13 lines**

#### 2.3 Rename hoist_for_dynamic_params to hoist_for_ref_params (~150 lines at 977-1126)
Currently hoists non-lvalue args only for Dynamic params.
After Phase 1, should hoist for ALL by-ref params.

**Change the condition from:**
```rust
// Only hoist for Dynamic params
if param_type == "Dynamic" && !is_lvalue(arg) { ... }
```
**To:**
```rust
// Hoist for any by-ref param when arg is a function call (can't take &rvalue)
if by_ref && matches!(arg.node_type, NodeType::FCall) { ... }
```

**Callers (7 total, all just rename):**
| Line | Function |
|------|----------|
| 948 | `hoist_throwing_args` |
| 3558 | `emit_throwing_call` |
| 3861 | `emit_throwing_call_propagate` |
| 4122 | `emit_throwing_call_propagate` |
| 4671 | `emit_variadic_call` |
| 4717 | `emit_variadic_call` |
| 6269 | `emit_fcall` |

All callers just need the function name updated. The signature changes slightly:
- Add `param_by_ref: &[bool]` parameter
- Remove complex "is this Dynamic?" detection (now just checks the bool)

**Savings: ~30-50 lines** (simplified conditions, removed Dynamic-specific type detection)

#### 2.4 Unify Dynamic handling in emit_arg_with_param_type
Currently lines 1399-1540 have separate paths:
- Lines ~1440-1490: Dynamic param handling (cast + &)
- Lines ~1500-1540: mut param handling (just &)

After Phase 1, both use `by_ref` for the `&` decision. Only difference is Dynamic needs cast.

**Change from:**
```rust
if is_dynamic {
    // ~50 lines of Dynamic-specific code
    output.push_str("(til_Dynamic*)&");
    ...
} else if param_is_mut {
    // ~40 lines of mut-specific code
    output.push_str("&");
    ...
}
```
**To:**
```rust
if by_ref {
    if is_dynamic { output.push_str("(til_Dynamic*)"); }
    output.push_str("&");
    // ~30 lines of unified handling
    ...
}
```

**Savings: ~20-30 lines** (merged duplicate logic)

### Total Estimated Savings
| Change | Lines Saved |
|--------|-------------|
| Delete emit_arg_with_mut | ~50 |
| Delete emit_arg_or_hoisted | ~13 |
| Simplify hoist_for_dynamic_params | ~30-50 |
| Unify Dynamic/mut paths | ~20-30 |
| **Total** | **~115-145 lines** |

Plus significant reduction in cognitive complexity - one rule instead of multiple special cases.

## Helper Function Needed
```rust
fn is_primitive_type(vt: &ValueType) -> bool {
    match vt {
        ValueType::I64 | ValueType::U8 | ValueType::Bool => true,
        ValueType::TCustom(name) => name == "Type" || name == "Dynamic",
        _ => false,
    }
}
```

## Execution Order

### Phase 1a: Pure Renames (C output unchanged)
1. Rename `current_mut_params` → `current_ref_params` (field + 20 usages)
2. Rename `is_mut_param` → `is_ref_param` (line 2926)
3. Rename `ParamTypeInfo.is_mut` → `by_ref` (line 5610 + 3 access sites)
4. Rename `param_is_mut` → `param_by_ref` (4 places)
5. Rename local `let is_mut =` → `let by_ref =` in param context (8 places)
6. Test: generated C should be IDENTICAL
7. Port to ccodegen.til
8. Test again
9. Commit: "Rename is_mut to by_ref in param passing context (prep for by-ref change)"

### Phase 1b: Extend Functionality (C output changes)
10. Add `is_primitive_type()` helper function
11. Change `emit_struct_func_signature` line ~2712: `const Type` → `const Type*`
12. Change `current_ref_params` insertion: `arg.is_mut` → `!arg.is_copy && !is_primitive_type`
13. Change ParamTypeInfo.by_ref creation: `p.is_mut` → `!p.is_copy && !is_primitive_type`
14. Change `param_by_ref` vector creation: same logic change
15. Test: generated C should have more pointers, tests pass
16. Port to ccodegen.til
17. Test again
18. Commit: "Pass non-copy non-primitive params by reference"

### Phase 2: Delete emit_arg_with_mut (~50 lines)
19. Update 3 callers (lines 3385, 3425, 3450) to use `emit_arg_with_param_type`
20. Delete now-unused `emit_arg_with_mut`
21. Test, port to til, test, commit

### Phase 3: Delete emit_arg_or_hoisted (~13 lines)
22. Update 4 callers (lines 5373, 6429, 6631, 6671) to use `emit_arg_with_param_type`
23. Delete now-unused `emit_arg_or_hoisted`
24. Test, port to til, test, commit

### Phase 4: Rename hoist_for_dynamic_params → hoist_for_ref_params
25. Rename function and update 7 callers
26. Test, port to til, test, commit

### Phase 5: Simplify hoist_for_ref_params logic
27. Change condition from Dynamic-specific to by_ref check
28. Test, port to til, test, commit

### Phase 6: Unify Dynamic/by_ref paths in emit_arg_with_param_type (~20-30 lines)
29. Merge duplicate `&` prefix logic
30. Keep Dynamic cast as special case
31. Test, port to til, test, commit

### Phase 7: Delete current_ref_params (use SymbolInfo lookup)
32. Replace all `ctx.current_ref_params.contains(name)` with SymbolInfo lookup
33. Delete the HashSet field
34. Test, port to til, test, commit

## Files to Modify
- `src/rs/ccodegen.rs` - All changes
- `src/self/ccodegen.til` - Port changes

## Key Insight From Failed Attempt
The previous attempt failed because we tried to do too much at once and didn't understand all the code paths. This plan:
1. First makes mechanical changes only (Step 1)
2. Tests that it works
3. Then simplifies incrementally (Step 2)
4. Each simplification is small and testable
