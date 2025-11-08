use std::collections::HashMap;
use std::collections::HashSet;
use std::convert::TryInto;
use std::env;
use std::fs;
use std::io::ErrorKind;

mod rs {
    pub mod lexer;
    pub mod parser;
    pub mod init;
    pub mod typer;
    pub mod interpreter;
}
use rs::lexer::{LANG_NAME, lexer_from_source};
use rs::parser::{
    Expr, NodeType, FunctionType, Declaration, SStructDef, ValueType, ModeDef, SFuncDef, SEnumDef, TTypeDef, Literal,
    mode_from_name, can_be_imported, value_type_to_str, parse_mode, parse_tokens,
};

const DEFAULT_MODE         : &str = "lib";
const SELF_HOSTED_PATH     : &str = "src/til.til";
const SKIP_AST             : bool = true;

// ---------- Context

#[derive(Debug, Clone, PartialEq)]
pub struct SymbolInfo {
    pub value_type: ValueType,
    pub is_mut: bool,
}

#[derive(Debug, Clone, PartialEq)]
struct EnumVal {
    enum_type: String,
    enum_name: String,
    // Payload for tagged unions: stores the associated data
    // For now, supports Bool (1 byte) and I64 (8 bytes)
    payload: Option<Vec<u8>>,
    payload_type: Option<ValueType>,
}

// Singleton struct that will hold the arena
struct Arena {
    memory: Vec<u8>,
    temp_id_counter: usize,
}

// heap/arena memory (starts at 1 to avoid NULL confusion)
// REM: first address 0 is reserved (invalid), malloc always >0
impl Arena {
    // This function gives access to the singleton instance of Arena
    #[allow(static_mut_refs)]
    fn g() -> &'static mut Arena {
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
    arena_index: HashMap<String, usize>, // stores offsets
    // Temporary storage for enum payload data during construction
    temp_enum_payload: Option<(Vec<u8>, ValueType)>, // (payload_bytes, payload_type)
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
    fn new(path: &String, mode_name: &str) -> Result<Context, String> {
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

    fn get_variant_pos(selfi: &SEnumDef, variant_name: &str, e: &Expr) -> Result<i64, String> {
        match selfi.enum_map.keys().position(|k| k == variant_name) {
            Some(position) => Ok(position as i64),
            None => {
                return Err(e.lang_error("context", &format!("Error: Enum variant '{}' not found in enum map.", variant_name)))
            },
        }
    }

    fn variant_pos_to_str(selfi: &SEnumDef, position: i64, e: &Expr) -> Result<String, String> {
        let keys: Vec<String> = selfi.enum_map.keys().cloned().collect();
        if position < 0 || position >= keys.len() as i64 {
            // Return an error if the position is out of bounds
            return Err(e.lang_error("context", &format!("Error: Invalid position '{}' for enum variant in '{}'.",
                                                        position, selfi.enum_map.keys().cloned().collect::<Vec<_>>().join(", "))));
        }

        // If position is valid, return the corresponding variant name
        return Ok(keys[position as usize].clone())
    }

    fn get_i64(self: &Context, id: &str, e: &Expr) -> Result<i64, String> {
        match self.arena_index.get(id) {
            Some(&offset) => match Arena::g().memory[offset..offset + 8].try_into() {
                Ok(bytes) => Ok(i64::from_ne_bytes(bytes)),
                Err(_) => Err(e.lang_error("context", &format!("Invalid i64 read for id '{}'", id))),
            },
            None => Err(e.lang_error("context", &format!("i64 not found for id '{}'", id))),
        }
    }

    fn insert_i64(self: &mut Context, id: &str, i64_str: &String, e: &Expr) -> Result<(), String> {
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

    fn get_u8(self: &Context, id: &str, e: &Expr) -> Result<u8, String> {
        match self.arena_index.get(id) {
            Some(&offset) => Arena::g().memory.get(offset).copied()
                .ok_or_else(|| e.lang_error("context", &format!("Invalid u8 read for id '{}'", id))),
            None => Err(e.lang_error("context", &format!("u8 not found for id '{}'", id))),
        }
    }

    fn insert_u8(self: &mut Context, id: &str, u8_str: &String, e: &Expr) -> Result<(), String> {
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

    fn get_bool(self: &Context, id: &str, e: &Expr) -> Result<bool, String> {
        match self.arena_index.get(id) {
            Some(&offset) => match Arena::g().memory.get(offset) {
                Some(&byte) => Ok(byte == 1),
                None => Err(e.lang_error("context", &format!("Invalid bool read for id '{}'", id))),
            },
            None => Err(e.lang_error("context", &format!("bool not found for id '{}'", id))),
        }
    }

    fn insert_bool(self: &mut Context, id: &str, bool_str: &String, e: &Expr) -> Result<(), String> {
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
        });
        self.arena_index.insert(field_id, offset);

        self.arena_index.insert(id.to_string(), offset);
        return Ok(())
    }

    fn map_instance_fields(&mut self, custom_type_name: &str, instance_name: &str, e: &Expr) -> Result<(), String> {
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
            } else {
                // Handle immutable Str fields by copying arena_index entries from type to instance
                if let ValueType::TCustom(type_name) = &decl.value_type {
                    if type_name == "Str" {
                        let type_field = format!("{}.{}", custom_type_name, field_name);
                        let instance_field = format!("{}.{}", instance_name, field_name);

                        // Copy c_string and cap arena_index entries
                        if let Some(&c_string_offset) = self.arena_index.get(&format!("{}.c_string", type_field)) {
                            self.arena_index.insert(format!("{}.c_string", instance_field), c_string_offset);
                        }
                        if let Some(&cap_offset) = self.arena_index.get(&format!("{}.cap", type_field)) {
                            self.arena_index.insert(format!("{}.cap", instance_field), cap_offset);
                        }

                        // Add symbol for the immutable field
                        self.symbols.insert(
                            instance_field.clone(),
                            SymbolInfo {
                                value_type: decl.value_type.clone(),
                                is_mut: false,
                            },
                        );
                    }
                }
            }
        }
        return Ok(())
    }

    // TODO all args should be passed as pointers/references and we wouldn't need this
    fn copy_fields(&mut self, custom_type_name: &str, src: &str, dest: &str, e: &Expr) -> Result<(), String> {
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

            let src_offset = *self.arena_index.get(&src_key)
                .ok_or_else(|| e.lang_error("context", &format!("copy_fields: source offset for '{}' not found", src_key)))?;

            let dest_offset = dest_base_offset + current_offset;

            self.arena_index.insert(dest_key.clone(), dest_offset);
            self.symbols.insert(dest_key.clone(), SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut,
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

    fn get_type_size(&self, type_name: &str) -> Result<usize, String> {
        match type_name {
            "U8"   => return Ok(1),
            "I64"  => return Ok(8),
            _ => {},
        }
        if self.enum_defs.contains_key(type_name) {
            return Ok(8);
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

    fn insert_struct(&mut self, id: &str, custom_type_name: &str, e: &Expr) -> Result<(), String> {
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
                    let res = rs::interpreter::eval_expr(self, e2)?;
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
                                        },
                                    );
                                    self.arena_index.insert(combined_name.clone(), offset + field_offset);
                                    self.insert_struct(&combined_name, type_name, e)
                                        .map_err(|_| e.lang_error("context", &format!("insert_struct: Failed to initialize nested struct '{}.{}'", id, member_name)))?;
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
                },
            );
        }

        // Map immutable fields by copying arena_index entries from the type to the instance
        for (member_name, decl) in struct_def.members.iter() {
            if decl.is_mut {
                continue; // Skip mutable fields (already handled above)
            }

            // For immutable Str fields, copy arena_index entries from type to instance
            if let ValueType::TCustom(type_name) = &decl.value_type {
                if type_name == "Str" {
                    let type_field = format!("{}.{}", custom_type_name, member_name);
                    let instance_field = format!("{}.{}", id, member_name);

                    // Copy c_string arena_index entry
                    if let Some(&c_string_offset) = self.arena_index.get(&format!("{}.c_string", type_field)) {
                        self.arena_index.insert(format!("{}.c_string", instance_field), c_string_offset);
                    }

                    // Copy cap arena_index entry
                    if let Some(&cap_offset) = self.arena_index.get(&format!("{}.cap", type_field)) {
                        self.arena_index.insert(format!("{}.cap", instance_field), cap_offset);
                    }

                    // Add symbol for the immutable field
                    self.symbols.insert(
                        instance_field.clone(),
                        SymbolInfo {
                            value_type: decl.value_type.clone(),
                            is_mut: false,
                        },
                    );
                }
            }
        }

        Ok(())
    }

    // Register struct field symbols for type checking without evaluating defaults or allocating memory
    // This allows type checking of struct method bodies without triggering evaluation errors
    fn register_struct_fields_for_typecheck(&mut self, instance_name: &str, struct_type_name: &str) {
        if let Some(struct_def) = self.struct_defs.get(struct_type_name).cloned() {
            for (member_name, decl) in &struct_def.members {
                let combined_name = format!("{}.{}", instance_name, member_name);
                self.symbols.insert(
                    combined_name.clone(),
                    SymbolInfo {
                        value_type: decl.value_type.clone(),
                        is_mut: decl.is_mut,
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

    fn get_string(&self, id: &str, e: &Expr) -> Result<String, String> {
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

    fn insert_string(self: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
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

    fn get_enum_at_offset(&self, enum_type: &str, offset: usize, e: &Expr) -> Result<EnumVal, String> {
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

    fn get_payload_size_for_type(&self, vtype: &ValueType, offset: usize, e: &Expr) -> Result<usize, String> {
        match vtype {
            ValueType::TCustom(type_name) if type_name == "Bool" => Ok(1),
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

    fn get_enum(&self, id: &str, e: &Expr) -> Result<EnumVal, String> {
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
    fn insert_enum(&mut self, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
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

        // Write ptr, len, cap, is_dyn using arena_index
        let ptr_offset = match self.arena_index.get(&format!("{}.ptr", name)) {
            Some(o) => *o,
            None => {
                return Err(e.lang_error("context", &format!("ERROR: insert_array: missing .ptr field offset")))
            }
        };
        Arena::g().memory[ptr_offset..ptr_offset+8].copy_from_slice(&(ptr as i64).to_ne_bytes());

        let len_bytes = len.to_ne_bytes();
        for field in &["len", "cap"] {
            if let Some(field_offset) = self.arena_index.get(&format!("{}.{}", name, field)) {
                Arena::g().memory[*field_offset..*field_offset+8].copy_from_slice(&len_bytes);
            } else {
                return Err(e.lang_error("context", &format!("ERROR: insert_array: missing .{} field offset", field)))
            }
        }

        if let Some(is_dyn_offset) = self.arena_index.get(&format!("{}.is_dyn", name)) {
            Arena::g().memory[*is_dyn_offset] = 0; // false
        } else {
            return Err(e.lang_error("context", "insert_array: missing .is_dyn field offset"))
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


#[derive(Clone, Debug)]
pub struct EvalResult {
    pub value: String,
    pub is_return: bool,
    pub is_throw: bool,
    thrown_type: Option<String>,
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


fn params_to_ast_str(end_line: bool, e: &Expr) -> String {
    let mut ast_str = "".to_string();
    for se in e.params.iter() {
        if end_line {
            ast_str.push_str(&format!("{}\n", to_ast_str(&se)));
        } else {
            ast_str.push_str(&format!("{} ", to_ast_str(&se)));
        }
    }
    return ast_str;
}

// TODO test this function again and maintain it, but in the self hosting side directly, perhaps
fn to_ast_str(e: &Expr) -> String {
    let mut ast_str = "".to_string();
    match &e.node_type {
        NodeType::LLiteral(Literal::Bool(lbool)) => {
            return lbool.to_string();
        },
        NodeType::LLiteral(Literal::Number(li64)) => {
            return li64.to_string();
        },
        NodeType::LLiteral(Literal::Str(lstring)) => {
            return lstring.to_string();
        },
        NodeType::DefaultCase => {
            return "default_case".to_string();
        }
        NodeType::Body => {
            return params_to_ast_str(true, &e)
        },
        // NodeType::Declaration(decl) => {
        //     ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::Assignment(var_name) => {
        //     ast_str.push_str(&format!("(set {} {})", var_name, to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        NodeType::FuncDef(func_def) => {
            match func_def.function_type {
                FunctionType::FTFunc => return "(func)".to_string(),
                FunctionType::FTProc => return "(proc)".to_string(),
                FunctionType::FTMacro => return "(macro)".to_string(),
                FunctionType::FTFuncExt => return "(ext_func)".to_string(),
                FunctionType::FTProcExt => return "(ext_proc)".to_string(),
            }
        },
        NodeType::EnumDef(_) => {
            return "(enum)".to_string();
        },
        NodeType::StructDef(_) => {
            return "(struct)".to_string();
        },
        NodeType::Identifier(id_name) => {
            return id_name.clone();
        },
        NodeType::FCall => {
            let f_name = rs::init::get_func_name_in_call(&e);
            ast_str.push_str(&format!("({} {})", f_name, params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::LLiteral(Literal::List(_)) => {
            ast_str.push_str(&format!("({})", params_to_ast_str(false, &e)));
            return ast_str;
        },
        // NodeType::If => {
        //     ast_str.push_str(&format!("(if {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::While => {
        //     ast_str.push_str(&format!("(while {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::Switch => {
        //     ast_str.push_str(&format!("(switch {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        _ => todo!(),
    }
}

// ---------- main binary

fn main_run(print_extra: bool, skip_init_and_typecheck: bool, context: &mut Context, path: &String, source: String, main_args: Vec<String>) -> Result<EvalResult, String> {

    let mut lexer = match lexer_from_source(&path, source) {
        Ok(_result) => _result,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };

    let mode = match parse_mode(&path, &mut lexer) {
        Ok(mode_) => mode_,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };
    context.mode = mode;
    if print_extra {
        println!("Mode: {}", context.mode.name);
    }

    for import_str in context.mode.imports.clone() {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall, params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};
        match rs::interpreter::eval_core_proc_import(context, &import_fcall_expr) {
            Ok(_) => {},
            Err(error_string) => {
                return Err(format!("{}:{}", &path, error_string));
            },
        }
    }

    let mut e: Expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };
    if !SKIP_AST {
        println!("AST: \n{}", to_ast_str(&e));
    }

    // Skip init and type checking if this is Phase 2 of a two-phase import
    // (declarations already registered in Phase 1)
    if !skip_init_and_typecheck {
        let mut errors = rs::init::init_context(context, &e);
        if errors.len() > 0 {
            for err in &errors {
                println!("{}:{}", path, err);
            }
            return Err(format!("Compiler errors: {} declaration errors found", errors.len()));
        }
        errors.extend(rs::typer::basic_mode_checks(&context, &e));

        // For modes that require a main proc, add an implicit call to main
        if context.mode.needs_main_proc {
            let mut main_params = Vec::new();
            main_params.push(Expr{node_type: NodeType::Identifier("main".to_string()), line: 0, col: 0, params: Vec::new()});
            for str_arg in main_args {
                main_params.push(Expr{node_type: NodeType::LLiteral(Literal::Str(str_arg)), line: 0, col: 0, params: Vec::new()});
            }
            e.params.push(Expr{node_type: NodeType::FCall, line: 0, col: 0, params: main_params});
        }
        errors.extend(rs::typer::check_types(context, &e));

        // Check throw/catch and return things in the root body of the file (for modes script and test, for example)
        let func_def = SFuncDef{args: vec![], body: vec![], function_type: FunctionType::FTProc, returns: vec![], throws: vec![]};
        let mut thrown_types: Vec<(String, String)> = vec![];
        let mut return_found = false;
        errors.extend(rs::typer::check_body_returns_throws(context, &e, &func_def, e.params.as_slice(), &mut thrown_types, &mut return_found));

        if return_found {
            errors.push(e.error("type", "Cannot return from the root of the file"));
        }
        for (_thrown_type, error_msg) in &thrown_types {
            errors.push(error_msg.to_string());
        }

        if errors.len() > 0 {
            for err in &errors {
                println!("{}:{}", path, err);
            }
            return Err(format!("Compiler errors: {} type errors found", errors.len()));
        }
    }

    return match rs::interpreter::eval_expr(context, &e) {
        Ok(eval_result) => Ok(eval_result),
        Err(err) => Err(format!("{}:{}", path, err)),
    }
}

// ---------- main, usage, args, etc

fn run_file(path: &String, main_args: Vec<String>) -> Result<EvalResult, String> {
    let mut context = Context::new(path, DEFAULT_MODE)?;
    if path != "src/core/core.til" {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(Literal::Str("src/core/core".to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall, params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};
        rs::interpreter::eval_core_proc_import(&mut context, &import_fcall_expr)?;
    }
    return run_file_with_context(false, &mut context, &path, main_args)
}

fn run_file_with_context(is_import: bool, context: &mut Context, path: &String, main_args: Vec<String>) -> Result<EvalResult, String> {
    let previous_mode = context.mode.clone();
    if !is_import {
        println!("Running file '{}'", &path);
    }
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                return Err(format!("File '{path}' not found."))
            },
            other_error => {
                return Err(format!("Problem opening the file '{path}': {other_error:?}"))
            },
        },
    };
    // Skip init and type check if this is Phase 2 of a two-phase import
    let skip_init = is_import && context.imports_declarations_done.contains(path);
    let run_result = main_run(!is_import, skip_init, context, &path, source, main_args)?;

    if is_import && !can_be_imported(&context.mode) {
        return Err(format!("file '{path}' of mode '{}' cannot be imported", context.mode.name))
    }
    context.mode = previous_mode; // restore the context mode of the calling file
    return Ok(run_result)
}

fn usage() {
    println!("Usage: {} [command] [path]\n", LANG_NAME);
    println!("Entering no arguments is equavalent to: {} repl", LANG_NAME);
    println!("Entering a single argument that's not a command is interpreted as a path, equivalent to: {} interpret <path>\n", LANG_NAME);

    println!("Commands:\n");

    println!("repl: read eval print loop.");
    println!("interpret: reads a file in provided <path> and evaluates it.");
    // println!("ast: reads a file in provided <path> and prints its abstract syntax tree (aka (lisp-like-syntax ast-from-now-on ) ).");
    // println!("build: reads a file in provided <path> and compiles it. Not implemented yet.");
    // println!("run: reads a file in provided <path> and runs it if it compiles. Not implemented yet.");
    println!("help: Prints this.\n");
}

fn run_file_or_exit(path: &String, args: Vec<String>) {
    match run_file(path, args) {
        Ok(_) => {},
        Err(err) => {
            println!("ERROR: While running file {path}:\n{path}:{err}");
            std::process::exit(1);
        },
    };
}

fn main() {
    env::set_var("RUST_BACKTRACE", "1");
    let args: Vec<String> = env::args().collect();


    if args.len() > 2 {
        let mut main_args = Vec::new();
        let mut i = 0;
        for arg in &args {
            if i > 2 {
                main_args.push(arg.clone());
            }
            i += 1;
        }
        match args[1].as_str() {
            "interpret" => {
                run_file_or_exit(&args[2], main_args);
            },
            "repl" | "build" | "run" => {
                usage();
            },
            _ => {
                println!("command '{}' not implemented.", &args[1]);
                usage();
            },
        }
        return

    } else if args.len() > 1 {
        match args[1].as_str() {
            "repl" => {
                let mut repl_temp : Vec<String> = Vec::new();
                repl_temp.push("repl".to_string());
                run_file_or_exit(&SELF_HOSTED_PATH.to_string(), repl_temp);
            },
            "ast" | "interpret" | "build" | "run" |
            "help" | "-help" | "--help" | "--version" | "-v" => {
                usage();
            },
            _ => {
                run_file_or_exit(&args[1], Vec::new());
            },
        }
        return
    }

    // If not arguments, then repl/interactive "mode"
    let mut repl_temp : Vec<String> = Vec::new();
    repl_temp.push("repl".to_string());
    run_file_or_exit(&SELF_HOSTED_PATH.to_string(), repl_temp);
}
