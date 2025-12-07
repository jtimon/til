// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal, SFuncDef, SEnumDef, ValueType};
use std::collections::{HashMap, HashSet};

// Codegen context for tracking function info
struct CodegenContext {
    // Set of all known function names (for UFCS mangling)
    known_functions: HashSet<String>,
    // Map function name -> list of throw types
    func_throw_types: HashMap<String, Vec<ValueType>>,
    // Map function name -> list of return types
    func_return_types: HashMap<String, Vec<ValueType>>,
    // Map function name -> variadic arg info (arg_name, element_type, regular_arg_count)
    func_variadic_args: HashMap<String, (String, String, usize)>,
    // Map variable name -> its type (for UFCS mangling)
    var_types: HashMap<String, ValueType>,
    // Currently generating function's throw types (if any)
    current_throw_types: Vec<ValueType>,
    // Currently generating function's return types (if any)
    current_return_types: Vec<ValueType>,
    // Current function's variadic param name (if any) - for translating args.len()/args.get()
    current_variadic_param: Option<(String, String)>, // (name, element_type)
    // Counter for generating unique temporary variable names
    temp_counter: usize,
}

impl CodegenContext {
    fn new() -> Self {
        CodegenContext {
            known_functions: HashSet::new(),
            func_throw_types: HashMap::new(),
            func_return_types: HashMap::new(),
            func_variadic_args: HashMap::new(),
            var_types: HashMap::new(),
            current_throw_types: Vec::new(),
            current_return_types: Vec::new(),
            current_variadic_param: None,
            temp_counter: 0,
        }
    }

    fn next_temp(&mut self) -> String {
        let name = format!("_tmp{}", self.temp_counter);
        self.temp_counter += 1;
        name
    }
}

/// Check if an expression is a throwing function call
/// Returns Some((func_name, throw_types, return_type)) if it is, None otherwise
fn check_throwing_fcall(expr: &Expr, ctx: &CodegenContext) -> Option<(String, Vec<ValueType>, Option<ValueType>)> {
    if let NodeType::FCall = &expr.node_type {
        if let Some(func_name) = get_fcall_func_name(expr, ctx) {
            if let Some(throw_types) = ctx.func_throw_types.get(&func_name) {
                if !throw_types.is_empty() {
                    let return_type = ctx.func_return_types.get(&func_name)
                        .and_then(|types| types.first().cloned());
                    return Some((func_name, throw_types.clone(), return_type));
                }
            }
        }
    }
    None
}

/// Hoist throwing function calls from arguments (recursively)
/// Returns a vector of (arg_index, temp_var_name) for arguments that were hoisted
fn hoist_throwing_args(
    args: &[Expr],  // The arguments (skip first param which is function name)
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
) -> Result<Vec<(usize, String)>, String> {
    let mut hoisted = Vec::new();
    let indent_str = "    ".repeat(indent);

    for (idx, arg) in args.iter().enumerate() {
        if let Some((_func_name, throw_types, return_type)) = check_throwing_fcall(arg, ctx) {
            // RECURSIVELY hoist any throwing calls in this call's arguments first
            let nested_hoisted: std::collections::HashMap<usize, String> = if arg.params.len() > 1 {
                let nested_args = &arg.params[1..];
                let nested_vec = hoist_throwing_args(nested_args, output, indent, ctx)?;
                nested_vec.into_iter().collect()
            } else {
                std::collections::HashMap::new()
            };

            let temp_var = ctx.next_temp();

            // Determine the C type for the temp variable
            let c_type = if let Some(ret_type) = &return_type {
                til_type_to_c(ret_type).unwrap_or_else(|| "int".to_string())
            } else {
                "int".to_string()
            };

            // Declare temp variable
            output.push_str(&indent_str);
            output.push_str(&c_type);
            output.push_str(" ");
            output.push_str(&temp_var);
            output.push_str(";\n");

            // Declare error variables for each throw type
            let temp_suffix = ctx.next_temp();
            for (err_idx, throw_type) in throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = throw_type {
                    output.push_str(&indent_str);
                    output.push_str(type_name);
                    output.push_str(" _err");
                    output.push_str(&err_idx.to_string());
                    output.push_str("_");
                    output.push_str(&temp_suffix);
                    output.push_str(";\n");
                }
            }

            // Emit the function call with output pointers
            output.push_str(&indent_str);
            output.push_str("int _status_");
            output.push_str(&temp_suffix);
            output.push_str(" = ");

            // Emit the function name and args (using nested hoisted temps)
            emit_fcall_name_and_args_for_throwing(arg, &temp_var, &temp_suffix, &throw_types, &nested_hoisted, output, ctx)?;

            output.push_str(";\n");

            // Emit error checking - propagate if any error occurred
            output.push_str(&indent_str);
            output.push_str("if (_status_");
            output.push_str(&temp_suffix);
            output.push_str(" != 0) {\n");

            // Propagate error based on status value
            // For now, propagate to corresponding error pointer in current function
            for (err_idx, throw_type) in throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = throw_type {
                    // Find matching throw type in current function
                    for (curr_idx, curr_throw) in ctx.current_throw_types.iter().enumerate() {
                        if let ValueType::TCustom(curr_type_name) = curr_throw {
                            if curr_type_name == type_name {
                                output.push_str(&indent_str);
                                output.push_str("    if (_status_");
                                output.push_str(&temp_suffix);
                                output.push_str(" == ");
                                output.push_str(&(err_idx + 1).to_string());
                                output.push_str(") { *_err");
                                output.push_str(&(curr_idx + 1).to_string());
                                output.push_str(" = _err");
                                output.push_str(&err_idx.to_string());
                                output.push_str("_");
                                output.push_str(&temp_suffix);
                                output.push_str("; return ");
                                output.push_str(&(curr_idx + 1).to_string());
                                output.push_str("; }\n");
                                break;
                            }
                        }
                    }
                }
            }

            output.push_str(&indent_str);
            output.push_str("}\n");

            hoisted.push((idx, temp_var));
        }
    }

    Ok(hoisted)
}

/// Emit a throwing function call's name and arguments for hoisting
/// Outputs: func_name(&temp_var, &err1, &err2, ..., args...)
fn emit_fcall_name_and_args_for_throwing(
    expr: &Expr,
    temp_var: &str,
    temp_suffix: &str,
    throw_types: &[ValueType],
    nested_hoisted: &std::collections::HashMap<usize, String>,  // Hoisted temps for nested args
    output: &mut String,
    ctx: &mut CodegenContext,
) -> Result<(), String> {
    if expr.params.is_empty() {
        return Err("emit_fcall_name_and_args_for_throwing: FCall with no params".to_string());
    }

    // Determine function name and UFCS receiver
    let (func_name, ufcs_receiver) = match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                (name.clone(), None)
            } else {
                if let NodeType::Identifier(method_name) = &expr.params[0].params[0].node_type {
                    (method_name.clone(), Some(&expr.params[0]))
                } else {
                    return Err("emit_fcall_name_and_args_for_throwing: UFCS method name not Identifier".to_string());
                }
            }
        },
        _ => return Err("emit_fcall_name_and_args_for_throwing: FCall first param not Identifier".to_string()),
    };

    // Emit function name with potential UFCS mangling
    if let Some(receiver) = ufcs_receiver {
        if let NodeType::Identifier(receiver_name) = &receiver.node_type {
            let first_char = receiver_name.chars().next().unwrap_or('a');
            if first_char.is_uppercase() {
                // Type-qualified: Type.func -> Type_func
                output.push_str(receiver_name);
                output.push_str("_");
            } else {
                // Instance UFCS: instance.method -> Type_method
                if let Some(receiver_type) = ctx.var_types.get(receiver_name) {
                    if let ValueType::TCustom(type_name) = receiver_type {
                        output.push_str(type_name);
                        output.push_str("_");
                    }
                }
            }
        }
    } else {
        // Check for UFCS via first argument
        if expr.params.len() > 1 {
            if let NodeType::Identifier(first_arg_name) = &expr.params[1].node_type {
                if let Some(receiver_type) = ctx.var_types.get(first_arg_name) {
                    if let ValueType::TCustom(type_name) = receiver_type {
                        let candidate = format!("{}_{}", type_name, func_name);
                        if ctx.known_functions.contains(&candidate) {
                            output.push_str(type_name);
                            output.push_str("_");
                        }
                    }
                }
            }
        }
    }

    output.push_str(&func_name);
    output.push_str("(&");
    output.push_str(temp_var);

    // Add error output pointers
    for (idx, _) in throw_types.iter().enumerate() {
        output.push_str(", &_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(temp_suffix);
    }

    // Emit receiver for UFCS if any
    if let Some(receiver) = ufcs_receiver {
        if let NodeType::Identifier(receiver_name) = &receiver.node_type {
            let first_char = receiver_name.chars().next().unwrap_or('a');
            if !first_char.is_uppercase() {
                // Instance UFCS: add receiver as first actual argument
                output.push_str(", ");
                output.push_str(receiver_name);
            }
        }
    }

    // Build mangled function name for variadic lookup
    let mangled_name = {
        let mut name = String::new();
        if let Some(receiver) = ufcs_receiver {
            if let NodeType::Identifier(receiver_name) = &receiver.node_type {
                let first_char = receiver_name.chars().next().unwrap_or('a');
                if first_char.is_uppercase() {
                    name.push_str(receiver_name);
                    name.push('_');
                } else if let Some(receiver_type) = ctx.var_types.get(receiver_name) {
                    if let ValueType::TCustom(type_name) = receiver_type {
                        name.push_str(type_name);
                        name.push('_');
                    }
                }
            }
        } else if expr.params.len() > 1 {
            if let NodeType::Identifier(first_arg_name) = &expr.params[1].node_type {
                if let Some(receiver_type) = ctx.var_types.get(first_arg_name) {
                    if let ValueType::TCustom(type_name) = receiver_type {
                        let candidate = format!("{}_{}", type_name, func_name);
                        if ctx.known_functions.contains(&candidate) {
                            name.push_str(type_name);
                            name.push('_');
                        }
                    }
                }
            }
        }
        name.push_str(&func_name);
        name
    };

    // Check if this is a variadic function call
    if let Some((_variadic_name, elem_type, regular_count)) = ctx.func_variadic_args.get(&mangled_name).cloned() {
        // Emit regular args first (skip first param which is function name)
        let args: Vec<_> = expr.params.iter().skip(1).collect();
        for (arg_idx, arg) in args.iter().take(regular_count).enumerate() {
            output.push_str(", ");
            if let Some(temp) = nested_hoisted.get(&arg_idx) {
                output.push_str(temp);
            } else {
                emit_expr(arg, output, 0, ctx)?;
            }
        }
        // Emit count of variadic args
        let variadic_count = args.len().saturating_sub(regular_count);
        output.push_str(", ");
        output.push_str(&variadic_count.to_string());

        // Emit variadic args as compound literal array (C99)
        // Get C element type for the array
        let c_elem_type = match elem_type.as_str() {
            "Str" => "const char*",
            "I64" => "long long",
            "Bool" => "unsigned char",
            "U8" => "unsigned char",
            _ => elem_type.as_str(),
        };

        if variadic_count == 0 {
            // Empty variadic: pass NULL
            output.push_str(", NULL");
        } else {
            // Build compound literal: (type[]){arg1, arg2, ...}
            output.push_str(", (");
            output.push_str(c_elem_type);
            output.push_str("[]){");
            for (i, arg) in args.iter().skip(regular_count).enumerate() {
                if i > 0 {
                    output.push_str(", ");
                }
                let hoisted_idx = regular_count + i;
                if let Some(temp) = nested_hoisted.get(&hoisted_idx) {
                    output.push_str(temp);
                } else {
                    emit_expr(arg, output, 0, ctx)?;
                }
            }
            output.push_str("}");
        }
    } else {
        // Emit remaining arguments (using hoisted temps where available)
        for (arg_idx, arg) in expr.params.iter().skip(1).enumerate() {
            output.push_str(", ");
            // Use hoisted temp if this arg was hoisted, otherwise emit directly
            if let Some(temp) = nested_hoisted.get(&arg_idx) {
                output.push_str(temp);
            } else {
                emit_expr(arg, output, 0, ctx)?;
            }
        }
    }

    output.push_str(")");
    Ok(())
}

/// Emit an argument, using hoisted temp var if available
fn emit_arg_or_hoisted(
    arg: &Expr,
    arg_idx: usize,
    hoisted: &std::collections::HashMap<usize, String>,
    output: &mut String,
    ctx: &mut CodegenContext,
) -> Result<(), String> {
    if let Some(temp_var) = hoisted.get(&arg_idx) {
        output.push_str(temp_var);
        Ok(())
    } else {
        emit_expr(arg, output, 0, ctx)
    }
}

// Emit C code from AST (multi-pass architecture)
pub fn emit(ast: &Expr) -> Result<String, String> {
    let mut output = String::new();
    let mut ctx = CodegenContext::new();

    // C boilerplate
    output.push_str("#include <stdio.h>\n");
    output.push_str("#include <stdlib.h>\n");
    output.push_str("#include <string.h>\n");
    output.push_str("#include <stdbool.h>\n");
    output.push_str("#include <stdarg.h>\n\n");
    // Primitive type conversion functions (used by ext_func declarations in TIL)
    output.push_str("static inline long long u8_to_i64(unsigned char v) { return (long long)v; }\n");
    output.push_str("static inline unsigned char i64_to_u8(long long v) { return (unsigned char)v; }\n\n");

    // Pass 0: collect function info (throw types, return types) for call-site generation
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            collect_func_info(child, &mut ctx);
        }
    }

    // Pass 1: emit struct definitions (only mut fields become struct members)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_declaration(child, &mut output)?;
            }
        }
    }

    // Pass 1b: emit enum definitions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) {
                emit_enum_declaration(child, &mut output)?;
            }
        }
    }

    // Pass 2: emit struct constants (non-mut, non-function fields with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_constants(child, &mut output, &mut ctx)?;
            }
        }
    }

    // Pass 2b: emit top-level constants (non-mut declarations with literal values)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_constant_declaration(child) {
                emit_constant_declaration(child, &mut output)?;
            }
        }
    }
    output.push_str("\n");

    // Pass 3: emit function prototypes (forward declarations)
    // 3a: top-level functions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_prototype(child, &mut output, &ctx)?;
            }
        }
    }
    // 3b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_prototypes(child, &mut output, &ctx)?;
            }
        }
    }
    output.push_str("\n");

    // Pass 4: emit function definitions
    // 4a: top-level functions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_declaration(child, &mut output, &mut ctx)?;
            }
        }
    }
    // 4b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_bodies(child, &mut output, &mut ctx)?;
            }
        }
    }

    // Main function
    output.push_str("int main() {\n");

    // Pass 5: emit non-struct, non-function, non-enum, non-constant statements
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if !is_func_declaration(child) && !is_struct_declaration(child) && !is_enum_declaration(child) && !is_constant_declaration(child) {
                emit_expr(child, &mut output, 1, &mut ctx)?;
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

// Check if an expression is an enum declaration (Name := enum {...})
fn is_enum_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(_) = &expr.params[0].node_type {
                return true;
            }
        }
    }
    false
}

// Check if an expression is a top-level constant declaration (name := literal)
// Constants are non-mut declarations with literal values (numbers, strings, bools)
fn is_constant_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(decl) = &expr.node_type {
        // Must not be mutable
        if decl.is_mut {
            return false;
        }
        if !expr.params.is_empty() {
            match &expr.params[0].node_type {
                // Literal values are constants
                NodeType::LLiteral(_) => return true,
                // Skip struct, enum, and function definitions
                NodeType::StructDef(_) | NodeType::EnumDef(_) | NodeType::FuncDef(_) => return false,
                _ => return false,
            }
        }
    }
    false
}

// Emit a top-level constant declaration at file scope
fn emit_constant_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        // Skip C reserved words/macros
        match decl.name.as_str() {
            "NULL" | "true" | "false" => return Ok(()),
            _ => {}
        }
        if !expr.params.is_empty() {
            if let NodeType::LLiteral(lit) = &expr.params[0].node_type {
                let c_type = match lit {
                    Literal::Number(_) => "long long",
                    Literal::Str(_) => "const char*",
                    Literal::List(_) => return Ok(()), // Skip list literals for now
                };
                output.push_str(c_type);
                output.push_str(" ");
                output.push_str(&decl.name);
                output.push_str(" = ");
                emit_literal(lit, output)?;
                output.push_str(";\n");
            }
        }
    }
    Ok(())
}

// Collect function info (throw types, return types, names) from AST into context
// Handles both top-level functions and struct methods
fn collect_func_info(expr: &Expr, ctx: &mut CodegenContext) {
    match &expr.node_type {
        NodeType::Declaration(decl) => {
            if !expr.params.is_empty() {
                match &expr.params[0].node_type {
                    NodeType::FuncDef(func_def) => {
                        // Top-level function - track name and types
                        ctx.known_functions.insert(decl.name.clone());
                        if !func_def.throw_types.is_empty() {
                            ctx.func_throw_types.insert(
                                decl.name.clone(),
                                func_def.throw_types.clone()
                            );
                        }
                        if !func_def.return_types.is_empty() {
                            ctx.func_return_types.insert(
                                decl.name.clone(),
                                func_def.return_types.clone()
                            );
                        }
                        // Check for variadic args (TMulti)
                        for (idx, arg) in func_def.args.iter().enumerate() {
                            if let ValueType::TMulti(elem_type) = &arg.value_type {
                                // Track: (arg_name, element_type, count of regular args before variadic)
                                ctx.func_variadic_args.insert(
                                    decl.name.clone(),
                                    (arg.name.clone(), elem_type.clone(), idx)
                                );
                                break; // Only one variadic arg per function
                            }
                        }
                    },
                    NodeType::StructDef(struct_def) => {
                        // Struct methods - use mangled names (StructName_methodName)
                        let struct_name = &decl.name;
                        for (member_name, default_expr) in &struct_def.default_values {
                            if let NodeType::FuncDef(func_def) = &default_expr.node_type {
                                let mangled_name = format!("{}_{}", struct_name, member_name);
                                // Track all struct methods
                                ctx.known_functions.insert(mangled_name.clone());
                                if !func_def.throw_types.is_empty() {
                                    ctx.func_throw_types.insert(
                                        mangled_name.clone(),
                                        func_def.throw_types.clone()
                                    );
                                }
                                if !func_def.return_types.is_empty() {
                                    ctx.func_return_types.insert(
                                        mangled_name.clone(),
                                        func_def.return_types.clone()
                                    );
                                }
                                // Check for variadic args (TMulti) in struct methods
                                for (idx, arg) in func_def.args.iter().enumerate() {
                                    if let ValueType::TMulti(elem_type) = &arg.value_type {
                                        ctx.func_variadic_args.insert(
                                            mangled_name.clone(),
                                            (arg.name.clone(), elem_type.clone(), idx)
                                        );
                                        break;
                                    }
                                }
                            }
                        }
                    },
                    _ => {}
                }
            }
        },
        _ => {}
    }
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
fn emit_struct_constants(expr: &Expr, output: &mut String, ctx: &mut CodegenContext) -> Result<(), String> {
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
                                emit_expr(default_val, output, 0, ctx)?;
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

// Check if an enum has any payloads
fn enum_has_payloads(enum_def: &SEnumDef) -> bool {
    for (_variant_name, payload_type) in &enum_def.enum_map {
        if payload_type.is_some() {
            return true;
        }
    }
    false
}

// Emit an enum with payloads as a tagged union
fn emit_enum_with_payloads(enum_name: &str, enum_def: &SEnumDef, output: &mut String) -> Result<(), String> {
    // Sort variants by name for deterministic output
    let mut variants: Vec<_> = enum_def.enum_map.iter().collect();
    variants.sort_by_key(|(name, _)| *name);

    // 1. Emit tag enum: typedef enum { Color_Unknown = 0, ... } Color_Tag;
    output.push_str("typedef enum {\n");
    for (index, (variant_name, _)) in variants.iter().enumerate() {
        output.push_str("    ");
        output.push_str(enum_name);
        output.push_str("_");
        output.push_str(variant_name);
        output.push_str(" = ");
        output.push_str(&index.to_string());
        output.push_str(",\n");
    }
    output.push_str("} ");
    output.push_str(enum_name);
    output.push_str("_Tag;\n\n");

    // 2. Emit payload union (only for variants that have payloads)
    // typedef union { unsigned char Green; long long Number; } Color_Payload;
    let has_any_payload = variants.iter().any(|(_, payload)| payload.is_some());
    if has_any_payload {
        output.push_str("typedef union {\n");
        for (variant_name, payload_type) in &variants {
            if let Some(pt) = payload_type {
                if let Some(c_type) = til_type_to_c(pt) {
                    output.push_str("    ");
                    output.push_str(&c_type);
                    output.push_str(" ");
                    output.push_str(variant_name);
                    output.push_str(";\n");
                }
            }
        }
        output.push_str("} ");
        output.push_str(enum_name);
        output.push_str("_Payload;\n\n");
    }

    // 3. Emit wrapper struct: typedef struct { Color_Tag tag; Color_Payload payload; } Color;
    output.push_str("typedef struct {\n");
    output.push_str("    ");
    output.push_str(enum_name);
    output.push_str("_Tag tag;\n");
    if has_any_payload {
        output.push_str("    ");
        output.push_str(enum_name);
        output.push_str("_Payload payload;\n");
    }
    output.push_str("} ");
    output.push_str(enum_name);
    output.push_str(";\n\n");

    // 4. Emit constructor functions for ALL variants (including no-payload ones)
    // This ensures consistent calling convention: Color_make_Red(42), Color_make_Unknown()
    for (variant_name, payload_type) in &variants {
        output.push_str("static inline ");
        output.push_str(enum_name);
        output.push_str(" ");
        output.push_str(enum_name);
        output.push_str("_make_");
        output.push_str(variant_name);
        output.push_str("(");

        // Parameter for payload (if any)
        if let Some(pt) = payload_type {
            if let Some(c_type) = til_type_to_c(pt) {
                output.push_str(&c_type);
                output.push_str(" value");
            }
        } else {
            output.push_str("void");
        }
        output.push_str(") {\n");

        // Constructor body
        output.push_str("    ");
        output.push_str(enum_name);
        output.push_str(" result = { .tag = ");
        output.push_str(enum_name);
        output.push_str("_");
        output.push_str(variant_name);
        output.push_str(" };\n");

        // Set payload if present
        if payload_type.is_some() {
            output.push_str("    result.payload.");
            output.push_str(variant_name);
            output.push_str(" = value;\n");
        }

        output.push_str("    return result;\n");
        output.push_str("}\n\n");
    }

    Ok(())
}

// Emit an enum declaration as a C typedef enum (for simple enums without payloads)
// or as a tagged union struct (for enums with payloads)
fn emit_enum_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(enum_def) = &expr.params[0].node_type {
                let enum_name = &decl.name;

                if enum_has_payloads(enum_def) {
                    // Phase 2: Enums with payloads - tagged union
                    return emit_enum_with_payloads(enum_name, enum_def, output);
                }

                // Phase 1: Simple enum without payloads
                // typedef enum { EnumName_Variant1 = 0, ... } EnumName;
                output.push_str("typedef enum {\n");

                // Sort variants by name for deterministic output
                let mut variants: Vec<_> = enum_def.enum_map.keys().collect();
                variants.sort();

                for (index, variant_name) in variants.iter().enumerate() {
                    output.push_str("    ");
                    output.push_str(enum_name);
                    output.push_str("_");
                    output.push_str(variant_name);
                    output.push_str(" = ");
                    output.push_str(&index.to_string());
                    output.push_str(",\n");
                }

                output.push_str("} ");
                output.push_str(enum_name);
                output.push_str(";\n\n");

                // Generate constructor functions for consistency with payload enums
                // static inline EnumName EnumName_make_Variant(void) { return EnumName_Variant; }
                for variant_name in &variants {
                    output.push_str("static inline ");
                    output.push_str(enum_name);
                    output.push_str(" ");
                    output.push_str(enum_name);
                    output.push_str("_make_");
                    output.push_str(variant_name);
                    output.push_str("(void) { return ");
                    output.push_str(enum_name);
                    output.push_str("_");
                    output.push_str(variant_name);
                    output.push_str("; }\n");
                }
                output.push_str("\n");

                return Ok(());
            }
        }
    }
    Err("emit_enum_declaration: not an enum declaration".to_string())
}
// Emit struct function prototypes for all functions in a struct
fn emit_struct_func_prototypes(expr: &Expr, output: &mut String, ctx: &CodegenContext) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = &decl.name;
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            let mangled_name = format!("{}_{}", struct_name, member.name);
                            emit_func_signature(&mangled_name, func_def, output, ctx);
                            output.push_str(";\n");
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Emit a struct function body with mangled name: StructName_funcname
fn emit_struct_func_body(struct_name: &str, member: &crate::rs::parser::Declaration, func_def: &SFuncDef, output: &mut String, ctx: &mut CodegenContext) -> Result<(), String> {
    // Skip external functions
    if func_def.is_ext() {
        return Ok(());
    }

    // Set current function context
    ctx.current_throw_types = func_def.throw_types.clone();
    ctx.current_return_types = func_def.return_types.clone();

    // Clear var_types for new function scope and add function arguments
    ctx.var_types.clear();
    for arg in &func_def.args {
        ctx.var_types.insert(arg.name.clone(), arg.value_type.clone());
    }

    let mangled_name = format!("{}_{}", struct_name, member.name);
    emit_func_signature(&mangled_name, func_def, output, ctx);
    output.push_str(" {\n");

    // Emit function body with catch pattern detection
    emit_stmts(&func_def.body, output, 1, ctx)?;

    // For throwing void functions, add implicit return 0 at end
    if !func_def.throw_types.is_empty() && func_def.return_types.is_empty() {
        output.push_str("    return 0;\n");
    }

    output.push_str("}\n\n");

    // Clear current function context
    ctx.current_throw_types.clear();
    ctx.current_return_types.clear();

    Ok(())
}

// Emit struct function bodies for all functions in a struct
fn emit_struct_func_bodies(expr: &Expr, output: &mut String, ctx: &mut CodegenContext) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = &decl.name;
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            emit_struct_func_body(struct_name, member, func_def, output, ctx)?;
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

// Helper to get C type name for a ValueType (for error struct definitions)
fn value_type_to_c_name(vt: &ValueType) -> String {
    match vt {
        ValueType::TCustom(name) => {
            match name.as_str() {
                "I64" => "long long".to_string(),
                "Bool" => "unsigned char".to_string(),
                "U8" => "unsigned char".to_string(),
                "Str" => "const char*".to_string(),
                _ => name.clone(), // struct/error types
            }
        },
        _ => "int".to_string(),
    }
}

// Emit function signature (used by both prototype and definition)
// For throwing functions:
//   int func_name(RetType* _ret, Error1* _err1, Error2* _err2, args...)
// For non-throwing:
//   RetType func_name(args...)
fn emit_func_signature(func_name: &str, func_def: &SFuncDef, output: &mut String, _ctx: &CodegenContext) {
    let is_throwing = !func_def.throw_types.is_empty();

    if is_throwing {
        // Throwing function returns int status code
        output.push_str("int ");
    } else {
        // Non-throwing function returns its actual type
        if func_def.return_types.is_empty() {
            output.push_str("void ");
        } else {
            let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
            output.push_str(&ret_type);
            output.push_str(" ");
        }
    }

    output.push_str(func_name);
    output.push_str("(");

    let mut param_count = 0;

    if is_throwing {
        // Output params first: return value pointer, then error pointers
        if !func_def.return_types.is_empty() {
            let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
            output.push_str(&ret_type);
            output.push_str("* _ret");
            param_count += 1;
        }

        for (i, throw_type) in func_def.throw_types.iter().enumerate() {
            if param_count > 0 {
                output.push_str(", ");
            }
            let err_type = value_type_to_c_name(throw_type);
            output.push_str(&err_type);
            output.push_str("* _err");
            output.push_str(&(i + 1).to_string());
            param_count += 1;
        }
    }

    // Input parameters
    for arg in func_def.args.iter() {
        if param_count > 0 {
            output.push_str(", ");
        }
        // Check for variadic arg (TMulti)
        if let ValueType::TMulti(elem_type) = &arg.value_type {
            // Emit count parameter and array pointer: int args_len, element_type* args
            let c_elem_type = match elem_type.as_str() {
                "Str" => "const char*",
                "I64" => "long long",
                "Bool" => "unsigned char",
                "U8" => "unsigned char",
                _ => elem_type.as_str(),
            };
            output.push_str("int _");
            output.push_str(&arg.name);
            output.push_str("_len, ");
            output.push_str(c_elem_type);
            output.push_str("* ");
            output.push_str(&arg.name);
            param_count += 1;
            break; // Variadic must be last
        } else {
            let arg_type = til_type_to_c(&arg.value_type).unwrap_or("int".to_string());
            output.push_str(&arg_type);
            output.push_str(" ");
            output.push_str(&arg.name);
            param_count += 1;
        }
    }

    if param_count == 0 {
        output.push_str("void");
    }

    output.push_str(")");
}

// Emit a function prototype (forward declaration)
fn emit_func_prototype(expr: &Expr, output: &mut String, ctx: &CodegenContext) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                emit_func_signature(&decl.name, func_def, output, ctx);
                output.push_str(";\n");
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
fn emit_func_declaration(expr: &Expr, output: &mut String, ctx: &mut CodegenContext) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                // Set current function context for return/throw generation
                ctx.current_throw_types = func_def.throw_types.clone();
                ctx.current_return_types = func_def.return_types.clone();

                // Clear var_types for new function scope and add function arguments
                ctx.var_types.clear();
                // Check for variadic parameter and set context
                ctx.current_variadic_param = None;
                for arg in &func_def.args {
                    ctx.var_types.insert(arg.name.clone(), arg.value_type.clone());
                    if let ValueType::TMulti(elem_type) = &arg.value_type {
                        ctx.current_variadic_param = Some((arg.name.clone(), elem_type.clone()));
                    }
                }

                emit_func_signature(&decl.name, func_def, output, ctx);
                output.push_str(" {\n");

                // With Array approach, variadic args are passed directly as array pointer
                // No va_list setup needed - the array is built by caller

                // Emit function body with catch pattern detection
                emit_stmts(&func_def.body, output, 1, ctx)?;

                // For throwing void functions, add implicit return 0 at end
                if !func_def.throw_types.is_empty() && func_def.return_types.is_empty() {
                    output.push_str("    return 0;\n");
                }

                output.push_str("}\n\n");

                // Clear current function context
                ctx.current_throw_types.clear();
                ctx.current_return_types.clear();

                return Ok(());
            }
        }
    }
    Err("emit_func_declaration: not a function declaration".to_string())
}

fn emit_expr(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    match &expr.node_type {
        NodeType::Body => emit_body(expr, output, indent, ctx),
        NodeType::FCall => emit_fcall(expr, output, indent, ctx),
        NodeType::LLiteral(lit) => emit_literal(lit, output),
        NodeType::Declaration(decl) => emit_declaration(decl, expr, output, indent, ctx),
        NodeType::Identifier(name) => {
            // Check for type-qualified access (Type.field)
            if !expr.params.is_empty() {
                let first_char = name.chars().next().unwrap_or('a');
                if first_char.is_uppercase() {
                    if let NodeType::Identifier(field) = &expr.params[0].node_type {
                        let field_first_char = field.chars().next().unwrap_or('a');
                        if field_first_char.is_uppercase() {
                            // Enum variant: Type.Variant -> Type_make_Variant()
                            output.push_str(name);
                            output.push_str("_make_");
                            output.push_str(field);
                            output.push_str("()");
                            return Ok(());
                        } else {
                            // Type-qualified constant: Type.constant -> Type_constant
                            output.push_str(name);
                            output.push_str("_");
                            output.push_str(field);
                            return Ok(());
                        }
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
        NodeType::FuncDef(func_def) => emit_funcdef(func_def, expr, output, indent, ctx),
        NodeType::Assignment(name) => emit_assignment(name, expr, output, indent, ctx),
        NodeType::Return => emit_return(expr, output, indent, ctx),
        NodeType::If => emit_if(expr, output, indent, ctx),
        NodeType::While => emit_while(expr, output, indent, ctx),
        NodeType::Catch => Ok(()), // Catch blocks handled at call site
        NodeType::Throw => emit_throw(expr, output, indent, ctx),
        NodeType::StructDef(_) => Err("codegen_c: StructDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::EnumDef(_) => Err("codegen_c: EnumDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::Switch => emit_switch(expr, output, indent, ctx),
        NodeType::DefaultCase => Err("codegen_c: DefaultCase should be handled inside emit_switch".to_string()),
        NodeType::Range => Err("codegen_c: Range not yet supported".to_string()),
        NodeType::Pattern(_) => Err("codegen_c: Pattern should be handled inside emit_switch".to_string()),
    }
}

fn emit_body(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    emit_stmts(&expr.params, output, indent, ctx)
}

/// Emit a sequence of statements with catch pattern detection
/// This is the core logic shared between emit_body and emit_func_declaration
fn emit_stmts(stmts: &[Expr], output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    let mut i = 0;

    while i < stmts.len() {
        let stmt = &stmts[i];

        // Check if this statement is followed by catch blocks
        // And if it's a call to a throwing function (FCall, Declaration with FCall, or Assignment with FCall)
        let (maybe_fcall, maybe_decl_name, maybe_assign_name) = match &stmt.node_type {
            NodeType::FCall => (Some(stmt), None, None),
            NodeType::Declaration(decl) => {
                // Check if declaration has an FCall as initializer
                if !stmt.params.is_empty() {
                    if let NodeType::FCall = stmt.params[0].node_type {
                        (Some(&stmt.params[0]), Some(decl.name.clone()), None)
                    } else {
                        (None, None, None)
                    }
                } else {
                    (None, None, None)
                }
            }
            NodeType::Assignment(name) => {
                // Check if assignment has an FCall as RHS
                if !stmt.params.is_empty() {
                    if let NodeType::FCall = stmt.params[0].node_type {
                        (Some(&stmt.params[0]), None, Some(name.clone()))
                    } else {
                        (None, None, None)
                    }
                } else {
                    (None, None, None)
                }
            }
            _ => (None, None, None),
        };

        if let Some(fcall) = maybe_fcall {
            // Get function name from the FCall
            let func_name = get_fcall_func_name(fcall, ctx);

            // Check if this function is a throwing function
            if let Some(func_name) = func_name {
                if let Some(throw_types) = ctx.func_throw_types.get(&func_name).cloned() {
                    // Collect subsequent catch blocks
                    let mut catch_blocks = Vec::new();
                    let mut j = i + 1;
                    while j < stmts.len() {
                        if let NodeType::Catch = stmts[j].node_type {
                            catch_blocks.push(&stmts[j]);
                            j += 1;
                        } else {
                            break;
                        }
                    }

                    if !catch_blocks.is_empty() {
                        // Emit throwing call with catch handling
                        emit_throwing_call(fcall, &throw_types, &catch_blocks, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, indent, ctx)?;
                        i = j; // Skip past catch blocks
                        continue;
                    }
                }
            }
        }

        // Regular statement handling
        emit_expr(stmt, output, indent, ctx)?;
        i += 1;
    }
    Ok(())
}

/// Get the function name from an FCall expression
fn get_fcall_func_name(expr: &Expr, ctx: &CodegenContext) -> Option<String> {
    if expr.params.is_empty() {
        return None;
    }

    match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                // Regular function call
                Some(name.clone())
            } else {
                // UFCS: receiver.method() - determine mangled name
                if let NodeType::Identifier(method_name) = &expr.params[0].params[0].node_type {
                    // Check if receiver is PascalCase (type-qualified call)
                    let first_char = name.chars().next().unwrap_or('a');
                    if first_char.is_uppercase() {
                        // Type.method -> Type_method
                        Some(format!("{}_{}", name, method_name))
                    } else {
                        // instance.method -> look up instance type for mangling
                        if let Some(receiver_type) = ctx.var_types.get(name) {
                            if let ValueType::TCustom(type_name) = receiver_type {
                                return Some(format!("{}_{}", type_name, method_name));
                            }
                        }
                        // Fallback: just the method name (may not find throw info)
                        Some(method_name.clone())
                    }
                } else {
                    None
                }
            }
        }
        _ => None,
    }
}

/// Emit a call to a throwing function with catch handling
fn emit_throwing_call(
    fcall: &Expr,
    throw_types: &[crate::rs::parser::ValueType],
    catch_blocks: &[&Expr],
    decl_name: Option<&str>,
    assign_name: Option<&str>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Get function name
    let func_name = get_fcall_func_name(fcall, ctx)
        .ok_or_else(|| "emit_throwing_call: could not get function name".to_string())?;

    // Generate unique temp names for this call
    let temp_suffix = ctx.next_temp();

    // Determine if we need a return value temp variable
    let needs_ret = decl_name.is_some() || assign_name.is_some();

    // Declare local variables for return value and errors
    // Look up the actual return type from collected function info
    let ret_type = if needs_ret {
        ctx.func_return_types.get(&func_name)
            .and_then(|types| types.first())
            .map(|t| til_type_to_c(t).unwrap_or("int".to_string()))
            .unwrap_or("int".to_string())
    } else {
        "int".to_string()
    };

    if needs_ret {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" _ret_");
        output.push_str(&temp_suffix.to_string());
        output.push_str(";\n");
    }

    // For declarations: declare the variable BEFORE the if block so it's visible after
    if let Some(var_name) = decl_name {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" ");
        output.push_str(var_name);
        output.push_str(";\n");
    }

    // Declare error structs for each throw type
    // Check if struct is empty to avoid {0} warning
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if let crate::rs::parser::ValueType::TCustom(type_name) = throw_type {
            output.push_str(&indent_str);
            output.push_str(type_name);
            output.push_str(" _err");
            output.push_str(&idx.to_string());
            output.push_str("_");
            output.push_str(&temp_suffix.to_string());
            // Use = {} for empty structs to avoid warning
            output.push_str(" = {};\n");
        }
    }

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int _status_");
    output.push_str(&temp_suffix.to_string());
    output.push_str(" = ");
    output.push_str(&func_name);
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix.to_string());
    }

    // Then: error pointers
    for idx in 0..throw_types.len() {
        if needs_ret || idx > 0 {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix.to_string());
    }

    // Then: actual arguments
    for arg in fcall.params.iter().skip(1) {
        if needs_ret || !throw_types.is_empty() {
            output.push_str(", ");
        }
        emit_expr(arg, output, 0, ctx)?;
    }

    output.push_str(");\n");

    // Generate if/else chain for error handling
    output.push_str(&indent_str);
    output.push_str("if (_status_");
    output.push_str(&temp_suffix.to_string());
    output.push_str(" == 0) {\n");

    // Success case: assign return value to target variable
    if let Some(var_name) = decl_name {
        // Declaration: assign to newly declared variable (declared before if block)
        let inner_indent = "    ".repeat(indent + 1);
        output.push_str(&inner_indent);
        output.push_str(var_name);
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix.to_string());
        output.push_str(";\n");
    } else if let Some(var_name) = assign_name {
        // Assignment: assign to existing variable
        let inner_indent = "    ".repeat(indent + 1);
        output.push_str(&inner_indent);
        output.push_str(var_name);
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix.to_string());
        output.push_str(";\n");
    }

    output.push_str(&indent_str);
    output.push_str("}");

    // Generate else-if branches for each catch block
    for catch_block in catch_blocks {
        if catch_block.params.len() >= 3 {
            // Get error type name from catch block
            if let NodeType::Identifier(err_type_name) = &catch_block.params[1].node_type {
                // Find index of this error type
                let err_idx = throw_types.iter().position(|vt| {
                    if let crate::rs::parser::ValueType::TCustom(name) = vt {
                        name == err_type_name
                    } else {
                        false
                    }
                });

                if let Some(idx) = err_idx {
                    output.push_str(" else if (_status_");
                    output.push_str(&temp_suffix.to_string());
                    output.push_str(" == ");
                    output.push_str(&(idx + 1).to_string());
                    output.push_str(") {\n");

                    // Bind error variable
                    if let NodeType::Identifier(err_var_name) = &catch_block.params[0].node_type {
                        let inner_indent = "    ".repeat(indent + 1);
                        output.push_str(&inner_indent);
                        output.push_str(err_type_name);
                        output.push_str(" ");
                        output.push_str(err_var_name);
                        output.push_str(" = _err");
                        output.push_str(&idx.to_string());
                        output.push_str("_");
                        output.push_str(&temp_suffix.to_string());
                        output.push_str(";\n");
                    }

                    // Emit catch body
                    emit_expr(&catch_block.params[2], output, indent + 1, ctx)?;

                    output.push_str(&indent_str);
                    output.push_str("}");
                }
            }
        }
    }

    output.push_str("\n");
    Ok(())
}

fn emit_declaration(decl: &crate::rs::parser::Declaration, expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    // Skip inline ext_func/ext_proc declarations - they're just declaring external functions exist
    if !expr.params.is_empty() {
        if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
            if func_def.is_ext() {
                return Ok(());
            }
        }
    }

    // Skip C reserved words/macros
    match decl.name.as_str() {
        "NULL" | "true" | "false" => return Ok(()),
        _ => {}
    }

    let indent_str = "    ".repeat(indent);
    let name = &decl.name;
    let is_mut = decl.is_mut;

    // Check if this is a struct construction (TypeName())
    let struct_type = if !expr.params.is_empty() {
        get_struct_construction_type(&expr.params[0])
    } else {
        None
    };

    // Check if this is an enum construction (Type.Variant or Type.Variant(value))
    let enum_type = if !expr.params.is_empty() {
        get_enum_construction_type(&expr.params[0])
    } else {
        None
    };

    // Track variable type for UFCS mangling
    // Use the inferred type from struct/enum construction if available,
    // or infer from literal if type is "auto"
    if let Some(ref type_name) = struct_type {
        ctx.var_types.insert(name.clone(), ValueType::TCustom(type_name.clone()));
    } else if let Some(ref type_name) = enum_type {
        ctx.var_types.insert(name.clone(), ValueType::TCustom(type_name.clone()));
    } else if let ValueType::TCustom(type_name) = &decl.value_type {
        if type_name == "auto" && !expr.params.is_empty() {
            // Try to infer type from initializer literal
            if let Some(inferred) = infer_type_from_expr(&expr.params[0], ctx) {
                ctx.var_types.insert(name.clone(), inferred);
            } else {
                ctx.var_types.insert(name.clone(), decl.value_type.clone());
            }
        } else {
            ctx.var_types.insert(name.clone(), decl.value_type.clone());
        }
    } else {
        ctx.var_types.insert(name.clone(), decl.value_type.clone());
    }

    if let Some(type_name) = struct_type {
        // Struct variable declaration
        output.push_str(&indent_str);
        output.push_str(&type_name);
        output.push_str(" ");
        output.push_str(name);
        output.push_str(" = {0};\n");
    } else if let Some(type_name) = enum_type {
        // Enum variable declaration
        output.push_str(&indent_str);
        output.push_str(&type_name);
        output.push_str(" ");
        output.push_str(name);
        output.push_str(" = ");
        emit_expr(&expr.params[0], output, 0, ctx)?;
        output.push_str(";\n");
    } else if is_mut {
        output.push_str(&indent_str);
        // Determine C type from inferred type or fall back to int
        let c_type = if !expr.params.is_empty() {
            if let Some(inferred) = infer_type_from_expr(&expr.params[0], ctx) {
                til_type_to_c(&inferred).unwrap_or("int".to_string())
            } else {
                til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
            }
        } else {
            til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
        };
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(name);
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0, ctx)?;
        }
        output.push_str(";\n");
    } else {
        // const declaration
        output.push_str(&indent_str);
        // Determine C type from inferred type or fall back to int
        let c_type = if !expr.params.is_empty() {
            if let Some(inferred) = infer_type_from_expr(&expr.params[0], ctx) {
                til_type_to_c(&inferred).unwrap_or("int".to_string())
            } else {
                til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
            }
        } else {
            til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
        };
        output.push_str("const ");
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(name);
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0, ctx)?;
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

// Check if an expression is an enum construction (Type.Variant or Type.Variant(value))
// Returns the type name if it is, None otherwise
// AST structure for Color.Red(42): FCall -> [Identifier("Color") -> [Identifier("Red")], Literal(42)]
// AST structure for Color.Unknown: Identifier("Color") -> [Identifier("Unknown")]
fn get_enum_construction_type(expr: &Expr) -> Option<String> {
    // Check FCall case: Type.Variant(value) or Type.Variant()
    if let NodeType::FCall = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(type_name) = &expr.params[0].node_type {
                // Check if the type name is PascalCase
                if type_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
                    // Check if there's a nested identifier (the variant) that's also PascalCase
                    if !expr.params[0].params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &expr.params[0].params[0].node_type {
                            if variant_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
                                return Some(type_name.clone());
                            }
                        }
                    }
                }
            }
        }
    }

    // Check Identifier case: Type.Variant (no parentheses, no payload)
    if let NodeType::Identifier(type_name) = &expr.node_type {
        if type_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.params[0].node_type {
                    if variant_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
                        return Some(type_name.clone());
                    }
                }
            }
        }
    }

    None
}

// Infer type from a literal expression
// Returns Some(ValueType) if type can be inferred, None otherwise
fn infer_type_from_expr(expr: &Expr, ctx: &CodegenContext) -> Option<ValueType> {
    match &expr.node_type {
        NodeType::LLiteral(lit) => {
            match lit {
                Literal::Number(_) => Some(ValueType::TCustom("I64".to_string())),
                Literal::Str(_) => Some(ValueType::TCustom("Str".to_string())),
                Literal::List(_) => None, // Can't infer list element type from literal
            }
        },
        NodeType::FCall => {
            // Look up function return type
            if let Some(func_name) = get_fcall_func_name(expr, ctx) {
                if let Some(return_types) = ctx.func_return_types.get(&func_name) {
                    return return_types.first().cloned();
                }
            }
            None
        },
        NodeType::Identifier(name) => {
            // Look up variable type
            ctx.var_types.get(name).cloned()
        },
        _ => None
    }
}

fn emit_funcdef(_func_def: &SFuncDef, expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    // For now, just inline the function body (we're inside main anyway)
    // TODO: proper function generation with prototypes
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("{\n");
    for stmt in &expr.params {
        emit_expr(stmt, output, indent + 1, ctx)?;
    }
    output.push_str(&indent_str);
    output.push_str("}\n");
    Ok(())
}

fn emit_assignment(name: &str, expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str(name);
    output.push_str(" = ");
    if !expr.params.is_empty() {
        emit_expr(&expr.params[0], output, 0, ctx)?;
    }
    output.push_str(";\n");
    Ok(())
}

fn emit_return(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    let is_throwing = !ctx.current_throw_types.is_empty();

    if is_throwing {
        // Throwing function: store value through _ret pointer and return 0 (success)
        if !expr.params.is_empty() {
            output.push_str(&indent_str);
            output.push_str("*_ret = ");
            emit_expr(&expr.params[0], output, 0, ctx)?;
            output.push_str(";\n");
        }
        output.push_str(&indent_str);
        output.push_str("return 0;\n");
    } else {
        // Non-throwing function: normal return
        output.push_str(&indent_str);
        output.push_str("return");
        if !expr.params.is_empty() {
            output.push_str(" ");
            emit_expr(&expr.params[0], output, 0, ctx)?;
        }
        output.push_str(";\n");
    }
    Ok(())
}

fn emit_throw(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    // Throw: params[0] = the value to throw (typically a struct constructor like DivideByZero())
    if expr.params.is_empty() {
        return Err("codegen_c: throw requires a value".to_string());
    }

    let indent_str = "    ".repeat(indent);
    let thrown_expr = &expr.params[0];

    // Get the thrown type name from the expression
    // For FCall like DivideByZero(), params[0] is the Identifier with the name
    let thrown_type_name = match &thrown_expr.node_type {
        NodeType::FCall => {
            if !thrown_expr.params.is_empty() {
                if let NodeType::Identifier(name) = &thrown_expr.params[0].node_type {
                    name.clone()
                } else {
                    return Err("codegen_c: throw FCall must have identifier as first param".to_string());
                }
            } else {
                return Err("codegen_c: throw FCall has no params".to_string());
            }
        }
        NodeType::Identifier(name) => name.clone(),
        _ => return Err(format!("codegen_c: throw expression must be a constructor, got {:?}", thrown_expr.node_type)),
    };

    // Find the index of this type in current_throw_types
    let error_index = ctx.current_throw_types.iter().position(|vt| {
        match vt {
            crate::rs::parser::ValueType::TCustom(name) => name == &thrown_type_name,
            _ => false,
        }
    });

    match error_index {
        Some(idx) => {
            // Hoist throwing function calls from arguments of the thrown expression
            // E.g., throw Error.new(format(...)) needs to hoist format() first
            let hoisted: std::collections::HashMap<usize, String> = if let NodeType::FCall = &thrown_expr.node_type {
                if thrown_expr.params.len() > 1 {
                    let args = &thrown_expr.params[1..];
                    let hoisted_vec = hoist_throwing_args(args, output, indent, ctx)?;
                    hoisted_vec.into_iter().collect()
                } else {
                    std::collections::HashMap::new()
                }
            } else {
                std::collections::HashMap::new()
            };

            // Store the error value in the appropriate error pointer
            // Note: error params are 1-based (_err1, _err2, etc.)
            output.push_str(&indent_str);
            output.push_str(&format!("*_err{} = ", idx + 1));

            // Emit the thrown expression, using hoisted temp vars for arguments
            if let NodeType::FCall = &thrown_expr.node_type {
                emit_fcall_with_hoisted(thrown_expr, &hoisted, output, ctx)?;
            } else {
                emit_expr(thrown_expr, output, 0, ctx)?;
            }
            output.push_str(";\n");

            // Return the error index (1-based, since 0 = success)
            output.push_str(&indent_str);
            output.push_str(&format!("return {};\n", idx + 1));
            Ok(())
        }
        None => Err(format!(
            "codegen_c: thrown type '{}' not found in function's throw types: {:?}",
            thrown_type_name, ctx.current_throw_types
        )),
    }
}

/// Emit an FCall expression using pre-hoisted temp vars for arguments
fn emit_fcall_with_hoisted(
    expr: &Expr,
    hoisted: &std::collections::HashMap<usize, String>,
    output: &mut String,
    ctx: &mut CodegenContext,
) -> Result<(), String> {
    if expr.params.is_empty() {
        return Err("emit_fcall_with_hoisted: FCall with no params".to_string());
    }

    // Determine function name and UFCS receiver
    let (func_name, ufcs_receiver) = match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                (name.clone(), None)
            } else {
                if let NodeType::Identifier(method_name) = &expr.params[0].params[0].node_type {
                    (method_name.clone(), Some(&expr.params[0]))
                } else {
                    return Err("emit_fcall_with_hoisted: UFCS method name not Identifier".to_string());
                }
            }
        },
        _ => return Err("emit_fcall_with_hoisted: FCall first param not Identifier".to_string()),
    };

    // Handle UFCS or struct construction
    if let Some(receiver) = ufcs_receiver {
        if let NodeType::Identifier(receiver_name) = &receiver.node_type {
            let first_char = receiver_name.chars().next().unwrap_or('a');
            if first_char.is_uppercase() {
                // Type-qualified call: Type.func(args...) -> Type_func(args...)
                output.push_str(receiver_name);
                output.push_str("_");
                output.push_str(&func_name);
                output.push_str("(");
                for (i, arg) in expr.params.iter().skip(1).enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    emit_arg_or_hoisted(arg, i, hoisted, output, ctx)?;
                }
                output.push_str(")");
                return Ok(());
            }
        }
    }

    // Check for struct construction: TypeName() -> (TypeName){}
    if func_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false)
        && expr.params[0].params.is_empty()
        && expr.params.len() == 1
    {
        output.push_str("(");
        output.push_str(&func_name);
        output.push_str("){}");
        return Ok(());
    }

    // Regular function call
    output.push_str(&func_name);
    output.push_str("(");
    for (i, arg) in expr.params.iter().skip(1).enumerate() {
        if i > 0 {
            output.push_str(", ");
        }
        emit_arg_or_hoisted(arg, i, hoisted, output, ctx)?;
    }
    output.push_str(")");
    Ok(())
}

fn emit_if(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    // If: params[0] = condition, params[1] = then-body, params[2] = else-body (optional)
    if expr.params.len() < 2 {
        return Err("codegen_c: If requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("if (");
    emit_expr(&expr.params[0], output, 0, ctx)?;
    output.push_str(") {\n");

    // Then body
    emit_body(&expr.params[1], output, indent + 1, ctx)?;

    output.push_str(&indent_str);
    output.push_str("}");

    // Else branch (optional)
    if expr.params.len() > 2 {
        // Check if it's an else-if (nested If) or else block
        if let NodeType::If = &expr.params[2].node_type {
            output.push_str(" else ");
            // Emit nested if without extra indentation (it handles its own)
            emit_if(&expr.params[2], output, indent, ctx)?;
        } else {
            output.push_str(" else {\n");
            emit_body(&expr.params[2], output, indent + 1, ctx)?;
            output.push_str(&indent_str);
            output.push_str("}\n");
        }
    } else {
        output.push_str("\n");
    }

    Ok(())
}

fn emit_while(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    // While: params[0] = condition, params[1] = body
    if expr.params.len() < 2 {
        return Err("codegen_c: While requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("while (");
    emit_expr(&expr.params[0], output, 0, ctx)?;
    output.push_str(") {\n");

    emit_body(&expr.params[1], output, indent + 1, ctx)?;

    output.push_str(&indent_str);
    output.push_str("}\n");

    Ok(())
}

// Result struct for variant info extraction
struct VariantInfo {
    type_name: String,
    variant_name: String,
}

// Extract enum type and variant names from a case pattern expression
// For FCall: Type.Variant -> VariantInfo { type_name: "Type", variant_name: "Variant" }
fn get_case_variant_info(expr: &Expr) -> VariantInfo {
    match &expr.node_type {
        NodeType::FCall => {
            // FCall for Type.Variant (without payload extraction)
            if !expr.params.is_empty() {
                if let NodeType::Identifier(type_name) = &expr.params[0].node_type {
                    if !expr.params[0].params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &expr.params[0].params[0].node_type {
                            return VariantInfo {
                                type_name: type_name.clone(),
                                variant_name: variant_name.clone(),
                            };
                        }
                    }
                }
            }
            VariantInfo { type_name: String::new(), variant_name: String::new() }
        },
        NodeType::Identifier(name) => {
            // Identifier with nested params: Type.Variant
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.params[0].node_type {
                    return VariantInfo {
                        type_name: name.clone(),
                        variant_name: variant_name.clone(),
                    };
                }
            }
            VariantInfo { type_name: String::new(), variant_name: name.clone() }
        },
        _ => VariantInfo { type_name: String::new(), variant_name: String::new() },
    }
}

// Extract type name and variant name from a Pattern's variant_name (e.g., "Color.Green")
fn parse_pattern_variant_name(variant_name: &str) -> VariantInfo {
    if let Some(dot_pos) = variant_name.rfind('.') {
        let type_name = variant_name[..dot_pos].to_string();
        let var_name = variant_name[dot_pos + 1..].to_string();
        VariantInfo { type_name, variant_name: var_name }
    } else {
        // No dot - just variant name (shouldn't happen in practice)
        VariantInfo { type_name: String::new(), variant_name: variant_name.to_string() }
    }
}

fn emit_switch(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
    // Switch: params[0] = switch expression
    // params[1..] = alternating (case_pattern, body) pairs
    if expr.params.is_empty() {
        return Err("codegen_c: Switch requires expression".to_string());
    }

    let indent_str = "    ".repeat(indent);
    let case_indent = "    ".repeat(indent + 1);
    let body_indent = "    ".repeat(indent + 2);

    // Get the switch expression - we need to reference it for payload extraction
    let switch_expr = &expr.params[0];

    // Determine if this is an enum switch or a primitive switch
    // by scanning case patterns for Range or Pattern types
    let mut is_enum_switch = false;
    let mut has_ranges = false;
    let mut i = 1;
    while i < expr.params.len() {
        let case_pattern = &expr.params[i];
        match &case_pattern.node_type {
            NodeType::Range => {
                has_ranges = true;
            },
            NodeType::Pattern(_) => {
                is_enum_switch = true;
            },
            NodeType::Identifier(name) => {
                // Check if it has nested params (Type.Variant pattern like Color.Unknown)
                if !case_pattern.params.is_empty() {
                    is_enum_switch = true;
                }
                // Or check if it looks like an enum variant (contains a dot)
                else if name.contains('.') {
                    is_enum_switch = true;
                }
            },
            _ => {
                // DefaultCase and other patterns (literals) don't change detection
            }
        }
        i += 2;
    }

    // Emit: switch (expr) { or switch (expr.tag) {
    output.push_str(&indent_str);
    output.push_str("switch (");
    emit_expr(switch_expr, output, 0, ctx)?;
    if is_enum_switch && !has_ranges {
        output.push_str(".tag");
    }
    output.push_str(") {\n");

    // Process case patterns and bodies in pairs
    let mut i = 1;
    while i < expr.params.len() {
        let case_pattern = &expr.params[i];
        let case_body = if i + 1 < expr.params.len() {
            Some(&expr.params[i + 1])
        } else {
            None
        };

        match &case_pattern.node_type {
            NodeType::DefaultCase => {
                // default: { ... break; }
                output.push_str(&case_indent);
                output.push_str("default: {\n");
                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
            NodeType::Pattern(pattern_info) => {
                // case Type_Variant: { PayloadType binding = expr.payload.Variant; ... break; }
                let info = parse_pattern_variant_name(&pattern_info.variant_name);

                output.push_str(&case_indent);
                output.push_str("case ");
                output.push_str(&info.type_name);
                output.push_str("_");
                output.push_str(&info.variant_name);
                output.push_str(": {\n");

                // Emit payload extraction: PayloadType binding_var = expr.payload.VariantName;
                // TODO: Replace __auto_type with actual type by looking up enum definition
                // This would require passing a CodegenContext with enum defs through emit functions
                output.push_str(&body_indent);
                output.push_str("__auto_type ");
                output.push_str(&pattern_info.binding_var);
                output.push_str(" = ");
                emit_expr(switch_expr, output, 0, ctx)?;
                output.push_str(".payload.");
                output.push_str(&info.variant_name);
                output.push_str(";\n");

                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
            NodeType::Range => {
                // Range case: case low ... high: { ... break; }
                // Uses GCC extension for case ranges
                if case_pattern.params.len() < 2 {
                    return Err("codegen_c: Range requires start and end values".to_string());
                }

                output.push_str(&case_indent);
                output.push_str("case ");
                emit_expr(&case_pattern.params[0], output, 0, ctx)?;
                output.push_str(" ... ");
                emit_expr(&case_pattern.params[1], output, 0, ctx)?;
                output.push_str(": {\n");

                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
            _ => {
                // Regular case: Type.Variant -> case Type_Variant: { ... break; }
                let info = get_case_variant_info(case_pattern);

                output.push_str(&case_indent);
                output.push_str("case ");
                if !info.type_name.is_empty() {
                    output.push_str(&info.type_name);
                    output.push_str("_");
                }
                output.push_str(&info.variant_name);
                output.push_str(": {\n");

                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
        }

        i += 2; // Move to next case pattern
    }

    output.push_str(&indent_str);
    output.push_str("}\n");

    Ok(())
}

fn emit_fcall(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext) -> Result<(), String> {
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

    // Handle variadic parameter methods: args.len() and args.get(i, val)
    if let Some(receiver) = &ufcs_receiver {
        if let NodeType::Identifier(receiver_name) = &receiver.node_type {
            if let Some((param_name, _elem_type)) = &ctx.current_variadic_param {
                if receiver_name == param_name {
                    match func_name.as_str() {
                        "len" => {
                            // args.len() -> _args_len
                            output.push_str("_");
                            output.push_str(param_name);
                            output.push_str("_len");
                            return Ok(());
                        },
                        "get" => {
                            // args.get(i, val) -> val = args[i]
                            // params[1] is index, params[2] is output variable
                            if expr.params.len() >= 3 {
                                if let NodeType::Identifier(out_var) = &expr.params[2].node_type {
                                    output.push_str(&indent_str);
                                    output.push_str(out_var);
                                    output.push_str(" = ");
                                    output.push_str(param_name);
                                    output.push_str("[");
                                    emit_expr(&expr.params[1], output, 0, ctx)?;
                                    output.push_str("];\n");
                                    return Ok(());
                                }
                            }
                        },
                        _ => {}
                    }
                }
            }
        }
    }

    // Hoist throwing function calls from arguments (only at statement level)
    // When indent > 0, we're at statement level and can emit hoisted calls
    let hoisted: std::collections::HashMap<usize, String> = if indent > 0 && expr.params.len() > 1 {
        let args = &expr.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx)?;
        hoisted_vec.into_iter().collect()
    } else {
        std::collections::HashMap::new()
    };

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
                emit_arg_or_hoisted(arg, i, &hoisted, output, ctx)?;
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
                emit_arg_or_hoisted(arg, i, &hoisted, output, ctx)?;
            }
            output.push_str(");\n");
            Ok(())
        },
        // Arithmetic operations - emit as C expressions
        "add" => emit_binop(expr, output, "+", ufcs_receiver, &hoisted, ctx),
        "sub" => emit_binop(expr, output, "-", ufcs_receiver, &hoisted, ctx),
        "mul" => emit_binop(expr, output, "*", ufcs_receiver, &hoisted, ctx),
        "div" => emit_binop(expr, output, "/", ufcs_receiver, &hoisted, ctx),
        "mod" => emit_binop(expr, output, "%", ufcs_receiver, &hoisted, ctx),
        // Comparison
        "eq" => emit_binop(expr, output, "==", ufcs_receiver, &hoisted, ctx),
        "lt" => emit_binop(expr, output, "<", ufcs_receiver, &hoisted, ctx),
        "gt" => emit_binop(expr, output, ">", ufcs_receiver, &hoisted, ctx),
        "lteq" => emit_binop(expr, output, "<=", ufcs_receiver, &hoisted, ctx),
        "gteq" => emit_binop(expr, output, ">=", ufcs_receiver, &hoisted, ctx),
        // test(loc, cond, msg) - emit as assertion
        "test" => {
            // For C codegen, we just emit the test as an if statement
            // test(loc, cond, msg) -> if (!(cond)) { printf("FAIL: %s\n", msg); }
            if expr.params.len() < 4 {
                return Err("codegen_c: test requires 3 arguments".to_string());
            }
            output.push_str(&indent_str);
            output.push_str("if (!(");
            emit_arg_or_hoisted(&expr.params[2], 1, &hoisted, output, ctx)?;  // arg index 1 = params[2]
            output.push_str(")) { printf(\"FAIL: %s\\n\", ");
            emit_arg_or_hoisted(&expr.params[3], 2, &hoisted, output, ctx)?;  // arg index 2 = params[3]
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
            emit_arg_or_hoisted(&expr.params[2], 1, &hoisted, output, ctx)?;  // arg index 1 = params[2]
            output.push_str(") != (");
            emit_arg_or_hoisted(&expr.params[3], 2, &hoisted, output, ctx)?;  // arg index 2 = params[3]
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
                        // Check if this is an enum value (no arguments) vs function/constructor call
                        let has_args = expr.params.len() > 1;

                        if !has_args {
                            // Simple enum value: Type.Variant -> Type_Variant
                            output.push_str(receiver_name);
                            output.push_str("_");
                            output.push_str(&func_name);
                            if indent > 0 {
                                output.push_str(";\n");
                            }
                            return Ok(());
                        }

                        // Type-qualified call with args: Type.func(args...) -> Type_func(args...)
                        // For enum constructors with payloads: Type.Variant(val) -> Type_make_Variant(val)
                        // For struct constants: Type.CONSTANT -> Type_CONSTANT (no parens)
                        // Enum variants are capitalized, function names are lowercase
                        output.push_str(receiver_name);
                        output.push_str("_");
                        let func_first_char = func_name.chars().next().unwrap_or('a');
                        let has_args = expr.params.len() > 1;
                        if func_first_char.is_uppercase() && has_args {
                            // Enum constructor with payload (has arguments)
                            output.push_str("make_");
                        }
                        output.push_str(&func_name);
                        // Only add parens if it's a function call (has args or is lowercase)
                        if has_args || !func_first_char.is_uppercase() {
                            output.push_str("(");
                            // Emit all arguments after the function name
                            for (i, arg) in expr.params.iter().skip(1).enumerate() {
                                if i > 0 {
                                    output.push_str(", ");
                                }
                                emit_arg_or_hoisted(arg, i, &hoisted, output, ctx)?;
                            }
                            output.push_str(")");
                        }
                        if indent > 0 {
                            output.push_str(";\n");
                        }
                        return Ok(());
                    } else {
                        // Instance UFCS: instance.func(args...) -> Type_func(instance, args...)
                        // Look up the receiver's type for proper mangling
                        if let Some(receiver_type) = ctx.var_types.get(receiver_name) {
                            if let ValueType::TCustom(type_name) = receiver_type {
                                // Skip "auto" type - it's an inferred type placeholder
                                if type_name != "auto" {
                                    // Mangle as Type_func
                                    output.push_str(type_name);
                                    output.push_str("_");
                                }
                            }
                        }
                        output.push_str(&func_name);
                        output.push_str("(");
                        // First emit the receiver as first argument
                        emit_identifier_without_nested(receiver, output)?;
                        // Then emit remaining arguments
                        for (i, arg) in expr.params.iter().skip(1).enumerate() {
                            output.push_str(", ");
                            emit_arg_or_hoisted(arg, i, &hoisted, output, ctx)?;
                        }
                        output.push_str(")");
                        if indent > 0 {
                            output.push_str(";\n");
                        }
                        return Ok(());
                    }
                }
            }

            // Check for struct construction: TypeName() -> (TypeName){}
            // Struct names are PascalCase, no nested identifiers, no args
            if func_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false)
                && expr.params[0].params.is_empty()  // No nested params (not Type.Variant)
                && expr.params.len() == 1            // No constructor args
            {
                output.push_str("(");
                output.push_str(&func_name);
                output.push_str("){}");
                if indent > 0 {
                    output.push_str(";\n");
                }
                return Ok(());
            }

            // Regular function call - check for UFCS: func(instance, ...) -> Type_func(instance, ...)
            // If first argument is a variable with known type, try mangled name
            let mut mangled_name = func_name.clone();
            if expr.params.len() > 1 {
                if let NodeType::Identifier(first_arg_name) = &expr.params[1].node_type {
                    if let Some(receiver_type) = ctx.var_types.get(first_arg_name) {
                        if let ValueType::TCustom(type_name) = receiver_type {
                            // Check if mangled function exists in our known functions
                            let candidate = format!("{}_{}", type_name, func_name);
                            if ctx.known_functions.contains(&candidate) {
                                mangled_name = candidate;
                            }
                        }
                    }
                }
            }
            output.push_str(&mangled_name);
            output.push_str("(");

            // Check if this is a variadic function call
            if let Some((_variadic_name, elem_type, regular_count)) = ctx.func_variadic_args.get(&mangled_name).cloned() {
                // Emit regular args first (skip first param which is function name)
                let args: Vec<_> = expr.params.iter().skip(1).collect();
                for (i, arg) in args.iter().take(regular_count).enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    emit_arg_or_hoisted(arg, i, &hoisted, output, ctx)?;
                }
                // Emit count of variadic args
                let variadic_count = args.len().saturating_sub(regular_count);
                if regular_count > 0 {
                    output.push_str(", ");
                }
                output.push_str(&variadic_count.to_string());

                // Emit variadic args as compound literal array (C99)
                // Get C element type for the array
                let c_elem_type = match elem_type.as_str() {
                    "Str" => "const char*",
                    "I64" => "long long",
                    "Bool" => "unsigned char",
                    "U8" => "unsigned char",
                    _ => elem_type.as_str(),
                };

                if variadic_count == 0 {
                    // Empty variadic: pass NULL
                    output.push_str(", NULL");
                } else {
                    // Build compound literal: (type[]){arg1, arg2, ...}
                    output.push_str(", (");
                    output.push_str(c_elem_type);
                    output.push_str("[]){");
                    for (i, arg) in args.iter().skip(regular_count).enumerate() {
                        if i > 0 {
                            output.push_str(", ");
                        }
                        emit_arg_or_hoisted(arg, regular_count + i, &hoisted, output, ctx)?;
                    }
                    output.push_str("}");
                }
            } else {
                // Regular non-variadic function call
                // Emit arguments (skip first param which is function name)
                for (i, arg) in expr.params.iter().skip(1).enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    emit_arg_or_hoisted(arg, i, &hoisted, output, ctx)?;
                }
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

fn emit_binop(expr: &Expr, output: &mut String, op: &str, ufcs_receiver: Option<&Expr>, hoisted: &std::collections::HashMap<usize, String>, ctx: &mut CodegenContext) -> Result<(), String> {
    output.push('(');

    // For UFCS: receiver.op(arg) -> (receiver op arg)
    // For type-qualified: Type.op(a, b) -> (a op b) - ignore type prefix
    // For regular: op(a, b) -> (a op b)
    if let Some(receiver) = ufcs_receiver {
        // Check if this is a type-qualified call (Type.op(a, b)) vs instance call (x.op(y))
        // Type-qualified calls have 2+ args after the function name
        if expr.params.len() >= 3 {
            // Type-qualified: Type.op(a, b) -> (a op b)
            emit_arg_or_hoisted(&expr.params[1], 0, hoisted, output, ctx)?;
            output.push(' ');
            output.push_str(op);
            output.push(' ');
            emit_arg_or_hoisted(&expr.params[2], 1, hoisted, output, ctx)?;
        } else if expr.params.len() >= 2 {
            // Instance UFCS: x.op(y) -> (x op y)
            emit_identifier_without_nested(receiver, output)?;
            output.push(' ');
            output.push_str(op);
            output.push(' ');
            emit_arg_or_hoisted(&expr.params[1], 0, hoisted, output, ctx)?;
        } else {
            return Err("codegen_c: UFCS binary op requires 1 argument".to_string());
        }
    } else {
        // Regular call: emit params[1] and params[2]
        if expr.params.len() < 3 {
            return Err("codegen_c: binary op requires 2 arguments".to_string());
        }
        emit_arg_or_hoisted(&expr.params[1], 0, hoisted, output, ctx)?;
        output.push(' ');
        output.push_str(op);
        output.push(' ');
        emit_arg_or_hoisted(&expr.params[2], 1, hoisted, output, ctx)?;
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
