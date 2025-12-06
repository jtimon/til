// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal};

// Emit C code from AST (wraps in main)
pub fn emit(ast: &Expr) -> Result<String, String> {
    let mut output = String::new();

    // C boilerplate
    output.push_str("#include <stdio.h>\n\n");
    output.push_str("int main() {\n");

    // Emit body
    emit_expr(ast, &mut output, 1)?;

    output.push_str("    return 0;\n");
    output.push_str("}\n");

    Ok(output)
}

fn emit_expr(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    match &expr.node_type {
        NodeType::Body => emit_body(expr, output, indent),
        NodeType::FCall => emit_fcall(expr, output, indent),
        NodeType::LLiteral(lit) => emit_literal(lit, output),
        other => Err(format!("codegen_c: unsupported node type: {:?}", other)),
    }
}

fn emit_body(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    for child in &expr.params {
        emit_expr(child, output, indent)?;
    }
    Ok(())
}

fn emit_fcall(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    // First param is the function name
    if expr.params.is_empty() {
        return Err("codegen_c: FCall with no params".to_string());
    }

    let func_name = match &expr.params[0].node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return Err("codegen_c: FCall first param not Identifier".to_string()),
    };

    let indent_str = "    ".repeat(indent);

    // Hardcoded builtins
    match func_name.as_str() {
        "println" => {
            output.push_str(&indent_str);
            output.push_str("printf(");
            // Emit args
            for (i, arg) in expr.params.iter().skip(1).enumerate() {
                if i > 0 {
                    output.push_str(", ");
                }
                emit_expr(arg, output, 0)?;
            }
            output.push_str("\"\\n\");\n");
            Ok(())
        },
        "print" => {
            output.push_str(&indent_str);
            output.push_str("printf(");
            for (i, arg) in expr.params.iter().skip(1).enumerate() {
                if i > 0 {
                    output.push_str(", ");
                }
                emit_expr(arg, output, 0)?;
            }
            output.push_str(");\n");
            Ok(())
        },
        _ => Err(format!("codegen_c: unknown function '{}'", func_name)),
    }
}

fn emit_literal(lit: &Literal, output: &mut String) -> Result<(), String> {
    match lit {
        Literal::Str(s) => {
            output.push('"');
            output.push_str(s);
            output.push('"');
            Ok(())
        },
        Literal::Number(n) => {
            output.push_str(n);
            Ok(())
        },
        _ => Err("codegen_c: unsupported literal type".to_string()),
    }
}
