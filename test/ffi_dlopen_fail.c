// Issue #283 regression fixture.
//
// til_283_undefined_symbol is declared but never defined anywhere, so the
// shared object links fine (ELF shared objects allow undefined symbols) yet
// dlopen(..., RTLD_NOW) rejects it because the symbol cannot be resolved.
// Running this file under `til interpret` therefore drives ffi_init_user_so
// down its "dlopen failed for '<path>': <loader error>" runtime branch.
//
// That diagnostic must survive const-folding: stderr_print / ffi_last_error
// are ext_proc (side-effecting), never folded, so the print stays in the
// compiled compiler instead of being executed at build time and dropped from
// the runtime. See src/self/interpreter.til.

extern long til_283_undefined_symbol(void);

long til_283_boom(void) {
    return til_283_undefined_symbol();
}
