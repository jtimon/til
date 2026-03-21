// FFI bridge for til.til — thin wrappers around C module APIs.
// Converts Str* ↔ const char*, handles output params, provides Expr field accessors.

#include "../../bootstrap/modes.h"
#include "pre70.h"
#include "interpreter.h"
#include "builder.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

// Replace children: old children are freed, new_children is moved in
void expr_swap_children(Expr *e, Vec *new_children) {
    Vec_delete(&e->children, &(Bool){0});
    e->children = *new_children;
    memset(new_children, 0, sizeof(Vec));
}


