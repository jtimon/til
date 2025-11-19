# Bug: Catch variable not accessible in arena

## Issue

When catching an error in a catch block, the caught error variable (`err`) is not properly stored in the execution arena. This causes runtime errors when trying to access fields of the caught error.

## Symptoms

1. **Compilation error**: When trying to use `throw err.msg` directly in a catch block:
   - Error: "Undefined symbol 'err'"

2. **Runtime error**: When using a workaround (assigning to an external variable first):
   - Error: "get_struct: get_field_offset: base variable 'err' not found in arena_index"

## Reproduction

See `src/test/test_rethrow.til` for a minimal reproduction case.

The test tries to:
1. Catch an `IndexOutOfBoundsError`
2. Rethrow it as a different type (String) using `err.msg`
3. This fails because `err` is not accessible

## Current workaround

None - cannot access caught error fields in catch blocks.

## Suspected root cause

The catch block's error parameter isn't being properly registered in the execution arena/context when the catch block is entered.

## Related issues

This bug affects:
- Throwing error fields: `throw err.msg` ✗ **confirmed broken**
- Returning error fields: `return err.msg` ✗ **confirmed broken**
- Assigning error fields to variables: `msg = err.msg` ✗ **confirmed broken**
- Any field access from caught errors in catch blocks

The issue is not specific to throw statements - it affects any attempt to access fields of the caught error variable.

## Test location

`src/test/test_rethrow.til` - contains tests for this bug
