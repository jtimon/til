// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::Expr;

// Emit C code from AST
pub fn emit(_ast: &Expr) -> Result<String, String> {
    Err("TODO: C codegen: emit not implemented".to_string())
}
