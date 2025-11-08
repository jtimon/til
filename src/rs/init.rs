use std::fs;
use std::io::ErrorKind;

use crate::Context;
use crate::SymbolInfo;
use crate::rs::lexer::{lexer_from_source};
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, FunctionType, ValueType, SFuncDef, TTypeDef, Literal,
    can_be_imported, value_type_to_str, str_to_value_type, parse_mode, parse_tokens,
};

// Init phase: Declaration indexing and import processing
// This module handles the "context priming" phase that runs before type checking.
// No eval, no arena access - declarations only.

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

fn value_type_func_proc(e: &Expr, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.returns.len() {
        0 => {
            return Err(e.error("type", &format!("func '{}' does not return anything", name)));
        },
        1 => {
            match func_def.returns.get(0) {
                Some(ValueType::TCustom(type_str)) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                Some(other) => Err(e.error("type", &format!("func '{}' returns unsupported type {}", name, value_type_to_str(other)))),
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
        return Err(e.error("type", &format!("Cannot call '{}', it is not a function or struct, it is a '{}'",
                                            &f_name, value_type_to_str(&symbol.value_type))));
    }

    // Get the last param (the method name)
    let method_name_expr = match id_expr.params.last() {
        Some(expr) => expr,
        None => return Err(e.lang_error("type", "Expected method name in UFCS call")),
    };

    let method_name = match &method_name_expr.node_type {
        NodeType::Identifier(name) => name,
        _ => return Err(e.error("type", &format!("Expected identifier for method name, found '{:?}'", method_name_expr.node_type))),
    };

    // Check if it's a regular function
    if let Some(func_def) = context.funcs.get(method_name) {
        return value_type_func_proc(&e, &f_name, func_def)
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
                return value_type_func_proc(&e, &id_expr_name, &func_def);
            }
            return Err(e.error("type", &format!("Type '{}' has no method '{}'", custom_type_name, method_name)));
        },
        _ => {
            return Err(e.error("type", &format!("'{}' of type '{}' doesn't support methods", f_name, value_type_to_str(&target_type))));
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
                    return value_type_func_proc(&e, &method_name, func_def);
                }
            }
        }
        // If we couldn't determine type or no associated method exists, fall through
    }

    // Original logic: check for standalone function
    if let Some(func_def) = context.funcs.get(&f_name) {
        return value_type_func_proc(&e, &f_name, func_def)
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
                        let member_decl = match struct_def.members.iter().find(|(k, _)| k == after_dot_name).map(|(_, v)| v) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' a", f_name, after_dot_name)));
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' b", f_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", f_name, after_dot_name);
                                return value_type_func_proc(&e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error("type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
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
                                return Err(e.error("type", &format!("enum '{}' has no variant '{}'", f_name, variant_name)));
                            },
                        };

                        // Validate argument count based on whether the variant expects a payload
                        match variant_type {
                            Some(payload_type) => {
                                // This variant expects a payload
                                if e.params.len() < 2 {
                                    return Err(e.error("type", &format!("Enum constructor {}.{} expects a payload of type {}", f_name, variant_name, value_type_to_str(payload_type))));
                                }
                                // Type check the payload argument
                                let payload_expr = e.get(1)?;
                                let payload_actual_type = get_value_type(context, payload_expr)?;

                                // Verify payload type matches expected type
                                if payload_actual_type != *payload_type {
                                    return Err(e.error("type", &format!(
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
                                    return Err(e.error("type", &format!("Enum variant {}.{} does not take a payload", f_name, variant_name)));
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
            ValueType::TCustom(custom_type_name) => { // TODO handle enums too
                let struct_def = match context.struct_defs.get(custom_type_name) {
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
                        let member_decl = match struct_def.members.iter().find(|(k, _)| k == after_dot_name).map(|(_, v)| v) {
                            Some(_member) => _member,
                            None => {
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error("type", &format!("struct '{}' has no member '{}' c", custom_type_name, after_dot_name)));
                                    },
                                }
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' d", custom_type_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", custom_type_name, after_dot_name);
                                return value_type_func_proc(&e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error("type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
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
                        let member_decl = match struct_def.members.iter().find(|(k, _)| k == after_dot_name).map(|(_, v)| v) {
                            Some(_member) => _member,
                            None => {
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error("type", &format!("struct '{}' has no member '{}' (variadic)", custom_type_name, after_dot_name)));
                                    },
                                }
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' (variadic default)", custom_type_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", custom_type_name, after_dot_name);
                                return value_type_func_proc(&e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error("type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
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
        return Err(e.error("type", &format!("Undefined symbol '{}'", &f_name)));
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
                None => return Err(e.error("type", &format!("Undefined symbol '{}'", name))),
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
                            .ok_or_else(|| e.error("type", &format!("Struct '{}' not found", name)))?;

                        match struct_def.members.iter().find(|(k, _)| k == member_name).map(|(_, v)| v) {
                            Some(decl) => {
                                current_type = decl.value_type.clone();
                            },
                            None => return Err(e.error("type", &format!("Struct '{}' has no member '{}' e", name, member_name))),
                        }
                    },
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        // If it's an enum, resolve the variant
                        let enum_def = context.enum_defs.get(name)
                            .ok_or_else(|| e.error("type", &format!("Enum '{}' not found", name)))?;

                        if enum_def.enum_map.contains_key(member_name) {
                            return Ok(ValueType::TCustom(name.to_string()));
                        } else {
                            return Err(e.error("type", &format!("Enum '{}' has no value '{}'", name, member_name)));
                        }
                    },
                    ValueType::TCustom(custom_type_name) => {
                        // If it's a custom type (a struct), resolve the member
                        let struct_def = context.struct_defs.get(custom_type_name)
                            .ok_or_else(|| e.error("type", &format!("Struct '{}' not found", custom_type_name)))?;

                        match struct_def.members.iter().find(|(k, _)| k == member_name).map(|(_, v)| v) {
                            Some(decl) => {
                                current_type = decl.value_type.clone();
                            },
                            None => return Err(e.error("type", &format!("Struct '{}' has no member '{}' f", custom_type_name, member_name))),
                        }
                    },
                    ValueType::TMulti(_variadic_type_name) => {
                        // Variadic parameters are implemented as Array at runtime
                        current_type = ValueType::TCustom("Array".to_string());
                    },
                    _ => {
                        return Err(e.error("type", &format!("'{}' of type '{}' can't have members", name, value_type_to_str(&current_type))));
                    }
                }
            }

            Ok(current_type) // Return the type of the last field (x)
        },

        node_type => return Err(e.error("type", &format!("get_value_type() not implemented for {:?} yet.", node_type))),
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
        return Err(e.error("import", &format!("While trying to import {} from {}: Circular import dependency",
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
                ErrorKind::NotFound => Err(e.error("import", &format!("File '{}' not found", path))),
                other_error => Err(e.error("import", &format!("Problem reading file '{}': {}", path, other_error))),
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
            return Err(e.error("import", &format!("While trying to import {} from {}:\n{}",
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
            return Err(e.error("import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Check if mode can be imported
    if !can_be_imported(&mode) {
        context.path = original_path;
        context.imports_wip.remove(&path);
        return Err(e.error("import", &format!("file '{}' of mode '{}' cannot be imported", path, mode.name)));
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
            return Err(e.error("import", &format!("While trying to import {} from {}:\n{}",
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
                errors.push(e.error("type", &format!("'{}' already declared.", decl.name)));
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
                    errors.push(e.error("type", &format!("'{}' declared of type '{}' but initialized to type '{}'.",
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
                                context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
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
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
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
                            context.symbols.insert(decl.name.to_string(), SymbolInfo { value_type: value_type.clone(), is_mut: decl.is_mut });
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
                                    context.symbols.insert(full_name.clone(), SymbolInfo { value_type: member_value_type.clone(), is_mut: member_decl.is_mut });
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
                    context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                },
            }
        }
        _ => {
            if !context.mode.allows_base_anything {
                if context.mode.allows_base_calls {
                    errors.push(e.error("mode", &format!("mode '{}' allows only declarations and calls in the root context, found {:?}.",
                                                         context.mode.name, e.node_type)));
                } else {
                    errors.push(e.error("mode", &format!("mode '{}' allows only declarations in the root context, found {:?}.",
                                                         context.mode.name, e.node_type)));
                }
            }
        },
    }
    errors
}
