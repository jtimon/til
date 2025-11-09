# rstil Bug Fixes - Historical Reference

This document provides a brief changelog of bugs that were fixed in the rstil interpreter.

## Active Bugs

### Bug #6: Enum Payloads Lost in Struct-to-Struct Copy
- **Status**: ⚠️ ARCHITECTURAL LIMITATION
- **Symptom**: When copying a struct that contains enum fields with payloads, the payloads are lost or corrupted
- **Root Cause**: Structs are allocated with fixed sizes based on `get_type_size()`, which returns 8 bytes for all enums regardless of payload. When enum payloads are written, they extend beyond the allocated space, causing memory corruption.
- **What Works**:
  ```til
  mut t := Token()
  t.token_type = TokenType.Identifier("foo")  // ✅ Direct assignment works!
  ```
- **What Doesn't Work**:
  ```til
  t1.token_type = TokenType.Identifier("foo")
  t2 = t1  // ❌ Struct copy loses enum payload
  ```
- **Impact**:
  - Direct enum-to-field assignment works correctly
  - Struct-to-struct copying doesn't preserve enum payloads
  - test_parser.til blocked by related issues
- **Possible Solutions**:
  1. Use indirection (pointers) for enum fields
  2. Implement struct reallocation when payloads change
  3. Reserve maximum possible size for enum fields
  4. Copy structs field-by-field instead of memcpy
- **Tests**: src/test/enum_payloads.til covers working cases
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
