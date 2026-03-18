#include "modes.h"
#include <string.h>

// --- Mode constants ---

Mode MODE_SCRIPT = {STR_LIT("script"), 0, 0, STR_EMPTY, 0, 0};
Mode MODE_CLI    = {STR_LIT("cli"),    1, 1, STR_EMPTY, 0, 0};
Mode MODE_GUI    = {STR_LIT("gui"),    1, 1, STR_LIT("gui"), 0, 0};
Mode MODE_TEST   = {STR_LIT("test"),   0, 1, STR_EMPTY, 0, 0};
Mode MODE_PURE   = {STR_LIT("pure"),   0, 1, STR_EMPTY, 1, 0};
Mode MODE_PURA   = {STR_LIT("pura"),   0, 1, STR_EMPTY, 1, 1};
Mode MODE_LIB    = {STR_LIT("lib"),    0, 1, STR_EMPTY, 0, 0};
Mode MODE_LIBA   = {STR_LIT("liba"),   0, 1, STR_EMPTY, 0, 1};

// --- Mode helpers ---

Mode *mode_resolve(Str *name) {
    if (!name) return NULL;
    if ((name->count == 6 && memcmp(name->c_str, "script", 6) == 0)) return &MODE_SCRIPT;
    if ((name->count == 3 && memcmp(name->c_str, "cli", 3) == 0))    return &MODE_CLI;
    if ((name->count == 3 && memcmp(name->c_str, "gui", 3) == 0))    return &MODE_GUI;
    if ((name->count == 4 && memcmp(name->c_str, "test", 4) == 0))   return &MODE_TEST;
    if ((name->count == 4 && memcmp(name->c_str, "pure", 4) == 0))   return &MODE_PURE;
    if ((name->count == 4 && memcmp(name->c_str, "pura", 4) == 0))   return &MODE_PURA;
    if ((name->count == 3 && memcmp(name->c_str, "lib", 3) == 0))    return &MODE_LIB;
    if ((name->count == 4 && memcmp(name->c_str, "liba", 4) == 0))   return &MODE_LIBA;
    return NULL;
}

// Bridge-only functions (Mode_eq, mode_script/cli/etc getters,
// mode_name, mode_auto_import) removed — only til_bridge.c uses them.

Bool mode_is_lib(Mode *m) {
    return m && (m == &MODE_LIB || m == &MODE_LIBA);
}
Bool mode_is_lib_output(Mode *m) {
    return m && (m == &MODE_LIB || m == &MODE_LIBA ||
                 m == &MODE_PURE || m == &MODE_PURA);
}
