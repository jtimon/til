use crate::rs::init::{Context, SymbolInfo};
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, Literal, ValueType, TTypeDef, Declaration, PatternInfo, FunctionType, SFuncDef,
    value_type_to_str, get_combined_name,
};
use std::io;
use std::io::{ErrorKind, Write};
use std::fs;
use crate::{main_run, run_file, run_file_with_context};

// Interpreter/Eval phase: Runtime evaluation and execution
// This module handles the eval phase that runs after type checking.
// Manages arena, memory allocation, and actual program execution.

const RETURN_INSTANCE_NAME : &str = "___temp_return_val_";

pub struct Arena {
    pub memory: Vec<u8>,
    pub temp_id_counter: usize,
}

// heap/arena memory (starts at 1 to avoid NULL confusion)
// REM: first address 0 is reserved (invalid), malloc always >0
impl Arena {
    // This function gives access to the singleton instance of Arena
    #[allow(static_mut_refs)]
    pub fn g() -> &'static mut Arena {
        unsafe { // TODO research if we can do "safe" singletons in rust before self hosting, just out of curiosity
            static mut INSTANCE: Option<Arena> = None;

            // Lazy initialization of the singleton instance
            INSTANCE.get_or_insert_with(|| Arena {
                memory: vec![0], // REM: first address 0 is reserved (invalid), malloc always >0
                temp_id_counter: 0, // A temporary ugly hack for return values
            })
        }
    }
}

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

pub fn eval_expr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match &e.node_type {
        NodeType::Body => eval_body(context, &e.params),
        NodeType::LLiteral(Literal::Bool(lbool)) => Ok(EvalResult::new(lbool)),
        NodeType::LLiteral(Literal::Number(li64)) => Ok(EvalResult::new(li64)),
        NodeType::LLiteral(Literal::Str(lstring)) => Ok(EvalResult::new(lstring)),
        NodeType::LLiteral(Literal::List(llist)) => Ok(EvalResult::new(llist)),
        NodeType::FCall => {
            let f_name = crate::rs::init::get_func_name_in_call(&e);
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
            if e.params.len() != 2 && e.params.len() != 3 {
                return Err(e.lang_error("eval", "if nodes must have 2 or 3 parameters."))
            }
            let cond_expr = e.get(0)?;
            let result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond)
            }
            if result_cond.value.parse::<bool>().map_err(
                |err| cond_expr.lang_error("eval", &format!("Expected bool, got '{}': {}", result_cond.value, err)))? {
                return eval_expr(context, e.get(1)?)
            } else if e.params.len() == 3 {
                return eval_expr(context, e.get(2)?)
            } else {
                return Ok(EvalResult::new(""))
            }
        },
        NodeType::While => {
            if e.params.len() != 2 {
                return Err(e.lang_error("eval", "while nodes must have exactly 2 parameters."))
            }
            let mut cond_expr = e.get(0)?;
            let mut result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond.clone())
            }
            while result_cond.value.parse::<bool>().map_err(
                |err| cond_expr.lang_error("eval", &format!("Expected bool, got '{}': {}", result_cond.value, err)))? {
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
                return Err(e.lang_error("eval", "switch nodes must have at least 3 parameters."));
            }
            let to_switch = e.get(0)?;
            let value_type = crate::rs::init::get_value_type(&context, &to_switch)?;
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

                let case_type = crate::rs::init::get_value_type(&context, &case)?;
                let vt_str = value_type_to_str(&value_type);
                let ct_str = value_type_to_str(&case_type);
                if ct_str != vt_str && ct_str != format!("{}Range", vt_str) {
                    return Err(e.lang_error("eval", &format!("switch value type {:?}, case value type {:?}", value_type, case_type)));
                }

                // Handle pattern matching with payload extraction
                if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case.node_type {
                    // Check if the switch value's enum variant matches the pattern
                    // The switch value should be an enum stored as EnumVal
                    // We need to extract the enum value - get the identifier name from to_switch
                    let enum_var_name = if let NodeType::Identifier(name) = &to_switch.node_type {
                        name
                    } else {
                        return Err(case.error("eval", "Pattern matching requires switch value to be a variable"));
                    };

                    let enum_val = context.get_enum(enum_var_name, &case)?;

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
                                match payload_type {
                                    ValueType::TCustom(type_name) if type_name == "Bool" => {
                                        if payload_bytes.len() != 1 {
                                            return Err(case.error("eval", "Invalid Bool payload size"));
                                        }
                                        let bool_val = payload_bytes[0] != 0;

                                        // First add the symbol to context
                                        context.symbols.insert(
                                            binding_var.clone(),
                                            crate::rs::init::SymbolInfo {
                                                value_type: ValueType::TCustom("Bool".to_string()),
                                                is_mut: false,
                                            }
                                        );

                                        // Now insert the value
                                        context.insert_bool(binding_var, &bool_val.to_string(), &case)?;
                                    }
                                    ValueType::TCustom(type_name) if type_name == "I64" => {
                                        if payload_bytes.len() != 8 {
                                            return Err(case.error("eval", "Invalid I64 payload size"));
                                        }
                                        let mut bytes = [0u8; 8];
                                        bytes.copy_from_slice(&payload_bytes[0..8]);
                                        let i64_val = i64::from_le_bytes(bytes);

                                        // First add the symbol to context
                                        context.symbols.insert(
                                            binding_var.clone(),
                                            crate::rs::init::SymbolInfo {
                                                value_type: ValueType::TCustom("I64".to_string()),
                                                is_mut: false,
                                            }
                                        );

                                        context.insert_i64(binding_var, &i64_val.to_string(), &case)?;
                                    }
                                    ValueType::TCustom(type_name) if type_name == "Str" => {
                                        // For Str, the payload contains pointer + size (16 bytes total)
                                        // We need to reconstruct the string from the arena
                                        if payload_bytes.len() != 16 {
                                            return Err(case.error("eval", &format!("Invalid Str payload size: expected 16, got {}", payload_bytes.len())));
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
                                        context.symbols.insert(
                                            binding_var.clone(),
                                            crate::rs::init::SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false,
                                            }
                                        );

                                        if size > 0 && ptr_offset > 0 {
                                            // Read the actual string from the global arena
                                            let ptr = ptr_offset as usize;
                                            let len = size as usize;
                                            if ptr + len > Arena::g().memory.len() {
                                                return Err(case.error("eval", "String payload pointer out of bounds"));
                                            }
                                            let str_bytes = &Arena::g().memory[ptr..ptr + len];
                                            let string_value = String::from_utf8_lossy(str_bytes).to_string();
                                            context.insert_string(binding_var, &string_value, &case)?;
                                        } else {
                                            let empty_string = String::new();
                                            context.insert_string(binding_var, &empty_string, &case)?;
                                        }
                                    }
                                    ValueType::TCustom(type_name) => {
                                        // Handle custom types (structs and enums)
                                        let type_symbol = context.symbols.get(type_name).ok_or_else(|| {
                                            case.error("eval", &format!("Unknown type '{}'", type_name))
                                        })?;

                                        match &type_symbol.value_type {
                                            ValueType::TType(TTypeDef::TStructDef) => {
                                                // Handle struct payloads
                                                // First add the symbol to context
                                                context.symbols.insert(
                                                    binding_var.clone(),
                                                    crate::rs::init::SymbolInfo {
                                                        value_type: payload_type.clone(),
                                                        is_mut: false,
                                                    }
                                                );

                                                // Allocate destination struct in arena
                                                context.insert_struct(binding_var, type_name, &case)?;

                                                // Get destination offset
                                                let dest_offset = context.arena_index.get(binding_var).ok_or_else(|| {
                                                    case.error("eval", &format!("Struct '{}' not found in arena", binding_var))
                                                })?;

                                                // Validate payload size
                                                let struct_size = context.get_type_size(type_name)
                                                    .map_err(|err| case.error("eval", &err))?;
                                                if payload_bytes.len() != struct_size {
                                                    return Err(case.error("eval", &format!(
                                                        "Payload size mismatch: expected {}, got {}",
                                                        struct_size, payload_bytes.len()
                                                    )));
                                                }

                                                // Copy payload bytes directly into arena
                                                Arena::g().memory[*dest_offset..*dest_offset + struct_size]
                                                    .copy_from_slice(&payload_bytes);
                                            },
                                            ValueType::TType(TTypeDef::TEnumDef) => {
                                                // Handle enum payloads
                                                // The payload_bytes contains: [8 bytes variant tag][N bytes enum's payload]

                                                if payload_bytes.len() < 8 {
                                                    return Err(case.error("eval", "Invalid enum payload: too small"));
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
                                                let enum_def = context.enum_defs.get(type_name).ok_or_else(|| {
                                                    case.error("eval", &format!("Enum definition for '{}' not found", type_name))
                                                })?;

                                                // Find variant name by matching the variant position
                                                let mut found_variant = None;
                                                for (name, _) in &enum_def.enum_map {
                                                    let pos = Context::get_variant_pos(enum_def, name, &case)?;
                                                    if pos == variant_pos {
                                                        found_variant = Some(name.clone());
                                                        break;
                                                    }
                                                }

                                                let variant_name = found_variant.ok_or_else(|| {
                                                    case.error("eval", &format!("Variant position {} not found in enum {}", variant_pos, type_name))
                                                })?;

                                                // Get the inner payload type
                                                let inner_payload_type = enum_def.enum_map.get(&variant_name)
                                                    .and_then(|opt| opt.clone());

                                                // Add symbol to context first
                                                context.symbols.insert(
                                                    binding_var.clone(),
                                                    crate::rs::init::SymbolInfo {
                                                        value_type: payload_type.clone(),
                                                        is_mut: false,
                                                    }
                                                );

                                                // Now reconstruct the enum and insert it
                                                let enum_val_str = format!("{}.{}", type_name, variant_name);

                                                // Set temp_enum_payload if there's an inner payload
                                                if let Some(payload_data) = inner_payload {
                                                    context.temp_enum_payload = Some((payload_data, inner_payload_type.unwrap()));
                                                }

                                                // Insert the enum
                                                context.insert_enum(binding_var, type_name, &enum_val_str, &case)?;
                                            },
                                            _ => {
                                                // Other types not yet implemented
                                                return Err(case.error("eval", &format!("Pattern matching not yet implemented for payload type: {:?}", payload_type)));
                                            }
                                        }
                                    },
                                    _ => {
                                        // Unknown types
                                        return Err(case.error("eval", &format!("Pattern matching not yet implemented for payload type: {:?}", payload_type)));
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
                return Err(e.lang_error("eval", "multiple return values not implemented yet"))
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
                return Err(e.lang_error("eval", "Throw can only return one value. This should have been caught before"))
            } else {
                let param_expr = e.get(0)?;
                let result = eval_expr(context, param_expr)?;
                if result.is_throw {
                    return Ok(result)
                }
                let thrown_type = crate::rs::init::get_value_type(context, param_expr)?;
                return Ok(EvalResult::new_throw(&result.value, thrown_type))
            }
        },
        NodeType::Catch => {
            return Err(e.lang_error("eval", "Catch statements should always be evaluated within bodies."))
        },
        _ => Err(e.lang_error("eval", &format!("Not implemented yet, found node type {:?}.", e.node_type))),
    }
}

fn eval_func_proc_call(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.node_type != NodeType::FCall {
        return Err(e.lang_error("eval", "eval_func_proc_call: Expected FCall node type"));
    }
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Err(e.lang_error("eval", "eval_func_proc_call: Expected FCall with at least one param for the Identifier")),
    };

    if context.struct_defs.contains_key(name) {
        // TODO allow instantiations with arguments
        let id_expr = e.get(0)?;
        if id_expr.params.len() == 0 {
            let id_name = match &id_expr.node_type {
                NodeType::Identifier(s) => s,
                _ => return Err(e.todo_error("eval", "Expected identifier name for struct instantiation")),
            };
            context.insert_struct(&id_name, &name, e)?;
            return Ok(EvalResult::new(match id_name.as_str() {
                "Bool" => "false",
                "U8" | "I64" => "0",
                "Str" => "",
                _ => id_name, // TODO Where is the struct being inserted in this case? Is this returned value even used?
            }))
        }
    }

    let combined_name = &get_combined_name(func_expr)?;

    // Check if this is an enum constructor call (e.g., Color.Green(true))
    let parts: Vec<&str> = combined_name.split('.').collect();
    if parts.len() == 2 {
        let enum_type = parts[0];
        if context.enum_defs.contains_key(enum_type) {
            // This is an enum constructor!
            let variant_name = parts[1];

            // Get the enum definition to check if this variant has a payload type
            let enum_def = context.enum_defs.get(enum_type).unwrap();
            let variant_type = enum_def.enum_map.get(variant_name).cloned();

            match variant_type {
                Some(Some(payload_type)) => {
                    // This variant expects a payload
                    if e.params.len() < 2 {
                        return Err(e.error("eval", &format!("Enum constructor {}.{} expects a payload of type {}", enum_type, variant_name, value_type_to_str(&payload_type))));
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
                                .map_err(|_| e.error("eval", &format!("Expected I64 payload, got '{}'", payload_result.value)))?;
                            i64_val.to_le_bytes().to_vec()
                        },
                        ValueType::TCustom(struct_type_name) => {
                            // Handle struct payloads
                            // Check if this is a struct type
                            let type_symbol = context.symbols.get(struct_type_name).ok_or_else(|| {
                                e.error("eval", &format!("Unknown type '{}'", struct_type_name))
                            })?;

                            match &type_symbol.value_type {
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    // Get struct size
                                    let struct_size = context.get_type_size(struct_type_name)
                                        .map_err(|err| e.error("eval", &err))?;

                                    // Get struct variable name from the original expression or create temporary for literals
                                    let struct_var_name = match &payload_expr.node_type {
                                        NodeType::Identifier(_name) if struct_type_name == "Str" => {
                                            // For Str payloads with identifier expressions (like t.token_str),
                                            // create a temporary Str from the evaluated result value
                                            let temp_var_name = format!("__temp_str_{}", context.arena_index.len());
                                            let string_value = &payload_result.value;

                                            // Add symbol entry before calling insert_string
                                            context.symbols.insert(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false,
                                            });

                                            context.insert_string(&temp_var_name, &string_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        NodeType::Identifier(name) => name.clone(),
                                        NodeType::LLiteral(Literal::Bool(_)) if struct_type_name == "Bool" => {
                                            // For bool literals, create a temporary Bool struct
                                            let temp_var_name = format!("__temp_bool_{}", context.arena_index.len());
                                            let bool_value = &payload_result.value;

                                            // Add symbol entry before calling insert_bool
                                            context.symbols.insert(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Bool".to_string()),
                                                is_mut: false,
                                            });

                                            context.insert_bool(&temp_var_name, &bool_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        NodeType::LLiteral(Literal::Str(_)) if struct_type_name == "Str" => {
                                            // For string literals, create a temporary Str struct
                                            let temp_var_name = format!("__temp_str_{}", context.arena_index.len());
                                            let string_value = &payload_result.value;

                                            // Add symbol entry before calling insert_string
                                            context.symbols.insert(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("Str".to_string()),
                                                is_mut: false, // Temporary string is immutable
                                            });

                                            context.insert_string(&temp_var_name, &string_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        NodeType::LLiteral(Literal::Number(_)) if struct_type_name == "I64" => {
                                            // For I64 literals, create a temporary I64 struct
                                            let temp_var_name = format!("__temp_i64_{}", context.arena_index.len());
                                            let i64_value = &payload_result.value;

                                            // Add symbol entry before calling insert_i64
                                            context.symbols.insert(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom("I64".to_string()),
                                                is_mut: false,
                                            });

                                            context.insert_i64(&temp_var_name, &i64_value.to_string(), e)?;
                                            temp_var_name
                                        },
                                        _ => return Err(e.error("eval", &format!("Struct payload must be a variable identifier or literal, got {:?}", payload_expr.node_type))),
                                    };

                                    // Get struct offset from arena
                                    let offset = context.arena_index.get(&struct_var_name).ok_or_else(|| {
                                        e.error("eval", &format!("Struct '{}' not found in arena", struct_var_name))
                                    })?;

                                    // Copy struct bytes from arena
                                    let struct_bytes = Arena::g().memory[*offset..*offset + struct_size].to_vec();
                                    struct_bytes
                                },
                                ValueType::TType(TTypeDef::TEnumDef) => {
                                    // Handle enum payloads
                                    // Get enum variable name from the original expression
                                    // If it's a function call (enum constructor), evaluate it first to create a temp variable
                                    let enum_var_name = match &payload_expr.node_type {
                                        NodeType::Identifier(name) => name.clone(),
                                        NodeType::FCall => {
                                            // This is a nested enum constructor call (e.g., InnerEnum.ValueA(42))
                                            // Create a temporary variable to hold the result
                                            let temp_var_name = format!("__temp_enum_{}", context.arena_index.len());

                                            // Get the function name from the nested enum constructor
                                            let nested_func_expr = payload_expr.params.first()
                                                .ok_or_else(|| e.error("eval", "Expected identifier in nested enum constructor"))?;
                                            let nested_name = get_combined_name(nested_func_expr)?;

                                            // Recursively evaluate the enum constructor
                                            let nested_result = eval_func_proc_call(&nested_name, context, payload_expr)?;
                                            if nested_result.is_throw {
                                                return Ok(nested_result);
                                            }

                                            // Add symbol entry before calling insert_enum
                                            context.symbols.insert(temp_var_name.clone(), SymbolInfo {
                                                value_type: ValueType::TCustom(struct_type_name.clone()),
                                                is_mut: false,
                                            });

                                            // The result is the enum variant name (e.g., "InnerEnum.ValueA")
                                            // insert_enum will use context.temp_enum_payload for the payload bytes
                                            context.insert_enum(&temp_var_name, struct_type_name, &nested_result.value, e)?;
                                            temp_var_name
                                        },
                                        _ => return Err(e.error("eval", &format!("Enum payload must be a variable identifier or enum constructor, got {:?}", payload_expr.node_type))),
                                    };

                                    // Get the full enum value including its payload
                                    let enum_val = context.get_enum(&enum_var_name, e)?;

                                    // Calculate total enum size: 8 bytes tag + payload bytes
                                    let mut enum_bytes = Vec::new();

                                    // Get the variant position
                                    let variant_pos = Context::get_variant_pos(
                                        context.enum_defs.get(struct_type_name).ok_or_else(|| {
                                            e.error("eval", &format!("Enum definition for '{}' not found", struct_type_name))
                                        })?,
                                        &enum_val.enum_name,
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
                                    return Err(e.error("eval", &format!("Unsupported payload type: {}", value_type_to_str(&payload_type))));
                                }
                            }
                        },
                        _ => {
                            return Err(e.error("eval", &format!("Unsupported payload type: {}", value_type_to_str(&payload_type))));
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
                        return Err(e.error("eval", &format!("Enum variant {}.{} does not take a payload", enum_type, variant_name)));
                    }
                },
                None => {
                    return Err(e.error("eval", &format!("Enum {} does not have variant {}", enum_type, variant_name)));
                }
            }
        }
    }

    let mut new_fcall_e = e.clone();
    let func_def = match crate::rs::typer::get_func_def_for_fcall_with_expr(&context, &mut new_fcall_e)? {
        Some(func_def_) => func_def_,
        None  => {
            return Err(e.lang_error("eval", "eval_func_proc_call: Instantiations should be handled already"))
        },
    };
    if func_def.is_ext() {
        // External/core functions are treated specially
        let is_proc = func_def.is_proc();
        let parts: Vec<&str> = combined_name.split('.').collect();
        let last_name = match parts.last() {
            Some(last_name_) => last_name_,
            None => {
                return Err(e.lang_error("eval", "Somehow function without name"))
            }
        };
        return eval_core_func_proc_call(&last_name, context, &new_fcall_e, is_proc)
    }
    return eval_user_func_proc_call(&func_def, &combined_name, context, &new_fcall_e)
}

fn eval_declaration(declaration: &Declaration, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let inner_e = e.get(0)?;
    let mut value_type = match crate::rs::init::get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error("eval", &error_string));
        },
    };
    if declaration.value_type != ValueType::TCustom(INFER_TYPE.to_string()) {
        if declaration.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
            value_type = declaration.value_type.clone();
        } else if value_type != declaration.value_type {
            return Err(e.lang_error("eval", &format!("'{}' declared of type {} but initialized to type {:?}.", declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type))));
        }
    }

    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Declarations can have only one child expression"))
    }

    match value_type {
        ValueType::TCustom(s) if s == INFER_TYPE => {
            return Err(e.lang_error("eval", &format!("'{}' declared of type '{}' but still to infer type '{}'",
                                                     declaration.name, value_type_to_str(&declaration.value_type), &s)));
        },
        ValueType::TType(TTypeDef::TEnumDef) => {
            match &inner_e.node_type {
                NodeType::EnumDef(enum_def) => {
                    context.enum_defs.insert(declaration.name.clone(), enum_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error("eval", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                              &declaration.name, value_type_to_str(&declaration.value_type)))),
            }
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            match &inner_e.node_type {
                NodeType::StructDef(struct_def) => {
                    context.struct_defs.insert(declaration.name.to_string(), struct_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    for (_, member_decl) in &struct_def.members {
                        if !member_decl.is_mut {
                            let combined_name = format!("{}.{}", declaration.name, member_decl.name);
                            let default_value = match struct_def.default_values.get(&member_decl.name) {
                                Some(_default_value) => _default_value,
                                None => {
                                    return Err(e.lang_error("eval", &format!("Struct member '{}.{}' expected to have default value.",
                                                                             &declaration.name, &member_decl.name)));
                                },
                            };
                            let member_value_type = match &member_decl.value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    match crate::rs::init::get_value_type(&context, &default_value) {
                                        Ok(val_type) => val_type,
                                        Err(error_string) => {
                                            return Err(e.lang_error("eval", &error_string));
                                        },
                                    }
                                },
                                _ => member_decl.value_type.clone(),
                            };

                            match member_value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    return Err(e.lang_error("eval", &format!("Cannot infer type of '{}.{}', but it should be inferred already.",
                                                                             &declaration.name, &member_decl.name)));
                                },
                                ValueType::TCustom(type_name) => {
                                    let result = eval_expr(context, default_value)?;
                                    if result.is_throw {
                                        return Ok(result); // Propagate throw
                                    }
                                    let expr_result_str = result.value;
                                    match type_name.as_str() {
                                        "I64" => {
                                            context.insert_i64(&combined_name, &expr_result_str, e)?;
                                        },
                                        "U8" => {
                                            context.insert_u8(&combined_name, &expr_result_str, e)?;
                                        },
                                        "Bool" => {
                                            context.insert_bool(&combined_name, &expr_result_str, e)?;
                                        },
                                        "Str" => {
                                            context.insert_string(&combined_name, &expr_result_str, e)?;
                                        },
                                        _ => {
                                            return Err(e.todo_error("eval", &format!("Cannot declare '{}.{}' of custom type '{}'",
                                                                                     &declaration.name,
                                                                                     &member_decl.name,
                                                                                     type_name)));
                                        },
                                    }
                                },
                                ValueType::TFunction(_) => {
                                    match &default_value.node_type {
                                        NodeType::FuncDef(func_def) => {
                                            context.funcs.insert(combined_name.to_string(), func_def.clone());
                                        },
                                        _ => {
                                            return Err(e.lang_error("eval", &format!("Cannot declare '{}.{}' of type '{}', expected '{}' definition.",
                                                                                     &declaration.name,
                                                                                     &member_decl.name,
                                                                                     value_type_to_str(&member_value_type),
                                                                                     value_type_to_str(&member_decl.value_type))));
                                        },
                                    }
                                },
                               _ => {
                                    return Err(e.todo_error("eval", &format!("Cannot declare '{}.{}' of type '{}'",
                                                                             &declaration.name,
                                                                             &member_decl.name,
                                                                             value_type_to_str(&member_decl.value_type))));
                                },
                            }

                            context.symbols.insert(combined_name.to_string(),
                                                   SymbolInfo{value_type: member_decl.value_type.clone(), is_mut: member_decl.is_mut});
                        }
                    }
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error("eval", &format!("Cannot declare {} of type {:?}, expected struct definition.",
                                                              &declaration.name, &declaration.value_type))),
            }
        },
        ValueType::TFunction(_) => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(declaration.name.to_string(), func_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return Ok(EvalResult::new(""))
                },

                _ => return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}', expected '{}' definition.",
                                                         &declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type)))),
            }
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_i64(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                "U8" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_u8(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                "Bool" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_bool(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_string(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                _ => {
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    let custom_symbol = match context.symbols.get(custom_type_name) {
                        Some(sym) => sym,
                        None => return Err(e.lang_error("eval", &format!("Symbol '{}' not found in context", custom_type_name))),
                    };
                    if custom_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                        let result = eval_expr(context, inner_e)?;
                        if result.is_throw {
                            return Ok(result); // Propagate throw
                        }
                        let enum_expr_result_str = &result.value;
                        context.insert_enum(&declaration.name, custom_type_name, enum_expr_result_str, e)?;

                    } else if custom_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        // Special case for instantiation
                        if inner_e.node_type == NodeType::FCall && inner_e.params.len() == 1 {
                            if let NodeType::Identifier(potentially_struct_name) = &inner_e.params[0].node_type {
                                if inner_e.params[0].params.is_empty() {
                                    if context.struct_defs.contains_key(potentially_struct_name) {
                                        context.insert_struct(&declaration.name, custom_type_name, e)?;
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
                        if let Some(offset) = context.arena_index.get(&expr_result_str) {
                            context.arena_index.insert(declaration.name.to_string(), *offset);
                        } else {
                            return Err(e.lang_error("eval", &format!("Could not find arena index for '{}'", expr_result_str)));
                        }
                        context.map_instance_fields(custom_type_name, &declaration.name, e)?;
                    } else {
                        return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}'. Only 'enum' and 'struct' custom types allowed.",
                                                            &declaration.name, value_type_to_str(&custom_symbol.value_type))))
                    }
                    return Ok(EvalResult::new(""))
                },
            }
        },
        ValueType::TMulti(_) => {
            return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}'",
                                                &declaration.name, value_type_to_str(&declaration.value_type))))
        },
    }
}

fn eval_assignment(var_name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let symbol_info = match context.symbols.get(var_name) {
        Some(sym) => sym,
        None => return Err(e.lang_error("eval", &format!("Symbol '{}' not found in context", var_name))),
    };
    if !symbol_info.is_mut {
        return Err(e.lang_error("eval", &format!("in eval_assignment, while assigning to '{}': Assignments can only be to mut values. Offending expr: {:?}", var_name, e)));
    }
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", &format!("in eval_assignment, while assigning to '{}': assignments must take exactly one value", var_name)));
    }

    let inner_e = e.get(0)?;
    let value_type = match crate::rs::init::get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error("eval", &error_string));
        },
    };
    match value_type {
        ValueType::TCustom(s) if s == INFER_TYPE => {
            return Err(e.lang_error("eval", &format!("Cannot assign {}, type should already be inferred of type '{:?}'.", &var_name, &symbol_info.value_type)));
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_i64(var_name, &expr_result_str, e)?;
                },
                "U8" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_u8(var_name, &expr_result_str, e)?;
                },
                "Bool" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_bool(var_name, &expr_result_str, e)?;
                },
                "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_string(var_name, &expr_result_str, e)?;
                },
                _ => {
                    let custom_symbol_info = match context.symbols.get(custom_type_name) {
                        Some(symbol_info) => symbol_info,
                        None => return Err(inner_e.lang_error("eval", &format!("Unknown custom type '{}'", custom_type_name))),
                    };
                    match &custom_symbol_info.value_type {
                        ValueType::TType(TTypeDef::TEnumDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            context.insert_enum(var_name, &custom_type_name, &expr_result_str, e)?;
                        },
                        ValueType::TType(TTypeDef::TStructDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            context.copy_fields(custom_type_name, &expr_result_str, var_name, inner_e)?;
                        },
                        other_value_type => {
                            return Err(inner_e.lang_error("eval", &format!("Cannot assign '{}' of custom type '{}' of value type '{}'.",
                                                                           &var_name, custom_type_name, value_type_to_str(&other_value_type))))
                        },
                    }
                },
            }
            return Ok(EvalResult::new(""))
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            return Err(e.todo_error("eval", &format!("Cannot assign '{}' of type '{}'", &var_name, value_type_to_str(&value_type))))
        },
        ValueType::TFunction(_) => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(var_name.to_string(), func_def.clone());
                    Ok(EvalResult::new(""))
                },
                _ => Err(e.lang_error("eval", &format!("Cannot assign '{}' to function type '{}'",
                                                       &var_name, value_type_to_str(&value_type)))),
            }
        },

        ValueType::TType(TTypeDef::TEnumDef) | ValueType::TMulti(_) => {
            Err(e.lang_error("eval", &format!("Cannot assign '{}' of type '{}'.", &var_name, value_type_to_str(&value_type))))
        },
    }
}

fn eval_identifier_expr_struct_member(name: &str, inner_name: &str, context: &mut Context, inner_e: &Expr, member_decl: &Declaration) -> Result<EvalResult, String> {
    return match member_decl.value_type {
        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = context.get_i64(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "U8" => {
                    let result = context.get_u8(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "Bool" => {
                    let result = context.get_bool(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "Str" => {
                    let result = context.get_string(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                _ => Err(inner_e.lang_error("eval", &format!("evaluating member '{}.{}' of custom type '{}' is not supported yet",
                                                             name, inner_name, value_type_to_str(&member_decl.value_type)))),
            }
        },
        _ => Err(inner_e.lang_error("eval", &format!("struct '{}' has no const (static) member '{}' of struct value type '{}'",
                                                     name, inner_name, value_type_to_str(&member_decl.value_type)))),
    }
}

fn eval_identifier_expr_struct(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let struct_def = match context.struct_defs.get(name) {
        Some(def) => def.clone(),  // Clone to avoid borrow checker issues
        None => return Err(e.lang_error("eval", &format!("Struct '{}' not found in context", name))),
    };
    let inner_e = e.get(0)?;
    match &inner_e.node_type {
        NodeType::Identifier(inner_name) => {
            match struct_def.members.iter().find(|(k, _)| k == inner_name).map(|(_, v)| v.clone()) {
                Some(member_decl) => {
                    return eval_identifier_expr_struct_member(name, inner_name, context, inner_e, &member_decl);
                },
                None => {
                    return Err(e.lang_error("eval", &format!("struct '{}' has no member '{}' j", name, inner_name)));
                },
            }
        },
        _ => {
            return Err(e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name)));
        },
    }
}

fn eval_custom_expr(e: &Expr, context: &mut Context, name: &str, custom_type_name: &str) -> Result<EvalResult, String> {
    let custom_symbol = match context.symbols.get(custom_type_name) {
        Some(sym) => sym,
        None => return Err(e.lang_error("eval", &format!("Argument '{}' is of undefined type {}.", name, custom_type_name))),
    };
    match custom_symbol.value_type {
        ValueType::TType(TTypeDef::TEnumDef) => {
            let enum_val = context.get_enum(name, e)?;
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
                                return Err(inner_e.todo_error("eval", &format!("'{}': StructDef cannot be a field yet", current_name)));
                            },
                            ValueType::TCustom(ref custom_type_name) => {
                                if let Some(custom_symbol) = context.symbols.get(custom_type_name) {
                                    match custom_symbol.value_type {
                                        ValueType::TType(TTypeDef::TStructDef) => {
                                            let struct_def = match context.struct_defs.get(custom_type_name) {
                                                Some(def) => def,
                                                None => return Err(e.lang_error("eval", &format!("Struct '{}' not found in context", custom_type_name))),
                                            };
                                            match struct_def.members.iter().find(|(k, _)| k == inner_name).map(|(_, v)| v) {
                                                Some(member_decl) => {
                                                    current_type = member_decl.value_type.clone();
                                                    current_name = format!("{}.{}", current_name, inner_name);
                                                },
                                                None => return Err(inner_e.lang_error("eval", &format!("Struct '{}' has no member '{}' k", value_type_to_str(&current_type), inner_name))),
                                            }
                                        },
                                        ValueType::TType(TTypeDef::TEnumDef) => {
                                            return Err(inner_e.lang_error("eval", &format!("Enum '{}' does not support nested members", current_name)));
                                        },
                                        _ => return Err(inner_e.lang_error("eval", "Custom types cannot have nested members")),
                                    }
                                } else {
                                    return Err(inner_e.lang_error("eval", &format!("Custom type '{}' not found in symbols", custom_type_name)));
                                }
                            },
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                return Err(inner_e.lang_error("eval", &format!("Enum '{}' does not support nested members", current_name)));
                            },
                            _ => return Err(inner_e.lang_error("eval", &format!("Unexpected type for '{}', cannot access member '{}'", current_name, inner_name))),
                        }
                    },
                    _ => return Err(inner_e.lang_error("eval", &format!("Expected identifier, found {:?}", inner_e.node_type))),
                }
            }

            let inner_e = match e.params.last() {
                Some(expr) => expr,
                None => return Err(e.lang_error("eval", "eval_custom_expr: Expected at least one parameter")),
            };
            match current_type {
                ValueType::TCustom(ref custom_type_name) => {
                    match custom_type_name.as_str() {
                        "I64" => match context.get_i64(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "U8" => match context.get_u8(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "Bool" => match context.get_bool(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "Str" => match context.get_string(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        _ => {
                            let custom_type_name = &value_type_to_str(&current_type);
                            let custom_symbol_info = match context.symbols.get(custom_type_name) {
                                Some(symbol_info) => symbol_info,
                                None => return Err(inner_e.lang_error("eval", &format!("Unknown custom type '{}'", custom_type_name))),
                            };
                            match &custom_symbol_info.value_type {
                                ValueType::TType(TTypeDef::TEnumDef) => {
                                    let enum_val = context.get_enum(&current_name, inner_e)?;
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
                                _ => Err(inner_e.todo_error("eval", &format!("Cannot access '{}'. Fields of custom type '{}' not implemented", current_name, custom_type_name))),
                            }
                        },
                    }
                },
                _ => Err(e.lang_error("eval", &format!("Invalid type for '{}'.", current_name))),
            }
        },
        _ => Err(e.lang_error("eval", &format!("'{}' of type: '{}': custom types are supposed to be struct or enum, found '{}'.", name, custom_type_name, value_type_to_str(&custom_symbol.value_type)))),
    }
}

fn eval_identifier_expr(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match context.symbols.get(name) {
        Some(symbol_info) => match &symbol_info.value_type {
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                return Ok(EvalResult::new(name));
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                // let enum_def = match context.enum_defs.get(name) {
                //     Some(def) => def,
                //     None => return Err(e.lang_error("eval", &format!("Enum '{}' not found in context", name))),
                // };
                let inner_e = e.get(0)?;
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        // TODO check that inner_name is in enum_def
                        // TODO check if that inner_name has an optional type
                        return Ok(EvalResult::new(&format!("{}.{}", name, inner_name)));
                    },
                    _ => {
                        return Err(e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name)));
                    },
                }
            },
            ValueType::TType(TTypeDef::TStructDef) => {
                return eval_identifier_expr_struct(name, context, e)
            }
            ValueType::TCustom(s) if s == INFER_TYPE => {
                return Err(e.lang_error("eval", &format!("Can't infer the type of identifier '{}'.", name)));
            },
            ValueType::TCustom(ref custom_type_name) => {
                // Clone custom_type_name to avoid borrow checker issues
                let custom_type_name_clone = custom_type_name.clone();
                match custom_type_name_clone.as_str() {
                    "I64" => {
                        let val = context.get_i64(name, e)?;
                        return Ok(EvalResult::new(&val.to_string()))
                    },
                    "U8" => {
                        let val = context.get_u8(name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Bool" => {
                        let val = context.get_bool(name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Str" => {
                        if e.params.len() == 0 {
                            let val = context.get_string(name, e)?;
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
                return Err(e.todo_error("eval", &format!("Can't use identifier '{}'. Type {:?} not supported yet.", name, symbol_info.value_type)));
            },
        },
        None => {
            return Err(e.lang_error("eval", &format!("Undefined symbol '{}'. This should have been caught in the compile phase.", name)));
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
                        _ => return Err(stmt.lang_error("eval", "Catch variable must be an identifier")),
                    };
                    let type_expr = &stmt.params[1];
                    let type_name = match &type_expr.node_type {
                        NodeType::Identifier(name) => name,
                        _ => return Err(stmt.lang_error("eval", "Catch type must be an identifier")),
                    };
                    if let Some(thrown_type) = &throw_result.thrown_type {
                        if type_name == thrown_type {
                            // Bind the error variable to the caught error value
                            context.symbols.insert(var_name.to_string(), SymbolInfo {
                                value_type: ValueType::TCustom(thrown_type.clone()),
                                is_mut: false,
                            });

                            // Map instance fields for the error variable
                            // First try to find the arena index for proper field mapping
                            if let Some(offset) = context.arena_index.get(&throw_result.value) {
                                context.arena_index.insert(var_name.to_string(), *offset);

                                // Copy ALL field mappings (including nested) from thrown instance to catch variable
                                // This handles both mutable and immutable fields, and nested struct fields like .msg.c_string
                                let source_prefix = format!("{}.", &throw_result.value);
                                let dest_prefix = format!("{}.", var_name);

                                let keys_to_copy: Vec<String> = context.arena_index.keys()
                                    .filter(|k| k.starts_with(&source_prefix))
                                    .cloned()
                                    .collect();
                                for src_key in keys_to_copy {
                                    if let Some(&src_offset) = context.arena_index.get(&src_key) {
                                        let dest_key = src_key.replacen(&source_prefix, &dest_prefix, 1);
                                        context.arena_index.insert(dest_key, src_offset);
                                    }
                                }

                                // Also copy symbol mappings for all fields
                                let symbol_keys_to_copy: Vec<String> = context.symbols.keys()
                                    .filter(|k| k.starts_with(&source_prefix))
                                    .cloned()
                                    .collect();
                                for src_key in symbol_keys_to_copy {
                                    if let Some(src_symbol) = context.symbols.get(&src_key) {
                                        let dest_key = src_key.replacen(&source_prefix, &dest_prefix, 1);
                                        context.symbols.insert(dest_key, src_symbol.clone());
                                    }
                                }
                            } else {
                                // Fallback: try to map fields from the thrown value or type
                                // This happens when throwing inline struct constructors or when arena_index lookup fails
                                let source_name = &throw_result.value;

                                if let Some(struct_def) = context.struct_defs.get(thrown_type) {
                                    for (field_name, field_decl) in &struct_def.members {
                                        let src_instance_field = format!("{}.{}", source_name, field_name);
                                        let src_type_field = format!("{}.{}", thrown_type, field_name);
                                        let dst_field = format!("{}.{}", var_name, field_name);

                                        // Add symbol for the field
                                        context.symbols.insert(
                                            dst_field.clone(),
                                            SymbolInfo {
                                                value_type: field_decl.value_type.clone(),
                                                is_mut: false,
                                            },
                                        );

                                        // For Str fields, copy arena_index entries for c_string and cap
                                        // Try instance field first, then fall back to type field
                                        if let ValueType::TCustom(type_name) = &field_decl.value_type {
                                            if type_name == "Str" {
                                                // Try instance field first
                                                let c_string_src = if let Some(&offset) = context.arena_index.get(&format!("{}.c_string", src_instance_field)) {
                                                    Some(offset)
                                                } else {
                                                    // Fall back to type field
                                                    context.arena_index.get(&format!("{}.c_string", src_type_field)).copied()
                                                };

                                                let cap_src = if let Some(&offset) = context.arena_index.get(&format!("{}.cap", src_instance_field)) {
                                                    Some(offset)
                                                } else {
                                                    context.arena_index.get(&format!("{}.cap", src_type_field)).copied()
                                                };

                                                if let Some(c_string_offset) = c_string_src {
                                                    context.arena_index.insert(format!("{}.c_string", dst_field), c_string_offset);
                                                }
                                                if let Some(cap_offset) = cap_src {
                                                    context.arena_index.insert(format!("{}.cap", dst_field), cap_offset);
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            let body_expr = &stmt.params[2];
                            let result = eval_body(&mut context, &body_expr.params)?;

                            // Clean up the error variable binding after the catch block
                            context.symbols.remove(var_name);
                            context.arena_index.remove(var_name);
                            // Also remove the field mappings
                            if let Some(struct_def) = context.struct_defs.get(thrown_type) {
                                for (field_name, field_decl) in &struct_def.members {
                                    let combined_name = format!("{}.{}", var_name, field_name);
                                    context.symbols.remove(&combined_name);
                                    context.arena_index.remove(&combined_name);

                                    // For Str fields, also remove c_string and cap entries
                                    if let ValueType::TCustom(type_name) = &field_decl.value_type {
                                        if type_name == "Str" {
                                            context.arena_index.remove(&format!("{}.c_string", combined_name));
                                            context.arena_index.remove(&format!("{}.cap", combined_name));
                                        }
                                    }
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

    let mut function_context = context.clone();
    let has_multi_arg = crate::rs::typer::func_proc_has_multi_arg(func_def);
    if !has_multi_arg && func_def.args.len() != e.params.len() - 1 {
        return Err(e.lang_error("eval", &format!("func '{}' expected {} args, but {} were provided.",
                                                 name, func_def.args.len(), e.params.len() - 1)))
    }
    if has_multi_arg && func_def.args.len() - 1 > e.params.len() - 1 {
        return Err(e.lang_error( "eval", &format!("func '{}' expected at least {} args, but {} were provided.",
                                                  name, func_def.args.len() - 1, e.params.len() - 1)));
    }

    let mut param_index = 1;
    let mut mut_args: Vec<(String, String, ValueType)> = Vec::new(); // (arg_name, source_name, type)

    for arg in &func_def.args {
        function_context.symbols.insert(arg.name.to_string(), SymbolInfo {value_type: arg.value_type.clone(), is_mut: arg.is_mut});
        match &arg.value_type {
            ValueType::TMulti(ref multi_value_type) => {
                let variadic_args = &e.params[param_index..];
                let mut values = Vec::new();
                for expr in variadic_args {
                    let result = eval_expr(context, expr)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let val = result.value;
                    values.push(val);
                }

                // All array types now use the generic Array
                let array_type_name = "Array".to_string();

                function_context.symbols.insert(arg.name.to_string(), SymbolInfo {
                    value_type: ValueType::TCustom(array_type_name),
                    is_mut: arg.is_mut,
                });
                function_context.insert_array(&arg.name, &multi_value_type, &values, e)?;

                // We've consumed all remaining parameters, break out of loop
                break;
            },
            ValueType::TCustom(ref custom_type_name) => {
                let current_arg = e.get(param_index)?;

                // If this is an enum argument and current_arg is an identifier, get the enum value to preserve payload
                let enum_payload_backup = if let NodeType::Identifier(id_name) = &current_arg.node_type {
                    if let Some(sym) = context.symbols.get(id_name) {
                        if let ValueType::TCustom(arg_type_name) = &sym.value_type {
                            if let Some(type_sym) = context.symbols.get(arg_type_name) {
                                if type_sym.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                    // This is an enum variable, get its value to preserve payload
                                    match context.get_enum(id_name, e) {
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
                    return Ok(result); // Propagate throw
                }
                let result_str = result.value;

                // Restore enum payload if we saved it
                if let Some(payload_data) = enum_payload_backup {
                    context.temp_enum_payload = Some(payload_data);
                }

                // Resolve Dynamic to actual type first
                let custom_type_name = &match custom_type_name.as_str() {
                    "Dynamic" => value_type_to_str(&crate::rs::init::get_value_type(context, &current_arg)?),
                    _ => custom_type_name.clone(),
                };

                // Now push to mut_args with the resolved type
                if arg.is_mut {
                    match &current_arg.node_type {
                        NodeType::Identifier(id_) => {
                            mut_args.push((arg.name.clone(), id_.clone(), ValueType::TCustom(custom_type_name.clone())));
                        },
                        _ => {
                            return Err(e.lang_error("eval", "mut arguments must be passed as identifiers"))
                        }
                    }
                }

                match custom_type_name.as_str() {
                    "I64" => {
                        function_context.insert_i64(&arg.name, &result_str, e)?;
                    },
                    "U8" => {
                        function_context.insert_u8(&arg.name, &result_str, e)?;
                    },
                    "Bool" => {
                        function_context.insert_bool(&arg.name, &result_str, e)?;
                    },
                    "Str" => {
                        function_context.insert_string(&arg.name, &result_str, e)?;
                    },
                    _ => {
                        let custom_symbol = function_context.symbols.get(custom_type_name).ok_or_else(|| {
                            return e.lang_error("eval", &format!( "Undefined symbol for custom type '{}'", custom_type_name))
                        })?;
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                // Transfer payload from outer context if present
                                function_context.temp_enum_payload = context.temp_enum_payload.clone();
                                function_context.insert_enum(&arg.name, &custom_type_name, &result_str, e)?;
                            },
                            ValueType::TType(TTypeDef::TStructDef) => {
                                if current_arg.params.len() > 0 {
                                    return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only name of struct instances allowed for struct arguments for now.",
                                                                             &arg.name, &custom_type_name)))
                                }
                                match &current_arg.node_type {
                                    NodeType::Identifier(id_) => {
                                        // If source and dest have the same name, we need to save the source offsets
                                        // before insert_struct overwrites them
                                        let (saved_offsets, temp_src_key) = if id_ == &arg.name {
                                            let mut offsets = Vec::new();

                                            // Save all arena_index entries that start with the struct name
                                            // This includes the base offset and all nested field offsets
                                            let prefix = format!("{}.", id_);
                                            for (key, offset) in function_context.arena_index.iter() {
                                                if key == id_ || key.starts_with(&prefix) {
                                                    offsets.push((key.clone(), *offset));
                                                }
                                            }

                                            (Some(offsets), Some(format!("__temp_src_{}", id_)))
                                        } else {
                                            (None, None)
                                        };

                                        function_context.insert_struct(&arg.name, &custom_type_name, e)?;

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
                                                function_context.arena_index.insert(new_key, *offset);
                                            }

                                            function_context.copy_fields(&custom_type_name, &temp_key, &arg.name, e)?;

                                            // Clean up temp keys
                                            for (orig_key, _) in offsets.iter() {
                                                let new_key = if orig_key == id_ {
                                                    temp_key.clone()
                                                } else if orig_key.starts_with(&format!("{}.", id_)) {
                                                    format!("{}{}", temp_key, &orig_key[id_.len()..])
                                                } else {
                                                    orig_key.clone()
                                                };
                                                function_context.arena_index.remove(&new_key);
                                            }
                                        } else {
                                            function_context.copy_fields(&custom_type_name, &id_, &arg.name, e)?;
                                        }
                                    },
                                    _ => {
                                        return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only names of struct instances allowed for struct arguments for now.",
                                                                                 &arg.name, &custom_type_name)))
                                    },
                                }
                            },
                            _ => {
                                return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Custom types can only be struct or enum.",
                                                                         &arg.name, &custom_type_name)))
                            },
                        }
                    },
                }

            },

            _ => {
                return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only enum custom types allowed for now.",
                                                         &arg.name, value_type_to_str(&arg.value_type))))
            },
        }

        param_index += 1;
    }

    let result = eval_body(&mut function_context, &func_def.body)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let result_str = result.value;

    for (arg_name, source_name, value_type) in mut_args {
        match value_type {
            ValueType::TCustom(ref type_name) if type_name == "I64" => {
                let val = function_context.get_i64(&arg_name, e)?;
                context.insert_i64(&source_name, &val.to_string(), e)?;
            },
            ValueType::TCustom(ref type_name) if type_name == "U8" => {
                let val = function_context.get_u8(&arg_name, e)?;
                context.insert_u8(&source_name, &val.to_string(), e)?;
            },
            ValueType::TCustom(ref type_name) if type_name == "Str" => {
                let val = function_context.get_string(&arg_name, e)?;
                context.insert_string(&source_name, &val.to_string(), e)?;
            },
            ValueType::TCustom(ref type_name) => {
                let symbol_info = match context.symbols.get(type_name) {
                    Some(symbol_info_) => symbol_info_,
                    None => {
                        return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an mut argument. Undefined symbol.", arg_name, type_name)))
                    },
                };
                match &symbol_info.value_type {
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        let val = function_context.get_enum(&arg_name, e)?;
                        context.insert_enum(&source_name, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name), e)?;
                    },
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // TODO this can be simplified once we pass all args by reference
                        if let Some(offset) = function_context.arena_index.get(&arg_name) {
                            context.arena_index.insert(source_name.to_string(), *offset);
                            context.map_instance_fields(type_name, &source_name, e)?;
                        } else {
                            return Err(e.lang_error("eval", &format!("Missing struct arena index for argument '{}'", arg_name)));
                        }
                    },
                    _ => {
                        // TODO support functions and types (ie enum_defs struct_defs) as arguments
                        return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Not an enum or struct, but a '{}'.",
                                                                 arg_name, type_name, value_type_to_str(&symbol_info.value_type))))
                    },
                }

            },
            _ => {
                return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Only structs and enums allowed for now.",
                                                         arg_name, value_type_to_str(&value_type))))
            }
        }
    }

    // If function returns a user-defined struct, copy fields back to context as temp return val
    if func_def.return_types.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.return_types[0] {
            // Skip core types like I64, Bool, String, U8
            match custom_type_name.as_str() {
                "I64" | "U8" | "Bool" | "Str" => { /* Do nothing for core types */ },
                _ => {

                    if let Some(custom_symbol) = function_context.symbols.get(custom_type_name) {
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                let return_instance = format!("{}{}", RETURN_INSTANCE_NAME, Arena::g().temp_id_counter);
                                Arena::g().temp_id_counter += 1;

                                // Insert the temporary return variable into the symbols table (temporary solution)
                                context.symbols.insert(return_instance.to_string(), SymbolInfo {
                                    value_type: ValueType::TCustom(custom_type_name.to_string()),
                                    is_mut: true,
                                });

                                if let Some(offset) = function_context.arena_index.get(&result_str) {
                                    context.arena_index.insert(return_instance.to_string(), *offset);
                                } else {
                                    return Err(e.lang_error("eval", &format!("Missing arena index for return value '{}'", result_str)));
                                }
                                context.map_instance_fields(custom_type_name, &return_instance, e)?;
                                return Ok(EvalResult::new_return(&return_instance))
                            },
                            _ => {
                                // Not a struct return, ignore
                            }
                        }
                    }
                },

            }
        }
    }

    return Ok(EvalResult::new(&result_str))
}

fn eval_core_func_proc_call(name: &str, context: &mut Context, e: &Expr, is_proc: bool) -> Result<EvalResult, String> {
    return match name {
        "loc" => eval_core_func_loc(context, e),
        "size_of" => eval_core_func_size_of(context, &e),
        "type_as_str" => eval_core_func_type_as_str(context, &e),
        "to_ptr" => eval_core_func_to_ptr(context, &e),
        "malloc" => eval_core_func_malloc(context, &e),
        "free" => eval_core_func_free(context, &e),
        "memset" => eval_core_func_memset(context, &e),
        "memcpy" => eval_core_func_memcpy(context, &e),
        "memcmp" => eval_core_func_memcmp(context, &e),
        "lt" => eval_core_func_lt(context, &e),
        "gt" => eval_core_func_gt(context, &e),
        "add" => eval_core_func_add(context, &e),
        "sub" => eval_core_func_sub(context, &e),
        "mul" => eval_core_func_mul(context, &e),
        "div" => eval_core_func_div(context, &e),
        "mod" => eval_core_func_mod(context, &e),
        "str_to_i64" => eval_core_func_str_to_i64(context, &e),
        "i64_to_str" => eval_core_func_i64_to_str(context, &e),
        "enum_to_str" => eval_core_func_enum_to_str(context, &e),
        "rsonly_enum_extract_payload" => eval_core_proc_enum_extract_payload(context, &e),
        "u8_to_i64" => eval_core_func_u8_to_i64(context, &e),
        "i64_to_u8" => eval_core_func_i64_to_u8(context, &e),
        "eval_to_str" => eval_core_proc_eval_to_str(context, &e),
        "exit" => eval_core_exit(&e),
        "import" => eval_core_proc_import(context, &e), // Phase 2: Initialize imported values
        "input_read_line" => eval_core_proc_input_read_line(context, &e),
        "single_print" => eval_core_proc_single_print(context, &e),
        "print_flush" => eval_core_proc_print_flush(context, &e),
        "readfile" => eval_core_proc_readfile(context, &e),
        "runfile" => eval_core_proc_runfile(context, &e),
        _ => {
            if is_proc {
                Err(e.lang_error("eval", &format!("Core procedure '{}' not implemented.", name)))
            } else {
                Err(e.lang_error("eval", &format!("Core function '{}' not implemented.", name)))
            }
        },
    }
}

fn eval_core_func_loc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Core func 'loc' doesn't take arguments"))
    }
    let file = context.path.clone();
    let line = e.line;
    let col = e.col;

    Ok(EvalResult::new(&format!("{}:{}:{}:", file, line, col)))
}

// ---------- eval memory

fn eval_core_func_malloc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'malloc' takes exactly 1 argument"))
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let size_str = result.value;
    let size = size_str.parse::<usize>().map_err(|err| {
        e.lang_error("eval", &format!("Invalid size for 'malloc': {}", err))
    })?;
    let offset = Arena::g().memory.len(); // take *current* end of arena

    if size > 0 {
        Arena::g().memory.resize(offset + size, 0); // extend safely
    }

    if offset == 0 { // TODO: REM: throw AllocError instead of return NULL pointer
        return Err(e.lang_error("eval", "Core func 'malloc' was about to produce a NULL pointer"))
    }
    return Ok(EvalResult::new(&offset.to_string()))
}

fn eval_core_func_free(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'free' takes exactly 1 argument"))
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let _ptr_str = result.value;
    // REM: Free does nothing in arena model (for now).

    return Ok(EvalResult::new(""))
}

fn eval_core_func_memset(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memset' takes exactly 3 arguments"))
    }

    let dest_result = eval_expr(context, e.get(1)?)?;
    if dest_result.is_throw {
        return Ok(dest_result); // Propagate throw
    }

    let value_result = eval_expr(context, e.get(2)?)?;
    if value_result.is_throw {
        return Ok(value_result); // Propagate throw
    }

    let size_result = eval_expr(context, e.get(3)?)?;
    if size_result.is_throw {
        return Ok(size_result); // Propagate throw
    }

    let dest_str = dest_result.value;
    let value_str = value_result.value;
    let size_str = size_result.value;

    let dest = match dest_str.trim().parse::<i64>() {
        Ok(v) => v as usize,
        Err(err) => return Err(e.error("eval", &format!("Invalid dest (I64): '{}': {}", dest_str, err))),
    };

    let value = match value_str.trim().parse::<u8>() {
        Ok(v) => v,
        Err(err) => return Err(e.error("eval", &format!("Invalid value (U8): '{}': {}", value_str, err))),
    };

    let size = match size_str.trim().parse::<i64>() {
        Ok(v) => v as usize,
        Err(err) => return Err(e.error("eval", &format!("Invalid size (I64): '{}': {}", size_str, err))),
    };

    if dest + size > Arena::g().memory.len() {
        return Err(e.error("eval", &format!(
            "memset out of bounds: dest={} size={} arena_len={}",
            dest, size, Arena::g().memory.len()
        )));
    }

    for i in 0..size {
        Arena::g().memory[dest + i] = value;
    }

    Ok(EvalResult::new(""))
}

fn eval_core_func_memcpy(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memcpy' takes exactly 3 arguments"))
    }

    let dest_result = eval_expr(context, e.get(1)?)?;
    if dest_result.is_throw {
        return Ok(dest_result); // Propagate throw
    }
    let src_result = eval_expr(context, e.get(2)?)?;
    if src_result.is_throw {
        return Ok(src_result); // Propagate throw
    }
    let size_result = eval_expr(context, e.get(3)?)?;
    if size_result.is_throw {
        return Ok(size_result); // Propagate throw
    }

    let dest_str = dest_result.value;
    let src_str = src_result.value;
    let size_str = size_result.value;

    let dest = match dest_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error("eval", &format!("memcpy: Invalid dest (usize): '{}': {}", dest_str, err))),
    };

    let src = match src_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error("eval", &format!("memcpy: Invalid src (usize): '{}': {}", src_str, err))),
    };

    let size = match size_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error("eval", &format!("memcpy: Invalid size (usize): '{}': {}", size_str, err))),
    };

    if dest + size > Arena::g().memory.len() || src + size > Arena::g().memory.len() {
        return Err(e.error("eval", &format!("memcpy out of bounds: src={} dest={} size={} arena_len={}",
                                            src, dest, size, Arena::g().memory.len())));
    }

    for i in 0..size {
        Arena::g().memory[dest + i] = Arena::g().memory[src + i];
    }

    Ok(EvalResult::new(""))
}

fn eval_core_func_memcmp(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memcmp' takes exactly 3 arguments"))
    }

    let ptr1_result = eval_expr(context, e.get(1)?)?;
    if ptr1_result.is_throw {
        return Ok(ptr1_result); // Propagate throw
    }
    let ptr2_result = eval_expr(context, e.get(2)?)?;
    if ptr2_result.is_throw {
        return Ok(ptr2_result); // Propagate throw
    }
    let size_result = eval_expr(context, e.get(3)?)?;
    if size_result.is_throw {
        return Ok(size_result); // Propagate throw
    }

    let ptr1_str = ptr1_result.value;
    let ptr2_str = ptr2_result.value;
    let size_str = size_result.value;

    let ptr1 = match ptr1_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error("eval", &format!("memcmp: Invalid ptr1 (usize): '{}': {}", ptr1_str, err))),
    };

    let ptr2 = match ptr2_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error("eval", &format!("memcmp: Invalid ptr2 (usize): '{}': {}", ptr2_str, err))),
    };

    let size = match size_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error("eval", &format!("memcmp: Invalid size (usize): '{}': {}", size_str, err))),
    };

    if ptr1 + size > Arena::g().memory.len() || ptr2 + size > Arena::g().memory.len() {
        return Err(e.error("eval", &format!("memcmp out of bounds: ptr1={} ptr2={} size={} arena_len={}",
                                            ptr1, ptr2, size, Arena::g().memory.len())));
    }

    // Compare bytes
    for i in 0..size {
        let byte1 = Arena::g().memory[ptr1 + i];
        let byte2 = Arena::g().memory[ptr2 + i];
        if byte1 < byte2 {
            return Ok(EvalResult::new("-1"));
        } else if byte1 > byte2 {
            return Ok(EvalResult::new("1"));
        }
    }

    // All bytes equal
    Ok(EvalResult::new("0"))
}

fn eval_core_func_to_ptr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'to_ptr' takes exactly 1 argument"))
    }

    let identifier_expr = e.get(1)?;
    let combined_name = get_combined_name(identifier_expr)?;
    match context.arena_index.get(&combined_name) {
        Some(addr) => Ok(EvalResult::new(&format!("{}", addr))),
        None => Err(e.lang_error("eval", &format!("calling core func to_ptr, but '{}' is not a known identifier.", combined_name))),
    }
}

fn eval_core_func_size_of(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'size_of' takes exactly 1 argument"))
    }

    let type_expr = e.get(1)?;
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            match context.get_type_size(type_name) {
                Ok(size) => Ok(EvalResult::new(&format!("{}", size))),
                Err(msg) => Err(e.lang_error("eval", &format!("calling core func size: {}", msg))),
            }
        },
        node_type => Err(e.lang_error("eval", &format!("calling core func size_of, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

fn eval_core_func_type_as_str(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'type_as_str' takes exactly 1 argument"))
    }

    let type_expr = e.get(1)?;
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            Ok(EvalResult::new(&format!("{}", type_name)))
        },
        node_type => Err(e.lang_error("eval", &format!("calling core func type_as_str, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

fn eval_core_func_lt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'lt' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'lt': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'lt': {}", err)))?;
    Ok(EvalResult::new(&(a < b).to_string()))
}

fn eval_core_func_gt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'gt' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'gt': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'gt': {}", err)))?;
    Ok(EvalResult::new(&(a > b).to_string()))
}

fn eval_core_func_add(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'add' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'add': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'add': {}", err)))?;
    Ok(EvalResult::new(&(a + b).to_string()))
}

fn eval_core_func_sub(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'sub' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'sub': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'sub': {}", err)))?;
    Ok(EvalResult::new(&(a - b).to_string()))
}

fn eval_core_func_mul(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'mul' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'mul': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'mul': {}", err)))?;
    Ok(EvalResult::new(&(a * b).to_string()))
}

fn eval_core_func_div(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'div' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'div': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'div': {}", err)))?;
    // Return 0 for division by zero (safe default, revisit post-self-hosting)
    if b == 0 {
        return Ok(EvalResult::new("0"));
    }
    Ok(EvalResult::new(&(a / b).to_string()))
}

fn eval_core_func_mod(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
   if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'mod' takes exactly 2 arguments"))
    }
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'mod': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid integer for 'mod': {}", err)))?;
    // Return 0 for modulo by zero (safe default, revisit post-self-hosting)
    if b == 0 {
        return Ok(EvalResult::new("0"));
    }
    Ok(EvalResult::new(&(a % b).to_string()))
}

fn eval_core_func_str_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'str_to_i64' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid input for 'str_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

fn eval_core_func_i64_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'i64_to_str' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

fn eval_core_func_enum_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'enum_to_str' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}


fn eval_core_proc_enum_extract_payload(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core proc 'rsonly_enum_extract_payload' takes exactly 2 arguments"))
    }

    // First argument: enum variable
    let enum_expr = e.get(1)?;
    let enum_result = eval_expr(context, enum_expr)?;
    if enum_result.is_throw {
        return Ok(enum_result);
    }

    let enum_var_name = match &enum_expr.node_type {
        NodeType::Identifier(name) => name,
        _ => return Err(e.error("eval", "rsonly_enum_extract_payload expects an enum variable as first argument")),
    };

    // Second argument: destination variable (must be mutable)
    let dest_expr = e.get(2)?;
    let dest_var_name = match &dest_expr.node_type {
        NodeType::Identifier(name) => name,
        _ => return Err(e.error("eval", "enum_extract_payload expects a variable name as second argument")),
    };

    // Verify destination is mutable
    let dest_symbol = context.symbols.get(dest_var_name).ok_or_else(|| {
        e.error("eval", &format!("Destination variable '{}' not found", dest_var_name))
    })?;
    if !dest_symbol.is_mut {
        return Err(e.error("eval", &format!("Destination variable '{}' must be mutable", dest_var_name)));
    }

    // Get the enum value
    let enum_val = context.get_enum(enum_var_name, e)?;

    // Check if enum has a payload
    let (payload_bytes, payload_type) = match (&enum_val.payload, &enum_val.payload_type) {
        (Some(bytes), Some(ptype)) => (bytes, ptype),
        _ => return Err(e.error("eval", &format!("Enum '{}' has no payload", enum_var_name))),
    };

    // Verify destination type matches payload type
    let dest_type = &dest_symbol.value_type;
    if dest_type != payload_type {
        return Err(e.error("eval", &format!(
            "Type mismatch: enum payload is {}, but destination is {}",
            value_type_to_str(payload_type),
            value_type_to_str(dest_type)
        )));
    }

    // Extract payload based on type
    match payload_type {
        ValueType::TCustom(type_name) if type_name == "I64" => {
            if payload_bytes.len() != 8 {
                return Err(e.error("eval", "Invalid I64 payload size"));
            }
            let mut bytes = [0u8; 8];
            bytes.copy_from_slice(&payload_bytes[0..8]);
            let i64_val = i64::from_le_bytes(bytes);
            context.insert_i64(dest_var_name, &i64_val.to_string(), e)?;
        },
        ValueType::TCustom(struct_type_name) => {
            // Handle struct payloads
            let type_symbol = context.symbols.get(struct_type_name).ok_or_else(|| {
                e.error("eval", &format!("Unknown type '{}'", struct_type_name))
            })?;

            match &type_symbol.value_type {
                ValueType::TType(TTypeDef::TStructDef) => {
                    // Get destination struct offset
                    let dest_offset = context.arena_index.get(dest_var_name).ok_or_else(|| {
                        e.error("eval", &format!("Destination struct '{}' not found in arena", dest_var_name))
                    })?;

                    // Verify payload size matches struct size
                    let struct_size = context.get_type_size(struct_type_name)
                        .map_err(|err| e.error("eval", &err))?;
                    if payload_bytes.len() != struct_size {
                        return Err(e.error("eval", &format!(
                            "Payload size mismatch: expected {}, got {}",
                            struct_size, payload_bytes.len()
                        )));
                    }

                    // Copy payload bytes into destination struct's arena location
                    Arena::g().memory[*dest_offset..*dest_offset + struct_size]
                        .copy_from_slice(&payload_bytes);

                    // Re-map the struct fields to update field offsets in arena_index and symbols
                    // This is necessary because the destination struct's fields were registered
                    // when it was created, but the byte copy changed the internal structure
                    context.map_instance_fields(struct_type_name, dest_var_name, e)?;
                },
                ValueType::TType(TTypeDef::TEnumDef) => {
                    // Handle enum payloads
                    // The payload_bytes contains: [8 bytes variant tag][N bytes enum's payload]

                    if payload_bytes.len() < 8 {
                        return Err(e.error("eval", "Invalid enum payload: too small"));
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
                    let enum_def = context.enum_defs.get(struct_type_name).ok_or_else(|| {
                        e.error("eval", &format!("Enum definition for '{}' not found", struct_type_name))
                    })?;

                    // Find variant name by matching the variant position
                    let mut found_variant = None;
                    for (name, _) in &enum_def.enum_map {
                        let pos = Context::get_variant_pos(enum_def, name, e)?;
                        if pos == variant_pos {
                            found_variant = Some(name.clone());
                            break;
                        }
                    }

                    let variant_name = found_variant.ok_or_else(|| {
                        e.error("eval", &format!("Variant position {} not found in enum {}", variant_pos, struct_type_name))
                    })?;

                    // Get the inner payload type
                    let inner_payload_type = enum_def.enum_map.get(&variant_name)
                        .and_then(|opt| opt.clone());

                    // Now reconstruct the enum and insert it
                    let enum_val_str = format!("{}.{}", struct_type_name, variant_name);

                    // Set temp_enum_payload if there's an inner payload
                    if let Some(payload_data) = inner_payload {
                        context.temp_enum_payload = Some((payload_data, inner_payload_type.unwrap()));
                    }

                    // Insert the enum (needs: id, enum_type, pre_normalized_enum_name, e)
                    context.insert_enum(dest_var_name, struct_type_name, &enum_val_str, e)?;
                },
                _ => {
                    return Err(e.error("eval", &format!("Unsupported payload type: {}", value_type_to_str(payload_type))));
                }
            }
        },
        _ => {
            return Err(e.error("eval", &format!("Unsupported payload type: {}", value_type_to_str(payload_type))));
        }
    }

    Ok(EvalResult::new(""))
}

fn eval_core_func_u8_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'u8_to_i64' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid input for 'u8_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

fn eval_core_func_i64_to_u8(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'i64_to_u8' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

// ---------- core procs implementations for eval

fn eval_core_proc_single_print(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'single_print' takes exactly 1 argument"));
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    print!("{}", result.value);
    Ok(EvalResult::new(""))
}

fn eval_core_proc_print_flush(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Core proc 'print_flush' takes 0 arguments"));
    }

    io::stdout().flush().map_err(|err| e.lang_error("eval", &format!("Failed to flush stdout: {}", err)))?;
    Ok(EvalResult::new(""))
}

fn eval_core_proc_input_read_line(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'input_read_line' takes exactly 1 argument"));
    }

    let first_param = e.get(1)?;
    let read_line_error_msg = match &first_param.node_type {
        NodeType::LLiteral(Literal::Str(error_msg_)) => error_msg_.clone(),
        _ => return Err(e.lang_error("eval", &format!("input_read_line() expects a literal string error message. Found '{:?}' instead.",
                                                      first_param.node_type))),
    };

    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .map_err(|_| e.lang_error("eval", &read_line_error_msg))?;

    Ok(EvalResult::new(&line))
}

fn eval_core_proc_eval_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'eval_to_str' takes exactly 1 argument"));
    }

    let path = "eval".to_string(); // Placeholder path
    let source_expr = eval_expr(context, e.get(1)?)?;
    if source_expr.is_throw {
        return Ok(source_expr); // Propagate throw
    }

    let str_source = format!("mode script; {}", source_expr.value);
    return main_run(false, false, context, &path, str_source, Vec::new())
}

fn eval_core_proc_runfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() < 2 {
        return Err(e.lang_error("eval", "Core proc 'runfile' expects at least 1 parameter"));
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let path = result.value;

    let mut main_args = Vec::new();
    for i in 2..e.params.len() {
        let arg_result = eval_expr(context, e.get(i)?)?;
        if arg_result.is_throw {
            return Ok(arg_result); // Propagate throw
        }
        main_args.push(arg_result.value);
    }

    match run_file(&path, main_args) {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error_string) => Err(e.error("eval", &format!("While running file {path}\n{error_string}"))),
    }
}

pub fn eval_core_proc_import(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'import' expects a single parameter"));
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    let original_path = context.path.clone();
    let path = format!("{}{}", result.value, ".til");

    // If imported values already initialized, use the cache (Phase 2)
    match context.imports_values_done.get(&path) {
        Some(import_result) => return import_result.clone(),
        None => match context.imports_wip.contains(&path) {
            true => {
                // TODO do a more detailed message with backtraces or storing a graph of the dependencies or something
                return Err(e.error("eval", &format!("While trying to import {} from {}: Circular import dependency",
                                                    path, original_path)))
            },
            false => {
                if !context.imports_wip.insert(path.clone()) {
                    return Err(e.lang_error("eval", &format!("While trying to import {} from {}: Can't insert in imports_wip",
                                                             path, original_path)))
                }
            },
        },
    }
    context.path = path.clone();

    let result = match run_file_with_context(true, context, &path, Vec::new()) {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error_string) => {
            context.path = original_path.clone();
            return Err(e.error("eval", &format!("While trying to import {} from {}:\n{}",
                                                path, original_path, error_string)))
        },
    };

    context.imports_wip.remove(&path);
    context.imports_values_done.insert(path, result.clone());
    context.path = original_path;
    return result
}

fn eval_core_proc_readfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'readfile' expects a single parameter"));
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let path = result.value;

    let source = match fs::read_to_string(&path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => return Err(e.error("eval", &format!("File '{}' not found.", path))),
            other_error => return Err(e.error("eval", &format!("Problem reading file '{}': {}", path, other_error))),
        },
    };

    Ok(EvalResult::new(&source))
}

fn eval_core_exit(e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'exit' expects a single parameter"));
    }

    let e_exit_code = e.get(1)?;
    let exit_code = match &e_exit_code.node_type {
        NodeType::LLiteral(Literal::Number(my_li64)) => my_li64.parse::<i64>()
            .map_err(|err| e.lang_error("eval", &format!("Invalid number literal '{}': {}", *my_li64, err)))?,
        node_type => return Err(e.lang_error("eval", &format!("calling core proc 'exit', but found {:?} instead of literal i64 exit code.", node_type))),
    };

    std::process::exit(exit_code as i32);
}
