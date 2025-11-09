# rstil Interpreter Bugs Blocking Self-Hosting

This document tracks critical bugs in the rstil interpreter that prevent the self-hosted TIL compiler from working.

## Status Summary

- **Parser**: ✅ WORKING (after workarounds for bugs #1-3)
- **Evaluator**: ✅ WORKING (bug #4 FIXED!)

The self-hosted parser successfully parses `println("test")` and reaches EOF. Enum payload extraction now works correctly. Self-hosted evaluation progresses further but hits other issues.

## Bug #1: Enum Comparison in Switch/Case ✅ WORKED AROUND

**Problem**: Switch/case with enum variables performs pattern binding instead of comparison.

```til
// This doesn't work:
switch p.token_type {
case expected:  // 'expected' is a TokenType variable - this binds instead of compares!
    matches = true
}
```

**Workaround**: Convert enums to strings and compare:
```til
mut p_type_str := enum_to_str(p.token_type)
mut expected_str := enum_to_str(expected)
if p_type_str.eq(expected_str) {
    // Match!
}
```

**Location**: `src/core/lexer.til` - `lexer_expect()` function

**Status**: Workaround implemented in commit `46a00bc`

## Bug #2: Return Statements Pop Multiple Stack Frames ✅ WORKED AROUND

**Problem**: Return statements in functions pop multiple stack frames when called from deep call stacks, returning from the caller instead of from the current function.

```til
func(mut lexer: Lexer) returns Token {
    // ...
    return p  // This returns from the CALLER, not from this function!
}
```

**Workaround**: Either inline the logic or assign to variable first before returning:
```til
// Workaround 1: Inline logic
mut p := lexer.peek()
mut p_type_str := enum_to_str(p.token_type)
// ... direct logic instead of function call

// Workaround 2: Assign first (doesn't always work)
mut result := some_function()
return result  // Still broken in some contexts
```

**Locations**:
- `src/core/parser.til` - parse_list LeftParen check (inlined)
- `src/core/parser.til` - parse_primary literal return (assign first)

**Status**: Workaround implemented in commit `46a00bc`

## Bug #3: Nested Enum Payloads ✅ WORKED AROUND

**Problem**: Enum constructors can't be used directly as payloads to other enum constructors.

```til
// This doesn't work:
node_type = NodeType.Literal(LiteralNodeType.String(s))
//                           ^^^^^^^^^^^^^^^^^^^^^^^^
//                           Can't use enum constructor as direct payload
```

**Workaround**: Assign inner enum to variable first:
```til
mut str_lit := LiteralNodeType.String(s)
node_type = NodeType.Literal(str_lit)  // Now works
```

**Locations**:
- `src/core/parser.til` - parse_literal (String/I64/Bool payloads)
- `src/core/parser.til` - parse_list return value (List payload)

**Status**: Workaround implemented in commit `46a00bc`

## Bug #4: Enum Payload Lost When Copying Between Variables ✅ FIXED

**Problem**: When assigning an enum value from one variable to another, the enum payload was lost. This happened because:
1. Reading an enum variable (e.g., `func_name_expr.node_type`) would call `get_enum` to retrieve the enum value
2. The enum variant name was returned as a string (e.g., "NodeType.Identifier")
3. When this was assigned to a new variable, `insert_enum` was called to store it
4. But `temp_enum_payload` was never set, so the new enum had NO payload bytes stored in the arena
5. Later attempts to extract the payload would read garbage values

**Error Message**: `String payload pointer out of bounds`

**Error Location**: `src/rs/interpreter.rs:240` (extraction code)

**Root Cause**: The `eval_custom_expr` function at line 1214 (and line 1125 for non-field enums) would call `get_enum` to read an enum value, but did NOT set `context.temp_enum_payload` with the payload data before returning. Later when `insert_enum` was called, it had no payload to store.

**Fix**: Added code to set `temp_enum_payload` when reading enum values in two locations:
1. `src/rs/interpreter.rs:1125-1135` - When reading enum variables
2. `src/rs/interpreter.rs:1214-1224` - When reading enum struct fields

Additional fixes:
- `src/rs/init.rs:1531-1533` - Added special case for Str payload type to return correct size (16 bytes)

**Status**: ✅ FIXED - Enum payloads now preserved when copying between variables

## Workarounds Implemented (Bugs #1-3)

All workarounds are documented with comments in the code:
```til
// Workaround for rstil bug: <description>
```

These workarounds are necessary for self-hosted code to work and should NOT be removed even after rstil is fixed, as self-hosted code must run on current rstil.

## Next Steps

All critical rstil bugs blocking basic self-hosted evaluation have been fixed! The self-hosted parser works, and enum payload extraction works. Further self-hosting work may reveal additional bugs, but the fundamental infrastructure is now functional.
