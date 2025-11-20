# Scope Stack Refactoring - Preparation Complete

## Summary

All preparatory steps completed for the big-bang context cloning → scope push/pop refactoring.

## Completed Prep Work

### 1. ✅ Scope Helper Functions (Commit: adb8332)
- Added `Context::push_function_scope(path)` - Returns saved path
- Added `Context::pop_function_scope(saved_path)` - Restores path and pops scope
- Encapsulates the push/pop pattern for cleaner refactoring

### 2. ✅ Scope Isolation Tests (Commit: 17371b8)
- New file: `src/test/scope_isolation.til`
- Tests: parameter shadowing, nested calls, recursion, mut pass-by-ref
- All tests pass with current context cloning implementation
- Will verify scope stack correctness after refactoring

### 3. ✅ Return Path Documentation (Commit: 91903f1)
- Documented all 7 main return paths in `eval_user_func_proc_call`
- Marked with "CLEANUP SITE" comments
- Added comprehensive refactoring plan at function top
- Makes it clear where `pop_function_scope()` must be called

### 4. ✅ Investigated wip_clone_context Str Bug
- **Root Cause**: `insert_struct` expects symbols to pre-exist for struct parameters
- **Symptom**: "insert_struct: id 'loc_str' for struct 'Str' not found in symbols"
- **Context**: Occurs when passing Str to nested functions (test → assertm)
- **Related Issue**: Hybrid field mapping (some dynamic, some pre-registered)

## The Big-Bang Refactoring

### What Needs to Change

**File**: `src/rs/interpreter.rs`

**Function**: `eval_user_func_proc_call` (lines 2521-3192)

#### Step 1: Replace Context Clone with Scope Push
```rust
// OLD (lines 2539-2540):
let mut function_context = context.clone();
function_context.path = func_def.source_path.clone();

// NEW:
let saved_path = context.push_function_scope(&func_def.source_path);
```

#### Step 2: Replace All `function_context` with `context`
- ~52 occurrences throughout the function
- Use find-replace: `function_context` → `context`

#### Step 3: Fix Arena Insert Functions
**File**: `src/rs/interpreter.rs`

**Functions**: `insert_i64`, `insert_u8` (and possibly `insert_bool`, `insert_string`)

Add in-place update check:
```rust
// Check if variable already exists (e.g., mut parameters)
if let Some(existing_offset) = ctx.scope_stack.lookup_var(id) {
    // Update existing value in-place (needed for mut parameters)
    Arena::g().memory[offset..offset + size].copy_from_slice(&bytes);
    return Ok(())
}

// Variable doesn't exist yet - create new allocation
let offset = Arena::g().memory.len();
Arena::g().memory.extend_from_slice(&bytes);
ctx.scope_stack.insert_var(id.to_string(), offset);
```

**Why**: With context cloning, each function got a separate context but shared the global Arena. Parameters created new allocations in cloned scope_stack. With scope push/pop, we need to update existing variables in-place for mut parameters to work.

#### Step 4: Add Cleanup Before Each Return
Add before all 7 main returns (+ ~15 error returns):
```rust
context.pop_function_scope(saved_path)?;
return Ok(...)  // or Err(...)
```

**Return Sites**:
1. Line 2556: Propagate throw from variadic args
2. Line 2637: Propagate throw from argument evaluation
3. Line 3064: Propagate throw from function body
4. Line 3152: Return struct instance
5. Line 3164: Return enum constructor
6. Line 3178: Return enum variable
7. Line 3191: Return normal value (final)

### Str Bug Prevention

**Problem**: When passing Str by reference, `insert_struct` expects symbol to exist

**Solutions to Consider**:

1. **Pre-register Str parameters in symbols before calling insert functions**
   ```rust
   // Before: Arena::insert_string(&mut context, &arg.name, &result_str, e)?

   // After: Ensure symbol exists first
   if !context.scope_stack.lookup_symbol(&arg.name).is_some() {
       context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
           value_type: ValueType::TCustom("Str".to_string()),
           is_mut: arg.is_mut,
           is_copy: false,
           is_own: false,
       });
   }
   Arena::insert_string(&mut context, &arg.name, &result_str, e)?;
   ```

2. **Modify insert_struct to declare symbol if missing** (more invasive)

3. **Fully dynamic field offset calculation** (eliminate pre-registration entirely)

Recommendation: **Option 1** is safest for initial refactoring.

### Additional Refactorings

#### Catch Blocks (interpreter.rs ~line 2361-2510)
Replace manual cleanup with scope push/pop:
```rust
// OLD:
context.scope_stack.declare_symbol(var_name, ...);
// ... catch body ...
context.scope_stack.remove_symbol(var_name);
context.scope_stack.remove_var(var_name);
// ... remove field mappings ...

// NEW:
context.scope_stack.push(ScopeType::Catch);
context.scope_stack.declare_symbol(var_name, ...);
// ... catch body ...
context.scope_stack.pop()?;
```

#### Type Checker (typer.rs lines 131, 666)
Replace 2 context clones with push/pop:
```rust
// OLD:
let mut function_context = context.clone();
errors.extend(check_func_proc_types(&func_def, &mut function_context, &e));

// NEW:
context.scope_stack.push(ScopeType::Function);
errors.extend(check_func_proc_types(&func_def, context, &e));
context.scope_stack.pop()?;
```

## Testing Strategy

1. **Incremental verification**: After each major change, run `make && ./bin/rstil src/test/scope_isolation.til`
2. **Full test suite**: `make tests` only when all changes complete
3. **Specific tests to watch**:
   - `src/test/scope_isolation.til` - New scope tests
   - `src/test/args.til` - Parameter passing, including Str
   - `src/test/mut_test.til` - Mut parameter behavior
   - `src/test/hello/hello_test.til` - Where wip_clone_context failed

## Risk Assessment

**High Risk Areas**:
1. Str parameter passing (known from wip_clone_context failure)
2. Pass-by-reference mechanics (lines 2728-2904)
3. Mut argument copy-back (lines 3056-3109)

**Why This Must Be Atomic**:
- Removing clone without push/pop → name collisions in frame 0
- Cannot test incrementally - all or nothing
- But with prep work done, the actual change is mechanical

## Estimated Diff Size

- ~100 lines changed in `eval_user_func_proc_call`
- ~30 lines changed in arena insert functions
- ~20 lines changed in catch block handling
- ~10 lines changed in typer.rs
- **Total: ~160 lines** (much smaller with helper functions!)

## Performance Expectation

Current: ~68-247 KB cloned per function call
After: ~0 KB (just a frame push = few HashMaps created empty)

**Expected improvement**: 1000-1500x reduction in allocation/copying per function call
