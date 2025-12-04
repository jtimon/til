use std::collections::HashMap;
use std::convert::TryInto;
use crate::rs::init::{Context, SymbolInfo, EnumVal, ScopeFrame, ScopeType};
use crate::rs::parser::{Expr, ValueType, TTypeDef, value_type_to_str};

// Arena: Memory management for the TIL interpreter
// Extracted from interpreter.rs to enable incremental translation to TIL.

pub struct Arena {
    pub memory: Vec<u8>,
    pub temp_id_counter: usize,
    pub default_instances: HashMap<String, usize>,  // type name → arena offset of default template
}

/// Result from insert_struct_core containing mappings to be stored
pub struct StructInsertResult {
    pub arena_mappings: Vec<(String, usize)>,
    pub symbols: Vec<(String, SymbolInfo)>,
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
                default_instances: HashMap::new(),
            })
        }
    }

    // === EVAL-PHASE MEMORY OPERATIONS ===
    // These methods manage runtime memory allocation and access
    // They take Context as parameter to access type info and arena_index

    pub fn get_u8(ctx: &Context, id: &str, e: &Expr) -> Result<u8, String> {
        // Try direct lookup first (for base variables)
        let offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
            offset
        } else if id.contains('.') {
            // For field paths, calculate offset dynamically
            ctx.get_field_offset( id).map_err(|err| {
                e.lang_error(&ctx.path, "context", &format!("get_u8: {}", err))
            })?
        } else {
            return Err(e.lang_error(&ctx.path, "context", &format!("u8 not found for id '{}'", id)));
        };

        Arena::g().memory.get(offset).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("Invalid u8 read for id '{}'", id)))
    }

    pub fn get_i64(ctx: &Context, id: &str, e: &Expr) -> Result<i64, String> {
        // Try direct lookup first (for base variables)
        let offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
            offset
        } else if id.contains('.') {
            // For field paths, calculate offset dynamically
            ctx.get_field_offset( id).map_err(|err| {
                e.lang_error(&ctx.path, "context", &format!("get_i64: {}", err))
            })?
        } else {
            return Err(e.lang_error(&ctx.path, "context", &format!("i64 not found for id '{}'", id)));
        };

        match Arena::g().memory[offset..offset + 8].try_into() {
            Ok(bytes) => Ok(i64::from_ne_bytes(bytes)),
            Err(_) => Err(e.lang_error(&ctx.path, "context", &format!("Invalid i64 read for id '{}'", id))),
        }
    }

    /// Core logic for insert_i64 - returns Some(offset) if caller needs to store it, None if already handled
    fn insert_i64_core(ctx: &Context, id: &str, i64_str: &String, e: &Expr) -> Result<Option<usize>, String> {
        let v = i64_str.parse::<i64>()
            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("Invalid i64 literal '{}'", i64_str)))?;
        let bytes = v.to_ne_bytes();

        let is_instance_field = if id.contains('.') {
            // Check if base is an instance variable (not a struct type)
            let parts: Vec<&str> = id.split('.').collect();
            let base = parts[0];
            // If base is in symbols and is NOT a struct type, it's an instance field access
            ctx.scope_stack.lookup_symbol(base).map_or(false, |sym| {
                match &sym.value_type {
                    ValueType::TType(_) => false,
                    _ => true
                }
            })
        } else {
            false
        };

        if is_instance_field {
            // For instance field paths, calculate offset dynamically
            let offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
                // Pre-registered field (old path)
                offset
            } else {
                // Calculate offset from struct definition
                ctx.get_field_offset( id).map_err(|err| {
                    e.lang_error(&ctx.path, "context", &format!("insert_i64: {}", err))
                })?
            };

            // Ensure arena has enough space
            let required_len = offset + 8;
            if Arena::g().memory.len() < required_len {
                Arena::g().memory.resize(required_len, 0);
            }

            Arena::g().memory[offset..offset + 8].copy_from_slice(&bytes);
            return Ok(None)
        }

        // For non-instance fields (including struct constants like Vec.INIT_CAP), create new entry
        let offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(&bytes);
        Ok(Some(offset))
    }

    pub fn insert_i64(ctx: &mut Context, id: &str, i64_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(offset) = Self::insert_i64_core(ctx, id, i64_str, e)? {
            ctx.scope_stack.insert_var(id.to_string(), offset);
        }
        Ok(())
    }

    pub fn insert_i64_into_frame(ctx: &Context, frame: &mut ScopeFrame, id: &str, i64_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(offset) = Self::insert_i64_core(ctx, id, i64_str, e)? {
            frame.arena_index.insert(id.to_string(), offset);
        }
        Ok(())
    }

    // REM: Can't be moved to TIL until compilation - needs way to calculate size from TIL declarations
    fn insert_u8_core(ctx: &Context, id: &str, u8_str: &String, e: &Expr) -> Result<Option<usize>, String> {
        let v = u8_str.parse::<u8>()
            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("Invalid u8 literal '{}'", u8_str)))?;

        let is_instance_field = if id.contains('.') {
            let parts: Vec<&str> = id.split('.').collect();
            let base = parts[0];
            ctx.scope_stack.lookup_symbol(base).map_or(false, |sym| {
                match &sym.value_type {
                    ValueType::TType(_) => false,
                    _ => true
                }
            })
        } else {
            false
        };

        if is_instance_field {
            // For instance field paths, calculate offset dynamically
            let offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
                // Pre-registered field (old path)
                offset
            } else {
                // Calculate offset from struct definition
                ctx.get_field_offset( id).map_err(|err| {
                    e.lang_error(&ctx.path, "context", &format!("insert_u8: {}", err))
                })?
            };
            Arena::g().memory[offset] = v;
            return Ok(None)
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.push(v);
        Ok(Some(offset))
    }

    pub fn insert_u8(ctx: &mut Context, id: &str, u8_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(offset) = Self::insert_u8_core(ctx, id, u8_str, e)? {
            ctx.scope_stack.insert_var(id.to_string(), offset);
        }
        Ok(())
    }

    pub fn insert_u8_into_frame(ctx: &Context, frame: &mut ScopeFrame, id: &str, u8_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(offset) = Self::insert_u8_core(ctx, id, u8_str, e)? {
            frame.arena_index.insert(id.to_string(), offset);
        }
        Ok(())
    }

    // TODO all args should be passed as pointers/references and we wouldn't need this
    pub fn copy_fields(ctx: &mut Context, custom_type_name: &str, src: &str, dest: &str, e: &Expr) -> Result<(), String> {
        let struct_def = ctx.scope_stack.lookup_struct(custom_type_name)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("copy_fields: definition for '{}' not found", custom_type_name)))?;

        let is_mut = ctx.scope_stack.lookup_symbol(dest)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("copy_fields: destination symbol '{}' not found", dest)))?
            .is_mut;

        let dest_base_offset = ctx.scope_stack.lookup_var(dest)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("copy_fields: destination arena offset for '{}' not found", dest)))?;

        let members = struct_def.members.clone();

        let mut current_offset = 0;
        for decl in members {
            if decl.is_mut {
                let field_size = match &decl.value_type {
                    ValueType::TCustom(name) => ctx.get_type_size( name)?,
                    _ => return Err(e.lang_error(&ctx.path, "context", &format!("copy_fields: unsupported field type '{}'", value_type_to_str(&decl.value_type)))),
                };

                let src_key = format!("{}.{}", src, decl.name);
                let dest_key = format!("{}.{}", dest, decl.name);

                // Try to get source offset - first from arena_index, then calculate dynamically
                let src_offset_result = if let Some(offset) = ctx.scope_stack.lookup_var(&src_key) {
                    Some(offset)
                } else {
                    // Calculate offset dynamically from struct definition
                    match ctx.get_field_offset( &src_key) {
                        Ok(offset) => Some(offset),
                        Err(_) => {
                            // Skip if source field doesn't exist (e.g., is_dyn in Array but not in Vec)
                            current_offset += field_size;
                            None
                        }
                    }
                };

                if let Some(src_offset) = src_offset_result {
                    let dest_offset = dest_base_offset + current_offset;

                    ctx.scope_stack.insert_var(dest_key.clone(), dest_offset);
                    ctx.scope_stack.declare_symbol(dest_key.clone(), SymbolInfo {
                        value_type: decl.value_type.clone(),
                        is_mut,
                        is_copy: false,
                        is_own: false,
                    });

                    Arena::g().memory.copy_within(src_offset..src_offset + field_size, dest_offset);

                    if let ValueType::TCustom(type_name) = &decl.value_type {
                        if ctx.scope_stack.lookup_struct(type_name).is_some() {
                            Arena::copy_fields(ctx, type_name, &src_key, &dest_key, e).map_err(|_| {
                                e.lang_error(&ctx.path, "context", &format!("copy_fields: failed to recursively copy field '{}'", dest_key))
                            })?;
                        }
                    }

                    current_offset += field_size;
                }
            }
        }

        Ok(())
    }

    /// Core logic for insert_struct - does all the work but returns mappings instead of inserting them
    pub fn insert_struct_core(ctx: &mut Context, id: &str, custom_type_name: &str, existing_offset: Option<usize>, defaults: &HashMap<String, String>, e: &Expr) -> Result<StructInsertResult, String> {
        let mut result = StructInsertResult {
            arena_mappings: Vec::new(),
            symbols: Vec::new(),
        };

        // Lookup the struct definition
        let struct_def = match ctx.scope_stack.lookup_struct(custom_type_name) {
            Some(struct_def_) => struct_def_.clone(),
            None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: definition for '{}' not found", custom_type_name))),
        };

        // Determine mutability from symbols table
        let is_mut = match ctx.scope_stack.lookup_symbol(id) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: id '{}' for struct '{}' not found in symbols", id, custom_type_name))),
        };

        // Calculate total size (for now no alignment)
        let mut total_size = 0;
        let mut field_offsets = HashMap::new();

        for decl in struct_def.members.iter() {
            if decl.is_mut {
                let field_size = match &decl.value_type {
                    ValueType::TCustom(type_name) => ctx.get_type_size( type_name)?,
                    _ => return Err(e.lang_error(&ctx.path, "context", "insert_struct: Unsupported value type in struct")),
                };

                field_offsets.insert(decl.name.clone(), total_size);
                total_size += field_size;
            }
        }

        // Either use existing offset (for nested structs) or allocate new memory
        let offset = match existing_offset {
            Some(off) => off,
            None => {
                let off = Arena::g().memory.len();
                Arena::g().memory.resize(off + total_size, 0);
                off
            }
        };
        result.arena_mappings.push((id.to_string(), offset));

        // Store each field's default value
        for decl in struct_def.members.iter() {
            if decl.is_mut {
                let field_offset = match field_offsets.get(&decl.name) {
                Some(offset) => offset,
                None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Missing field offset for '{}'", decl.name))),
            };

            let default_value = match defaults.get(&decl.name) {
                Some(v) => v.clone(),
                None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Missing pre-evaluated default for field '{}'", decl.name))),
            };

            match &decl.value_type {
                ValueType::TCustom(type_name) => {
                    if let Some(enum_def) = ctx.scope_stack.lookup_enum(type_name) {
                        let parts: Vec<&str> = default_value.split('.').collect();
                        if parts.len() != 2 || parts[0] != type_name {
                            return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid enum default value '{}' for field '{}'", default_value, decl.name)));
                        }
                        let variant = parts[1];
                        let index = match enum_def.enum_map.keys().position(|v| v == variant) {
                            Some(i) => i as i64,
                            None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Unknown enum variant '{}' for field '{}'", variant, decl.name))),
                        };
                        Arena::g().memory[offset + field_offset..offset + field_offset + 8]
                            .copy_from_slice(&index.to_ne_bytes());
                    } else {
                        match type_name.as_str() {
                            "U8" => {
                                let v = default_value.parse::<u8>().map_err(|_| {
                                    e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid U8 default value '{}' for field '{}'", default_value, decl.name))
                                })?;
                                Arena::g().memory[offset + field_offset] = v;
                            },
                            "I64" => {
                                let v = default_value.parse::<i64>().map_err(|_| {
                                    e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid I64 default value '{}' for field '{}'", default_value, decl.name))
                                })?;
                                Arena::g().memory[offset + field_offset..offset + field_offset + 8]
                                    .copy_from_slice(&v.to_ne_bytes());
                            },
                            _ => {
                                if ctx.scope_stack.lookup_struct(type_name).is_some() {
                                    let combined_name = format!("{}.{}", id, decl.name);
                                    let nested_symbol = SymbolInfo {
                                        value_type: ValueType::TCustom(type_name.clone()),
                                        is_mut: true,
                                        is_copy: false,
                                        is_own: false,
                                    };
                                    // Must declare symbol BEFORE recursive call (needed for is_mut lookup)
                                    ctx.scope_stack.declare_symbol(combined_name.clone(), nested_symbol.clone());
                                    result.symbols.push((combined_name.clone(), nested_symbol));

                                    // Special case: Str field initialization
                                    if type_name == "Str" {
                                        // Register inline offset BEFORE insert_string so it writes to the inline space
                                        let field_arena_offset = offset + field_offset;
                                        result.arena_mappings.push((combined_name.clone(), field_arena_offset));
                                        // Need to temporarily insert for insert_string to work
                                        ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(combined_name.clone(), field_arena_offset);
                                        Arena::insert_string(ctx, &combined_name, &default_value, e)?;
                                    } else {
                                        // Use existing offset for nested struct (inline allocation)
                                        let field_arena_offset = offset + field_offset;
                                        result.arena_mappings.push((combined_name.clone(), field_arena_offset));
                                        // Need to temporarily insert for recursive call to work
                                        ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(combined_name.clone(), field_arena_offset);
                                        // Extract nested defaults (field.subfield -> subfield)
                                        let prefix = format!("{}.", decl.name);
                                        let nested_defaults: HashMap<String, String> = defaults.iter()
                                            .filter_map(|(k, v)| k.strip_prefix(&prefix).map(|rest| (rest.to_string(), v.clone())))
                                            .collect();
                                        let nested_result = Arena::insert_struct_core(ctx, &combined_name, type_name, Some(field_arena_offset), &nested_defaults, e)
                                            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("insert_struct: Failed to initialize nested struct '{}.{}'", id, decl.name)))?;
                                        // Collect nested mappings (but they're already inserted by the temp inserts above)
                                        result.arena_mappings.extend(nested_result.arena_mappings);
                                        result.symbols.extend(nested_result.symbols);
                                    }
                                } else {
                                    return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Unknown field type '{}'", type_name)));
                                }
                            },
                        }
                    }
                },
                _ => {
                    return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Unsupported field value type '{}'", value_type_to_str(&decl.value_type))));
                }
            }

            let combined_name = format!("{}.{}", id, decl.name);
            let field_arena_offset = offset + field_offset;
            result.arena_mappings.push((combined_name.clone(), field_arena_offset));
            result.symbols.push((combined_name, SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut,
                is_copy: false,
                is_own: false,
            }));
            }
        }

        Ok(result)
    }

    /// Generate arena mappings and symbols for a struct without writing bytes.
    /// Used for template-based insertion where bytes are already memcpy'd.
    fn generate_struct_mappings(ctx: &mut Context, id: &str, custom_type_name: &str, base_offset: usize, e: &Expr) -> Result<StructInsertResult, String> {
        let mut result = StructInsertResult {
            arena_mappings: Vec::new(),
            symbols: Vec::new(),
        };

        let struct_def = match ctx.scope_stack.lookup_struct(custom_type_name) {
            Some(def) => def.clone(),
            None => return Err(e.lang_error(&ctx.path, "generate_struct_mappings", &format!("struct '{}' not found", custom_type_name))),
        };

        let is_mut = match ctx.scope_stack.lookup_symbol(id) {
            Some(sym) => sym.is_mut,
            None => return Err(e.lang_error(&ctx.path, "generate_struct_mappings", &format!("symbol '{}' not found", id))),
        };

        // Calculate field offsets (same as insert_struct_core)
        let mut current_offset = 0;
        let mut field_offsets = HashMap::new();
        for decl in struct_def.members.iter() {
            if decl.is_mut {
                let field_size = match &decl.value_type {
                    ValueType::TCustom(type_name) => ctx.get_type_size(type_name)?,
                    _ => return Err(e.lang_error(&ctx.path, "generate_struct_mappings", "Unsupported value type")),
                };
                field_offsets.insert(decl.name.clone(), current_offset);
                current_offset += field_size;
            }
        }

        // Add base struct mapping
        result.arena_mappings.push((id.to_string(), base_offset));

        // Generate mappings for each field
        for decl in struct_def.members.iter() {
            if decl.is_mut {
                let field_rel_offset = field_offsets.get(&decl.name).copied().unwrap_or(0);
                let field_abs_offset = base_offset + field_rel_offset;
                let combined_name = format!("{}.{}", id, decl.name);

                result.arena_mappings.push((combined_name.clone(), field_abs_offset));
                result.symbols.push((combined_name.clone(), SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut,
                    is_copy: false,
                    is_own: false,
                }));

                // Handle nested structs recursively
                if let ValueType::TCustom(type_name) = &decl.value_type {
                    if type_name != "U8" && type_name != "I64" {
                        if ctx.scope_stack.lookup_struct(type_name).is_some() {
                            // Declare nested symbol first
                            ctx.scope_stack.declare_symbol(combined_name.clone(), SymbolInfo {
                                value_type: ValueType::TCustom(type_name.clone()),
                                is_mut: true,
                                is_copy: false,
                                is_own: false,
                            });
                            let nested = Arena::generate_struct_mappings(ctx, &combined_name, type_name, field_abs_offset, e)?;
                            result.arena_mappings.extend(nested.arena_mappings);
                            result.symbols.extend(nested.symbols);
                        }
                    }
                }
            }
        }

        Ok(result)
    }

    /// Insert a struct by copying from a cached template.
    /// Much faster than insert_struct_core for subsequent instances of the same type.
    pub fn insert_struct_from_template(ctx: &mut Context, id: &str, custom_type_name: &str, template_offset: usize, e: &Expr) -> Result<(), String> {
        // Get struct size
        let struct_size = ctx.get_type_size(custom_type_name)?;

        // Allocate new memory
        let new_offset = Arena::g().memory.len();
        Arena::g().memory.resize(new_offset + struct_size, 0);

        // memcpy from template
        let arena = Arena::g();
        for i in 0..struct_size {
            arena.memory[new_offset + i] = arena.memory[template_offset + i];
        }

        // Generate and apply mappings
        let result = Arena::generate_struct_mappings(ctx, id, custom_type_name, new_offset, e)?;
        for (name, offset) in result.arena_mappings {
            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(name, offset);
        }
        for (name, symbol) in result.symbols {
            ctx.scope_stack.declare_symbol(name, symbol);
        }

        Ok(())
    }

    /// Insert a struct from template into a specific frame (for function parameters).
    pub fn insert_struct_from_template_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, custom_type_name: &str, template_offset: usize, e: &Expr) -> Result<(), String> {
        // Get struct size
        let struct_size = ctx.get_type_size(custom_type_name)?;

        // Allocate new memory
        let new_offset = Arena::g().memory.len();
        Arena::g().memory.resize(new_offset + struct_size, 0);

        // memcpy from template
        let arena = Arena::g();
        for i in 0..struct_size {
            arena.memory[new_offset + i] = arena.memory[template_offset + i];
        }

        // Temporarily push frame for generate_struct_mappings
        let empty_frame = ScopeFrame {
            arena_index: std::collections::HashMap::new(),
            symbols: std::collections::HashMap::new(),
            funcs: std::collections::HashMap::new(),
            enums: std::collections::HashMap::new(),
            structs: std::collections::HashMap::new(),
            scope_type: ScopeType::Function,
        };
        let taken_frame = std::mem::replace(frame, empty_frame);
        ctx.scope_stack.frames.push(taken_frame);

        let result = Arena::generate_struct_mappings(ctx, id, custom_type_name, new_offset, e);

        // Pop frame back
        *frame = ctx.scope_stack.frames.pop().unwrap();

        let result = result?;
        for (name, offset) in result.arena_mappings {
            frame.arena_index.insert(name, offset);
        }
        for (name, symbol) in result.symbols {
            frame.symbols.insert(name, symbol);
        }

        Ok(())
    }

    pub fn insert_struct(ctx: &mut Context, id: &str, custom_type_name: &str, defaults: &HashMap<String, String>, e: &Expr) -> Result<(), String> {
        let result = Arena::insert_struct_core(ctx, id, custom_type_name, None, defaults, e)?;
        for (name, offset) in result.arena_mappings {
            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(name, offset);
        }
        for (name, symbol) in result.symbols {
            ctx.scope_stack.declare_symbol(name, symbol);
        }
        Ok(())
    }

    pub fn insert_struct_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, custom_type_name: &str, defaults: &HashMap<String, String>, e: &Expr) -> Result<(), String> {
        // Temporarily push frame so symbol lookups work in core function
        let empty_frame = ScopeFrame {
            arena_index: std::collections::HashMap::new(),
            symbols: std::collections::HashMap::new(),
            funcs: std::collections::HashMap::new(),
            enums: std::collections::HashMap::new(),
            structs: std::collections::HashMap::new(),
            scope_type: ScopeType::Function,
        };
        let taken_frame = std::mem::replace(frame, empty_frame);
        ctx.scope_stack.frames.push(taken_frame);

        let result = Arena::insert_struct_core(ctx, id, custom_type_name, None, defaults, e);

        // Pop frame back
        *frame = ctx.scope_stack.frames.pop().unwrap();

        // Now apply results to the frame
        let result = result?;
        for (name, offset) in result.arena_mappings {
            frame.arena_index.insert(name, offset);
        }
        for (name, symbol) in result.symbols {
            frame.symbols.insert(name, symbol);
        }
        Ok(())
    }

    /// Core logic for insert_string - returns Some((string_offset_bytes, len_bytes)) if caller needs to create struct, None if already handled
    fn insert_string_core(ctx: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<Option<([u8; 8], [u8; 8])>, String> {
        let is_field = if id.contains('.') {
            let parts: Vec<&str> = id.split('.').collect();
            let base = parts[0];
            ctx.scope_stack.lookup_symbol(base).map_or(false, |sym| {
                match &sym.value_type {
                    ValueType::TType(_) => false,
                    _ => true
                }
            })
        } else {
            false
        };

        // Allocate string data
        let string_offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(value_str.as_bytes());
        Arena::g().memory.push(0); // null terminator
        let string_offset_bytes = (string_offset as i64).to_ne_bytes();
        let len_bytes = (value_str.len() as i64).to_ne_bytes();

        if is_field {
            if let Some(base_offset) = ctx.scope_stack.lookup_var(id) {
                if let Some(str_def) = ctx.scope_stack.lookup_struct("Str") {
                    let members = str_def.members.clone();
                    let mut current_offset = 0;

                    for decl in members.iter() {
                        if decl.is_mut {
                            let type_size = ctx.get_type_size( &value_type_to_str(&decl.value_type))?;
                            let absolute_offset = base_offset + current_offset;
                            let target_slice = &mut Arena::g().memory[absolute_offset..absolute_offset + type_size];

                            if decl.name == "c_string" {
                                target_slice.copy_from_slice(&string_offset_bytes);
                            } else if decl.name == "cap" {
                                target_slice.copy_from_slice(&len_bytes);
                            }

                            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(format!("{}.{}", id, decl.name), absolute_offset);
                            current_offset += type_size;
                        }
                    }
                    return Ok(None)
                }
                return Err(e.lang_error(&ctx.path, "context", "ERROR: 'Str' struct definition not found"))
            }

            // Not yet inserted — insert fresh inlined Str
            if let Some(str_def) = ctx.scope_stack.lookup_struct("Str") {
                let members = str_def.members.clone();
                let struct_offset = Arena::g().memory.len();
                let mut current_offset = 0;

                for decl in members.iter() {
                    if decl.is_mut {
                        let type_size = ctx.get_type_size( &value_type_to_str(&decl.value_type))?;
                        if Arena::g().memory.len() < struct_offset + current_offset + type_size {
                            Arena::g().memory.resize(struct_offset + current_offset + type_size, 0);
                        }

                        let field_slice = &mut Arena::g().memory[struct_offset + current_offset..struct_offset + current_offset + type_size];
                        if decl.name == "c_string" {
                            field_slice.copy_from_slice(&string_offset_bytes);
                        } else if decl.name == "cap" {
                            field_slice.copy_from_slice(&len_bytes);
                        }

                        ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(format!("{}.{}", id, decl.name), struct_offset + current_offset);
                        current_offset += type_size;
                    }
                }

                ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(id.to_string(), struct_offset);
                return Ok(None)
            }
            return Err(e.lang_error(&ctx.path, "context", "'Str' struct definition not found"))
        }

        Ok(Some((string_offset_bytes, len_bytes)))
    }

    pub fn insert_string(ctx: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        if let Some((string_offset_bytes, len_bytes)) = Self::insert_string_core(ctx, id, value_str, e)? {
            // Create Str struct from template
            let template_offset = Arena::g().default_instances.get("Str")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string", "Str template not found - ensure str.til is imported"))?;
            Arena::insert_struct_from_template(ctx, id, "Str", template_offset, e)?;
            let c_string_offset = ctx.scope_stack.lookup_var(&format!("{}.c_string", id))
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string: missing '{}.c_string'", id)))?;
            let cap_offset = ctx.scope_stack.lookup_var(&format!("{}.cap", id))
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string: missing '{}.cap'", id)))?;
            Arena::g().memory[c_string_offset..c_string_offset + 8].copy_from_slice(&string_offset_bytes);
            Arena::g().memory[cap_offset..cap_offset + 8].copy_from_slice(&len_bytes);
        }
        Ok(())
    }

    pub fn insert_string_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        if let Some((string_offset_bytes, len_bytes)) = Self::insert_string_core(ctx, id, value_str, e)? {
            // Create Str struct from template
            let template_offset = Arena::g().default_instances.get("Str")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string_into_frame", "Str template not found - ensure str.til is imported"))?;
            Arena::insert_struct_from_template_into_frame(ctx, frame, id, "Str", template_offset, e)?;
            let c_string_offset = frame.arena_index.get(&format!("{}.c_string", id))
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string_into_frame: missing '{}.c_string'", id)))?;
            let cap_offset = frame.arena_index.get(&format!("{}.cap", id))
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string_into_frame: missing '{}.cap'", id)))?;
            Arena::g().memory[c_string_offset..c_string_offset + 8].copy_from_slice(&string_offset_bytes);
            Arena::g().memory[cap_offset..cap_offset + 8].copy_from_slice(&len_bytes);
        }
        Ok(())
    }

    /// Helper function to insert primitive types (I64, U8, Bool, Str) based on value_type
    pub fn insert_primitive(
        ctx: &mut Context,
        var_name: &str,
        value_type: &ValueType,
        value: &str,
        e: &Expr
    ) -> Result<(), String> {
        match value_type {
            ValueType::TCustom(type_name) if type_name == "I64" => {
                Arena::insert_i64(ctx, var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "U8" => {
                Arena::insert_u8(ctx, var_name, &value.to_string(), e)
            },
            // TODO FIX: Bool special case for insert_primitive - needed for bootstrap and primitives handling
            ValueType::TCustom(type_name) if type_name == "Bool" => {
                Arena::insert_bool(ctx, var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "Str" => {
                Arena::insert_string(ctx, var_name, &value.to_string(), e)
            },
            _ => Err(e.lang_error(&ctx.path, "eval", &format!("insert_primitive: Unsupported type {:?}", value_type)))
        }
    }

    /// Core logic for insert_bool - returns Some(stored_value) if caller needs to create struct, None if already handled
    fn insert_bool_core(ctx: &Context, id: &str, bool_str: &String, e: &Expr) -> Result<Option<u8>, String> {
        // Parse the bool value
        let bool_to_insert = bool_str.parse::<bool>()
            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("Invalid bool literal '{}'", bool_str)))?;
        let stored = if bool_to_insert { 1 } else { 0 };

        // Check if this is an assignment to an existing instance field
        let is_instance_field = if id.contains('.') {
            let parts: Vec<&str> = id.split('.').collect();
            let base = parts[0];
            ctx.scope_stack.lookup_symbol(base).map_or(false, |sym| {
                match &sym.value_type {
                    ValueType::TType(_) => false,
                    _ => true
                }
            })
        } else {
            false
        };

        if is_instance_field {
            // For instance field, write directly to the .data field
            let field_id = format!("{}.data", id);
            let offset = ctx.scope_stack.lookup_var(&field_id)
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("Bool field '{}.data' not found", id)))?;
            Arena::g().memory[offset] = stored;
            return Ok(None)
        }

        Ok(Some(stored))
    }

    // Helper function to insert a Bool value using insert_struct
    pub fn insert_bool(ctx: &mut Context, id: &str, bool_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(stored) = Self::insert_bool_core(ctx, id, bool_str, e)? {
            // Create Bool struct from template
            let template_offset = Arena::g().default_instances.get("Bool")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_bool", "Bool template not found - ensure bool.til is imported"))?;
            Arena::insert_struct_from_template(ctx, id, "Bool", template_offset, e)?;
            let field_id = format!("{}.data", id);
            let offset = ctx.scope_stack.lookup_var(&field_id)
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("Bool field '{}.data' not found", id)))?;
            Arena::g().memory[offset] = stored;
        }
        Ok(())
    }

    pub fn insert_bool_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, bool_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(stored) = Self::insert_bool_core(ctx, id, bool_str, e)? {
            // Create Bool struct from template
            let template_offset = Arena::g().default_instances.get("Bool")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_bool_into_frame", "Bool template not found - ensure bool.til is imported"))?;
            Arena::insert_struct_from_template_into_frame(ctx, frame, id, "Bool", template_offset, e)?;
            let field_id = format!("{}.data", id);
            let offset = frame.arena_index.get(&field_id)
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("Bool field '{}.data' not found in frame", id)))?;
            Arena::g().memory[offset] = stored;
        }
        Ok(())
    }

    pub fn get_enum_at_offset(ctx: &Context, enum_type: &str, offset: usize, e: &Expr) -> Result<EnumVal, String> {

        // Read enum from a specific offset (used for nested enum payloads)
        let enum_value_bytes = &Arena::g().memory[offset..offset + 8];
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error(&ctx.path, "context", "get_enum_at_offset: Failed to convert bytes to i64"))?);

        let enum_def = ctx.scope_stack.lookup_enum(enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum_at_offset: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, &ctx.path, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.enum_map.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload - recursively determine size
                let payload_size = Arena::get_payload_size_for_type(ctx, vtype, offset + 8, e)?;
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

    pub fn get_payload_size_for_type(ctx: &Context, vtype: &ValueType, offset: usize, e: &Expr) -> Result<usize, String> {
        match vtype {
            ValueType::TCustom(type_name) if type_name == "I64" => Ok(8),
            ValueType::TCustom(type_name) => {
                match ctx.scope_stack.lookup_symbol(type_name) {
                    Some(type_symbol) => {
                        match &type_symbol.value_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                ctx.get_type_size( type_name).map_err(|e| e.to_string())
                            },
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                // Recursively get the inner enum's size
                                let inner_enum = Arena::get_enum_at_offset(ctx, type_name, offset, e)?;
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

    pub fn get_enum(ctx: &Context, id: &str, e: &Expr) -> Result<EnumVal, String> {

        let symbol_info = ctx.scope_stack.lookup_symbol(id)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum: Symbol '{}' not found", id)))?;

        let enum_type = match &symbol_info.value_type {
            ValueType::TCustom(custom_type_name) => custom_type_name,
            _ => return Err(e.lang_error(&ctx.path, "context", &format!("get_enum: '{}' is not a custom enum type", id))),
        };

        // Try to get offset - first from arena_index, then calculate dynamically for fields
        let offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
            offset
        } else if id.contains('.') {
            // Field path - calculate offset dynamically
            ctx.get_field_offset( id)
                .map_err(|err| e.lang_error(&ctx.path, "context", &format!("get_enum: {}", err)))?
        } else {
            return Err(e.lang_error(&ctx.path, "context", &format!("get_enum: Arena index for '{}' not found", id)))
        };

        let enum_value_bytes = &Arena::g().memory[offset..offset + 8];
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("get_enum: Failed to convert bytes to i64 for '{}'", id)))?);

        let enum_def = ctx.scope_stack.lookup_enum(enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, &ctx.path, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.enum_map.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload, read it from arena
                // TODO FIX: Bool payload size hardcoded to 1 byte - should get from struct definition
                let payload_size = match vtype {
                    ValueType::TCustom(type_name) if type_name == "Bool" => 1,
                    ValueType::TCustom(type_name) if type_name == "I64" => 8,
                    ValueType::TCustom(type_name) if type_name == "Str" => {
                        16  // Str is always 16 bytes (pointer + size)
                    },
                    ValueType::TCustom(type_name) => {
                        // Check if this is a struct or enum type
                        match ctx.scope_stack.lookup_symbol(type_name) {
                            Some(type_symbol) => {
                                match &type_symbol.value_type {
                                    ValueType::TType(TTypeDef::TStructDef) => {
                                        // Get struct size
                                        ctx.get_type_size( type_name).unwrap_or(0)
                                    },
                                    ValueType::TType(TTypeDef::TEnumDef) => {
                                        // For enum payloads, recursively get the enum to determine size
                                        let inner_enum = Arena::get_enum_at_offset(ctx, type_name, offset + 8, e)?;
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

    /// Core logic for insert_enum - returns (optional mapping, EnumVal)
    fn insert_enum_core(ctx: &mut Context, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<(Option<(String, usize)>, EnumVal), String> {
        let enum_def = ctx.scope_stack.lookup_enum(enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = pre_normalized_enum_name.split('.').last()
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_enum: Invalid enum name format '{}'", pre_normalized_enum_name)))?;

        let enum_value = Context::get_variant_pos(enum_def, enum_name, &ctx.path, e)?;

        // Check if there's payload data to store
        let (payload_data, payload_type) = match &ctx.temp_enum_payload {
            Some((data, vtype)) => (Some(data.clone()), Some(vtype.clone())),
            None => (None, None),
        };

        let mapping = {
            let is_field = id.contains('.');
            if is_field {
                if let Some(offset) = ctx.scope_stack.lookup_var(id) {
                    // Update existing enum value (no new mapping needed)
                    Arena::g().memory[offset..offset + 8].copy_from_slice(&enum_value.to_le_bytes());
                    if let Some(payload_bytes) = &payload_data {
                        let payload_offset = offset + 8;
                        let payload_end = payload_offset + payload_bytes.len();
                        if Arena::g().memory.len() < payload_end {
                            Arena::g().memory.resize(payload_end, 0);
                        }
                        Arena::g().memory[payload_offset..payload_end].copy_from_slice(&payload_bytes);
                    }
                    None
                } else {
                    let offset = Arena::g().memory.len();
                    Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes());
                    if let Some(payload_bytes) = &payload_data {
                        Arena::g().memory.extend_from_slice(&payload_bytes);
                    }
                    Some((id.to_string(), offset))
                }
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes());
                if let Some(payload_bytes) = &payload_data {
                    Arena::g().memory.extend_from_slice(&payload_bytes);
                }
                Some((id.to_string(), offset))
            }
        };

        // Clear the temp payload after using it
        ctx.temp_enum_payload = None;

        Ok((mapping, EnumVal {
            enum_type: enum_type.to_string(),
            enum_name: enum_name.to_string(),
            payload: payload_data,
            payload_type,
        }))
    }

    // TODO Context.insert_enum gets an Expr for errors, any Context method that can throw should too
    pub fn insert_enum(ctx: &mut Context, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
        let (mapping, enum_val) = Self::insert_enum_core(ctx, id, enum_type, pre_normalized_enum_name, e)?;
        if let Some((key, offset)) = mapping {
            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(key, offset);
        }
        Ok(enum_val)
    }

    pub fn insert_enum_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
        // Temporarily push frame so symbol lookups work in core function
        let empty_frame = ScopeFrame {
            arena_index: std::collections::HashMap::new(),
            symbols: std::collections::HashMap::new(),
            funcs: std::collections::HashMap::new(),
            enums: std::collections::HashMap::new(),
            structs: std::collections::HashMap::new(),
            scope_type: ScopeType::Function,
        };
        let taken_frame = std::mem::replace(frame, empty_frame);
        ctx.scope_stack.frames.push(taken_frame);

        let result = Self::insert_enum_core(ctx, id, enum_type, pre_normalized_enum_name, e);

        // Pop frame back
        *frame = ctx.scope_stack.frames.pop().unwrap();

        // Now apply result to the frame
        let (mapping, enum_val) = result?;
        if let Some((key, offset)) = mapping {
            frame.arena_index.insert(key, offset);
        }
        Ok(enum_val)
    }

    /// Core logic for insert_array - returns mappings to be inserted by caller
    fn insert_array_core(ctx: &mut Context, name: &str, elem_type: &str, values: &Vec<String>, e: &Expr) -> Result<Vec<(String, usize)>, String> {
        // All array types now use the generic Array
        let array_type = "Array".to_string();

        // SPECIAL CASE: Array is a built-in type with known defaults.
        // We inline them here to avoid calling eval_struct_defaults from within Arena.
        // Array has: type_name (Str), type_size (I64), ptr (I64), _len (I64)
        let mut array_defaults = HashMap::new();
        array_defaults.insert("type_name".to_string(), "".to_string());
        array_defaults.insert("type_name.c_string".to_string(), "0".to_string());
        array_defaults.insert("type_name.cap".to_string(), "0".to_string());
        array_defaults.insert("type_size".to_string(), "0".to_string());
        array_defaults.insert("ptr".to_string(), "0".to_string());
        array_defaults.insert("_len".to_string(), "0".to_string());

        // Get struct mappings (don't insert yet)
        let struct_result = Self::insert_struct_core(ctx, name, &array_type, None, &array_defaults, e)?;
        let mut mappings = struct_result.arena_mappings;

        // Helper to find offset from mappings
        let find_offset = |mappings: &Vec<(String, usize)>, key: &str| -> Option<usize> {
            mappings.iter().find(|(k, _)| k == key).map(|(_, v)| *v)
        };

        let len = values.len() as i64;
        let elem_size = match ctx.get_type_size( elem_type) {
            Ok(sz) => sz,
            Err(err) => return Err(e.lang_error(&ctx.path, "context", &err)),
        };
        let total_size = (len as usize) * elem_size;

        // Allocate memory
        let ptr = Arena::g().memory.len();
        Arena::g().memory.resize(ptr + total_size, 0);

        // Write values into allocated buffer
        for (i, val) in values.iter().enumerate() {
            let offset = ptr + i * elem_size;
            // TODO FIX: Bool can't be removed yet - array initialization needs to parse "true"/"false" strings
            match elem_type {
                "Bool" => {
                    let stored = if val.as_str() == "true" { 1 } else { 0 };
                    Arena::g().memory[offset] = stored;
                },
                "U8" => {
                    match val.parse::<u8>() {
                        Ok(byte) => Arena::g().memory[offset] = byte,
                        Err(err) => return Err(e.lang_error(&ctx.path, "context", &format!("ERROR: insert_array: invalid U8 '{}'", &err)))
                    }
                },
                "I64" => {
                    match val.parse::<i64>() {
                        Ok(n) => {
                            let bytes = n.to_ne_bytes();
                            Arena::g().memory[offset..offset+8].copy_from_slice(&bytes);
                        },
                        Err(err) => return Err(e.lang_error(&ctx.path, "context", &format!("ERROR: insert_array: invalid I64 '{}'", &err)))
                    }
                },
                "Str" => {
                    for (i, val) in values.iter().enumerate() {
                        let offset = ptr + i * elem_size;

                        let temp_id = format!("{}_{}", name, i);
                        // Declare temp symbol (insert_struct_core requires it for is_mut lookup)
                        ctx.scope_stack.declare_symbol(temp_id.clone(), SymbolInfo {
                            value_type: ValueType::TCustom("Str".to_string()),
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                        });
                        // For Str elements: call insert_string_core for data, insert_struct_core for Str struct
                        if let Some((string_offset_bytes, len_bytes)) = Self::insert_string_core(ctx, &temp_id, val, e)? {
                            // SPECIAL CASE: Str defaults inlined (see insert_string)
                            let mut str_defaults = HashMap::new();
                            str_defaults.insert("c_string".to_string(), "0".to_string());
                            str_defaults.insert("cap".to_string(), "0".to_string());
                            let str_struct_result = Self::insert_struct_core(ctx, &temp_id, "Str", None, &str_defaults, e)?;
                            let c_string_offset = str_struct_result.arena_mappings.iter()
                                .find(|(k, _)| k == &format!("{}.c_string", temp_id))
                                .map(|(_, v)| *v)
                                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing '{}.c_string'", temp_id)))?;
                            let cap_offset = str_struct_result.arena_mappings.iter()
                                .find(|(k, _)| k == &format!("{}.cap", temp_id))
                                .map(|(_, v)| *v)
                                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing '{}.cap'", temp_id)))?;
                            Arena::g().memory[c_string_offset..c_string_offset + 8].copy_from_slice(&string_offset_bytes);
                            Arena::g().memory[cap_offset..cap_offset + 8].copy_from_slice(&len_bytes);

                            // Get the struct base offset and copy to array slot
                            let str_offset = str_struct_result.arena_mappings.iter()
                                .find(|(k, _)| k == &temp_id)
                                .map(|(_, v)| *v)
                                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing arena offset for '{}'", temp_id)))?;
                            Arena::g().memory[offset..offset + elem_size]
                                .copy_from_slice(&Arena::g().memory[str_offset..str_offset + elem_size]);
                            mappings.extend(str_struct_result.arena_mappings);
                        }
                    }
                }

                _ => {
                    return Err(e.lang_error(&ctx.path, "context", &format!("insert_array: unsupported element type '{}'", elem_type)))
                }
            }
        }

        // Write ptr, len (and cap for Vec) using calculated offsets
        let ptr_field_path = format!("{}.ptr", name);
        let ptr_offset = find_offset(&mappings, &ptr_field_path)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing '{}'", ptr_field_path)))?;
        Arena::g().memory[ptr_offset..ptr_offset+8].copy_from_slice(&(ptr as i64).to_ne_bytes());

        // Set _len field (required for both Array and Vec)
        let len_bytes = len.to_ne_bytes();
        let len_field_path = format!("{}._len", name);
        let len_offset = find_offset(&mappings, &len_field_path)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing '{}'", len_field_path)))?;
        Arena::g().memory[len_offset..len_offset+8].copy_from_slice(&len_bytes);

        // Note: Array doesn't have a cap field (only Vec has cap)
        // This function only creates Array structs (see line 2058)

        // For generic Array, also set type_name and type_size fields
        if array_type == "Array" {
            // Set type_name field (it's a Str, so we need to store it properly)
            let type_name_field = format!("{}.type_name", name);
            if let Some(type_name_offset) = find_offset(&mappings, &type_name_field) {
                let temp_id = format!("{}_type_name_temp", name);
                // Declare temp symbol (insert_struct_core requires it for is_mut lookup)
                ctx.scope_stack.declare_symbol(temp_id.clone(), SymbolInfo {
                    value_type: ValueType::TCustom("Str".to_string()),
                    is_mut: false,
                    is_copy: false,
                    is_own: false,
                });
                if let Some((string_offset_bytes, len_bytes)) = Self::insert_string_core(ctx, &temp_id, &elem_type.to_string(), e)? {
                    // SPECIAL CASE: Str defaults inlined (see insert_string)
                    let mut str_defaults = HashMap::new();
                    str_defaults.insert("c_string".to_string(), "0".to_string());
                    str_defaults.insert("cap".to_string(), "0".to_string());
                    let str_struct_result = Self::insert_struct_core(ctx, &temp_id, "Str", None, &str_defaults, e)?;
                    let c_string_offset = str_struct_result.arena_mappings.iter()
                        .find(|(k, _)| k == &format!("{}.c_string", temp_id))
                        .map(|(_, v)| *v)
                        .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing '{}.c_string'", temp_id)))?;
                    let cap_offset = str_struct_result.arena_mappings.iter()
                        .find(|(k, _)| k == &format!("{}.cap", temp_id))
                        .map(|(_, v)| *v)
                        .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing '{}.cap'", temp_id)))?;
                    Arena::g().memory[c_string_offset..c_string_offset + 8].copy_from_slice(&string_offset_bytes);
                    Arena::g().memory[cap_offset..cap_offset + 8].copy_from_slice(&len_bytes);

                    let str_offset = str_struct_result.arena_mappings.iter()
                        .find(|(k, _)| k == &temp_id)
                        .map(|(_, v)| *v)
                        .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_array: missing arena offset for '{}'", temp_id)))?;
                    let str_size = ctx.get_type_size( "Str")?;
                    Arena::g().memory[type_name_offset..type_name_offset + str_size]
                        .copy_from_slice(&Arena::g().memory[str_offset..str_offset + str_size]);
                    mappings.extend(str_struct_result.arena_mappings);
                }
            }

            // Set type_size field
            let type_size_field = format!("{}.type_size", name);
            if let Some(type_size_offset) = find_offset(&mappings, &type_size_field) {
                let size_bytes = (elem_size as i64).to_ne_bytes();
                Arena::g().memory[type_size_offset..type_size_offset + 8].copy_from_slice(&size_bytes);
            }
        }

        Ok(mappings)
    }

    pub fn insert_array_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, name: &str, elem_type: &str, values: &Vec<String>, e: &Expr) -> Result<(), String> {
        // Temporarily push frame so symbol lookups work in core function
        let empty_frame = ScopeFrame {
            arena_index: std::collections::HashMap::new(),
            symbols: std::collections::HashMap::new(),
            funcs: std::collections::HashMap::new(),
            enums: std::collections::HashMap::new(),
            structs: std::collections::HashMap::new(),
            scope_type: ScopeType::Function,
        };
        let taken_frame = std::mem::replace(frame, empty_frame);
        ctx.scope_stack.frames.push(taken_frame);

        let result = Self::insert_array_core(ctx, name, elem_type, values, e);

        // Pop frame back
        *frame = ctx.scope_stack.frames.pop().unwrap();

        // Now apply mappings to the frame
        let mappings = result?;
        for (key, offset) in mappings {
            frame.arena_index.insert(key, offset);
        }
        Ok(())
    }
}
