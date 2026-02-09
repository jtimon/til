// External/Core functions for TIL interpreter
// This module contains all built-in core functions and procedures.

use std::convert::TryInto;
use crate::rs::init::{Context, SymbolInfo};
use crate::rs::parser::{
    Expr, NodeType, Literal, ValueType,
    get_combined_name,
};
use crate::rs::eval_arena::EvalArena;
use crate::rs::interpreter::{EvalResult, eval_expr, string_from_context};
use std::io;
use std::io::{ErrorKind, Write};
use std::fs;
use std::process::{Command, Child};
use std::collections::HashMap;
use std::thread;
use std::time::Duration;

// ---------- Helper functions

// General whitelist for all modes
// TODO: "bash" is a temporary workaround for passing arguments to tests (src/tests.til).
// Proper fix: add Array spread/apply operation to pass dynamic args to variadic functions.
// Having bash here defeats the whitelist purpose since bash -c can run anything.
const ALLOWED_COMMANDS: [&str; 9] = ["ls", "mkdir", "find", "gcc", "./bin/rstil", "diff", "bash", "rm", "cp"];
// More restrictive whitelist for safe_script mode
const SAFE_COMMANDS: [&str; 2] = ["ls", "mkdir"];

/// Macro to evaluate an expression and propagate throws early
macro_rules! eval_or_throw {
    ($context:expr, $expr:expr) => {{
        let result = eval_expr($context, $expr)?;
        if result.is_throw {
            return Ok(result);
        }
        result.value
    }};
}

/// Validates that a function/procedure call has the expected number of arguments.
/// The e.params.len() includes the function name as the first parameter, so we subtract 1.
pub fn validate_arg_count(path: &str, e: &Expr, func_name: &str, expected: usize, is_proc: bool) -> Result<(), String> {
    let actual = e.params.len() - 1; // First param is function name
    if actual != expected {
        let func_type = if is_proc { "proc" } else { "func" };
        let plural = if expected == 1 { "" } else { "s" };
        return Err(e.lang_error(path, "eval", &format!(
            "Core {} '{}' takes exactly {} argument{}",
            func_type, func_name, expected, plural
        )));
    }
    Ok(())
}

// Note: loc, _file, _line, _col moved to precomp_ext.rs (replaced with literals at compile time)

// ---------- eval memory

pub fn func_malloc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "malloc", 1, false)?;

    let size_str = eval_or_throw!(context, e.get(1)?);
    let size = size_str.parse::<usize>().map_err(|err| {
        e.lang_error(&context.path, "eval", &format!("Invalid size for 'malloc': {}", err))
    })?;
    let offset = if size > 0 { EvalArena::g().reserve(size)? } else { EvalArena::g().len() };

    if offset == 0 { // TODO: REM: throw AllocError instead of return NULL pointer
        return Err(e.lang_error(&context.path, "eval", "Core func 'malloc' was about to produce a NULL pointer"))
    }
    return Ok(EvalResult::new(&offset.to_string()))
}

pub fn func_free(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "free", 1, false)?;

    let _ptr_str = eval_or_throw!(context, e.get(1)?);
    // REM: Free does nothing in arena model (for now).

    return Ok(EvalResult::new(""))
}

pub fn func_memset(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "memset", 3, false)?;

    let dest_str = eval_or_throw!(context, e.get(1)?);
    let value_str = eval_or_throw!(context, e.get(2)?);
    let size_str = eval_or_throw!(context, e.get(3)?);

    let dest = match dest_str.trim().parse::<i64>() {
        Ok(v) => v as usize,
        Err(err) => return Err(e.error(&context.path, "eval", &format!("Invalid dest (I64): '{}': {}", dest_str, err))),
    };

    let value = match value_str.trim().parse::<u8>() {
        Ok(v) => v,
        Err(err) => return Err(e.error(&context.path, "eval", &format!("Invalid value (U8): '{}': {}", value_str, err))),
    };

    let size = match size_str.trim().parse::<i64>() {
        Ok(v) => v as usize,
        Err(err) => return Err(e.error(&context.path, "eval", &format!("Invalid size (I64): '{}': {}", size_str, err))),
    };

    if dest + size > EvalArena::g().len() {
        return Err(e.error(&context.path, "eval", &format!(
            "memset out of bounds: dest={} size={} arena_len={}",
            dest, size, EvalArena::g().len()
        )));
    }

    for i in 0..size {
        EvalArena::g().set(dest + i, &[value])?;
    }

    Ok(EvalResult::new(""))
}

pub fn func_memcpy(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "memcpy", 3, false)?;

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
        Err(err) => return Err(e.lang_error(&context.path, "eval", &format!("memcpy: Invalid dest (usize): '{}': {}", dest_str, err))),
    };

    let src = match src_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error(&context.path, "eval", &format!("memcpy: Invalid src (usize): '{}': {}", src_str, err))),
    };

    let size = match size_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error(&context.path, "eval", &format!("memcpy: Invalid size (usize): '{}': {}", size_str, err))),
    };

    if dest + size > EvalArena::g().len() || src + size > EvalArena::g().len() {
        return Err(e.error(&context.path, "eval", &format!("memcpy out of bounds: src={} dest={} size={} arena_len={}",
                                            src, dest, size, EvalArena::g().len())));
    }

    for i in 0..size {
        let byte = EvalArena::g().get(src + i, 1)[0];
        EvalArena::g().set(dest + i, &[byte])?;
    }

    Ok(EvalResult::new(""))
}

pub fn func_memcmp(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "memcmp", 3, false)?;

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
        Err(err) => return Err(e.lang_error(&context.path, "eval", &format!("memcmp: Invalid ptr1 (usize): '{}': {}", ptr1_str, err))),
    };

    let ptr2 = match ptr2_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error(&context.path, "eval", &format!("memcmp: Invalid ptr2 (usize): '{}': {}", ptr2_str, err))),
    };

    let size = match size_str.parse::<usize>() {
        Ok(v) => v,
        Err(err) => return Err(e.lang_error(&context.path, "eval", &format!("memcmp: Invalid size (usize): '{}': {}", size_str, err))),
    };

    if ptr1 + size > EvalArena::g().len() || ptr2 + size > EvalArena::g().len() {
        return Err(e.error(&context.path, "eval", &format!("memcmp out of bounds: ptr1={} ptr2={} size={} arena_len={}",
                                            ptr1, ptr2, size, EvalArena::g().len())));
    }

    // Compare bytes
    for i in 0..size {
        let byte1 = EvalArena::g().get(ptr1 + i, 1)[0];
        let byte2 = EvalArena::g().get(ptr2 + i, 1)[0];
        if byte1 < byte2 {
            return Ok(EvalResult::new("-1"));
        } else if byte1 > byte2 {
            return Ok(EvalResult::new("1"));
        }
    }

    // All bytes equal
    Ok(EvalResult::new("0"))
}

pub fn func_to_ptr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "to_ptr", 1, false)?;

    let identifier_expr = e.get(1)?;
    let combined_name = get_combined_name(&context.path, identifier_expr)?;
    match context.scope_stack.lookup_var(&combined_name) {
        Some(addr) => Ok(EvalResult::new(&format!("{}", addr))),
        None => Err(e.lang_error(&context.path, "eval", &format!("calling core func to_ptr, but '{}' is not a known identifier.", combined_name))),
    }
}

pub fn func_create_alias(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "create_alias", 3, false)?;

    // Param 1: NOT evaluated - variable name from AST
    let identifier_expr = e.get(1)?;
    let combined_name = get_combined_name(&context.path, identifier_expr)?;

    // Param 2: NOT evaluated - type name
    let type_expr = e.get(2)?;
    let type_name = match &type_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return Err(e.lang_error(&context.path, "eval", "create_alias: second argument must be a type name identifier")),
    };

    // Param 3: evaluated - source address (I64)
    let addr_str = eval_or_throw!(context, e.get(3)?);
    let addr = addr_str.parse::<usize>().map_err(|err| {
        e.lang_error(&context.path, "eval", &format!("create_alias: Invalid address (I64): '{}': {}", addr_str, err))
    })?;

    // Declare variable with type and bind to source address
    context.scope_stack.declare_symbol(combined_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name),
        is_mut: true,
        is_copy: false,
        is_own: false,
        is_comptime_const: false,
    });
    context.scope_stack.insert_var(combined_name, addr);

    Ok(EvalResult::new(""))
}

pub fn func_size_of(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "size_of", 1, false)?;

    let type_expr = e.get(1)?;
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            // Check if this identifier is a string variable (Dynamic parameter storing a type name)
            let actual_type_name = if let Some(sym) = context.scope_stack.lookup_symbol(type_name) {
                if let ValueType::TCustom(ref custom_type) = sym.value_type {
                    if custom_type == "Str" {
                        // This might be a Dynamic parameter - try to get its string value
                        match string_from_context(context, type_name, e) {
                            Ok(stored_type_name) => stored_type_name,
                            Err(_) => type_name.to_string(),
                        }
                    } else {
                        type_name.to_string()
                    }
                } else {
                    type_name.to_string()
                }
            } else {
                type_name.to_string()
            };

            match context.get_type_size(&actual_type_name) {
                Ok(size) => Ok(EvalResult::new(&format!("{}", size))),
                Err(msg) => Err(e.lang_error(&context.path, "eval", &format!("calling core func size: {}", msg))),
            }
        },
        node_type => Err(e.lang_error(&context.path, "eval", &format!("calling core func size_of, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

pub fn func_type_as_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "type_as_str", 1, false)?;

    let type_expr = e.get(1)?;
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            // Check if this identifier is a string variable (Dynamic parameter storing a type name)
            let actual_type_name = if let Some(sym) = context.scope_stack.lookup_symbol(type_name) {
                if let ValueType::TCustom(ref custom_type) = sym.value_type {
                    if custom_type == "Str" {
                        // This might be a Dynamic parameter - try to get its string value
                        match string_from_context(context, type_name, e) {
                            Ok(stored_type_name) => stored_type_name,
                            Err(_) => type_name.to_string(),
                        }
                    } else {
                        type_name.to_string()
                    }
                } else {
                    type_name.to_string()
                }
            } else {
                type_name.to_string()
            };

            Ok(EvalResult::new(&actual_type_name))
        },
        node_type => Err(e.lang_error(&context.path, "eval", &format!("calling core func type_as_str, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

pub fn func_lt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "lt", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'lt': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'lt': {}", err)))?;
    Ok(EvalResult::new(&(a < b).to_string()))
}

pub fn func_gt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "gt", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'gt': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'gt': {}", err)))?;
    Ok(EvalResult::new(&(a > b).to_string()))
}

pub fn func_u8_lt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "u8_lt", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_lt': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_lt': {}", err)))?;
    Ok(EvalResult::new(&(a < b).to_string()))
}

pub fn func_u8_gt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "u8_gt", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_gt': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_gt': {}", err)))?;
    Ok(EvalResult::new(&(a > b).to_string()))
}

pub fn func_u8_xor(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "u8_xor", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_xor': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_xor': {}", err)))?;
    Ok(EvalResult::new(&(a ^ b).to_string()))
}

pub fn func_u8_and(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "u8_and", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_and': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_and': {}", err)))?;
    Ok(EvalResult::new(&(a & b).to_string()))
}

pub fn func_u8_or(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "u8_or", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_or': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid u8 for 'u8_or': {}", err)))?;
    Ok(EvalResult::new(&(a | b).to_string()))
}

pub fn func_add(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "add", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'add': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'add': {}", err)))?;
    Ok(EvalResult::new(&(a.wrapping_add(b)).to_string()))
}

pub fn func_sub(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "sub", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'sub': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'sub': {}", err)))?;
    Ok(EvalResult::new(&(a.wrapping_sub(b)).to_string()))
}

pub fn func_mul(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "mul", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'mul': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'mul': {}", err)))?;
    Ok(EvalResult::new(&(a.wrapping_mul(b)).to_string()))
}

pub fn func_div(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "div", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'div': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'div': {}", err)))?;
    // Return 0 for division by zero (safe default, revisit post-self-hosting)
    if b == 0 {
        return Ok(EvalResult::new("0"));
    }
    Ok(EvalResult::new(&(a / b).to_string()))
}

pub fn func_mod(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "mod", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result); // Propagate throw
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result); // Propagate throw
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'mod': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'mod': {}", err)))?;
    // Return 0 for modulo by zero (safe default, revisit post-self-hosting)
    if b == 0 {
        return Ok(EvalResult::new("0"));
    }
    Ok(EvalResult::new(&(a % b).to_string()))
}

// Bitwise operations - don't really belong in arithmetics, but here for now
pub fn func_i64_xor(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "I64_xor", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'I64_xor': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'I64_xor': {}", err)))?;
    Ok(EvalResult::new(&(a ^ b).to_string()))
}

pub fn func_i64_and(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "I64_and", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'I64_and': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'I64_and': {}", err)))?;
    Ok(EvalResult::new(&(a & b).to_string()))
}

pub fn func_i64_or(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "I64_or", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'I64_or': {}", err)))?;
    let b = b_result.value.parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid integer for 'I64_or': {}", err)))?;
    Ok(EvalResult::new(&(a | b).to_string()))
}

pub fn func_str_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "str_to_i64", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid input for 'str_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

pub fn func_i64_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "i64_to_str", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

pub fn func_enum_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "enum_to_str", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

pub fn func_enum_get_payload(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "enum_get_payload", 3, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result);
    }
    // Get payload type from second argument
    let type_arg = e.get(2)?;
    let type_name = if let NodeType::Identifier(name) = &type_arg.node_type {
        name.clone()
    } else {
        return Err(e.lang_error(&context.path, "eval", "enum_get_payload: type argument must be a type name"));
    };
    // Check if payload type is an enum (for nested enums)
    let is_enum_payload = context.scope_stack.has_enum(&type_name);
    // Get expected type size
    let type_size = context.get_type_size(&type_name)?;
    // After eval_expr, context.temp_enum_payload should contain the payload data
    if let Some(payload) = &context.temp_enum_payload {
        let payload_bytes = &payload.data;
        let out_arg = e.get(3)?;
        if let NodeType::Identifier(out_name) = &out_arg.node_type {
            // For enum payloads, the actual bytes may be less than max type size
            // (e.g., Option.None is just 8 bytes tag, Option.Some(x) is 8 + payload)
            // For struct payloads, bytes should match type size exactly
            let bytes_to_copy = if is_enum_payload {
                // For enums, copy what we have (must have at least 8 bytes for tag)
                if payload_bytes.len() >= 8 {
                    payload_bytes.len()
                } else {
                    return Err(e.lang_error(&context.path, "eval", "enum_get_payload: enum payload too small"));
                }
            } else {
                // For structs/primitives, must have at least type_size bytes
                if payload_bytes.len() >= type_size {
                    type_size
                } else {
                    return Err(e.lang_error(&context.path, "eval", &format!(
                        "enum_get_payload: payload size {} < expected type size {}",
                        payload_bytes.len(), type_size
                    )));
                }
            };
            // Get out variable offset
            let offset = context.scope_stack.lookup_var(out_name)
                .ok_or_else(|| e.lang_error(&context.path, "eval", &format!("Variable '{}' not found", out_name)))?;
            // Copy payload bytes to out variable
            EvalArena::g().set(offset, &payload_bytes[0..bytes_to_copy])?;
            return Ok(EvalResult::new(""));
        }
    }
    Err(e.lang_error(&context.path, "eval", "enum_get_payload: enum has no payload or unsupported payload type"))
}

/// Returns the payload's enum tag as a string (e.g., "TTypeDef.TEnumDef").
/// Used for nested enum pattern matching without extracting the full payload.
/// Args: enum_get_payload_type(enum_expr, VariantName, PayloadType)
/// - VariantName: the variant whose payload we're accessing (e.g., TType)
/// - PayloadType: the type of the payload (e.g., TTypeDef)
/// In interpreter, we just use temp_enum_payload. The extra args are for ccodegen.
pub fn func_enum_get_payload_type(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "enum_get_payload_type", 3, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result);
    }
    // Get payload type from third argument (for validation)
    let type_arg = e.get(3)?;
    let expected_type_name = if let NodeType::Identifier(name) = &type_arg.node_type {
        name.clone()
    } else {
        return Err(e.lang_error(&context.path, "eval", "enum_get_payload_type: type argument must be a type name"));
    };
    // After eval_expr, context.temp_enum_payload should contain the payload data
    if let Some(payload) = &context.temp_enum_payload {
        let payload_bytes = &payload.data;
        // Check if payload type is an enum
        if let ValueType::TCustom(type_name) = &payload.value_type {
            // Verify payload type matches expected
            if type_name != &expected_type_name {
                return Err(e.lang_error(&context.path, "eval", &format!(
                    "enum_get_payload_type: expected payload type '{}', got '{}'",
                    expected_type_name, type_name
                )));
            }
            if let Some(enum_def) = context.scope_stack.lookup_enum(type_name) {
                // Read the first 8 bytes as the enum tag
                if payload_bytes.len() >= 8 {
                    let tag_bytes: [u8; 8] = payload_bytes[0..8].try_into().unwrap();
                    let tag = i64::from_le_bytes(tag_bytes);
                    // Look up variant name from tag position
                    let variant_name = Context::variant_pos_to_str(&enum_def, tag, &context.path, e)?;
                    return Ok(EvalResult::new(&format!("{}.{}", type_name, variant_name)));
                }
            }
        }
    }
    // No payload or not an enum payload - return empty string
    Ok(EvalResult::new(""))
}

pub fn func_u8_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "u8_to_i64", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid input for 'u8_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

pub fn func_i64_to_u8(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "i64_to_u8", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

pub fn func_u8_add(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "U8_add", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_add': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_add': {}", err)))?;
    // Wrapping add
    let result = a.wrapping_add(b);
    Ok(EvalResult::new(&result.to_string()))
}

pub fn func_u8_sub(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "U8_sub", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_sub': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_sub': {}", err)))?;
    // Wrapping sub
    let result = a.wrapping_sub(b);
    Ok(EvalResult::new(&result.to_string()))
}

pub fn func_u8_mul(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "U8_mul", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_mul': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_mul': {}", err)))?;
    // Wrapping mul
    let result = a.wrapping_mul(b);
    Ok(EvalResult::new(&result.to_string()))
}

pub fn func_u8_div(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "U8_div", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_div': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_div': {}", err)))?;
    // Division returns 0 on divide by zero
    let result = if b == 0 { 0 } else { a / b };
    Ok(EvalResult::new(&result.to_string()))
}

pub fn func_u8_mod(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "U8_mod", 2, false)?;
    let a_result = eval_expr(context, e.get(1)?)?;
    if a_result.is_throw {
        return Ok(a_result);
    }
    let b_result = eval_expr(context, e.get(2)?)?;
    if b_result.is_throw {
        return Ok(b_result);
    }
    let a = a_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_mod': {}", err)))?;
    let b = b_result.value.parse::<u8>()
        .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid U8 for 'U8_mod': {}", err)))?;
    // Modulo returns 0 on divide by zero
    let result = if b == 0 { 0 } else { a % b };
    Ok(EvalResult::new(&result.to_string()))
}

// ---------- core procs implementations for eval

// Note: If this prints an Array instead of a Str, check that single_print is declared
// as `ext_proc(s: Str)` not `ext_proc(args: ..Str)` in core.til. Variadic wrapping
// bypasses validate_arg_count by passing args as a single Array. (Bug #30)
pub fn proc_single_print(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "single_print", 1, true)?;

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    print!("{}", result.value);
    Ok(EvalResult::new(""))
}

pub fn proc_print_flush(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "print_flush", 0, true)?;

    io::stdout().flush().map_err(|err| e.lang_error(&context.path, "eval", &format!("Failed to flush stdout: {}", err)))?;
    Ok(EvalResult::new(""))
}

// Bug #98: Now throws ReadError instead of panicking
pub fn proc_input_read_line(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "input_read_line", 1, true)?;

    let prompt_result = eval_expr(context, e.get(1)?)?;
    if prompt_result.is_throw {
        return Ok(prompt_result);
    }
    let prompt = prompt_result.value;

    // Print prompt
    if !prompt.is_empty() {
        print!("{}", prompt);
        io::stdout().flush().ok();
    }

    let mut line = String::new();
    match io::stdin().read_line(&mut line) {
        Ok(_) => Ok(EvalResult::new(&line)),
        Err(error) => Ok(EvalResult::new_throw(&format!("Failed to read from stdin: {}", error), ValueType::TCustom("ReadError".to_string()))),
    }
}

// Bug #98: Now throws ReadError instead of Str
pub fn proc_readfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "readfile", 1, true)?;

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let path = result.value;

    let source = match fs::read_to_string(&path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => return Ok(EvalResult::new_throw(&format!("File '{}' not found.", path), ValueType::TCustom("ReadError".to_string()))),
            other_error => return Ok(EvalResult::new_throw(&format!("Problem reading file '{}': {}", path, other_error), ValueType::TCustom("ReadError".to_string()))),
        },
    };

    Ok(EvalResult::new(&source))
}

// Bug #98: Now throws WriteError instead of panicking
pub fn proc_writefile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "writefile", 2, true)?;

    let path_result = eval_expr(context, e.get(1)?)?;
    if path_result.is_throw {
        return Ok(path_result);
    }
    let path = path_result.value;

    let contents_result = eval_expr(context, e.get(2)?)?;
    if contents_result.is_throw {
        return Ok(contents_result);
    }
    let contents = contents_result.value;

    match fs::write(&path, &contents) {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error) => Ok(EvalResult::new_throw(&format!("Problem writing file '{}': {}", path, error), ValueType::TCustom("WriteError".to_string()))),
    }
}

// WARNING: run_cmd executes shell commands.
// In mode safe_script, only whitelisted commands are allowed (configurable).
// In other modes, arbitrary commands can be executed - use with caution.
// Returns exit code as I64, output is written to mut output_str arg
pub fn proc_run_cmd(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    // run_cmd(mut output_str, args...) - runs a command with arguments
    // First arg is mut output string, second is command, remaining are args
    // Returns exit code as I64
    if e.params.len() < 3 {
        return Err(e.error(&context.path, "eval", "run_cmd requires at least 2 arguments (mut output_str, command)"));
    }

    // Get output variable name (must be identifier for mut assignment)
    let output_var = e.get(1)?;

    let cmd_result = eval_expr(context, e.get(2)?)?;
    if cmd_result.is_throw {
        return Ok(cmd_result);
    }
    let cmd = cmd_result.value;

    // Check command against whitelists
    if context.mode_def.name == "safe_script" {
        if !SAFE_COMMANDS.contains(&cmd.as_str()) {
            return Err(e.error(&context.path, "eval", &format!("Command '{}' not in safe_script whitelist: {:?}", cmd, SAFE_COMMANDS)));
        }
    } else {
        if !ALLOWED_COMMANDS.contains(&cmd.as_str()) {
            return Err(e.error(&context.path, "eval", &format!("Command '{}' not in allowed whitelist: {:?}", cmd, ALLOWED_COMMANDS)));
        }
    }

    let mut args: Vec<String> = Vec::new();
    for i in 3..e.params.len() {
        let arg_result = eval_expr(context, e.get(i)?)?;
        if arg_result.is_throw {
            return Ok(arg_result);
        }
        args.push(arg_result.value);
    }

    let output = Command::new(&cmd)
        .args(&args)
        .output();

    match output {
        Ok(out) => {
            let stdout = String::from_utf8_lossy(&out.stdout).to_string();
            let code = out.status.code().unwrap_or(-1);

            // Assign stdout to mut output variable
            let var_name = match &output_var.node_type {
                NodeType::Identifier(name) => name.clone(),
                _ => return Err(e.error(&context.path, "eval", "run_cmd first argument must be an identifier")),
            };
            EvalArena::insert_primitive(context, &var_name, &ValueType::TCustom("Str".to_string()), &stdout, e)?;

            Ok(EvalResult::new(&code.to_string()))
        },
        Err(err) => {
            Err(e.error(&context.path, "eval", &format!("Failed to run command '{}': {}", cmd, err)))
        }
    }
}

// ---------- Process spawning functions

// Singleton for tracking spawned processes
pub struct SpawnedProcesses {
    processes: HashMap<i64, Child>,
}

impl SpawnedProcesses {
    #[allow(static_mut_refs)]
    pub fn g() -> &'static mut SpawnedProcesses {
        unsafe {
            static mut INSTANCE: Option<SpawnedProcesses> = None;
            INSTANCE.get_or_insert_with(|| SpawnedProcesses {
                processes: HashMap::new(),
            })
        }
    }
}

// spawn_cmd: Spawn a command in the background, returns PID
pub fn proc_spawn_cmd(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "spawn_cmd", 1, true)?;

    let cmd = eval_or_throw!(context, e.get(1)?);

    #[cfg(windows)]
    let child_result = Command::new("cmd").args(&["/C", &cmd]).spawn();
    #[cfg(not(windows))]
    let child_result = Command::new("sh").args(&["-c", &cmd]).spawn();

    match child_result {
        Ok(child) => {
            let pid = child.id() as i64;
            SpawnedProcesses::g().processes.insert(pid, child);
            Ok(EvalResult::new(&pid.to_string()))
        }
        Err(err) => {
            Ok(EvalResult::new_throw(&format!("Failed to spawn command '{}': {}", cmd, err), ValueType::TCustom("SpawnError".to_string())))
        }
    }
}

// check_cmd_status: Check if a spawned process has finished (non-blocking)
// Returns -1 if still running, exit code if finished
pub fn proc_check_cmd_status(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "check_cmd_status", 1, true)?;

    let pid_str = eval_or_throw!(context, e.get(1)?);
    let pid = pid_str.parse::<i64>().map_err(|err| {
        e.lang_error(&context.path, "eval", &format!("Invalid PID for check_cmd_status: {}", err))
    })?;

    if let Some(child) = SpawnedProcesses::g().processes.get_mut(&pid) {
        match child.try_wait() {
            Ok(Some(status)) => {
                // Process finished, remove from map and return exit code
                SpawnedProcesses::g().processes.remove(&pid);
                Ok(EvalResult::new(&status.code().unwrap_or(-1).to_string()))
            }
            Ok(None) => {
                // Still running
                Ok(EvalResult::new("-1"))
            }
            Err(_) => {
                // Error checking status, treat as still running
                Ok(EvalResult::new("-1"))
            }
        }
    } else {
        // Unknown PID, return -1
        Ok(EvalResult::new("-1"))
    }
}

// sleep: Sleep for specified milliseconds
pub fn proc_sleep(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "sleep", 1, true)?;

    let ms_str = eval_or_throw!(context, e.get(1)?);
    let ms = ms_str.parse::<u64>().map_err(|err| {
        e.lang_error(&context.path, "eval", &format!("Invalid milliseconds for sleep: {}", err))
    })?;

    thread::sleep(Duration::from_millis(ms));
    Ok(EvalResult::new(""))
}

// get_thread_count: Returns number of hardware threads (logical CPUs)
pub fn proc_get_thread_count(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "get_thread_count", 0, true)?;

    let count = thread::available_parallelism()
        .map(|n| n.get() as i64)
        .unwrap_or(1);

    Ok(EvalResult::new(&count.to_string()))
}

// file_mtime: Returns file modification time as Unix timestamp, -1 if not exists
pub fn func_file_mtime(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "file_mtime", 1, false)?;

    let path = eval_or_throw!(context, e.get(1)?);

    match fs::metadata(&path) {
        Ok(metadata) => {
            match metadata.modified() {
                Ok(time) => {
                    let duration = time.duration_since(std::time::UNIX_EPOCH).unwrap_or_default();
                    Ok(EvalResult::new(&(duration.as_secs() as i64).to_string()))
                }
                Err(_) => Ok(EvalResult::new("-1")),
            }
        }
        Err(_) => Ok(EvalResult::new("-1")),
    }
}

// Bug #98: Now throws IOError instead of returning empty string
pub fn func_list_dir_raw(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "list_dir_raw", 1, false)?;

    let path = eval_or_throw!(context, e.get(1)?);

    match fs::read_dir(&path) {
        Ok(entries) => {
            let names: Vec<String> = entries
                .filter_map(|e| e.ok())
                .map(|e| e.file_name().to_string_lossy().into_owned())
                .filter(|name| !name.starts_with('.'))
                .collect();
            Ok(EvalResult::new(&names.join("\n")))
        }
        Err(error) => Ok(EvalResult::new_throw(&format!("Could not open directory '{}': {}", path, error), ValueType::TCustom("IOError".to_string()))),
    }
}

// fs_parent_dir: Get parent directory of a path
pub fn func_fs_parent_dir(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "fs_parent_dir", 1, false)?;

    let path = eval_or_throw!(context, e.get(1)?);

    match std::path::Path::new(&path).parent() {
        Some(parent) => Ok(EvalResult::new(parent.to_string_lossy().as_ref())),
        None => Ok(EvalResult::new("")),
    }
}

// fs_mkdir_p: Create directory and all parent directories
pub fn proc_fs_mkdir_p(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "fs_mkdir_p", 1, true)?;

    let path = eval_or_throw!(context, e.get(1)?);

    match std::fs::create_dir_all(&path) {
        Ok(_) => Ok(EvalResult::new("0")),
        Err(_) => Ok(EvalResult::new("-1")),
    }
}

// ---------- Introspection functions

pub fn func_has_const(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "has_const", 2, false)?;

    let type_name = eval_or_throw!(context, e.get(1)?);
    let const_name = eval_or_throw!(context, e.get(2)?);

    // Check if type exists in struct_defs
    if let Some(struct_def) = context.scope_stack.lookup_struct(&type_name) {
        // Check for immutable field (!is_mut)
        if let Some(decl) = struct_def.get_member(&const_name) {
            if !decl.is_mut {
                return Ok(EvalResult::new("true"));
            }
        }
    }

    Ok(EvalResult::new("false"))
}

pub fn func_has_field(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "has_field", 2, false)?;

    let type_name = eval_or_throw!(context, e.get(1)?);
    let field_name = eval_or_throw!(context, e.get(2)?);

    // Check if type exists in struct_defs
    if let Some(struct_def) = context.scope_stack.lookup_struct(&type_name) {
        // Check for mutable field (is_mut)
        if let Some(decl) = struct_def.get_member(&field_name) {
            if decl.is_mut {
                return Ok(EvalResult::new("true"));
            }
        }
    }

    Ok(EvalResult::new("false"))
}

pub fn func_exit(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "exit", 1, false)?;

    let e_exit_code = e.get(1)?;
    let exit_code = match &e_exit_code.node_type {
        NodeType::LLiteral(Literal::Number(my_li64)) => my_li64.parse::<i64>()
            .map_err(|err| e.lang_error(&context.path, "eval", &format!("Invalid number literal '{}': {}", *my_li64, err)))?,
        node_type => return Err(e.lang_error(&context.path, "eval", &format!("calling core proc 'exit', but found {:?} instead of literal i64 exit code.", node_type))),
    };

    std::process::exit(exit_code as i32);
}
