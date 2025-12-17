use std::collections::HashMap;
use std::convert::TryInto;
use crate::rs::init::{Context, SymbolInfo, EnumVal, ScopeFrame, ScopeType};
use crate::rs::parser::{Expr, ValueType, TTypeDef, value_type_to_str, NodeType, Literal};

// Arena: Memory management for the TIL interpreter
// Extracted from interpreter.rs to enable incremental translation to TIL.

pub struct Arena {
    pub memory: Vec<u8>,
    pub temp_id_counter: usize,
    pub default_instances: HashMap<String, usize>,  // type name -> arena offset of default template
}

pub struct ArenaMapping {
    pub name: String,
    pub offset: usize,
}

pub struct SymbolEntry {
    pub name: String,
    pub info: SymbolInfo,
}

/// Result from insert_struct_core containing mappings to be stored
pub struct StructInsertResult {
    pub arena_mappings: Vec<ArenaMapping>,
    pub symbols: Vec<SymbolEntry>,
}

/// Result from insert_string_core containing string offset and length bytes
pub struct StringInsertInfo {
    pub string_offset_bytes: [u8; 8],
    pub len_bytes: [u8; 8],
}

/// Result from insert_enum_core containing optional mapping and enum value
pub struct EnumInsertResult {
    pub mapping: Option<ArenaMapping>,
    pub enum_val: EnumVal,
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

    /// Get current used length of arena memory
    pub fn len(&self) -> usize {
        self.memory.len()
    }

    /// Get size of arena memory (same as len for Arena)
    pub fn size(&self) -> usize {
        self.memory.len()
    }

    /// Append bytes to arena, return offset where they were placed
    pub fn put(&mut self, bytes: &[u8]) -> usize {
        let offset = self.memory.len();
        self.memory.extend_from_slice(bytes);
        offset
    }

    /// Read bytes from arena at offset
    pub fn get(&self, offset: usize, len: usize) -> &[u8] {
        &self.memory[offset..offset + len]
    }

    /// Write bytes to arena at offset
    pub fn set(&mut self, offset: usize, bytes: &[u8]) {
        self.memory[offset..offset + bytes.len()].copy_from_slice(bytes);
    }

    // === EVAL-PHASE MEMORY OPERATIONS ===
    // These methods manage runtime memory allocation and access
    // They take Context as parameter to access type info and arena_index

    /// Check if id refers to an instance field (e.g., "myStruct.field") vs a type constant
    fn is_instance_field(ctx: &Context, id: &str) -> bool {
        if !id.contains('.') { return false; }
        let base = id.split('.').next().unwrap();
        ctx.scope_stack.lookup_symbol(base).map_or(false, |sym| {
            !matches!(sym.value_type, ValueType::TType(_))
        })
    }

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

        match Arena::g().get(offset, 8).try_into() {
            Ok(bytes) => Ok(i64::from_ne_bytes(bytes)),
            Err(_) => Err(e.lang_error(&ctx.path, "context", &format!("Invalid i64 read for id '{}'", id))),
        }
    }

    /// Core logic for insert_i64 - returns Some(offset) if caller needs to store it, None if already handled
    fn insert_i64_core(ctx: &Context, id: &str, i64_str: &String, e: &Expr) -> Result<Option<usize>, String> {
        let v = i64_str.parse::<i64>()
            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("Invalid i64 literal '{}'", i64_str)))?;
        let bytes = v.to_ne_bytes();

        if Self::is_instance_field(ctx, id) {
            // For instance field paths, calculate offset dynamically
            // REM renamed to field_offset (vs Rust's offset) due to C scope flattening
            let field_offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
                // Pre-registered field (old path)
                offset
            } else {
                // Calculate offset from struct definition
                ctx.get_field_offset( id).map_err(|err| {
                    e.lang_error(&ctx.path, "context", &format!("insert_i64: {}", err))
                })?
            };

            // Ensure arena has enough space
            let required_len = field_offset + 8;
            if Arena::g().len() < required_len {
                Arena::g().memory.resize(required_len, 0);
            }

            Arena::g().set(field_offset, &bytes);
            return Ok(None)
        }

        // For non-instance fields (including struct constants like Vec.INIT_CAP), create new entry
        let offset = Arena::g().put(&bytes);
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

        if Self::is_instance_field(ctx, id) {
            // For instance field paths, calculate offset dynamically
            // REM renamed to field_offset (vs Rust's offset) due to C scope flattening
            let field_offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
                // Pre-registered field (old path)
                offset
            } else {
                // Calculate offset from struct definition
                ctx.get_field_offset( id).map_err(|err| {
                    e.lang_error(&ctx.path, "context", &format!("insert_u8: {}", err))
                })?
            };
            Arena::g().set(field_offset, &[v]);
            return Ok(None)
        }

        let offset = Arena::g().put(&[v]);
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
                        is_comptime_const: false,
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
                let off = Arena::g().len();
                Arena::g().memory.resize(off + total_size, 0);
                off
            }
        };
        result.arena_mappings.push(ArenaMapping { name: id.to_string(), offset });

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
                        let index = match enum_def.keys().position(|v| v == variant) {
                            Some(i) => i as i64,
                            None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Unknown enum variant '{}' for field '{}'", variant, decl.name))),
                        };
                        Arena::g().set(offset + field_offset, &index.to_ne_bytes());
                    } else {
                        match type_name.as_str() {
                            "U8" => {
                                let v = default_value.parse::<u8>().map_err(|_| {
                                    e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid U8 default value '{}' for field '{}'", default_value, decl.name))
                                })?;
                                Arena::g().set(offset + field_offset, &[v]);
                            },
                            "I64" => {
                                let v = default_value.parse::<i64>().map_err(|_| {
                                    e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid I64 default value '{}' for field '{}'", default_value, decl.name))
                                })?;
                                Arena::g().set(offset + field_offset, &v.to_ne_bytes());
                            },
                            _ => {
                                if ctx.scope_stack.lookup_struct(type_name).is_some() {
                                    let combined_name = format!("{}.{}", id, decl.name);
                                    let nested_symbol = SymbolInfo {
                                        value_type: ValueType::TCustom(type_name.clone()),
                                        is_mut: true,
                                        is_copy: false,
                                        is_own: false,
                                        is_comptime_const: false,
                                    };
                                    // Must declare symbol BEFORE recursive call (needed for is_mut lookup)
                                    ctx.scope_stack.declare_symbol(combined_name.clone(), nested_symbol.clone());
                                    result.symbols.push(SymbolEntry { name: combined_name.clone(), info: nested_symbol });

                                    // Special case: Str field initialization
                                    if type_name == "Str" {
                                        // Register inline offset BEFORE insert_string so it writes to the inline space
                                        let field_arena_offset = offset + field_offset;
                                        result.arena_mappings.push(ArenaMapping { name: combined_name.clone(), offset: field_arena_offset });
                                        // Need to temporarily insert for insert_string to work
                                        ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(combined_name.clone(), field_arena_offset);
                                        Arena::insert_string(ctx, &combined_name, &default_value, e)?;
                                    } else {
                                        // Use existing offset for nested struct (inline allocation)
                                        let field_arena_offset = offset + field_offset;
                                        result.arena_mappings.push(ArenaMapping { name: combined_name.clone(), offset: field_arena_offset });
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
            result.arena_mappings.push(ArenaMapping { name: combined_name.clone(), offset: field_arena_offset });
            result.symbols.push(SymbolEntry { name: combined_name, info: SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut,
                is_copy: false,
                is_own: false,
                is_comptime_const: false,
            }});
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
        result.arena_mappings.push(ArenaMapping { name: id.to_string(), offset: base_offset });

        // Generate mappings for each field
        for decl in struct_def.members.iter() {
            if decl.is_mut {
                let field_rel_offset = field_offsets.get(&decl.name).copied().unwrap_or(0);
                let field_abs_offset = base_offset + field_rel_offset;
                let combined_name = format!("{}.{}", id, decl.name);

                result.arena_mappings.push(ArenaMapping { name: combined_name.clone(), offset: field_abs_offset });
                result.symbols.push(SymbolEntry { name: combined_name.clone(), info: SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut,
                    is_copy: false,
                    is_own: false,
                    is_comptime_const: false,
                }});

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
                                is_comptime_const: false,
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
    pub fn insert_struct(ctx: &mut Context, id: &str, custom_type_name: &str, template_offset: usize, e: &Expr) -> Result<(), String> {
        // Get struct size
        let struct_size = ctx.get_type_size(custom_type_name)?;

        // Allocate new memory
        let new_offset = Arena::g().len();
        Arena::g().memory.resize(new_offset + struct_size, 0);

        // memcpy from template
        let data = Arena::g().get(template_offset, struct_size).to_vec();
        Arena::g().set(new_offset, &data);

        // Generate and apply mappings
        let result = Arena::generate_struct_mappings(ctx, id, custom_type_name, new_offset, e)?;
        for m in result.arena_mappings {
            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(m.name, m.offset);
        }
        for s in result.symbols {
            ctx.scope_stack.declare_symbol(s.name, s.info);
        }

        Ok(())
    }

    /// Insert a struct from template into a specific frame (for function parameters).
    pub fn insert_struct_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, custom_type_name: &str, template_offset: usize, e: &Expr) -> Result<(), String> {
        // Get struct size
        let struct_size = ctx.get_type_size(custom_type_name)?;

        // Allocate new memory
        let new_offset = Arena::g().len();
        Arena::g().memory.resize(new_offset + struct_size, 0);

        // memcpy from template
        let data = Arena::g().get(template_offset, struct_size).to_vec();
        Arena::g().set(new_offset, &data);

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
        for m in result.arena_mappings {
            frame.arena_index.insert(m.name, m.offset);
        }
        for s in result.symbols {
            frame.symbols.insert(s.name, s.info);
        }

        Ok(())
    }

    /// Core logic for insert_string - returns Some(StringInsertInfo) if caller needs to create struct, None if already handled
    fn insert_string_core(ctx: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<Option<StringInsertInfo>, String> {
        let is_field = Self::is_instance_field(ctx, id);

        // Allocate string data
        let string_offset = Arena::g().put(value_str.as_bytes());
        Arena::g().put(&[0]); // null terminator
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
                            if decl.name == "c_string" {
                                Arena::g().set(absolute_offset, &string_offset_bytes);
                            } else if decl.name == "cap" {
                                Arena::g().set(absolute_offset, &len_bytes);
                            }

                            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(format!("{}.{}", id, decl.name), absolute_offset);
                            current_offset += type_size;
                        }
                    }
                    return Ok(None)
                }
                return Err(e.lang_error(&ctx.path, "context", "ERROR: 'Str' struct definition not found"))
            }

            // Not yet inserted - insert fresh inlined Str
            if let Some(str_def) = ctx.scope_stack.lookup_struct("Str") {
                let members = str_def.members.clone();
                let struct_offset = Arena::g().len();
                let mut current_offset = 0;

                for decl in members.iter() {
                    if decl.is_mut {
                        let type_size = ctx.get_type_size( &value_type_to_str(&decl.value_type))?;
                        if Arena::g().len() < struct_offset + current_offset + type_size {
                            Arena::g().memory.resize(struct_offset + current_offset + type_size, 0);
                        }

                        if decl.name == "c_string" {
                            Arena::g().set(struct_offset + current_offset, &string_offset_bytes);
                        } else if decl.name == "cap" {
                            Arena::g().set(struct_offset + current_offset, &len_bytes);
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

        Ok(Some(StringInsertInfo { string_offset_bytes, len_bytes }))
    }

    pub fn insert_string(ctx: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(info) = Self::insert_string_core(ctx, id, value_str, e)? {
            // Create Str struct from template
            let template_offset = Arena::g().default_instances.get("Str")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string", "Str template not found - ensure str.til is imported"))?;
            Arena::insert_struct(ctx, id, "Str", template_offset, e)?;
            let c_string_offset = ctx.scope_stack.lookup_var(&format!("{}.c_string", id))
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string: missing '{}.c_string'", id)))?;
            let cap_offset = ctx.scope_stack.lookup_var(&format!("{}.cap", id))
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string: missing '{}.cap'", id)))?;
            Arena::g().set(c_string_offset, &info.string_offset_bytes);
            Arena::g().set(cap_offset, &info.len_bytes);
        }
        Ok(())
    }

    pub fn insert_string_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(info) = Self::insert_string_core(ctx, id, value_str, e)? {
            // Create Str struct from template
            let template_offset = Arena::g().default_instances.get("Str")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string_into_frame", "Str template not found - ensure str.til is imported"))?;
            Arena::insert_struct_into_frame(ctx, frame, id, "Str", template_offset, e)?;
            let c_string_offset = frame.arena_index.get(&format!("{}.c_string", id))
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string_into_frame: missing '{}.c_string'", id)))?;
            let cap_offset = frame.arena_index.get(&format!("{}.cap", id))
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_string_into_frame: missing '{}.cap'", id)))?;
            Arena::g().set(c_string_offset, &info.string_offset_bytes);
            Arena::g().set(cap_offset, &info.len_bytes);
        }
        Ok(())
    }

    /// Helper function to insert primitive types (I64, U8, Str) based on value_type
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
            ValueType::TCustom(type_name) if type_name == "Str" => {
                Arena::insert_string(ctx, var_name, &value.to_string(), e)
            },
            _ => Err(e.lang_error(&ctx.path, "eval", &format!("insert_primitive: Unsupported type {:?}", value_type)))
        }
    }

    pub fn get_enum_at_offset(ctx: &Context, enum_type: &str, offset: usize, e: &Expr) -> Result<EnumVal, String> {

        // Read enum from a specific offset (used for nested enum payloads)
        let enum_value_bytes = Arena::g().get(offset, 8);
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error(&ctx.path, "context", "get_enum_at_offset: Failed to convert bytes to i64"))?);

        let enum_def = ctx.scope_stack.lookup_enum(enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum_at_offset: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, &ctx.path, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload - recursively determine size
                let payload_size = Arena::get_payload_size_for_type(ctx, vtype, offset + 8, e)?;
                if payload_size > 0 {
                    let payload_offset = offset + 8;
                    let payload_end = payload_offset + payload_size;
                    if payload_end <= Arena::g().len() {
                        let payload_bytes = Arena::g().get(payload_offset, payload_size).to_vec();
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
        // For field paths (e.g., "s.color"), get the field's type, not the base struct's type
        let enum_type = if id.contains('.') {
            match ctx.get_field_type(id) {
                Ok(ValueType::TCustom(type_name)) => type_name,
                Ok(_) => return Err(e.lang_error(&ctx.path, "context", &format!("get_enum: field '{}' is not a custom enum type", id))),
                Err(err) => return Err(e.lang_error(&ctx.path, "context", &format!("get_enum: {}", err))),
            }
        } else {
            let symbol_info = ctx.scope_stack.lookup_symbol(id)
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum: Symbol '{}' not found", id)))?;

            match &symbol_info.value_type {
                ValueType::TCustom(custom_type_name) => custom_type_name.clone(),
                _ => return Err(e.lang_error(&ctx.path, "context", &format!("get_enum: '{}' is not a custom enum type", id))),
            }
        };

        // Try to get offset - first from arena_index, then calculate dynamically for fields
        let offset = if let Some(offset) = ctx.scope_stack.lookup_var(id) {
            offset
        } else if id.contains('.') {
            // Field path - calculate offset dynamically
            ctx.get_field_offset(id)
                .map_err(|err| e.lang_error(&ctx.path, "context", &format!("get_enum: {}", err)))?
        } else {
            return Err(e.lang_error(&ctx.path, "context", &format!("get_enum: Arena index for '{}' not found", id)))
        };

        let enum_value_bytes = Arena::g().get(offset, 8);
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("get_enum: Failed to convert bytes to i64 for '{}'", id)))?);

        let enum_def = ctx.scope_stack.lookup_enum(&enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, &ctx.path, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload, read it from arena
                let payload_size = match vtype {
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
                    if payload_end <= Arena::g().len() {
                        let payload_bytes = Arena::g().get(payload_offset, payload_size).to_vec();
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

    /// Core logic for insert_enum - returns EnumInsertResult with optional mapping and EnumVal
    fn insert_enum_core(ctx: &mut Context, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumInsertResult, String> {
        let enum_def = ctx.scope_stack.lookup_enum(enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = pre_normalized_enum_name.split('.').last()
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("insert_enum: Invalid enum name format '{}'", pre_normalized_enum_name)))?;

        let enum_value = Context::get_variant_pos(enum_def, enum_name, &ctx.path, e)?;

        // Check if there's payload data to store
        let (payload_data, payload_type) = match &ctx.temp_enum_payload {
            Some(payload) => (Some(payload.data.clone()), Some(payload.value_type.clone())),
            None => (None, None),
        };

        // Bug #38 fix: Always allocate the maximum enum size to support memcpy of any variant
        // This ensures that when an enum is copied via memcpy (e.g., from Vec.get), the full
        // payload space is available even if the current variant has no payload.
        let max_enum_size = ctx.get_type_size(enum_type)
            .map_err(|err| e.lang_error(&ctx.path, "context", &format!("insert_enum: {}", err)))?;
        let payload_size = if let Some(ref bytes) = payload_data { bytes.len() } else { 0 };
        let actual_size = 8 + payload_size; // tag + current payload

        let mapping = {
            let is_field = id.contains('.');
            if is_field {
                if let Some(offset) = ctx.scope_stack.lookup_var(id) {
                    // Update existing enum value (no new mapping needed)
                    Arena::g().set(offset, &enum_value.to_le_bytes());
                    if let Some(payload_bytes) = &payload_data {
                        let payload_offset = offset + 8;
                        let payload_end = payload_offset + payload_bytes.len();
                        if Arena::g().len() < payload_end {
                            Arena::g().memory.resize(payload_end, 0);
                        }
                        Arena::g().set(payload_offset, &payload_bytes);
                    }
                    None
                } else {
                    // Allocate max enum size, write tag and payload, then zero-pad remaining
                    let offset = Arena::g().put(&enum_value.to_le_bytes());
                    if let Some(payload_bytes) = &payload_data {
                        Arena::g().put(&payload_bytes);
                    }
                    // Pad with zeros to reach max_enum_size
                    if actual_size < max_enum_size {
                        Arena::g().memory.resize(offset + max_enum_size, 0);
                    }
                    Some(ArenaMapping { name: id.to_string(), offset })
                }
            } else {
                // Allocate max enum size, write tag and payload, then zero-pad remaining
                let offset = Arena::g().put(&enum_value.to_le_bytes());
                if let Some(payload_bytes) = &payload_data {
                    Arena::g().put(&payload_bytes);
                }
                // Pad with zeros to reach max_enum_size
                if actual_size < max_enum_size {
                    Arena::g().memory.resize(offset + max_enum_size, 0);
                }
                Some(ArenaMapping { name: id.to_string(), offset })
            }
        };

        // Clear the temp payload after using it
        ctx.temp_enum_payload = None;

        Ok(EnumInsertResult {
            mapping,
            enum_val: EnumVal {
                enum_type: enum_type.to_string(),
                enum_name: enum_name.to_string(),
                payload: payload_data,
                payload_type,
            },
        })
    }

    // TODO Context.insert_enum gets an Expr for errors, any Context method that can throw should too
    pub fn insert_enum(ctx: &mut Context, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
        let result = Self::insert_enum_core(ctx, id, enum_type, pre_normalized_enum_name, e)?;
        if let Some(m) = result.mapping {
            ctx.scope_stack.frames.last_mut().unwrap().arena_index.insert(m.name, m.offset);
        }
        Ok(result.enum_val)
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
        let result = result?;
        if let Some(m) = result.mapping {
            frame.arena_index.insert(m.name, m.offset);
        }
        Ok(result.enum_val)
    }

    /// Insert an Array for variadic arguments into a function frame.
    /// Uses insert_struct_into_frame internally.
    pub fn insert_array_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, name: &str, elem_type: &str, values: &Vec<String>, e: &Expr) -> Result<(), String> {
        // Create Array struct using template
        let template_offset = Arena::g().default_instances.get("Array").copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array_into_frame", "Array template not found - ensure array.til is imported"))?;
        Self::insert_struct_into_frame(ctx, frame, name, "Array", template_offset, e)?;

        let len = values.len() as i64;
        let elem_size = ctx.get_type_size(elem_type)?;
        let total_size = (len as usize) * elem_size;

        // Allocate memory for elements
        let ptr = Arena::g().len();
        Arena::g().memory.resize(ptr + total_size, 0);

        // Write values into allocated buffer
        for (i, val) in values.iter().enumerate() {
            let offset = ptr + i * elem_size;
            match elem_type {
                "U8" => {
                    let byte = val.parse::<u8>()
                        .map_err(|err| e.lang_error(&ctx.path, "insert_array", &format!("invalid U8 '{}'", err)))?;
                    Arena::g().set(offset, &[byte]);
                },
                "I64" => {
                    let n = val.parse::<i64>()
                        .map_err(|err| e.lang_error(&ctx.path, "insert_array", &format!("invalid I64 '{}'", err)))?;
                    Arena::g().set(offset, &n.to_ne_bytes());
                },
                "Str" => {
                    // For Str elements, create temp Str and copy bytes to array slot
                    let temp_id = format!("{}_{}", name, i);
                    frame.symbols.insert(temp_id.clone(), SymbolInfo {
                        value_type: ValueType::TCustom("Str".to_string()),
                        is_mut: false,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    });
                    Self::insert_string_into_frame(ctx, frame, &temp_id, val, e)?;
                    let str_offset = frame.arena_index.get(&temp_id).copied()
                        .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing Str offset for '{}'", temp_id)))?;
                    let data = Arena::g().get(str_offset, elem_size).to_vec();
                    Arena::g().set(offset, &data);
                },
                _ => {
                    // Struct element - val is identifier, copy from source
                    let src_offset = ctx.scope_stack.lookup_var(val)
                        .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("struct source '{}' not found", val)))?;
                    let data = Arena::g().get(src_offset, elem_size).to_vec();
                    Arena::g().set(offset, &data);
                }
            }
        }

        // Update Array fields from frame.arena_index
        let ptr_offset = frame.arena_index.get(&format!("{}.ptr", name)).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing '{}.ptr'", name)))?;
        Arena::g().set(ptr_offset, &(ptr as i64).to_ne_bytes());

        let len_offset = frame.arena_index.get(&format!("{}._len", name)).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing '{}._len'", name)))?;
        Arena::g().set(len_offset, &len.to_ne_bytes());

        let type_size_offset = frame.arena_index.get(&format!("{}.type_size", name)).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing '{}.type_size'", name)))?;
        Arena::g().set(type_size_offset, &(elem_size as i64).to_ne_bytes());

        // Set type_name field (it's a Str)
        let type_name_field = format!("{}.type_name", name);
        let temp_type_name_id = format!("{}_type_name_temp", name);
        frame.symbols.insert(temp_type_name_id.clone(), SymbolInfo {
            value_type: ValueType::TCustom("Str".to_string()),
            is_mut: false,
            is_copy: false,
            is_own: false,
            is_comptime_const: false,
        });
        Self::insert_string_into_frame(ctx, frame, &temp_type_name_id, &elem_type.to_string(), e)?;
        let temp_str_offset = frame.arena_index.get(&temp_type_name_id).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", "missing type_name temp Str offset"))?;
        let type_name_offset = frame.arena_index.get(&type_name_field).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing '{}'", type_name_field)))?;
        let str_size = ctx.get_type_size("Str")?;
        let data = Arena::g().get(temp_str_offset, str_size).to_vec();
        Arena::g().set(type_name_offset, &data);

        Ok(())
    }

    /// Convert a struct instance stored in Arena to a struct literal Expr.
    /// Given instance "___temp_return_val_0" of type "Bool", produces:
    ///   Bool(data=1)
    /// The `e` parameter is only used for error reporting.
    pub fn to_struct_literal(
        ctx: &Context,
        instance_name: &str,
        type_name: &str,
        e: &Expr,
    ) -> Result<Expr, String> {
        let struct_def = ctx.scope_stack.lookup_struct(type_name)
            .ok_or_else(|| e.lang_error(&ctx.path, "arena",
                &format!("to_struct_literal: struct '{}' not found", type_name)))?;

        // First param is the type identifier
        let type_id = Expr::new_explicit(NodeType::Identifier(type_name.to_string()), vec![], 0, 0);
        let mut params = vec![type_id];

        // For each mutable field, read value and create NamedArg
        for member in &struct_def.members {
            if !member.is_mut {
                continue;  // Skip static fields
            }
            let field_id = format!("{}.{}", instance_name, member.name);
            let field_value = Self::field_to_literal(ctx, &field_id, &member.value_type, e)?;

            let named_arg = Expr::new_explicit(
                NodeType::NamedArg(member.name.clone()),
                vec![field_value],
                0, 0
            );
            params.push(named_arg);
        }

        Ok(Expr::new_explicit(NodeType::FCall, params, 0, 0))
    }

    /// Helper: read a field value from Arena and convert to literal Expr
    fn field_to_literal(
        ctx: &Context,
        field_id: &str,
        value_type: &ValueType,
        e: &Expr,
    ) -> Result<Expr, String> {
        match value_type {
            ValueType::TCustom(ref t) if t == "I64" => {
                let val = Self::get_i64(ctx, field_id, e)?;
                Ok(Expr::new_explicit(NodeType::LLiteral(Literal::Number(val.to_string())), vec![], 0, 0))
            },
            ValueType::TCustom(ref t) if t == "U8" => {
                let val = Self::get_u8(ctx, field_id, e)?;
                Ok(Expr::new_explicit(NodeType::LLiteral(Literal::Number(val.to_string())), vec![], 0, 0))
            },
            ValueType::TCustom(ref nested_type) => {
                // Check if nested struct
                if ctx.scope_stack.lookup_struct(nested_type).is_some() {
                    return Self::to_struct_literal(ctx, field_id, nested_type, e);
                }
                Err(e.lang_error(&ctx.path, "arena", &format!("to_struct_literal: unsupported nested type '{}'", nested_type)))
            },
            _ => Err(e.lang_error(&ctx.path, "arena", &format!("to_struct_literal: unsupported field type '{}'", value_type_to_str(value_type)))),
        }
    }
}
