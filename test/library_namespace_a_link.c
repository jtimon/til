I64 library_link_global = 10;

I64 library_link_helper(I64 value) {
    return value + library_link_global;
}

// The generated library defines a ref global as a C pointer variable. Move
// that pointer to another U64-layout object after the interpreter has already
// registered its original pointee.
extern BindingWidths *library_widths_cursor;
extern BindingWidths library_widths_other;

void library_widths_cursor_advance_native(void) {
    library_widths_cursor = &library_widths_other;
}

USize library_widths_cursor_second_native(void) {
    return library_widths_cursor->second;
}

// A C-managed one-slot pool releases a borrowed target-layout object and
// immediately reuses the same address for raw host-layout bytes. Unlike
// malloc/free reuse this is deterministic under ASAN and on every host.
static union {
    BindingWidths target;
    U8 host[sizeof(BindingWidths)];
} library_widths_pool;

BindingWidths *library_widths_pool_borrow_native(void) {
    library_widths_pool.target = (BindingWidths){.first = 101, .second = 203, .marker = 307};
    return &library_widths_pool.target;
}

void library_widths_pool_reuse_native(void) {
    // The caller has ended its ref scope. Its old target object is no longer
    // live; the next borrowed pointer names the same bytes as a raw buffer.
}

U8 *library_widths_pool_host_native(void) {
    return library_widths_pool.host;
}
