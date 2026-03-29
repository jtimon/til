#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LIT(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)(sizeof(s) - 1), .cap=CAP_LIT})
#define STR_VIEW(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)strlen((const char *)(s)), .cap=CAP_VIEW})

// --- Type inference/checking pass ---

// --- Collection literal helpers ---

// --- Set literal desugaring ---
// Transforms s := {v1, v2, v3} into:
//   mut s := Set.new(elem_type, elem_size)
//   Set.add(s, own v1)
//   Set.add(s, own v2)
//   Set.add(s, own v3)

// --- Map literal desugaring ---
// Transforms m := {k1: v1, k2: v2} into:
//   mut m := Map.new(key_type, key_size, val_type, val_size)
//   Map.set(m, own k1, own v1)
//   Map.set(m, own k2, own v2)

// --- Variadic call desugaring ---
// Transforms variadic function calls into Array.new + Array.set + normal call.
// Must run before hoisting so that synthetic Array calls get hoisted too.

// Create a namespace method call: StructName.method(args...)
// --- Kwargs call desugaring ---
// Transforms kwargs function calls into Map.new + Map.set + normal call.

// --- Argument hoisting ---


// Check if a function call returns ref

// --- Delete call insertion ---
