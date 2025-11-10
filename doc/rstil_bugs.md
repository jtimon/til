# rstil Bug Fixes - Historical Reference

This document provides a brief changelog of bugs that were fixed in the rstil interpreter.

## Active Bugs

None - all known bugs have been fixed!

## Fixed Bugs Summary

Bugs #1-#7 have been fixed and their tests integrated into the regular test suite (`enums.til`, `flow.til`, `arithmetics.til`).

### Bug #1: Enum Comparison in Switch/Case
- **Status**: ❌ NOT PRESENT - Type system prevents this issue
- **Workaround**: Commit 46a00bc (string comparison)

### Bug #2: Return Statement Stack Frame Handling
- **Status**: ❌ NOT PRESENT - All nested return tests pass
- **Workaround**: Commit 46a00bc (function inlining)

### Bug #3: Nested Enum Payloads
- **Status**: ✅ FIXED - Direct nested enum construction works
- **Fix**: interpreter.rs:607-633 (recursive enum constructor evaluation)
- **Commit**: b75c886

### Bug #4: Enum Payload Copy
- **Status**: ✅ FIXED - Payloads preserved when copying between variables
- **Fix**: interpreter.rs:1125-1135, 1214-1224 (temp_enum_payload handling)
- **Commit**: 6b1702a

### Bug #5: rsonly_enum_extract_payload Function
- **Status**: ✅ FIXED - All payload types (I64, Str, Struct, Nested) work
- **Fix**: interpreter.rs:2346 (map_instance_fields for struct payloads)
- **Commit**: 4676a6b

### Bug #6: Enum Payloads Lost in Struct-to-Struct Copy
- **Status**: ✅ FIXED - Enum fields now reserve maximum variant size
- **Symptom**: When copying a struct that contains enum fields with payloads, the payloads were lost or corrupted
- **Root Cause**: Structs were allocated with fixed sizes based on `get_type_size()`, which returned only 8 bytes for all enums regardless of payload size. When enum payloads were written, they extended beyond the allocated space, causing memory corruption.
- **Solution**: Modified `get_type_size()` to calculate and reserve the maximum variant size for each enum type (8 bytes for tag + largest payload size), following the Rust approach.
- **Fix**: init.rs:1118-1144 (calculate max variant size in get_type_size)
- **Tests**: src/test/enums.til includes comprehensive regression tests for direct assignment and struct copying
- **Discovery**: 2025-01-09 during test_parser.til investigation
- **Fixed**: 2025-01-09

### Bug #7: Enum Return Value Handling
- **Status**: ✅ FIXED - Functions can now return enums with payloads correctly
- **Symptom**: When a function returned an enum value (especially with enum payloads), the payload data was lost, causing "range end index out of bounds" errors or incorrect values
- **Root Cause**: Enums were not being properly transferred from the function's context to the caller's context. The `temp_enum_payload` stored in the function context was discarded when the function returned.
- **Solution**: Added special handling for enum return values in `eval_func_proc_call`:
  - For constructor expressions (e.g., `OuterType.Nested`), transfer `temp_enum_payload` from function context to caller context
  - For variable returns, copy the enum value with its payload to caller context using `get_enum` and `insert_enum`
- **Fix**: interpreter.rs:1761-1786 (enum return value handling)
- **Tests**: src/test/enums.til:test_enum_constructor_in_function (comprehensive tests for returning enums with enum payloads)
- **Discovery**: 2025-01-10 during parser.til homogenization
- **Fixed**: 2025-01-10
- **Commit**: 05dd5c9

### Division/Modulo by Zero
- **Status**: ✅ FIXED - Returns 0 instead of panicking (safe default)
- **Fix**: interpreter.rs (zero checks in div/mod operations)
- **Commit**: 576a7fe
- **Note**: Users can implement custom error handling with throw/catch if needed

---

**All historical bugs (#1-#7) fixed as of January 2025.**

For implementation details and self-hosting progress, see git history and commit messages.
