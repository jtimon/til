#include "library_namespace_a.h"
#include "library_namespace_b.h"

int main(void) {
    if (til_library_x5fnamespace_x5fa__library_namespace_a_value() != 21) return 1;
    if (til_library_x5fnamespace_x5fb__library_namespace_b_value() != 42) return 2;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_link_value() != 21) return 3;
    if (til_library_x5fnamespace_x5fb__library_namespace_b_link_value() != 42) return 4;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_extra_link_value() != 22) return 5;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_count != 17) return 6;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_state != 23) return 7;
    if (til_library_x5fnamespace_x5fa__BindingPoint_COUNT != 5) return 8;
    if (til_library_x5fnamespace_x5fa__BindingPoint_STATE != 6) return 9;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_global_sum() != 51) return 10;
    til_library_x5fnamespace_x5fa__library_namespace_a_state = 30;
    til_library_x5fnamespace_x5fa__BindingPoint_STATE = 8;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_global_sum() != 60) return 11;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_origin.scalar != 19) return 12;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_point_state.scalar != 20) return 13;
    til_library_x5fnamespace_x5fa__library_namespace_a_point_state.scalar = 24;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_point_state.scalar != 24) return 14;
    return 0;
}
