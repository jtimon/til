use std::collections::HashMap;
use crate::rs::init::{Context, SymbolInfo, EnumVal, ScopeFrame, ScopeType, get_value_type, get_func_name_in_call};
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, Literal, ValueType, TTypeDef, Declaration, PatternInfo, FunctionType, SFuncDef,
    value_type_to_str, get_combined_name,
};
use crate::rs::typer::{get_func_def_for_fcall_with_expr, func_proc_has_multi_arg};
use crate::rs::ext;

// Interpreter/Eval phase: Runtime evaluation and execution
// This module handles the eval phase that runs after type checking.
// Manages arena, memory allocation, and actual program execution.

const RETURN_INSTANCE_NAME : &str = "___temp_return_val_";

use crate::rs::arena::Arena;


#[derive(Clone, Debug)]
pub struct EvalResult {
    pub value: String,
    pub is_return: bool,
    pub is_throw: bool,
    pub thrown_type: Option<String>,
}

impl EvalResult {
    pub fn new(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: false, thrown_type: None}
    }

    pub fn new_return(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: true, is_throw: false, thrown_type: None}
    }

    pub fn new_throw(value: &str, thrown_type: ValueType) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: true, thrown_type: Some(value_type_to_str(&thrown_type))}
    }
}

// Helper function to extract bool value from a Bool struct instance
pub fn bool_from_context(context: &Context, id: &str, e: &Expr) -> Result<bool, String> {
    // Validate the Bool struct exists
    context.get_struct(id, e)?;

    // Read the .data field (which is a U8)
    let data_field = format!("{}.data", id);
    let u8_val = Arena::get_u8(context, &data_field, e)?;

    // Convert U8 to bool (0 = false, non-zero = true)
    Ok(u8_val != 0)
}

// Helper function to extract String value from a Str struct instance
pub fn string_from_context(context: &Context, id: &str, e: &Expr) -> Result<String, String> {
    // Validate the Str struct exists
    context.get_struct(id, e)?;

    // Read the c_string field (I64 pointer to string data in Arena)
    let c_string_ptr = Arena::get_i64(context, &format!("{}.c_string", id), e)? as usize;

    // Read the cap field (I64 length)
    let length = Arena::get_i64(context, &format!("{}.cap", id), e)? as usize;

    // Bounds check
    if c_string_ptr + length > Arena::g().memory.len() {
        return Err(e.lang_error(&context.path, "string_from_context", &format!("string content out of bounds for '{}'", id)));
    }

    // Read string bytes from Arena and convert to String
    let bytes = &Arena::g().memory[c_string_ptr..c_string_ptr + length];
    Ok(String::from_utf8_lossy(bytes).to_string())
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
// Supports both legacy string bools ("true"/"false") and Bool struct instances.
fn eval_condition_to_bool(context: &Context, result: &EvalResult, expr: &Expr) -> Result<bool, String> {
    // First try parsing as string bool (backwards compatibility)
    if let Ok(b) = result.value.parse::<bool>() {
        return Ok(b);
    }

    // Otherwise, assume it's a Bool struct instance - read its .data field
    // The value should be the identifier name of the Bool instance
    let bool_id = &result.value;
    let data_field_id = format!("{}.data", bool_id);
    let u8_val = Arena::get_u8(context, &data_field_id, expr)?;
    Ok(u8_val != 0)
}

// Helper function to validate function/procedure argument counts
fn validate_func_arg_count(path: &str, e: &Expr, name: &str, func_def: &SFuncDef) -> Result<(), String> {
    let provided_args = e.params.len() - 1;
    let has_multi_arg = func_proc_has_multi_arg(func_def);

    // Check exact count for non-variadic functions
    if !has_multi_arg && func_def.args.len() != provided_args {
        return Err(e.lang_error(path, "eval", &format!("func '{}' expected {} args, but {} were provided.",
                                                 name, func_def.args.len(), provided_args)));
    }

    // Check minimum count for variadic functions
    if has_multi_arg && func_def.args.len() - 1 > provided_args {
        return Err(e.lang_error(path, "eval", &format!("func '{}' expected at least {} args, but {} were provided.",
                                                 name, func_def.args.len() - 1, provided_args)));
    }

    Ok(())
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
                let res = eval_expr(ctx, default_expr)?;
                if res.is_throw {
                    return Err(e.lang_error(&ctx.path, "eval_struct_defaults", &format!("thrown '{}' while evaluating default for field '{}'", res.thrown_type.unwrap_or_default(), decl.name)));
                }
                defaults.insert(decl.name.clone(), res.value);

                // Handle nested structs recursively
                if let ValueType::TCustom(type_name) = &decl.value_type {
                    // Skip primitives, enums, and Str (handled specially)
                    if type_name != "U8" && type_name != "I64" && type_name != "Str" {
                        if ctx.scope_stack.lookup_enum(type_name).is_none() {
                            if ctx.scope_stack.lookup_struct(type_name).is_some() {
                                let nested = eval_struct_defaults(ctx, type_name, e)?;
                                for (k, v) in nested {
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

/// Get or create a default instance template for a struct type.
/// Returns the arena offset of the template. Template is cached for reuse.
fn get_or_create_default_instance(ctx: &mut Context, struct_type: &str, e: &Expr) -> Result<usize, String> {
    // Check if template already exists
    if let Some(&offset) = Arena::g().default_instances.get(struct_type) {
        return Ok(offset);
    }

    // Create template instance
    let template_id = format!("__default_{}", struct_type);

    // Declare temporary symbol for template (needed by insert_struct_core)
    ctx.scope_stack.declare_symbol(template_id.clone(), SymbolInfo {
        value_type: ValueType::TCustom(struct_type.to_string()),
        is_mut: true,
        is_copy: false,
        is_own: false,
    });

    // Evaluate defaults and create template
    let defaults = eval_struct_defaults(ctx, struct_type, e)?;
    let result = Arena::insert_struct_core(ctx, &template_id, struct_type, None, &defaults, e)?;

    // Get the template's arena offset (first mapping is the base struct)
    let template_offset = result.arena_mappings.first()
        .map(|(_, off)| *off)
        .ok_or_else(|| e.lang_error(&ctx.path, "get_or_create_default_instance", "No arena mapping for template"))?;

    // Cache the template offset
    Arena::g().default_instances.insert(struct_type.to_string(), template_offset);

    Ok(template_offset)
}

pub fn eval_expr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match &e.node_type {
        NodeType::Body => eval_body(context, &e.params),
        NodeType::LLiteral(Literal::Number(li64)) => Ok(EvalResult::new(li64)),
        NodeType::LLiteral(Literal::Str(lstring)) => Ok(EvalResult::new(lstring)),
        NodeType::LLiteral(Literal::List(llist)) => Ok(EvalResult::new(llist)),
        NodeType::FCall => {
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
            let cond_expr = e.get(0)?;
            let result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond)
            }
            if eval_condition_to_bool(context, &result_cond, cond_expr)? {
                return eval_expr(context, e.get(1)?)
            } else if e.params.len() == 3 {
                return eval_expr(context, e.get(2)?)
            } else {
                return Ok(EvalResult::new(""))
            }
        },
        NodeType::While => {
            validate_conditional_params(&context.path, e, "while", 2, 2)?;
            let mut cond_expr = e.get(0)?;
            let mut result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond.clone())
            }
            while eval_condition_to_bool(context, &result_cond, cond_expr)? {
                let result = eval_expr(context, e.get(1)?)?;
                if result.is_return || result.is_throw {
                    return Ok(result)
                }
                cond_expr = e.get(0)?;
                result_cond = eval_expr(context, cond_expr)?;
                if result_cond.is_throw {
                    return Ok(result_cond)
                }
            }
            Ok(EvalResult::new(""))
        },
        NodeType::Switch => {
            if e.params.len() < 3 {
                return Err(e.lang_error(&context.path, "eval", "switch nodes must have at least 3 parameters."));
            }
            let to_switch = e.get(0)?;
            let value_type = get_value_type(&context, &to_switch)?;
            let result_to_switch = eval_expr(context, &to_switch)?;
            if result_to_switch.is_throw {
                return Ok(result_to_switch);
            }

            let mut param_it = 1;
            while param_it < e.params.len() {
                let case = e.get(param_it)?;
                if case.node_type == NodeType::DefaultCase {
                    param_it += 1;
                    return eval_expr(context, e.get(param_it)?);
                }

                let case_type = get_value_type(&context, &case)?;
                let vt_str = value_type_to_str(&value_type);
                let ct_str = value_type_to_str(&case_type);
                if ct_str != vt_str && ct_str != format!("{}Range", vt_str) {
                    return Err(e.lang_error(&context.path, "eval", &format!("switch value type {:?}, case value type {:?}", value_type, case_type)));
                }

                // Handle pattern matching with payload extraction
                if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case.node_type {
                    // Check if the switch value's enum variant matches the pattern
                    // The switch value should be an enum stored as EnumVal
                    // We need to extract the enum value - get the identifier name from to_switch
                    let enum_var_name = if let NodeType::Identifier(name) = &to_switch.node_type {
                        name
                    } else {
                        return Err(case.error(&context.path, "eval", "Pattern matching requires switch value to be a variable"));
                    };

                    let enum_val = Arena::get_enum(context, enum_var_name, &case)?;

                    // Check if variant matches (enum_val.enum_name should match variant_name)
                    let full_variant = format!("{}.{}", enum_val.enum_type, enum_val.enum_name);
                    if full_variant == *variant_name || enum_val.enum_name == *variant_name {
                        // Match! Extract the payload and bind it to the variable
                        param_it += 1;

                        // Extract payload into the binding variable
                        if let Some(payload_type) = &enum_val.payload_type {
                            if let Some(payload_bytes) = &enum_val.payload {
                                // Use the existing payload extraction logic
                                // We need to insert the payload into context with the binding_var name
                                // TODO FIX: Bool enum payload extraction - needs special handling to read 1 byte and create Bool value
                                match payload_type {
                                    ValueType::TCustom(type_name) if type_name == "Bool" => {
                                        if payload_bytes.len() != 1 {
                                            return Err(case.error(&context.path, "eval", "Invalid Bool payload size"));
                                        }
                                        let bool_val = payload_bytes[0] != 0;

                                        // First add the symbol to context
                                        context.scope_stack.declare_symbol(
                                            binding_var.clone(),
                                            SymbolInfo {
                                                value_type: ValueType::TCustom("Bool".to_string()),
                                                is_mut: false,
                                                is_copy: false,
                                            is_own: false,
                                            }
                                        );

                                        // Now insert the value
                                        Arena::insert_bool(context, binding_var, &bool_val.to_string(), &case)?;
                                    }
                                    ValueType::TCustom(type_name) if type_name == "I64" => {
                                        if payload_bytes.len() != 8 {
                                            return Err(case.error(&context.path, "eval", "Invalid I64 payload size"));
                                        }
                                        let mut bytes = [0u8; 8];
                                        bytes.copy_from_slice(&payload_bytes[0..8]);
                                        let i64_val = i64::from_le_bytes(bytes);

                                        // First add the symbol to context
                                        context.scope_stack.declare_symbol(
                                            binding_var.clone(),
                                            SymbolInfo {
                                                value_type: ValueType::TCustom("I64".to_string()),
                                                is_mut: false,
                                                is_copy: false,
                                            is_own: false,
                                            }
                                        );

                                        Arena::insert_i64(context, binding_var, &i64_val.to_string(), &case)?;
                                    }
                                    ValueType::TCustom(type_name) if type_name == "Str" => {
                                        // For Str, the payload contains pointer + size (16 bytes total)
                                        // We need to reconstruct the string from the arena
                                        if payload_bytes.len() != 16 {
                                            return Err(case.error(&context.path, "eval", &format!("Invalid Str payload size: expected 16, got {}", payload_bytes.len())));
                                        }
                                        // Extract the c_string pointer (first 8 bytes)
                                        let mut ptr_bytes = [0u8; 8];
                                        ptr_bytes.copy_from_slice(&payload_bytes[0..8]);
                                        let ptr_offset = i64::from_le_bytes(ptr_bytes);

                                        // Extract size (next 8 bytes)
                                        let mut size_bytes = [0u8; 8];
                                        size_bytes.copy_from_slice(&payload_bytes[8..16]);
                                        let size = i64::from_le_bytes(size_bytes);

                                        // First add the symbol to context
                                        context.scope_stack.declare_symbol(
                                            binding_var.clone(),
                                            SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false,
                                                is_copy: false,
                                            is_own: false,
                                            }
                                        );

                                        if size > 0 && ptr_offset > 0 {
                                            // Read the actual string from the global arena
                                            let ptr = ptr_offset as usize;
                                            let len = size as usize;
                                            if ptr + len > Arena::g().memory.len() {
                                                return Err(case.error(&context.path, "eval", "String payload pointer out of bounds"));
                                            }
                                            let str_bytes = &Arena::g().memory[ptr..ptr + len];
                                            let string_value = String::from_utf8_lossy(str_bytes).to_string();
                                            Arena::insert_string(context, binding_var, &string_value, &case)?;
                                        } else {
                                            let empty_string = String::new();
                                            Arena::insert_string(context, binding_var, &empty_string, &case)?;
                                        }
                                    }
                                    ValueType::TCustom(type_name) => {
                                        // Handle custom types (structs and enums)
                                        let type_symbol = context.scope_stack.lookup_symbol(type_name).ok_or_else(|| {
                                            case.error(&context.path, "eval", &format!("Unknown type '{}'", type_name))
                                        })?;

                                        match &type_symbol.value_type {
                                            ValueType::TType(TTypeDef::TStructDef) => {
                                                // Handle struct payloads
                                                // First add the symbol to context
                                                context.scope_stack.declare_symbol(
                                                    binding_var.clone(),
                                                    SymbolInfo {
                                                        value_type: payload_type.clone(),
                                                        is_mut: false,
                                                        is_copy: false,
                                                    is_own: false,
                                                    }
                                                );

                                                // Allocate destination struct in arena (from cached template)
                                                let template_offset = get_or_create_default_instance(context, type_name, &case)?;
                                                Arena::insert_struct_from_template(context, binding_var, type_name, template_offset, &case)?;

                                                // Get destination offset
                                                let dest_offset = context.scope_stack.lookup_var(binding_var).ok_or_else(|| {
                                                    case.error(&context.path, "eval", &format!("Struct '{}' not found in arena", binding_var))
                                                })?;

                                                // Validate payload size
                                                let struct_size = context.get_type_size( type_name)
                                                    .map_err(|err| case.error(&context.path, "eval", &err))?;
                                                if payload_bytes.len() != struct_size {
                                                    return Err(case.error(&context.path, "eval", &format!(
                                                        "Payload size mismatch: expected {}, got {}",
                                                        struct_size, payload_bytes.len()
                                                    )));
                                                }

                                                // Copy payload bytes directly into arena
                                                Arena::g().memory[dest_offset..dest_offset + struct_size]
                                                    .copy_from_slice(&payload_bytes);
                                            },
                                            ValueType::TType(TTypeDef::TEnumDef) => {
                                                // Handle enum payloads
                                                // The payload_bytes contains: [8 bytes variant tag][N bytes enum's payload]

                                                if payload_bytes.len() < 8 {
                                                    return Err(case.error(&context.path, "eval", "Invalid enum payload: too small"));
                                                }

                                                // Extract variant tag (first 8 bytes)
                                                let mut variant_bytes = [0u8; 8];
                                                variant_bytes.copy_from_slice(&payload_bytes[0..8]);
                                                let variant_pos = i64::from_le_bytes(variant_bytes);

                                                // Extract enum's own payload (rest of bytes)
                                                let inner_payload = if payload_bytes.len() > 8 {
                                                    Some(payload_bytes[8..].to_vec())
                                                } else {
                                                    None
                                                };

                                                // Get the enum definition to find variant name
                                                let enum_def = context.scope_stack.lookup_enum(type_name).ok_or_else(|| {
                                                    case.error(&context.path, "eval", &format!("Enum definition for '{}' not found", type_name))
                                                })?;

                                                // Find variant name by matching the variant position
                                                let mut found_variant = None;
                                                let mut found = false;
                                                for (name, _) in &enum_def.enum_map {
                                                    if !found {
                                                        let pos = Context::get_variant_pos(enum_def, name, &context.path, &case)?;
                                                        if pos == variant_pos {
                                                            found_variant = Some(name.clone());
                                                            found = true;
                                                        }
                                                    }
                                                }

                                                let variant_name = found_variant.ok_or_else(|| {
                                                    case.error(&context.path, "eval", &format!("Variant position {} not found in enum {}", variant_pos, type_name))
                                                })?;

                                                // Get the inner payload type
                                                let inner_payload_type = enum_def.enum_map.get(&variant_name)
                                                    .and_then(|opt| opt.clone());

                                                // Add symbol to context first
                                                context.scope_stack.declare_symbol(
                                                    binding_var.clone(),
                                                    SymbolInfo {
                                                        value_type: payload_type.clone(),
                                                        is_mut: false,
                                                        is_copy: false,
                                                    is_own: false,
                                                    }
                                                );

                                                // Now reconstruct the enum and insert it
                                                let enum_val_str = format!("{}.{}", type_name, variant_name);

                                                // Set temp_enum_payload if there's an inner payload
                                                if let Some(payload_data) = inner_payload {
                                                    context.temp_enum_payload = Some((payload_data, inner_payload_type.unwrap()));
                                                }

                                                // Insert the enum
                                                Arena::insert_enum(context, binding_var, type_name, &enum_val_str, &case)?;
                                            },
                                            _ => {
                                                // Other types not yet implemented
                                                return Err(case.error(&context.path, "eval", &format!("Pattern matching not yet implemented for payload type: {:?}", payload_type)));
                                            }
                                        }
                                    },
                                    _ => {
                                        // Unknown types
                                        return Err(case.error(&context.path, "eval", &format!("Pattern matching not yet implemented for payload type: {:?}", payload_type)));
                                    }
                                }
                            }
                        }

                        // Execute the case body with the bound variable available
                        return eval_expr(context, e.get(param_it)?);
                    } else {
                        // No match, continue to next case
                        param_it += 2;
                        continue;
                    }
                }

                let is_match = match &case.node_type {
                    NodeType::Range => {
                        let start = eval_expr(context, &case.params[0])?;
                        if start.is_throw {
                            return Ok(start);
                        }
                        let end = eval_expr(context, &case.params[1])?;
                        if end.is_throw {
                            return Ok(end);
                        }
                        match &value_type {
                            ValueType::TCustom(s) if s == "I64" || s == "U8" => {
                                let val = result_to_switch.value.parse::<i64>();
                                let start_val = start.value.parse::<i64>();
                                let end_val = end.value.parse::<i64>();

                                if let (Ok(val), Ok(start_val), Ok(end_val)) = (val, start_val, end_val) {
                                    val >= start_val && val <= end_val
                                } else {
                                    false
                                }
                            }
                            _ => {
                                // Lexicographical comparisons for Str
                                result_to_switch.value >= start.value && result_to_switch.value <= end.value
                            }
                        }
                    }
                    _ => {
                        let result_case = eval_expr(context, &case)?;
                        if result_case.is_throw {
                            return Ok(result_case);
                        }
                        result_to_switch.value == result_case.value
                    }
                };

                param_it += 1;
                if is_match {
                    return eval_expr(context, e.get(param_it)?);
                }
                param_it += 1;
            }
            return Ok(EvalResult::new(""))
        },
        NodeType::Return => {
            if e.params.len() == 0 {
                return Ok(EvalResult::new_return(""))
            } else if e.params.len() > 1 {
                return Err(e.lang_error(&context.path, "eval", "multiple return values not implemented yet"))
            } else {
                let result = eval_expr(context, e.get(0)?)?;
                if result.is_throw {
                    return Ok(result)
                }
                return Ok(EvalResult::new_return(&result.value))
            }
        },
        NodeType::Throw => {
            if e.params.len() != 1 {
                return Err(e.lang_error(&context.path, "eval", "Throw can only return one value. This should have been caught before"))
            } else {
                let param_expr = e.get(0)?;
                let result = eval_expr(context, param_expr)?;
                if result.is_throw {
                    return Ok(result)
                }
                let thrown_type = get_value_type(context, param_expr)?;
                return Ok(EvalResult::new_throw(&result.value, thrown_type))
            }
        },
        NodeType::Catch => {
            return Err(e.lang_error(&context.path, "eval", "Catch statements should always be evaluated within bodies."))
        },
        _ => Err(e.lang_error(&context.path, "eval", &format!("Not implemented yet, found node type {:?}.", e.node_type))),
    }
}

fn eval_func_proc_call(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.node_type != NodeType::FCall {
        return Err(e.lang_error(&context.path, "eval", "eval_func_proc_call: Expected FCall node type"));
    }
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Err(e.lang_error(&context.path, "eval", "eval_func_proc_call: Expected FCall with at least one param for the Identifier")),
    };

    if context.scope_stack.lookup_struct(name).is_some() {
        // TODO allow instantiations with arguments
        let id_expr = e.get(0)?;
        if id_expr.params.len() == 0 {
            let id_name = match &id_expr.node_type {
                NodeType::Identifier(s) => s,
                _ => return Err(e.todo_error(&context.path, "eval", "Expected identifier name for struct instantiation")),
            };
            let template_offset = get_or_create_default_instance(context, &name, e)?;
            Arena::insert_struct_from_template(context, &id_name, &name, template_offset, e)?;
            // TODO FIX: Bool can't be removed yet - Bool() constructor must return "false" string, not "Bool"
            return Ok(EvalResult::new(match id_name.as_str() {
                "Bool" => "false",
                "U8" | "I64" => "0",
                "Str" => "",
                _ => id_name, // TODO Where is the struct being inserted in this case? Is this returned value even used?
            }))
        }
    }

    let combined_name = &get_combined_name(&context.path, func_expr)?;

    // Check if this is an enum constructor call (e.g., Color.Green(true))
    let parts: Vec<&str> = combined_name.split('.').collect();
    if parts.len() == 2 {
        let enum_type = parts[0];
        if context.scope_stack.lookup_enum(enum_type).is_some() {
            // This is an enum constructor!
            let variant_name = parts[1];

            // Get the enum definition to check if this variant has a payload type
            let enum_def = context.scope_stack.lookup_enum(enum_type).unwrap();
            let variant_type = enum_def.enum_map.get(variant_name).cloned();

            match variant_type {
                Some(Some(payload_type)) => {
                    // This variant expects a payload
                    if e.params.len() < 2 {
                        return Err(e.error(&context.path, "eval", &format!("Enum constructor {}.{} expects a payload of type {}", enum_type, variant_name, value_type_to_str(&payload_type))));
                    }

                    // Evaluate the payload argument
                    let payload_expr = e.get(1)?;
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
                                            let temp_var_name = format!("__temp_str_{}", context.scope_stack.frames.last().unwrap().arena_index.len());
                                            let string_value = &payload_result.value;

                                            // Add symbol entry before calling insert_string
                                            context.scope_stack.declare_symbol(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false,
                                                is_copy: false,
                                            is_own: false,
                                            });

                                            Arena::insert_string(context, &temp_var_name, &string_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        NodeType::Identifier(name) => name.clone(),
                                        NodeType::LLiteral(Literal::Str(_)) if struct_type_name == "Str" => {
                                            // For string literals, create a temporary Str struct
                                            let temp_var_name = format!("__temp_str_{}", context.scope_stack.frames.last().unwrap().arena_index.len());
                                            let string_value = &payload_result.value;

                                            // Add symbol entry before calling insert_string
                                            context.scope_stack.declare_symbol(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false, // Temporary string is immutable
                                                is_copy: false,
                                            is_own: false,
                                            });

                                            Arena::insert_string(context, &temp_var_name, &string_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        NodeType::LLiteral(Literal::Number(_)) if struct_type_name == "I64" => {
                                            // For I64 literals, create a temporary I64 struct
                                            let temp_var_name = format!("__temp_i64_{}", context.scope_stack.frames.last().unwrap().arena_index.len());
                                            let i64_value = &payload_result.value;

                                            // Add symbol entry before calling insert_i64
                                            context.scope_stack.declare_symbol(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("I64".to_string()),
                                                is_mut: false,
                                                is_copy: false,
                                            is_own: false,
                                            });

                                            Arena::insert_i64(context, &temp_var_name, &i64_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        _ => return Err(e.error(&context.path, "eval", &format!("Struct payload must be a variable identifier or literal, got {:?}", payload_expr.node_type))),
                                    };

                                    // Get struct offset from arena
                                    let offset = context.scope_stack.lookup_var(&struct_var_name).ok_or_else(|| {
                                        e.error(&context.path, "eval", &format!("Struct '{}' not found in arena", struct_var_name))
                                    })?;

                                    // Copy struct bytes from arena
                                    let struct_bytes = Arena::g().memory[offset..offset + struct_size].to_vec();
                                    struct_bytes
                                },
                                ValueType::TType(TTypeDef::TEnumDef) => {
                                    // Handle enum payloads
                                    // Get enum variable name from the original expression
                                    // If it's a function call (enum constructor), evaluate it first to create a temp variable
                                    let enum_var_name = match &payload_expr.node_type {
                                        NodeType::Identifier(name) if payload_expr.params.is_empty() => name.clone(),
                                        NodeType::Identifier(_) | NodeType::FCall => {
                                            // This is a nested enum constructor call (e.g., InnerEnum.ValueA(42))
                                            // Create a temporary variable to hold the result
                                            let temp_var_name = format!("__temp_enum_{}", context.scope_stack.frames.last().unwrap().arena_index.len());

                                            // Recursively evaluate the enum constructor
                                            // This could be either an FCall or an Identifier with params (like Inner.A)
                                            let nested_result = eval_expr(context, payload_expr)?;
                                            if nested_result.is_throw {
                                                return Ok(nested_result);
                                            }

                                            // Add symbol entry before calling insert_enum
                                            context.scope_stack.declare_symbol(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom(struct_type_name.clone()),
                                                is_mut: false,
                                                is_copy: false,
                                            is_own: false,
                                            });

                                            // The result is the enum variant name (e.g., "InnerEnum.ValueA")
                                            // insert_enum will use context.temp_enum_payload for the payload bytes
                                            Arena::insert_enum(context, &temp_var_name, struct_type_name, &nested_result.value, e)?;
                                            temp_var_name
                                        },
                                        _ => return Err(e.error(&context.path, "eval", &format!("Enum payload must be a variable identifier or enum constructor, got {:?}", payload_expr.node_type))),
                                    };

                                    // Get the full enum value including its payload
                                    let enum_val = Arena::get_enum(context, &enum_var_name, e)?;

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
                    context.temp_enum_payload = Some((payload_bytes, payload_type));

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
    }

    let mut new_fcall_e = e.clone();
    let func_def = match get_func_def_for_fcall_with_expr(&context, &mut new_fcall_e)? {
        Some(func_def_) => func_def_,
        None  => {
            return Err(e.lang_error(&context.path, "eval", "eval_func_proc_call: Instantiations should be handled already"))
        },
    };
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

fn eval_declaration(declaration: &Declaration, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let inner_e = e.get(0)?;
    let mut value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error(&context.path, "eval", &error_string));
        },
    };
    if declaration.value_type != ValueType::TCustom(INFER_TYPE.to_string()) {
        if declaration.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
            value_type = declaration.value_type.clone();
        } else if value_type != declaration.value_type {
            return Err(e.lang_error(&context.path, "eval", &format!("'{}' declared of type {} but initialized to type {:?}.", declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type))));
        }
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
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_copy: declaration.is_copy, is_own: declaration.is_own });
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                              &declaration.name, value_type_to_str(&declaration.value_type)))),
            }
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            match &inner_e.node_type {
                NodeType::StructDef(struct_def) => {
                    context.scope_stack.declare_struct(declaration.name.to_string(), struct_def.clone());
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_copy: declaration.is_copy, is_own: declaration.is_own });
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
                            let member_value_type = match &member_decl.value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    match get_value_type(&context, &default_value) {
                                        Ok(val_type) => val_type,
                                        Err(error_string) => {
                                            return Err(e.lang_error(&context.path, "eval", &error_string));
                                        },
                                    }
                                },
                                _ => member_decl.value_type.clone(),
                            };

                            match member_value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    return Err(e.lang_error(&context.path, "eval", &format!("Cannot infer type of '{}.{}', but it should be inferred already.",
                                                                             &declaration.name, &member_decl.name)));
                                },
                                ValueType::TCustom(ref type_name) => {
                                    let result = eval_expr(context, default_value)?;
                                    if result.is_throw {
                                        return Ok(result); // Propagate throw
                                    }
                                    let expr_result_str = result.value;
                                    // TODO FIX: Bool can't be removed yet - causes "Cannot declare 'MyStruct.associated_constant' of custom type 'Bool'" error
                                    match type_name.as_str() {
                                        "I64" | "U8" | "Bool" | "Str" => {
                                            Arena::insert_primitive(context, &combined_name, &member_value_type, &expr_result_str, e)?;
                                        },
                                        _ => {
                                            return Err(e.todo_error(&context.path, "eval", &format!("Cannot declare '{}.{}' of custom type '{}'",
                                                                                     &declaration.name,
                                                                                     &member_decl.name,
                                                                                     type_name)));
                                        },
                                    }
                                },
                                ValueType::TFunction(_) => {
                                    match &default_value.node_type {
                                        NodeType::FuncDef(func_def) => {
                                            context.scope_stack.declare_func(combined_name.to_string(), func_def.clone());
                                        },
                                        _ => {
                                            return Err(e.lang_error(&context.path, "eval", &format!("Cannot declare '{}.{}' of type '{}', expected '{}' definition.",
                                                                                     &declaration.name,
                                                                                     &member_decl.name,
                                                                                     value_type_to_str(&member_value_type),
                                                                                     value_type_to_str(&member_decl.value_type))));
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
                                                   SymbolInfo{value_type: member_decl.value_type.clone(), is_mut: member_decl.is_mut, is_copy: member_decl.is_copy, is_own: member_decl.is_own });
                        }
                    }
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
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_copy: declaration.is_copy, is_own: declaration.is_own });
                    return Ok(EvalResult::new(""))
                },

                _ => return Err(e.error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}', expected '{}' definition.",
                                                         &declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type)))),
            }
        },

        ValueType::TCustom(ref custom_type_name) => {
            // TODO FIX: Bool can't be removed yet - causes "Could not find arena index for 'false'" error for bootstrap constants
            match custom_type_name.as_str() {
                "I64" | "U8" | "Bool" | "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_copy: declaration.is_copy, is_own: declaration.is_own });
                    Arena::insert_primitive(context, &declaration.name, &value_type, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                _ => {
                    context.scope_stack.declare_symbol(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut, is_copy: declaration.is_copy, is_own: declaration.is_own });
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
                        Arena::insert_enum(context, &declaration.name, custom_type_name, enum_expr_result_str, e)?;

                    } else if custom_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        // Special case for instantiation
                        if inner_e.node_type == NodeType::FCall && inner_e.params.len() == 1 {
                            if let NodeType::Identifier(potentially_struct_name) = &inner_e.params[0].node_type {
                                if inner_e.params[0].params.is_empty() {
                                    if context.scope_stack.lookup_struct(potentially_struct_name).is_some() {
                                        let template_offset = get_or_create_default_instance(context, custom_type_name, e)?;
                                        Arena::insert_struct_from_template(context, &declaration.name, custom_type_name, template_offset, e)?;
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

                        // Bug #25 fix: mut declarations should create independent copies
                        // Exception: temporary return values can be transferred (zero-copy)
                        // Non-mut declarations can share offsets (will use 'own' keyword for transfers in future)
                        let is_temp_return_val = expr_result_str.starts_with(RETURN_INSTANCE_NAME);

                        if declaration.is_mut && !is_temp_return_val {
                            // Allocate space and copy fields for mut declaration (independent copy)
                            let template_offset = get_or_create_default_instance(context, custom_type_name, e)?;
                            Arena::insert_struct_from_template(context, &declaration.name, custom_type_name, template_offset, e)?;
                            Arena::copy_fields(context, custom_type_name, &expr_result_str, &declaration.name, e)?;
                        } else {
                            // Share offset for non-mut declaration or temp return value (zero-copy transfer)
                            if let Some(offset) = context.scope_stack.lookup_var(&expr_result_str) {
                                context.scope_stack.frames.last_mut().unwrap().arena_index.insert(declaration.name.to_string(), offset);
                            } else {
                                return Err(e.lang_error(&context.path, "eval", &format!("Could not find arena index for '{}'", expr_result_str)));
                            }
                            // Keep map_instance_fields for now as fallback for copy_fields
                            context.map_instance_fields(custom_type_name, &declaration.name, e)?;
                        }
                    } else {
                        return Err(e.error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}'. Only 'enum' and 'struct' custom types allowed.",
                                                            &declaration.name, value_type_to_str(&custom_symbol.value_type))))
                    }
                    return Ok(EvalResult::new(""))
                },
            }
        },
        ValueType::TMulti(_) => {
            return Err(e.error(&context.path, "eval", &format!("Cannot declare '{}' of type '{}'",
                                                &declaration.name, value_type_to_str(&declaration.value_type))))
        },
    }
}

fn eval_assignment(var_name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    // For field access (e.g., "v.x"), extract the base variable name
    let base_var_name = if var_name.contains('.') {
        var_name.split('.').next().unwrap()
    } else {
        var_name
    };

    let symbol_info = match context.scope_stack.lookup_symbol(base_var_name) {
        Some(sym) => sym,
        None => return Err(e.lang_error(&context.path, "eval", &format!("Symbol '{}' not found in context", base_var_name))),
    };
    if !symbol_info.is_mut && !symbol_info.is_copy && !symbol_info.is_own {
        return Err(e.lang_error(&context.path, "eval", &format!("in eval_assignment, while assigning to '{}': Assignments can only be to mut values. Offending expr: {:?}", var_name, e)));
    }
    if e.params.len() != 1 {
        return Err(e.lang_error(&context.path, "eval", &format!("in eval_assignment, while assigning to '{}': assignments must take exactly one value", var_name)));
    }

    let inner_e = e.get(0)?;
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
                    Arena::insert_primitive(context, var_name, &value_type, &expr_result_str, e)?;
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
                            Arena::insert_enum(context, var_name, &custom_type_name, &expr_result_str, e)?;
                        },
                        ValueType::TType(TTypeDef::TStructDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            Arena::copy_fields(context, custom_type_name, &expr_result_str, var_name, inner_e)?;
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
                _ => Err(e.lang_error(&context.path, "eval", &format!("Cannot assign '{}' to function type '{}'",
                                                       &var_name, value_type_to_str(&value_type)))),
            }
        },

        ValueType::TType(TTypeDef::TEnumDef) | ValueType::TMulti(_) => {
            Err(e.lang_error(&context.path, "eval", &format!("Cannot assign '{}' of type '{}'.", &var_name, value_type_to_str(&value_type))))
        },
    }
}

fn eval_identifier_expr_struct_member(name: &str, inner_name: &str, context: &mut Context, inner_e: &Expr, member_decl: &Declaration) -> Result<EvalResult, String> {
    return match member_decl.value_type {
        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = Arena::get_i64(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "U8" => {
                    let result = Arena::get_u8(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                // TODO FIX: Bool field reading uses bool_from_context to read the .data byte
                "Bool" => {
                    let result = bool_from_context(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "Str" => {
                    let result = string_from_context(context, &format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                _ => Err(inner_e.lang_error(&context.path, "eval", &format!("evaluating member '{}.{}' of custom type '{}' is not supported yet",
                                                             name, inner_name, value_type_to_str(&member_decl.value_type)))),
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
    let inner_e = e.get(0)?;
    match &inner_e.node_type {
        NodeType::Identifier(inner_name) => {
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
            let enum_val = Arena::get_enum(context, name, e)?;
            // Set temp_enum_payload so that if this enum is assigned to another variable,
            // the payload will be preserved
            if enum_val.payload.is_some() && enum_val.payload_type.is_some() {
                context.temp_enum_payload = Some((enum_val.payload.clone().unwrap(), enum_val.payload_type.clone().unwrap()));
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
                        "I64" => match Arena::get_i64(context, &current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "U8" => match Arena::get_u8(context, &current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        // TODO FIX: Bool identifier reading uses bool_from_context to get value
                        "Bool" => match bool_from_context(context, &current_name, e)? {
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
                                    let enum_val = Arena::get_enum(context, &current_name, inner_e)?;
                                    // Set temp_enum_payload so that if this enum is assigned to another variable,
                                    // the payload will be preserved
                                    if enum_val.payload.is_some() && enum_val.payload_type.is_some() {
                                        context.temp_enum_payload = Some((enum_val.payload.clone().unwrap(), enum_val.payload_type.clone().unwrap()));
                                    }
                                    return Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name)))
                                },
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    return Ok(EvalResult::new(&current_name))
                                },
                                _ => Err(inner_e.todo_error(&context.path, "eval", &format!("Cannot access '{}'. Fields of custom type '{}' not implemented", current_name, custom_type_name))),
                            }
                        },
                    }
                },
                _ => Err(e.lang_error(&context.path, "eval", &format!("Invalid type for '{}'.", current_name))),
            }
        },
        _ => Err(e.lang_error(&context.path, "eval", &format!("'{}' of type: '{}': custom types are supposed to be struct or enum, found '{}'.", name, custom_type_name, value_type_to_str(&custom_symbol.value_type)))),
    }
}

fn eval_identifier_expr(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match context.scope_stack.lookup_symbol(name) {
        Some(symbol_info) => match &symbol_info.value_type {
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                return Ok(EvalResult::new(name));
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                // let enum_def = match context.scope_stack.lookup_enum(name) {
                //     Some(def) => def,
                //     None => return Err(e.lang_error(&context.path, "eval", &format!("Enum '{}' not found in context", name))),
                // };
                let inner_e = e.get(0)?;
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        // TODO check that inner_name is in enum_def
                        // TODO check if that inner_name has an optional type
                        return Ok(EvalResult::new(&format!("{}.{}", name, inner_name)));
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
                        let val = Arena::get_i64(context, name, e)?;
                        return Ok(EvalResult::new(&val.to_string()))
                    },
                    "U8" => {
                        let val = Arena::get_u8(context, name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    // TODO FIX: Bool identifier evaluation uses bool_from_context
                    "Bool" => {
                        let val = bool_from_context(context, name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Str" => {
                        if e.params.len() == 0 {
                            let val = string_from_context(context, name, e)?;
                            return Ok(EvalResult::new(&val.to_string()));
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
                    let var_expr = &stmt.params[0];
                    let var_name = match &var_expr.node_type {
                        NodeType::Identifier(name) => name,
                        _ => return Err(stmt.lang_error(&context.path, "eval", "Catch variable must be an identifier")),
                    };
                    let type_expr = &stmt.params[1];
                    let type_name = match &type_expr.node_type {
                        NodeType::Identifier(name) => name,
                        _ => return Err(stmt.lang_error(&context.path, "eval", "Catch type must be an identifier")),
                    };
                    if let Some(thrown_type) = &throw_result.thrown_type {
                        if type_name == thrown_type {
                            // Bind the error variable to the caught error value
                            context.scope_stack.declare_symbol(var_name.to_string(), SymbolInfo {
                                value_type: ValueType::TCustom(thrown_type.clone()),
                                is_mut: false,
                                is_copy: false,
                            is_own: false,
                            });

                            // Map instance fields for the error variable
                            // First try to find the arena index for proper field mapping
                            if let Some(offset) = context.scope_stack.lookup_var(&throw_result.value) {
                                context.scope_stack.frames.last_mut().unwrap().arena_index.insert(var_name.to_string(), offset);

                                // Copy ALL field mappings (including nested) from thrown instance to catch variable
                                // This handles both mutable and immutable fields, and nested struct fields
                                let source_prefix = format!("{}.", &throw_result.value);
                                let dest_prefix = format!("{}.", var_name);

                                let keys_to_copy: Vec<String> = context.scope_stack.frames.last().unwrap().arena_index.keys()
                                    .filter(|k| k.starts_with(&source_prefix))
                                    .cloned()
                                    .collect();
                                for src_key in keys_to_copy {
                                    if let Some(src_offset) = context.scope_stack.lookup_var(&src_key) {
                                        let dest_key = src_key.replacen(&source_prefix, &dest_prefix, 1);
                                        context.scope_stack.frames.last_mut().unwrap().arena_index.insert(dest_key, src_offset);
                                    }
                                }

                                // Also copy symbol mappings for all fields
                                let symbol_keys_to_copy = context.scope_stack.get_symbols_with_prefix(&source_prefix);
                                for src_key in symbol_keys_to_copy {
                                    if let Some(src_symbol) = context.scope_stack.lookup_symbol(&src_key) {
                                        let dest_key = src_key.replacen(&source_prefix, &dest_prefix, 1);
                                        context.scope_stack.declare_symbol(dest_key, src_symbol.clone());
                                    }
                                }
                            } else {
                                // Fallback: try to map fields from the thrown value or type
                                // This happens when throwing inline struct constructors or when arena_index lookup fails

                                // Special handling for Str: when throwing a string literal, we need to create a proper Str struct
                                if thrown_type == "Str" {
                                    // The thrown value is the actual string content, not a struct instance name
                                    // Create a proper Str struct for the catch variable
                                    Arena::insert_string(context, var_name, &throw_result.value, stmt)?;
                                } else if let Some(struct_def) = context.scope_stack.lookup_struct(thrown_type) {
                                    let source_name = &throw_result.value;
                                    // Clone the members to avoid borrow conflict
                                    let members = struct_def.members.clone();

                                    // Register the base variable first
                                    if let Some(base_offset) = context.scope_stack.lookup_var(source_name) {
                                        context.scope_stack.frames.last_mut().unwrap().arena_index.insert(
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
                                                is_copy: false,
                                            is_own: false,
                                            },
                                        );

                                        // Copy arena_index entry for the field
                                        // Try instance field first, then fall back to type field
                                        if let Some(offset) = context.scope_stack.lookup_var(&src_instance_field) {
                                            context.scope_stack.frames.last_mut().unwrap().arena_index.insert(dst_field.clone(), offset);
                                        } else if let Some(offset) = context.scope_stack.lookup_var(&src_type_field) {
                                            context.scope_stack.frames.last_mut().unwrap().arena_index.insert(dst_field.clone(), offset);
                                        }
                                    }
                                }
                            }

                            let body_expr = &stmt.params[2];
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

                            if result.is_return {
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
                if result.is_return {
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

fn eval_user_func_proc_call(func_def: &SFuncDef, name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
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
        arena_index: std::collections::HashMap::new(),
        symbols: std::collections::HashMap::new(),
        funcs: std::collections::HashMap::new(),
        enums: std::collections::HashMap::new(),
        structs: std::collections::HashMap::new(),
        scope_type: ScopeType::Function,
    };
    let saved_path = context.path.clone();
    validate_func_arg_count(&context.path, e, name, func_def)?;

    let mut param_index = 1;
    let mut mut_args: Vec<(String, String, ValueType, bool)> = Vec::new(); // (arg_name, source_name, type, is_pass_by_ref)
    let mut pass_by_ref_params: std::collections::HashSet<String> = std::collections::HashSet::new(); // Track which params used pass-by-ref
    let mut params_consumed = false;

    for arg in &func_def.args {
        if !params_consumed {
        function_frame.symbols.insert(arg.name.to_string(), SymbolInfo {value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own });
        match &arg.value_type {
            ValueType::TMulti(ref multi_value_type) => {
                let variadic_args = &e.params[param_index..];
                let mut values = Vec::new();
                for expr in variadic_args {
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
                    is_copy: arg.is_copy,
                    is_own: arg.is_own,
                });
                Arena::insert_array_into_frame(context, &mut function_frame, &arg.name, &multi_value_type, &values, e)?;

                // We've consumed all remaining parameters, break out of loop
                params_consumed = true;
            },
            ValueType::TCustom(ref custom_type_name) => {
                let current_arg = e.get(param_index)?;

                // Special handling for Dynamic parameters: don't evaluate, just copy the value
                // When a type like I64, U8, Str is passed to a Dynamic/Type parameter,
                // store the type name as a string so size_of(T) and type_as_str(T) can use it
                if custom_type_name == "Dynamic" || custom_type_name == "Type" {
                    if let NodeType::Identifier(id_name) = &current_arg.node_type {
                        if let Some(sym) = context.scope_stack.lookup_symbol(id_name) {
                            if let ValueType::TType(_) = &sym.value_type {
                                // This is a type identifier - store the type name as a string
                                function_frame.symbols.insert(arg.name.clone(), SymbolInfo {
                                    value_type: ValueType::TCustom("Str".to_string()),
                                    is_mut: false,
                                    is_copy: false,
                                is_own: false,
                                });
                                Arena::insert_string_into_frame(context, &mut function_frame, &arg.name, id_name, e)?;
                                param_index += 1;
                                continue; // Skip eval_expr for this parameter
                            }
                        }
                    }
                    // If it's not a type identifier, fall through to normal evaluation
                }

                // If this is an enum argument and current_arg is an identifier, get the enum value to preserve payload
                let enum_payload_backup = if let NodeType::Identifier(id_name) = &current_arg.node_type {
                    if let Some(sym) = context.scope_stack.lookup_symbol(id_name) {
                        if let ValueType::TCustom(arg_type_name) = &sym.value_type {
                            if let Some(type_sym) = context.scope_stack.lookup_symbol(arg_type_name) {
                                if type_sym.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                    // This is an enum variable, get its value to preserve payload
                                    match Arena::get_enum(context, id_name, e) {
                                        Ok(enum_val) => {
                                            if enum_val.payload.is_some() && enum_val.payload_type.is_some() {
                                                Some((enum_val.payload.clone().unwrap(), enum_val.payload_type.clone().unwrap()))
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
                let result_str = result.value;

                // Restore enum payload if we saved it
                if let Some(payload_data) = enum_payload_backup {
                    context.temp_enum_payload = Some(payload_data);
                }

                // Resolve Dynamic/Type to actual type first
                let custom_type_name = &match custom_type_name.as_str() {
                    "Dynamic" | "Type" => value_type_to_str(&get_value_type(context, &current_arg)?),
                    _ => custom_type_name.clone(),
                };

                // Create resolved ValueType for the parameter
                let resolved_value_type = ValueType::TCustom(custom_type_name.clone());

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
                            mut_args.push((arg.name.clone(), full_id, ValueType::TCustom(custom_type_name.clone()), false)); // Not pass-by-ref yet, will be set later
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
                        // Transfer arena offset from caller to function frame
                        if let Some(offset) = context.scope_stack.lookup_var(source_var) {
                            function_frame.arena_index.insert(arg.name.clone(), offset);

                            // Transfer all related entries (for structs with fields, strings with metadata, etc.)
                            let prefix = format!("{}.", source_var);
                            let keys_to_transfer: Vec<String> = context.scope_stack.frames.last().unwrap().arena_index.keys()
                                .filter(|k| k.starts_with(&prefix))
                                .cloned()
                                .collect();

                            for key in &keys_to_transfer {
                                if let Some(field_offset) = context.scope_stack.lookup_var(key) {
                                    let new_key = key.replace(source_var, &arg.name);
                                    function_frame.arena_index.insert(new_key.clone(), field_offset);
                                    // Also transfer symbol info for fields
                                    if let Some(field_sym) = context.scope_stack.lookup_symbol(key) {
                                        function_frame.symbols.insert(new_key.clone(), field_sym.clone());
                                    }
                                }
                            }

                            // Note: register_struct_fields_for_typecheck done after frame is pushed

                            // Remove from caller's context (ownership transferred)
                            context.scope_stack.remove_var(source_var);
                            context.scope_stack.remove_symbol(source_var);
                            for key in &keys_to_transfer {
                                context.scope_stack.remove_var(key);
                                context.scope_stack.remove_symbol(key);
                            }

                            param_index += 1;
                            continue; // Skip normal allocation logic
                        }
                    }
                    // If not an identifier, fall through to copy like const/mut do
                }

                // Phase 3: Pass-by-reference for non-copy, non-own, non-Type parameters
                // If argument is a variable (identifier), share arena offset instead of copying
                // Note: Type parameters need copy semantics for type name storage, so skip them
                // Note: Dynamic parameters NOW use pass-by-reference (including mut Dynamic)
                // Note: own parameters are handled separately above and should not fall through here
                // Works for ALL types thanks to field offset refactoring (commit 2b9d08d):
                // - Only base offset stored in arena_index
                // - Field offsets calculated dynamically from struct definitions
                // - Inline memory layout means sharing base offset shares all fields
                if !arg.is_copy && !arg.is_own && custom_type_name != "Type" {
                    if let NodeType::Identifier(source_var) = &current_arg.node_type {
                        // Only share offset for SIMPLE identifiers (no field access, no params)
                        // Field access like s.cap is also an Identifier node but has params
                        if current_arg.params.is_empty() {
                            // Share arena offset from caller context (zero-copy pass-by-reference)
                            if let Some(offset) = context.scope_stack.lookup_var(source_var) {
                            // Create symbol info for parameter using the resolved type
                            let param_symbol = SymbolInfo {
                                value_type: resolved_value_type.clone(),
                                is_mut: arg.is_mut,
                                is_copy: arg.is_copy,
                                is_own: arg.is_own,
                            };
                            function_frame.symbols.insert(arg.name.clone(), param_symbol);
                            function_frame.arena_index.insert(arg.name.clone(), offset);

                            // CRITICAL: Copy all nested field offsets AND symbols from ALL frames to callee
                            // insert_struct registers nested field offsets (e.g., "l.start.x")
                            // We need to copy these so field access works in the callee
                            // Must search ALL frames because globals like `true` are in frame 0
                            let prefix = format!("{}.", source_var);
                            let replacement_prefix = format!("{}.", arg.name);
                            let mut field_offsets_to_copy = Vec::new();
                            let mut field_symbols_to_copy = Vec::new();
                            for caller_frame in context.scope_stack.frames.iter() {
                                for (key, &value) in caller_frame.arena_index.iter() {
                                    if key.starts_with(&prefix) {
                                        let new_key = key.replacen(&prefix, &replacement_prefix, 1);
                                        field_offsets_to_copy.push((new_key, value));
                                    }
                                }
                                for (key, value) in caller_frame.symbols.iter() {
                                    if key.starts_with(&prefix) {
                                        let new_key = key.replacen(&prefix, &replacement_prefix, 1);
                                        field_symbols_to_copy.push((new_key, value.clone()));
                                    }
                                }
                            }
                            for (key, value) in field_offsets_to_copy {
                                function_frame.arena_index.insert(key, value);
                            }
                            for (key, value) in field_symbols_to_copy {
                                function_frame.symbols.insert(key, value);
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

                match custom_type_name.as_str() {
                    "I64" => {
                        Arena::insert_i64_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    "U8" => {
                        Arena::insert_u8_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    // TODO FIX: Bool function argument uses insert_bool helper
                    "Bool" => {
                        Arena::insert_bool_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    "Str" => {
                        Arena::insert_string_into_frame(context, &mut function_frame, &arg.name, &result_str, e)?;
                    },
                    _ => {
                        let custom_symbol = context.scope_stack.lookup_symbol(custom_type_name).ok_or_else(|| {
                            return e.lang_error(&context.path, "eval", &format!( "Undefined symbol for custom type '{}'", custom_type_name))
                        })?;
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                // Transfer payload from outer context if present (temp_enum_payload already on context)
                                Arena::insert_enum_into_frame(context, &mut function_frame, &arg.name, &custom_type_name, &result_str, e)?;
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
                                        // If source and dest have the same name, we need to save the source offsets
                                        // before insert_struct overwrites them
                                        let (saved_offsets, temp_src_key) = if id_ == &arg.name {
                                            let mut offsets = Vec::new();

                                            // Save all arena_index entries that start with the struct name
                                            // This includes the base offset and all nested field offsets
                                            let prefix = format!("{}.", id_);
                                            for (key, offset) in context.scope_stack.frames.last().unwrap().arena_index.iter() {
                                                if key == id_ || key.starts_with(&prefix) {
                                                    offsets.push((key.clone(), *offset));
                                                }
                                            }

                                            (Some(offsets), Some(format!("__temp_src_{}", id_)))
                                        } else {
                                            (None, None)
                                        };

                                        // For pass-by-reference (non-copy, non-own, non-Type), just share the offset
                                        if !arg.is_copy && !arg.is_own && custom_type_name != "Type" {
                                            let src_offset = if let Some(offset) = context.scope_stack.lookup_var(id_) {
                                                offset
                                            } else if id_.contains('.') {
                                                // Field path - calculate offset dynamically
                                                context.get_field_offset( id_)
                                                    .map_err(|err| e.lang_error(&context.path, "eval", &format!("Pass-by-reference: {}", err)))?
                                            } else {
                                                return Err(e.lang_error(&context.path, "eval", &format!("Source struct '{}' not found in caller context arena_index", id_)))
                                            };

                                            // Create symbol for parameter
                                            function_frame.symbols.insert(arg.name.clone(), SymbolInfo {
                                                value_type: resolved_value_type.clone(),
                                                is_mut: arg.is_mut,
                                                is_copy: arg.is_copy,
                                                is_own: arg.is_own,
                                            });

                                            // Share the offset (pass-by-reference)
                                            function_frame.arena_index.insert(arg.name.clone(), src_offset);

                                            // Copy nested field offsets (e.g., "o1.inner_vec._len" -> "self._len")
                                            // Must search ALL frames because globals like `true` are in frame 0
                                            let prefix = format!("{}.", id_);
                                            let replacement_prefix = format!("{}.", arg.name);
                                            let mut field_offsets_to_copy = Vec::new();
                                            let mut field_symbols_to_copy = Vec::new();
                                            for caller_frame in context.scope_stack.frames.iter() {
                                                for (key, &value) in caller_frame.arena_index.iter() {
                                                    if key.starts_with(&prefix) {
                                                        let new_key = key.replacen(&prefix, &replacement_prefix, 1);
                                                        field_offsets_to_copy.push((new_key, value));
                                                    }
                                                }
                                                for (key, value) in caller_frame.symbols.iter() {
                                                    if key.starts_with(&prefix) {
                                                        let new_key = key.replacen(&prefix, &replacement_prefix, 1);
                                                        field_symbols_to_copy.push((new_key, value.clone()));
                                                    }
                                                }
                                            }
                                            for (key, value) in field_offsets_to_copy {
                                                function_frame.arena_index.insert(key, value);
                                            }
                                            for (key, value) in field_symbols_to_copy {
                                                function_frame.symbols.insert(key, value);
                                            }

                                            // Track that this was passed by reference
                                            pass_by_ref_params.insert(arg.name.clone());
                                        } else {
                                            // For copy parameters, allocate and copy
                                            let template_offset = get_or_create_default_instance(context, &custom_type_name, e)?;
                                            Arena::insert_struct_from_template_into_frame(context, &mut function_frame, &arg.name, &custom_type_name, template_offset, e)?;

                                            // Push frame temporarily for copy_fields (needs dest accessible)
                                            context.scope_stack.frames.push(function_frame);

                                            // If we saved offsets, restore them with temp keys for copy_fields
                                            if let (Some(offsets), Some(temp_key)) = (saved_offsets, temp_src_key) {
                                                for (orig_key, offset) in offsets.iter() {
                                                    let new_key = if orig_key == id_ {
                                                        temp_key.clone()
                                                    } else if orig_key.starts_with(&format!("{}.", id_)) {
                                                        format!("{}{}", temp_key, &orig_key[id_.len()..])
                                                    } else {
                                                        orig_key.clone()
                                                    };
                                                    context.scope_stack.frames.last_mut().unwrap().arena_index.insert(new_key, *offset);
                                                }

                                                Arena::copy_fields(context, &custom_type_name, &temp_key, &arg.name, e)?;

                                                // Clean up temp keys
                                                for (orig_key, _) in offsets.iter() {
                                                    let new_key = if orig_key == id_ {
                                                        temp_key.clone()
                                                    } else if orig_key.starts_with(&format!("{}.", id_)) {
                                                        format!("{}{}", temp_key, &orig_key[id_.len()..])
                                                    } else {
                                                        orig_key.clone()
                                                    };
                                                    context.scope_stack.remove_var(&new_key);
                                                }
                                            } else {
                                                // Temporarily register source struct's base offset and symbol
                                                // so that copy_fields() can calculate field offsets dynamically
                                                let src_offset = if let Some(offset) = context.scope_stack.lookup_var(id_) {
                                                    offset
                                                } else if id_.contains('.') {
                                                    // Field path - calculate offset dynamically
                                                    context.get_field_offset( id_)
                                                        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Pass-by-copy: {}", err)))?
                                                } else {
                                                    return Err(e.lang_error(&context.path, "eval", &format!("Source struct '{}' not found in caller context arena_index", id_)))
                                                };
                                                let src_symbol = context.scope_stack.lookup_symbol(id_).cloned()
                                                    .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("Source struct '{}' not found in caller context symbols", id_)))?;

                                                context.scope_stack.frames.last_mut().unwrap().arena_index.insert(id_.clone(), src_offset);
                                                context.scope_stack.declare_symbol(id_.clone(), src_symbol);
                                                Arena::copy_fields(context, &custom_type_name, &id_, &arg.name, e)?;
                                                context.scope_stack.remove_var(id_);
                                                context.scope_stack.remove_symbol(id_);
                                            }

                                            // Pop frame back for remaining arg processing
                                            function_frame = context.scope_stack.frames.pop().unwrap();
                                        }
                                    },
                                    _ => {
                                        // For expression arguments (like Vec.new(Expr)), the struct is already
                                        // allocated and evaluated in result_str. We need to copy it to the parameter.
                                        let template_offset = get_or_create_default_instance(context, &custom_type_name, e)?;
                                        Arena::insert_struct_from_template_into_frame(context, &mut function_frame, &arg.name, &custom_type_name, template_offset, e)?;

                                        // Push frame temporarily for copy_fields
                                        context.scope_stack.frames.push(function_frame);

                                        // Temporarily register source for copy_fields
                                        let src_offset = context.scope_stack.lookup_var(&source_id)
                                            .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("Source '{}' not found in caller context", source_id)))?;
                                        let src_symbol = context.scope_stack.lookup_symbol(&source_id).cloned()
                                            .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("Source symbol '{}' not found", source_id)))?;

                                        context.scope_stack.frames.last_mut().unwrap().arena_index.insert(source_id.clone(), src_offset);
                                        context.scope_stack.declare_symbol(source_id.clone(), src_symbol);
                                        Arena::copy_fields(context, &custom_type_name, &source_id, &arg.name, e)?;
                                        context.scope_stack.remove_var(&source_id);
                                        context.scope_stack.remove_symbol(&source_id);

                                        // Pop frame back for remaining arg processing
                                        function_frame = context.scope_stack.frames.pop().unwrap();

                                        // For own parameters, remove the source from caller's context (ownership transferred)
                                        if arg.is_own {
                                            context.scope_stack.remove_var(&source_id);
                                            context.scope_stack.remove_symbol(&source_id);
                                            // Also remove field entries
                                            let prefix = format!("{}.", &source_id);
                                            let keys_to_remove: Vec<String> = context.scope_stack.frames.last().unwrap().arena_index.keys()
                                                .filter(|k| k.starts_with(&prefix))
                                                .cloned()
                                                .collect();
                                            for key in keys_to_remove {
                                                context.scope_stack.remove_var(&key);
                                                context.scope_stack.remove_symbol(&key);
                                            }
                                        }
                                    },
                                }
                            },
                            _ => {
                                return Err(e.lang_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as an argument. Custom types can only be struct or enum.",
                                                                         &arg.name, &custom_type_name)))
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
        // When throwing from a method, we need to copy the thrown struct's arena_index entries
        // from the function frame to the caller frame so that catch blocks can access fields
        if let Some(thrown_type_name) = &result.thrown_type {
            // Check if this is a custom type (struct)
            if let Some(type_symbol) = context.scope_stack.lookup_symbol(thrown_type_name) {
                if type_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                    // Copy the base variable entry first (from function frame to caller frame)
                    if let Some(base_offset) = context.scope_stack.lookup_var(&result.value) {
                        // Get the second-to-last frame (caller's frame)
                        let frame_count = context.scope_stack.frames.len();
                        if frame_count >= 2 {
                            context.scope_stack.frames[frame_count - 2].arena_index.insert(
                                result.value.clone(),
                                base_offset
                            );
                        }
                    }

                    // Copy arena_index and symbol entries for the thrown instance's fields
                    let source_prefix = format!("{}.", &result.value);

                    // Copy arena_index entries (including nested fields like .msg.c_string)
                    let keys_to_copy: Vec<String> = context.scope_stack.frames.last().unwrap().arena_index.keys()
                        .filter(|k| k.starts_with(&source_prefix))
                        .cloned()
                        .collect();
                    let frame_count = context.scope_stack.frames.len();
                    for src_key in keys_to_copy {
                        if let Some(src_offset) = context.scope_stack.lookup_var(&src_key) {
                            if frame_count >= 2 {
                                context.scope_stack.frames[frame_count - 2].arena_index.insert(src_key, src_offset);
                            }
                        }
                    }

                    // Copy symbol entries for fields
                    let symbol_keys_to_copy = context.scope_stack.get_symbols_with_prefix(&source_prefix);
                    for src_key in symbol_keys_to_copy {
                        if let Some(src_symbol) = context.scope_stack.lookup_symbol(&src_key) {
                            context.scope_stack.declare_symbol(src_key, src_symbol.clone());
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
    let result_str = result.value;

    // Save struct/enum return value info BEFORE popping (needed for return handling)
    let saved_return_offset: Option<usize> = if func_def.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.return_types[0] {
            match custom_type_name.as_str() {
                "I64" | "U8" | "Bool" | "Str" => None,
                _ => context.scope_stack.lookup_var(&result_str),
            }
        } else {
            None
        }
    } else {
        None
    };

    // Save enum value if returning an enum variable (not constructor)
    let saved_enum_value: Option<EnumVal> = if func_def.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.return_types[0] {
            if let Some(custom_symbol) = context.scope_stack.lookup_symbol(custom_type_name) {
                if custom_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                    if !result_str.contains('.') {
                        // This is a variable, not a constructor - save the enum value
                        Arena::get_enum(context, &result_str, e).ok()
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
    enum MutArgValue {
        I64(i64),
        U8(u8),
        Str(String),
        Enum(EnumVal),
        Struct { offset: usize, type_name: String, was_passed_by_ref: bool },
    }
    let mut collected_mut_args: Vec<(String, MutArgValue)> = Vec::new();

    for (arg_name, source_name, value_type, _) in &mut_args {
        let was_passed_by_ref = pass_by_ref_params.contains(arg_name);
        match value_type {
            ValueType::TCustom(ref type_name) if type_name == "I64" => {
                let val = Arena::get_i64(context, arg_name, e)?;
                collected_mut_args.push((source_name.clone(), MutArgValue::I64(val)));
            },
            ValueType::TCustom(ref type_name) if type_name == "U8" => {
                let val = Arena::get_u8(context, arg_name, e)?;
                collected_mut_args.push((source_name.clone(), MutArgValue::U8(val)));
            },
            ValueType::TCustom(ref type_name) if type_name == "Str" => {
                let val = string_from_context(context, arg_name, e)?;
                collected_mut_args.push((source_name.clone(), MutArgValue::Str(val)));
            },
            ValueType::TCustom(ref type_name) => {
                let symbol_info = match context.scope_stack.lookup_symbol(type_name) {
                    Some(symbol_info_) => symbol_info_.clone(),
                    None => {
                        context.scope_stack.frames.pop();
                        context.path = saved_path;
                        return Err(e.lang_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as an mut argument. Undefined symbol.", arg_name, type_name)))
                    },
                };
                match &symbol_info.value_type {
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        let val = Arena::get_enum(context, arg_name, e)?;
                        collected_mut_args.push((source_name.clone(), MutArgValue::Enum(val)));
                    },
                    ValueType::TType(TTypeDef::TStructDef) => {
                        if let Some(offset) = context.scope_stack.lookup_var(arg_name) {
                            collected_mut_args.push((source_name.clone(), MutArgValue::Struct {
                                offset,
                                type_name: type_name.clone(),
                                was_passed_by_ref,
                            }));
                        } else {
                            context.scope_stack.frames.pop();
                            context.path = saved_path;
                            return Err(e.lang_error(&context.path, "eval", &format!("Missing struct arena index for argument '{}'", arg_name)));
                        }
                    },
                    _ => {
                        context.scope_stack.frames.pop();
                        context.path = saved_path;
                        return Err(e.lang_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Not an enum or struct, but a '{}'.",
                                                                 arg_name, type_name, value_type_to_str(&symbol_info.value_type))))
                    },
                }

            },
            _ => {
                context.scope_stack.frames.pop();
                context.path = saved_path;
                return Err(e.todo_error(&context.path, "eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Only structs and enums allowed for now.",
                                                         arg_name, value_type_to_str(value_type))))
            }
        }
    }

    // Pop function frame BEFORE writing mut args back to caller
    context.scope_stack.frames.pop();
    context.path = saved_path.clone();

    // Write collected mut_args values to caller's frame (now on top)
    for (source_name, value) in collected_mut_args {
        match value {
            MutArgValue::I64(val) => {
                Arena::insert_i64(context, &source_name, &val.to_string(), e)?;
            },
            MutArgValue::U8(val) => {
                Arena::insert_u8(context, &source_name, &val.to_string(), e)?;
            },
            MutArgValue::Str(val) => {
                Arena::insert_string(context, &source_name, &val, e)?;
            },
            MutArgValue::Enum(val) => {
                Arena::insert_enum(context, &source_name, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name), e)?;
            },
            MutArgValue::Struct { offset, type_name, was_passed_by_ref } => {
                context.scope_stack.frames.last_mut().unwrap().arena_index.insert(source_name.to_string(), offset);
                if !was_passed_by_ref {
                    context.map_instance_fields(&type_name, &source_name, e)?;
                }
            },
        }
    }

    // If function returns a user-defined struct or enum, copy it back to caller frame as temp return val
    // NOTE: Frame already popped above, using saved_return_offset and saved_enum_value
    if func_def.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.return_types[0] {
            // Skip core types like I64, Bool, String, U8
            match custom_type_name.as_str() {
                "I64" | "U8" | "Bool" | "Str" => { /* Do nothing for core types */ },
                _ => {

                    if let Some(custom_symbol) = context.scope_stack.lookup_symbol(custom_type_name) {
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                let return_instance = format!("{}{}", RETURN_INSTANCE_NAME, Arena::g().temp_id_counter);
                                Arena::g().temp_id_counter += 1;

                                // Use saved offset (saved before popping)
                                let offset = saved_return_offset.ok_or_else(|| {
                                    e.lang_error(&context.path, "eval", &format!("Missing arena index for return value '{}'", result_str))
                                })?;

                                // Insert the temporary return variable into the caller's frame
                                context.scope_stack.declare_symbol(return_instance.to_string(), SymbolInfo {
                                    value_type: ValueType::TCustom(custom_type_name.to_string()),
                                    is_mut: true,
                                    is_copy: false,
                                    is_own: false,
                                });

                                // Share the base offset in caller's frame
                                context.scope_stack.frames.last_mut().unwrap().arena_index.insert(return_instance.to_string(), offset);

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

                                let return_instance = format!("{}{}", RETURN_INSTANCE_NAME, Arena::g().temp_id_counter);
                                Arena::g().temp_id_counter += 1;

                                // Set temp_enum_payload if the enum has a payload
                                if let (Some(payload_data), Some(payload_type)) = (val.payload, val.payload_type) {
                                    context.temp_enum_payload = Some((payload_data, payload_type));
                                }

                                Arena::insert_enum(context, &return_instance, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name), e)?;
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
    return Ok(EvalResult::new(&result_str)) // CLEANUP SITE 7: Return normal value (final return)
}

// ---------- Core function/procedure dispatcher

fn eval_core_func_proc_call(name: &str, context: &mut Context, e: &Expr, is_proc: bool) -> Result<EvalResult, String> {
    return match name {
        "loc" => ext::func_loc(context, e),
        "_file" => ext::func_file(context, e),
        "_line" => ext::func_line(context, e),
        "_col" => ext::func_col(context, e),
        "size_of" => ext::func_size_of(context, &e),
        "type_as_str" => ext::func_type_as_str(context, &e),
        "to_ptr" => ext::func_to_ptr(context, &e),
        "malloc" => ext::func_malloc(context, &e),
        "free" => ext::func_free(context, &e),
        "memset" => ext::func_memset(context, &e),
        "memcpy" => ext::func_memcpy(context, &e),
        "memcmp" => ext::func_memcmp(context, &e),
        "lt" => ext::func_lt(context, &e),
        "gt" => ext::func_gt(context, &e),
        "add" => ext::func_add(context, &e),
        "sub" => ext::func_sub(context, &e),
        "mul" => ext::func_mul(context, &e),
        "div" => ext::func_div(context, &e),
        "mod" => ext::func_mod(context, &e),
        "str_to_i64" => ext::func_str_to_i64(context, &e),
        "i64_to_str" => ext::func_i64_to_str(context, &e),
        "enum_to_str" => ext::func_enum_to_str(context, &e),
        "u8_to_i64" => ext::func_u8_to_i64(context, &e),
        "i64_to_u8" => ext::func_i64_to_u8(context, &e),
        "eval_to_str" => ext::proc_eval_to_str(context, &e),
        "exit" => ext::func_exit(context, &e),
        "import" => ext::proc_import(context, &e),
        "input_read_line" => ext::proc_input_read_line(context, &e),
        "single_print" => ext::proc_single_print(context, &e),
        "print_flush" => ext::proc_print_flush(context, &e),
        "readfile" => ext::proc_readfile(context, &e),
        "run_cmd" => ext::proc_run_cmd(context, &e),
        "runfile" => ext::proc_runfile(context, &e),
        "has_const" => ext::func_has_const(context, &e),
        "has_field" => ext::func_has_field(context, &e),
        _ => {
            if is_proc {
                Err(e.lang_error(&context.path, "eval", &format!("Core procedure '{}' not implemented.", name)))
            } else {
                Err(e.lang_error(&context.path, "eval", &format!("Core function '{}' not implemented.", name)))
            }
        },
    }
}

