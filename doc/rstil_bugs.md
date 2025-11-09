# rstil Interpreter Bugs Blocking Self-Hosting

This document tracks critical bugs in the rstil interpreter that prevent the self-hosted TIL compiler from working.

## Status Summary

- **Parser**: ✅ WORKING (after workarounds for bugs #1-3)
- **Evaluator**: ❌ BLOCKED (by bug #4)

The self-hosted parser successfully parses `println("test")` and reaches EOF. However, evaluation fails due to string payload extraction issues.

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

## Bug #4: String Payload Extraction from Self-Hosted Enums ❌ BLOCKING

**Problem**: rstil cannot extract string payloads from enums created by self-hosted code. This affects ANY enum with a string payload, including:
- `NodeType.Identifier(name)` - function names, variable names
- `LiteralNodeType.String(s)` - string literals
- Any other enum with string payloads

**Error Message**: `String payload pointer out of bounds`

**Error Location**: `src/rs/interpreter.rs:240`

**Where It Fails**:
```til
// In init_context, trying to extract function name:
case NodeType.Identifier(name):  // Fails at interpreter.rs:240
    func_name = name  // Never reached
```

**Impact**:
- ✅ Parser works - successfully parses `println("test")`
- ❌ Evaluator fails - cannot extract "println" identifier from AST
- ❌ Blocks ALL self-hosted evaluation

**Root Cause**: When self-hosted parser creates `NodeType.Identifier("println")`, the string "println" is stored in the global arena. When rstil tries to extract it via pattern matching, the pointer arithmetic fails - the string offset is beyond arena bounds.

**Attempted Workarounds**:
- ❌ Using `rsonly_enum_extract_payload()` - same error
- ❌ Using `enum_to_str()` - doesn't include payload data
- ❌ String comparison on enum string - no access to payload

**Current Blockers**:
1. Cannot extract function names from FCall nodes
2. Cannot extract variable names from Identifier nodes
3. Cannot extract string values from String literal nodes
4. Cannot process ANY AST nodes with string payloads

**Status**: CRITICAL BLOCKER - Needs fix in rstil interpreter

## Workarounds Implemented (Bugs #1-3)

All workarounds are documented with comments in the code:
```til
// Workaround for rstil bug: <description>
```

These workarounds are necessary for self-hosted code to work and should NOT be removed even after rstil is fixed, as self-hosted code must run on current rstil.

## Next Steps

**For Bug #4**: This requires either:
1. Fix in rstil interpreter's string payload extraction logic
2. Alternative enum representation that doesn't use arena pointers
3. Different AST structure that avoids string payloads entirely

**Priority**: CRITICAL - Blocks entire self-hosting effort
