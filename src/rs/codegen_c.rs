// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal, SFuncDef};

// Emit C code from AST (multi-pass architecture)
pub fn emit(ast: &Expr) -> Result<String, String> {
    let mut output = String::new();

    // C boilerplate
    output.push_str("#include <stdio.h>\n");
    output.push_str("#include <stdlib.h>\n");
    output.push_str("#include <string.h>\n");
    output.push_str("#include <stdbool.h>\n\n");

    // Pass 1: emit struct definitions (only mut fields become struct members)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_declaration(child, &mut output)?;
            }
        }
    }

    // Pass 2: emit struct constants (non-mut, non-function fields with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_constants(child, &mut output)?;
            }
        }
    }
    output.push_str("\n");

    // Pass 3: emit function prototypes (forward declarations)
    // 3a: top-level functions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_prototype(child, &mut output)?;
            }
        }
    }
    // 3b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_prototypes(child, &mut output)?;
            }
        }
    }
    output.push_str("\n");

    // Pass 4: emit function definitions
    // 4a: top-level functions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_declaration(child, &mut output)?;
            }
        }
    }
    // 4b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_bodies(child, &mut output)?;
            }
        }
    }

    // Main function
    output.push_str("int main() {\n");

    // Pass 5: emit non-struct, non-function statements
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

// Emit a struct declaration as a C typedef struct (only mut fields become struct fields)
fn emit_struct_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                output.push_str("typedef struct {\n");
                for member in &struct_def.members {
                    // Only emit mut fields as struct members
                    // Skip functions and non-mut fields (constants)
                    if member.is_mut {
                        if let Some(c_type) = til_type_to_c(&member.value_type) {
                            output.push_str("    ");
                            output.push_str(&c_type);
                            output.push_str(" ");
                            output.push_str(&member.name);
                            output.push_str(";\n");
                        }
                    }
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

// Emit struct constants (non-mut, non-function fields) with mangled names: StructName_constant
fn emit_struct_constants(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = &decl.name;
                for member in &struct_def.members {
                    // Only emit non-mut, non-function fields as constants
                    if !member.is_mut {
                        if let Some(c_type) = til_type_to_c(&member.value_type) {
                            // Get the default value
                            if let Some(default_val) = struct_def.default_values.get(&member.name) {
                                output.push_str(&c_type);
                                output.push_str(" ");
                                output.push_str(struct_name);
                                output.push_str("_");
                                output.push_str(&member.name);
                                output.push_str(" = ");
                                emit_expr(default_val, output, 0)?;
                                output.push_str(";\n");
                            }
                        }
                    }
                }
                return Ok(());
            }
        }
    }
    Ok(()) // Not a struct, nothing to emit
}

// Emit a struct function prototype with mangled name: StructName_funcname
fn emit_struct_func_prototype(struct_name: &str, member: &crate::rs::parser::Declaration, func_def: &SFuncDef, output: &mut String) -> Result<(), String> {
    // Skip external functions
    if func_def.is_ext() {
        return Ok(());
    }

    // Return type
    if func_def.return_types.is_empty() {
        output.push_str("void ");
    } else {
        let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
        output.push_str(&ret_type);
        output.push_str(" ");
    }

    // Mangled name: StructName_funcname
    output.push_str(struct_name);
    output.push_str("_");
    output.push_str(&member.name);
    output.push_str("(");

    // Parameters
    for (i, arg) in func_def.args.iter().enumerate() {
        if i > 0 {
            output.push_str(", ");
        }
        let arg_type = til_type_to_c(&arg.value_type).unwrap_or("int".to_string());
        output.push_str(&arg_type);
        output.push_str(" ");
        output.push_str(&arg.name);
    }
    output.push_str(");\n");
    Ok(())
}

// Emit struct function prototypes for all functions in a struct
fn emit_struct_func_prototypes(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = &decl.name;
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            emit_struct_func_prototype(struct_name, member, func_def, output)?;
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Emit a struct function body with mangled name: StructName_funcname
fn emit_struct_func_body(struct_name: &str, member: &crate::rs::parser::Declaration, func_def: &SFuncDef, output: &mut String) -> Result<(), String> {
    // Skip external functions
    if func_def.is_ext() {
        return Ok(());
    }

    // Return type
    if func_def.return_types.is_empty() {
        output.push_str("void ");
    } else {
        let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
        output.push_str(&ret_type);
        output.push_str(" ");
    }

    // Mangled name: StructName_funcname
    output.push_str(struct_name);
    output.push_str("_");
    output.push_str(&member.name);
    output.push_str("(");

    // Parameters
    for (i, arg) in func_def.args.iter().enumerate() {
        if i > 0 {
            output.push_str(", ");
        }
        let arg_type = til_type_to_c(&arg.value_type).unwrap_or("int".to_string());
        output.push_str(&arg_type);
        output.push_str(" ");
        output.push_str(&arg.name);
    }
    output.push_str(") {\n");

    // Emit function body
    for stmt in &func_def.body {
        emit_expr(stmt, output, 1)?;
    }
    output.push_str("}\n\n");
    Ok(())
}

// Emit struct function bodies for all functions in a struct
fn emit_struct_func_bodies(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = &decl.name;
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            emit_struct_func_body(struct_name, member, func_def, output)?;
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Convert TIL type to C type. Returns None if the type can't be represented in C (e.g., functions)
fn til_type_to_c(til_type: &crate::rs::parser::ValueType) -> Option<String> {
    match til_type {
        crate::rs::parser::ValueType::TCustom(name) => {
            match name.as_str() {
                "I64" => Some("long long".to_string()),
                "I32" => Some("int".to_string()),
                "Bool" => Some("unsigned char".to_string()),
                "U8" => Some("unsigned char".to_string()),
                "Str" => Some("const char*".to_string()),
                "auto" => None, // Skip inferred types (usually methods)
                _ => Some(name.clone()), // Assume it's a struct type
            }
        },
        crate::rs::parser::ValueType::TFunction(_) => None, // Skip function types
        crate::rs::parser::ValueType::TType(_) => None, // Skip type types
        crate::rs::parser::ValueType::TMulti(_) => None, // Skip variadic types
    }
}

// Emit a function prototype (forward declaration)
fn emit_func_prototype(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                // Return type
                if func_def.return_types.is_empty() {
                    output.push_str("void ");
                } else {
                    let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
                    output.push_str(&ret_type);
                    output.push_str(" ");
                }

                output.push_str(&decl.name);
                output.push_str("(");

                // Parameters
                for (i, arg) in func_def.args.iter().enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    let arg_type = til_type_to_c(&arg.value_type).unwrap_or("int".to_string());
                    output.push_str(&arg_type);
                    output.push_str(" ");
                    output.push_str(&arg.name);
                }
                output.push_str(");\n");
                return Ok(());
            }
        }
    }
    Err("emit_func_prototype: not a function declaration".to_string())
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
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                // Return type
                if func_def.return_types.is_empty() {
                    output.push_str("void ");
                } else {
                    let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
                    output.push_str(&ret_type);
                    output.push_str(" ");
                }

                output.push_str(&decl.name);
                output.push_str("(");

                // Parameters
                for (i, arg) in func_def.args.iter().enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    let arg_type = til_type_to_c(&arg.value_type).unwrap_or("int".to_string());
                    output.push_str(&arg_type);
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
            // Check for type-qualified constant access (Type.CONSTANT -> Type_CONSTANT)
            if !expr.params.is_empty() {
                let first_char = name.chars().next().unwrap_or('a');
                if first_char.is_uppercase() {
                    // Type-qualified access: Type.field -> Type_field
                    if let NodeType::Identifier(field) = &expr.params[0].node_type {
                        output.push_str(name);
                        output.push_str("_");
                        output.push_str(field);
                        return Ok(());
                    }
                }
            }
            // Regular identifier or field access (b.val -> b.val)
            output.push_str(name);
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
        NodeType::If => emit_if(expr, output, indent),
        NodeType::While => emit_while(expr, output, indent),
        NodeType::Catch => Ok(()), // Skip catch blocks in C (no exception support)
        NodeType::Throw => Ok(()), // Skip throw in C
        NodeType::StructDef(_) => Err("codegen_c: StructDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::EnumDef(_) => Err("codegen_c: EnumDef not yet supported".to_string()),
        NodeType::Switch => Err("codegen_c: Switch not yet supported".to_string()),
        NodeType::DefaultCase => Err("codegen_c: DefaultCase not yet supported".to_string()),
        NodeType::Range => Err("codegen_c: Range not yet supported".to_string()),
        NodeType::Pattern(_) => Err("codegen_c: Pattern not yet supported".to_string()),
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

fn emit_if(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    // If: params[0] = condition, params[1] = then-body, params[2] = else-body (optional)
    if expr.params.len() < 2 {
        return Err("codegen_c: If requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("if (");
    emit_expr(&expr.params[0], output, 0)?;
    output.push_str(") {\n");

    // Then body
    emit_body(&expr.params[1], output, indent + 1)?;

    output.push_str(&indent_str);
    output.push_str("}");

    // Else branch (optional)
    if expr.params.len() > 2 {
        // Check if it's an else-if (nested If) or else block
        if let NodeType::If = &expr.params[2].node_type {
            output.push_str(" else ");
            // Emit nested if without extra indentation (it handles its own)
            emit_if(&expr.params[2], output, indent)?;
        } else {
            output.push_str(" else {\n");
            emit_body(&expr.params[2], output, indent + 1)?;
            output.push_str(&indent_str);
            output.push_str("}\n");
        }
    } else {
        output.push_str("\n");
    }

    Ok(())
}

fn emit_while(expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    // While: params[0] = condition, params[1] = body
    if expr.params.len() < 2 {
        return Err("codegen_c: While requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("while (");
    emit_expr(&expr.params[0], output, 0)?;
    output.push_str(") {\n");

    emit_body(&expr.params[1], output, indent + 1)?;

    output.push_str(&indent_str);
    output.push_str("}\n");

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

            // Check if this is a type-qualified call (Type.func(...))
            // Type names start with uppercase
            if let Some(receiver) = ufcs_receiver {
                if let NodeType::Identifier(receiver_name) = &receiver.node_type {
                    let first_char = receiver_name.chars().next().unwrap_or('a');
                    if first_char.is_uppercase() {
                        // Type-qualified call: Type.func(args...) -> Type_func(args...)
                        output.push_str(receiver_name);
                        output.push_str("_");
                        output.push_str(&func_name);
                        output.push_str("(");
                        // Emit all arguments after the function name
                        for (i, arg) in expr.params.iter().skip(1).enumerate() {
                            if i > 0 {
                                output.push_str(", ");
                            }
                            emit_expr(arg, output, 0)?;
                        }
                        output.push_str(")");
                        if indent > 0 {
                            output.push_str(";\n");
                        }
                        return Ok(());
                    } else {
                        // Instance UFCS: instance.func(args...) -> func(instance, args...)
                        // For now, just emit as regular call (TODO: need type info for proper mangling)
                        output.push_str(&func_name);
                        output.push_str("(");
                        // First emit the receiver as first argument
                        emit_identifier_without_nested(receiver, output)?;
                        // Then emit remaining arguments
                        for arg in expr.params.iter().skip(1) {
                            output.push_str(", ");
                            emit_expr(arg, output, 0)?;
                        }
                        output.push_str(")");
                        if indent > 0 {
                            output.push_str(";\n");
                        }
                        return Ok(());
                    }
                }
            }

            // Regular function call
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
            // Escape special characters for C string literals
            for c in s.chars() {
                match c {
                    '\n' => output.push_str("\\n"),
                    '\r' => output.push_str("\\r"),
                    '\t' => output.push_str("\\t"),
                    '\\' => output.push_str("\\\\"),
                    '"' => output.push_str("\\\""),
                    _ => output.push(c),
                }
            }
            output.push('"');
            Ok(())
        },
        Literal::Number(n) => {
            output.push_str(n);
            Ok(())
        },
        Literal::List(_) => Err("codegen_c: List literals not yet supported".to_string()),
    }
}
