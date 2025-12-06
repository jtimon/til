// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal, SFuncDef};

// Emit C code from AST (three-pass: structs, functions, then main)
pub fn emit(ast: &Expr) -> Result<String, String> {
    let mut output = String::new();

    // C boilerplate
    output.push_str("#include <stdio.h>\n\n");

    // First pass: emit struct definitions (before functions)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_declaration(child, &mut output)?;
            }
        }
    }

    // Second pass: emit function definitions (before main)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_declaration(child, &mut output)?;
            }
        }
    }

    // Main function
    output.push_str("int main() {\n");

    // Third pass: emit non-struct, non-function statements
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if !is_func_declaration(child) && !is_struct_declaration(child) {
                emit_expr(child, &mut output, 1)?;
            }
        }
    }

    output.push_str("    return 0;\n");
    output.push_str("}\n");

    Ok(output)
}

// Check if an expression is a struct declaration (Name := struct {...})
fn is_struct_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(_) = &expr.params[0].node_type {
                return true;
            }
        }
    }
    false
}

// Emit a struct declaration as a C typedef struct
fn emit_struct_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                output.push_str("typedef struct {\n");
                for member in &struct_def.members {
                    output.push_str("    ");
                    output.push_str(&til_type_to_c(&member.value_type));
                    output.push_str(" ");
                    output.push_str(&member.name);
                    output.push_str(";\n");
                }
                output.push_str("} ");
                output.push_str(&decl.name);
                output.push_str(";\n\n");
                return Ok(());
            }
        }
    }
    Err("emit_struct_declaration: not a struct declaration".to_string())
}

// Convert TIL type to C type
fn til_type_to_c(til_type: &crate::rs::parser::ValueType) -> String {
    match til_type {
        crate::rs::parser::ValueType::TCustom(name) => {
            match name.as_str() {
                "I64" => "long long".to_string(),
                "I32" => "int".to_string(),
                "Bool" => "unsigned char".to_string(),
                "U8" => "unsigned char".to_string(),
                "Str" => "const char*".to_string(),
                _ => name.clone(), // Assume it's a struct type
            }
        },
        _ => "int".to_string(), // Default
    }
}

// Check if an expression is a function declaration (name := proc/func)
fn is_func_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(_) = &expr.params[0].node_type {
                return true;
            }
        }
    }
    false
}

// Emit a function declaration as a C function
fn emit_func_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Return type
                if func_def.return_types.is_empty() {
                    output.push_str("void ");
                } else {
                    output.push_str(&til_type_to_c(&func_def.return_types[0]));
                    output.push_str(" ");
                }

                output.push_str(&decl.name);
                output.push_str("(");

                // Parameters
                for (i, arg) in func_def.args.iter().enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    output.push_str(&til_type_to_c(&arg.value_type));
                    output.push_str(" ");
                    output.push_str(&arg.name);
                }
                output.push_str(") {\n");

                // Emit function body
                for stmt in &func_def.body {
                    emit_expr(stmt, output, 1)?;
                }
                output.push_str("}\n\n");
                return Ok(());
            }
        }
    }
    Err("emit_func_declaration: not a function declaration".to_string())
}

fn emit_expr(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    match &expr.node_type {
        NodeType::Body => emit_body(expr, output, indent),
        NodeType::FCall => emit_fcall(expr, output, indent),
        NodeType::LLiteral(lit) => emit_literal(lit, output),
        NodeType::Declaration(decl) => emit_declaration(&decl.name, decl.is_mut, expr, output, indent),
        NodeType::Identifier(name) => {
            output.push_str(name);
            // Handle field access (b.val -> b.val)
            for param in &expr.params {
                if let NodeType::Identifier(field) = &param.node_type {
                    output.push_str(".");
                    output.push_str(field);
                }
            }
            Ok(())
        },
        NodeType::FuncDef(func_def) => emit_funcdef(func_def, expr, output, indent),
        NodeType::Assignment(name) => emit_assignment(name, expr, output, indent),
        NodeType::Return => emit_return(expr, output, indent),
        other => Err(format!("codegen_c: unsupported node type: {:?}", other)),
    }
}

fn emit_body(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    for child in &expr.params {
        emit_expr(child, output, indent)?;
    }
    Ok(())
}

fn emit_declaration(name: &str, is_mut: bool, expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Check if this is a struct construction (TypeName())
    let struct_type = if !expr.params.is_empty() {
        get_struct_construction_type(&expr.params[0])
    } else {
        None
    };

    if let Some(type_name) = struct_type {
        // Struct variable declaration
        output.push_str(&indent_str);
        output.push_str(&type_name);
        output.push_str(" ");
        output.push_str(name);
        output.push_str(" = {0};\n");
    } else if is_mut {
        output.push_str(&indent_str);
        output.push_str("int ");
        output.push_str(name);
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0)?;
        }
        output.push_str(";\n");
    } else {
        // const declaration
        output.push_str(&indent_str);
        output.push_str("const int ");
        output.push_str(name);
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0)?;
        }
        output.push_str(";\n");
    }
    Ok(())
}

// Check if an expression is a struct construction call (TypeName())
// Returns the type name if it is, None otherwise
fn get_struct_construction_type(expr: &Expr) -> Option<String> {
    if let NodeType::FCall = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(name) = &expr.params[0].node_type {
                // If it's a PascalCase identifier with no nested params and no other args, assume struct
                if name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false)
                    && expr.params.len() == 1
                    && expr.params[0].params.is_empty() {
                    return Some(name.clone());
                }
            }
        }
    }
    None
}

fn emit_funcdef(_func_def: &SFuncDef, expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    // For now, just inline the function body (we're inside main anyway)
    // TODO: proper function generation with prototypes
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("{\n");
    for stmt in &expr.params {
        emit_expr(stmt, output, indent + 1)?;
    }
    output.push_str(&indent_str);
    output.push_str("}\n");
    Ok(())
}

fn emit_assignment(name: &str, expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str(name);
    output.push_str(" = ");
    if !expr.params.is_empty() {
        emit_expr(&expr.params[0], output, 0)?;
    }
    output.push_str(";\n");
    Ok(())
}

fn emit_return(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("return");
    if !expr.params.is_empty() {
        output.push_str(" ");
        emit_expr(&expr.params[0], output, 0)?;
    }
    output.push_str(";\n");
    Ok(())
}

fn emit_fcall(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    // First param is the function name (or UFCS receiver.method)
    if expr.params.is_empty() {
        return Err("codegen_c: FCall with no params".to_string());
    }

    // Check for UFCS: first param is Identifier with nested params (method name)
    let (func_name, ufcs_receiver) = match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                // Regular function call
                (name.clone(), None)
            } else {
                // UFCS: receiver.method() - method name is in nested params
                if let NodeType::Identifier(method_name) = &expr.params[0].params[0].node_type {
                    (method_name.clone(), Some(&expr.params[0]))
                } else {
                    return Err("codegen_c: UFCS method name not Identifier".to_string());
                }
            }
        },
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
        // Arithmetic operations - emit as C expressions
        "add" => emit_binop(expr, output, "+", ufcs_receiver),
        "sub" => emit_binop(expr, output, "-", ufcs_receiver),
        "mul" => emit_binop(expr, output, "*", ufcs_receiver),
        "div" => emit_binop(expr, output, "/", ufcs_receiver),
        "mod" => emit_binop(expr, output, "%", ufcs_receiver),
        // Comparison
        "eq" => emit_binop(expr, output, "==", ufcs_receiver),
        "lt" => emit_binop(expr, output, "<", ufcs_receiver),
        "gt" => emit_binop(expr, output, ">", ufcs_receiver),
        "lteq" => emit_binop(expr, output, "<=", ufcs_receiver),
        "gteq" => emit_binop(expr, output, ">=", ufcs_receiver),
        // test(loc, cond, msg) - emit as assertion
        "test" => {
            // For C codegen, we just emit the test as an if statement
            // test(loc, cond, msg) -> if (!(cond)) { printf("FAIL: %s\n", msg); }
            if expr.params.len() < 4 {
                return Err("codegen_c: test requires 3 arguments".to_string());
            }
            output.push_str(&indent_str);
            output.push_str("if (!(");
            emit_expr(&expr.params[2], output, 0)?;
            output.push_str(")) { printf(\"FAIL: %s\\n\", ");
            emit_expr(&expr.params[3], output, 0)?;
            output.push_str("); }\n");
            Ok(())
        },
        // assert_eq(loc, expected, actual) - emit as equality check
        "assert_eq" => {
            if expr.params.len() < 4 {
                return Err("codegen_c: assert_eq requires 3 arguments".to_string());
            }
            output.push_str(&indent_str);
            output.push_str("if ((");
            emit_expr(&expr.params[2], output, 0)?;
            output.push_str(") != (");
            emit_expr(&expr.params[3], output, 0)?;
            output.push_str(")) { printf(\"FAIL: assert_eq\\n\"); }\n");
            Ok(())
        },
        // loc() - just emit empty string for now
        "loc" => {
            output.push_str("\"\"");
            Ok(())
        },
        // User-defined function call
        _ => {
            output.push_str(&indent_str);
            output.push_str(&func_name);
            output.push_str("(");
            // Emit arguments (skip first param which is function name)
            for (i, arg) in expr.params.iter().skip(1).enumerate() {
                if i > 0 {
                    output.push_str(", ");
                }
                emit_expr(arg, output, 0)?;
            }
            output.push_str(")");
            // Only add statement terminator if this is a statement (indent > 0)
            if indent > 0 {
                output.push_str(";\n");
            }
            Ok(())
        },
    }
}

fn emit_binop(expr: &Expr, output: &mut String, op: &str, ufcs_receiver: Option<&Expr>) -> Result<(), String> {
    output.push('(');

    // For UFCS: receiver.op(arg) -> (receiver op arg)
    // For type-qualified: Type.op(a, b) -> (a op b) - ignore type prefix
    // For regular: op(a, b) -> (a op b)
    if let Some(receiver) = ufcs_receiver {
        // Check if this is a type-qualified call (Type.op(a, b)) vs instance call (x.op(y))
        // Type-qualified calls have 2+ args after the function name
        if expr.params.len() >= 3 {
            // Type-qualified: Type.op(a, b) -> (a op b)
            emit_expr(&expr.params[1], output, 0)?;
            output.push(' ');
            output.push_str(op);
            output.push(' ');
            emit_expr(&expr.params[2], output, 0)?;
        } else if expr.params.len() >= 2 {
            // Instance UFCS: x.op(y) -> (x op y)
            emit_identifier_without_nested(receiver, output)?;
            output.push(' ');
            output.push_str(op);
            output.push(' ');
            emit_expr(&expr.params[1], output, 0)?;
        } else {
            return Err("codegen_c: UFCS binary op requires 1 argument".to_string());
        }
    } else {
        // Regular call: emit params[1] and params[2]
        if expr.params.len() < 3 {
            return Err("codegen_c: binary op requires 2 arguments".to_string());
        }
        emit_expr(&expr.params[1], output, 0)?;
        output.push(' ');
        output.push_str(op);
        output.push(' ');
        emit_expr(&expr.params[2], output, 0)?;
    }

    output.push(')');
    Ok(())
}

// Emit identifier without its nested params (for UFCS receiver)
fn emit_identifier_without_nested(expr: &Expr, output: &mut String) -> Result<(), String> {
    match &expr.node_type {
        NodeType::Identifier(name) => {
            output.push_str(name);
            Ok(())
        },
        _ => Err("codegen_c: expected identifier".to_string()),
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
