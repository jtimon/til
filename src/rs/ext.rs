// External/Core functions for TIL interpreter
// This module contains all built-in core functions and procedures.

use crate::rs::init::Context;
use crate::rs::parser::{
    Expr, NodeType, Literal, ValueType, TTypeDef,
    value_type_to_str, get_combined_name,
};
use crate::rs::interpreter::{Arena, EvalResult, eval_expr};
use std::io;
use std::io::{ErrorKind, Write};
use std::fs;
use crate::{main_run, run_file, run_file_with_context};

// ---------- Helper functions

/// Validates that a function/procedure call has the expected number of arguments.
/// The e.params.len() includes the function name as the first parameter, so we subtract 1.
fn validate_arg_count(e: &Expr, func_name: &str, expected: usize, is_proc: bool) -> Result<(), String> {
    let actual = e.params.len() - 1; // First param is function name
    if actual != expected {
        let func_type = if is_proc { "proc" } else { "func" };
        let plural = if expected == 1 { "" } else { "s" };
        return Err(e.lang_error("eval", &format!(
            "Core {} '{}' takes exactly {} argument{}",
            func_type, func_name, expected, plural
        )));
    }
    Ok(())
}

// ---------- Core functions - called from interpreter.rs dispatcher

pub fn func_loc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "loc", 0, false)?;
    let file = context.path.clone();
    let line = e.line;
    let col = e.col;

    Ok(EvalResult::new(&format!("{}:{}:{}:", file, line, col)))
}

// ---------- eval memory

pub fn func_malloc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "malloc", 1, false)?;

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

pub fn func_free(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "free", 1, false)?;

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let _ptr_str = result.value;
    // REM: Free does nothing in arena model (for now).

    return Ok(EvalResult::new(""))
}

pub fn func_memset(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "memset", 3, false)?;

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

pub fn func_memcpy(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "memcpy", 3, false)?;

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

pub fn func_memcmp(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "memcmp", 3, false)?;

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

pub fn func_to_ptr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "to_ptr", 1, false)?;

    let identifier_expr = e.get(1)?;
    let combined_name = get_combined_name(identifier_expr)?;
    match context.arena_index.get(&combined_name) {
        Some(addr) => Ok(EvalResult::new(&format!("{}", addr))),
        None => Err(e.lang_error("eval", &format!("calling core func to_ptr, but '{}' is not a known identifier.", combined_name))),
    }
}

pub fn func_size_of(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "size_of", 1, false)?;

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

pub fn func_type_as_str(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "type_as_str", 1, false)?;

    let type_expr = e.get(1)?;
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            Ok(EvalResult::new(&format!("{}", type_name)))
        },
        node_type => Err(e.lang_error("eval", &format!("calling core func type_as_str, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

pub fn func_lt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "lt", 2, false)?;
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

pub fn func_gt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "gt", 2, false)?;
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

pub fn func_add(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "add", 2, false)?;
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

pub fn func_sub(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "sub", 2, false)?;
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

pub fn func_mul(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "mul", 2, false)?;
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

pub fn func_div(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "div", 2, false)?;
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

pub fn func_mod(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "mod", 2, false)?;
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

pub fn func_str_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "str_to_i64", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid input for 'str_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

pub fn func_i64_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "i64_to_str", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

pub fn func_enum_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "enum_to_str", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}


pub fn proc_enum_extract_payload(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "rsonly_enum_extract_payload", 2, true)?;

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

pub fn func_u8_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "u8_to_i64", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid input for 'u8_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

pub fn func_i64_to_u8(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "i64_to_u8", 1, false)?;
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

// ---------- core procs implementations for eval

pub fn proc_single_print(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "single_print", 1, true)?;

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    print!("{}", result.value);
    Ok(EvalResult::new(""))
}

pub fn proc_print_flush(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "print_flush", 0, true)?;

    io::stdout().flush().map_err(|err| e.lang_error("eval", &format!("Failed to flush stdout: {}", err)))?;
    Ok(EvalResult::new(""))
}

pub fn proc_input_read_line(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "input_read_line", 1, true)?;

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

pub fn proc_eval_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "eval_to_str", 1, true)?;

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

pub fn proc_import(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "import", 1, true)?;

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

pub fn proc_readfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "readfile", 1, true)?;

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

pub fn func_exit(e: &Expr) -> Result<EvalResult, String> {
    validate_arg_count(e, "exit", 1, false)?;

    let e_exit_code = e.get(1)?;
    let exit_code = match &e_exit_code.node_type {
        NodeType::LLiteral(Literal::Number(my_li64)) => my_li64.parse::<i64>()
            .map_err(|err| e.lang_error("eval", &format!("Invalid number literal '{}': {}", *my_li64, err)))?,
        node_type => return Err(e.lang_error("eval", &format!("calling core proc 'exit', but found {:?} instead of literal i64 exit code.", node_type))),
    };

    std::process::exit(exit_code as i32);
}
