# Pre-Self-Hosting Priority Analysis

**Date:** 2025-11-20
**Purpose:** Identify features from post.org that should be implemented BEFORE self-hosting

## Executive Summary

After reviewing the post-self-hosting TODO list, I've identified several features that could significantly benefit the self-hosting effort itself. While most items can genuinely wait, a few stand out as high-value investments that would make the self-hosting development process smoother, safer, and more maintainable.

---

## Critical Priority - Fix Before Self-Hosting

### 1. Variable Shadowing Bug (MEDIUM → HIGH) ✅ CONFIRMED BUG

**Location:** doc/todo/post.org:148-270
**Current Status:** Nested-scope shadowing MUTATES outer variables instead of creating new bindings
**Design Decision:** TIL will ALLOW shadowing (like Rust) - decided 2025-11-20

**Why This Is Critical:**
```til
z := 5
{
    z := 10  // BUG: This mutates outer z instead of creating inner binding
}
// z is now 10, not 5! (WRONG - should be 5)
```

**Root Cause Found:**
- `declare_symbol`/`insert_var` use `HashMap.insert()` which replaces existing values
- Nested blocks don't create new scope frames
- When inner `:=` is used, it mutates the HashMap entry → looks like mutation instead of shadowing

**Residual Code Preventing Shadowing (Option A residues):**
1. **src/rs/init.rs:898-900** - `init_context` prevents global shadowing (ACTIVE - needs removal)
2. **src/rs/init.rs:120-137** - `declare_var` has shadowing check (UNUSED - never called)

This is not a design question—it's a **correctness bug**. During self-hosting, the compiler will have complex nested scopes. This bug could cause:
- Silent data corruption
- Extremely difficult-to-debug issues
- Incorrect code generation

**Recommendation:** **FIX IMMEDIATELY** before self-hosting.

**What Needs Fixing:**
1. Remove shadowing prevention check in `init_context` (line 898-900)
2. Implement proper shadowing in nested blocks
3. Allow type-change shadowing (`x := 5` then `x := "hello"`)
4. Remove or modify unused `declare_var` function

---

## High Priority - Strongly Consider Before Self-Hosting

### 2. Unicode Support (MEDIUM → HIGH)

**Location:** doc/todo/post.org:194-224
**Current Status:** Lexer panics on multi-byte UTF-8 characters

**Why This Matters:**
```
byte index 368 is not a char boundary; it is inside '✓' (bytes 367..370)
```

**Impact on Self-Hosting:**
- Self-hosted compiler WILL encounter Unicode in real-world code
- Crashes are unacceptable for a production compiler
- Even if TIL source is ASCII-only, string literals may contain Unicode
- Comments might contain Unicode (developer names, documentation)

**Current Workaround:** "Use ASCII-only characters everywhere"
**Problem:** This isn't sustainable for a production compiler

**Recommendation:** **Implement before self-hosting**. A compiler that crashes on Unicode is not production-ready.

**Effort:** Update lexer.rs to use `chars()` iterator instead of byte indexing. Moderate effort, high value.

---

### 3. Better Error Messages & Backtraces (MEDIUM → HIGH)

**Location:** doc/todo/post.org:955-973
**Current Issues:**
- No stack traces for runtime errors
- Circular dependency errors lack detail
- No source location tracking in many errors

**Why This Matters for Self-Hosting:**

When developing a self-hosted compiler, you'll encounter:
- Complex error scenarios (parsing, type checking, codegen)
- Deep call stacks
- Subtle bugs that are hard to reproduce

**Without good error messages:**
- Debugging takes 10x longer
- Developers waste time tracking down error locations
- Bugs that should take 5 minutes take hours

**Recommendation:** **Invest in this before self-hosting**. Good developer experience during self-hosting pays massive dividends.

**Specific Improvements:**
1. Add source location to ALL errors (file, line, column)
2. Implement runtime stack traces showing call chain
3. Add "did you mean X?" suggestions for common mistakes
4. Better formatting (show source code snippet with error)

---

## Medium Priority - Would Help Self-Hosting

### 4. Namespace-Style Imports (MEDIUM)

**Location:** doc/todo/post.org:225-290
**Current Problem:** All imports pollute global namespace

**Why This Helps:**
```til
// Current: Everything in global scope
import("src/core/parser")
import("src/core/lexer")
parse(tokens)  // Which module is this from?

// Desired: Namespaced imports
parser := import("src/core/parser")
lexer := import("src/core/lexer")
ast := parser.parse(tokens)  // Clear origin
tokens := lexer.scan(source)
```

**Self-Hosting Benefits:**
- Self-hosted compiler will have MANY modules (lexer, parser, typer, interpreter, etc.)
- Name conflicts are likely (Token, Node, Error all appear in multiple modules)
- Code clarity: `parser.Node` vs `lexer.Token` is self-documenting
- Easier refactoring: Know exactly which module each function comes from

**Recommendation:** **Consider implementing**. Not critical, but would make self-hosted codebase much cleaner.

**Effort:** Moderate. Requires:
- Import to return module-like struct
- Type checker to handle namespace types
- Dot notation for module member access

---

### 5. Dynamic Type Field/Method Access (MEDIUM)

**Location:** doc/todo/post.org:13-66
**Current Limitation:** Can pass Dynamic to functions, but can't access fields/methods

```til
test_field_access := proc(obj: Dynamic) returns I64 {
    return obj.x  // ERROR: Struct 'Dynamic' has no member 'x'
}
```

**Why This Might Matter:**
- If self-hosted code uses Dynamic for flexibility, this limitation is painful
- Workarounds exist (use concrete types), but reduce flexibility

**Recommendation:** **Optional**. Check if self-hosted code actually uses Dynamic extensively. If yes, implement. If no, defer.

---

### 6. Add More Test Cases (MEDIUM)

**Location:** doc/todo/post.org:1009-1024
**Current State:** Test coverage has gaps

**Why This Matters:**
- Self-hosted compiler will stress-test EVERY language feature
- Bugs found during self-hosting are much more painful to fix than bugs found in unit tests
- Edge cases in type checking, pattern matching, error handling need coverage

**Recommendation:** **Invest in testing**. Specifically:
1. Edge cases in type checking (complex nested types, circular references)
2. Pattern matching with enums + structs
3. Error handling (throw/catch chains, multiple error types)
4. Memory operations (structs, arrays, nested data structures)

**Effort:** Ongoing. Add tests as you encounter untested scenarios.

---

## Low Priority - Can Genuinely Wait

The following features are genuinely post-self-hosting:

### Language Features That Have Workarounds
- **Enum Tag Comparison** (LOW): Switch statements work fine
- **List/Tuple Support** (LOW): Arrays and structs sufficient
- **Negative Number Literals** (LOW): `sub(0, n)` acceptable
- **Match Keyword** (MEDIUM): Switch is equivalent
- **Guards in Pattern Matching** (LOW): If-statements work
- **Struct Literals** (LOW): Constructor functions work
- **Default Keyword for Switch** (LOW): Syntax preference only

### Advanced Features Not Needed Yet
- **Own Keyword** (MEDIUM): Move semantics can wait
- **Mode Safe** (MEDIUM): Borrow checker is ambitious future work
- **safe_script Mode** (MEDIUM): Not needed for compiler development
- **pure Mode** (LOW): Functional purity enforcement not critical
- **Macro System** (LOW): Power feature, not needed yet

### Performance & Optimization
- **All Performance TODOs** (LOW): Correctness first, speed later
- Self-hosting doesn't need to be fast initially

### Enhancements to Working Features
- **Error Handling Enhancements** (MEDIUM): Current throw/catch works
  - PanicError, Result<T,E>, rethrow, try operator (?) are nice-to-haves
  - Finally blocks are convenience
- **Cast Operations** (LOW): Manual conversion functions sufficient
- **Operator Overloading** (MEDIUM): UFCS provides method syntax already

### Code Quality
- **Code Quality Improvements** (LOW): Works, can be cleaned up later
- **Better Import Caching** (MEDIUM): Not a correctness issue

---

## Recommendation Summary (Updated 2025-11-20)

### Must Fix (Critical Bugs)
1. ✅ **Variable Shadowing Bug** - Correctness issue, could cause severe bugs
   - Remove shadowing prevention in init_context (src/rs/init.rs:898-900)
   - Implement proper nested-scope shadowing
   - Allow type-change shadowing

### Strongly Recommend (High Value for Self-Hosting)
2. ✅ **Better Error Messages** - Massive productivity boost during development
   - Always valuable, but identify specific bad error messages first
   - Ongoing improvement, not a one-time fix

### Consider (Would Help)
3. ⚠️ **Test Coverage** - Find bugs early, before they're in self-hosted compiler
   - Always valuable, but which specific tests are missing?
   - Needs analysis to identify gaps

### Not Recommended (Explicitly Deferred)
- ❌ **Unicode Support** - Explicitly decided NOT to do before self-hosting
- ❌ **Namespace-Style Imports** - Not easy at the moment, defer
- ❌ **Dynamic Field/Method Access** - Only if heavily used (unlikely)

### Defer (Genuinely Post-Self-Hosting)
- Everything else can wait

---

## Implementation Strategy (Revised)

### Phase 1: Critical Bug Fix (Do First)
1. **Fix variable shadowing bug**
   - Remove check at src/rs/init.rs:898-900
   - Implement proper nested-scope shadowing
   - Test thoroughly with nested blocks

### Phase 2: Ongoing Improvements (As Needed)
2. **Better error messages** - Identify and fix specific bad errors as encountered
3. **Test coverage** - Add tests for specific gaps as discovered

### Phase 3: Deferred (Post-Self-Hosting)
- Unicode support
- Namespace imports
- All other enhancements

---

## Rationale

The key insight is: **Some "post-self-hosting" features would actually make self-hosting development EASIER**.

- Unicode support prevents crashes
- Good error messages speed up debugging 10x
- Namespace imports prevent name conflicts in large codebase
- The variable shadowing bug could cause catastrophic issues

The other features are genuinely deferrable because:
- They have acceptable workarounds
- They're not needed for compiler functionality
- They're optimizations, not correctness fixes
- They're advanced features beyond initial self-hosting scope

---

## Questions for Decision Making

1. **How many modules will the self-hosted compiler have?**
   - If 10+, namespace imports become valuable
   - If 3-5, current import system might suffice

2. **Will Dynamic types be used extensively?**
   - Check current self-hosting plan
   - If yes, field/method access matters
   - If no, can defer

3. **What's the timeline?**
   - If self-hosting starts soon, prioritize fixes now
   - If months away, can implement more enhancements

4. **How much development pain is acceptable?**
   - High pain tolerance → minimal changes
   - Low pain tolerance → invest in DX improvements

---

## Conclusion (Updated 2025-11-20)

**Must do before self-hosting:**
1. **Fix variable shadowing bug** (correctness) - This is a real bug that causes silent data corruption

**Ongoing improvements (pre and post):**
2. **Better error messages** (productivity) - Identify specific bad errors and fix as encountered
3. **Test coverage** (quality) - Add tests for specific gaps as discovered

**Explicitly NOT doing before self-hosting:**
- Unicode support - Deferred to post-self-hosting
- Namespace imports - Too complex at the moment
- All other enhancements from post.org

**Everything else:** Genuinely can wait until after self-hosting is working.

The philosophy: **Fix critical correctness bugs, then proceed with self-hosting**. The shadowing bug is the only blocking issue. Error messages and tests are ongoing improvements that happen both before and after self-hosting.
