use std::collections::HashMap;
use std::fs;
use std::io::ErrorKind;
use crate::rs::init::{Context, SymbolInfo, EnumVal, EnumPayload, ScopeFrame, ScopeType, get_value_type, get_func_name_in_call, init_import_declarations, import_path_to_file_path};
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, Literal, ValueType, TTypeDef, Declaration, FunctionType, FuncDef, FCallInfo, FuncSig,
    value_type_to_str, get_combined_name, parse_tokens,
};
use crate::rs::typer::{get_func_def_for_fcall_with_expr, func_proc_has_multi_arg, basic_mode_checks, type_check, check_body_returns_throws, typer_import_declarations, ThrownType};
use crate::rs::utils::is_function_signature;
use crate::rs::lexer::lexer_from_source;
use crate::rs::mode::{can_be_imported, parse_mode, DEFAULT_MODE};
use crate::rs::preinit::preinit_expr;
use crate::rs::desugarer::desugar_expr;
use crate::rs::garbager::garbager_expr;
use crate::rs::ufcs::ufcs_expr;
use crate::rs::precomp::precomp_expr;
use crate::rs::ext;

// Interpreter/Eval phase: Runtime evaluation and execution
// This module handles the eval phase that runs after type checking.
// Manages heap memory allocation and actual program execution.

const RETURN_INSTANCE_NAME : &str = "___temp_return_val_";
const SKIP_AST             : bool = true;

// ---------- AST to string conversion

fn params_to_ast_str(end_line: bool, e: &Expr) -> String {
    let mut ast_str = "".to_string();
    for se in e.params.iter() {
        if end_line {
            ast_str.push_str(&format!("{}\n", to_ast_str(&se)));
        } else {
            ast_str.push_str(&format!("{} ", to_ast_str(&se)));
        }
    }
    return ast_str;
}

// TODO test this function again and maintain it, but in the self hosting side directly, perhaps
fn to_ast_str(e: &Expr) -> String {
    let mut ast_str = "".to_string();
    match &e.node_type {
        NodeType::LLiteral(Literal::Number(li64)) => {
            return li64.to_string();
        },
        NodeType::LLiteral(Literal::Str(lstring)) => {
            return lstring.to_string();
        },
        NodeType::DefaultCase => {
            return "default_case".to_string();
        }
        NodeType::Body => {
            return params_to_ast_str(true, &e)
        },
        // NodeType::Declaration(decl) => {
        //     ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::Assignment(var_name) => {
        //     ast_str.push_str(&format!("(set {} {})", var_name, to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        NodeType::FuncDef(func_def) => {
            match func_def.sig.function_type {
                FunctionType::FTFunc => return "(func)".to_string(),
                FunctionType::FTProc => return "(proc)".to_string(),
                FunctionType::FTMacro => return "(macro)".to_string(),
                FunctionType::FTFuncExt => return "(ext_func)".to_string(),
                FunctionType::FTProcExt => return "(ext_proc)".to_string(),
            }
        },
        NodeType::EnumDef(_) => {
            return "(enum)".to_string();
        },
        NodeType::StructDef(_) => {
            return "(struct)".to_string();
        },
        NodeType::Identifier(id_name) => {
            return id_name.clone();
        },
        NodeType::FCall(_) => {
            let f_name = get_func_name_in_call(&e);
            ast_str.push_str(&format!("({} {})", f_name, params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::LLiteral(Literal::List(_)) => {
            ast_str.push_str(&format!("({})", params_to_ast_str(false, &e)));
            return ast_str;
        },
        // NodeType::If => {
        //     ast_str.push_str(&format!("(if {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::While => {
        //     ast_str.push_str(&format!("(while {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::Switch => {
        //     ast_str.push_str(&format!("(switch {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        _ => todo!(),
    }
}

use crate::rs::eval_heap::{EvalHeap, SymbolEntry};



#[derive(Clone, Debug)]
pub struct EvalResult {
    pub value: String,
    pub is_return: bool,
    pub is_throw: bool,
    pub is_break: bool,
    pub is_continue: bool,
    pub thrown_type: String,  // Empty string means no thrown type
    pub heap_offset: usize,  // 0 means None (heap offset 0 is reserved for null)
}

impl EvalResult {
    pub fn new(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: false, is_break: false, is_continue: false, thrown_type: String::new(), heap_offset: 0}
    }

    pub fn new_return(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: true, is_throw: false, is_break: false, is_continue: false, thrown_type: String::new(), heap_offset: 0}
    }

    pub fn new_throw(value: &str, thrown_type: ValueType) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: true, is_break: false, is_continue: false, thrown_type: value_type_to_str(&thrown_type), heap_offset: 0}
    }

    pub fn new_break() -> EvalResult {
        return EvalResult{value: "".to_string(), is_return: false, is_throw: false, is_break: true, is_continue: false, thrown_type: String::new(), heap_offset: 0}
    }

    pub fn new_continue() -> EvalResult {
        return EvalResult{value: "".to_string(), is_return: false, is_throw: false, is_break: false, is_continue: true, thrown_type: String::new(), heap_offset: 0}
    }
}

// Helper function to extract String value from a Str struct instance
// Issue #91: Read a Str value from a raw heap address (e.g., for FuncSig variables from cast)
// This bypasses the field offset system which requires a known struct type.
// Issue #91: Read a Str value from a raw heap address (e.g., for FuncSig variables from cast)
// This bypasses the field offset system which requires a known struct type.
pub fn string_from_addr(context: &Context, addr: usize) -> Result<String, String> {
    // Str layout: c_string (Ptr at offset 0), _len (I64 after Ptr)
    // c_string.data is at offset 0 within Ptr (first field)
    // _len is at offset = size_of(Ptr) within Str (second field after c_string)
    let ptr_size = context.get_type_size("Ptr")?;
    // c_string.data at offset 0 (first field of first field)
    let data_bytes = EvalHeap::g().get(addr, 8);
    let mut buf = [0u8; 8];
    buf.copy_from_slice(&data_bytes[..8]);
    let c_string_ptr = usize::from_ne_bytes(buf);

    // _len at offset ptr_size (second field of Str, after c_string which is a Ptr)
    let len_bytes = EvalHeap::g().get(addr + ptr_size, 8);
    buf.copy_from_slice(&len_bytes[..8]);
    let length = usize::from_ne_bytes(buf);

    if length > 0 && length < 10_000_000 {
        let bytes = EvalHeap::g().get(c_string_ptr, length);
        Ok(String::from_utf8_lossy(bytes).to_string())
    } else {
        Ok(String::new())
    }
}

pub fn string_from_context(context: &Context, id: &str, e: &Expr) -> Result<String, String> {
    // Validate the Str struct exists
    context.get_struct(id, e)?;

    // Read the c_string.data field (I64 pointer to string data in EvalHeap)
    // Note: c_string is a Ptr struct { data: I64, is_borrowed: I64 }, so we read .data
    let c_string_ptr = EvalHeap::get_i64(context, &format!("{}.c_string.data", id), e)? as usize;

    // Read the _len field (I64 length)
    let length = EvalHeap::get_i64(context, &format!("{}._len", id), e)? as usize;

    // Read string bytes from EvalHeap and convert to String
    let bytes = EvalHeap::g().get(c_string_ptr, length);
    let result = String::from_utf8_lossy(bytes).to_string();
    Ok(result)
}

// Helper function to validate conditional statement parameters
fn validate_conditional_params(path: &str, e: &Expr, stmt_type: &str, min: usize, max: usize) -> Result<(), String> {
    if e.params.len() < min || e.params.len() > max {
        if min == max {
            return Err(e.lang_error(path, "eval", &format!("{} nodes must have exactly {} parameters.", stmt_type, min)));
        } else {
            return Err(e.lang_error(path, "eval", &format!("{} nodes must have {} or {} parameters.", stmt_type, min, max)));
        }
    }
    Ok(())
}

// Helper to evaluate boolean conditions for if/while statements.
fn eval_condition_to_bool(context: &Context, result: &EvalResult, expr: &Expr) -> Result<bool, String> {
    // Handle "true" and "false" directly (builtins return these, and they're the constant names)
    match result.value.as_str() {
        "true" => return Ok(true),
        "false" => return Ok(false),
        _ => {}
    }

    // Otherwise it's a Bool struct identifier - read its .data field
    let bool_id = &result.value;
    let data_field_id = format!("{}.data", bool_id);
    let u8_val = EvalHeap::get_u8(context, &data_field_id, expr)?;
    Ok(u8_val != 0)
}

// Helper function to validate function/procedure argument counts
fn validate_func_arg_count(path: &str, e: &Expr, name: &str, func_def: &FuncDef) -> Result<(), String> {
    let provided_args = e.params.len() - 1;
    let has_multi_arg = func_proc_has_multi_arg(func_def);

    // Check exact count for non-variadic functions
    if !has_multi_arg && func_def.sig.args.len() != provided_args {
        return Err(e.lang_error(path, "eval", &format!("func '{}' expected {} args, but {} were provided.",
                                                 name, func_def.sig.args.len(), provided_args)));
    }

    // Check minimum count for variadic functions
    if has_multi_arg && func_def.sig.args.len() - 1 > provided_args {
        return Err(e.lang_error(path, "eval", &format!("func '{}' expected at least {} args, but {} were provided.",
                                                 name, func_def.sig.args.len() - 1, provided_args)));
    }

    Ok(())
}

/// Read PRIMITIVE field values from an already-evaluated struct instance.
/// This reads ACTUAL primitive values (I64, U8) from the heap.
/// For nested struct fields (Str, Vec, etc.), recursively reads primitive values
/// but skips ptr fields to avoid copying pointers to temp instance memory.
/// Bug #43 fix: Recursively read primitive fields from nested structs to get
/// correct cap, _len values while skipping ptr. Also reads Str values as strings.
fn read_struct_primitive_fields(ctx: &Context, instance_id: &str, struct_type: &str, prefix: &str, e: &Expr) -> Result<HashMap<String, String>, String> {
    let struct_def = match ctx.scope_stack.lookup_struct(struct_type) {
        Some(def) => def.clone(),
        None => return Err(e.lang_error(&ctx.path, "read_struct_primitive_fields", &format!("struct '{}' not found", struct_type))),
    };

    let mut values = HashMap::new();
    for decl in struct_def.members.iter() {
        if decl.is_mut {
            let field_id = format!("{}.{}", instance_id, decl.name);
            let key = if prefix.is_empty() {
                decl.name.clone()
            } else {
                format!("{}.{}", prefix, decl.name)
            };

            if let ValueType::TCustom(type_name) = &decl.value_type {
                match type_name.as_str() {
                    "I64" => {
                        // Skip 'ptr' and 'c_string' fields - these point to temp instance memory
                        // and must use static default (0) so each instance gets fresh allocation
                        if decl.name == "ptr" || decl.name == "c_string" {
                            continue;
                        }
                        // Read actual I64 value from evaluated instance
                        let val = EvalHeap::get_i64(ctx, &field_id, e)?;
                        values.insert(key, val.to_string());
                    },
                    "U8" => {
                        // Read actual U8 value from evaluated instance
                        let val = EvalHeap::get_u8(ctx, &field_id, e)?;
                        values.insert(key, val.to_string());
                    },
                    "Str" => {
                        // Bug #43 fix: Read actual string VALUE, not pointer
                        // This ensures key_type_name = "Str" is correctly copied to template
                        let str_val = string_from_context(ctx, &field_id, e)?;
                        values.insert(key, str_val);
                    },
                    _ => {
                        // For nested structs (Vec, etc.), recursively read primitive fields
                        // This ensures we get actual cap, _len values from Vec.new while skipping ptr
                        if ctx.scope_stack.has_struct(type_name) {
                            let nested_key = if prefix.is_empty() {
                                decl.name.clone()
                            } else {
                                format!("{}.{}", prefix, decl.name)
                            };
                            let nested_values = read_struct_primitive_fields(ctx, &field_id, type_name, &nested_key, e)?;
                            for (k, v) in nested_values {
                                values.insert(k, v);
                            }
                        }
                    }
                }
            }
        }
    }
    Ok(values)
}

/// Pre-evaluate all default values for a struct type, including nested structs.
/// Returns a map from field name (with dotted paths for nested) to evaluated string value.
fn eval_struct_defaults(ctx: &mut Context, struct_type: &str, e: &Expr) -> Result<HashMap<String, String>, String> {
    let struct_def = match ctx.scope_stack.lookup_struct(struct_type) {
        Some(def) => def.clone(),
        None => return Err(e.lang_error(&ctx.path, "eval_struct_defaults", &format!("struct '{}' not found", struct_type))),
    };

    let mut defaults = HashMap::new();
    for decl in struct_def.members.iter() {
        if decl.is_mut {
            if let Some(default_expr) = struct_def.default_values.get(&decl.name) {
                // For nested struct types, eagerly create template BEFORE evaluating default
                // This handles forward references: Inner1's template is created before Inner1() is evaluated
                if let ValueType::TCustom(type_name) = &decl.value_type {
                    // Skip primitives, enums, and Str (handled specially)
                    if type_name != "U8" && type_name != "I64" && type_name != "Str" {
                        if ctx.scope_stack.lookup_enum(type_name).is_none() {
                            if ctx.scope_stack.has_struct(type_name) {
                                // Eagerly create template for nested struct (handles forward refs)
                                create_default_instance(ctx, type_name, e)?;
                            }
                        }
                    }
                }

                // Now evaluate the default expression (template exists if needed)
                let res = eval_expr(ctx, default_expr)?;
                if res.is_throw {
                    return Err(e.lang_error(&ctx.path, "eval_struct_defaults", &format!("thrown '{}' while evaluating default for field '{}'", res.thrown_type, decl.name)));
                }
                // Clone res.value before move so we can use it later for nested structs
                let instance_id = res.value.clone();
                defaults.insert(decl.name.clone(), res.value);

                // Handle nested structs: Bug #43 fix
                // 1. Read PRIMITIVE fields (I64, U8) from the evaluated instance to get actual values
                //    (e.g., Map.value_type_size = 8 from Map.new(Str, I64))
                // 2. Get STATIC defaults for nested struct fields (Str, Vec) to avoid copying ptr values
                //    that point to temp instance memory
                if let ValueType::TCustom(type_name) = &decl.value_type {
                    if type_name != "U8" && type_name != "I64" && type_name != "Str" {
                        if ctx.scope_stack.lookup_enum(type_name).is_none() {
                            if ctx.scope_stack.has_struct(type_name) {
                                // First, get static defaults for nested structs (Str, Vec fields)
                                let static_defaults = eval_struct_defaults(ctx, type_name, e)?;
                                for (k, v) in static_defaults {
                                    defaults.insert(format!("{}.{}", decl.name, k), v);
                                }

                                // Then, override with actual primitive values from evaluated instance
                                // This ensures value_type_size=8 instead of the static default 0
                                let primitive_values = read_struct_primitive_fields(ctx, &instance_id, type_name, "", e)?;
                                for (k, v) in primitive_values {
                                    defaults.insert(format!("{}.{}", decl.name, k), v);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Ok(defaults)
}

/// Create a default instance template for a struct type.
/// Called eagerly when struct declarations are evaluated.
pub fn create_default_instance(ctx: &mut Context, struct_type: &str, e: &Expr) -> Result<usize, String> {
    // Check if template already exists (e.g., from a previous import)
    if let Some(&offset) = EvalHeap::g().default_instances.get(struct_type) {
        return Ok(offset);
    }

    // Create template instance
    let template_id = format!("__default_{}", struct_type);

    // Declare temporary symbol for template (needed by insert_struct_core)
    ctx.scope_stack.declare_symbol(template_id.clone(), SymbolInfo {
        value_type: ValueType::TCustom(struct_type.to_string()),
        is_mut: true,
        
        is_own: false,
        is_comptime_const: false,
    });

    // Evaluate defaults and create template
    let defaults = eval_struct_defaults(ctx, struct_type, e)?;
    let result = EvalHeap::insert_struct_core(ctx, &template_id, struct_type, None, &defaults, e)?;

    // Get the template's heap offset (first mapping is the base struct)
    let template_offset = result.heap_mappings.first()
        .map(|m| m.offset)
        .ok_or_else(|| e.lang_error(&ctx.path, "create_default_instance", "No heap mapping for template"))?;

    // Cache the template offset
    EvalHeap::g().default_instances.insert(struct_type.to_string(), template_offset);

    Ok(template_offset)
}

/// Insert a struct instance using cached template.
/// Template is guaranteed to exist - created eagerly on eval_declaration.
pub fn insert_struct_instance(ctx: &mut Context, id: &str, type_name: &str, e: &Expr) -> Result<(), String> {
    let template_offset = EvalHeap::g().default_instances.get(type_name).copied()
        .ok_or_else(|| {
            e.lang_error(&ctx.path, "insert_struct_instance",
                &format!("template for '{}' not found", type_name))
        })?;
    EvalHeap::insert_struct(ctx, id, type_name, template_offset, e)
}

pub fn eval_expr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match &e.node_type {
        NodeType::Body => eval_body(context, &e.params),
        NodeType::LLiteral(Literal::Number(li64)) => Ok(EvalResult::new(li64)),
        NodeType::LLiteral(Literal::Str(lstring)) => Ok(EvalResult::new(lstring)),
        NodeType::LLiteral(Literal::List(llist)) => Ok(EvalResult::new(llist)),
        NodeType::FCall(_) => {
            // Issue #105: anonymous struct instantiation - struct { ... }(args)
            if let Some(first_param) = e.params.first() {
                if let NodeType::StructDef(struct_def) = &first_param.node_type {
                    // Register anonymous struct type
                    let temp_name = format!("AnonStruct{}", context.anon_struct_counter);
                    context.anon_struct_counter += 1;
                    if let Some(global_frame) = context.scope_stack.frames.first_mut() {
                        global_frame.structs.insert(temp_name.clone(), struct_def.clone());
                    }
                    // Replace StructDef with Identifier in a new FCall
                    let id_expr = Expr::new_clone(NodeType::Identifier(temp_name.clone()), first_param, vec![]);
                    let mut new_params = vec![id_expr];
                    new_params.extend(e.params.iter().skip(1).cloned());
                    let new_fcall = Expr::new_clone(e.node_type.clone(), e, new_params);
                    return eval_func_proc_call(&temp_name, context, &new_fcall);
                }
            }
            let f_name = get_func_name_in_call(&e);
            eval_func_proc_call(&f_name, context, &e)
        },
        NodeType::Declaration(declaration) => {
            eval_declaration(&declaration, context, &e)
        },
        NodeType::Assignment(var_name) => {
            eval_assignment(&var_name, context, &e)
        },
        NodeType::Identifier(name) => eval_identifier_expr(&name, context, &e),
        NodeType::If => {
            validate_conditional_params(&context.path, e, "if", 2, 3)?;
            let cond_expr = e.params.get(0).unwrap();
            let result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond)
            }
            if eval_condition_to_bool(context, &result_cond, cond_expr)? {
                return eval_expr(context, e.params.get(1).unwrap())
            } else if e.params.len() == 3 {
                return eval_expr(context, e.params.get(2).unwrap())
            } else {
                return Ok(EvalResult::new(""))
            }
        },
        NodeType::While => {
            validate_conditional_params(&context.path, e, "while", 2, 2)?;
            let mut while_cond_expr = e.params.get(0).unwrap();
            let mut while_result_cond = eval_expr(context, while_cond_expr)?;
            if while_result_cond.is_throw {
                return Ok(while_result_cond.clone())
            }
            while eval_condition_to_bool(context, &while_result_cond, while_cond_expr)? {
                let result = eval_expr(context, e.params.get(1).unwrap())?;
                if result.is_return || result.is_throw {
                    return Ok(result)
                }
                if result.is_break {
                    // Break exits the loop immediately
                    break;
                }
                // Continue just skips to the next iteration (re-evaluate condition)
                // No special handling needed - we just don't return
                while_cond_expr = e.params.get(0).unwrap();
                while_result_cond = eval_expr(context, while_cond_expr)?;
                if while_result_cond.is_throw {
                    return Ok(while_result_cond)
                }
            }
            Ok(EvalResult::new(""))
        },
        NodeType::Switch => Err(e.lang_error(&context.path, "eval", "Switch should have been desugared to if/else by desugarer phase")),
        NodeType::Return => {
            if e.params.len() == 0 {
                return Ok(EvalResult::new_return(""))
            } else if e.params.len() > 1 {
                return Err(e.lang_error(&context.path, "eval", "multiple return values not implemented yet"))
            } else {
                let return_result = eval_expr(context, e.params.get(0).unwrap())?;
                if return_result.is_throw {
                    return Ok(return_result)
                }
                let mut ret = EvalResult::new_return(&return_result.value);
                ret.heap_offset = return_result.heap_offset;
                return Ok(ret)
            }
        },
        NodeType::Throw => {
            if e.params.len() != 1 {
                return Err(e.lang_error(&context.path, "eval", "Throw can only return one value. This should have been caught before"))
            } else {
                let param_expr = e.params.get(0).unwrap();
                let throw_result = eval_expr(context, param_expr)?;
                if throw_result.is_throw {
                    return Ok(throw_result)
                }
                let thrown_type = get_value_type(context, param_expr)?;
                return Ok(EvalResult::new_throw(&throw_result.value, thrown_type))
            }
        },
        NodeType::Catch => {
            return Err(e.lang_error(&context.path, "eval", "Catch statements should always be evaluated within bodies."))
        },
        NodeType::Break => {
            return Ok(EvalResult::new_break())
        },
        NodeType::Continue => {
            return Ok(EvalResult::new_continue())
        },
        NodeType::ForIn(_) => {
            return Err(e.lang_error(&context.path, "eval", "ForIn should be desugared in precomp before reaching interpreter"))
        },
        NodeType::FuncDef(func_def) => {
            // Issue #91: Anonymous inline function - register with temp name and return it
            if !func_def.body.is_empty() {
                let temp_name = format!("__anon_func_{}", context.anon_func_counter);
                context.anon_func_counter += 1;
                if let Some(global_frame) = context.scope_stack.frames.first_mut() {
                    global_frame.funcs.insert(temp_name.clone(), func_def.clone());
                }
                Ok(EvalResult::new(&temp_name))
            } else {
                // FuncSig type definition - handled during registration
                Ok(EvalResult::new(""))
            }
        },
        NodeType::EnumDef(enum_def) => {
            // Issue #106: First-class enums - register as anonymous enum and return the name
            // Register in global frame so it survives function scope pops (e.g. macro returns)
            let temp_name = format!("AnonEnum{}", context.anon_enum_counter);
            context.anon_enum_counter += 1;
            if let Some(global_frame) = context.scope_stack.frames.first_mut() {
                global_frame.enums.insert(temp_name.clone(), enum_def.clone());
            }
            Ok(EvalResult::new(&temp_name))
        },
        NodeType::StructDef(struct_def) => {
            // Issue #105: First-class structs - register as anonymous struct and return the name
            // Register in global frame so it survives function scope pops (e.g. macro returns)
            let temp_name = format!("AnonStruct{}", context.anon_struct_counter);
            context.anon_struct_counter += 1;
            if let Some(global_frame) = context.scope_stack.frames.first_mut() {
                global_frame.structs.insert(temp_name.clone(), struct_def.clone());
            }
            Ok(EvalResult::new(&temp_name))
        },
        // NamedArg is handled inside FCall processing
        NodeType::NamedArg(_) => {
            return Err(e.lang_error(&context.path, "eval", "NamedArg should only appear inside FCall"))
        },
        // Range should be desugared by parser into for loops
        NodeType::Range => {
            return Err(e.lang_error(&context.path, "eval", "Range should be desugared in parser before reaching interpreter"))
        },
        // Pattern is handled inside Switch
        NodeType::Pattern(_) => {
            return Err(e.lang_error(&context.path, "eval", "Pattern should only appear inside Switch"))
        },
        // DefaultCase is handled inside Switch
        NodeType::DefaultCase => {
            return Err(e.lang_error(&context.path, "eval", "DefaultCase should only appear inside Switch"))
        },
        // Issue #188: Defer should have been desugared
        NodeType::Defer => {
            return Err(e.lang_error(&context.path, "eval", "Defer should have been desugared by desugarer phase"))
        },
        // Issue #185: OwnArg should have been desugared
        NodeType::OwnArg => {
            return Err(e.lang_error(&context.path, "eval", "OwnArg should have been desugared by desugarer phase"))
        },
    }
}

fn eval_func_proc_call(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if !matches!(e.node_type, NodeType::FCall(_)) {
        return Err(e.lang_error(&context.path, "eval", "eval_func_proc_call: Expected FCall node type"));
    }
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Err(e.lang_error(&context.path, "eval", "eval_func_proc_call: Expected FCall with at least one param for the Identifier")),
    };

    if let Some(struct_def) = context.scope_stack.lookup_struct(name) {
        let id_expr = e.params.get(0).unwrap();
        if id_expr.params.len() == 0 {
            // Clone struct members to avoid borrow issues
            let struct_members = struct_def.members.clone();

            // Check if this is a struct literal (has named args) or default constructor
            let has_named_args = e.params.iter().skip(1).any(|arg| matches!(&arg.node_type, NodeType::NamedArg(_)));

            if has_named_args {
                // Struct literal: Vec2(x=10, y=20)
                // Create a temp instance, set field values, return temp name
                let temp_id = EvalHeap::g().temp_id_counter;
                EvalHeap::g().temp_id_counter += 1;
                let temp_name = format!("{}{}", RETURN_INSTANCE_NAME, temp_id);

                // Declare the temp symbol
                context.scope_stack.declare_symbol(temp_name.to_string(), SymbolInfo {
                    value_type: ValueType::TCustom(name.to_string()),
                    is_mut: true,
                    
                    is_own: false,
                    is_comptime_const: false,
                });

                // Create struct instance with default values
                insert_struct_instance(context, &temp_name, &name, e)?;

                // Process named arguments to override field values
                for named_arg in e.params.iter().skip(1) {
                    if let NodeType::NamedArg(field_name) = &named_arg.node_type {
                        // Find the field type in the struct definition
                        let field_decl = struct_members.iter()
                            .find(|f| f.name == *field_name)
                            .ok_or_else(|| named_arg.error(&context.path, "eval",
                                &format!("Field '{}' not found in struct '{}'", field_name, name)))?;
                        let field_type = field_decl.value_type.clone();

                        // Evaluate the value expression
                        let named_value_expr = named_arg.params.get(0).unwrap();
                        let named_value_result = eval_expr(context, named_value_expr)?;
                        if named_value_result.is_throw {
                            return Ok(named_value_result);
                        }

                        // Set the field value based on its type
                        let field_id = format!("{}.{}", temp_name, field_name);
                        match &field_type {
                            ValueType::TCustom(field_type_name) => {
                                match field_type_name.as_str() {
                                    "I64" | "U8" | "Str" => {
                                        if field_type_name == "Str" && named_value_result.heap_offset > 0 {
                                            let src_offset = named_value_result.heap_offset;
                                            let dest_offset = context.get_field_offset(&field_id)?;
                                            let type_size = context.get_type_size("Str")?;
                                            let data = EvalHeap::g().get(src_offset, type_size).to_vec();
                                            EvalHeap::g().set(dest_offset, &data)?;
                                            continue;
                                        }
                                        EvalHeap::insert_primitive(context, &field_id, &field_type, &named_value_result.value, named_arg)?;
                                    },
                                    _ => {
                                        // Could be enum or nested struct
                                        let field_custom_symbol = context.scope_stack.lookup_symbol(&field_type_name)
                                            .ok_or_else(|| named_arg.error(&context.path, "eval",
                                                &format!("Unknown type '{}' for field '{}'", field_type_name, field_name)))?;
                                        let field_custom_value_type = field_custom_symbol.value_type.clone();
                                        match &field_custom_value_type {
                                            ValueType::TType(TTypeDef::TEnumDef) => {
                                                EvalHeap::insert_enum(context, &field_id, &field_type_name, &named_value_result.value, named_arg)?;
                                            },
                                            ValueType::TType(TTypeDef::TFuncSig) => {
                                                // Issue #91: Store function name as Str
                                                EvalHeap::insert_primitive(context, &field_id,
                                                    &ValueType::TCustom("Str".to_string()),
                                                    &named_value_result.value, named_arg)?;
                                            },
                                            ValueType::TType(TTypeDef::TStructDef) => {
                                                // Issue #159: deep copy via memcpy.
                                                // Garbager inserts clone for identifier args; fresh constructors are already new.
                                                // Copy bytes from source into parent struct's field slot.
                                                let src_offset = context.scope_stack.lookup_var(&named_value_result.value)
                                                    .ok_or_else(|| named_arg.error(&context.path, "eval",
                                                        &format!("Undefined variable '{}' for field '{}'", named_value_result.value, field_name)))?;
                                                let dest_offset = context.get_field_offset(&field_id)?;
                                                let type_size = context.get_type_size(&field_type_name)?;
                                                let data = EvalHeap::g().get(src_offset, type_size).to_vec();
                                                EvalHeap::g().set(dest_offset, &data)?;
                                            },
                                            _ => {
                                                return Err(named_arg.error(&context.path, "eval",
                                                    &format!("Unsupported field type '{}' for field '{}'", field_type_name, field_name)));
                                            }
                                        }
                                    }
                                }
                            },
                            _ => {
                                return Err(named_arg.error(&context.path, "eval",
                                    &format!("Unsupported field type for field '{}'", field_name)));
                            }
                        }
                    }
                }

                return Ok(EvalResult::new(&temp_name));
            } else {
                // Default constructor: Vec2()
                // Bug #160 fix: Create temp instance instead of using type name
                // This ensures field access via get_field_offset works correctly
                let default_temp_id = EvalHeap::g().temp_id_counter;
                EvalHeap::g().temp_id_counter += 1;
                let default_temp_name = format!("{}{}", RETURN_INSTANCE_NAME, default_temp_id);

                // Declare temp symbol
                context.scope_stack.declare_symbol(default_temp_name.clone(), SymbolInfo {
                    value_type: ValueType::TCustom(name.to_string()),
                    is_mut: true,
                    
                    is_own: false,
                    is_comptime_const: false,
                });

                insert_struct_instance(context, &default_temp_name, &name, e)?;
                return Ok(EvalResult::new(match &name[..] {
                    "U8" | "I64" => "0",
                    "Str" => "",
                    _ => &default_temp_name,
                }))
            }
        }
    }

    let combined_name = &get_combined_name(&context.path, func_expr)?;

    // Check if this is an enum constructor call (e.g., Color.Green(true))
    if context.scope_stack.is_enum_constructor(combined_name) {
        // Extract enum_type and variant_name
        let parts: Vec<&str> = combined_name.split('.').collect();
        let enum_type = parts[0];
        let variant_name = parts[1];

        // Get the enum definition to check if this variant has a payload type
        let enum_def = context.scope_stack.lookup_enum(enum_type).unwrap();
        let variant_type = enum_def.get(variant_name).cloned();

        match variant_type {
                Some(Some(payload_type)) => {
                    // This variant expects a payload
                    if e.params.len() < 2 {
                        return Err(e.error(&context.path, "eval", &format!("Enum constructor {}.{} expects a payload of type {}", enum_type, variant_name, value_type_to_str(&payload_type))));
                    }

                    // Evaluate the payload argument
                    let payload_expr = e.params.get(1).unwrap();
                    let payload_result = eval_expr(context, payload_expr)?;
                    if payload_result.is_throw {
                        return Ok(payload_result);
                    }

                    // Convert payload to bytes based on type
                    let payload_bytes = match &payload_type {
                        ValueType::TCustom(type_name) if type_name == "I64" => {
                            let i64_val = payload_result.value.parse::<i64>()
                                .map_err(|_| e.error(&context.path, "eval", &format!("Expected I64 payload, got '{}'", payload_result.value)))?;
                            i64_val.to_le_bytes().to_vec()
                        },
                        ValueType::TCustom(struct_type_name) => {
                            // Handle struct payloads
                            // Check if this is a struct type
                            let type_symbol = context.scope_stack.lookup_symbol(struct_type_name).ok_or_else(|| {
                                e.error(&context.path, "eval", &format!("Unknown type '{}'", struct_type_name))
                            })?;

                            match &type_symbol.value_type {
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    // Get struct size
                                    let struct_size = context.get_type_size( struct_type_name)
                                        .map_err(|err| e.error(&context.path, "eval", &err))?;

                                    // Get struct variable name from the original expression or create temporary for literals
                                    let struct_var_name = match &payload_expr.node_type {
                                        NodeType::Identifier(_name) if struct_type_name == "Str" => {
                                            // For Str payloads with identifier expressions (like t.token_str),
                                            // create a temporary Str from the evaluated result value
                                            let temp_var_name = format!("__temp_str_{}", context.scope_stack.frames.last().unwrap().heap_index.len());
                                            let string_value = &payload_result.value;

                                            // Add symbol entry before calling insert_string
                                            context.scope_stack.declare_symbol(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false,
                                                
                                                is_own: false,
                                                is_comptime_const: false,
                                            });

                                            EvalHeap::insert_string(context, &temp_var_name, &string_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        NodeType::Identifier(name) => name.clone(),
                                        NodeType::LLiteral(Literal::Str(_)) if struct_type_name == "Str" => {
                                            // For string literals, create a temporary Str struct
                                            let str_lit_temp_var_name = format!("__temp_str_{}", context.scope_stack.frames.last().unwrap().heap_index.len());
                                            let str_lit_string_value = &payload_result.value;

                                            // Add symbol entry before calling insert_string
                                            context.scope_stack.declare_symbol(str_lit_temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false, // Temporary string is immutable
                                                
                                                is_own: false,
                                                is_comptime_const: false,
                                            });

                                            EvalHeap::insert_string(context, &str_lit_temp_var_name, &str_lit_string_value.to_string(), e)?;
                                            str_lit_temp_var_name
                                        },
                                        NodeType::LLiteral(Literal::Number(_)) if struct_type_name == "I64" => {
                                            // For I64 literals, create a temporary I64 struct
                                            let i64_lit_temp_var_name = format!("__temp_i64_{}", context.scope_stack.frames.last().unwrap().heap_index.len());
                                            let i64_lit_value = &payload_result.value;

                                            // Add symbol entry before calling insert_i64
                                            context.scope_stack.declare_symbol(i64_lit_temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("I64".to_string()),
                                                is_mut: false,
                                                
                                                is_own: false,
                                                is_comptime_const: false,
                                            });

                                            EvalHeap::insert_i64(context, &i64_lit_temp_var_name, &i64_lit_value.to_string(), e)?;
                                            i64_lit_temp_var_name
                                        },
                                        // Bug #56 fix: Handle FCall (e.g., x.clone()) for Str payloads
                                        // Issue #180: Also handle FCall for non-Str struct payloads (e.g., FCallInfo())
                                        NodeType::FCall(_) if struct_type_name == "Str" => {
                                            let str_fcall_temp_var_name = format!("__temp_str_{}", context.scope_stack.frames.last().unwrap().heap_index.len());
                                            let str_fcall_string_value = &payload_result.value;

                                            context.scope_stack.declare_symbol(str_fcall_temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false,
                                                
                                                is_own: false,
                                                is_comptime_const: false,
                                            });

                                            EvalHeap::insert_string(context, &str_fcall_temp_var_name, &str_fcall_string_value.to_string(), e)?;
                                            str_fcall_temp_var_name
                                        },
                                        NodeType::FCall(_) => {
                                            // FCall returning a struct (e.g., FCallInfo()) - already evaluated,
                                            // payload_result.value is the temp var name holding the struct
                                            payload_result.value.clone()
                                        },
                                        _ => return Err(e.error(&context.path, "eval", &format!("Enum variant payload must be a variable, literal, or function call, got {:?}", payload_expr.node_type))),
                                    };

                                    // Get struct offset from heap
                                    let offset = context.scope_stack.lookup_var(&struct_var_name).ok_or_else(|| {
                                        e.error(&context.path, "eval", &format!("Struct '{}' not found in heap", struct_var_name))
                                    })?;

                                    // Copy struct bytes from heap
                                    let struct_bytes = EvalHeap::g().get(offset, struct_size).to_vec();
                                    struct_bytes
                                },
                                ValueType::TType(TTypeDef::TEnumDef) => {
                                    // Handle enum payloads
                                    // Get enum variable name from the original expression
                                    // If it's a function call (enum constructor), evaluate it first to create a temp variable
                                    let enum_var_name = match &payload_expr.node_type {
                                        NodeType::Identifier(name) if payload_expr.params.is_empty() => name.clone(),
                                        NodeType::Identifier(_) | NodeType::FCall(_) => {
                                            // This is a nested enum constructor call (e.g., InnerEnum.ValueA(42))
                                            // Create a temporary variable to hold the result
                                            let enum_ctor_temp_var_name = format!("__temp_enum_{}", context.scope_stack.frames.last().unwrap().heap_index.len());

                                            // Recursively evaluate the enum constructor
                                            // This could be either an FCall or an Identifier with params (like Inner.A)
                                            let enum_ctor_nested_result = eval_expr(context, payload_expr)?;
                                            if enum_ctor_nested_result.is_throw {
                                                return Ok(enum_ctor_nested_result);
                                            }

                                            // Add symbol entry before calling insert_enum
                                            context.scope_stack.declare_symbol(enum_ctor_temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom(struct_type_name.clone()),
                                                is_mut: false,
                                                
                                                is_own: false,
                                                is_comptime_const: false,
                                            });

                                            // The result is the enum variant name (e.g., "InnerEnum.ValueA")
                                            // insert_enum will use context.temp_enum_payload for the payload bytes
                                            EvalHeap::insert_enum(context, &enum_ctor_temp_var_name, struct_type_name, &enum_ctor_nested_result.value, e)?;
                                            enum_ctor_temp_var_name
                                        },
                                        _ => return Err(e.error(&context.path, "eval", &format!("Enum payload must be a variable identifier or enum constructor, got {:?}", payload_expr.node_type))),
                                    };

                                    // Get the full enum value including its payload
                                    let enum_val = EvalHeap::get_enum(context, &enum_var_name, e)?;

                                    // Calculate total enum size: 8 bytes tag + payload bytes
                                    let mut enum_bytes = Vec::new();

                                    // Get the variant position
                                    let variant_pos = Context::get_variant_pos(
                                        context.scope_stack.lookup_enum(struct_type_name).ok_or_else(|| {
                                            e.error(&context.path, "eval", &format!("Enum definition for '{}' not found", struct_type_name))
                                        })?,
                                        &enum_val.enum_name,
                                        &context.path,
                                        e
                                    )?;

                                    // Add 8 bytes for variant tag
                                    enum_bytes.extend_from_slice(&variant_pos.to_le_bytes());

                                    // Add payload bytes if present
                                    if let Some(payload_data) = &enum_val.payload {
                                        enum_bytes.extend_from_slice(payload_data);
                                    }

                                    enum_bytes
                                },
                                _ => {
                                    return Err(e.error(&context.path, "eval", &format!("Unsupported payload type: {}", value_type_to_str(&payload_type))));
                                }
                            }
                        },
                        _ => {
                            return Err(e.error(&context.path, "eval", &format!("Unsupported payload type: {}", value_type_to_str(&payload_type))));
                        }
                    };

                    // Store payload in temp location for insert_enum to use
                    context.temp_enum_payload = Some(EnumPayload { data: payload_bytes, value_type: payload_type });

                    // Return the enum variant name
                    return Ok(EvalResult::new(&format!("{}.{}", enum_type, variant_name)));
                },
                Some(None) => {
                    // This variant doesn't have a payload, but constructor was called with args
                    if e.params.len() > 1 {
                        return Err(e.error(&context.path, "eval", &format!("Enum variant {}.{} does not take a payload", enum_type, variant_name)));
                    }
            },
            None => {
                return Err(e.error(&context.path, "eval", &format!("Enum {} does not have variant {}", enum_type, variant_name)));
            }
        }
    }

    // TODO: After precomp, UFCS is already resolved so the mutation in get_func_def_for_fcall_with_expr
    // is a no-op. Could save this clone by adding a simpler lookup function that doesn't need &mut.
    let mut new_fcall_e = e.clone();
    let mut func_def = match get_func_def_for_fcall_with_expr(&context, &mut new_fcall_e)? {
        Some(func_def_) => func_def_,
        None  => {
            return Err(e.lang_error(&context.path, "eval", "eval_func_proc_call: Instantiations should be handled already"))
        },
    };
    // Issue #91: If this is a FuncSig-typed variable (e.g., from cast or struct field),
    // resolve the actual function by reading the stored function name
    if func_def.body.is_empty() && !func_def.is_ext() {
        if let Some(sym) = context.scope_stack.lookup_symbol(&combined_name) {
            if let ValueType::TCustom(ref type_name) = sym.value_type {
                if let Some(type_sym) = context.scope_stack.lookup_symbol(type_name) {
                    if type_sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                        // Read function name from heap (stored as Str)
                        // Use string_from_addr since variable may be typed as FuncSig, not Str
                        if let Some(var_addr) = context.scope_stack.lookup_var(&combined_name) {
                            let actual_func_name = string_from_addr(context, var_addr)?;
                            if let Some(actual_fd) = context.scope_stack.lookup_func(&actual_func_name) {
                                func_def = actual_fd.clone();
                            }
                        }
                    }
                }
            }
        }
    }
    if func_def.is_ext() {
        // External/core functions are treated specially
        let is_proc = func_def.is_proc();
        let parts: Vec<&str> = combined_name.split('.').collect();
        let last_name = match parts.last() {
            Some(last_name_) => last_name_,
            None => {
                return Err(e.lang_error(&context.path, "eval", "Somehow function without name"))
            }
        };
        return eval_core_func_proc_call(&last_name, context, &new_fcall_e, is_proc)
    }
    return eval_user_func_proc_call(&func_def, &combined_name, context, &new_fcall_e)
}

// Issue #105 Step 4d: Check if a declared metatype annotation matches an inferred TType
fn metatype_matches(declared: &ValueType, inferred: &ValueType) -> bool {
    match (declared, inferred) {
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TStructDef)) if name == "StructDef" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TEnumDef)) if name == "EnumDef" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TFuncSig)) if name == "FuncSig" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TFuncDef)) if name == "FuncDef" => true,
        // name : FuncDef = func(a: I64) { body } -- func literal inferred as TFunction
        (ValueType::TCustom(name), ValueType::TFunction(_)) if name == "FuncDef" => true,
        _ => false,
    }
}

pub fn eval_declaration(declaration: &Declaration, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let inner_e = e.params.get(0).unwrap();

    // cast(Type, ptr_expr) - create alias to data at ptr.data address
    if let NodeType::FCall(_) = &inner_e.node_type {
        let cast_f_name = get_func_name_in_call(&inner_e);
        if cast_f_name == "cast" && inner_e.params.len() >= 3 {
            let type_name = match &inner_e.params.get(1).unwrap().node_type {
                NodeType::Identifier(name) => name.clone(),
                _ => return Err(e.lang_error(&context.path, "eval", "cast: first argument must be a type name")),
            };
            // Evaluate ptr_expr to get the Ptr
            let ptr_result = eval_expr(context, inner_e.params.get(2).unwrap())?;
            if ptr_result.is_throw {
                return Ok(ptr_result);
            }
            // ptr_result.value is the Ptr variable name - look up its heap address
            let ptr_addr = match ptr_result.value.parse::<usize>() {
                Ok(addr) => addr,
                Err(_) => {
                    context.scope_stack.lookup_var(&ptr_result.value)
                        .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("cast: cannot find ptr variable '{}'", ptr_result.value)))?
                }
            };
            // Read .data field (first I64 at offset 0 of the Ptr struct)
            let data_bytes = EvalHeap::g().get(ptr_addr, 8);
            let mut addr_buf = [0u8; 8];
            addr_buf.copy_from_slice(&data_bytes[..8]);
            let alias_addr = usize::from_ne_bytes(addr_buf);
            // Declare variable with type and bind to alias address
            context.scope_stack.declare_symbol(declaration.name.clone(), SymbolInfo {
                value_type: ValueType::TCustom(type_name),
                is_mut: true,
                
                is_own: false,
                is_comptime_const: false,
            });
            context.scope_stack.insert_var(declaration.name.clone(), alias_addr);
            return Ok(EvalResult::new(""));
        }
    }

    let mut value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error(&context.path, "eval", &error_string));
        },
    };
    // Issue #91: Detect function signature definitions
    if let NodeType::FuncDef(func_def) = &inner_e.node_type {
        if is_function_signature(func_def) {
            value_type = ValueType::TType(TTypeDef::TFuncSig);
        }
    }
    // Issue #91: Resolve function signature type references
    let mut is_sig_ref = false;
    if let ValueType::TCustom(ref sig_name) = declaration.value_type {
        if let Some(sym) = context.scope_stack.lookup_symbol(sig_name) {
            if sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                if let Some(sfd) = context.scope_stack.lookup_func(sig_name) {
                    value_type = ValueType::TFunction(sfd.sig.function_type.clone());
                    is_sig_ref = true;
                }
            }
        }
    }
    // Type checking - INFER_TYPE should have been resolved by typer
    if declaration.value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
        // Issue #105: Accept inferred type (e.g., struct declarations inside macro bodies)
    } else if is_sig_ref {
        // Issue #91: FunctionSig reference resolved above - skip type check
    // Issue #105 Step 4d: Accept explicit metatype annotations
    } else if metatype_matches(&declaration.value_type, &value_type) {
        // StructDef/EnumDef/FuncSig annotations match TType variants
    } else if declaration.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
        value_type = declaration.value_type.clone();
    } else if value_type != declaration.value_type {
        return Err(e.lang_error(&context.path, "eval", &format!("'{}' declared of type {} but initialized to type {:?}.", declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type))));
    }

    if e.params.len() != 1 {
        return Err(e.lang_error(&context.path, "eval", "Declarations can have only one child expression"))
    }

    match value_type {
        ValueType::TCustom(s) if s == INFER_TYPE => {
            return Err(e.lang_error(&context.path, "eval", &format!("'{}' declared of type '{}' but still to infer type '{}'",
                                                     declaration.name, value_type_to_str(&declaration.value_type), &s)));
        },
        ValueType::TType(TTypeDef::TEnumDef) => {
            match &inner_e.node_type {
                NodeType::EnumDef(enum_def) => {
                    context.scope_stack.declare_enum(declaration.name.clone(), enum_def.clone());
                    // Issue #106: Also register in global frame so enum survives macro function scope pops
                    if let Some(global_frame) = context.scope_stack.frames.first_mut() {
                        global_frame.enums.entry(declaration.name.to_string()).or_insert_with(|| enum_def.clone());
                    }
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
                    // Issue #161: Process namespace mutable members for enums
                    for ns_member_decl in &enum_def.ns.members {
                        if !ns_member_decl.is_mut { continue; }
                        if let Some(ns_default_value) = enum_def.ns.default_values.get(&ns_member_decl.name) {
                            if let NodeType::FuncDef(_) = &ns_default_value.node_type {
                                continue; // Functions are handled by init, not here
                            }
                            let ns_combined_name = format!("{}.{}", declaration.name, ns_member_decl.name);
                            let ns_member_value_type = match &ns_member_decl.value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    return Err(e.lang_error(&context.path, "eval", &format!("Namespace member '{}.{}' has INFER_TYPE - should have been resolved by typer",
                                                                             &declaration.name, &ns_member_decl.name)));
                                },
                                _ => ns_member_decl.value_type.clone(),
                            };
                            match ns_member_value_type {
                                ValueType::TCustom(ref ns_type_name) => {
                                    let ns_result = eval_expr(context, ns_default_value)?;
                                    if ns_result.is_throw {
                                        return Ok(ns_result);
                                    }
                                    let ns_expr_result_str = ns_result.value;
                                    match ns_type_name.as_str() {
                                        "I64" | "U8" | "Str" => {
                                            EvalHeap::insert_primitive(context, &ns_combined_name, &ns_member_value_type, &ns_expr_result_str, e)?;
                                        },
                                        _ => {
                                            insert_struct_instance(context, &ns_combined_name, ns_type_name, e)?;
                                            let ns_src_offset = context.scope_stack.lookup_var(&ns_expr_result_str)
                                                .ok_or_else(|| e.lang_error(&context.path, "eval",
                                                    &format!("Undefined variable '{}' for namespace member '{}'", ns_expr_result_str, ns_combined_name)))?;
                                            let ns_dest_offset = context.get_field_offset(&ns_combined_name)?;
                                            let ns_type_size = context.get_type_size(ns_type_name)?;
                                            let ns_data = EvalHeap::g().get(ns_src_offset, ns_type_size).to_vec();
                                            EvalHeap::g().set(ns_dest_offset, &ns_data)?;
                                        },
                                    }
                                },
                                _ => {
                                    return Err(e.todo_error(&context.path, "eval", &format!("Cannot declare namespace member '{}.{}' of type '{}'",
                                                                             &declaration.name,
                                                                             &ns_member_decl.name,
                                                                             value_type_to_str(&ns_member_decl.value_type))));
                                },
                            }
                            context.scope_stack.declare_symbol(ns_combined_name.to_string(),
                                                   SymbolInfo{value_type: ns_member_decl.value_type.clone(), is_mut: ns_member_decl.is_mut, is_own: ns_member_decl.is_own, is_comptime_const: false });
                        }
                    }
                    // Issue #161: Update scope stack enum's ns with resolved types from AST
                    if let Some(existing_enum) = context.scope_stack.lookup_enum(&declaration.name) {
                        let mut updated_enum = existing_enum.clone();
                        updated_enum.ns = enum_def.ns.clone();
                        context.scope_stack.declare_enum(declaration.name.to_string(), updated_enum);
                    }
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                              &declaration.name, value_type_to_str(&declaration.value_type)))),
            }
        },
        ValueType::TType(TTypeDef::TFuncSig) => {
            // Issue #91: Function signature type definition
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.scope_stack.declare_func(declaration.name.to_string(), func_def.clone());
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: true });
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error(&context.path, "eval", &format!("Cannot declare '{}' of type 'FunctionSig', expected func definition.",
                                                              &declaration.name))),
            }
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            match &inner_e.node_type {
                NodeType::StructDef(struct_def) => {
                    // Issue #108: Don't overwrite struct if already declared (may have merged namespace members)
                    if context.scope_stack.lookup_struct(&declaration.name).is_none() {
                        context.scope_stack.declare_struct(declaration.name.to_string(), struct_def.clone());
                    }
                    // Issue #105: Also register in global frame so struct survives macro function scope pops
                    if let Some(global_frame) = context.scope_stack.frames.first_mut() {
                        global_frame.structs.entry(declaration.name.to_string()).or_insert_with(|| struct_def.clone());
                    }
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
                    // Process members from AST struct_def (not merged struct - namespace members handled separately)
                    for member_decl in &struct_def.members {
                        if !member_decl.is_mut {
                            let combined_name = format!("{}.{}", declaration.name, member_decl.name);
                            let default_value = match struct_def.default_values.get(&member_decl.name) {
                                Some(_default_value) => _default_value,
                                None => {
                                    return Err(e.lang_error(&context.path, "eval", &format!("Struct member '{}.{}' expected to have default value.",
                                                                             &declaration.name, &member_decl.name)));
                                },
                            };
                            // INFER_TYPE should have been resolved by typer
                            let member_value_type = match &member_decl.value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    return Err(e.lang_error(&context.path, "eval", &format!("Struct member '{}.{}' has INFER_TYPE - should have been resolved by typer",
                                                                             &declaration.name, &member_decl.name)));
                                },
                                _ => member_decl.value_type.clone(),
                            };

                            match member_value_type {
                                ValueType::TCustom(ref type_name) => {
                                    let result = eval_expr(context, default_value)?;
                                    if result.is_throw {
                                        return Ok(result); // Propagate throw
                                    }
                                    let expr_result_str = result.value;
                                    match type_name.as_str() {
                                        "I64" | "U8" | "Str" => {
                                            EvalHeap::insert_primitive(context, &combined_name, &member_value_type, &expr_result_str, e)?;
                                        },
                                        _ => {
                                            // Issue #159 Step 7: Replace copy_fields with memcpy
                                            // for struct member default values during struct definition.
                                            insert_struct_instance(context, &combined_name, type_name, e)?;
                                            let src_offset = context.scope_stack.lookup_var(&expr_result_str)
                                                .ok_or_else(|| e.lang_error(&context.path, "eval",
                                                    &format!("Undefined variable '{}' for member '{}'", expr_result_str, combined_name)))?;
                                            let dest_offset = context.get_field_offset(&combined_name)?;
                                            let type_size = context.get_type_size(type_name)?;
                                            let data = EvalHeap::g().get(src_offset, type_size).to_vec();
                                            EvalHeap::g().set(dest_offset, &data)?;
                                        },
                                    }
                                },
                               _ => {
                                    return Err(e.todo_error(&context.path, "eval", &format!("Cannot declare '{}.{}' of type '{}'",
                                                                             &declaration.name,
                                                                             &member_decl.name,
                                                                             value_type_to_str(&member_decl.value_type))));
                                },
                            }

                            context.scope_stack.declare_symbol(combined_name.to_string(),
                                                   SymbolInfo{value_type: member_decl.value_type.clone(), is_mut: member_decl.is_mut, is_own: member_decl.is_own, is_comptime_const: false });
                        }
                    }
                    // Issue #161: Process namespace mutable members
                    for ns_member_decl in &struct_def.ns.members {
                        if !ns_member_decl.is_mut { continue; }
                        if let Some(ns_default_value) = struct_def.ns.default_values.get(&ns_member_decl.name) {
                            if let NodeType::FuncDef(_) = &ns_default_value.node_type {
                                continue; // Functions are handled by init, not here
                            }
                            let ns_combined_name = format!("{}.{}", declaration.name, ns_member_decl.name);
                            let ns_member_value_type = match &ns_member_decl.value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    return Err(e.lang_error(&context.path, "eval", &format!("Namespace member '{}.{}' has INFER_TYPE - should have been resolved by typer",
                                                                             &declaration.name, &ns_member_decl.name)));
                                },
                                _ => ns_member_decl.value_type.clone(),
                            };
                            match ns_member_value_type {
                                ValueType::TCustom(ref ns_type_name) => {
                                    let ns_result = eval_expr(context, ns_default_value)?;
                                    if ns_result.is_throw {
                                        return Ok(ns_result);
                                    }
                                    let ns_expr_result_str = ns_result.value;
                                    match ns_type_name.as_str() {
                                        "I64" | "U8" | "Str" => {
                                            EvalHeap::insert_primitive(context, &ns_combined_name, &ns_member_value_type, &ns_expr_result_str, e)?;
                                        },
                                        _ => {
                                            insert_struct_instance(context, &ns_combined_name, ns_type_name, e)?;
                                            let ns_src_offset = context.scope_stack.lookup_var(&ns_expr_result_str)
                                                .ok_or_else(|| e.lang_error(&context.path, "eval",
                                                    &format!("Undefined variable '{}' for namespace member '{}'", ns_expr_result_str, ns_combined_name)))?;
                                            let ns_dest_offset = context.get_field_offset(&ns_combined_name)?;
                                            let ns_type_size = context.get_type_size(ns_type_name)?;
                                            let ns_data = EvalHeap::g().get(ns_src_offset, ns_type_size).to_vec();
                                            EvalHeap::g().set(ns_dest_offset, &ns_data)?;
                                        },
                                    }
                                },
                                _ => {
                                    return Err(e.todo_error(&context.path, "eval", &format!("Cannot declare namespace member '{}.{}' of type '{}'",
                                                                             &declaration.name,
                                                                             &ns_member_decl.name,
                                                                             value_type_to_str(&ns_member_decl.value_type))));
                                },
                            }
                            context.scope_stack.declare_symbol(ns_combined_name.to_string(),
                                                   SymbolInfo{value_type: ns_member_decl.value_type.clone(), is_mut: ns_member_decl.is_mut, is_own: ns_member_decl.is_own, is_comptime_const: false });
                        }
                    }
                    // Issue #161: Update scope stack struct's ns with resolved types from AST
                    if let Some(existing_struct) = context.scope_stack.lookup_struct(&declaration.name) {
                        let mut updated_struct = existing_struct.clone();
                        updated_struct.ns = struct_def.ns.clone();
                        context.scope_stack.declare_struct(declaration.name.to_string(), updated_struct);
                    }
                    // Eagerly create default instance template for this struct type
                    create_default_instance(context, &declaration.name, e)?;
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error(&context.path, "eval", &format!("Cannot declare {} of type {:?}, expected struct definition.",
                                                              &declaration.name, &declaration.value_type))),
            }
        },
        ValueType::TFunction(_) => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.scope_stack.declare_func(declaration.name.to_string(), func_def.clone());
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
                    return Ok(EvalResult::new(""))
                },

                _ => {
                    // Issue #91: Function pointer value from expression (e.g., op := get_op(0))
                    // Evaluate the expression to get the function name, then register the func def
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result);
                    }
                    let func_name = &result.value;
                    if let Some(func_def) = context.scope_stack.lookup_func(func_name) {
                        let fd_clone = func_def.clone();
                        context.scope_stack.declare_func(declaration.name.to_string(), fd_clone);
                        context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
                        return Ok(EvalResult::new(""))
                    } else {
                        return Err(e.error(&context.path, "eval", &format!("Cannot declare '{}': returned function '{}' not found.",
                                                                 &declaration.name, func_name)));
                    }
                },
            }
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" | "U8" | "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    let expr_heap_offset = result.heap_offset;
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
                    if custom_type_name == "Str" && expr_heap_offset > 0 {
                        context.scope_stack.frames.last_mut().unwrap()
                            .heap_index.insert(declaration.name.to_string(), expr_heap_offset);
                        return Ok(EvalResult::new(""))
                    }
                    EvalHeap::insert_primitive(context, &declaration.name, &value_type, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                _ => {
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
                    let custom_symbol = match context.scope_stack.lookup_symbol(custom_type_name) {
                        Some(sym) => sym,
                        None => return Err(e.lang_error(&context.path, "eval", &format!("Symbol '{}' not found in context", custom_type_name))),
                    };
                    if custom_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                        let result = eval_expr(context, inner_e)?;
                        if result.is_throw {
                            return Ok(result); // Propagate throw
                        }
                        let enum_expr_result_str = &result.value;
                        EvalHeap::insert_enum(context, &declaration.name, custom_type_name, enum_expr_result_str, e)?;

                    } else if custom_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        // Special case for instantiation
                        if matches!(inner_e.node_type, NodeType::FCall(_)) && inner_e.params.len() == 1 {
                            let first_param = inner_e.params.get(0).unwrap();
                            if let NodeType::Identifier(potentially_struct_name) = &first_param.node_type {
                                if first_param.params.is_empty() {
                                    if context.scope_stack.has_struct(potentially_struct_name) {
                                        insert_struct_instance(context, &declaration.name, custom_type_name, e)?;
                                        return Ok(EvalResult::new(""))
                                    }
                                }
                            }
                        }
                        // otherwise continue, it's a function that returns a struct
                        let result = eval_expr(context, inner_e)?;
                        if result.is_throw {
                            return Ok(result); // Propagate throw
                        }
                        let expr_result_str = result.value;

                        // Issue #159: Garbager handles clone() insertion for deep copy semantics
                        // Interpreter just binds offsets - both for temp return values and existing variables
                        // Bug #160: Deterministic dispatch - instance fields use get_field_offset
                        let offset = if EvalHeap::is_instance_field(context, &expr_result_str) {
                            context.get_field_offset(&expr_result_str)
                                .map_err(|err| e.lang_error(&context.path, "eval", &format!("Could not find heap index for '{}': {}", expr_result_str, err)))?
                        } else {
                            context.scope_stack.lookup_var(&expr_result_str)
                                .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("Could not find heap index for '{}'", expr_result_str)))?
                        };
                        context.scope_stack.frames.last_mut().unwrap().heap_index.insert(declaration.name.to_string(), offset);
                    } else {
                        return Err(e.error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}'. Only 'enum' and 'struct' custom types allowed.",
                                                            &declaration.name, value_type_to_str(&custom_symbol.value_type))))
                    }
                    return Ok(EvalResult::new(""))
                },
            }
        },
        ValueType::TType(TTypeDef::TFuncDef) => {
            // Issue #91: FuncDef metatype (placeholder for future first-class function definitions)
            context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_own: declaration.is_own, is_comptime_const: false });
            return Ok(EvalResult::new(""))
        },
        ValueType::TMulti(_) => {
            return Err(e.error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}'",
                                                &declaration.name, value_type_to_str(&declaration.value_type))))
        },
    }
}

fn eval_assignment(var_name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    // Issue #161: Check if the full name is a namespace mutable first
    // For field access (e.g., "v.x"), extract the base variable name
    let symbol_info = if var_name.contains('.') {
        if let Some(ns_sym) = context.scope_stack.lookup_symbol(var_name) {
            ns_sym // Full name is a registered symbol (namespace member)
        } else {
            let base_var_name = var_name.split('.').next().unwrap();
            match context.scope_stack.lookup_symbol(base_var_name) {
                Some(sym) => sym,
                None => {
                    return Err(e.lang_error(&context.path, "eval", &format!("Symbol '{}' not found in context", base_var_name)));
                }
            }
        }
    } else {
        match context.scope_stack.lookup_symbol(var_name) {
            Some(sym) => sym,
            None => {
                return Err(e.lang_error(&context.path, "eval", &format!("Symbol '{}' not found in context", var_name)));
            }
        }
    };
    if !symbol_info.is_mut && !symbol_info.is_own {
        return Err(e.lang_error(&context.path, "eval", &format!("in eval_assignment, while assigning to '{}': Assignments can only be to mut values. Offending expr: {:?}", var_name, e)));
    }
    if e.params.len() != 1 {
        return Err(e.lang_error(&context.path, "eval", &format!("in eval_assignment, while assigning to '{}': assignments must take exactly one value", var_name)));
    }

    let inner_e = e.params.get(0).unwrap();
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error(&context.path, "eval", &error_string));
        },
    };
    match value_type {
        ValueType::TCustom(s) if s == INFER_TYPE => {
            return Err(e.lang_error(&context.path, "eval", &format!("Cannot assign {}, type should already be inferred of type '{:?}'.", &var_name, &symbol_info.value_type)));
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" | "U8" | "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    let expr_heap_offset = result.heap_offset;
                    if custom_type_name == "Str" && expr_heap_offset > 0 {
                        let dest_offset = if var_name.contains('.') {
                            context.get_field_offset(var_name)?
                        } else {
                            context.scope_stack.lookup_var(var_name)
                                .ok_or_else(|| e.lang_error(&context.path, "eval",
                                    &format!("Could not find heap index for '{}'", var_name)))?
                        };
                        let type_size = context.get_type_size("Str")?;
                        let data = EvalHeap::g().get(expr_heap_offset, type_size).to_vec();
                        EvalHeap::g().set(dest_offset, &data)?;
                        return Ok(EvalResult::new(""));
                    }
                    EvalHeap::insert_primitive(context, var_name, &value_type, &expr_result_str, e)?;
                },
                _ => {
                    let custom_symbol_info = match context.scope_stack.lookup_symbol(custom_type_name) {
                        Some(symbol_info) => symbol_info,
                        None => return Err(inner_e.lang_error(&context.path, "eval", &format!("Unknown custom type '{}'", custom_type_name))),
                    };
                    match &custom_symbol_info.value_type {
                        ValueType::TType(TTypeDef::TEnumDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            EvalHeap::insert_enum(context, var_name, &custom_type_name, &expr_result_str, e)?;
                        },
                        ValueType::TType(TTypeDef::TStructDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            // Issue #159 Step 6: Replace copy_fields with clone + offset rebinding/memcpy
                            // Garbager inserts clone for identifiers; fresh constructors are already new.
                            if var_name.contains('.') {
                                // Field path: memcpy into field slot
                                let assign_src_offset = if EvalHeap::is_instance_field(context, &expr_result_str) {
                                    context.get_field_offset(&expr_result_str)?
                                } else {
                                    context.scope_stack.lookup_var(&expr_result_str)
                                        .ok_or_else(|| inner_e.lang_error(&context.path, "eval",
                                            &format!("Undefined variable '{}' for assignment to '{}'", expr_result_str, var_name)))?
                                };
                                let assign_dest_offset = context.get_field_offset(var_name)?;
                                let assign_type_size = context.get_type_size(custom_type_name)?;
                                let data = EvalHeap::g().get(assign_src_offset, assign_type_size).to_vec();
                                EvalHeap::g().set(assign_dest_offset, &data)?;
                            } else {
                                // Simple var: memcpy into existing slot
                                // Must use memcpy (not offset rebinding) because the variable
                                // may live in an outer scope frame. Offset rebinding would only
                                // update the current frame, leaving the outer frame stale.
                                let simple_assign_src_offset = if EvalHeap::is_instance_field(context, &expr_result_str) {
                                    context.get_field_offset(&expr_result_str)?
                                } else {
                                    context.scope_stack.lookup_var(&expr_result_str)
                                        .ok_or_else(|| inner_e.lang_error(&context.path, "eval",
                                            &format!("Could not find heap index for '{}'", expr_result_str)))?
                                };
                                let simple_assign_dest_offset = context.scope_stack.lookup_var(var_name)
                                    .ok_or_else(|| inner_e.lang_error(&context.path, "eval",
                                        &format!("Could not find heap index for '{}'", var_name)))?;
                                let simple_assign_type_size = context.get_type_size(custom_type_name)?;
                                let data = EvalHeap::g().get(simple_assign_src_offset, simple_assign_type_size).to_vec();
                                EvalHeap::g().set(simple_assign_dest_offset, &data)?;
                            }
                        },
                        other_value_type => {
                            return Err(inner_e.lang_error(&context.path, "eval", &format!("Cannot assign '{}' of custom type '{}' of value type '{}'.",
                                                                           &var_name, custom_type_name, value_type_to_str(&other_value_type))))
                        },
                    }
                },
            }
            return Ok(EvalResult::new(""))
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            return Err(e.todo_error(&context.path, "eval", &format!("Cannot assign '{}' of type '{}'", &var_name, value_type_to_str(&value_type))))
        },
        ValueType::TFunction(_) => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.scope_stack.declare_func(var_name.to_string(), func_def.clone());
                    Ok(EvalResult::new(""))
                },
                NodeType::Identifier(_) => {
                    // Issue #91: Assigning a function name to a FuncSig field
                    // e.g., h3.on_click = multiply
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result);
                    }
                    if var_name.contains('.') {
                        // Field path: store function name as Str at field offset
                        EvalHeap::insert_primitive(context, var_name,
                            &ValueType::TCustom("Str".to_string()),
                            &result.value, e)?;
                    } else {
                        // Simple var: re-register function
                        if let Some(func_def) = context.scope_stack.lookup_func(&result.value) {
                            let func_def_clone = func_def.clone();
                            context.scope_stack.declare_func(var_name.to_string(), func_def_clone);
                        } else {
                            return Err(e.lang_error(&context.path, "eval",
                                &format!("Function '{}' not found for assignment to '{}'", result.value, var_name)));
                        }
                    }
                    Ok(EvalResult::new(""))
                },
                _ => Err(e.lang_error(&context.path, "eval", &format!("Cannot assign '{}' to function type '{}'",
                                                       &var_name, value_type_to_str(&value_type)))),
            }
        },

        ValueType::TType(TTypeDef::TEnumDef) | ValueType::TType(TTypeDef::TFuncSig) | ValueType::TType(TTypeDef::TFuncDef) | ValueType::TMulti(_) => {
            Err(e.lang_error(&context.path, "eval", &format!("Cannot assign '{}' of type '{}'.", &var_name, value_type_to_str(&value_type))))
        },
    }
}

fn eval_identifier_expr_struct_member(name: &str, inner_name: &str, context: &mut Context, inner_e: &Expr, member_decl: &Declaration) -> Result<EvalResult, String> {
    return match member_decl.value_type {
        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = EvalHeap::get_i64(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "U8" => {
                    let result = EvalHeap::get_u8(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "Str" => {
                    let result = string_from_context(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                _ => Ok(EvalResult::new(&format!("{}.{}", name, inner_name))),
            }
        },
        _ => Err(inner_e.lang_error(&context.path, "eval", &format!("struct '{}' has no const (static) member '{}' of struct value type '{}'",
                                                     name, inner_name, value_type_to_str(&member_decl.value_type)))),
    }
}

fn eval_identifier_expr_struct(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let struct_def = match context.scope_stack.lookup_struct(name) {
        Some(def) => def.clone(),  // Clone to avoid borrow checker issues
        None => return Err(e.lang_error(&context.path, "eval", &format!("Struct '{}' not found in context", name))),
    };
    // Issue #105: bare struct name reference (e.g., `return TemplatedPtr` in a macro)
    if e.params.is_empty() {
        return Ok(EvalResult::new(name));
    }
    let inner_e = e.params.get(0).unwrap();
    match &inner_e.node_type {
        NodeType::Identifier(inner_name) => {
            // Issue #161: Check if this is a namespace member (from struct_def.ns)
            let ns_member = struct_def.ns.members.iter().find(|m| m.name == *inner_name);
            if let Some(ns_decl) = ns_member {
                let full_name = format!("{}.{}", name, inner_name);
                match &ns_decl.value_type {
                    ValueType::TCustom(ref type_name) => {
                        match type_name.as_str() {
                            "I64" => {
                                let val = EvalHeap::get_i64(context, &full_name, inner_e)?;
                                return Ok(EvalResult::new(&val.to_string()));
                            },
                            "U8" => {
                                let val = EvalHeap::get_u8(context, &full_name, inner_e)?;
                                return Ok(EvalResult::new(&val.to_string()));
                            },
                            "Str" => {
                                let val = string_from_context(context, &full_name, inner_e)?;
                                return Ok(EvalResult::new(&val));
                            },
                            _ => return Ok(EvalResult::new(&full_name)),
                        }
                    },
                    _ => return Ok(EvalResult::new(&full_name)),
                }
            }
            let member_decl = struct_def.get_member_or_err(inner_name, name, &context.path, e)?;
            return eval_identifier_expr_struct_member(name, inner_name, context, inner_e, &member_decl);
        },
        _ => {
            return Err(e.lang_error(&context.path, "eval", &format!("identifier '{}' should only have identifiers inside.", name)));
        },
    }
}

fn eval_custom_expr(e: &Expr, context: &mut Context, name: &str, custom_type_name: &str) -> Result<EvalResult, String> {
    let custom_symbol = match context.scope_stack.lookup_symbol(custom_type_name) {
        Some(sym) => sym,
        None => return Err(e.lang_error(&context.path, "eval", &format!("Argument '{}' is of undefined type {}.", name, custom_type_name))),
    };
    match custom_symbol.value_type {
        ValueType::TType(TTypeDef::TEnumDef) => {
            // If name equals the type name, this is a reference to the type itself, not a variable
            // This shouldn't happen in normal code, but handle it gracefully
            if name == custom_type_name {
                return Err(e.lang_error(&context.path, "eval", &format!("Cannot use enum type '{}' as a value", name)));
            }
            let enum_val = EvalHeap::get_enum(context, name, e)?;
            // Set temp_enum_payload so that if this enum is assigned to another variable,
            // the payload will be preserved
            if enum_val.payload.is_some() && enum_val.payload_type.is_some() {
                context.temp_enum_payload = Some(EnumPayload { data: enum_val.payload.clone().unwrap(), value_type: enum_val.payload_type.clone().unwrap() });
            }
            return Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name)))
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            if e.params.len() == 0 {
                return Ok(EvalResult::new(name));
            }

            let mut current_name = name.to_string();
            let mut current_type = ValueType::TCustom(custom_type_name.to_string());

            for inner_e in &e.params {
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        match current_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                return Err(inner_e.todo_error(&context.path, "eval", &format!("'{}': StructDef cannot be a field yet", current_name)));
                            },
                            ValueType::TCustom(ref custom_type_name) => {
                                if let Some(custom_symbol) = context.scope_stack.lookup_symbol(custom_type_name) {
                                    match custom_symbol.value_type {
                                        ValueType::TType(TTypeDef::TStructDef) => {
                                            let struct_def = match context.scope_stack.lookup_struct(custom_type_name) {
                                                Some(def) => def,
                                                None => return Err(e.lang_error(&context.path, "eval", &format!("Struct '{}' not found in context", custom_type_name))),
                                            };
                                            let member_decl = struct_def.get_member_or_err(inner_name, custom_type_name, &context.path, inner_e)?;
                                            current_type = member_decl.value_type.clone();
                                            current_name = format!("{}.{}", current_name, inner_name);
                                        },
                                        ValueType::TType(TTypeDef::TEnumDef) => {
                                            return Err(inner_e.lang_error(&context.path, "eval", &format!("Enum '{}' does not support nested members", current_name)));
                                        },
                                        _ => return Err(inner_e.lang_error(&context.path, "eval", "Custom types cannot have nested members")),
                                    }
                                } else {
                                    return Err(inner_e.lang_error(&context.path, "eval", &format!("Custom type '{}' not found in symbols", custom_type_name)));
                                }
                            },
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                return Err(inner_e.lang_error(&context.path, "eval", &format!("Enum '{}' does not support nested members", current_name)));
                            },
                            _ => return Err(inner_e.lang_error(&context.path, "eval", &format!("Unexpected type for '{}', cannot access member '{}'", current_name, inner_name))),
                        }
                    },
                    _ => return Err(inner_e.lang_error(&context.path, "eval", &format!("Expected identifier, found {:?}", inner_e.node_type))),
                }
            }

            let inner_e = match e.params.last() {
                Some(expr) => expr,
                None => return Err(e.lang_error(&context.path, "eval", "eval_custom_expr: Expected at least one parameter")),
            };
            match current_type {
                ValueType::TCustom(ref custom_type_name) => {
                    match custom_type_name.as_str() {
                        "I64" => match EvalHeap::get_i64(context, &current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "U8" => match EvalHeap::get_u8(context, &current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "Str" => match string_from_context(context, &current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        _ => {
                            let custom_type_name = &value_type_to_str(&current_type);
                            let custom_symbol_info = match context.scope_stack.lookup_symbol(custom_type_name) {
                                Some(symbol_info) => symbol_info,
                                None => return Err(inner_e.lang_error(&context.path, "eval", &format!("Unknown custom type '{}'", custom_type_name))),
                            };
                            match &custom_symbol_info.value_type {
                                ValueType::TType(TTypeDef::TEnumDef) => {
                                    let enum_val = EvalHeap::get_enum(context, &current_name, inner_e)?;
                                    // Set temp_enum_payload so that if this enum is assigned to another variable,
                                    // the payload will be preserved
                                    if enum_val.payload.is_some() && enum_val.payload_type.is_some() {
                                        context.temp_enum_payload = Some(EnumPayload { data: enum_val.payload.clone().unwrap(), value_type: enum_val.payload_type.clone().unwrap() });
                                    }
                                    return Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name)))
                                },
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    return Ok(EvalResult::new(&current_name))
                                },
                                // Issue #91: FuncSig fields store function names as Str
                                ValueType::TType(TTypeDef::TFuncSig) => {
                                    let func_name = string_from_context(context, &current_name, inner_e)?;
                                    return Ok(EvalResult::new(&func_name))
                                },
                                _ => Err(inner_e.todo_error(&context.path, "eval", &format!("Cannot access '{}'. Fields of custom type '{}' not implemented", current_name, custom_type_name))),
                            }
                        },
                    }
                },
                _ => Err(e.lang_error(&context.path, "eval", &format!("Invalid type for '{}'.", current_name))),
            }
        },
        // Issue #91: FuncSig type - return function name
        ValueType::TType(TTypeDef::TFuncSig) => {
            if e.params.len() == 0 {
                // FuncSig variable - the function name is stored in scope_stack.funcs
                // (parameters are registered as funcs, not as heap data)
                if let Some(fd) = context.scope_stack.lookup_func(name) {
                    // Re-register in parent frame so it survives frame pop after return
                    let fd_clone = fd.clone();
                    let temp_name = format!("_fptr_{}", name);
                    if context.scope_stack.frames.len() >= 2 {
                        let parent_idx = context.scope_stack.frames.len() - 2;
                        context.scope_stack.frames[parent_idx].funcs.insert(temp_name.clone(), fd_clone);
                    }
                    return Ok(EvalResult::new(&temp_name));
                }
                // Could also be a struct field read as Str
                let func_name = string_from_context(context, name, e)?;
                return Ok(EvalResult::new(&func_name));
            }
            return Err(e.lang_error(&context.path, "eval", &format!("FuncSig type '{}' does not support field access", name)));
        },
        _ => Err(e.lang_error(&context.path, "eval", &format!("'{}' of type: '{}': custom types are supposed to be struct or enum, found '{}'.", name, custom_type_name, value_type_to_str(&custom_symbol.value_type)))),
    }
}

fn eval_identifier_expr(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    // Bug #32 fix: Handle field access on expression results
    // When name is "_" and params[0] is an FCall, evaluate that first,
    // then params[1..] are field access on its result
    if name == "_" && !e.params.is_empty() {
        // Evaluate the base expression (params[0])
        let base_expr = e.params.get(0).unwrap();
        let base_result = eval_expr(context, base_expr)?;
        if base_result.is_throw {
            return Ok(base_result);
        }

        // Get the type of the result
        let base_type = get_value_type(context, base_expr)?;

        // Now we have the result stored in heap - access the fields
        // The result.value contains the identifier for the result
        let result_name = base_result.value.clone();

        // If there's only one param (the FCall), just return the result
        if e.params.len() == 1 {
            return Ok(base_result);
        }

        // Build the full field path by traversing params[1..]
        let mut current_name = result_name.clone();
        for i in 1..e.params.len() {
            let field_expr = e.params.get(i).unwrap();
            if let NodeType::Identifier(field_name) = &field_expr.node_type {
                current_name = format!("{}.{}", current_name, field_name);
            } else {
                return Err(e.error(&context.path, "eval", "Expected identifier in field access chain"));
            }
        }

        // Now evaluate the final field access using the built path
        // We need to determine the type of the final field to return it properly
        match base_type {
            ValueType::TCustom(ref type_name) => {
                // Get the struct definition to traverse the field chain
                let mut current_type = type_name.clone();
                for i in 1..e.params.len() {
                    let field_expr = e.params.get(i).unwrap();
                    if let NodeType::Identifier(field_name) = &field_expr.node_type {
                        if let Some(struct_def) = context.scope_stack.lookup_struct(&current_type) {
                            if let Some(member) = struct_def.get_member(field_name) {
                                match &member.value_type {
                                    ValueType::TCustom(inner_type) => {
                                        current_type = inner_type.clone();
                                    },
                                    _ => {
                                        return Err(e.error(&context.path, "eval", &format!("Unexpected field type for '{}'", field_name)));
                                    }
                                }
                            } else {
                                return Err(e.error(&context.path, "eval", &format!("Field '{}' not found in struct '{}'", field_name, current_type)));
                            }
                        } else {
                            return Err(e.error(&context.path, "eval", &format!("Struct '{}' not found", current_type)));
                        }
                    }
                }

                // Now get the value based on the final type
                match current_type.as_str() {
                    "I64" => {
                        let val = EvalHeap::get_i64(context, &current_name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "U8" => {
                        let val = EvalHeap::get_u8(context, &current_name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Str" => {
                        let val = string_from_context(context, &current_name, e)?;
                        return Ok(EvalResult::new(&val));
                    },
                    _ => {
                        // Bug #157: Check if this is an enum type - need to read actual value from heap
                        if context.scope_stack.has_enum(&current_type) {
                            let enum_val = EvalHeap::get_enum(context, &current_name, e)?;
                            return Ok(EvalResult::new(&format!("{}.{}", enum_val.enum_type, enum_val.enum_name)));
                        }
                        // Return the field path for struct fields
                        return Ok(EvalResult::new(&current_name));
                    }
                }
            },
            _ => {
                return Err(e.error(&context.path, "eval", &format!("Cannot access fields on non-struct type")));
            }
        }
    }

    match context.scope_stack.lookup_symbol(name) {
        Some(symbol_info) => match &symbol_info.value_type {
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                return Ok(EvalResult::new(name));
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                // Issue #106: bare enum name reference (e.g., `return TemplatedOption` in a macro)
                if e.params.is_empty() {
                    return Ok(EvalResult::new(name));
                }
                let inner_e = e.params.get(0).unwrap();
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        // Issue #161: Check if this is a namespace member (from enum_def.ns)
                        if let Some(enum_def) = context.scope_stack.lookup_enum(name) {
                            let ns_member = enum_def.ns.members.iter().find(|m| m.name == *inner_name);
                            if let Some(ns_decl) = ns_member {
                                let full_name = format!("{}.{}", name, inner_name);
                                match &ns_decl.value_type {
                                    ValueType::TCustom(ref type_name) => {
                                        match type_name.as_str() {
                                            "I64" => {
                                                let val = EvalHeap::get_i64(context, &full_name, inner_e)?;
                                                return Ok(EvalResult::new(&val.to_string()));
                                            },
                                            "U8" => {
                                                let val = EvalHeap::get_u8(context, &full_name, inner_e)?;
                                                return Ok(EvalResult::new(&val.to_string()));
                                            },
                                            "Str" => {
                                                let val = string_from_context(context, &full_name, inner_e)?;
                                                return Ok(EvalResult::new(&val));
                                            },
                                            _ => return Ok(EvalResult::new(&full_name)),
                                        }
                                    },
                                    _ => return Ok(EvalResult::new(&full_name)),
                                }
                            }
                        }
                        // Enum variant
                        let full_name = format!("{}.{}", name, inner_name);
                        return Ok(EvalResult::new(&full_name));
                    },
                    _ => {
                        return Err(e.lang_error(&context.path, "eval", &format!("identifier '{}' should only have identifiers inside.", name)));
                    },
                }
            },
            ValueType::TType(TTypeDef::TStructDef) => {
                return eval_identifier_expr_struct(name, context, e)
            }
            ValueType::TCustom(s) if s == INFER_TYPE => {
                return Err(e.lang_error(&context.path, "eval", &format!("Can't infer the type of identifier '{}'.", name)));
            },
            ValueType::TCustom(ref custom_type_name) => {
                // Clone custom_type_name to avoid borrow checker issues
                let custom_type_name_clone = custom_type_name.clone();
                match custom_type_name_clone.as_str() {
                    "I64" => {
                        let val = EvalHeap::get_i64(context, name, e)?;
                        return Ok(EvalResult::new(&val.to_string()))
                    },
                    "U8" => {
                        let val = EvalHeap::get_u8(context, name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Str" => {
                        if e.params.len() == 0 {
                            let val = string_from_context(context, name, e)?;
                            let mut result = EvalResult::new(&val);
                            result.heap_offset = context.scope_stack.lookup_var(name).unwrap_or(0);
                            return Ok(result);
                        }
                        return eval_custom_expr(e, context, name, &custom_type_name_clone);
                    },
                    _ => {
                        return eval_custom_expr(e, context, name, &custom_type_name_clone);
                    },
                }
            },
            _ => {
                return Err(e.todo_error(&context.path, "eval", &format!("Can't use identifier '{}'. Type {:?} not supported yet.", name, symbol_info.value_type)));
            },
        },
        None => {
            return Err(e.lang_error(&context.path, "eval", &format!("Undefined symbol '{}'. This should have been caught in the compile phase.", name)));
        },
    }
}

pub fn eval_body(mut context: &mut Context, statements: &Vec<Expr>) -> Result<EvalResult, String> {
    let mut i = 0;
    let mut pending_throw: Option<EvalResult> = None;

    while i < statements.len() {
        let stmt = &statements[i];

        if let Some(throw_result) = &pending_throw {
            if let NodeType::Catch = stmt.node_type {
                if stmt.params.len() == 3 {
                    // params[0]: error variable name (e.g., "err")
                    // params[1]: error type (e.g., "AllocError")
                    // params[2]: body
                    let var_expr = stmt.params.get(0).unwrap();
                    let var_name = match &var_expr.node_type {
                        NodeType::Identifier(name) => name,
                        _ => return Err(stmt.lang_error(&context.path, "eval", "Catch variable must be an identifier")),
                    };
                    let type_expr = stmt.params.get(1).unwrap();
                    let type_name = match &type_expr.node_type {
                        NodeType::Identifier(name) => name,
                        _ => return Err(stmt.lang_error(&context.path, "eval", "Catch type must be an identifier")),
                    };
                    let thrown_type = &throw_result.thrown_type;
                    if !thrown_type.is_empty() {
                        if type_name == thrown_type {
                            // Bind the error variable to the caught error value
                            context.scope_stack.declare_symbol(var_name.to_string(), SymbolInfo {
                                value_type: ValueType::TCustom(thrown_type.clone()),
                                is_mut: false,
                                
                                is_own: false,
                                is_comptime_const: false,
                            });

                            // Map instance fields for the error variable
                            // First try to find the heap index for proper field mapping
                            if let Some(offset) = context.scope_stack.lookup_var(&throw_result.value) {
                                context.scope_stack.frames.last_mut().unwrap().heap_index.insert(var_name.to_string(), offset);

                                // Copy symbol mappings for all fields
                                let source_prefix = format!("{}.", &throw_result.value);
                                let dest_prefix = format!("{}.", var_name);
                                let symbol_keys_to_copy = context.scope_stack.get_symbols_with_prefix(&source_prefix);
                                for sym_src_key in symbol_keys_to_copy {
                                    if let Some(src_symbol) = context.scope_stack.lookup_symbol(&sym_src_key) {
                                        let sym_dest_key = sym_src_key.replacen(&source_prefix, &dest_prefix, 1);
                                        context.scope_stack.declare_symbol(sym_dest_key, src_symbol.clone());
                                    }
                                }
                            } else {
                                // Fallback: try to map fields from the thrown value or type
                                // This happens when throwing inline struct constructors or when heap_index lookup fails

                                // Special handling for Str: when throwing a string literal, we need to create a proper Str struct
                                if thrown_type == "Str" {
                                    // The thrown value is the actual string content, not a struct instance name
                                    // Create a proper Str struct for the catch variable
                                    EvalHeap::insert_string(context, var_name, &throw_result.value, stmt)?;
                                } else if let Some(struct_def) = context.scope_stack.lookup_struct(thrown_type) {
                                    let source_name = &throw_result.value;
                                    // Clone the members to avoid borrow conflict
                                    let members = struct_def.members.clone();

                                    // Register the base variable first
                                    if let Some(base_offset) = context.scope_stack.lookup_var(source_name) {
                                        context.scope_stack.frames.last_mut().unwrap().heap_index.insert(
                                            var_name.to_string(),
                                            base_offset
                                        );
                                    }

                                    for field_decl in &members {
                                        let src_instance_field = format!("{}.{}", source_name, field_decl.name);
                                        let src_type_field = format!("{}.{}", thrown_type, field_decl.name);
                                        let dst_field = format!("{}.{}", var_name, field_decl.name);

                                        // Add symbol for the field
                                        context.scope_stack.declare_symbol(
                                            dst_field.clone(),
                                            SymbolInfo {
                                                value_type: field_decl.value_type.clone(),
                                                is_mut: false,
                                                
                                                is_own: false,
                                                is_comptime_const: false,
                                            },
                                        );

                                        // Copy heap_index entry for the field
                                        // Try instance field first, then fall back to type field
                                        if let Some(offset) = context.scope_stack.lookup_var(&src_instance_field) {
                                            context.scope_stack.frames.last_mut().unwrap().heap_index.insert(dst_field.clone(), offset);
                                        } else if let Some(offset) = context.scope_stack.lookup_var(&src_type_field) {
                                            context.scope_stack.frames.last_mut().unwrap().heap_index.insert(dst_field.clone(), offset);
                                        }
                                    }
                                }
                            }

                            let body_expr = stmt.params.get(2).unwrap();
                            let result = eval_body(&mut context, &body_expr.params)?;

                            // Clean up the error variable binding after the catch block
                            context.scope_stack.remove_symbol(var_name);
                            context.scope_stack.remove_var(var_name);
                            // Also remove the field mappings
                            if let Some(struct_def) = context.scope_stack.lookup_struct(thrown_type) {
                                // Collect field names to avoid borrow conflict
                                let field_names: Vec<String> = struct_def.members.iter().map(|decl| decl.name.clone()).collect();
                                for field_name in field_names {
                                    let combined_name = format!("{}.{}", var_name, field_name);
                                    context.scope_stack.remove_symbol(&combined_name);
                                    context.scope_stack.remove_var(&combined_name);
                                    // Nested struct fields are handled by subsequent iterations
                                }
                            }

                            if result.is_return || result.is_break || result.is_continue {
                                return Ok(result);
                            } else if result.is_throw {
                                pending_throw = Some(result);
                            } else {
                                pending_throw = None;
                            }
                        }
                    }
                }
            }
        } else {
            // If no pending throw, ignore catch statements
            if NodeType::Catch != stmt.node_type {
                let result = eval_expr(&mut context, stmt)?;
                if result.is_return || result.is_break || result.is_continue {
                    return Ok(result);
                } else if result.is_throw {
                    pending_throw = Some(result);
                }
            }
        }

        i += 1;
    }

    if let Some(final_throw) = pending_throw {
        return Ok(final_throw);
    }

    Ok(EvalResult::new(""))
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &FuncDef, name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    // TODO REFACTOR: Replace context.clone() with scope push/pop
    // When refactoring:
    // 1. Replace line 2523-2524 with: let saved_path = context.push_function_scope(&func_def.source_path);
    // 2. Replace all `function_context` references with `context`
    // 3. Add context.pop_function_scope(saved_path)? before EACH return statement
    // 4. Update insert_i64/insert_u8 to check lookup_var() and update in-place for existing variables
    //
    // Return paths requiring cleanup (search for "CLEANUP SITE"):
    // - Line 2540: Propagate throw from variadic args
    // - Line 2621: Propagate throw from argument evaluation
    // - Line 3048: Propagate throw from function body
    // - Line 3136: Return struct instance
    // - Line 3148: Return enum instance (constructor)
    // - Line 3162: Return enum instance (variable)
    // - Line 3175: Return normal value
    // Plus ~15 error returns that also need cleanup

    let mut function_frame = ScopeFrame {
        heap_index: std::collections::HashMap::new(),
        symbols: std::collections::HashMap::new(),
        funcs: std::collections::HashMap::new(),
        enums: std::collections::HashMap::new(),
        structs: std::collections::HashMap::new(),
        scope_type: ScopeType::Function,
    };
    let saved_path = context.path.clone();
    validate_func_arg_count(&context.path, e, name, func_def)?;

    let mut param_index = 1;
    struct MutArgEntry {
        arg_name: String,
        source_name: String,
        value_type: ValueType,
    }
    let mut mut_args: Vec<MutArgEntry> = Vec::new();
    let mut pass_by_ref_params: std::collections::HashSet<String> = std::collections::HashSet::new(); // Track which params used pass-by-ref
    let mut params_consumed = false;

    for arg in &func_def.sig.args {
        if !params_consumed {
        function_frame.symbols.insert(arg.name.to_string(), SymbolInfo {value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_own: arg.is_own, is_comptime_const: false });
        match &arg.value_type {
            ValueType::TMulti(ref multi_value_type) => {
                let mut values = Vec::new();
                for vi in param_index..e.params.len() {
                    let expr = e.params.get(vi).unwrap();
                    let result = eval_expr(context, expr)?;
                    if result.is_throw {
                        return Ok(result); // CLEANUP SITE 1: Propagate throw from variadic args
                    }
                    let val = result.value;
                    values.push(val);
                }

                // All array types now use the generic Array
                let array_type_name = "Array".to_string();

                function_frame.symbols.insert(arg.name.to_string(), SymbolInfo {
                    value_type: ValueType::TCustom(array_type_name),
                    is_mut: arg.is_mut,
                    
                    is_own: arg.is_own,
                    is_comptime_const: false,
                });
                EvalHeap::insert_array_into_frame(context, &mut function_frame, &arg.name, &multi_value_type, &values, e)?;

                // We've consumed all remaining parameters, break out of loop
                params_consumed = true;
            },
            ValueType::TCustom(ref custom_type_name) => {
                let current_arg = e.params.get(param_index).unwrap();

                // Issue #91: Handle function-typed parameters
                // If parameter type is a FuncSig, the argument is a function name -
                // register the function def in the callee frame under the parameter name
                if let Some(type_sym) = context.scope_stack.lookup_symbol(custom_type_name) {
                    if type_sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                        if let NodeType::Identifier(_) = &current_arg.node_type {
                            let combined_arg_name = get_combined_name(&context.path, current_arg)?;
                            if let Some(arg_func_def) = context.scope_stack.lookup_func(&combined_arg_name) {
                                function_frame.funcs.insert(arg.name.clone(), arg_func_def.clone());
                                param_index += 1;
                                continue;
                            }
                        }
                        // Issue #91: Anonymous inline function - evaluate to get temp name
                        if let NodeType::FuncDef(_) = &current_arg.node_type {
                            let anon_result = eval_expr(context, current_arg)?;
                            if let Some(anon_fd) = context.scope_stack.lookup_func(&anon_result.value) {
                                function_frame.funcs.insert(arg.name.clone(), anon_fd.clone());
                                param_index += 1;
                                continue;
                            }
                        }
                        return Err(e.lang_error(&context.path, "eval",
                            &format!("Expected function name for parameter '{}'", arg.name)));
                    }
                }

                // Special handling for Dynamic parameters: don't evaluate, just copy the value
                // When a type like I64, U8, Str is passed to a Dynamic/Type parameter,
                // store the type name as a string so size_of(T) and type_as_str(T) can use it
                if custom_type_name == "Dynamic" || custom_type_name == "Type" {
                    if let NodeType::Identifier(id_name) = &current_arg.node_type {
                        // Bug #37 fix: Only treat as type reference if there are NO params.
                        // An enum constructor like SimpleColor.Green has params (Green),
                        // so it should fall through to normal evaluation, not be treated as a type.
                        if current_arg.params.is_empty() {
                            if let Some(sym) = context.scope_stack.lookup_symbol(id_name) {
                                if let ValueType::TType(_) = &sym.value_type {
                                    // This is a type identifier - store the type name as a string
                                    function_frame.symbols.insert(arg.name.clone(), SymbolInfo {
                                        value_type: ValueType::TCustom("Str".to_string()),
                                        is_mut: false,
                                        
                                        is_own: false,
                                        is_comptime_const: false,
                                    });
                                    EvalHeap::insert_string_into_frame(context, &mut function_frame, &arg.name, id_name, e)?;
                                    param_index += 1;
                                    continue; // Skip eval_expr for this parameter
                                }
                            }
                        }
                    }
                    // If it's not a type identifier, fall through to normal evaluation
                }

                // If this is an enum argument and current_arg is an identifier, get the enum value to preserve payload
                let enum_payload_backup: Option<EnumPayload> = if let NodeType::Identifier(id_name) = &current_arg.node_type {
                    if let Some(sym) = context.scope_stack.lookup_symbol(id_name) {
                        if let ValueType::TCustom(arg_type_name) = &sym.value_type {
                            if let Some(type_sym) = context.scope_stack.lookup_symbol(arg_type_name) {
                                if type_sym.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                    // This is an enum variable, get its value to preserve payload
                                    match EvalHeap::get_enum(context, id_name, e) {
                                        Ok(enum_val) => {
                                            if enum_val.payload.is_some() && enum_val.payload_type.is_some() {
                                                Some(EnumPayload { data: enum_val.payload.clone().unwrap(), value_type: enum_val.payload_type.clone().unwrap() })
                                            } else {
                                                None
                                            }
                                        },
                                        Err(_) => None,
                                    }
                                } else {
                                    None
                                }
                            } else {
                                None
                            }
                        } else {
                            None
                        }
                    } else {
                        None
                    }
                } else {
                    None
                };

                let result = eval_expr(context, &current_arg)?;
                if result.is_throw {
                    return Ok(result); // CLEANUP SITE 2: Propagate throw from argument evaluation
                }
                let result_heap_offset = result.heap_offset;
                let result_str = result.value;

                // Restore enum payload if we saved it
                if let Some(payload_data) = enum_payload_backup {
                    context.temp_enum_payload = Some(payload_data);
                }

                // Resolve Dynamic/Type to actual type first
                // Note: Use resolved_type_name (not shadowing) to match TIL translation
                let resolved_type_name = match custom_type_name.as_str() {
                    "Dynamic" | "Type" => value_type_to_str(&get_value_type(context, &current_arg)?),
                    _ => custom_type_name.clone(),
                };

                // Create resolved ValueType for the parameter
                let resolved_value_type = ValueType::TCustom(resolved_type_name.clone());

                // Now push to mut_args with the resolved type
                if arg.is_mut {
                    match &current_arg.node_type {
                        NodeType::Identifier(id_) => {
                            // Bug #10 fix: Build full path for field access
                            let full_id = if current_arg.params.len() > 0 {
                                let mut full_path = id_.clone();
                                for param in &current_arg.params {
                                    match &param.node_type {
                                        NodeType::Identifier(field_name) => {
                                            full_path.push('.');
                                            full_path.push_str(field_name);
                                        },
                                        _ => {
                                            return Err(e.lang_error(&context.path, "eval", "Field access must use identifiers"));
                                        }
                                    }
                                }
                                full_path
                            } else {
                                id_.clone()
                            };
                            mut_args.push(MutArgEntry { arg_name: arg.name.clone(), source_name: full_id, value_type: ValueType::TCustom(resolved_type_name.clone()) });
                        },
                        _ => {
                            return Err(e.lang_error(&context.path, "eval", "mut arguments must be passed as identifiers or field access"))
                        }
                    }
                }

                // Handle ownership transfer for 'own' parameters
                // Like const/mut: identifiers (including field access) by reference, expressions copied
                if arg.is_own {
                    // Only handle identifiers here (variables and field access)
                    // Expressions will fall through and be copied
                    if let NodeType::Identifier(source_var) = &current_arg.node_type {
                        // Transfer heap offset from caller to function frame
                        if let Some(offset) = context.scope_stack.lookup_var(source_var) {
                            function_frame.heap_index.insert(arg.name.clone(), offset);

                            // Transfer symbol info for fields
                            let own_prefix = format!("{}.", source_var);
                            let symbol_keys_to_transfer = context.scope_stack.get_symbols_with_prefix(&own_prefix);
                            for transfer_key in &symbol_keys_to_transfer {
                                if let Some(field_sym) = context.scope_stack.lookup_symbol(transfer_key) {
                                    let own_new_key = transfer_key.replace(source_var, &arg.name);
                                    function_frame.symbols.insert(own_new_key, field_sym.clone());
                                }
                            }

                            // Remove from caller's context (ownership transferred)
                            context.scope_stack.remove_var(source_var);
                            context.scope_stack.remove_symbol(source_var);
                            for remove_key in &symbol_keys_to_transfer {
                                context.scope_stack.remove_symbol(remove_key);
                            }

                            param_index += 1;
                            continue; // Skip normal allocation logic
                        }
                    }
                    // If not an identifier, fall through to copy like const/mut do
                }

                // Phase 3: Pass-by-reference for non-copy, non-own, non-Type parameters
                // If argument is a variable (identifier), share heap offset instead of copying
                // Note: Type parameters need copy semantics for type name storage, so skip them
                // Note: Dynamic parameters NOW use pass-by-reference (including mut Dynamic)
                // Note: own parameters are handled separately above and should not fall through here
                // Works for ALL types thanks to field offset refactoring (commit 2b9d08d):
                // - Only base offset stored in heap_index
                // - Field offsets calculated dynamically from struct definitions
                // - Inline memory layout means sharing base offset shares all fields
                if !arg.is_own && resolved_type_name != "Type" {
                    if let NodeType::Identifier(source_var) = &current_arg.node_type {
                        // Only share offset for SIMPLE identifiers (no field access, no params)
                        // Field access like s.cap is also an Identifier node but has params
                        if current_arg.params.is_empty() {
                            // Share heap offset from caller context (zero-copy pass-by-reference)
                            if let Some(offset) = context.scope_stack.lookup_var(source_var) {
                            // Create symbol info for parameter using the resolved type
                            let param_symbol = SymbolInfo {
                                value_type: resolved_value_type.clone(),
                                is_mut: arg.is_mut,
                                
                                is_own: arg.is_own,
                                is_comptime_const: false,
                            };
                            function_frame.symbols.insert(arg.name.clone(), param_symbol);
                            function_frame.heap_index.insert(arg.name.clone(), offset);

                            // Copy symbol entries for fields from ALL frames to callee
                            let ref_prefix = format!("{}.", source_var);
                            let ref_replacement_prefix = format!("{}.", arg.name);
                            let mut ref_field_symbols_to_copy: Vec<SymbolEntry> = Vec::new();
                            for ref_caller_frame in context.scope_stack.frames.iter() {
                                for (ref_skey, ref_svalue) in ref_caller_frame.symbols.iter() {
                                    if ref_skey.starts_with(&ref_prefix) {
                                        let ref_new_skey = ref_skey.replacen(&ref_prefix, &ref_replacement_prefix, 1);
                                        ref_field_symbols_to_copy.push(SymbolEntry { name: ref_new_skey, info: ref_svalue.clone() });
                                    }
                                }
                            }
                            for ref_entry in ref_field_symbols_to_copy {
                                function_frame.symbols.insert(ref_entry.name, ref_entry.info);
                            }

                            // Track that this parameter was passed by reference
                            pass_by_ref_params.insert(arg.name.clone());

                            param_index += 1;
                            continue; // Skip allocation logic - we're sharing the offset
                            }
                        }
                    }
                    // If not an identifier or not found, fall through to normal allocation
                    // (expressions must allocate fresh memory)
                }

                match resolved_type_name.as_str() {
                    "I64" => {
                        EvalHeap::insert_i64_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    "U8" => {
                        EvalHeap::insert_u8_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    "Str" => {
                        if result_heap_offset > 0 {
                            function_frame.heap_index.insert(arg.name.clone(), result_heap_offset);
                        } else {
                            EvalHeap::insert_string_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                        }
                    },
                    // Issue #91: Function pointers stored as Str (function name)
                    "func" | "proc" | "ext_func" | "ext_proc" | "macro" => {
                        EvalHeap::insert_string_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    _ => {
                        let custom_symbol = context.scope_stack.lookup_symbol(&resolved_type_name).ok_or_else(|| {
                            return e.lang_error(&context.path, "eval", &format!( "Undefined symbol for custom type '{}'", resolved_type_name))
                        })?;
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                // Transfer payload from outer context if present (temp_enum_payload already on context)
                                EvalHeap::insert_enum_into_frame(context, &mut function_frame, &arg.name, &resolved_type_name, &result_str, e)?;
                            },
                            ValueType::TType(TTypeDef::TStructDef) => {
                                // Bug #10 fix: Handle field access chains like s.items
                                let source_id = if current_arg.params.len() > 0 {
                                    // Build the full path for field access: "s.items"
                                    match &current_arg.node_type {
                                        NodeType::Identifier(base_id) => {
                                            let mut full_path = base_id.clone();
                                            for param in &current_arg.params {
                                                match &param.node_type {
                                                    NodeType::Identifier(field_name) => {
                                                        full_path.push('.');
                                                        full_path.push_str(field_name);
                                                    },
                                                    _ => {
                                                        return Err(e.lang_error(&context.path, "eval", "Field access must use identifiers"));
                                                    }
                                                }
                                            }
                                            full_path
                                        },
                                        _ => {
                                            // For non-identifier expressions (like Vec.new(Expr)),
                                            // use the result_str which contains the allocated result
                                            result_str.clone()
                                        }
                                    }
                                } else {
                                    match &current_arg.node_type {
                                        NodeType::Identifier(id_) => id_.clone(),
                                        _ => {
                                            // For non-identifier expressions (like Vec.new(Expr)),
                                            // use the result_str which contains the allocated result
                                            result_str.clone()
                                        }
                                    }
                                };

                                match &current_arg.node_type {
                                    NodeType::Identifier(_id_) => {
                                        let id_ = &source_id; // Use the full path we calculated

                                        // For pass-by-reference (non-copy, non-own, non-Type), just share the offset
                                        if !arg.is_own && resolved_type_name != "Type" {
                                            let src_offset = if let Some(offset) = context.scope_stack.lookup_var(id_) {
                                                offset
                                            } else if id_.contains('.') {
                                                // Field path - calculate offset dynamically
                                                context.get_field_offset( id_)
                                                    .map_err(|err| e.lang_error(&context.path, "eval", &format!("Pass-by-reference: {}", err)))?
                                            } else {
                                                return Err(e.lang_error(&context.path, "eval", &format!("Source struct '{}' not found in caller context heap_index", id_)))
                                            };

                                            // Create symbol for parameter
                                            function_frame.symbols.insert(arg.name.clone(), SymbolInfo {
                                                value_type: resolved_value_type.clone(),
                                                is_mut: arg.is_mut,
                                                
                                                is_own: arg.is_own,
                                                is_comptime_const: false,
                                            });

                                            // Share the offset (pass-by-reference)
                                            function_frame.heap_index.insert(arg.name.clone(), src_offset);

                                            // Copy symbol entries for fields
                                            let pbr_prefix = format!("{}.", id_);
                                            let pbr_replacement_prefix = format!("{}.", arg.name);
                                            let mut pbr_field_symbols_to_copy: Vec<SymbolEntry> = Vec::new();
                                            for pbr_caller_frame in context.scope_stack.frames.iter() {
                                                for (pbr_skey, pbr_svalue) in pbr_caller_frame.symbols.iter() {
                                                    if pbr_skey.starts_with(&pbr_prefix) {
                                                        let pbr_new_skey = pbr_skey.replacen(&pbr_prefix, &pbr_replacement_prefix, 1);
                                                        pbr_field_symbols_to_copy.push(SymbolEntry { name: pbr_new_skey, info: pbr_svalue.clone() });
                                                    }
                                                }
                                            }
                                            for pbr_entry in pbr_field_symbols_to_copy {
                                                function_frame.symbols.insert(pbr_entry.name, pbr_entry.info);
                                            }

                                            // Track that this was passed by reference
                                            pass_by_ref_params.insert(arg.name.clone());
                                        } else {
                                            // Own/Type identifier parameters: ownership transfer via offset binding.
                                            // No allocation or copy needed - just bind the existing offset.
                                            let src_offset = if let Some(offset) = context.scope_stack.lookup_var(id_) {
                                                offset
                                            } else if id_.contains('.') {
                                                context.get_field_offset(id_)?
                                            } else {
                                                return Err(e.lang_error(&context.path, "eval", &format!("Source struct '{}' not found in caller context heap_index", id_)))
                                            };
                                            function_frame.heap_index.insert(arg.name.clone(), src_offset);
                                        }
                                    },
                                    _ => {
                                        // Own/Type expression parameters: bind the expression result offset.
                                        // The expression is already evaluated and allocated in the heap.
                                        let src_offset = context.scope_stack.lookup_var(&source_id)
                                            .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("Source '{}' not found in caller context", source_id)))?;
                                        function_frame.heap_index.insert(arg.name.clone(), src_offset);

                                        // For own parameters, remove the source from caller's context (ownership transferred)
                                        if arg.is_own {
                                            context.scope_stack.remove_var(&source_id);
                                            context.scope_stack.remove_symbol(&source_id);
                                        }
                                    },
                                }
                            },
                            _ => {
                                return Err(e.lang_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as an argument. Custom types can only be struct or enum.",
                                                                         &arg.name, &resolved_type_name)))
                            },
                        }
                    },
                }

            },

            _ => {
                return Err(e.todo_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as an argument. Only enum custom types allowed for now.",
                                                         &arg.name, value_type_to_str(&arg.value_type))))
            },
        }

        param_index += 1;
        }
    }

    // Push the populated frame and set function path
    context.scope_stack.frames.push(function_frame);
    context.path = func_def.source_path.clone();

    let result = eval_body(context, &func_def.body)?;
    if result.is_throw {
        // When throwing from a method, we need to copy the thrown struct's heap_index entries
        // from the function frame to the caller frame so that catch blocks can access fields
        let thrown_type_name = &result.thrown_type;
        if !thrown_type_name.is_empty() {
            // Check if this is a custom type (struct)
            if let Some(type_symbol) = context.scope_stack.lookup_symbol(thrown_type_name) {
                if type_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                    // Copy the base variable entry first (from function frame to caller frame)
                    if let Some(base_offset) = context.scope_stack.lookup_var(&result.value) {
                        // Get the second-to-last frame (caller's frame)
                        let frame_count = context.scope_stack.frames.len();
                        if frame_count >= 2 {
                            context.scope_stack.frames[frame_count - 2].heap_index.insert(
                                result.value.clone(),
                                base_offset
                            );
                        }
                    }

                    // Copy symbol entries for fields to caller's frame (not current frame which is about to be popped)
                    let throw_source_prefix = format!("{}.", &result.value);
                    let throw_frame_count = context.scope_stack.frames.len();
                    let throw_symbol_keys_to_copy = context.scope_stack.get_symbols_with_prefix(&throw_source_prefix);
                    for throw_sym_key in throw_symbol_keys_to_copy {
                        let throw_src_symbol_opt = context.scope_stack.lookup_symbol(&throw_sym_key).cloned();
                        if let Some(throw_src_symbol) = throw_src_symbol_opt {
                            if throw_frame_count >= 2 {
                                context.scope_stack.frames[throw_frame_count - 2].symbols.insert(throw_sym_key, throw_src_symbol);
                            }
                        }
                    }
                }
            }
        }
        // Pop frame and restore path before returning
        context.scope_stack.frames.pop();
        context.path = saved_path;
        return Ok(result); // CLEANUP SITE 3: Propagate throw from function body
    }
    let result_heap_offset = result.heap_offset;
    let result_str = result.value;

    // Save struct/enum return value info BEFORE popping (needed for return handling)
    // Bug #160: Deterministic dispatch - instance fields use get_field_offset
    let saved_return_offset: Option<usize> = if func_def.sig.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.sig.return_types[0] {
            match custom_type_name.as_str() {
                "I64" | "U8" | "Str" => None,
                _ => {
                    if EvalHeap::is_instance_field(context, &result_str) {
                        context.get_field_offset(&result_str).ok()
                    } else {
                        context.scope_stack.lookup_var(&result_str)
                    }
                },
            }
        } else {
            None
        }
    } else {
        None
    };

    // Save enum value if returning an enum variable (not constructor)
    let saved_enum_value: Option<EnumVal> = if func_def.sig.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.sig.return_types[0] {
            if let Some(custom_symbol) = context.scope_stack.lookup_symbol(custom_type_name) {
                if custom_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                    if !result_str.contains('.') {
                        // This is a variable, not a constructor - save the enum value
                        // May fail if not actually an enum - that's okay, .ok() returns None
                        EvalHeap::get_enum(context, &result_str, e).ok()
                    } else {
                        None
                    }
                } else {
                    None
                }
            } else {
                None
            }
        } else {
            None
        }
    } else {
        None
    };

    // Collect mut_args values BEFORE popping the function frame
    // (we need to read from the function frame where the args live)
    struct MutArgStructData {
        offset: usize,
        type_name: String,
        was_passed_by_ref: bool,
    }
    enum MutArgValue {
        I64(i64),
        U8(u8),
        Str(String),
        Enum(EnumVal),
        Struct(MutArgStructData),
    }
    struct CollectedMutArg {
        source_name: String,
        value: MutArgValue,
    }
    let mut collected_mut_args: Vec<CollectedMutArg> = Vec::new();

    for m in &mut_args {
        let was_passed_by_ref = pass_by_ref_params.contains(&m.arg_name);
        match &m.value_type {
            ValueType::TCustom(ref type_name) if type_name == "I64" => {
                let val = EvalHeap::get_i64(context, &m.arg_name, e)?;
                collected_mut_args.push(CollectedMutArg { source_name: m.source_name.clone(), value: MutArgValue::I64(val) });
            },
            ValueType::TCustom(ref type_name) if type_name == "U8" => {
                let val = EvalHeap::get_u8(context, &m.arg_name, e)?;
                collected_mut_args.push(CollectedMutArg { source_name: m.source_name.clone(), value: MutArgValue::U8(val) });
            },
            ValueType::TCustom(ref type_name) if type_name == "Str" => {
                let val = string_from_context(context, &m.arg_name, e)?;
                collected_mut_args.push(CollectedMutArg { source_name: m.source_name.clone(), value: MutArgValue::Str(val) });
            },
            ValueType::TCustom(ref type_name) => {
                let symbol_info = match context.scope_stack.lookup_symbol(type_name) {
                    Some(symbol_info_) => symbol_info_.clone(),
                    None => {
                        context.scope_stack.frames.pop();
                        context.path = saved_path;
                        return Err(e.lang_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as an mut argument. Undefined symbol.", m.arg_name, type_name)))
                    },
                };
                match &symbol_info.value_type {
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        let val = EvalHeap::get_enum(context, &m.arg_name, e)?;
                        collected_mut_args.push(CollectedMutArg { source_name: m.source_name.clone(), value: MutArgValue::Enum(val) });
                    },
                    ValueType::TType(TTypeDef::TStructDef) => {
                        if let Some(offset) = context.scope_stack.lookup_var(&m.arg_name) {
                            collected_mut_args.push(CollectedMutArg { source_name: m.source_name.clone(), value: MutArgValue::Struct(MutArgStructData {
                                offset,
                                type_name: type_name.clone(),
                                was_passed_by_ref,
                            })});
                        } else {
                            context.scope_stack.frames.pop();
                            context.path = saved_path;
                            return Err(e.lang_error(&context.path, "eval", &format!("Missing struct heap index for argument '{}'", m.arg_name)));
                        }
                    },
                    _ => {
                        context.scope_stack.frames.pop();
                        context.path = saved_path;
                        return Err(e.lang_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Not an enum or struct, but a '{}'.",
                                                                 m.arg_name, type_name, value_type_to_str(&symbol_info.value_type))))
                    },
                }

            },
            _ => {
                context.scope_stack.frames.pop();
                context.path = saved_path;
                return Err(e.todo_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Only structs and enums allowed for now.",
                                                         m.arg_name, value_type_to_str(&m.value_type))))
            }
        }
    }

    // Pop function frame BEFORE writing mut args back to caller
    context.scope_stack.frames.pop();
    context.path = saved_path.clone();

    // Write collected mut_args values to caller's frame (now on top)
    for c in collected_mut_args {
        match c.value {
            MutArgValue::I64(val) => {
                EvalHeap::insert_i64(context, &c.source_name, &val.to_string(), e)?;
            },
            MutArgValue::U8(val) => {
                EvalHeap::insert_u8(context, &c.source_name, &val.to_string(), e)?;
            },
            MutArgValue::Str(val) => {
                EvalHeap::insert_string(context, &c.source_name, &val, e)?;
            },
            MutArgValue::Enum(val) => {
                // Bug #38 fix: Set temp_enum_payload so insert_enum preserves the payload
                if let Some(payload_data) = &val.payload {
                    if let Some(payload_type) = &val.payload_type {
                        context.temp_enum_payload = Some(EnumPayload { data: payload_data.clone(), value_type: payload_type.clone() });
                    }
                }
                EvalHeap::insert_enum(context, &c.source_name, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name), e)?;
            },
            MutArgValue::Struct(MutArgStructData { offset, type_name, was_passed_by_ref }) => {
                if was_passed_by_ref {
                    // Pass-by-ref: just update heap_index (data already modified in-place)
                    context.scope_stack.frames.last_mut().unwrap().heap_index.insert(c.source_name.to_string(), offset);
                } else {
                    // Bug #43 fix: For non-pass-by-ref (struct was copied), we need to copy
                    // the modified data back to the original location, especially for field
                    // access chains like "frame.funcs" where just updating heap_index won't
                    // update the actual bytes in the parent struct.
                    if c.source_name.contains('.') {
                        // Field access: copy data back to original location
                        let dest_offset = context.get_field_offset(&c.source_name)
                            .map_err(|err| e.lang_error(&context.path, "eval", &format!("mut struct write-back: {}", err)))?;
                        let struct_size = context.get_type_size(&type_name)?;
                        // Copy from callee's offset to original location
                        for i in 0..struct_size {
                            let byte = EvalHeap::g().get(offset + i, 1)[0];
                            EvalHeap::g().set(dest_offset + i, &[byte])?;
                        }
                    } else {
                        // Simple identifier: update heap_index
                        // Bug #160: map_instance_fields removed - type checker handles symbol registration
                        context.scope_stack.frames.last_mut().unwrap().heap_index.insert(c.source_name.to_string(), offset);
                    }
                }
            },
        }
    }

    // If function returns a user-defined struct or enum, copy it back to caller frame as temp return val
    // NOTE: Frame already popped above, using saved_return_offset and saved_enum_value
    if func_def.sig.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.sig.return_types[0] {
            // Skip primitive types I64, U8, Str - they return values directly
            match custom_type_name.as_str() {
                "I64" | "U8" | "Str" => { /* Do nothing for primitive types */ },
                _ => {

                    if let Some(custom_symbol) = context.scope_stack.lookup_symbol(custom_type_name) {
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                let return_instance = format!("{}{}", RETURN_INSTANCE_NAME, EvalHeap::g().temp_id_counter);
                                EvalHeap::g().temp_id_counter += 1;

                                // Use saved offset (saved before popping)
                                let offset = saved_return_offset.ok_or_else(|| {
                                    e.lang_error(&context.path, "eval", &format!("Missing heap index for return value '{}'", result_str))
                                })?;

                                // Insert the temporary return variable into the caller's frame
                                context.scope_stack.declare_symbol(return_instance.to_string(), SymbolInfo {
                                    value_type: ValueType::TCustom(custom_type_name.to_string()),
                                    is_mut: true,
                                    
                                    is_own: false,
                                    is_comptime_const: false,
                                });

                                // Share the base offset in caller's frame
                                context.scope_stack.frames.last_mut().unwrap().heap_index.insert(return_instance.to_string(), offset);

                                return Ok(EvalResult::new_return(&return_instance)) // CLEANUP SITE 4: Return struct instance
                            },
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                // For enum returns, check if result_str is a constructor expression or a variable
                                if result_str.contains('.') {
                                    // This is a constructor expression - just return as-is
                                    return Ok(EvalResult::new(&result_str)); // CLEANUP SITE 5: Return enum constructor
                                }

                                // This is a variable, use saved enum value
                                let val = saved_enum_value.ok_or_else(|| {
                                    e.lang_error(&context.path, "eval", &format!("Missing enum value for return value '{}'", result_str))
                                })?;

                                let return_instance = format!("{}{}", RETURN_INSTANCE_NAME, EvalHeap::g().temp_id_counter);
                                EvalHeap::g().temp_id_counter += 1;

                                // Set temp_enum_payload if the enum has a payload
                                if let (Some(payload_data), Some(payload_type)) = (val.payload, val.payload_type) {
                                    context.temp_enum_payload = Some(EnumPayload { data: payload_data, value_type: payload_type });
                                }

                                EvalHeap::insert_enum(context, &return_instance, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name), e)?;
                                return Ok(EvalResult::new_return(&return_instance)) // CLEANUP SITE 6: Return enum variable
                            },
                            _ => {
                                // Not a struct or enum return, ignore
                            }
                        }
                    }
                },

            }
        }
    }

    // Frame already popped above
    let mut final_result = EvalResult::new(&result_str);
    final_result.heap_offset = result_heap_offset;
    return Ok(final_result) // CLEANUP SITE 7: Return normal value (final return)
}

// ---------- Core function/procedure dispatcher

fn eval_core_func_proc_call(name: &str, context: &mut Context, e: &Expr, is_proc: bool) -> Result<EvalResult, String> {
    // Note: loc, _file, _line, _col are handled by precomp (replaced with literals)
    return match name {
        "size_of" => ext::func_size_of(context, &e),
        "type_as_str" => ext::func_type_as_str(context, &e),
        "to_ptr" => ext::func_to_ptr(context, &e),
        "malloc" => ext::func_malloc(context, &e),
        "free" => ext::func_free(context, &e),
        "memset" => ext::func_memset(context, &e),
        "memcpy" => ext::func_memcpy(context, &e),
        "i64_lt" => ext::func_lt(context, &e),
        "i64_gt" => ext::func_gt(context, &e),
        "u8_lt" => ext::func_u8_lt(context, &e),
        "u8_gt" => ext::func_u8_gt(context, &e),
        "u8_xor" => ext::func_u8_xor(context, &e),
        "u8_and" => ext::func_u8_and(context, &e),
        "u8_or" => ext::func_u8_or(context, &e),
        "i64_add" => ext::func_add(context, &e),
        "i64_sub" => ext::func_sub(context, &e),
        "i64_mul" => ext::func_mul(context, &e),
        "i64_div" => ext::func_div(context, &e),
        "i64_mod" => ext::func_mod(context, &e),
        "i64_and" => ext::func_i64_and(context, &e),
        "i64_or" => ext::func_i64_or(context, &e),
        "i64_xor" => ext::func_i64_xor(context, &e),
        "str_to_i64" => ext::func_str_to_i64(context, &e),
        "i64_to_str" => ext::func_i64_to_str(context, &e),
        "enum_to_str" => ext::func_enum_to_str(context, &e),
        "enum_get_payload" => ext::func_enum_get_payload(context, &e),
        "enum_get_payload_type" => ext::func_enum_get_payload_type(context, &e),
        "u8_add" => ext::func_u8_add(context, &e),
        "u8_div" => ext::func_u8_div(context, &e),
        "u8_mod" => ext::func_u8_mod(context, &e),
        "u8_mul" => ext::func_u8_mul(context, &e),
        "u8_sub" => ext::func_u8_sub(context, &e),
        "u8_to_i64" => ext::func_u8_to_i64(context, &e),
        "i64_to_u8" => ext::func_i64_to_u8(context, &e),
        "eval_to_str" => proc_eval_to_str(context, &e),
        "exit" => ext::func_exit(context, &e),
        "import" => proc_import(context, &e),
        "input_read_line" => ext::proc_input_read_line(context, &e),
        "single_print" => ext::proc_single_print(context, &e),
        "print_flush" => ext::proc_print_flush(context, &e),
        "readfile" => ext::proc_readfile(context, &e),
        "writefile" => ext::proc_writefile(context, &e),
        "run_cmd" => ext::proc_run_cmd(context, &e),
        "spawn_cmd" => ext::proc_spawn_cmd(context, &e),
        "check_cmd_status" => ext::proc_check_cmd_status(context, &e),
        "sleep" => ext::proc_sleep(context, &e),
        "get_thread_count" => ext::proc_get_thread_count(context, &e),
        "file_mtime" => ext::func_file_mtime(context, &e),
        "list_dir_raw" => ext::func_list_dir_raw(context, &e),
        "fs_parent_dir" => ext::func_fs_parent_dir(context, &e),
        "fs_mkdir_p" => ext::proc_fs_mkdir_p(context, &e),
        "eval_file" => proc_eval_file(context, &e),
        "has_const" => ext::func_has_const(context, &e),
        "has_field" => ext::func_has_field(context, &e),
        "__struct_field_count" => ext::func_struct_field_count(context, &e),
        "__struct_field_name" => ext::func_struct_field_name(context, &e),
        "__struct_field_is_mut" => ext::func_struct_field_is_mut(context, &e),
        "__struct_field_type_kind" => ext::func_struct_field_type_kind(context, &e),
        "__struct_field_type_arg" => ext::func_struct_field_type_arg(context, &e),
        "__enum_variant_count" => ext::func_enum_variant_count(context, &e),
        "__enum_variant_name" => ext::func_enum_variant_name(context, &e),
        "__enum_variant_has_payload" => ext::func_enum_variant_has_payload(context, &e),
        "__enum_variant_payload_type" => ext::func_enum_variant_payload_type(context, &e),
        "__func_sig_param_count" => ext::func_func_sig_param_count(context, &e),
        "__func_sig_param_type" => ext::func_func_sig_param_type(context, &e),
        "__func_sig_return_count" => ext::func_func_sig_return_count(context, &e),
        "__func_sig_return_type" => ext::func_func_sig_return_type(context, &e),
        "__func_sig_throw_count" => ext::func_func_sig_throw_count(context, &e),
        "__func_sig_throw_type" => ext::func_func_sig_throw_type(context, &e),
        _ => {
            if is_proc {
                Err(e.lang_error(&context.path, "eval", &format!("Core procedure '{}' not implemented.", name)))
            } else {
                Err(e.lang_error(&context.path, "eval", &format!("Core function '{}' not implemented.", name)))
            }
        },
    }
}

// ---------- main_interpret, interpret_file_with_context, interpret_file (like rstil.rs/til.til)

pub fn main_interpret(skip_init_and_typecheck: bool, context: &mut Context, path: &String, source: String, main_args: Vec<String>) -> Result<EvalResult, String> {

    // Mark main file as "done" to prevent re-processing via circular imports
    context.imports_init_done.insert(path.clone());
    context.imports_typer_done.insert(path.clone());
    context.imports_precomp_done.insert(path.clone());
    context.imports_eval_done.insert(path.clone());

    let mut lexer = match lexer_from_source(&path, source) {
        Ok(_result) => _result,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };

    let mode = parse_mode(&path, &mut lexer)?;
    context.mode_def = mode;

    for import_str in context.mode_def.imports.clone() {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }), params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};

        // Mode imports need full processing: init, typer, eval
        // (Regular imports have init done during main file's init, but mode imports happen before that)
        match init_import_declarations(context, &import_fcall_expr, &import_str) {
            Ok(_) => {},
            Err(error_string) => {
                return Err(format!("{}:{}", &path, error_string));
            },
        }
        let typer_errors = typer_import_declarations(context, &import_str);
        if !typer_errors.is_empty() {
            for err in &typer_errors {
                println!("{}", err);
            }
            return Err(format!("Compiler errors: {} type errors found", typer_errors.len()));
        }
        match proc_import(context, &import_fcall_expr) {
            Ok(_) => {},
            Err(error_string) => {
                return Err(format!("{}:{}", &path, error_string));
            },
        }
    }

    let mut e: Expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };

    // Preinit phase: Auto-generate delete() and clone() methods for structs
    e = preinit_expr(&e)?;

    if !SKIP_AST {
        println!("AST: \n{}", to_ast_str(&e));
    }

    // Skip init and type checking if this is Phase 2 of a two-phase import
    // (declarations already registered in Phase 1)
    if !skip_init_and_typecheck {
        let mut errors = crate::rs::init::init_context(context, &e)?;
        if errors.len() > 0 {
            for err in &errors {
                println!("{}", err);
            }
            return Err(format!("Compiler errors: {} declaration errors found", errors.len()));
        }
        errors.extend(basic_mode_checks(&context, &e)?);

        // For modes that require a main proc, add an implicit call to main
        if context.mode_def.needs_main_proc {
            let mut main_params = Vec::new();
            main_params.push(Expr{node_type: NodeType::Identifier("main".to_string()), line: 0, col: 0, params: Vec::new()});
            for str_arg in main_args {
                main_params.push(Expr{node_type: NodeType::LLiteral(Literal::Str(str_arg)), line: 0, col: 0, params: Vec::new()});
            }
            e.params.push(Expr{node_type: NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }), line: 0, col: 0, params: main_params});
        }
        // Issue #105: Expand struct-returning macros before type checking
        e = crate::rs::precomp::expand_struct_macros(context, &e)?;

        // Bug #128: Unified type checking - runs check_types and resolves INFER_TYPE in one call
        let (resolved_e, type_errors) = type_check(context, &e)?;
        errors.extend(type_errors);

        // Check throw/catch and return things in the root body of the file (for modes script and test, for example)
        let func_def = FuncDef{sig: FuncSig{function_type: FunctionType::FTProc, args: vec![], return_types: vec![], throw_types: vec![]}, arg_names: vec![], body: vec![], source_path: path.clone()};
        let mut thrown_types: Vec<ThrownType> = vec![];
        let mut return_found = false;
        errors.extend(check_body_returns_throws(context, &resolved_e, &func_def, resolved_e.params.as_slice(), &mut thrown_types, &mut return_found)?);

        if return_found {
            errors.push(resolved_e.error(&path, "type", "Cannot return from the root of the file"));
        }
        for t in &thrown_types {
            errors.push(t.msg.clone());
        }

        if errors.len() > 0 {
            for err in &errors {
                println!("{}", err);
            }
            return Err(format!("Compiler errors: {} type errors found", errors.len()));
        }

        // No need to clear import cache - we use separate per-phase tracking now
        e = resolved_e;

        // Desugarer phase: Desugar ForIn loops to while loops
        e = desugar_expr(context, &e)?;

        // Garbager phase: (future) ASAP destruction - insert automatic delete() calls
        e = garbager_expr(context, &e)?;

        // UFCS phase: Resolve UFCS calls and reorder named arguments
        e = ufcs_expr(context, &e)?;

        // Precomputation phase: Handle comptime intrinsics, struct/enum constructors, import()
        e = precomp_expr(context, &e)?;

        // Scavenger phase: Remove unused function declarations
        // NOTE: Disabled for interpreter - it doesn't merge ASTs like builder does,
        // so UFCS calls from imported modules aren't fully resolved in the main file.
        // Scavenger is mainly useful for compilation anyway where code size matters.
        // e = crate::rs::scavenger::scavenger_expr(context, &e)?;
    }

    return match eval_expr(context, &e) {
        Ok(eval_result) => Ok(eval_result),
        Err(err) => Err(format!("{}:{}", path, err)),
    }
}

pub fn interpret_file(path: &String, main_args: Vec<String>) -> Result<EvalResult, String> {
    let mut context = Context::new(path, DEFAULT_MODE)?;
    if path != "src/core/core.til" {
        // Automatically import core.til (needs full init and eval, skip_init=false)
        let core_path = "src/core/core.til".to_string();
        interpret_file_with_context(true, false, &mut context, &core_path, Vec::new())?;
    }
    return interpret_file_with_context(false, false, &mut context, &path, main_args)
}

pub fn interpret_file_with_context(is_import: bool, skip_init: bool, context: &mut Context, path: &String, main_args: Vec<String>) -> Result<EvalResult, String> {
    let previous_mode = context.mode_def.clone();
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                return Err(format!("File '{path}' not found."))
            },
            other_error => {
                return Err(format!("Problem opening the file '{path}': {other_error:?}"))
            },
        },
    };
    let run_result = main_interpret(skip_init, context, &path, source, main_args)?;

    if is_import && !can_be_imported(&context.mode_def) {
        return Err(format!("file '{path}' of mode '{}' cannot be imported", context.mode_def.name))
    }
    context.mode_def = previous_mode; // restore the context mode of the calling file
    return Ok(run_result)
}

// ---------- proc_eval_to_str, proc_eval_file, proc_import (moved from ext.rs)

pub fn proc_eval_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    ext::validate_arg_count(&context.path, e, "eval_to_str", 1, true)?;

    let path = "eval".to_string(); // Placeholder path
    let source_expr = eval_expr(context, e.params.get(1).unwrap())?;
    if source_expr.is_throw {
        return Ok(source_expr); // Propagate throw
    }

    let str_source = format!("mode script; {}", source_expr.value);
    return main_interpret(false, context, &path, str_source, Vec::new())
}

pub fn proc_eval_file(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() < 2 {
        return Err(e.lang_error(&context.path, "eval", "Core proc 'eval_file' expects at least 1 parameter"));
    }

    let result = eval_expr(context, e.params.get(1).unwrap())?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let path = result.value;

    let mut main_args = Vec::new();
    for i in 2..e.params.len() {
        let arg_result = eval_expr(context, e.params.get(i).unwrap())?;
        if arg_result.is_throw {
            return Ok(arg_result); // Propagate throw
        }
        main_args.push(arg_result.value);
    }

    match interpret_file(&path, main_args) {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error_string) => Err(e.error(&context.path, "eval", &format!("While running file {path}\n{error_string}"))),
    }
}

pub fn proc_import(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    ext::validate_arg_count(&context.path, e, "import", 1, true)?;

    let result = eval_expr(context, e.params.get(1).unwrap())?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    let original_path = context.path.clone();
    let path = import_path_to_file_path(&result.value);

    // Already done (or in progress)? Skip.
    // Adding to done at START handles both circular imports and re-imports.
    if context.imports_eval_done.contains(&path) {
        return Ok(EvalResult::new(""));
    }

    // Mark as done immediately - before processing - to handle circular imports
    context.imports_eval_done.insert(path.clone());

    // Get stored AST from init phase
    let ast = match context.imported_asts.get(&path) {
        Some(ast) => ast.clone(),
        None => return Err(e.error(&context.path, "eval", &format!(
            "Import {} not found in stored ASTs - init phase should have stored it", path))),
    };

    context.path = path.clone();

    // Run desugar on the imported AST (always - no separate tracking)
    let ast = desugar_expr(context, &ast)?;

    // Run garbager on the imported AST (always - no separate tracking)
    let ast = garbager_expr(context, &ast)?;

    // Run UFCS on the imported AST (always - no separate tracking)
    let ast = ufcs_expr(context, &ast)?;

    // Run precomp on the imported AST if not already done
    let ast = if !context.imports_precomp_done.contains(&path) {
        context.imports_precomp_done.insert(path.clone());
        precomp_expr(context, &ast)?
    } else {
        ast
    };

    // Eval the precomp'd AST
    let eval_result = eval_expr(context, &ast);

    context.path = original_path;

    match eval_result {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error_string) => Err(e.error(&context.path, "eval", &format!(
            "While importing {}:\n{}", path, error_string))),
    }
}

