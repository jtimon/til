use std::fs;
use std::io::ErrorKind;
use std::collections::{HashMap, HashSet};
use std::convert::TryInto;

use crate::rs::lexer::{lexer_from_source};
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, FunctionType, ValueType, SFuncDef, TTypeDef, Literal, SEnumDef, SStructDef, ModeDef, Declaration, PatternInfo,
    can_be_imported, value_type_to_str, str_to_value_type, parse_mode, parse_tokens, mode_from_name,
};
use crate::rs::interpreter::{Arena, EvalResult, eval_expr};

// Init phase: Declaration indexing and import processing
// This module handles the "context priming" phase that runs before type checking.
// No eval, no arena access - declarations only.

#[derive(Clone)]
pub struct SymbolInfo {
    pub value_type: ValueType,
    pub is_mut: bool,
    pub is_copy: bool,
    pub is_own: bool,
}

#[derive(Debug, Clone, PartialEq)]
pub struct EnumVal {
    pub enum_type: String,
    pub enum_name: String,
    // Payload for tagged unions: stores the associated data
    // For now, supports Bool (1 byte) and I64 (8 bytes)
    pub payload: Option<Vec<u8>>,
    pub payload_type: Option<ValueType>,
}

pub fn get_func_name_in_call(e: &Expr) -> String {
    if e.node_type != NodeType::FCall {
        return e.exit_error("type", "get_func_name_in_call(): expected fcall node.")
    }
    if e.params.len() == 0 {
        return e.exit_error("type", "get_func_name_in_call(): fcall nodes must have at least 1 parameter.")
    }
    match &e.get(0) {
        Ok(param) => {
            match &param.node_type {
                NodeType::Identifier(f_name) => return f_name.clone(),
                node_type => return e.exit_error(
                    "type", &format!("in get_func_name_in_call(): Identifiers can only contain identifiers, found '{:?}'", node_type)),
            }
        },
        Err(error_str) => return error_str.to_string(),
    }
}

fn value_type_func_proc(path: &str, e: &Expr, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.return_types.len() {
        0 => {
            return Err(e.error(path, "type", &format!("func '{}' does not return anything", name)));
        },
        1 => {
            match func_def.return_types.get(0) {
                Some(ValueType::TCustom(type_str)) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                Some(other) => Err(e.error(path, "type", &format!("func '{}' returns unsupported type {}", name, value_type_to_str(other)))),
                None => Err(e.lang_error("type", &format!("func '{}' has inconsistent return type info", name))),
            }
        },
        _ => {
            return Err(e.todo_error("type", &format!("func '{}' returns multiple values", name)));
        },
    }
}

fn get_ufcs_fcall_value_type(context: &Context, e: &Expr, f_name: &String, id_expr: &Expr, symbol: &SymbolInfo) -> Result<ValueType, String> {
    if id_expr.params.is_empty() {
        return Err(e.error(&context.path, "type", &format!("Cannot call '{}', it is not a function or struct, it is a '{}'",
                                            &f_name, value_type_to_str(&symbol.value_type))));
    }

    // Get the last param (the method name)
    let method_name_expr = match id_expr.params.last() {
        Some(expr) => expr,
        None => return Err(e.lang_error("type", "Expected method name in UFCS call")),
    };

    let method_name = match &method_name_expr.node_type {
        NodeType::Identifier(name) => name,
        _ => return Err(e.error(&context.path, "type", &format!("Expected identifier for method name, found '{:?}'", method_name_expr.node_type))),
    };

    // Check if it's a regular function
    if let Some(func_def) = context.funcs.get(method_name) {
        return value_type_func_proc(&context.path, &e, &f_name, func_def)
    }

    // Create identifier expression without the last param (method name) to get the type
    let mut id_without_method = id_expr.clone();
    id_without_method.params.pop();

    // Get the type of the nested identifier
    let target_type = get_value_type(context, &id_without_method)?;

    // Check if it's an associated function for this type
    match &target_type {
        ValueType::TCustom(custom_type_name) => {
            let id_expr_name = format!("{}.{}", custom_type_name, method_name);
            if let Some(func_def) = context.funcs.get(&id_expr_name) {
                return value_type_func_proc(&context.path, &e, &id_expr_name, &func_def);
            }
            return Err(e.error(&context.path, "type", &format!("Type '{}' has no method '{}'", custom_type_name, method_name)));
        },
        _ => {
            return Err(e.error(&context.path, "type", &format!("'{}' of type '{}' doesn't support methods", f_name, value_type_to_str(&target_type))));
        }
    }
}

fn get_fcall_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {

    let f_name = get_func_name_in_call(&e);

    // Check if this is a UFCS call on a function/expression result
    // If e has 2+ params (func name + target + args), check if the target's type
    // has an associated method with this name, prioritizing it over standalone functions
    if e.params.len() >= 2 {
        let first_arg = e.get(1)?;  // Get the UFCS target (skip func name at index 0)

        // Try to get the type of the first argument
        if let Ok(target_type) = get_value_type(context, first_arg) {
            if let ValueType::TCustom(custom_type_name) = target_type {
                // Check if this type has an associated method with this name
                let method_name = format!("{}.{}", custom_type_name, f_name);
                if let Some(func_def) = context.funcs.get(&method_name) {
                    // UFCS method exists! Use it instead of standalone function
                    return value_type_func_proc(&context.path, &e, &method_name, func_def);
                }
            }
        }
        // If we couldn't determine type or no associated method exists, fall through
    }

    // Original logic: check for standalone function
    if let Some(func_def) = context.funcs.get(&f_name) {
        return value_type_func_proc(&context.path, &e, &f_name, func_def)
    } else if let Some(symbol) = context.symbols.get(&f_name) {

        let id_expr = e.get(0)?;
        match &symbol.value_type {
            ValueType::TType(TTypeDef::TStructDef) => {
                let struct_def = match context.struct_defs.get(&f_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error("type", &format!("struct '{}' not found in context", f_name)));
                    },
                };
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_decl = struct_def.get_member_or_err(after_dot_name, &f_name, &context.path, e)?;
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error(&context.path, "type", &format!("struct '{}' has no member '{}' b", f_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", f_name, after_dot_name);
                                return value_type_func_proc(&context.path, &e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error(&context.path, "type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    f_name, after_dot_name, value_type_to_str(&member_decl.value_type))));
                            },
                        }
                    },
                    _ => {
                        return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                // Handle enum constructor calls like Color.Green(true)
                let enum_def = match context.enum_defs.get(&f_name) {
                    Some(_enum_def) => _enum_def,
                    None => {
                        return Err(e.lang_error("type", &format!("enum '{}' not found in context", f_name)));
                    },
                };
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        // Just referencing the enum type itself, not constructing
                        return Ok(ValueType::TType(TTypeDef::TEnumDef));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(variant_name) => {
                        // Check if this variant exists in the enum
                        let variant_type = match enum_def.enum_map.get(variant_name) {
                            Some(_variant) => _variant,
                            None => {
                                return Err(e.error(&context.path, "type", &format!("enum '{}' has no variant '{}'", f_name, variant_name)));
                            },
                        };

                        // Validate argument count based on whether the variant expects a payload
                        match variant_type {
                            Some(payload_type) => {
                                // This variant expects a payload
                                if e.params.len() < 2 {
                                    return Err(e.error(&context.path, "type", &format!("Enum constructor {}.{} expects a payload of type {}", f_name, variant_name, value_type_to_str(payload_type))));
                                }
                                // Type check the payload argument
                                let payload_expr = e.get(1)?;
                                let payload_actual_type = get_value_type(context, payload_expr)?;

                                // Verify payload type matches expected type
                                if payload_actual_type != *payload_type {
                                    return Err(e.error(&context.path, "type", &format!(
                                        "Enum constructor {}.{} expects payload of type {}, but got {}",
                                        f_name, variant_name,
                                        value_type_to_str(payload_type),
                                        value_type_to_str(&payload_actual_type)
                                    )));
                                }
                            },
                            None => {
                                // This variant doesn't have a payload
                                if e.params.len() > 1 {
                                    return Err(e.error(&context.path, "type", &format!("Enum variant {}.{} does not take a payload", f_name, variant_name)));
                                }
                            },
                        }

                        // Return the enum type
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                    _ => {
                        return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            ValueType::TCustom(custom_type_name) => {
                // Check if it's an enum first
                if context.enum_defs.contains_key(custom_type_name) {
                    // It's an enum - try UFCS method call
                    let after_dot = match id_expr.params.get(0) {
                        Some(_after_dot) => _after_dot,
                        None => {
                            return Ok(ValueType::TCustom(f_name.clone()));
                        },
                    };
                    match &after_dot.node_type {
                        NodeType::Identifier(after_dot_name) => {
                            // Try associated method first
                            let method_name = format!("{}.{}", custom_type_name, after_dot_name);
                            if let Some(func_def) = context.funcs.get(&method_name) {
                                return value_type_func_proc(&context.path, &e, &method_name, func_def);
                            }

                            // Fall back to UFCS: try standalone function with enum as first arg
                            match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                Ok(ok_val) => return Ok(ok_val),
                                Err(_) => {
                                    return Err(e.error(&context.path, "type", &format!("enum '{}' has no method '{}' and no matching function found for UFCS", custom_type_name, after_dot_name)));
                                },
                            }
                        },
                        _ => {
                            return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                        },
                    }
                }

                // Not an enum, try struct
                let struct_def = match context.struct_defs.get(custom_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error("type", &format!("type '{}' not found in context", f_name)));
                    },
                };
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        // Bug #10 fix: Check if we have a multi-level chain like struct.field.method
                        // If id_expr.params has 2+ elements, try to resolve all-but-last as field access
                        if id_expr.params.len() >= 2 {
                            // Try to resolve the field access chain (all params except the last)
                            // Example: for e.params.len, resolve "e.params" to get its type
                            let mut field_access_expr = id_expr.clone();
                            field_access_expr.params.pop(); // Remove the last element (method/property name)

                            if let Ok(intermediate_type) = get_value_type(context, &field_access_expr) {
                                // Successfully resolved intermediate field access
                                // Now check if the last param is a member/method of that type
                                let last_param = id_expr.params.last().unwrap();
                                if let NodeType::Identifier(final_member_name) = &last_param.node_type {
                                    match &intermediate_type {
                                        ValueType::TCustom(intermediate_type_name) => {
                                            // First check if it's a method on this type
                                            let method_name = format!("{}.{}", intermediate_type_name, final_member_name);
                                            if let Some(func_def) = context.funcs.get(&method_name) {
                                                return value_type_func_proc(&context.path, &e, &method_name, func_def);
                                            }

                                            // Try UFCS: standalone function with intermediate type as first arg
                                            if let Some(func_def) = context.funcs.get(final_member_name) {
                                                return value_type_func_proc(&context.path, &e, final_member_name, func_def);
                                            }

                                            // Check if it's a struct with this member as a field
                                            if let Some(intermediate_struct_def) = context.struct_defs.get(intermediate_type_name) {
                                                if let Some(member_decl) = intermediate_struct_def.get_member(final_member_name) {
                                                    // It's a field access - return the field's type
                                                    return Ok(member_decl.value_type.clone());
                                                }
                                            }
                                        },
                                        _ => {
                                            // Intermediate type is not a custom type, fall through
                                        }
                                    }
                                }
                            }
                        }

                        // Original logic: single-level access (struct.member)
                        let member_decl = match struct_def.get_member(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error(&context.path, "type", &format!("struct '{}' has no member '{}' c", custom_type_name, after_dot_name)));
                                    },
                                }
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error(&context.path, "type", &format!("struct '{}' has no member '{}' d", custom_type_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", custom_type_name, after_dot_name);
                                return value_type_func_proc(&context.path, &e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error(&context.path, "type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    f_name, after_dot_name, value_type_to_str(&member_decl.value_type))));
                            },
                        }
                    },

                    _ => {
                        return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            ValueType::TMulti(_) => {
                // Variadic parameters are implemented as Array at runtime
                // Treat them as Array for type checking method calls
                let custom_type_name = "Array";
                let struct_def = match context.struct_defs.get(custom_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error("type", &format!("struct '{}' not found in context", custom_type_name)));
                    },
                };
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Ok(ValueType::TCustom(custom_type_name.to_string()));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_decl = match struct_def.get_member(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error(&context.path, "type", &format!("struct '{}' has no member '{}' (variadic)", custom_type_name, after_dot_name)));
                                    },
                                }
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error(&context.path, "type", &format!("struct '{}' has no member '{}' (variadic default)", custom_type_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", custom_type_name, after_dot_name);
                                return value_type_func_proc(&context.path, &e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error(&context.path, "type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    custom_type_name, after_dot_name, value_type_to_str(&member_decl.value_type))));
                            },
                        }
                    },

                    _ => {
                        return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            _ => {
                return get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol)
            },
        }

    } else {
        return Err(e.error(&context.path, "type", &format!("Undefined symbol '{}'", &f_name)));
    }
}

pub fn get_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {
    match &e.node_type {
        NodeType::LLiteral(Literal::Number(_)) => Ok(ValueType::TCustom("I64".to_string())),
        NodeType::LLiteral(Literal::Bool(_)) => Ok(ValueType::TCustom("Bool".to_string())),
        NodeType::LLiteral(Literal::Str(_)) => Ok(ValueType::TCustom("Str".to_string())),
        NodeType::LLiteral(Literal::List(_)) => Ok(ValueType::TCustom("List".to_string())),
        NodeType::FuncDef(func_def) => match func_def.function_type {
            FunctionType::FTFunc | FunctionType::FTFuncExt => Ok(ValueType::TFunction(FunctionType::FTFunc)),
            FunctionType::FTProc | FunctionType::FTProcExt => Ok(ValueType::TFunction(FunctionType::FTProc)),
            FunctionType::FTMacro => Ok(ValueType::TFunction(FunctionType::FTMacro)),
        },
        NodeType::EnumDef(_) => Ok(ValueType::TType(TTypeDef::TEnumDef)),
        NodeType::StructDef(_) => Ok(ValueType::TType(TTypeDef::TStructDef)),
        NodeType::FCall => get_fcall_value_type(context, e),
        NodeType::Range => Ok(ValueType::TCustom(format!("{}Range", value_type_to_str(&get_value_type(&context, e.get(0)?)?)))),

        NodeType::Identifier(name) => {
            let mut current_type = match context.symbols.get(name) {
                Some(symbol_info_m) => {
                    symbol_info_m.value_type.clone()
                },
                None => return Err(e.error(&context.path, "type", &format!("Undefined symbol '{}'", name))),
            };

            // If there are no parameters, just return the type of the first identifier
            if e.params.is_empty() {
                return Ok(current_type);
            }

            // Now, process each nested member.
            for cursor in &e.params {
                let member_name = match &cursor.node_type {
                    NodeType::Identifier(n) => n,
                    node_type => return Err(e.lang_error("type", &format!("Identifiers can only contain identifiers, found '{:?}'", node_type))),
                };

                match &current_type {
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // If it's a struct, resolve its member
                        let struct_def = context.struct_defs.get(name)
                            .ok_or_else(|| e.error(&context.path, "type", &format!("Struct '{}' not found", name)))?;

                        let decl = struct_def.get_member_or_err(member_name, name, &context.path, e)?;
                        current_type = decl.value_type.clone();
                    },
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        // If it's an enum, resolve the variant
                        let enum_def = context.enum_defs.get(name)
                            .ok_or_else(|| e.error(&context.path, "type", &format!("Enum '{}' not found", name)))?;

                        if enum_def.enum_map.contains_key(member_name) {
                            return Ok(ValueType::TCustom(name.to_string()));
                        } else {
                            return Err(e.error(&context.path, "type", &format!("Enum '{}' has no value '{}'", name, member_name)));
                        }
                    },
                    ValueType::TCustom(custom_type_name) => {
                        // If it's a custom type (a struct), resolve the member
                        let struct_def = context.struct_defs.get(custom_type_name)
                            .ok_or_else(|| e.error(&context.path, "type", &format!("Struct '{}' not found", custom_type_name)))?;

                        let decl = struct_def.get_member_or_err(member_name, custom_type_name, &context.path, e)?;
                        current_type = decl.value_type.clone();
                    },
                    ValueType::TMulti(_variadic_type_name) => {
                        // Variadic parameters are implemented as Array at runtime
                        current_type = ValueType::TCustom("Array".to_string());
                    },
                    _ => {
                        return Err(e.error(&context.path, "type", &format!("'{}' of type '{}' can't have members", name, value_type_to_str(&current_type))));
                    }
                }
            }

            Ok(current_type) // Return the type of the last field (x)
        },

        NodeType::Pattern(PatternInfo { variant_name, .. }) => {
            // Extract enum type from "EnumType.Variant" format
            if let Some(dot_pos) = variant_name.rfind('.') {
                let enum_type = &variant_name[..dot_pos];
                Ok(ValueType::TCustom(enum_type.to_string()))
            } else {
                // If no dot, assume the whole thing is the enum type (shouldn't happen in practice)
                Ok(ValueType::TCustom(variant_name.clone()))
            }
        },

        node_type => return Err(e.error(&context.path, "type", &format!("get_value_type() not implemented for {:?} yet.", node_type))),
    }
}

// Import declarations only (no eval) - for init phase
// This processes imports during declaration indexing, copying only declarations
// to the parent context. The eval phase will later initialize values.
fn init_import_declarations(context: &mut Context, e: &Expr, import_path_str: &str) -> Result<(), String> {
    let path = format!("{}{}", import_path_str, ".til");
    let original_path = context.path.clone();

    // Check if already processed for declarations
    if context.imports_declarations_done.contains(&path) {
        return Ok(()); // Already imported declarations
    }

    // Check for circular imports
    if context.imports_wip.contains(&path) {
        return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}: Circular import dependency",
                                              path, original_path)));
    }

    // Mark as work-in-progress
    if !context.imports_wip.insert(path.clone()) {
        return Err(e.lang_error("import", &format!("While trying to import {} from {}: Can't insert in imports_wip",
                                                   path, original_path)));
    }

    // Read and parse the imported file
    let source: String = match fs::read_to_string(&path) {
        Ok(file) => file,
        Err(error) => {
            context.imports_wip.remove(&path);
            return match error.kind() {
                ErrorKind::NotFound => Err(e.error(&context.path, "import", &format!("File '{}' not found", path))),
                other_error => Err(e.error(&context.path, "import", &format!("Problem reading file '{}': {}", path, other_error))),
            };
        },
    };

    context.path = path.clone();

    // Lex the imported file
    let mut lexer = match lexer_from_source(&path, source) {
        Ok(lexer) => lexer,
        Err(error_string) => {
            let orig_path_clone = original_path.clone();
            context.path = original_path;
            context.imports_wip.remove(&path);
            return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Parse mode
    let mode = match parse_mode(&path, &mut lexer) {
        Ok(mode_) => mode_,
        Err(error_string) => {
            let orig_path_clone = original_path.clone();
            context.path = original_path;
            context.imports_wip.remove(&path);
            return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Check if mode can be imported
    if !can_be_imported(&mode) {
        context.path = original_path;
        context.imports_wip.remove(&path);
        return Err(e.error(&context.path, "import", &format!("file '{}' of mode '{}' cannot be imported", path, mode.name)));
    }

    let previous_mode = context.mode.clone();
    context.mode = mode;

    // Process mode imports recursively
    for import_str in context.mode.imports.clone() {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall, params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};
        if let Err(error_string) = init_import_declarations(context, &import_fcall_expr, &import_str) {
            context.mode = previous_mode;
            context.path = original_path;
            context.imports_wip.remove(&path);
            return Err(error_string);
        }
    }

    // Parse to AST
    let imported_ast: Expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            context.mode = previous_mode;
            let orig_path_clone = original_path.clone();
            context.path = original_path;
            context.imports_wip.remove(&path);
            return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Run init_context to extract declarations
    // This will recursively handle any imports in the imported file
    let errors = init_context(context, &imported_ast);
    if errors.len() > 0 {
        context.mode = previous_mode;
        let orig_path_clone = original_path.clone();
        context.path = original_path;
        context.imports_wip.remove(&path);
        let mut error_msg = format!("While trying to import {} from {}:\n", path, orig_path_clone);
        for err in &errors {
            error_msg.push_str(&format!("{}:{}\n", path, err));
        }
        return Err(error_msg);
    }

    // Restore context state
    context.mode = previous_mode;
    context.path = original_path;
    context.imports_wip.remove(&path);

    // Cache that we've processed this import's declarations
    context.imports_declarations_done.insert(path);

    Ok(())
}

// aka "context priming" or "declaration indexing"
pub fn init_context(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                errors.extend(init_context(context, &se));
            }
        },
        NodeType::FCall => {
            let f_name = get_func_name_in_call(&e);
            if f_name == "import" {
                // Extract import path (must be literal string)
                let import_path_expr = match e.get(1) {
                    Ok(import_path_expr_) => import_path_expr_,
                    Err(err) => {
                        errors.push(e.exit_error("import", &format!("{}:{}", context.path, err)));
                        return errors
                    },
                };
                let import_path = match &import_path_expr.node_type {
                    NodeType::LLiteral(import_path_str_lit_expr) => match import_path_str_lit_expr {
                        Literal::Str(import_path_) => import_path_,
                        literal_type => {
                            errors.push(import_path_expr.exit_error("import", &format!("Expected literal 'Str' for import, found literal '{:?}'",
                                                                                       literal_type)));
                            return errors
                        },

                    },
                    import_node_type => {
                        errors.push(import_path_expr.exit_error("import", &format!("Expected literal Str for import, found '{:?}'",
                                                                                   import_node_type)));
                        return errors
                    },
                };

                // Process import declarations (no eval)
                match init_import_declarations(context, &e, import_path) {
                    Ok(_) => {},
                    Err(err) => {
                        errors.push(err);
                        return errors;
                    },
                }
            }
        },
        NodeType::Declaration(decl) => {
            if context.funcs.contains_key(&decl.name) || context.symbols.contains_key(&decl.name) {
                errors.push(e.error(&context.path, "type", &format!("'{}' already declared.", decl.name)));
            }
            if e.params.len() != 1 {
                errors.push(e.exit_error("type", &format!("in init_context, while declaring {}, declarations must take exactly one value.", decl.name)));
                return errors
            }
            let inner_e = match e.get(0) {
                Ok(inner_e_) => inner_e_,
                Err(error_str) => {
                    errors.push(error_str);
                    return errors
                },
            };
            let mut value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            if decl.value_type != str_to_value_type(INFER_TYPE) {
                if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
                    value_type = decl.value_type.clone();
                } else if value_type != decl.value_type {
                    errors.push(e.error(&context.path, "type", &format!("'{}' declared of type '{}' but initialized to type '{}'.",
                                                         decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type))));
                }
            }
            match value_type {
                ValueType::TFunction(ref ftype) => match ftype {
                    FunctionType::FTFunc | FunctionType::FTFuncExt |
                    FunctionType::FTProc | FunctionType::FTProcExt |
                    FunctionType::FTMacro => {
                        match &inner_e.node_type {
                            NodeType::FuncDef(func_def) => {
                                context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own });
                                context.funcs.insert(decl.name.to_string(), func_def.clone());
                            },
                            _ => {
                                errors.push(e.lang_error("type", &format!("{}s should have definitions", value_type_to_str(&value_type))));
                                return errors;
                            },
                        }
                    }
                },

                ValueType::TType(TTypeDef::TEnumDef) => {
                    if inner_e.params.len() != 0 {
                        errors.push(e.exit_error("type", &format!("while declaring {}: enum declarations don't have any parameters in the tree.",
                                                                  decl.name)));
                        return errors
                    }
                    match &inner_e.node_type {
                        NodeType::EnumDef(enum_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own });
                            context.enum_defs.insert(decl.name.to_string(), enum_def.clone());
                        },
                        _ => {
                            errors.push(e.lang_error("type", "enums should have definitions."));
                            return errors;
                        },
                    }
                },

                ValueType::TType(TTypeDef::TStructDef) => {
                    if inner_e.params.len() != 0 {
                        errors.push(e.exit_error("type", &format!("while declaring {}, struct declarations must have exactly 0 params.",
                                                                  decl.name)));
                        return errors
                    }
                    match &inner_e.node_type {
                        NodeType::StructDef(struct_def) => {
                            // Register the struct itself
                            context.symbols.insert(decl.name.to_string(), SymbolInfo { value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own });
                            context.struct_defs.insert(decl.name.to_string(), struct_def.clone());
                            // Register associated funcs and constants (non-mut members only)
                            for (member_name, member_decl) in &struct_def.members {
                                if member_decl.is_mut {
                                    continue; // Skip instance fields
                                }
                                // Try to find a default_value (required for funcs/consts)
                                if let Some(member_expr) = struct_def.default_values.get(member_name) {
                                    let member_value_type = get_value_type(&context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                                    let full_name = format!("{}.{}", decl.name, member_name); // Note: using '.' not '::'
                                    // Register in symbols
                                    context.symbols.insert(full_name.clone(), SymbolInfo { value_type: member_value_type.clone(), is_mut: member_decl.is_mut, is_copy: member_decl.is_copy, is_own: member_decl.is_own });
                                    // If it's a function, also register in funcs
                                    if let NodeType::FuncDef(func_def) = &member_expr.node_type {
                                        context.funcs.insert(full_name, func_def.clone());
                                    }
                                }
                            }
                        },
                        _ => {
                            errors.push(e.lang_error("type", "struct declarations should have definitions."));
                            return errors;
                        },
                    }
                }

                ValueType::TMulti(_) | ValueType::TCustom(_) => {
                    context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own });
                },
            }
        }
        _ => {
            if !context.mode.allows_base_anything {
                if context.mode.allows_base_calls {
                    errors.push(e.error(&context.path, "mode", &format!("mode '{}' allows only declarations and calls in the root context, found {:?}.",
                                                         context.mode.name, e.node_type)));
                } else {
                    errors.push(e.error(&context.path, "mode", &format!("mode '{}' allows only declarations in the root context, found {:?}.",
                                                         context.mode.name, e.node_type)));
                }
            }
        },
    }
    errors
}
#[derive(Clone)]
pub struct Context {
    pub mode: ModeDef, // All contexts need a mode
    // TODO use Context.path to properly report eval errors, or...no, don't refactor the whole eval phase to return Result<String, String>
    pub path: String, // this is needed for core func "loc"
    // All declared symbols (types, constants, variables, and function names)
    // This is necessary for so called "context priming" or "declaration indexing"
    // aka declaring things in whatever order, aka not needing forward declarations
    // in theory it should only be needed for the "type" phase after the init context phase
    // but it can be convenient at times in eval or compile phases too, I guess.
    pub symbols: HashMap<String, SymbolInfo>,
    // All functions, with their function types, signatures and bodies (functions, methods, macros, etc).
    pub funcs: HashMap<String, SFuncDef>,
    // Enum type definitions (variants and associated data)
    pub enum_defs: HashMap<String, SEnumDef>,
    // Struct type definitions (fields and associated constants [including functions, structs are namespaces, almost])
    pub struct_defs: HashMap<String, SStructDef>,
    // maps variable names to their offsets in the arena
    pub arena_index: HashMap<String, usize>, // stores offsets
    // Temporary storage for enum payload data during construction
    pub temp_enum_payload: Option<(Vec<u8>, ValueType)>, // (payload_bytes, payload_type)
    // Two-phase imports: separate caches for declaration and value initialization
    pub imports_declarations_done: HashSet<String>, // tracks which imports have had declarations copied (init phase)
    pub imports_values_done: HashMap<String, Result<EvalResult, String>>, // tracks which imports have had values initialized (eval phase)
    pub imports_wip: HashSet<String>, // wip imports (for cycle detection)
    // DEPRECATED: old single-phase cache, kept for compatibility
    #[allow(dead_code)]
    imports_done: HashMap<String, Result<EvalResult, String>>,
    // REM: A hashmap for in the future return a struct (namespace) so that it can be assigned to a constant/var
    // REM: This would enable: std := import("src/core/std") and then std.panic(), std.format(), etc.
    // REM: TODO change the cached type to support import as returning a struct_def
}

impl Context {
    pub fn new(path: &String, mode_name: &str) -> Result<Context, String> {
        return Ok(Context {
            path: path.to_string(),
            mode: mode_from_name(mode_name)?,
            symbols: HashMap::new(),
            funcs: HashMap::new(),
            enum_defs: HashMap::new(),
            struct_defs: HashMap::new(),
            arena_index: HashMap::new(),
            temp_enum_payload: None,
            imports_declarations_done: HashSet::new(),
            imports_values_done: HashMap::new(),
            imports_wip: HashSet::new(),
            imports_done: HashMap::new(), // DEPRECATED
        });
    }

    pub fn get_variant_pos(selfi: &SEnumDef, variant_name: &str, e: &Expr) -> Result<i64, String> {
        match selfi.enum_map.keys().position(|k| k == variant_name) {
            Some(position) => Ok(position as i64),
            None => {
                return Err(e.lang_error("context", &format!("Error: Enum variant '{}' not found in enum map.", variant_name)))
            },
        }
    }

    pub fn variant_pos_to_str(selfi: &SEnumDef, position: i64, e: &Expr) -> Result<String, String> {
        let keys: Vec<String> = selfi.enum_map.keys().cloned().collect();
        if position < 0 || position >= keys.len() as i64 {
            // Return an error if the position is out of bounds
            return Err(e.lang_error("context", &format!("Error: Invalid position '{}' for enum variant in '{}'.",
                                                        position, selfi.enum_map.keys().cloned().collect::<Vec<_>>().join(", "))));
        }

        // If position is valid, return the corresponding variant name
        return Ok(keys[position as usize].clone())
    }

    pub fn get_i64(self: &Context, id: &str, e: &Expr) -> Result<i64, String> {
        match self.arena_index.get(id) {
            Some(&offset) => match Arena::g().memory[offset..offset + 8].try_into() {
                Ok(bytes) => Ok(i64::from_ne_bytes(bytes)),
                Err(_) => Err(e.lang_error("context", &format!("Invalid i64 read for id '{}'", id))),
            },
            None => Err(e.lang_error("context", &format!("i64 not found for id '{}'", id))),
        }
    }

    pub fn insert_i64(self: &mut Context, id: &str, i64_str: &String, e: &Expr) -> Result<(), String> {
        let v = i64_str.parse::<i64>()
            .map_err(|_| e.lang_error("context", &format!("Invalid i64 literal '{}'", i64_str)))?;
        let bytes = v.to_ne_bytes();

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                Arena::g().memory[offset..offset + 8].copy_from_slice(&bytes);
                return Ok(())
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&bytes);
                self.arena_index.insert(id.to_string(), offset);
                return Ok(())
            }
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(&bytes);
        self.arena_index.insert(id.to_string(), offset);
        return Ok(())
    }

    pub fn get_u8(self: &Context, id: &str, e: &Expr) -> Result<u8, String> {
        match self.arena_index.get(id) {
            Some(&offset) => Arena::g().memory.get(offset).copied()
                .ok_or_else(|| e.lang_error("context", &format!("Invalid u8 read for id '{}'", id))),
            None => Err(e.lang_error("context", &format!("u8 not found for id '{}'", id))),
        }
    }

    pub fn insert_u8(self: &mut Context, id: &str, u8_str: &String, e: &Expr) -> Result<(), String> {
        let v = u8_str.parse::<u8>()
            .map_err(|_| e.lang_error("context", &format!("Invalid u8 literal '{}'", u8_str)))?;
        let bytes = [v];

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                Arena::g().memory[offset] = v;
                return Ok(())
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&bytes);
                self.arena_index.insert(id.to_string(), offset);
                return Ok(())
            }
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(&bytes);
        self.arena_index.insert(id.to_string(), offset);
        return Ok(())
    }

    pub fn get_bool(self: &Context, id: &str, e: &Expr) -> Result<bool, String> {
        match self.arena_index.get(id) {
            Some(&offset) => match Arena::g().memory.get(offset) {
                Some(&byte) => Ok(byte == 1),
                None => Err(e.lang_error("context", &format!("Invalid bool read for id '{}'", id))),
            },
            None => Err(e.lang_error("context", &format!("bool not found for id '{}'", id))),
        }
    }

    pub fn insert_bool(self: &mut Context, id: &str, bool_str: &String, e: &Expr) -> Result<(), String> {
        let is_mut = match self.symbols.get(id) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return Err(e.lang_error("context", &format!("Symbol '{}' not found", id))),
        };

        let bool_to_insert = bool_str.parse::<bool>()
            .map_err(|_| e.lang_error("context", &format!("Invalid bool literal '{}'", bool_str)))?;
        let stored = if bool_to_insert { 1 } else { 0 };
        let bytes = [stored];

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                Arena::g().memory[offset] = stored;
                return Ok(())
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&bytes);
                self.arena_index.insert(id.to_string(), offset);
                return Ok(())
            }
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(&bytes);

        // Insert Bool data field too
        let field_id = format!("{}.data", id);
        self.symbols.insert(field_id.clone(), SymbolInfo {
            value_type: ValueType::TCustom("U8".to_string()),
            is_mut: is_mut,
            is_copy: false,
            is_own: false,
        });
        self.arena_index.insert(field_id, offset);

        self.arena_index.insert(id.to_string(), offset);
        return Ok(())
    }

    pub fn map_instance_fields(&mut self, custom_type_name: &str, instance_name: &str, e: &Expr) -> Result<(), String> {
        let struct_def = self.struct_defs.get(custom_type_name)
            .ok_or_else(|| e.lang_error("context", &format!("map_instance_fields: definition for '{}' not found", custom_type_name)))?;

        let is_mut = self.symbols.get(instance_name)
            .ok_or_else(|| e.lang_error("context", &format!("map_instance_fields: instance '{}' not found in symbols", instance_name)))?
            .is_mut;

        let base_offset = *self.arena_index.get(instance_name)
            .ok_or_else(|| e.lang_error("context", &format!("map_instance_fields: base offset for '{}' not found", instance_name)))?;

        let members: Vec<(String, Declaration)> = struct_def
            .members
            .iter()
            .map(|(k, v)| (k.clone(), v.clone()))
            .collect();

        let mut current_offset = 0;
        for (field_name, decl) in members {
            if decl.is_mut {
                let combined_name = format!("{}.{}", instance_name, field_name);
                let field_offset = base_offset + current_offset;
                self.arena_index.insert(combined_name.clone(), field_offset);

                self.symbols.insert(
                    combined_name.clone(),
                    SymbolInfo {
                        value_type: decl.value_type.clone(),
                        is_mut,
                        is_copy: false,
                        is_own: false,
                    },
                );

                if let ValueType::TCustom(type_name) = &decl.value_type {
                    if self.struct_defs.contains_key(type_name) {
                        self.map_instance_fields(type_name, &combined_name, e).map_err(|_| {
                            e.lang_error("context", &format!("map_instance_fields: failed to map nested struct field '{}'", combined_name))
                        })?;
                    }
                }

                let field_size = match &decl.value_type {
                    ValueType::TCustom(name) => self.get_type_size(name)?,
                    _ => return Err(e.lang_error("context", &format!(
                        "map_instance_fields: Unsupported value type '{}'", value_type_to_str(&decl.value_type)
                    ))),
                };

                current_offset += field_size;
            }
            // Immutable struct fields are handled generically through struct_defs
        }
        return Ok(())
    }

    // TODO all args should be passed as pointers/references and we wouldn't need this
    pub fn copy_fields(&mut self, custom_type_name: &str, src: &str, dest: &str, e: &Expr) -> Result<(), String> {
        let struct_def = self.struct_defs.get(custom_type_name)
            .ok_or_else(|| e.lang_error("context", &format!("copy_fields: definition for '{}' not found", custom_type_name)))?;

        let is_mut = self.symbols.get(dest)
            .ok_or_else(|| e.lang_error("context", &format!("copy_fields: destination symbol '{}' not found", dest)))?
            .is_mut;

        let dest_base_offset = *self.arena_index.get(dest)
            .ok_or_else(|| e.lang_error("context", &format!("copy_fields: destination arena offset for '{}' not found", dest)))?;

        let members: Vec<(String, Declaration)> = struct_def
            .members
            .iter()
            .map(|(k, v)| (k.clone(), v.clone()))
            .collect();

        let mut current_offset = 0;
        for (field_name, decl) in members {
            if !decl.is_mut {
                continue;
            }

            let field_size = match &decl.value_type {
                ValueType::TCustom(name) => self.get_type_size(name)?,
                _ => return Err(e.lang_error("context", &format!("copy_fields: unsupported field type '{}'", value_type_to_str(&decl.value_type)))),
            };

            let src_key = format!("{}.{}", src, field_name);
            let dest_key = format!("{}.{}", dest, field_name);

            // Skip if source field doesn't exist (e.g., is_dyn in Array but not in Vec)
            let src_offset = match self.arena_index.get(&src_key) {
                Some(offset) => *offset,
                None => {
                    current_offset += field_size;
                    continue;
                }
            };

            let dest_offset = dest_base_offset + current_offset;

            self.arena_index.insert(dest_key.clone(), dest_offset);
            self.symbols.insert(dest_key.clone(), SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut,
                is_copy: false,
                is_own: false,
            });

            Arena::g().memory.copy_within(src_offset..src_offset + field_size, dest_offset);

            if let ValueType::TCustom(type_name) = &decl.value_type {
                if self.struct_defs.contains_key(type_name) {
                    self.copy_fields(type_name, &src_key, &dest_key, e).map_err(|_| {
                        e.lang_error("context", &format!("copy_fields: failed to recursively copy field '{}'", dest_key))
                    })?;
                }
            }

            current_offset += field_size;
        }

        Ok(())
    }

    pub fn get_type_size(&self, type_name: &str) -> Result<usize, String> {
        match type_name {
            "U8"   => return Ok(1),
            "I64"  => return Ok(8),
            _ => {},
        }
        if let Some(enum_def) = self.enum_defs.get(type_name) {
            // Calculate maximum variant size (8 bytes for tag + largest payload)
            let mut max_size = 8; // Start with tag size

            for (_variant_name, payload_type_opt) in &enum_def.enum_map {
                if let Some(payload_type) = payload_type_opt {
                    let payload_size = match payload_type {
                        ValueType::TCustom(t) => self.get_type_size(t)?,
                        _ => {
                            return Err(format!(
                                "get_type_size: unsupported payload type in enum '{}': {:?}",
                                type_name, payload_type
                            ));
                        }
                    };
                    let variant_total = 8 + payload_size; // tag + payload
                    if variant_total > max_size {
                        max_size = variant_total;
                    }
                }
            }

            return Ok(max_size);
        }

        if let Some(struct_def) = self.struct_defs.get(type_name) {
            let mut total_size = 0;

            for (field_name, decl) in &struct_def.members {
                if !decl.is_mut {
                    continue;
                }

                let field_size = match &decl.value_type {
                    ValueType::TCustom(t) => {
                        self.get_type_size(t)?
                    }
                    _ => {
                        return Err(format!(
                            "get_type_size: unsupported value type '{}' in '{}.{}'",
                            value_type_to_str(&decl.value_type),
                            type_name,
                            field_name
                        ));
                    }
                };

                total_size += field_size;
            }

            Ok(total_size)
        } else {
            Err(format!("get_type_size: type '{}' not found in struct or enum defs", type_name))
        }
    }

    pub fn insert_struct(&mut self, id: &str, custom_type_name: &str, e: &Expr) -> Result<(), String> {
        // Lookup the struct definition
        let struct_def = match self.struct_defs.get(custom_type_name) {
            Some(struct_def_) => struct_def_.clone(),
            None => return Err(e.lang_error("context", &format!("insert_struct: definition for '{}' not found", custom_type_name))),
        };

        // Determine mutability from symbols table
        let is_mut = match self.symbols.get(id) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return Err(e.lang_error("context", &format!("insert_struct: id '{}' for struct '{}' not found in symbols", id, custom_type_name))),
        };

        // Calculate total size (for now no alignment)
        let mut total_size = 0;
        let mut field_offsets = HashMap::new();

        for (member_name, decl) in struct_def.members.iter() {
            if !decl.is_mut {
                continue;
            }

            let field_size = match &decl.value_type {
                ValueType::TCustom(type_name) => self.get_type_size(type_name)?,
                _ => return Err(e.lang_error("context", "insert_struct: Unsupported value type in struct")),
            };

            field_offsets.insert(member_name.clone(), total_size);
            total_size += field_size;
        }

        // Allocate blob in arena
        let offset = Arena::g().memory.len();
        Arena::g().memory.resize(offset + total_size, 0);
        self.arena_index.insert(id.to_string(), offset);

        // Store each field's default value
        for (member_name, decl) in struct_def.members.iter() {
            if !decl.is_mut {
                continue;
            }

            let field_offset = match field_offsets.get(member_name) {
                Some(offset) => offset,
                None => return Err(e.lang_error("context", &format!("insert_struct: Missing field offset for '{}'", member_name))),
            };

            let default_expr = struct_def.default_values.get(member_name);
            let default_value = match default_expr {
                Some(e2) => {
                    let res = eval_expr(self, e2)?;
                    if res.is_throw {
                        return Err(e.lang_error("context", &format!("insert_struct: Thrown '{}' while evaluating default value for field '{}'", res.thrown_type.unwrap_or_default(), member_name)));
                    }
                    res.value
                },
                None => return Err(e.lang_error("context", &format!("insert_struct: Missing default value for field '{}'", member_name))),
            };

            match &decl.value_type {
                ValueType::TCustom(type_name) => {
                    if let Some(enum_def) = self.enum_defs.get(type_name) {
                        let parts: Vec<&str> = default_value.split('.').collect();
                        if parts.len() != 2 || parts[0] != type_name {
                            return Err(e.lang_error("context", &format!("insert_struct: Invalid enum default value '{}' for field '{}'", default_value, member_name)));
                        }
                        let variant = parts[1];
                        let index = match enum_def.enum_map.keys().position(|v| v == variant) {
                            Some(i) => i as i64,
                            None => return Err(e.lang_error("context", &format!("insert_struct: Unknown enum variant '{}' for field '{}'", variant, member_name))),
                        };
                        Arena::g().memory[offset + field_offset..offset + field_offset + 8]
                            .copy_from_slice(&index.to_ne_bytes());
                    } else {
                        match type_name.as_str() {
                            "U8" => {
                                let v = default_value.parse::<u8>().map_err(|_| {
                                    e.lang_error("context", &format!("insert_struct: Invalid U8 default value '{}' for field '{}'", default_value, member_name))
                                })?;
                                Arena::g().memory[offset + field_offset] = v;
                            },
                            "I64" => {
                                let v = default_value.parse::<i64>().map_err(|_| {
                                    e.lang_error("context", &format!("insert_struct: Invalid I64 default value '{}' for field '{}'", default_value, member_name))
                                })?;
                                Arena::g().memory[offset + field_offset..offset + field_offset + 8]
                                    .copy_from_slice(&v.to_ne_bytes());
                            },
                            _ => {
                                if self.struct_defs.contains_key(type_name) {
                                    let combined_name = format!("{}.{}", id, member_name);
                                    self.symbols.insert(
                                        combined_name.clone(),
                                        SymbolInfo {
                                            value_type: ValueType::TCustom(type_name.clone()),
                                            is_mut: true,
                                            is_copy: false,
                                            is_own: false,
                                        },
                                    );
                                    self.arena_index.insert(combined_name.clone(), offset + field_offset);

                                    // Special case: Str initialization with string literal
                                    if type_name == "Str" {
                                        self.insert_string(&combined_name, &default_value, e)?;
                                    } else {
                                        self.insert_struct(&combined_name, type_name, e)
                                            .map_err(|_| e.lang_error("context", &format!("insert_struct: Failed to initialize nested struct '{}.{}'", id, member_name)))?;
                                    }
                                } else {
                                    return Err(e.lang_error("context", &format!("insert_struct: Unknown field type '{}'", type_name)));
                                }
                            },
                        }
                    }
                },
                _ => {
                    return Err(e.lang_error("context", &format!("insert_struct: Unsupported field value type '{}'", value_type_to_str(&decl.value_type))));
                }
            }

            let combined_name = format!("{}.{}", id, member_name);
            self.arena_index.insert(combined_name.clone(), offset + field_offset);
            self.symbols.insert(
                combined_name,
                SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut,
                    is_copy: false,
                    is_own: false,
                },
            );
        }

        // Map immutable fields by copying arena_index entries from the type to the instance
        for (_member_name, decl) in struct_def.members.iter() {
            if decl.is_mut {
                continue; // Skip mutable fields (already handled above)
            }

            // Immutable struct fields are handled generically through struct_defs
            // No special cases needed anymore
        }

        Ok(())
    }

    // Register struct field symbols for type checking without evaluating defaults or allocating memory
    // This allows type checking of struct method bodies without triggering evaluation errors
    pub fn register_struct_fields_for_typecheck(&mut self, instance_name: &str, struct_type_name: &str) {
        if let Some(struct_def) = self.struct_defs.get(struct_type_name).cloned() {
            for (member_name, decl) in &struct_def.members {
                let combined_name = format!("{}.{}", instance_name, member_name);
                self.symbols.insert(
                    combined_name.clone(),
                    SymbolInfo {
                        value_type: decl.value_type.clone(),
                        is_mut: decl.is_mut,
                        is_copy: decl.is_copy,
                        is_own: decl.is_own,
                    },
                );

                // Recursively register nested struct fields
                if let ValueType::TCustom(ref nested_type) = decl.value_type {
                    if self.struct_defs.contains_key(nested_type) {
                        self.register_struct_fields_for_typecheck(&combined_name, nested_type);
                    }
                }
            }
        }
    }

    pub fn get_string(&self, id: &str, e: &Expr) -> Result<String, String> {
        let c_string_offset = match self.arena_index.get(&format!("{}.c_string", id)) {
            Some(offset) => *offset,
            None => return Err(e.lang_error("context", &format!("missing field '{}.c_string'", id))),
        };
        let cap_offset = match self.arena_index.get(&format!("{}.cap", id)) {
            Some(offset) => *offset,
            None => return Err(e.lang_error("context", &format!("missing field '{}.cap'", id))),
        };

        if c_string_offset + 8 > Arena::g().memory.len() || cap_offset + 8 > Arena::g().memory.len() {
            return Err(e.lang_error("context", &format!("field offsets out of bounds for '{}'", id)));
        }

        let c_string_ptr_bytes = &Arena::g().memory[c_string_offset..c_string_offset + 8];
        let c_string_ptr = match c_string_ptr_bytes.try_into() {
            Ok(arr) => i64::from_ne_bytes(arr) as usize,
            Err(_) => return Err(e.lang_error("context", &format!("failed to read c_string pointer for '{}'", id))),
        };

        let cap_bytes = &Arena::g().memory[cap_offset..cap_offset + 8];
        let length = match cap_bytes.try_into() {
            Ok(arr) => i64::from_ne_bytes(arr) as usize,
            Err(_) => return Err(e.lang_error("context", &format!("failed to read cap value for '{}'", id))),
        };

        if c_string_ptr + length > Arena::g().memory.len() {
            return Err(e.lang_error("context", &format!("string content out of bounds for '{}'", id)));
        }

        let bytes = &Arena::g().memory[c_string_ptr..c_string_ptr + length];
        return Ok(String::from_utf8_lossy(bytes).to_string());
    }

    pub fn insert_string(self: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        let is_field = id.contains('.');

        // Allocate string data
        let string_offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(value_str.as_bytes());
        Arena::g().memory.push(0); // null terminator
        let string_offset_bytes = (string_offset as i64).to_ne_bytes();
        let len_bytes = (value_str.len() as i64).to_ne_bytes();

        if is_field {
            if let Some(&base_offset) = self.arena_index.get(id) {
                if let Some(str_def) = self.struct_defs.get("Str") {
                    let mut current_offset = 0;

                    for (member_name, decl) in str_def.members.iter() {
                        if !decl.is_mut {
                            continue;
                        }

                        let type_size = self.get_type_size(&value_type_to_str(&decl.value_type))?;
                        let absolute_offset = base_offset + current_offset;
                        let target_slice = &mut Arena::g().memory[absolute_offset..absolute_offset + type_size];

                        if member_name == "c_string" {
                            target_slice.copy_from_slice(&string_offset_bytes);
                        } else if member_name == "cap" {
                            target_slice.copy_from_slice(&len_bytes);
                        }

                        self.arena_index.insert(format!("{}.{}", id, member_name), absolute_offset);
                        current_offset += type_size;
                    }
                    return Ok(())
                }
                return Err(e.lang_error("context", "ERROR: 'Str' struct definition not found"))
            }

            // Not yet inserted — insert fresh inlined Str
            if let Some(str_def) = self.struct_defs.get("Str") {
                let struct_offset = Arena::g().memory.len();
                let mut current_offset = 0;

                for (member_name, decl) in str_def.members.iter() {
                    if !decl.is_mut {
                        continue;
                    }

                    let type_size = self.get_type_size(&value_type_to_str(&decl.value_type))?;
                    if Arena::g().memory.len() < struct_offset + current_offset + type_size {
                        Arena::g().memory.resize(struct_offset + current_offset + type_size, 0);
                    }

                    let field_slice = &mut Arena::g().memory[struct_offset + current_offset..struct_offset + current_offset + type_size];
                    if member_name == "c_string" {
                        field_slice.copy_from_slice(&string_offset_bytes);
                    } else if member_name == "cap" {
                        field_slice.copy_from_slice(&len_bytes);
                    }

                    self.arena_index.insert(format!("{}.{}", id, member_name), struct_offset + current_offset);
                    current_offset += type_size;
                }

                self.arena_index.insert(id.to_string(), struct_offset);
                return Ok(())
            }
            return Err(e.lang_error("context", "'Str' struct definition not found"))
        }

        self.insert_struct(id, "Str", e)?;
        let c_string_offset = match self.arena_index.get(&format!("{}.c_string", id)) {
            Some(&offset) => offset,
            None => {
                return Err(e.lang_error("context", &format!("insert_string: missing '{}.c_string'", id)))
            }
        };
        let cap_offset = match self.arena_index.get(&format!("{}.cap", id)) {
            Some(&offset) => offset,
            None => {
                return Err(e.lang_error("context", &format!("insert_string: missing '{}.cap'", id)))
            }
        };

        Arena::g().memory[c_string_offset..c_string_offset + 8].copy_from_slice(&string_offset_bytes);
        Arena::g().memory[cap_offset..cap_offset + 8].copy_from_slice(&len_bytes);

        return Ok(())
    }

    /// Helper function to insert primitive types (I64, U8, Bool, Str) based on value_type
    pub fn insert_primitive(
        &mut self,
        var_name: &str,
        value_type: &ValueType,
        value: &str,
        e: &Expr
    ) -> Result<(), String> {
        match value_type {
            ValueType::TCustom(type_name) if type_name == "I64" => {
                self.insert_i64(var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "U8" => {
                self.insert_u8(var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "Bool" => {
                self.insert_bool(var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "Str" => {
                self.insert_string(var_name, &value.to_string(), e)
            },
            _ => Err(e.lang_error("eval", &format!("insert_primitive: Unsupported type {:?}", value_type)))
        }
    }

    pub fn get_enum_at_offset(&self, enum_type: &str, offset: usize, e: &Expr) -> Result<EnumVal, String> {
        // Read enum from a specific offset (used for nested enum payloads)
        let enum_value_bytes = &Arena::g().memory[offset..offset + 8];
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error("context", "get_enum_at_offset: Failed to convert bytes to i64"))?);

        let enum_def = self.enum_defs.get(enum_type)
            .ok_or_else(|| e.lang_error("context", &format!("get_enum_at_offset: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.enum_map.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload - recursively determine size
                let payload_size = self.get_payload_size_for_type(vtype, offset + 8, e)?;
                if payload_size > 0 {
                    let payload_offset = offset + 8;
                    let payload_end = payload_offset + payload_size;
                    if payload_end <= Arena::g().memory.len() {
                        let payload_bytes = Arena::g().memory[payload_offset..payload_end].to_vec();
                        (Some(payload_bytes), Some(vtype.clone()))
                    } else {
                        (None, None)
                    }
                } else {
                    (None, None)
                }
            },
            _ => (None, None),
        };

        Ok(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name,
            payload: payload_data,
            payload_type,
        })
    }

    pub fn get_payload_size_for_type(&self, vtype: &ValueType, offset: usize, e: &Expr) -> Result<usize, String> {
        match vtype {
            ValueType::TCustom(type_name) if type_name == "I64" => Ok(8),
            ValueType::TCustom(type_name) => {
                match self.symbols.get(type_name) {
                    Some(type_symbol) => {
                        match &type_symbol.value_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                self.get_type_size(type_name).map_err(|e| e.to_string())
                            },
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                // Recursively get the inner enum's size
                                let inner_enum = self.get_enum_at_offset(type_name, offset, e)?;
                                let mut total_size = 8; // variant tag
                                if let Some(inner_payload) = &inner_enum.payload {
                                    total_size += inner_payload.len();
                                }
                                Ok(total_size)
                            },
                            _ => Ok(0),
                        }
                    },
                    None => Ok(0),
                }
            },
            _ => Ok(0),
        }
    }

    pub fn get_enum(&self, id: &str, e: &Expr) -> Result<EnumVal, String> {
        let symbol_info = self.symbols.get(id)
            .ok_or_else(|| e.lang_error("context", &format!("get_enum: Symbol '{}' not found", id)))?;

        let enum_type = match &symbol_info.value_type {
            ValueType::TCustom(custom_type_name) => custom_type_name,
            _ => return Err(e.lang_error("context", &format!("get_enum: '{}' is not a custom enum type", id))),
        };

        let offset = *self.arena_index.get(id)
            .ok_or_else(|| e.lang_error("context", &format!("get_enum: Arena index for '{}' not found", id)))?;

        let enum_value_bytes = &Arena::g().memory[offset..offset + 8];
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error("context", &format!("get_enum: Failed to convert bytes to i64 for '{}'", id)))?);

        let enum_def = self.enum_defs.get(enum_type)
            .ok_or_else(|| e.lang_error("context", &format!("get_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.enum_map.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload, read it from arena
                let payload_size = match vtype {
                    ValueType::TCustom(type_name) if type_name == "Bool" => 1,
                    ValueType::TCustom(type_name) if type_name == "I64" => 8,
                    ValueType::TCustom(type_name) if type_name == "Str" => {
                        16  // Str is always 16 bytes (pointer + size)
                    },
                    ValueType::TCustom(type_name) => {
                        // Check if this is a struct or enum type
                        match self.symbols.get(type_name) {
                            Some(type_symbol) => {
                                match &type_symbol.value_type {
                                    ValueType::TType(TTypeDef::TStructDef) => {
                                        // Get struct size
                                        self.get_type_size(type_name).unwrap_or(0)
                                    },
                                    ValueType::TType(TTypeDef::TEnumDef) => {
                                        // For enum payloads, recursively get the enum to determine size
                                        let inner_enum = self.get_enum_at_offset(type_name, offset + 8, e)?;
                                        // Size is: 8 bytes (tag) + payload bytes
                                        let mut total_size = 8;
                                        if let Some(inner_payload) = &inner_enum.payload {
                                            total_size += inner_payload.len();
                                        }
                                        total_size
                                    },
                                    _ => 0,
                                }
                            },
                            None => 0,
                        }
                    },
                    _ => 0,
                };
                if payload_size > 0 {
                    let payload_offset = offset + 8;
                    let payload_end = payload_offset + payload_size;
                    if payload_end <= Arena::g().memory.len() {
                        let payload_bytes = Arena::g().memory[payload_offset..payload_end].to_vec();
                        (Some(payload_bytes), Some(vtype.clone()))
                    } else {
                        (None, None)
                    }
                } else {
                    (None, None)
                }
            },
            _ => (None, None),
        };

        Ok(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name,
            payload: payload_data,
            payload_type,
        })
    }

    // TODO Context.insert_enum gets an Expr for errors, any Context method that can throw should too
    pub fn insert_enum(&mut self, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
        let enum_def = self.enum_defs.get(enum_type)
            .ok_or_else(|| e.lang_error("context", &format!("insert_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = pre_normalized_enum_name.split('.').last()
            .ok_or_else(|| e.lang_error("context", &format!("insert_enum: Invalid enum name format '{}'", pre_normalized_enum_name)))?;

        let enum_value = Context::get_variant_pos(enum_def, enum_name, e)?;

        // Check if there's payload data to store
        let (payload_data, payload_type) = match &self.temp_enum_payload {
            Some((data, vtype)) => (Some(data.clone()), Some(vtype.clone())),
            None => (None, None),
        };

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                // Update existing enum value
                Arena::g().memory[offset..offset + 8].copy_from_slice(&enum_value.to_le_bytes());
                // Store payload if present
                if let Some(payload_bytes) = &payload_data {
                    let payload_offset = offset + 8;
                    let payload_end = payload_offset + payload_bytes.len();
                    // Ensure arena has enough space
                    if Arena::g().memory.len() < payload_end {
                        Arena::g().memory.resize(payload_end, 0);
                    }
                    Arena::g().memory[payload_offset..payload_end].copy_from_slice(&payload_bytes);
                }
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes());
                // Store payload if present
                if let Some(payload_bytes) = &payload_data {
                    Arena::g().memory.extend_from_slice(&payload_bytes);
                }
                self.arena_index.insert(id.to_string(), offset);
            }
        } else {
            let offset = Arena::g().memory.len();
            Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes());
            // Store payload if present
            if let Some(payload_bytes) = &payload_data {
                Arena::g().memory.extend_from_slice(&payload_bytes);
            }
            self.arena_index.insert(id.to_string(), offset);
        }

        // Clear the temp payload after using it
        self.temp_enum_payload = None;

        Ok(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name: enum_name.to_string(),
            payload: payload_data,
            payload_type,
        })
    }

    pub fn insert_array(&mut self, name: &str, elem_type: &str, values: &Vec<String>, e: &Expr) -> Result<(), String> {
        // All array types now use the generic Array
        let array_type = "Array".to_string();

        self.insert_struct(name, &array_type, e)?;

        let len = values.len() as i64;
        let elem_size = match self.get_type_size(elem_type) {
            Ok(sz) => sz,
            Err(err) => return Err(e.lang_error("context", &err)),
        };
        let total_size = (len as usize) * elem_size;

        // Allocate memory
        let ptr = Arena::g().memory.len();
        Arena::g().memory.resize(ptr + total_size, 0);

        // Write values into allocated buffer
        for (i, val) in values.iter().enumerate() {
            let offset = ptr + i * elem_size;
            match elem_type {
                "Bool" => {
                    let stored = if val.as_str() == "true" { 1 } else { 0 };
                    Arena::g().memory[offset] = stored;
                },
                "U8" => {
                    match val.parse::<u8>() {
                        Ok(byte) => Arena::g().memory[offset] = byte,
                        Err(err) => return Err(e.lang_error("context", &format!("ERROR: insert_array: invalid U8 '{}'", &err)))
                    }
                },
                "I64" => {
                    match val.parse::<i64>() {
                        Ok(n) => {
                            let bytes = n.to_ne_bytes();
                            Arena::g().memory[offset..offset+8].copy_from_slice(&bytes);
                        },
                        Err(err) => return Err(e.lang_error("context", &format!("ERROR: insert_array: invalid I64 '{}'", &err)))
                    }
                },
                "Str" => {
                    for (i, val) in values.iter().enumerate() {
                        let offset = ptr + i * elem_size;

                        let temp_id = format!("{}_{}", name, i);
                        self.symbols.insert(temp_id.clone(), SymbolInfo {
                            value_type: ValueType::TCustom("Str".to_string()),
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                        });

                        self.insert_string(&temp_id, val, e)?;

                        let str_offset = match self.arena_index.get(&temp_id) {
                            Some(&off) => off,
                            None => return Err(e.lang_error("context", &format!("ERROR: insert_array: missing arena offset for '{}'", temp_id))),
                        };
                        Arena::g().memory[offset..offset + elem_size]
                            .copy_from_slice(&Arena::g().memory[str_offset..str_offset + elem_size]);
                    }
                }

                _ => {
                    return Err(e.lang_error("context", &format!("insert_array: unsupported element type '{}'", elem_type)))
                }
            }
        }

        // Write ptr, len (and cap for Vec) using arena_index
        let ptr_offset = match self.arena_index.get(&format!("{}.ptr", name)) {
            Some(o) => *o,
            None => {
                return Err(e.lang_error("context", &format!("ERROR: insert_array: missing .ptr field offset")))
            }
        };
        Arena::g().memory[ptr_offset..ptr_offset+8].copy_from_slice(&(ptr as i64).to_ne_bytes());

        // Set _len field (required for both Array and Vec)
        let len_bytes = len.to_ne_bytes();
        if let Some(len_offset) = self.arena_index.get(&format!("{}._len", name)) {
            Arena::g().memory[*len_offset..*len_offset+8].copy_from_slice(&len_bytes);
        } else {
            return Err(e.lang_error("context", &format!("ERROR: insert_array: missing ._len field offset")))
        }

        // Set cap field (only exists in Vec, not in Array)
        if let Some(cap_offset) = self.arena_index.get(&format!("{}.cap", name)) {
            Arena::g().memory[*cap_offset..*cap_offset+8].copy_from_slice(&len_bytes);
        }

        // For generic Array, also set type_name and type_size fields
        if array_type == "Array" {
            // Set type_name field (it's a Str, so we need to store it properly)
            let type_name_offset_opt = self.arena_index.get(&format!("{}.type_name", name)).copied();
            if let Some(type_name_offset) = type_name_offset_opt {
                let temp_id = format!("{}_type_name_temp", name);
                self.symbols.insert(temp_id.clone(), SymbolInfo {
                    value_type: ValueType::TCustom("Str".to_string()),
                    is_mut: false,
                    is_copy: false,
                    is_own: false,
                });
                self.insert_string(&temp_id, &elem_type.to_string(), e)?;
                if let Some(&str_offset) = self.arena_index.get(&temp_id) {
                    let str_size = self.get_type_size("Str")?;
                    Arena::g().memory[type_name_offset..type_name_offset + str_size]
                        .copy_from_slice(&Arena::g().memory[str_offset..str_offset + str_size]);
                }
            }

            // Set type_size field
            if let Some(&type_size_offset) = self.arena_index.get(&format!("{}.type_size", name)) {
                let size_bytes = (elem_size as i64).to_ne_bytes();
                Arena::g().memory[type_size_offset..type_size_offset + 8].copy_from_slice(&size_bytes);
            }
        }

        Ok(())
    }

}
