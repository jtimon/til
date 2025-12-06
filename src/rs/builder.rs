// Builder module - orchestrates compilation to target languages
// Mirrors src/core/self/builder.til

use std::fs;
use std::io::ErrorKind;
use crate::rs::lexer::lexer_from_source;
use crate::rs::parser::parse_tokens;
use crate::rs::mode::parse_mode;
use crate::rs::codegen_c;

// Build a TIL source file to C (default target)
pub fn build(path: &str) -> Result<(), String> {
    println!("Building file '{}'", path);

    // Read source file
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                return Err(format!("File '{}' not found.", path))
            },
            other_error => {
                return Err(format!("Problem opening the file '{}': {:?}", path, other_error))
            },
        },
    };

    // Lex
    let mut lexer = match lexer_from_source(&path.to_string(), source) {
        Ok(result) => result,
        Err(error_string) => {
            return Err(format!("{}:{}", path, error_string));
        },
    };

    // Parse mode (skip it for codegen)
    let _mode = parse_mode(&path.to_string(), &mut lexer)?;

    // Parse body
    let ast = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            return Err(format!("{}:{}", path, error_string));
        },
    };

    // Generate C code
    let c_code = codegen_c::emit(&ast)?;

    // Write output file
    let output_path = path.replace(".til", ".c");
    match fs::write(&output_path, &c_code) {
        Ok(_) => {
            println!("Wrote C output to '{}'", output_path);
            Ok(())
        },
        Err(e) => Err(format!("Failed to write '{}': {}", output_path, e)),
    }
}
