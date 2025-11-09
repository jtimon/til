# rstil Bug Fixes - Historical Reference

This document provides a brief changelog of bugs that were fixed in the rstil interpreter.

## Active Bugs

### Bug #6: Enum Payload Corruption in Struct Field Assignment
- **Status**: ⚠️ ACTIVE BUG - Blocks test_parser.til
- **Symptom**: When assigning an enum value to a struct field, the payload is replaced with the struct's type name
- **Example**:
  ```til
  node_type := NodeType.Identifier("foo")  // Correctly contains "foo"
  mut e := Expr()
  e.node_type = node_type                   // Now contains "Expr" instead of "foo"!
  ```
- **Impact**: test_parser.til fails with `assert_eq_str failed: expected 'foo', found 'Expr'`
- **Workaround**: None known - direct assignment of enums to struct fields is broken
- **Discovery**: 2025-01-09 during test_parser.til investigation

## Fixed Bugs Summary

Bugs #1-#5 have been fixed and their tests integrated into the regular test suite (`enums.til`, `flow.til`, `arithmetics.til`).

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

### Division/Modulo by Zero
- **Status**: ✅ FIXED - Returns 0 instead of panicking (safe default)
- **Fix**: interpreter.rs (zero checks in div/mod operations)
- **Commit**: 576a7fe
- **Note**: Users can implement custom error handling with throw/catch if needed

---

**Historical bugs (#1-#5) all fixed as of January 2025.**
**Bug #6 discovered January 2025 - ACTIVE.**

For implementation details and self-hosting progress, see git history and commit messages.
