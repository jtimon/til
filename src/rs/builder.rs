// Builder module - orchestrates compilation to target languages
// Mirrors src/core/self/builder.til

// use crate::rs::codegen_c;  // TODO: enable when codegen is ready

// Build a TIL source file to C (default target)
pub fn build(path: &str) -> Result<(), String> {
    Err(format!("TODO: build '{}': C codegen not implemented", path))
}
