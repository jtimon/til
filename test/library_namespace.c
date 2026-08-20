#include "library_namespace_a.h"
#include "library_namespace_b.h"

int main(void) {
    if (til_library_x5fnamespace_x5fa__library_namespace_a_value() != 21) return 1;
    if (til_library_x5fnamespace_x5fb__library_namespace_b_value() != 42) return 2;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_link_value() != 21) return 3;
    if (til_library_x5fnamespace_x5fb__library_namespace_b_link_value() != 42) return 4;
    if (til_library_x5fnamespace_x5fa__library_namespace_a_extra_link_value() != 22) return 5;
    return 0;
}
