// External/Core functions for TIL interpreter
// This module contains all built-in core functions and procedures.

use crate::rs::init::Context;
use crate::rs::parser::{
    Expr, NodeType, Literal, ValueType,
    get_combined_name,
};
use crate::rs::interpreter::{Arena, EvalResult, eval_expr, string_from_context};
use std::io;
use std::io::{ErrorKind, Write};
use std::fs;
use crate::{main_run, run_file, run_file_with_context};

// ---------- Helper functions

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
fn validate_arg_count(path: &str, e: &Expr, func_name: &str, expected: usize, is_proc: bool) -> Result<(), String> {
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

// ---------- Core functions - called from interpreter.rs dispatcher

pub fn func_loc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "loc", 0, false)?;
    let file = context.path.clone();
    let line = e.line;
    let col = e.col;

    Ok(EvalResult::new(&format!("{}:{}:{}:", file, line, col)))
}

pub fn func___file(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "__file", 0, false)?;
    Ok(EvalResult::new(&context.path.clone()))
}

pub fn func___line(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "__line", 0, false)?;
    Ok(EvalResult::new(&(e.line as i64).to_string()))
}

pub fn func___col(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "__col", 0, false)?;
    Ok(EvalResult::new(&(e.col as i64).to_string()))
}

// ---------- eval memory

pub fn func_malloc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "malloc", 1, false)?;

    let size_str = eval_or_throw!(context, e.get(1)?);
    let size = size_str.parse::<usize>().map_err(|err| {
        e.lang_error(&context.path, "eval", &format!("Invalid size for 'malloc': {}", err))
    })?;
    let offset = Arena::g().memory.len(); // take *current* end of arena

    if size > 0 {
        Arena::g().memory.resize(offset + size, 0); // extend safely
    }

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

    if dest + size > Arena::g().memory.len() {
        return Err(e.error(&context.path, "eval", &format!(
            "memset out of bounds: dest={} size={} arena_len={}",
            dest, size, Arena::g().memory.len()
        )));
    }

    for i in 0..size {
        Arena::g().memory[dest + i] = value;
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

    if dest + size > Arena::g().memory.len() || src + size > Arena::g().memory.len() {
        return Err(e.error(&context.path, "eval", &format!("memcpy out of bounds: src={} dest={} size={} arena_len={}",
                                            src, dest, size, Arena::g().memory.len())));
    }

    for i in 0..size {
        Arena::g().memory[dest + i] = Arena::g().memory[src + i];
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

    if ptr1 + size > Arena::g().memory.len() || ptr2 + size > Arena::g().memory.len() {
        return Err(e.error(&context.path, "eval", &format!("memcmp out of bounds: ptr1={} ptr2={} size={} arena_len={}",
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

pub fn func_to_ptr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "to_ptr", 1, false)?;

    let identifier_expr = e.get(1)?;
    let combined_name = get_combined_name(&context.path, identifier_expr)?;
    match context.scope_stack.lookup_var(&combined_name) {
        Some(addr) => Ok(EvalResult::new(&format!("{}", addr))),
        None => Err(e.lang_error(&context.path, "eval", &format!("calling core func to_ptr, but '{}' is not a known identifier.", combined_name))),
    }
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

            match Arena::get_type_size(context, &actual_type_name) {
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
    Ok(EvalResult::new(&(a + b).to_string()))
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
    Ok(EvalResult::new(&(a - b).to_string()))
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
    Ok(EvalResult::new(&(a * b).to_string()))
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

// ---------- core procs implementations for eval

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

pub fn proc_input_read_line(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "input_read_line", 1, true)?;

    let first_param = e.get(1)?;
    let read_line_error_msg = match &first_param.node_type {
        NodeType::LLiteral(Literal::Str(error_msg_)) => error_msg_.clone(),
        _ => return Err(e.lang_error(&context.path, "eval", &format!("input_read_line() expects a literal string error message. Found '{:?}' instead.",
                                                      first_param.node_type))),
    };

    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .map_err(|_| e.lang_error(&context.path, "eval", &read_line_error_msg))?;

    Ok(EvalResult::new(&line))
}

pub fn proc_eval_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "eval_to_str", 1, true)?;

    let path = "eval".to_string(); // Placeholder path
    let source_expr = eval_expr(context, e.get(1)?)?;
    if source_expr.is_throw {
        return Ok(source_expr); // Propagate throw
    }

    let str_source = format!("mode script; {}", source_expr.value);
    return main_run(false, false, context, &path, str_source, Vec::new())
}

pub fn proc_runfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() < 2 {
        return Err(e.lang_error(&context.path, "eval", "Core proc 'runfile' expects at least 1 parameter"));
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
        Err(error_string) => Err(e.error(&context.path, "eval", &format!("While running file {path}\n{error_string}"))),
    }
}

// Convert dot-based import path to OS-specific file path
// Example: "src.core.std" -> "src/core/std.til" (Unix) or "src\core\std.til" (Windows)
fn import_path_to_file_path(import_path: &str) -> String {
    let file_path = import_path.replace(".", std::path::MAIN_SEPARATOR_STR);
    format!("{}.til", file_path)
}

pub fn proc_import(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(&context.path, e, "import", 1, true)?;

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    let original_path = context.path.clone();
    let path = import_path_to_file_path(&result.value);

    // If imported values already initialized, use the cache (Phase 2)
    match context.imports_values_done.get(&path) {
        Some(import_result) => return import_result.clone(),
        None => match context.imports_wip.contains(&path) {
            true => {
                // TODO do a more detailed message with backtraces or storing a graph of the dependencies or something
                return Err(e.error(&context.path, "eval", &format!("While trying to import {} from {}: Circular import dependency",
                                                    path, original_path)))
            },
            false => {
                if !context.imports_wip.insert(path.clone()) {
                    return Err(e.lang_error(&context.path, "eval", &format!("While trying to import {} from {}: Can't insert in imports_wip",
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
            // Prepend the imported file path to the error if not already present
            let error_with_path = if error_string.starts_with(&path) {
                error_string
            } else {
                format!("{}:{}", path, error_string)
            };
            return Err(e.error(&context.path, "eval", &format!("While trying to import {} from {}:\n{}",
                                                path, original_path, error_with_path)))
        },
    };

    context.imports_wip.remove(&path);
    context.imports_values_done.insert(path, result.clone());
    context.path = original_path;
    return result
}

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
            ErrorKind::NotFound => return Err(e.error(&context.path, "eval", &format!("File '{}' not found.", path))),
            other_error => return Err(e.error(&context.path, "eval", &format!("Problem reading file '{}': {}", path, other_error))),
        },
    };

    Ok(EvalResult::new(&source))
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
