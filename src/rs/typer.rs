use crate::Context;
use crate::rs::init::SymbolInfo;
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, ValueType, SEnumDef, SStructDef, SFuncDef, Declaration, FunctionType, TTypeDef,
    value_type_to_str, str_to_value_type,
};

// Type checking phase: Validates types, return/throw statements, mode constraints
// This module handles the type checking phase that runs after init.
// No eval, no arena access - pure type analysis.

fn check_enum_def(e: &Expr, enum_def: &SEnumDef) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_enum_def(): enum declarations don't have any parameters in the tree."));
        return errors
    }

    for (_enum_val_name, enum_opt) in &enum_def.enum_map {
        match &enum_opt {
            None => {},
            Some(value_type) => {
                match value_type {
                    ValueType::TCustom(ref _custom_type_name) => {},
                    _ => {
                        errors.push(e.todo_error("type", &format!("'enum' does not support payloads of value type '{}' yet",
                                                                  value_type_to_str(&value_type))));
                    },
                }
            },
        }
    }
    return errors;
}

pub fn check_types(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.extend(check_types(context, &p));
            }
        },
        NodeType::EnumDef(enum_def) => {
            errors.extend(check_enum_def(&e, enum_def));
        },
        NodeType::StructDef(struct_def) => {
            errors.extend(check_struct_def(context, &e, struct_def));
        },
        NodeType::If => {
            errors.extend(check_if_statement(context, &e));
        },
        NodeType::While => {
            errors.extend(check_while_statement(context, &e));
        },
        NodeType::Switch => {
            errors.extend(check_switch_statement(context, &e));
        },
        NodeType::Range => {
            if e.params.len() != 2 {
                errors.push(e.lang_error("type", "Range expression must have exactly two elements"));
                return errors;
            }

            let left_type = crate::rs::init::get_value_type(context, &e.params[0]);
            if let Err(err) = &left_type {
                errors.push(err.clone());
            }
            let right_type = crate::rs::init::get_value_type(context, &e.params[1]);
            if let Err(err) = &right_type {
                errors.push(err.clone());
            }

            if let (Ok(t1), Ok(t2)) = (left_type, right_type) {
                if t1 != t2 {
                    errors.push(e.error("type", &format!("Range start and end must be of same type, found '{}' and '{}'",
                                                         value_type_to_str(&t1), value_type_to_str(&t2))));
                }
            }
        },
        NodeType::FCall => {
            errors.extend(check_fcall(context, &e));
        },
        NodeType::FuncDef(func_def) => {
            let mut function_context = context.clone();
            errors.extend(check_func_proc_types(&func_def, &mut function_context, &e));
        },
        NodeType::Identifier(name) => {
            if !(context.funcs.contains_key(name) || context.symbols.contains_key(name)) {
                errors.push(e.error("type", &format!("Undefined symbol {}", name)));
            }
        },
        NodeType::Declaration(decl) => {
            errors.extend(check_declaration(context, &e, decl));
        },
        NodeType::Assignment(var_name) => {
            errors.extend(check_assignment(context, &e, var_name));
        },
        NodeType::Return | NodeType::Throw => {
            for return_val in &e.params {
                errors.extend(check_types(context, &return_val));
            }
        },
        NodeType::Catch => {
            errors.extend(check_catch_statement(context, &e));
        }

        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_, _) => {},
    }

    return errors
}

fn check_if_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 2 && e.params.len() != 3 {
        errors.push(e.exit_error("type", "if nodes must have 2 or 3 parameters."));
        return errors
    }

    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    let value_type = match crate::rs::init::get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };

    let first_is_condition = match value_type {
        ValueType::TCustom(type_name) => match type_name.as_str() {
            "Bool" => true,
            _ => false,
        },
        _ => false,
    };
    if !first_is_condition {
        errors.push(inner_e.error("type", &format!("'if' can only accept a bool condition first, found {:?}.", &inner_e.node_type)));
    }
    for p in e.params.iter() {
        errors.extend(check_types(context, &p));
    }
    return errors;
}

fn check_while_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 2 {
        errors.push(e.exit_error("type", "while nodes must have exactly 2 parameters."));
        return errors
    }

    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    let value_type = match crate::rs::init::get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };

    let first_is_condition = match value_type {
        ValueType::TCustom(type_name) => match type_name.as_str() {
            "Bool" => true,
            _ => false,
        },
        _ => false,
    };
    if !first_is_condition {
        errors.push(inner_e.error("type", &format!("'while' can only accept a bool condition first, found {:?}.", &inner_e.node_type)));
    }
    for p in e.params.iter() {
        errors.extend(check_types(context, &p));
    }
    return errors;
}
fn check_fcall(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();
    let f_name = crate::rs::init::get_func_name_in_call(e);
    let mut e = e.clone();
    let func_def = match get_func_def_for_fcall_with_expr(&context, &mut e) {
        Ok(func_def_) => match func_def_ {
            Some(func_def_) => func_def_,
            None => return errors, // REM: This is to allow struct instantiation
        },
        Err(err) => {
            errors.push(err);
            return errors
        },
    };

    if func_def.args.len() == 0 && e.params.len() - 1 > 0 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects 0 args, but {} were provided.", f_name, e.params.len() - 1)));
        return errors;
    }
    let has_multi_arg = func_proc_has_multi_arg(&func_def);
    if !has_multi_arg && func_def.args.len() != e.params.len() - 1 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects {} args, but {} were provided.",
                                             f_name, func_def.args.len(), e.params.len() - 1)));
    }
    if has_multi_arg && func_def.args.len() > e.params.len() - 1 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
                                             f_name, func_def.args.len(), e.params.len() - 1)));
    }

    let max_arg_def = func_def.args.len();
    for i in 0..e.params.len() - 1 {
        let arg = match func_def.args.get(std::cmp::min(i, max_arg_def - 1)) {
            Some(arg) => arg,
            None => {
                errors.push(e.lang_error("type", &format!("argument index {} out of bounds for function '{}'", i, f_name)));
                return errors;
            }
        };
        let expected_type = &match &arg.value_type {
            ValueType::TMulti(inner_type_name) => str_to_value_type(&inner_type_name.clone()),
            _ => arg.value_type.clone(),
        };
        let arg_expr = match e.get(i + 1) {
            Ok(expr) => expr,
            Err(err) => {
                errors.push(err);
                return errors;
            }
        };
        errors.extend(check_types(context, &arg_expr));

        let found_type = match crate::rs::init::get_value_type(&context, arg_expr) {
            Ok(val_type) => val_type,
            Err(error_string) => {
                errors.push(error_string);
                return errors;
            },
        };
        match expected_type {
            ValueType::TCustom(tn) if tn == "Dynamic" => {}, // Accept any type for Dynamic-typed argument
            ValueType::TCustom(tn) if tn == INFER_TYPE => {
                errors.push(e.error("type", &format!(
                    "calling func/proc '{}' declared arg {} without type, but type inference in args is not supported.\n\
                     Suggestion: the arg should be '{} : {},' instead of just '{}'.\n\
                     Alternative option: the arg could be '{} : Dynamic,' for dynamic arguments.
                     ",
                    f_name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, arg.name,
                )));
            },
            _ if expected_type != &found_type => {
                errors.push(e.error("type", &format!(
                    "calling function '{}' expects '{}' for arg '{}', but '{}' was provided.",
                    f_name, value_type_to_str(expected_type), arg.name, value_type_to_str(&found_type)
                )));
            },
            _ => {} // types match; no error
        }
    }

    return errors
}

fn check_func_proc_types(func_def: &SFuncDef, context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if !context.mode.allows_procs && func_def.is_proc() {
        errors.push(e.error("type", "Procs not allowed in pure modes"));
    }
    let mut has_variadic = false;
    for (i, arg) in func_def.args.iter().enumerate() {
        if has_variadic {
            errors.push(e.error("type", &format!("Variadic argument '{}' must be the last (only one variadic argument allowed).", &arg.name)));
        }

        match &arg.value_type {
            ValueType::TMulti(_multi_type) => {
                if arg.is_mut {
                    errors.push(e.error("type", &format!("Variadic argument '{}' cannot be 'mut'.", &arg.name)));
                }
                if i != func_def.args.len() - 1 {
                    errors.push(e.error("type", &format!("Variadic argument '{}' must be the last.", &arg.name)));
                }
                has_variadic = true;

                // All array types now use the generic Array
                let array_type_name = "Array".to_string();

                context.symbols.insert(arg.name.clone(), SymbolInfo {
                    value_type: ValueType::TCustom(array_type_name),
                    is_mut: false,
                });
            },
            ValueType::TCustom(ref custom_type_name) => {
                let custom_symbol = match context.symbols.get(custom_type_name) {
                    Some(custom_symbol_) => custom_symbol_.clone(),
                    None => {
                        errors.push(e.error("type", &format!("Argument '{}' is of undefined type '{}'.", &arg.name, &custom_type_name)));
                        return errors
                    },
                };
                // TODO check more type stuff

                context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});

                // For struct parameters, register field symbols for type checking
                // We use the lightweight registration instead of insert_struct to avoid evaluating
                // default values during type checking (which would cause errors for literals)
                if let ValueType::TType(TTypeDef::TStructDef) = custom_symbol.value_type {
                    context.register_struct_fields_for_typecheck(&arg.name, custom_type_name);
                }
            },
            _ => {
                context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
            },
        }
    }

    // TODO re-enable test when it is decided what to do with free, memcpy and memset
    // if func_def.function_type == FunctionType::FTFunc || func_def.function_type == FunctionType::FTFuncExt {
    //     if func_def.returns.len() == 0 && func_def.throws.len() == 0 {
    //         errors.push(e.error("type", "funcs must return or throw something, use a proc instead"));
    //     }
    // }

    // Don't check the bodies of external functions
    if func_def.is_ext() {
        return errors;
    }

    // TODO should macros be allowed to call procs?
    if !func_def.is_proc() {
        for se in &func_def.body {
            if is_expr_calling_procs(&context, &se) {
                errors.push(se.error("type", "funcs cannot call procs."));
            }
        }
    }
    for p in &func_def.body {
        errors.extend(check_types(context, &p));
    }

    let mut return_found = false;
    let mut thrown_types = Vec::new();
    errors.extend(check_body_returns_throws(context, e, func_def, &func_def.body, &mut thrown_types, &mut return_found));

    if !return_found && func_def.returns.len() > 0 {
        errors.push(e.error("type", "No return statments found in function that returns "));
    }

    // Filter and report only the thrown types that are not declared
    for (thrown_type, error_msg) in &thrown_types {
        if !func_def.throws.iter().any(|declared| &value_type_to_str(declared) == thrown_type) {
            errors.push(error_msg.to_string());
        }
    }

    for declared_throw in &func_def.throws {
        let declared_str = value_type_to_str(declared_throw);
        if !thrown_types.iter().any(|(t, _)| t == &declared_str) {
            errors.push(e.error("warning", &format!("It looks like `{}` is declared in the throws section, but this function never throws it.\nSuggestion: You can remove it to improve readability.",
                                                    declared_str)));
        }
    }

    return errors
}

pub fn check_body_returns_throws(context: &mut Context, e: &Expr, func_def: &SFuncDef, body: &[Expr], thrown_types: &mut Vec<(String, String)>, return_found: &mut bool) -> Vec<String> {

    let mut errors = vec![];
    let returns_len = func_def.returns.len();

    for p in body.iter() {
        match &p.node_type {
            NodeType::Body => {
                let mut temp_thrown_types = Vec::new();
                errors.extend(check_body_returns_throws(context, e, func_def, &p.params, &mut temp_thrown_types, return_found));
                thrown_types.extend(temp_thrown_types);
            },
            NodeType::Return => {
                *return_found = true;
                if returns_len != p.params.len() {
                    errors.push(p.error("type", &format!("Returning {} values when {} were expected.", p.params.len(), returns_len)));
                    errors.push(e.error("type", "Suggestion: Update returns section here"));
                } else {
                    for i in 0..p.params.len() {
                        let expected_value_type = match func_def.returns.get(i) {
                            Some(t) => t,
                            None => {
                                errors.push(e.lang_error("type", &format!("Fewer return values than provided at position {}", i)));
                                continue;
                            }
                        };
                        let return_val_e = match p.params.get(i) {
                            Some(val) => val,
                            None => {
                                errors.push(e.lang_error("type", &format!("Missing return value at position {}", i)));
                                continue;
                            }
                        };

                        // Recursively check this return expression for throws
                        errors.extend(
                            check_body_returns_throws(context, return_val_e, func_def, std::slice::from_ref(return_val_e), thrown_types, return_found));

                        match crate::rs::init::get_value_type(&context, return_val_e) {
                            Ok(actual_value_type) => {
                                if expected_value_type != &actual_value_type {
                                    errors.push(return_val_e.error(
                                        "type", &format!("Return value in pos {} expected to be '{}', but found '{}' instead",
                                                         i, value_type_to_str(&expected_value_type), value_type_to_str(&actual_value_type))));
                                    errors.push(e.error("type", "Suggestion: Update returns section here"));
                                }
                            },
                            Err(error_string) => {
                                errors.push(error_string);
                            },
                        };
                    }
                }
            },
            NodeType::Throw => {
                if p.params.len() != 1 {
                    errors.push(p.error("type", "Throw statement must have exactly one parameter."));
                } else {
                    let throw_param = &p.params[0];
                    // Recursively check this throw expression for throws (just in case, although users should avoid this)
                    // TODO fix this, not a priority
                    // errors.extend(
                    //     check_body_returns_throws(context, throw_param, func_def, std::slice::from_ref(throw_param), thrown_types, return_found));

                    match crate::rs::init::get_value_type(&context, throw_param) {
                        Ok(thrown_type) => {
                            if thrown_type == ValueType::TType(TTypeDef::TStructDef) {
                                errors.push(throw_param.error("type", "Cannot throw a struct definition.\nSuggestion: Create an instance by adding parentheses at the end."));
                            } else {
                                // Track the thrown type as a string and another string with its error
                                let thrown_type_str = value_type_to_str(&thrown_type);
                                thrown_types.push((thrown_type_str.clone(), throw_param.error("type", &format!("Function throws '{}', but it is not declared in this function's throws section.", thrown_type_str))));
                                thrown_types.push((thrown_type_str.clone(), e.error("type", "Suggestion: Either add it to the throws section here, or catch it with a catch block")));
                            }
                        },
                        Err(err) => {
                            errors.push(err);
                        }
                    }
                }
            },

            NodeType::Catch => {
                if p.params.len() != 3 {
                    errors.push(p.error("type", "Catch must have 3 parameters: variable, type, and body."));
                } else {
                    let err_type_expr = &p.params[1];
                    let catch_body_expr = &p.params[2];

                    let caught_type = match &err_type_expr.node_type {
                        NodeType::Identifier(name) => name.clone(),
                        _ => {
                            errors.push(err_type_expr.error("type", "Catch type must be a valid identifier"));
                            return errors;
                        }
                    };

                    // Remove first, before descending into body
                    if thrown_types.iter().any(|(t, _)| t == &caught_type) {
                        thrown_types.retain(|(t, _)| t != &caught_type);
                    } else {
                        errors.push(p.error("warning", &format!("Trying to catch '{}', but it is not among the thrown types", caught_type)));
                    }

                    // Then check body for other thrown exceptions
                    let mut temp_thrown_types = Vec::new();
                    errors.extend(check_body_returns_throws(context, e, func_def, &catch_body_expr.params, &mut temp_thrown_types, return_found));
                    thrown_types.extend(temp_thrown_types);
                }
            },

            NodeType::FCall => {
                match get_func_def_for_fcall(&context, p) {
                    Ok(Some(called_func_def)) => {
                        for called_throw in &called_func_def.throws {
                            let called_throw_str = value_type_to_str(called_throw);
                            let error_msg = format!(
                                "Function throws '{}', but it is not declared in this function's throws section.",
                                called_throw_str
                            );

                            thrown_types.push((called_throw_str.clone(), p.error("type", &error_msg)));
                            thrown_types.push((called_throw_str.clone(), e.error("type", "Suggestion: Either add it to the throws section here, or catch it with a catch block")));
                        }

                        for arg in p.params.iter().skip(1) {
                            if let NodeType::FCall = arg.node_type {
                                match get_func_def_for_fcall(&context, arg) {
                                    Ok(Some(nested_func_def)) => {
                                        let mut temp_thrown_types = Vec::new();
                                        errors.extend(check_body_returns_throws(context, arg, &nested_func_def, &arg.params, &mut temp_thrown_types, return_found));
                                        thrown_types.extend(temp_thrown_types);
                                    },
                                    Ok(None) => {
                                        errors.push(arg.error("type", "Could not resolve function definition for nested call."));
                                    },
                                    Err(reason) => {
                                        errors.push(arg.error("type", &format!("Failed to resolve nested function call: {}", reason)));
                                    }
                                }
                            }
                        }
                    },
                    Ok(None) => {
                        errors.push(p.error("type", "Could not resolve function definition for call."));
                    },
                    Err(reason) => {
                        errors.push(p.error("type", &reason));
                    }
                }
            }

            NodeType::While => {
                let mut temp_thrown_types = Vec::new();
                if let Some(cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(cond_expr), &mut temp_thrown_types, return_found));
                }
                if let Some(body_expr) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                }
                thrown_types.extend(temp_thrown_types);
            }
            NodeType::If => {
                let mut temp_thrown_types = Vec::new();
                if let Some(cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(cond_expr), &mut temp_thrown_types, return_found));
                }
                if let Some(then_block) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &then_block.params, &mut temp_thrown_types, return_found));
                }
                if let Some(else_block) = p.params.get(2) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &else_block.params, &mut temp_thrown_types, return_found));
                }
                thrown_types.extend(temp_thrown_types);
            }
            NodeType::Switch => {
                let mut temp_thrown_types = Vec::new();
                // Analyze the switch expression itself (could throw)
                if let Some(switch_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(switch_expr), &mut temp_thrown_types, return_found));
                }

                let mut i = 1;
                while i + 1 < p.params.len() {
                    let case_expr = &p.params[i];
                    let body_expr = &p.params[i + 1];

                    // Check case expression and the body block
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(case_expr), &mut temp_thrown_types, return_found));
                    errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));

                    i += 2;
                }
                thrown_types.extend(temp_thrown_types);
            }

            NodeType::Declaration(_) | NodeType::Assignment(_) => {
                if let Some(initializer) = p.params.get(0) {
                    if let NodeType::FCall = initializer.node_type {

                        let id_expr = match initializer.get(0) {
                            Ok(id_expr_) => id_expr_,
                            Err(err) => {
                                errors.push(err);
                                continue;
                            },
                        };
                        if let NodeType::Identifier(name) = &id_expr.node_type {
                            // Only skip default constructor calls (simple StructName() with no dots)
                            // Don't skip method calls like Struct.method()
                            if id_expr.params.is_empty() {
                                if let Some(symbol) = context.symbols.get(name) {
                                    if symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                                        continue; // Skip default constructor calls, for instantiations like 'StructName()'
                                    }
                                }
                            }

                            // Check for enum constructors (e.g., Color.Green(true))
                            if id_expr.params.len() == 1 {
                                if let Some(symbol) = context.symbols.get(name) {
                                    if symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                        if let Some(variant_expr) = id_expr.params.get(0) {
                                            if let NodeType::Identifier(_variant_name) = &variant_expr.node_type {
                                                continue; // Skip enum constructor calls, for instantiations like 'Color.Green(true)'
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        match get_func_def_for_fcall(&context, initializer) {
                            Ok(Some(called_func_def)) => {
                                for called_throw in &called_func_def.throws {
                                    let called_throw_str = value_type_to_str(called_throw);
                                    let error_msg = format!(
                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                        called_throw_str
                                    );

                                    thrown_types.push((called_throw_str.clone(), initializer.error("type", &error_msg)));
                                    thrown_types.push((called_throw_str.clone(), e.error("type", "Suggestion: Either add it to the throws section here, or catch it with a catch block")));
                                }

                                let mut temp_thrown_types = Vec::new();
                                errors.extend(check_body_returns_throws(context, initializer, &called_func_def, &initializer.params, &mut temp_thrown_types, return_found));
                                thrown_types.extend(temp_thrown_types);
                            },
                            Ok(None) => {
                                errors.push(initializer.error("type", "Could not resolve function definition in declaration initializer."));
                            },
                            Err(reason) => {
                                errors.push(initializer.error("type", &format!("Failed to resolve function in declaration initializer: {}", reason)));
                            }
                        }
                    }
                }
            }


            _ => {},
        }
    }

    return errors
}

fn check_catch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors = Vec::new();

    if e.params.len() != 3 {
        errors.push(e.error("type", "Catch node must have three parameters: variable, type, and body."));
        return errors
    }

    let err_var_expr = &e.params[0];
    let err_type_expr = &e.params[1];
    let body_expr = &e.params[2];

    let var_name = match &err_var_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_var_expr.error("type", "First catch param must be an identifier"));
            return errors
        }
    };

    let type_name = match &err_type_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_type_expr.error("type", "Second catch param must be a type identifier"));
            return errors
        }
    };

    // Confirm that the type exists in the context (as done for function args)
    if context.symbols.get(&type_name).is_none() {
        errors.push(e.error("type", &format!("Catch refers to undefined type '{}'", &type_name)));
        return errors
    }

    // Create scoped context for catch body
    let mut temp_context = context.clone();
    temp_context.symbols.insert(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name.clone()),
        is_mut: false,
    });

    // Map struct fields so err.msg etc. can be accessed during type-checking
    if let Some(struct_def) = context.struct_defs.get(&type_name) {
        for (field_name, field_decl) in &struct_def.members {
            let combined_name = format!("{}.{}", var_name, field_name);
            temp_context.symbols.insert(
                combined_name.clone(),
                SymbolInfo {
                    value_type: field_decl.value_type.clone(),
                    is_mut: false,  // Error variables are not mutable in catch blocks
                },
            );
        }
    }

    errors.extend(check_types(&mut temp_context, body_expr));

    return errors
}

fn check_declaration(context: &mut Context, e: &Expr, decl: &Declaration) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in declaration of {}, declaration nodes must take exactly 1 parameter.",
                                                  decl.name)));
        return errors
    }


    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    if !context.symbols.contains_key(&decl.name) {
        let mut value_type = decl.value_type.clone();
        if value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
            value_type = match crate::rs::init::get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
        }
        // TODO move to init_context() ? inner contexts are not persisted in init_context
        context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
        match value_type {
            ValueType::TCustom(custom_type) => {
                if custom_type == INFER_TYPE {
                    errors.push(e.lang_error("type", &format!("Cannot infer the declaration type of {}", decl.name)));
                    return errors;
                }
                // During type checking, register struct fields so they can be accessed in the code
                // Memory allocation and default value evaluation happens during runtime in eval_declaration
                if context.struct_defs.contains_key(&custom_type) {
                    context.register_struct_fields_for_typecheck(&decl.name, &custom_type);
                }
            }
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                match &inner_e.node_type {
                    NodeType::FuncDef(func_def) => {
                        // TODO move to init_context() ? inner contexts are not persisted in init_context
                        context.funcs.insert(decl.name.clone(), func_def.clone());
                    },
                    _ => {
                        errors.push(e.lang_error("type", "functions should have definitions"));
                        return errors;
                    },
                }
            },
            _ => {},
        }
    }
    errors.extend(check_types(context, &inner_e));

    return errors
}

fn check_assignment(context: &mut Context, e: &Expr, var_name: &str) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in assignment to {}, assignments must take exactly one value, not {}.",
                                                  var_name, e.params.len())));
        return errors
    }

    if context.funcs.contains_key(var_name)  {
        errors.push(e.error("type", &format!("function '{}' cannot be assigned to.", var_name)));
    } else if context.symbols.contains_key(var_name) {
        let symbol_info = match context.symbols.get(var_name) {
            Some(info) => info,
            None => {
                errors.push(e.error("type", &format!("Undeclared variable '{}'", var_name)));
                return errors;
            }
        };
        if !symbol_info.is_mut {
            errors.push(e.error("type", &format!("Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", var_name)));
        }
    } else {
        errors.push(e.error("type", &format!("Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                                             var_name, var_name, var_name)));
    }

    match e.get(0) {
        Ok(inner_e) => errors.extend(check_types(context, inner_e)),
        Err(err) => errors.push(err),
    }
    return errors;
}

fn check_switch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    let switch_expr_type = match e.get(0) {
        Ok(expr) => match crate::rs::init::get_value_type(context, expr) {
            Ok(t) => t,
            Err(err) => {
                errors.push(err);
                return errors;
            }
        },
        Err(err) => {
            errors.push(err);
            return errors;
        }
    };

    let mut case_found = false;
    let mut default_found = false;

    let mut i = 1;
    while i < e.params.len() {
        let case_expr = &e.params[i];

        match &case_expr.node_type {
            NodeType::DefaultCase => {
                if default_found {
                    errors.push(case_expr.error("type", "Duplicate default case in switch"));
                }
                default_found = true;
                case_found = true;
            }
            NodeType::Pattern(_variant_name, _binding_var) => {
                // Pattern matching - type is checked in exhaustiveness check below
                case_found = true;
                // No need to check type here - patterns implicitly match the switch type
            }
            _ => {
                case_found = true;

                match crate::rs::init::get_value_type(context, case_expr) {
                    Ok(case_type) => {
                        let switch_type_str = value_type_to_str(&switch_expr_type);
                        let case_type_str = value_type_to_str(&case_type);
                        if case_type_str != switch_type_str && case_type_str != format!("{}Range", switch_type_str) {
                            errors.push(case_expr.error("type", &format!(
                                "Switch value type '{}', case value type '{}' do not match",
                                switch_type_str, case_type_str
                            )));
                        }
                    }
                    Err(err) => {
                        errors.push(err);
                    }
                }
            }
        }

        i += 1;

        if i >= e.params.len() {
            errors.push(e.error("type", "Switch case missing body expression"));
            return errors
        }

        let body_expr = &e.params[i];

        // For pattern matching, add the binding variable to the context before type checking the body
        if let NodeType::Pattern(variant_name, binding_var) = &case_expr.node_type {
            // Get the payload type for this variant
            if let ValueType::TCustom(enum_name) = &switch_expr_type {
                if let Some(enum_def) = context.enum_defs.get(enum_name) {
                    // Extract just the variant name (remove enum prefix if present)
                    let variant = if let Some(dot_pos) = variant_name.rfind('.') {
                        &variant_name[dot_pos + 1..]
                    } else {
                        variant_name.as_str()
                    };

                    if let Some(payload_type_opt) = enum_def.enum_map.get(variant) {
                        if let Some(payload_type) = payload_type_opt {
                            // Create a temporary context with the binding variable
                            let mut temp_context = context.clone();
                            temp_context.symbols.insert(
                                binding_var.clone(),
                                crate::rs::init::SymbolInfo {
                                    value_type: payload_type.clone(),
                                    is_mut: false,
                                }
                            );
                            errors.extend(check_types(&mut temp_context, body_expr));
                        } else {
                            // Variant exists but has no payload
                            errors.push(case_expr.error("type", &format!("Variant '{}' has no payload, cannot use pattern matching", variant)));
                            errors.extend(check_types(context, body_expr));
                        }
                    } else {
                        errors.push(case_expr.error("type", &format!("Unknown variant '{}'", variant)));
                        errors.extend(check_types(context, body_expr));
                    }
                } else {
                    errors.extend(check_types(context, body_expr));
                }
            } else {
                errors.extend(check_types(context, body_expr));
            }
        } else {
            errors.extend(check_types(context, body_expr));
        }

        i += 1;
    }

    if !case_found {
        errors.push(e.error("type", "Switch must have at least one case"));
    }

    // Exhaustiveness check only for enums
    if let ValueType::TCustom(enum_name) = switch_expr_type {
        if let Some(enum_def) = context.enum_defs.get(&enum_name) {
            let mut matched_variants: Vec<String> = Vec::new();

            let mut j = 1;
            while j < e.params.len() {
                let case_expr = &e.params[j];
                match &case_expr.node_type {
                    NodeType::Pattern(variant_name, _binding_var) => {
                        // Pattern matching: case EnumType.Variant(binding)
                        // Extract the variant name from the full "EnumType.Variant" string
                        if let Some(dot_pos) = variant_name.rfind('.') {
                            let enum_part = &variant_name[..dot_pos];
                            let variant_part = &variant_name[dot_pos + 1..];
                            if enum_part != enum_name {
                                errors.push(case_expr.error("type", &format!("Mismatched enum type '{}', expected '{}'.", enum_part, enum_name)));
                            }
                            matched_variants.push(variant_part.to_string());
                        } else {
                            // Just the variant name without enum prefix
                            matched_variants.push(variant_name.clone());
                        }
                    }
                    NodeType::Identifier(name) => {
                        if case_expr.params.is_empty() {
                            // case A
                            matched_variants.push(name.clone());
                        } else {
                            // case ExampleEnum.A
                            let variant_expr = &case_expr.params[0];
                            if let NodeType::Identifier(variant) = &variant_expr.node_type {
                                if name != &enum_name {
                                    errors.push(case_expr.error("type", &format!("Mismatched enum type '{}', expected '{}'.", name, enum_name)));
                                }
                                matched_variants.push(variant.clone());
                            } else {
                                errors.push(case_expr.error("type", "Invalid enum case syntax"));
                            }
                        }
                    }
                    NodeType::DefaultCase => {
                        default_found = true;
                    }
                    _ => {}
                }
                j += 2;
            }

            if !default_found {
                for variant in enum_def.enum_map.keys() {
                    if !matched_variants.contains(variant) {
                        errors.push(e.error("type", &format!("Switch is missing case for variant '{}'", variant)));
                    }
                }
            }
        }
    }

    return errors
}

fn check_struct_def(context: &mut Context, e: &Expr, struct_def: &SStructDef) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_struct_def(): struct declarations must take exactly 0 params."));
        return errors
    }

    for (member_name, _member_decl) in &struct_def.members {
        // TODO check types for members inside structs too
        match struct_def.default_values.get(member_name) {
            Some(inner_e) => {
                // println!("inner_e {:?}", inner_e);
                match &inner_e.node_type {
                    // If the member's default value is a function (method), type check it
                    NodeType::FuncDef(func_def) => {
                        let mut function_context = context.clone();
                        errors.extend(check_func_proc_types(&func_def, &mut function_context, &inner_e));
                    },
                    // For other types of members, treat them like regular declarations
                    _ => {
                        // println!("DEBUG: Check members that are NOT function definitions, got inner_e: {:?}", inner_e);
                        // errors.extend(check_declaration(&mut context, &inner_e, &member_decl));
                    }
                }
            },
            None => {
                errors.push(e.todo_error("type", &format!("Member '{}' lacks a default value. Not allowed yet.", member_name)));
            }
        }
    }

    return errors
}

pub fn get_func_def_for_fcall_with_expr(context: &Context, fcall_expr: &mut Expr) -> Result<Option<SFuncDef>, String> {
    if fcall_expr.node_type != NodeType::FCall {
        return Err(fcall_expr.lang_error("type", "Expected FCall node type"));
    }
    let func_expr = match fcall_expr.params.first() {
        Some(expr) => expr,
        None => return Err(fcall_expr.lang_error("type", "get_func_def_for_fcall_with_expr: Fcalls must have a name")),
    };

    match &func_expr.node_type {
        NodeType::Identifier(_) => {
            // Regular functions and associated functions used directly
            let combined_name = crate::rs::parser::get_combined_name(func_expr)?;

            // NEW: Check if this is a UFCS call on a function/expression result
            // If params has 2+ elements and params[1] is an expression (FCall, etc.)
            if fcall_expr.params.len() >= 2 {
                let first_arg = fcall_expr.get(1)?;
                // Try to get the type of the first argument
                if let Ok(target_type) = crate::rs::init::get_value_type(context, first_arg) {
                    if let ValueType::TCustom(custom_type_name) = target_type {
                        // Check if this type has an associated method
                        let method_name = format!("{}.{}", custom_type_name, combined_name);
                        if let Some(func_def) = context.funcs.get(&method_name) {
                            // Transform: method(target, args...) with proper identifier
                            let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), fcall_expr.get(0)?, Vec::new());
                            let mut new_args = Vec::new();
                            new_args.push(new_e);
                            new_args.extend(fcall_expr.params[1..].to_vec());

                            *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                            return Ok(Some(func_def.clone()));
                        }
                    }
                }
            }

            // Original logic: check for regular function
            if let Some(func_def) = context.funcs.get(&combined_name) {
                return Ok(Some(func_def.clone()))
            }

            if let Some(_struct_def) = context.struct_defs.get(&combined_name) {
                return Ok(None) // REM: This is to allow struct instantiation
            }

            // Check for enum constructors (e.g., Color.Green(true))
            let parts: Vec<&str> = combined_name.split('.').collect();
            if parts.len() == 2 {
                let enum_type = parts[0];
                if let Some(enum_def) = context.enum_defs.get(enum_type) {
                    let variant_name = parts[1];
                    if enum_def.enum_map.contains_key(variant_name) {
                        // This is a valid enum constructor
                        return Ok(None) // Allow enum construction
                    }
                }
            }

            // Using UFCS
            if let Some(func_name_expr) = func_expr.params.last() {
                if let NodeType::Identifier(ufcs_func_name) = &func_name_expr.node_type {
                    let mut parts: Vec<&str> = combined_name.split('.').collect();
                    parts.pop(); // Remove the last element (the function name)
                    let new_combined_name = parts.join(".");

                    // Create identifier expression preserving nested structure
                    // Copy func_expr but remove the last param (the method name)
                    let mut id_params = func_expr.params.clone();
                    id_params.pop(); // Remove the method name
                    let extra_arg_e = Expr::new_clone(func_expr.node_type.clone(), fcall_expr, id_params);

                    // Regular functions used with UFCS
                    if let Some(func_def) = context.funcs.get(&ufcs_func_name.to_string()) {

                        let new_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), fcall_expr.get(0)?, Vec::new());
                        let mut new_args = Vec::new();
                        new_args.push(new_e);
                        new_args.push(extra_arg_e);
                        new_args.extend(fcall_expr.params[1..].to_vec());

                        *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                        return Ok(Some(func_def.clone()))
                    }

                    // Associated functions used with UFCS (aka methods)
                    if let Some(symbol_info) = context.symbols.get(&new_combined_name) {

                        match &symbol_info.value_type {
                            ValueType::TCustom(ref custom_type_name) => {
                                let id_expr_name = format!("{}.{}", custom_type_name, ufcs_func_name);
                                if let Some(func_def) = context.funcs.get(&id_expr_name) {

                                    let new_e = Expr::new_clone(NodeType::Identifier(id_expr_name.clone()), fcall_expr.get(0)?, Vec::new());
                                    let mut new_args = Vec::new();
                                    new_args.push(new_e);
                                    new_args.push(extra_arg_e);
                                    new_args.extend(fcall_expr.params[1..].to_vec());

                                    *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                                    return Ok(Some(func_def.clone()))
                                }
                            },
                            found_value_type => return Err(func_expr.error("type", &format!(
                                "'{}' is of type '{}' and thus can't have a '{}' associated function",
                                new_combined_name, value_type_to_str(&found_value_type), ufcs_func_name)))
                        }
                    }
                }
            }
            return Err(func_expr.lang_error("type", "Could not find function defintion"))
        },
        _ => return Err(func_expr.lang_error("type", "Expected Identifier node type"))
    }
}

fn get_func_def_for_fcall(context: &Context, fcall_expr_: &Expr) -> Result<Option<SFuncDef>, String> {
    let mut fcall_expr = fcall_expr_.clone();
    return get_func_def_for_fcall_with_expr(&context, &mut fcall_expr);
}






// ---------- Type checking

fn is_expr_calling_procs(context: &Context, e: &Expr) -> bool {
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se) {
                    return true
                }
            }
            return false
        },
        NodeType::StructDef(_) => {
            // TODO default values could try to call procs
            return false
        },
        NodeType::EnumDef(_) => {
            return false
        },
        NodeType::LLiteral(_) => return false,
        NodeType::DefaultCase => return false,
        NodeType::Pattern(_, _) => return false,
        NodeType::Identifier(_) => return false,
        NodeType::Range => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se) {
                    return true
                }
            }
            return false
        },
        NodeType::FCall => {
            // TODO the arguments of a function call can also call procedures
            let f_name = crate::rs::init::get_func_name_in_call(e);
            // TODO Temp: In the future, implement a special PanicError that's potentially  thrown implicitly everywhere
            if f_name == "panic" {
                return false
            }
            match context.funcs.get(&f_name) {
                // TODO check the args too
                Some(func) => return func.is_proc(),
                None => return false,
            }
        },
        NodeType::Declaration(decl) => {
            match e.params.get(0) {
                Some(inner_e) => is_expr_calling_procs(context, inner_e),
                None => {
                    e.exit_error("type", &format!("while declaring '{}', parameter is unexpectedly missing.", decl.name));
                    true
                }
            }
        },
        NodeType::Assignment(var_name) => {
            match e.params.get(0) {
                Some(inner_e) => is_expr_calling_procs(context, inner_e),
                None => {
                    e.exit_error("type", &format!("while assigning {}, parameter is unexpectedly missing.", var_name));
                    true
                }
            }
        }
        NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(context, it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return | NodeType::Throw => {
            for it_e in &e.params {
                if is_expr_calling_procs(context, it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::Catch => {
            // The catch body is always the third parameter
            if let Some(body_expr) = e.params.get(2) {
                is_expr_calling_procs(context, body_expr)
            } else {
                // TODO Err(lang_error) here instead
                true
            }
        }
    }
}

pub fn func_proc_has_multi_arg(func_def: &SFuncDef) -> bool {
    for a in &func_def.args {
        match a.value_type {
            ValueType::TMulti(_) => {
                return true;
            }
            _ => {}
        }
    }
    return false
}

pub fn basic_mode_checks(context: &Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                match &p.node_type {

                    NodeType::Declaration(decl) => {
                        if !context.mode.allows_base_mut && decl.is_mut {
                            errors.push(e.error("mode", &format!("mode {} doesn't allow mut declarations of 'mut {}'.\nSuggestion: remove 'mut' or change to mode script or cli",
                                                                 context.mode.name, decl.name)));
                        }
                    },
                    NodeType::FCall => {
                        if !context.mode.allows_base_calls {
                            let f_name = crate::rs::init::get_func_name_in_call(&p);
                            if f_name != "import" {
                                errors.push(e.error("mode", &format!("mode {} doesn't allow calls in the root context of the file'.\nSuggestion: remove the call to '{}' or change mode 'test' or 'script'",
                                                                     context.mode.name, f_name)));
                            }
                        }
                    },
                    _ => {},
                }
            }
        },
        _ => {
            errors.push(e.lang_error("mode", "basic_mode_checks() expects a body expression, this should never happen."))
        },
    }

    if context.mode.needs_main_proc {
        match context.symbols.get("main") {
            Some(symbol_info) => {
                if symbol_info.value_type != ValueType::TFunction(FunctionType::FTProc) {
                    errors.push(e.error("mode", &format!("mode {} requires 'main' to be defined as a proc. It was defined as a {} instead",
                                                         context.mode.name, value_type_to_str(&symbol_info.value_type))));
                }
            },
            None => {
                errors.push(e.error("mode", &format!("mode {} requires 'main' to be defined as a proc.", context.mode.name)));
            },
        };
    }
    return errors;
}

