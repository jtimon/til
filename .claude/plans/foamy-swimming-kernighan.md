# Bug #168: ccodegen return values create copies the interpreter doesn't

## Context

The interpreter returns structs via shared offsets (zero copies). The ccodegen
creates memcpy copies on every struct return:

- **Non-throwing functions**: return by value (`return local;` + `dest = func();`)
  = 2 implicit memcpys
- **Throwing functions**: already use out-pointer (`*_ret = local;`) but then
  copy at call site (`dest = _ret_N;`) = 2 explicit memcpys

This is the root cause of the memory leak gap between interpreter and compiled
code, and blocks #117 -> #80 -> #100 (self-hosting).

**Goal**: Every struct-returning call has at most 1 copy (`*_ret = local` inside
the callee). Call sites pass destination address directly -- no intermediate temp.

---

## Commit 1: Throwing calls -- eliminate intermediate `_ret_N` temp

Throwing functions already use the out-pointer pattern. The only problem is
the unnecessary intermediate temp at call sites:

```c
// BEFORE (current):
til_Str _ret_N;                              // temp
int _status_N = func(&_ret_N, &_err, args);  // write to temp
dest = _ret_N;                               // UNNECESSARY COPY

// AFTER:
int _status_N = func(&dest, &_err, args);    // write to dest directly
```

### Step 1: Add `build_dest_ptr_expr` helper (ccodegen.rs ~line 4530)

Given `decl_name` or `assign_name`, compute the address expression to pass
as `_ret`:

| Case | assign_name | Address expression |
|------|-------------|--------------------|
| Declaration | decl_name="x" | `&til_Str_x` |
| Simple var | "x" | `&til_Str_x` |
| Return value | "*_ret" | `_ret` (strip `*`) |
| Ref param field | "self.field" | `&(til_T_self->field)` |
| Local field | "x.field" | `&(til_T_x.field)` |
| Ref param direct | "x" (is ref) | `til_T_x` (already ptr) |
| Discarded (_ or None) | -- | keep using `_ret_N` temp |

Returns `None` if we must fall back to temp (discarded result).

### Step 2: Modify `emit_throwing_call_propagate` (ccodegen.rs:4530-4790)

- Lines 4593-4599 (temp declaration): Skip when `build_dest_ptr_expr`
  returns Some. Only declare `_ret_N` when result is discarded.
- Lines 4650-4661 (function call): Instead of `&_ret_N`, use the
  destination pointer expression.
- Lines 4749-4787 (the copy): Skip entirely when using direct dest pointer.
  The function already wrote to the destination.

### Step 3: Modify `emit_throwing_call_with_goto` (ccodegen.rs:4794-5068)

Same changes as Step 2 -- identical structure. Lines 4856-4862 (temp),
4913-4925 (call), 5026-5065 (copy).

### Step 4: Port to ccodegen.til

Same changes in `src/self/ccodegen.til`.

### Verify: `make benchmark`

---

## Commit 2: Non-throwing struct returns -- switch to out-pointer

Change non-throwing struct-returning functions from return-by-value to
out-pointer, matching the pattern throwing functions already use.

```c
// BEFORE:
til_Vec til_Vec_new(til_Type T) {
    til_Vec vec = {...};
    return vec;            // implicit memcpy
}
til_Vec dest = til_Vec_new(T);  // implicit memcpy

// AFTER:
void til_Vec_new(til_Vec* _ret, til_Type T) {
    til_Vec vec = {...};
    *_ret = vec;           // one copy
    return;
}
til_Vec dest;
til_Vec_new(&dest, T);    // zero copies at call site
```

### Step 5: Add `needs_out_pointer` helper (ccodegen.rs ~line 172)

Includes Str (heap data), Vec, Array, Map, Set, List, all user structs.
Excludes Ptr (small), I64, U8, Bool, Dynamic, Type.

### Step 6: Modify `emit_func_signature` (ccodegen.rs:3370-3479)

Non-throwing branch: when `needs_out_pointer(ret_type)`, emit `void` instead
of `RetType` and add `RetType* _ret` as first parameter.

### Step 7: Modify `emit_return` (ccodegen.rs:5647-5773)

When `needs_out_pointer(current_return_type)`:
- Regular return: `return value;` -> `*_ret = value; return;`
- Return of non-throwing struct call: `return other()` -> `other(_ret, args); return;`
- Variadic return: same pattern

### Step 8: Modify implicit return fallbacks (3 locations)

`return (Type){0};` -> `return;` when `needs_out_pointer`.

### Step 9: Modify `emit_fcall_arg_string` (ccodegen.rs:1596-1648)

For non-throwing struct-returning calls used as arguments: hoist to temp.

### Step 10: Modify `emit_declaration` for direct out-pointer

When RHS is a non-throwing struct-returning FCall: declare var first, call
with `&var` as `_ret`.

### Step 11: Modify `emit_assignment` for direct out-pointer

When RHS is a non-throwing struct-returning FCall: call with `&dest` as `_ret`.

### Step 12: Update ext.c

Change `til_i64_to_str` and `til_fs_parent_dir` signatures to out-pointer.

### Step 13: Port all to ccodegen.til

### Verify: `make benchmark`

---

## Not changed (scope exclusions)

- `emit_enum_to_str_function` -- returns Str with borrowed literals, safe
- Enum `_make_Variant` constructors -- inline, typically no heap pointers

## Key Files

| File | Commit | Changes |
|------|--------|---------|
| `src/rs/ccodegen.rs` | 1, 2 | All major codegen changes |
| `src/self/ccodegen.til` | 1, 2 | TIL port of all changes |
| `src/ext.c` | 2 | Update 2 function signatures |
