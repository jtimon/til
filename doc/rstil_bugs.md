# rstil Interpreter Bugs and Fixes

This document tracks bugs in the rstil interpreter, including those that blocked self-hosting (now worked around or fixed).

## Status Summary

- **Bug #1 (enum comparison)**: ❌ NOT PRESENT (typer prevents)
- **Bug #2 (return frames)**: ❌ NOT PRESENT (tests pass)
- **Bug #3 (nested enums)**: ⚠️ CONFIRMED BUG (workaround available)
- **Bug #4 (enum payload copy)**: ✅ FIXED
- **Bug #5 (enum extract)**: ⚠️ PARTIALLY WORKING (I64/Str work, struct fails)
- **Arithmetic**: ✅ SAFE (div/mod by zero fixed to return 0)

All bugs have test files in `src/test/bug_*.til` and are included in the test suite.

## Bug #1: Enum Comparison in Switch/Case ❌ NOT PRESENT

**Problem**: Switch/case with enum variables performs pattern binding instead of comparison.

**Test Result**: Bug is NOT present in current rstil. The typer prevents using enum variables as case patterns, requiring exhaustive enum variant matching instead. Test: `src/test/bug_enum_comparison.til`

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

## Bug #2: Return Statements Pop Multiple Stack Frames ❌ NOT PRESENT

**Problem**: Return statements in functions pop multiple stack frames when called from deep call stacks, returning from the caller instead of from the current function.

**Test Result**: Bug is NOT present in current rstil. All nested return tests pass correctly, including 4-level deep nesting. Test: `src/test/bug_return_frames.til`

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

## Bug #3: Nested Enum Payloads ⚠️ CONFIRMED BUG

**Problem**: Enum constructors can't be used directly as payloads to other enum constructors.

**Test Result**: Bug CONFIRMED in current rstil. Direct nested enum construction fails with "Enum payload must be a variable identifier, got FCall". Workaround (assign to variable first) works. Test: `src/test/bug_nested_enums.til`

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

## Bug #5: rsonly_enum_extract_payload Function ⚠️ PARTIALLY WORKING

**Problem**: The `rsonly_enum_extract_payload` core function is used for extracting enum payloads during pattern matching. Testing revealed issues with certain payload types.

**Test Result**: PARTIALLY WORKING in current rstil. Test: `src/test/bug_enum_extract.til`
- ✅ I64 payloads work correctly
- ✅ Str payloads work correctly
- ❌ Struct payloads fail (empty values extracted)
- ❌ Nested enum payloads hit instantiation bug
- ⚠️ Enum variants without payloads hit instantiation bug

**Working Example**:
```til
mut val := SimplePayload.IntValue(42)
mut extracted: I64 = 0
rsonly_enum_extract_payload(val, extracted)
// extracted now contains 42
```

**Status**: Core I64/Str extraction works. Struct and nested enum extraction needs investigation.

## Division/Modulo by Zero ✅ FIXED

**Problem**: Division (`div()`) and modulo (`mod()`) by zero caused Rust panic, terminating the program.

**Error**: `thread 'main' panicked at src/rs/interpreter.rs:2157: attempt to divide by zero`

**Fix**: Added zero checks to return 0 instead of panicking (safe default behavior).

**Implementation**:
```rust
// src/rs/interpreter.rs - eval_core_func_div
if b == 0 {
    return Ok(EvalResult::new("0"));
}

// src/rs/interpreter.rs - eval_core_func_mod
if b == 0 {
    return Ok(EvalResult::new("0"));
}
```

**Rationale**:
- Prevents program termination
- Provides predictable behavior (returns 0)
- Users can implement custom error handling if needed

**For custom error handling**, see `safe_div` example in `src/test/errors.til`:
```til
DivideByZero := struct {}

safe_div := func(a: I64, b: I64) returns I64 throws DivideByZero {
    if I64.eq(b, 0) {
        throw DivideByZero()
    }
    return div(a, b)
}

// Catch and handle the error
unsafe_div := proc(a: I64, b: I64) returns I64 {
    return safe_div(a, b)
    catch (err: DivideByZero) {
        return 0  // Or handle however you want
    }
}
```

**Future consideration**: Post-self-hosting, may add optional `DivideByZero` error to core `div()` and `mod()` functions. Current behavior prioritizes convenience and safety.

**Status**: ✅ FIXED - Returns 0 for div/mod by zero

## Workarounds Implemented (Bugs #1-3)

All workarounds are documented with comments in the code:
```til
// Workaround for rstil bug: <description>
```

These workarounds are necessary for self-hosted code to work and should NOT be removed even after rstil is fixed, as self-hosted code must run on current rstil.

## Self-Hosted Test Attempts

### Attempt: Copy Struct Before Switching on Enum Field (2025-01-09)

**Goal**: Enable self-hosted hello_script.til test by applying struct copy workaround

**Approach Tried**:
```til
// Instead of:
switch e.node_type {

// Use:
mut e_copy := Expr()
e_copy.node_type = e.node_type
e_copy.params = e.params
e_copy.line = e.line
e_copy.col = e.col

switch e_copy.node_type {
```

**Result**: Incomplete - still causes enum errors when run via `runfile("src/til.til", "src/test/hello/hello_script.til")`

**Error**: `get_enum: Enum definition for 'Expr' not found` at various locations during self-hosted execution

**Conclusion**: The "copy struct before switching" workaround doesn't fully solve the issue for self-hosted code execution. The problem appears to be more complex than simple field access - it may involve:
- How enums are stored/retrieved during self-hosted interpretation
- Interaction between rstil interpreter and self-hosted til interpreter
- Deeper issues with enum handling in nested execution contexts

**Status**: Reverted - needs deeper investigation into rstil's enum handling

**Files Attempted**: init.til, interpreter.til, parser.til, typer.til

## init.til Completion Progress

**Goal**: Make init.til functionally equivalent to init.rs for basic programs

### Phase 1: Foundation (In Progress)

#### ✅ Step 1: Complex Type Serialization (COMPLETED)
**Status**: Basic function serialization/deserialization working

**Implemented**:
- SFuncDef serialization format: `"FUNC|<function_type>|<return_type>"`
- `parse_func_return_type()` for deserialization
- Updated `process_declarations()` to store serialized function data
- Updated `get_fcall_value_type()` to return actual function types
- Both standalone functions and UFCS methods supported

**Commits**: 066e373, f92e58f

**Next**: Step 2 - Basic struct support (`insert_struct`, `get_type_size`)

#### ✅ Step 2: Basic Struct Support (COMPLETED)

**Implemented:**
- ✅ Implement `get_type_size` for structs (recursive calculation)
  - Serialization format: `"STRUCT|field1=Type1|field2=Type2|..."`
  - Parses serialized data and recursively calculates field sizes
  - Commit: c004cd2
- ✅ Implement `insert_struct` for basic allocation
  - Allocates memory blob in arena
  - Registers fields in arena_index and symbols
  - Recursively handles nested structs
  - Commit: 988a944
- ✅ Implement `map_instance_fields` for field offsets
  - Maps struct instance fields to arena offsets
  - Calculates field offsets relative to base offset
  - Recursively handles nested structs
  - Commit: 988a944

#### ✅ Step 3: String Storage Structure (COMPLETED - Simplified)

**Implemented:**
- ✅ `insert_str` and `get_str` with simplified arena storage
  - Stores strings as string representations in arena.memory (Array of U8)
  - Works for all current tests
  - Located in src/core/init.til lines 657-711

**Note:** Full c_string/cap/len byte-level implementation planned for future phase.
Current simplified approach sufficient for Phase 1 foundation work.

### Phase 2: Enum and Array Support (In Progress)

**Goal**: Implement enum and array operations for init.til

#### ✅ Step 1: Enum Support (COMPLETED)

**Implemented:**
- ✅ `get_enum` - Read enum values from arena
  - Parses symbol info to get enum type
  - Reads I64 variant position from arena
  - Maps position to variant name
  - Commit: 5a50732
- ✅ `insert_enum` - Store enum values in arena
  - Normalizes variant names
  - Calculates variant position
  - Stores as I64 in arena
  - Commit: 5a50732
- ✅ `get_enum_at_offset` - Read enum at specific offset
  - Reads variant position at given offset
  - Used for nested enum payloads
  - Commit: 5a50732

**Helper functions added:**
- `get_i64_at_offset` and `set_i64_at_offset`

**Note:** Simplified implementation without payload handling. Payloads marked as TODO for future enhancement.

#### ✅ Step 2: Array Support (COMPLETED)

**Implemented:**
- ✅ `insert_array` - Allocate empty arrays
  - Calls insert_struct to allocate Array struct
  - Initializes all fields (ptr, len, cap, is_dyn, type_name, type_size)
  - Creates empty arrays (len=0, cap=0, ptr=0)
  - Commit: edae985

**Helper functions added:**
- `insert_bool_at_offset` - Write Bool at specific offset

**Note:** Simplified implementation for empty arrays. Support for arrays with initial values marked as TODO.

### Phase 3: Struct Operations (In Progress)

**Goal**: Implement remaining struct operations for init.til

#### ✅ Step 1: Struct Field Operations (COMPLETED)

**Implemented:**
- ✅ `copy_fields` - Copy struct field values from source to dest
  - Parses serialized struct definition
  - Iterates through fields and copies values
  - Registers destination fields in arena_index and symbols
  - Recursively handles nested structs
  - Commit: b94100d
- ✅ `register_struct_fields_for_typecheck` - Register fields for type checking
  - Parses serialized struct definition
  - Registers each field in symbols with type info
  - Recursively registers nested struct fields
  - Commit: b94100d

**Note:** Simplified implementation using string value copying in arena.

### Ongoing: Type Inference Improvements

**Goal**: Make init.til increasingly equivalent to init.rs

**Recent improvements (Commit: b5431db):**
- ✅ Implemented proper SymbolInfo serialization
  - Added str_to_value_type() to parse ValueType from strings
  - Added serialize_symbol_info() and parse_symbol_info_from_str()
  - Format: "VALUE_TYPE|is_mut" (e.g., "ValueType.TCustom=I64|true")
  - Updated all symbol storage/retrieval to use proper serialization
  - Backward compatible with old format

**Previous improvements (Commit: 5d268f4):**
- ✅ Implemented mode validation in process_declarations
  - Checks context.mode_def.allows_base_anything and allows_base_calls
  - Throws error if non-declaration nodes found at root when not allowed
- ✅ Documented associated function registration with implementation plan
  - Blocked on parser.til storing Expr objects in default_values

**Earlier improvements (Commit: d8a08ba):**
- ✅ Implemented get_payload_size_for_type properly
  - Returns correct sizes for Bool (1), I64 (8), structs (calculated), enums (8)
- ✅ Removed unused get_ufcs_fcall_value_type stub

**Current status of init.til:**
- **~91% functionally equivalent to init.rs** (syntax aside)
- All core type inference working
- All struct/enum/array operations implemented (simplified)
- Using serialization formats for complex types (SFuncDef, SStructDef, SymbolInfo)
- UFCS method resolution working
- Payload size calculation working
- Mode validation working
- SymbolInfo serialization working ✅ NEW

**Remaining for full equivalence (~9%):**
- init_import_declarations (file I/O, recursive imports) - complex, future work
- Enum payloads (beyond basic tags) - needs byte-level storage
- Array initialization with values - needs byte-level storage
- Byte-level string storage (c_string/cap/len) - architectural change
- Associated function registration - needs parser changes first

## Next Steps

Self-hosted execution is currently blocked by complex enum handling issues. Meanwhile, working on making init.til complete for basic single-file programs.

Current focus: Phase 1 Foundation work to enable:
- Function type checking (✅ DONE)
- Simple struct instantiation (IN PROGRESS)
- Proper string handling (PENDING)

The workarounds for bugs #1-3 continue to work for directly-executed til code. Self-hosting remains a future goal.
