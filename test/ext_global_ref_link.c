#include "ext.h"

// The forward header is force-included by the builder: RefPoint is the
// ext_struct test/ext_global_ref.til declares.

// Two slots and one POINTER variable the C side re-points. A til `ref`
// bound to ext_global_ref_cursor borrows THROUGH the variable, so after
// ext_global_ref_advance it must read slot_b -- in both backends.
I64 ext_global_ref_slot_a = 44;
I64 ext_global_ref_slot_b = 45;
I64 *ext_global_ref_cursor = &ext_global_ref_slot_a;

void ext_global_ref_advance(void) {
    ext_global_ref_cursor = &ext_global_ref_slot_b;
}

I64 ext_global_ref_slot_b_value(void) {
    return ext_global_ref_slot_b;
}

// A pointer to an aggregate: field reads go through the pointer.
RefPoint ext_global_ref_point_storage = {3, 4};
RefPoint *ext_global_ref_point = &ext_global_ref_point_storage;
