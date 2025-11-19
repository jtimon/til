use crate::Context;
use crate::rs::init::{SymbolInfo, get_value_type, get_func_name_in_call};
use crate::rs::parser::{
    INFER_TYPE, Literal,
    Expr, NodeType, ValueType, SEnumDef, SStructDef, SFuncDef, Declaration, PatternInfo, FunctionType, TTypeDef,
    value_type_to_str, str_to_value_type,
};

// Type checking phase: Validates types, return/throw statements, mode constraints
// This module handles the type checking phase that runs after init.
// No eval, no arena access - pure type analysis.

// Context tracking for return value usage enforcement (Bug #8 fix)
#[derive(Clone, Copy, PartialEq)]
enum ExprContext {
    // Return value is being used (assigned, passed as arg, returned, etc)
    ValueUsed,
    // Return value is discarded (statement in Body)
    ValueDiscarded,
}

fn check_enum_def(context: &Context, e: &Expr, enum_def: &SEnumDef) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_enum_def(): enum declarations don't have any parameters in the tree."));
        return errors
    }

    for (enum_val_name, enum_opt) in &enum_def.enum_map {
        match &enum_opt {
            None => {},
            Some(value_type) => {
                match value_type {
                    ValueType::TCustom(ref custom_type_name) => {
                        // Validate that the custom type exists
                        if context.scope_stack.lookup_symbol(custom_type_name).is_none() {
                            errors.push(e.error(&context.path, "type", &format!(
                                "Enum variant '{}' uses undefined type '{}'.\nHint: Make sure '{}' is defined before this enum.",
                                enum_val_name, custom_type_name, custom_type_name
                            )));
                        } else {
                            // Validate it's actually a type (enum or struct), not a value
                            let symbol_info = context.scope_stack.lookup_symbol(custom_type_name).unwrap();
                            match &symbol_info.value_type {
                                ValueType::TType(TTypeDef::TEnumDef) |
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    // Valid type
                                },
                                _ => {
                                    errors.push(e.error(&context.path, "type", &format!(
                                        "Enum variant '{}' payload type '{}' is not a valid type (expected enum or struct, found {}).",
                                        enum_val_name, custom_type_name, value_type_to_str(&symbol_info.value_type)
                                    )));
                                }
                            }
                        }
                    },
                    _ => {
                        errors.push(e.todo_error(&context.path, "type", &format!("'enum' does not support payloads of value type '{}' yet",
                                                                  value_type_to_str(&value_type))));
                    },
                }
            },
        }
    }
    return errors;
}

// Public entry point: assumes Body-level context (return values discarded at statement level)
pub fn check_types(context: &mut Context, e: &Expr) -> Vec<String> {
    return check_types_with_context(context, e, ExprContext::ValueDiscarded);
}

// Internal type checker with context tracking for return value usage
fn check_types_with_context(context: &mut Context, e: &Expr, expr_context: ExprContext) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            // Statements in Body discard return values
            for p in e.params.iter() {
                errors.extend(check_types_with_context(context, &p, ExprContext::ValueDiscarded));
            }
        },
        NodeType::EnumDef(enum_def) => {
            errors.extend(check_enum_def(context, &e, enum_def));
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
                errors.push(e.lang_error(&context.path, "type", "Range expression must have exactly two elements"));
                return errors;
            }

            // Range operands are used
            errors.extend(check_types_with_context(context, &e.params[0], ExprContext::ValueUsed));
            errors.extend(check_types_with_context(context, &e.params[1], ExprContext::ValueUsed));

            let left_type = get_value_type(context, &e.params[0]);
            if let Err(err) = &left_type {
                errors.push(err.clone());
            }
            let right_type = get_value_type(context, &e.params[1]);
            if let Err(err) = &right_type {
                errors.push(err.clone());
            }

            if let (Ok(t1), Ok(t2)) = (left_type, right_type) {
                if t1 != t2 {
                    errors.push(e.error(&context.path, "type", &format!("Range start and end must be of same type, found '{}' and '{}'",
                                                         value_type_to_str(&t1), value_type_to_str(&t2))));
                }
            }
        },
        NodeType::FCall => {
            errors.extend(check_fcall(context, &e));
            // Check if return value usage is correct for this context
            errors.extend(check_fcall_return_usage(context, &e, expr_context));
        },
        NodeType::FuncDef(func_def) => {
            let mut function_context = context.clone();
            errors.extend(check_func_proc_types(&func_def, &mut function_context, &e));
        },
        NodeType::Identifier(name) => {
            if !(context.scope_stack.lookup_func(name).is_some() || context.scope_stack.lookup_symbol(name).is_some()) {
                errors.push(e.error(&context.path, "type", &format!("Undefined symbol {}", name)));
            }
        },
        NodeType::Declaration(decl) => {
            errors.extend(check_declaration(context, &e, decl));
        },
        NodeType::Assignment(var_name) => {
            errors.extend(check_assignment(context, &e, var_name));
        },
        NodeType::Return | NodeType::Throw => {
            // Return/throw values are used
            for return_val in &e.params {
                errors.extend(check_types_with_context(context, &return_val, ExprContext::ValueUsed));
            }
        },
        NodeType::Catch => {
            errors.extend(check_catch_statement(context, &e));
        }

        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => {},
    }

    return errors
}

// Helper function to validate conditional statement parameters
fn validate_conditional_params(_path: &str, e: &Expr, stmt_type: &str, min: usize, max: usize) -> Option<String> {
    if e.params.len() < min || e.params.len() > max {
        if min == max {
            return Some(e.exit_error("type", &format!("{} nodes must have exactly {} parameters.", stmt_type, min)));
        } else {
            return Some(e.exit_error("type", &format!("{} nodes must have {} or {} parameters.", stmt_type, min, max)));
        }
    }
    None
}

// Helper function to validate function/procedure argument counts
fn validate_func_arg_count(path: &str, e: &Expr, f_name: &str, func_def: &SFuncDef) -> Option<String> {
    let provided_args = e.params.len() - 1;

    // Check zero-arg functions
    if func_def.args.len() == 0 && provided_args > 0 {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects 0 args, but {} were provided.", f_name, provided_args)));
    }

    let has_multi_arg = func_proc_has_multi_arg(&func_def);

    // Check exact count for non-variadic functions
    if !has_multi_arg && func_def.args.len() != provided_args {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects {} args, but {} were provided.",
                                             f_name, func_def.args.len(), provided_args)));
    }

    // Check minimum count for variadic functions
    if has_multi_arg && func_def.args.len() - 1 > provided_args {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
                                             f_name, func_def.args.len() - 1, provided_args)));
    }

    None
}

fn check_if_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if let Some(err) = validate_conditional_params(&context.path, e, "if", 2, 3) {
        errors.push(err);
        return errors;
    }

    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    // Type check the condition expression exists, but don't enforce it must be Bool
    // NOTE: Bool type checking removed - Bool is a regular struct, not a special primitive
    match get_value_type(&context, &inner_e) {
        Ok(_val_type) => {},
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };
    // First param (condition) is used, remaining params (then/else bodies) discard values
    for (i, p) in e.params.iter().enumerate() {
        let ctx = if i == 0 { ExprContext::ValueUsed } else { ExprContext::ValueDiscarded };
        errors.extend(check_types_with_context(context, &p, ctx));
    }
    return errors;
}

fn check_while_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if let Some(err) = validate_conditional_params(&context.path, e, "while", 2, 2) {
        errors.push(err);
        return errors;
    }

    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    // Type check the condition expression exists, but don't enforce it must be Bool
    // NOTE: Bool type checking removed - Bool is a regular struct, not a special primitive
    match get_value_type(&context, &inner_e) {
        Ok(_val_type) => {},
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };
    // First param (condition) is used, second param (body) discards values
    for (i, p) in e.params.iter().enumerate() {
        let ctx = if i == 0 { ExprContext::ValueUsed } else { ExprContext::ValueDiscarded };
        errors.extend(check_types_with_context(context, &p, ctx));
    }
    return errors;
}
fn check_fcall(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();
    let f_name = get_func_name_in_call(e);
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

    if let Some(err) = validate_func_arg_count(&context.path, &e, &f_name, &func_def) {
        errors.push(err);
        return errors;
    }

    let max_arg_def = func_def.args.len();
    for i in 0..e.params.len() - 1 {
        let arg = match func_def.args.get(std::cmp::min(i, max_arg_def - 1)) {
            Some(arg) => arg,
            None => {
                errors.push(e.lang_error(&context.path, "type", &format!("argument index {} out of bounds for function '{}'", i, f_name)));
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
        // Function call arguments are being used (passed to the function)
        errors.extend(check_types_with_context(context, &arg_expr, ExprContext::ValueUsed));

        // Check mut parameter requirements
        if arg.is_mut {
            // The parameter expects mut, so the argument must be a mutable variable
            match &arg_expr.node_type {
                NodeType::Identifier(var_name) => {
                    // Simple variable - check if it's mut
                    if let Some(symbol_info) = context.scope_stack.lookup_symbol(var_name) {
                        if !symbol_info.is_mut {
                            errors.push(arg_expr.error(&context.path, "type", &format!(
                                "Cannot pass const variable '{}' to mut parameter '{}' of function '{}'.\n\
                                 Suggestion: declare '{}' as 'mut {}'.",
                                var_name, arg.name, f_name, var_name, var_name
                            )));
                        }
                    }
                },
                _ => {
                    // For other expressions (literals, function calls, field access, etc.)
                    // Try to determine if it's a valid mut target
                    // For now, we allow non-identifier expressions (this could be tightened later)
                    // TODO: add stricter checking for field access and other complex expressions
                }
            }
        }

        // Check copy parameter requirements - structs must have clone() implementation
        // Only check for explicit 'copy' parameters, not regular immutable parameters
        if arg.is_copy {
            // Get the actual type being passed
            let arg_type = match get_value_type(&context, arg_expr) {
                Ok(val_type) => val_type,
                Err(_) => {
                    // Type error already reported, skip clone check
                    continue;
                }
            };

            // Only check for custom types (user-defined structs)
            if let ValueType::TCustom(type_name) = &arg_type {
                // Skip primitive types that are trivially copyable (don't require clone())
                // These types are copy-by-value and don't need deep cloning
                // NOTE: Bool removed from this list - it's a regular struct, not a special primitive
                let primitives = vec!["I64", "U8", "Str"];
                if primitives.contains(&type_name.as_str()) {
                    continue;
                }

                if let Some(struct_def) = context.scope_stack.lookup_struct(type_name) {
                    // Check if clone() exists as a const (associated function)
                    let has_clone = struct_def.get_member("clone")
                        .map(|decl| !decl.is_mut)
                        .unwrap_or(false);

                    if !has_clone {
                        errors.push(arg_expr.error(&context.path, "type", &format!(
                            "Cannot pass struct '{}' to copy parameter '{}' of function '{}'.\n\
                             Reason: struct '{}' does not implement clone() method.\n\
                             Suggestion: add 'clone := func(self: {}) returns {} {{ ... }}' to struct '{}'.",
                            type_name, arg.name, f_name, type_name, type_name, type_name, type_name
                        )));
                    }
                }
            }
        }

        let found_type = match get_value_type(&context, arg_expr) {
            Ok(val_type) => val_type,
            Err(error_string) => {
                errors.push(error_string);
                return errors;
            },
        };
        match expected_type {
            ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => {}, // Accept any type for Dynamic/Type-typed argument
            ValueType::TCustom(tn) if tn == INFER_TYPE => {
                errors.push(e.error(&context.path, "type", &format!(
                    "calling func/proc '{}' declared arg {} without type, but type inference in args is not supported.\n\
                     Suggestion: the arg should be '{} : {},' instead of just '{}'.\n\
                     Alternative option: the arg could be '{} : Dynamic,' for dynamic arguments.
                     ",
                    f_name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, arg.name,
                )));
            },
            _ if expected_type != &found_type => {
                errors.push(e.error(&context.path, "type", &format!(
                    "calling function '{}' expects '{}' for arg '{}', but '{}' was provided.",
                    f_name, value_type_to_str(expected_type), arg.name, value_type_to_str(&found_type)
                )));
            },
            _ => {} // types match; no error
        }
    }

    return errors
}

// Check if a function call's return value is being used correctly (Bug #8 fix)
fn check_fcall_return_usage(context: &Context, e: &Expr, expr_context: ExprContext) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    // Get the function definition to check if it returns a value
    let func_def = match get_func_def_for_fcall(&context, e) {
        Ok(Some(func_def_)) => func_def_,
        Ok(None) => return errors, // Struct/enum constructor, no return value check needed
        Err(_) => return errors, // Error already reported by check_fcall
    };

    // Check if this function returns a value
    let returns_value = func_def.return_types.len() > 0;

    if returns_value && expr_context == ExprContext::ValueDiscarded {
        let f_name = get_func_name_in_call(e);

        errors.push(e.error(&context.path, "type", &format!(
            "Function '{}' returns a value that is not being used.\n\
             Hint: Capture the return value with '_ := {}(...)' or use it in an expression.",
            f_name, f_name
        )));
    }

    return errors;
}

fn check_func_proc_types(func_def: &SFuncDef, context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if !context.mode.allows_procs && func_def.is_proc() {
        errors.push(e.error(&context.path, "type", "Procs not allowed in pure modes"));
    }
    let mut has_variadic = false;
    for (i, arg) in func_def.args.iter().enumerate() {
        if has_variadic {
            errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' must be the last (only one variadic argument allowed).", &arg.name)));
        }

        match &arg.value_type {
            ValueType::TMulti(_multi_type) => {
                if arg.is_mut {
                    errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' cannot be 'mut'.", &arg.name)));
                }
                if i != func_def.args.len() - 1 {
                    errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' must be the last.", &arg.name)));
                }
                has_variadic = true;

                // All array types now use the generic Array
                let array_type_name = "Array".to_string();

                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
                    value_type: ValueType::TCustom(array_type_name),
                    is_mut: false,
                    is_copy: false,
                    is_own: false,
                });
            },
            ValueType::TCustom(ref custom_type_name) => {
                let custom_symbol = match context.scope_stack.lookup_symbol(custom_type_name) {
                    Some(custom_symbol_) => custom_symbol_.clone(),
                    None => {
                        errors.push(e.error(&context.path, "type", &format!("Argument '{}' is of undefined type '{}'.", &arg.name, &custom_type_name)));
                        return errors
                    },
                };

                // Validate that the custom type is actually a type definition, not a value
                match &custom_symbol.value_type {
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // Valid: struct type
                        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own });
                        // Register struct fields for type checking
                        context.register_struct_fields_for_typecheck(&arg.name, custom_type_name, e);
                    },
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        // Valid: enum type
                        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own });
                    },
                    _ => {
                        // Invalid: not a type, it's a value or something else
                        errors.push(e.error(&context.path, "type", &format!("Argument '{}' has type '{}' which is not a valid type (expected struct or enum)", &arg.name, &custom_type_name)));
                    },
                }
            },
            _ => {
                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own });
            },
        }
    }

    // TODO re-enable test when it is decided what to do with free, memcpy and memset
    // if func_def.function_type == FunctionType::FTFunc || func_def.function_type == FunctionType::FTFuncExt {
    //     if func_def.return_types.len() == 0 && func_def.throw_types.len() == 0 {
    //         errors.push(e.error(&context.path, "type", "funcs must return or throw something, use a proc instead"));
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
                errors.push(se.error(&context.path, "type", "funcs cannot call procs."));
            }
        }
    }
    // Function body statements discard return values at the top level
    for p in &func_def.body {
        errors.extend(check_types_with_context(context, &p, ExprContext::ValueDiscarded));
    }

    let mut return_found = false;
    let mut thrown_types = Vec::new();
    errors.extend(check_body_returns_throws(context, e, func_def, &func_def.body, &mut thrown_types, &mut return_found));

    if !return_found && func_def.return_types.len() > 0 {
        errors.push(e.error(&context.path, "type", "No return statments found in function that returns "));
    }

    // Filter and report only the thrown types that are not declared
    for (thrown_type, error_msg) in &thrown_types {
        if !func_def.throw_types.iter().any(|declared| &value_type_to_str(declared) == thrown_type) {
            errors.push(error_msg.to_string());
        }
    }

    for declared_throw in &func_def.throw_types {
        let declared_str = value_type_to_str(declared_throw);
        if !thrown_types.iter().any(|(t, _)| t == &declared_str) {
            errors.push(e.error(&context.path, "warning", &format!("It looks like `{}` is declared in the throws section, but this function never throws it.\nSuggestion: You can remove it to improve readability.",
                                                    declared_str)));
        }
    }

    return errors
}

pub fn check_body_returns_throws(context: &mut Context, e: &Expr, func_def: &SFuncDef, body: &[Expr], thrown_types: &mut Vec<(String, String)>, return_found: &mut bool) -> Vec<String> {

    let mut errors = vec![];
    let returns_len = func_def.return_types.len();

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
                    errors.push(p.error(&context.path, "type", &format!("Returning {} values when {} were expected.", p.params.len(), returns_len)));
                    errors.push(e.error(&context.path, "type", "Suggestion: Update returns section here"));
                } else {
                    for i in 0..p.params.len() {
                        let expected_value_type = match func_def.return_types.get(i) {
                            Some(t) => t,
                            None => {
                                errors.push(e.lang_error(&context.path, "type", &format!("Fewer return values than provided at position {}", i)));
                                continue;
                            }
                        };
                        let return_val_e = match p.params.get(i) {
                            Some(val) => val,
                            None => {
                                errors.push(e.lang_error(&context.path, "type", &format!("Missing return value at position {}", i)));
                                continue;
                            }
                        };

                        // Recursively check this return expression for throws
                        errors.extend(
                            check_body_returns_throws(context, return_val_e, func_def, std::slice::from_ref(return_val_e), thrown_types, return_found));

                        match get_value_type(&context, return_val_e) {
                            Ok(actual_value_type) => {
                                if expected_value_type != &actual_value_type {
                                    errors.push(return_val_e.error(&context.path, 
                                        "type", &format!("Return value in pos {} expected to be '{}', but found '{}' instead",
                                                         i, value_type_to_str(&expected_value_type), value_type_to_str(&actual_value_type))));
                                    errors.push(e.error(&context.path, "type", "Suggestion: Update returns section here"));
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
                    errors.push(p.error(&context.path, "type", "Throw statement must have exactly one parameter."));
                } else {
                    let throw_param = &p.params[0];
                    // Recursively check this throw expression for throws (just in case, although users should avoid this)
                    // TODO fix this, not a priority
                    // errors.extend(
                    //     check_body_returns_throws(context, throw_param, func_def, std::slice::from_ref(throw_param), thrown_types, return_found));

                    match get_value_type(&context, throw_param) {
                        Ok(thrown_type) => {
                            if thrown_type == ValueType::TType(TTypeDef::TStructDef) {
                                errors.push(throw_param.error(&context.path, "type", "Cannot throw a struct definition.\nSuggestion: Create an instance by adding parentheses at the end."));
                            } else {
                                // Track the thrown type as a string and another string with its error
                                let thrown_type_str = value_type_to_str(&thrown_type);
                                thrown_types.push((thrown_type_str.clone(), throw_param.error(&context.path, "type", &format!("Function throws '{}', but it is not declared in this function's throws section.", thrown_type_str))));
                                thrown_types.push((thrown_type_str.clone(), e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block")));
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
                    errors.push(p.error(&context.path, "type", "Catch must have 3 parameters: variable, type, and body."));
                } else {
                    let err_type_expr = &p.params[1];
                    let catch_body_expr = &p.params[2];

                    let caught_type = match &err_type_expr.node_type {
                        NodeType::Identifier(name) => name.clone(),
                        _ => {
                            errors.push(err_type_expr.error(&context.path, "type", "Catch type must be a valid identifier"));
                            return errors;
                        }
                    };

                    // Remove first, before descending into body
                    if thrown_types.iter().any(|(t, _)| t == &caught_type) {
                        thrown_types.retain(|(t, _)| t != &caught_type);
                    } else {
                        errors.push(p.error(&context.path, "warning", &format!("Trying to catch '{}', but it is not among the thrown types", caught_type)));
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
                        for called_throw in &called_func_def.throw_types {
                            let called_throw_str = value_type_to_str(called_throw);
                            let error_msg = format!(
                                "Function throws '{}', but it is not declared in this function's throws section.",
                                called_throw_str
                            );

                            thrown_types.push((called_throw_str.clone(), p.error(&context.path, "type", &error_msg)));
                            thrown_types.push((called_throw_str.clone(), e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block")));
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
                                        // Ok(None) is returned for enum constructors and struct instantiation
                                        // These are valid and don't throw errors, so we don't add an error here
                                    },
                                    Err(reason) => {
                                        errors.push(arg.error(&context.path, "type", &format!("Failed to resolve nested function call: {}", reason)));
                                    }
                                }
                            }
                        }
                    },
                    Ok(None) => {
                        // Ok(None) is returned for enum constructors and struct instantiation
                        // These are valid and don't throw errors, so we don't add an error here
                    },
                    Err(reason) => {
                        errors.push(p.error(&context.path, "type", &reason));
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
                                if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
                                    if symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                                        continue; // Skip default constructor calls, for instantiations like 'StructName()'
                                    }
                                }
                            }

                            // Check for enum constructors (e.g., Color.Green(true))
                            if id_expr.params.len() == 1 {
                                if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
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
                                for called_throw in &called_func_def.throw_types {
                                    let called_throw_str = value_type_to_str(called_throw);
                                    let error_msg = format!(
                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                        called_throw_str
                                    );

                                    thrown_types.push((called_throw_str.clone(), initializer.error(&context.path, "type", &error_msg)));
                                    thrown_types.push((called_throw_str.clone(), e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block")));
                                }

                                let mut temp_thrown_types = Vec::new();
                                errors.extend(check_body_returns_throws(context, initializer, &called_func_def, &initializer.params, &mut temp_thrown_types, return_found));
                                thrown_types.extend(temp_thrown_types);
                            },
                            Ok(None) => {
                                errors.push(initializer.error(&context.path, "type", "Could not resolve function definition in declaration initializer."));
                            },
                            Err(reason) => {
                                errors.push(initializer.error(&context.path, "type", &format!("Failed to resolve function in declaration initializer: {}", reason)));
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
        errors.push(e.error(&context.path, "type", "Catch node must have three parameters: variable, type, and body."));
        return errors
    }

    let err_var_expr = &e.params[0];
    let err_type_expr = &e.params[1];
    let body_expr = &e.params[2];

    let var_name = match &err_var_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_var_expr.error(&context.path, "type", "First catch param must be an identifier"));
            return errors
        }
    };

    let type_name = match &err_type_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_type_expr.error(&context.path, "type", "Second catch param must be a type identifier"));
            return errors
        }
    };

    // Confirm that the type exists in the context (as done for function args)
    if context.scope_stack.lookup_symbol(&type_name).is_none() {
        errors.push(e.error(&context.path, "type", &format!("Catch refers to undefined type '{}'", &type_name)));
        return errors
    }

    // Create scoped context for catch body
    let mut temp_context = context.clone();
    temp_context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name.clone()),
        is_mut: false,
        is_copy: false,
        is_own: false,
    });

    // Map struct fields so err.msg etc. can be accessed during type-checking
    if let Some(struct_def) = context.scope_stack.lookup_struct(&type_name) {
        for (field_name, field_decl) in &struct_def.members {
            let combined_name = format!("{}.{}", var_name, field_name);
            temp_context.scope_stack.declare_symbol(
                combined_name.clone(),
                SymbolInfo {
                    value_type: field_decl.value_type.clone(),
                    is_mut: false,  // Error variables are not mutable in catch blocks
                    is_copy: false,
                    is_own: false,
                },
            );
        }
    }

    // Catch body statements discard return values
    errors.extend(check_types_with_context(&mut temp_context, body_expr, ExprContext::ValueDiscarded));

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
    if context.scope_stack.lookup_symbol(&decl.name).is_none() {
        let mut value_type = decl.value_type.clone();
        if value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
            value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
        }
        // TODO move to init_context() ? inner contexts are not persisted in init_context
        context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own });
        match value_type {
            ValueType::TCustom(custom_type) => {
                if custom_type == INFER_TYPE {
                    errors.push(e.lang_error(&context.path, "type", &format!("Cannot infer the declaration type of {}", decl.name)));
                    return errors;
                }
                // During type checking, register struct fields so they can be accessed in the code
                // Memory allocation and default value evaluation happens during runtime in eval_declaration
                if context.scope_stack.lookup_struct(&custom_type).is_some() {
                    context.register_struct_fields_for_typecheck(&decl.name, &custom_type, e);
                }
            }
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                match &inner_e.node_type {
                    NodeType::FuncDef(func_def) => {
                        // TODO move to init_context() ? inner contexts are not persisted in init_context
                        context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
                    },
                    _ => {
                        errors.push(e.lang_error(&context.path, "type", "functions should have definitions"));
                        return errors;
                    },
                }
            },
            _ => {},
        }
    }
    // The RHS of a declaration is being used (assigned to the variable)
    errors.extend(check_types_with_context(context, &inner_e, ExprContext::ValueUsed));

    return errors
}

fn check_assignment(context: &mut Context, e: &Expr, var_name: &str) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in assignment to {}, assignments must take exactly one value, not {}.",
                                                  var_name, e.params.len())));
        return errors
    }

    if context.scope_stack.lookup_func(var_name).is_some()  {
        errors.push(e.error(&context.path, "type", &format!("function '{}' cannot be assigned to.", var_name)));
    } else if context.scope_stack.lookup_symbol(var_name).is_some() {
        let symbol_info = match context.scope_stack.lookup_symbol(var_name) {
            Some(info) => info,
            None => {
                errors.push(e.error(&context.path, "type", &format!("Undeclared variable '{}'", var_name)));
                return errors;
            }
        };
        if !symbol_info.is_mut && !symbol_info.is_copy && !symbol_info.is_own {
            errors.push(e.error(&context.path, "type", &format!("Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", var_name)));
        }
        // Additional check: if this is a field access (e.g., "s.value"), also check base instance mutability
        if var_name.contains('.') {
            let base_var = var_name.split('.').next().unwrap();
            if let Some(base_info) = context.scope_stack.lookup_symbol(base_var) {
                if !base_info.is_mut && !base_info.is_copy && !base_info.is_own {
                    errors.push(e.error(&context.path, "type", &format!("Cannot assign to field of constant '{}', Suggestion: declare it as 'mut {}'.", base_var, base_var)));
                }
            }
        }
    } else if var_name.contains('.') {
        // Field access assignment where the field itself isn't registered in symbols
        // With dynamic offset calculation, we need to validate against struct definition
        let parts: Vec<&str> = var_name.split('.').collect();
        let base_var = parts[0];

        if let Some(base_info) = context.scope_stack.lookup_symbol(base_var) {
            // Check base mutability
            if !base_info.is_mut && !base_info.is_copy && !base_info.is_own {
                errors.push(e.error(&context.path, "type", &format!("Cannot assign to field of constant '{}', Suggestion: declare it as 'mut {}'.", base_var, base_var)));
            }

            // Validate field path exists in struct definition
            let mut current_type = base_info.value_type.clone();
            for field_name in &parts[1..] {
                match current_type {
                    ValueType::TCustom(ref type_name) => {
                        if let Some(struct_def) = context.scope_stack.lookup_struct(type_name) {
                            if let Some((_, field_decl)) = struct_def.members.iter().find(|(name, _)| name == field_name) {
                                current_type = field_decl.value_type.clone();
                            } else {
                                errors.push(e.error(&context.path, "type", &format!("Field '{}' not found in struct '{}'", field_name, type_name)));
                                break;
                            }
                        } else {
                            errors.push(e.error(&context.path, "type", &format!("Struct '{}' not found", type_name)));
                            break;
                        }
                    },
                    _ => {
                        errors.push(e.error(&context.path, "type", &format!("Cannot access field '{}' on non-struct type", field_name)));
                        break;
                    }
                }
            }
        } else {
            errors.push(e.error(&context.path, "type", &format!("Undefined symbol '{}'", base_var)));
        }
    } else {
        errors.push(e.error(&context.path, "type", &format!("Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                                             var_name, var_name, var_name)));
    }

    // The RHS of an assignment is being used (assigned to the variable)
    match e.get(0) {
        Ok(inner_e) => errors.extend(check_types_with_context(context, inner_e, ExprContext::ValueUsed)),
        Err(err) => errors.push(err),
    }
    return errors;
}

fn check_switch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    let switch_expr_type = match e.get(0) {
        Ok(expr) => match get_value_type(context, expr) {
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
                    errors.push(case_expr.error(&context.path, "type", "Duplicate default case in switch"));
                }
                default_found = true;
                case_found = true;
            }
            NodeType::Pattern(_) => {
                // Pattern matching - type is checked in exhaustiveness check below
                case_found = true;
                // No need to check type here - patterns implicitly match the switch type
            }
            _ => {
                case_found = true;

                match get_value_type(context, case_expr) {
                    Ok(case_type) => {
                        let switch_type_str = value_type_to_str(&switch_expr_type);
                        let case_type_str = value_type_to_str(&case_type);
                        if case_type_str != switch_type_str && case_type_str != format!("{}Range", switch_type_str) {
                            errors.push(case_expr.error(&context.path, "type", &format!(
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
            errors.push(e.error(&context.path, "type", "Switch case missing body expression"));
            return errors
        }

        let body_expr = &e.params[i];

        // For pattern matching, add the binding variable to the context before type checking the body
        if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case_expr.node_type {
            // Get the payload type for this variant
            if let ValueType::TCustom(enum_name) = &switch_expr_type {
                if let Some(enum_def) = context.scope_stack.lookup_enum(enum_name) {
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
                            temp_context.scope_stack.declare_symbol(
                                binding_var.clone(),
                                SymbolInfo {
                                    value_type: payload_type.clone(),
                                    is_mut: false,
                                    is_copy: false,
                                is_own: false,
                                }
                            );
                            // Switch case body statements discard return values
                            errors.extend(check_types_with_context(&mut temp_context, body_expr, ExprContext::ValueDiscarded));
                        } else {
                            // Variant exists but has no payload
                            errors.push(case_expr.error(&context.path, "type", &format!("Variant '{}' has no payload, cannot use pattern matching", variant)));
                            errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                        }
                    } else {
                        errors.push(case_expr.error(&context.path, "type", &format!("Unknown variant '{}'", variant)));
                        errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                    }
                } else {
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                }
            } else {
                errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
            }
        } else {
            errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
        }

        i += 1;
    }

    if !case_found {
        errors.push(e.error(&context.path, "type", "Switch must have at least one case"));
    }

    // Exhaustiveness check only for enums
    if let ValueType::TCustom(enum_name) = switch_expr_type {
        if let Some(enum_def) = context.scope_stack.lookup_enum(&enum_name) {
            let mut matched_variants: Vec<String> = Vec::new();

            let mut j = 1;
            while j < e.params.len() {
                let case_expr = &e.params[j];
                match &case_expr.node_type {
                    NodeType::Pattern(PatternInfo { variant_name, .. }) => {
                        // Pattern matching: case EnumType.Variant(binding)
                        // Extract the variant name from the full "EnumType.Variant" string
                        if let Some(dot_pos) = variant_name.rfind('.') {
                            let enum_part = &variant_name[..dot_pos];
                            let variant_part = &variant_name[dot_pos + 1..];
                            if enum_part != enum_name {
                                errors.push(case_expr.error(&context.path, "type", &format!("Mismatched enum type '{}', expected '{}'.", enum_part, enum_name)));
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
                                    errors.push(case_expr.error(&context.path, "type", &format!("Mismatched enum type '{}', expected '{}'.", name, enum_name)));
                                }
                                matched_variants.push(variant.clone());
                            } else {
                                errors.push(case_expr.error(&context.path, "type", "Invalid enum case syntax"));
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
                        errors.push(e.error(&context.path, "type", &format!("Switch is missing case for variant '{}'", variant)));
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

    for (member_name, member_decl) in &struct_def.members {
        // Validate that the member's declared type exists (if it's a custom type)
        match &member_decl.value_type {
            ValueType::TCustom(ref custom_type_name) => {
                // Skip built-in types and special types
                if custom_type_name != "Dynamic" && custom_type_name != "Type" && custom_type_name != INFER_TYPE {
                    // Check if the type exists
                    if context.scope_stack.lookup_symbol(custom_type_name).is_none() {
                        errors.push(e.error(&context.path, "type", &format!(
                            "Struct member '{}' uses undefined type '{}'.\nHint: Make sure '{}' is defined before this struct.",
                            member_name, custom_type_name, custom_type_name
                        )));
                    } else {
                        // Validate it's actually a type (enum or struct), not a value
                        let symbol_info = context.scope_stack.lookup_symbol(custom_type_name).unwrap();
                        match &symbol_info.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) |
                            ValueType::TType(TTypeDef::TStructDef) |
                            ValueType::TCustom(_) => {
                                // Valid type (TCustom covers built-in types like I64, Str, etc.)
                            },
                            _ => {
                                errors.push(e.error(&context.path, "type", &format!(
                                    "Struct member '{}' type '{}' is not a valid type (expected enum, struct, or primitive, found {}).",
                                    member_name, custom_type_name, value_type_to_str(&symbol_info.value_type)
                                )));
                            }
                        }
                    }
                }
            },
            _ => {} // Non-custom types (like functions) are handled elsewhere
        }

        match struct_def.default_values.get(member_name) {
            Some(inner_e) => {
                // println!("inner_e {:?}", inner_e);
                match &inner_e.node_type {
                    // If the member's default value is a function (method), type check it
                    NodeType::FuncDef(func_def) => {
                        let mut function_context = context.clone();
                        errors.extend(check_func_proc_types(&func_def, &mut function_context, &inner_e));
                    },
                    // For other types of members, check type and purity
                    _ => {
                        // Check if default value calls procs (violates purity of constructors)
                        if is_expr_calling_procs(context, inner_e) {
                            errors.push(inner_e.exit_error("type",
                                &format!("Struct field '{}' has default value that calls proc. Default values must be pure (can only call funcs, not procs).", member_name)));
                        }

                        // Check if default value type matches declared member type
                        let expected_type = &member_decl.value_type;
                        let found_type = match get_value_type(&context, inner_e) {
                            Ok(val_type) => val_type,
                            Err(error_string) => {
                                errors.push(error_string);
                                continue;
                            },
                        };

                        // Check if the value is a numeric literal (for implicit conversion)
                        let is_numeric_literal = matches!(&inner_e.node_type, NodeType::LLiteral(Literal::Number(_)));

                        match expected_type {
                            ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => {}, // Accept any type for Dynamic/Type
                            ValueType::TCustom(tn) if tn == INFER_TYPE => {}, // Type inference is OK
                            // Allow implicit conversion from I64 literals to U8
                            ValueType::TCustom(tn) if tn == "U8" && found_type == ValueType::TCustom("I64".to_string()) && is_numeric_literal => {},
                            _ if expected_type != &found_type => {
                                errors.push(inner_e.error(&context.path, "type", &format!(
                                    "Struct field '{}' declared as '{}' but default value has type '{}'.",
                                    member_name, value_type_to_str(expected_type), value_type_to_str(&found_type)
                                )));
                            },
                            _ => {} // types match; no error
                        }
                    }
                }
            },
            None => {
                errors.push(e.todo_error(&context.path, "type", &format!("Member '{}' lacks a default value. Not allowed yet.", member_name)));
            }
        }
    }

    // Check if collection-like structs have mandatory len() and size() methods
    // A struct is considered collection-like if it has push/get/set/insert methods
    // Note: delete() is excluded as it's a cleanup method, not a collection operation
    let has_push = struct_def.get_member("push").is_some();
    let has_get = struct_def.get_member("get").is_some();
    let has_set = struct_def.get_member("set").is_some();
    let has_insert = struct_def.get_member("insert").is_some();

    if has_push || has_get || has_set || has_insert {
        // This looks like a collection type - check for len() method
        let has_len = struct_def.get_member("len")
            .map(|decl| !decl.is_mut)
            .unwrap_or(false);

        if !has_len {
            let struct_name = e.params.get(0)
                .and_then(|param| {
                    if let NodeType::Identifier(name) = &param.node_type {
                        Some(name.as_str())
                    } else {
                        None
                    }
                })
                .unwrap_or("unknown");

            let methods: Vec<&str> = vec![
                if has_push { Some("push()") } else { None },
                if has_get { Some("get()") } else { None },
                if has_set { Some("set()") } else { None },
                if has_insert { Some("insert()") } else { None },
            ].into_iter().filter_map(|x| x).collect();

            errors.push(e.error(&context.path, "type", &format!(
                "Collection-like struct '{}' has {} method(s) but no len() method.\n\
                 Reason: Collection types must provide a way to query their size.\n\
                 Suggestion: add 'len := func(self: {}) returns I64 {{ ... }}' to struct '{}'.",
                struct_name, methods.join("/"), struct_name, struct_name
            )));
        }

        // Also check for size() method (returns size in bytes)
        let has_size = struct_def.get_member("size")
            .map(|decl| !decl.is_mut)
            .unwrap_or(false);

        if !has_size {
            let struct_name = e.params.get(0)
                .and_then(|param| {
                    if let NodeType::Identifier(name) = &param.node_type {
                        Some(name.as_str())
                    } else {
                        None
                    }
                })
                .unwrap_or("unknown");

            let methods: Vec<&str> = vec![
                if has_push { Some("push()") } else { None },
                if has_get { Some("get()") } else { None },
                if has_set { Some("set()") } else { None },
                if has_insert { Some("insert()") } else { None },
            ].into_iter().filter_map(|x| x).collect();

            errors.push(e.error(&context.path, "type", &format!(
                "Collection-like struct '{}' has {} method(s) but no size() method.\n\
                 Reason: Collection types must provide their size in bytes.\n\
                 Suggestion: add 'size := func(self: {}) returns I64 {{ ... }}' to struct '{}'.\n\
                 Note: size() should return the total size in bytes, not element count (use len() for that).",
                struct_name, methods.join("/"), struct_name, struct_name
            )));
        }
    }

    return errors
}

pub fn get_func_def_for_fcall_with_expr(context: &Context, fcall_expr: &mut Expr) -> Result<Option<SFuncDef>, String> {
    if fcall_expr.node_type != NodeType::FCall {
        return Err(fcall_expr.lang_error(&context.path, "type", "Expected FCall node type"));
    }
    let func_expr = match fcall_expr.params.first() {
        Some(expr) => expr,
        None => return Err(fcall_expr.lang_error(&context.path, "type", "get_func_def_for_fcall_with_expr: Fcalls must have a name")),
    };

    match &func_expr.node_type {
        NodeType::Identifier(_) => {
            // Regular functions and associated functions used directly
            let combined_name = crate::rs::parser::get_combined_name(&context.path, func_expr)?;

            // NEW: Check if this is a UFCS call on a function/expression result
            // If params has 2+ elements and params[1] is an expression (FCall, etc.)
            if fcall_expr.params.len() >= 2 {
                let first_arg = fcall_expr.get(1)?;
                // Try to get the type of the first argument
                if let Ok(target_type) = get_value_type(context, first_arg) {
                    if let ValueType::TCustom(custom_type_name) = target_type {
                        // Check if this type has an associated method
                        let method_name = format!("{}.{}", custom_type_name, combined_name);
                        if let Some(func_def) = context.scope_stack.lookup_func(&method_name) {
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
            if let Some(func_def) = context.scope_stack.lookup_func(&combined_name) {
                return Ok(Some(func_def.clone()))
            }

            if let Some(_struct_def) = context.scope_stack.lookup_struct(&combined_name) {
                return Ok(None) // REM: This is to allow struct instantiation
            }

            // Check for enum constructors (e.g., Color.Green(true))
            let parts: Vec<&str> = combined_name.split('.').collect();
            if parts.len() == 2 {
                let enum_type = parts[0];
                if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type) {
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
                    if let Some(func_def) = context.scope_stack.lookup_func(&ufcs_func_name.to_string()) {

                        let new_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), fcall_expr.get(0)?, Vec::new());
                        let mut new_args = Vec::new();
                        new_args.push(new_e);
                        new_args.push(extra_arg_e);
                        new_args.extend(fcall_expr.params[1..].to_vec());

                        *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                        return Ok(Some(func_def.clone()))
                    }

                    // Associated functions used with UFCS (aka methods)
                    if let Some(symbol_info) = context.scope_stack.lookup_symbol(&new_combined_name) {

                        match &symbol_info.value_type {
                            ValueType::TCustom(ref custom_type_name) => {
                                let id_expr_name = format!("{}.{}", custom_type_name, ufcs_func_name);
                                if let Some(func_def) = context.scope_stack.lookup_func(&id_expr_name) {

                                    let new_e = Expr::new_clone(NodeType::Identifier(id_expr_name.clone()), fcall_expr.get(0)?, Vec::new());
                                    let mut new_args = Vec::new();
                                    new_args.push(new_e);
                                    new_args.push(extra_arg_e);
                                    new_args.extend(fcall_expr.params[1..].to_vec());

                                    *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                                    return Ok(Some(func_def.clone()))
                                }
                            },
                            found_value_type => return Err(func_expr.error(&context.path, "type", &format!(
                                "'{}' is of type '{}' and thus can't have a '{}' associated function",
                                new_combined_name, value_type_to_str(&found_value_type), ufcs_func_name)))
                        }
                    }
                }
            }
            return Err(func_expr.lang_error(&context.path, "type", "Could not find function defintion"))
        },
        _ => return Err(func_expr.lang_error(&context.path, "type", "Expected Identifier node type"))
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
        NodeType::StructDef(struct_def) => {
            // Check if any default values call procs
            for (_member_name, default_expr) in &struct_def.default_values {
                if is_expr_calling_procs(context, default_expr) {
                    return true
                }
            }
            return false
        },
        NodeType::EnumDef(_) => {
            return false
        },
        NodeType::LLiteral(_) => return false,
        NodeType::DefaultCase => return false,
        NodeType::Pattern(_) => return false,
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
            // Check if the function being called is a proc
            let f_name = get_func_name_in_call(e);
            // TODO Temp: In the future, implement a special PanicError that's potentially  thrown implicitly everywhere
            if f_name == "panic" {
                return false
            }
            let func_is_proc = match context.scope_stack.lookup_func(&f_name) {
                Some(func) => func.is_proc(),
                None => false,
            };

            // Also check if any of the arguments call procs
            // Skip the first param which is the function name itself
            for i in 1..e.params.len() {
                if is_expr_calling_procs(context, &e.params[i]) {
                    return true
                }
            }

            return func_is_proc
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
                            errors.push(e.error(&context.path, "mode", &format!("mode {} doesn't allow mut declarations of 'mut {}'.\nSuggestion: remove 'mut' or change to mode script or cli",
                                                                 context.mode.name, decl.name)));
                        }
                    },
                    NodeType::FCall => {
                        if !context.mode.allows_base_calls {
                            let f_name = get_func_name_in_call(&p);
                            if f_name != "import" {
                                errors.push(e.error(&context.path, "mode", &format!("mode {} doesn't allow calls in the root context of the file'.\nSuggestion: remove the call to '{}' or change mode 'test' or 'script'",
                                                                     context.mode.name, f_name)));
                            }
                        }
                    },
                    _ => {},
                }
            }
        },
        _ => {
            errors.push(e.lang_error(&context.path, "mode", "basic_mode_checks() expects a body expression, this should never happen."))
        },
    }

    if context.mode.needs_main_proc {
        match context.scope_stack.lookup_symbol("main") {
            Some(symbol_info) => {
                if symbol_info.value_type != ValueType::TFunction(FunctionType::FTProc) {
                    errors.push(e.error(&context.path, "mode", &format!("mode {} requires 'main' to be defined as a proc. It was defined as a {} instead",
                                                         context.mode.name, value_type_to_str(&symbol_info.value_type))));
                }
            },
            None => {
                errors.push(e.error(&context.path, "mode", &format!("mode {} requires 'main' to be defined as a proc.", context.mode.name)));
            },
        };
    }
    return errors;
}

