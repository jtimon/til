# rstil Bug Fixes - Historical Reference

This document provides a brief changelog of bugs that were fixed in the rstil interpreter. All documented bugs are now fixed or were never present.

## Fixed Bugs Summary

All bugs have been fixed and their tests integrated into the regular test suite (`enums.til`, `flow.til`, `arithmetics.til`).

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

**All documented bugs fixed as of January 2025.**

For implementation details and self-hosting progress, see git history and commit messages.
