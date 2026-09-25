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
