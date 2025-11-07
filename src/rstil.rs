use std::collections::HashMap;
use std::collections::HashSet;
use std::convert::TryInto;
use std::env;
use std::fs;
use std::io::ErrorKind;
use std::io::Write; // <--- bring flush() into scope
use std::io;

mod rs {
    pub mod lexer;
    pub mod parser;
}
use rs::lexer::{LANG_NAME, lexer_from_source};
use rs::parser::{
    INFER_TYPE,
    Expr, NodeType, FunctionType, Declaration, SStructDef, ValueType, ModeDef, SFuncDef, SEnumDef, TTypeDef, Literal,
    mode_from_name, can_be_imported, value_type_to_str, str_to_value_type, parse_mode, parse_tokens,
};

const DEFAULT_MODE         : &str = "lib";
const SELF_HOSTED_PATH     : &str = "src/til.til";
const RETURN_INSTANCE_NAME : &str = "___temp_return_val_";
const SKIP_AST             : bool = true;

// ---------- Context

#[derive(Debug, Clone, PartialEq)]
struct SymbolInfo {
    value_type: ValueType,
    is_mut: bool,
}

#[derive(Debug, Clone, PartialEq)]
struct EnumVal {
    enum_type: String,
    enum_name: String,
    // TODO implement tagged unions
    // payload: Option<String>,
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
struct Context {
    mode: ModeDef, // All contexts need a mode
    // TODO use Context.path to properly report eval errors, or...no, don't refactor the whole eval phase to return Result<String, String>
    path: String, // this is needed for core func "loc"
    // All declared symbols (types, constants, variables, and function names)
    // This is necessary for so called "context priming" or "declaration indexing"
    // aka declaring things in whatever order, aka not needing forward declarations
    // in theory it should only be needed for the "type" phase after the init context phase
    // but it can be convenient at times in eval or compile phases too, I guess.
    symbols: HashMap<String, SymbolInfo>,
    // All functions, with their function types, signatures and bodies (functions, methods, macros, etc).
    funcs: HashMap<String, SFuncDef>,
    // Enum type definitions (variants and associated data)
    enum_defs: HashMap<String, SEnumDef>,
    // Struct type definitions (fields and associated constants [including functions, structs are namespaces, almost])
    struct_defs: HashMap<String, SStructDef>,
    // maps variable names to their offsets in the arena
    arena_index: HashMap<String, usize>, // stores offsets
    // A hashmap for in the future return a struct (namespace) so that it can be assigned to a constant/var
    // TODO change the cached type to support import as returning a struct_def
    imports_done: HashMap<String, Result<EvalResult, String> >, // finalized imports
    imports_wip: HashSet<String>, // wip imports
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
            imports_done: HashMap::new(),
            imports_wip: HashSet::new(),
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
                Some(&byte) => Ok(byte == 0), // <- Fix: restore original behavior
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
        let stored = if bool_to_insert { 0 } else { 1 }; // TODO why this is backwards?
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

        Ok(())
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

        Ok(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name,
        })
    }

    // TODO Context.insert_enum gets an Expr for errors, any Context method that can throw should too
    fn insert_enum(&mut self, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
        let enum_def = self.enum_defs.get(enum_type)
            .ok_or_else(|| e.lang_error("context", &format!("insert_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = pre_normalized_enum_name.split('.').last()
            .ok_or_else(|| e.lang_error("context", &format!("insert_enum: Invalid enum name format '{}'", pre_normalized_enum_name)))?;

        let enum_value = Context::get_variant_pos(enum_def, enum_name, e)?;

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                Arena::g().memory[offset..offset + 8].copy_from_slice(&enum_value.to_le_bytes());
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes());
                self.arena_index.insert(id.to_string(), offset);
            }
        } else {
            let offset = Arena::g().memory.len();
            Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes());
            self.arena_index.insert(id.to_string(), offset);
        }

        Ok(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name: enum_name.to_string(),
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
                    let stored = if val.as_str() == "true" { 0 } else { 1 }; // TODO FIX Invert like insert_bool
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

fn get_func_name_in_call(e: &Expr) -> String {
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

fn get_combined_name(expr: &Expr) -> Result<String, String> {
    let mut parts = Vec::new();

    match &expr.node_type {
        NodeType::Identifier(s) => parts.push(s.clone()),
        _ => return Err(expr.lang_error("type", "Expected Identifier node_type at root")),
    }

    for param in &expr.params {
        match &param.node_type {
            NodeType::Identifier(s) => {
                if !param.params.is_empty() {
                    return Err(param.lang_error("type", "Nested parameters in identifier chain not supported"));
                }
                parts.push(s.clone());
            },
            _ => return Err(param.lang_error("type", "Expected Identifier node_type in params")),
        }
    }

    Ok(parts.join("."))
}

fn get_func_def_for_fcall_with_expr(context: &Context, fcall_expr: &mut Expr) -> Result<Option<SFuncDef>, String> {
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
            let combined_name = get_combined_name(func_expr)?;
            if let Some(func_def) = context.funcs.get(&combined_name) {
                return Ok(Some(func_def.clone()))
            }

            if let Some(_struct_def) = context.struct_defs.get(&combined_name) {
                return Ok(None) // REM: This is to allow struct instantiation
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

fn get_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {
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

// aka "context priming" or "declaration indexing"
fn init_context(context: &mut Context, e: &Expr) -> Vec<String> {
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
                match eval_core_proc_import(context, &e) {
                    Ok(_) => {},
                    Err(err) => {
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
                        println!("{}.til:{}", import_path, err);
                        println!("{}:{}", context.path, err);
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
            let f_name = get_func_name_in_call(e);
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

fn func_proc_has_multi_arg(func_def: &SFuncDef) -> bool {
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

fn basic_mode_checks(context: &Context, e: &Expr) -> Vec<String> {
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
                            let f_name = get_func_name_in_call(&p);
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
    let value_type = match get_value_type(&context, &inner_e) {
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
    let value_type = match get_value_type(&context, &inner_e) {
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

        let found_type = match get_value_type(&context, arg_expr) {
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

                // For struct parameters, register the field offsets so they can be accessed in the function body
                if let ValueType::TType(TTypeDef::TStructDef) = custom_symbol.value_type {
                    if let Err(err) = context.insert_struct(&arg.name, custom_type_name, e) {
                        errors.push(err);
                        return errors;
                    }
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

fn check_body_returns_throws(context: &mut Context, e: &Expr, func_def: &SFuncDef, body: &[Expr], thrown_types: &mut Vec<(String, String)>, return_found: &mut bool) -> Vec<String> {

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

                        match get_value_type(&context, return_val_e) {
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

                    match get_value_type(&context, throw_param) {
                        Ok(thrown_type) => {
                            if thrown_type == ValueType::TType(TTypeDef::TStructDef) {
                                errors.push(throw_param.error("type", "Cannot throw a struct definition.\nSuggestion: Create an instance by adding parentheses at the end."));
                            } else {
                                // Track the thrown type as a string and another string with its error
                                let thrown_type_str = value_type_to_str(&thrown_type);
                                thrown_types.push((thrown_type_str.clone(), throw_param.error("type", &format!("Function throws '{}', but it is not declared in this function's throws section.", thrown_type_str))));
                                thrown_types.push((thrown_type_str.clone(), e.error("type", "Suggestion: Update throws section here")));
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
                            thrown_types.push((called_throw_str.clone(), e.error("type", "Suggestion: Update throws section here")));
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
                                    thrown_types.push((called_throw_str.clone(), e.error("type", "Suggestion: Update throws section here")));
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
        value_type: ValueType::TCustom(type_name),
        is_mut: false,
    });
    // TODO properly insert whatever struct in the context, including the arena_index
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
            value_type = match get_value_type(&context, &inner_e) {
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
                match context.struct_defs.get(&custom_type) {
                    Some(_struct_def) => {
                        match context.insert_struct(&decl.name, &custom_type, e) {
                            Ok(_) => {},
                            Err(err) => {
                                errors.push(err);
                                return errors
                            },
                        }
                    },
                    _ => {}, // If it's enum, don't do anything
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
                    errors.push(case_expr.error("type", "Duplicate default case in switch"));
                }
                default_found = true;
                case_found = true;
            }
            _ => {
                case_found = true;

                match get_value_type(context, case_expr) {
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
        errors.extend(check_types(context, body_expr));

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
                    NodeType::FuncDef(_func_def) => {
                        let mut _function_context = context.clone();
                        // TODO FIX Uncomment to test functions inside structs
                        // errors.extend(check_func_proc_types(&func_def, &mut function_context, &inner_e));
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

fn check_types(context: &mut Context, e: &Expr) -> Vec<String> {
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

        NodeType::LLiteral(_) | NodeType::DefaultCase => {},
    }

    return errors
}

// ---------- eval (interpreter)

#[derive(Clone, Debug)]
struct EvalResult {
    value: String,
    is_return: bool,
    is_throw: bool,
    thrown_type: Option<String>,
}

impl EvalResult {
    fn new(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: false, thrown_type: None}
    }

    fn new_return(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: true, is_throw: false, thrown_type: None}
    }

    fn new_throw(value: &str, thrown_type: ValueType) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: true, thrown_type: Some(value_type_to_str(&thrown_type))}
    }
}

// ---------- core funcs implementations for eval

fn eval_core_func_loc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Core func 'loc' doesn't take arguments"))
    }
    let file = context.path.clone();
    let line = e.line;
    let col = e.col;

    Ok(EvalResult::new(&format!("{}:{}:{}:", file, line, col)))
}

// ---------- eval memory

fn eval_core_func_malloc(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'malloc' takes exactly 1 argument"))
    }

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

fn eval_core_func_free(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'free' takes exactly 1 argument"))
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let _ptr_str = result.value;
    // REM: Free does nothing in arena model (for now).

    return Ok(EvalResult::new(""))
}

fn eval_core_func_memset(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memset' takes exactly 3 arguments"))
    }

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

fn eval_core_func_memcpy(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memcpy' takes exactly 3 arguments"))
    }

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

fn eval_core_func_to_ptr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'to_ptr' takes exactly 1 argument"))
    }

    let identifier_expr = e.get(1)?;
    let combined_name = get_combined_name(identifier_expr)?;
    match context.arena_index.get(&combined_name) {
        Some(addr) => Ok(EvalResult::new(&format!("{}", addr))),
        None => Err(e.lang_error("eval", &format!("calling core func to_ptr, but '{}' is not a known identifier.", combined_name))),
    }
}

fn eval_core_func_size_of(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'size_of' takes exactly 1 argument"))
    }

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

fn eval_core_func_type_as_str(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'type_as_str' takes exactly 1 argument"))
    }

    let type_expr = e.get(1)?;
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            Ok(EvalResult::new(&format!("{}", type_name)))
        },
        node_type => Err(e.lang_error("eval", &format!("calling core func type_as_str, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

fn eval_core_func_lt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'lt' takes exactly 2 arguments"))
    }
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

fn eval_core_func_gt(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'gt' takes exactly 2 arguments"))
    }
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

fn eval_core_func_add(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'add' takes exactly 2 arguments"))
    }
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

fn eval_core_func_sub(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'sub' takes exactly 2 arguments"))
    }
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

fn eval_core_func_mul(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'mul' takes exactly 2 arguments"))
    }
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

fn eval_core_func_div(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'div' takes exactly 2 arguments"))
    }
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
    Ok(EvalResult::new(&(a / b).to_string()))
}

fn eval_core_func_mod(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
   if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'mod' takes exactly 2 arguments"))
    }
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

    // TODO: Handle b == 0? (e.g., return 0, throw, or propagate Rust panic/UB)
    Ok(EvalResult::new(&(a % b).to_string()))
}

fn eval_core_func_str_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'str_to_i64' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid input for 'str_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

fn eval_core_func_i64_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'i64_to_str' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

fn eval_core_func_enum_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'enum_to_str' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

fn eval_core_func_u8_to_i64(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'u8_to_i64' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let a = result.value
        .parse::<i64>()
        .map_err(|err| e.lang_error("eval", &format!("Invalid input for 'u8_to_i64': {}", err)))?;
    Ok(EvalResult::new(&a.to_string()))
}

fn eval_core_func_i64_to_u8(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'i64_to_u8' takes exactly 1 argument"))
    }
    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let val = result.value;
    Ok(EvalResult::new(&val))
}

// ---------- core procs implementations for eval

fn eval_core_proc_single_print(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'single_print' takes exactly 1 argument"));
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    print!("{}", result.value);
    Ok(EvalResult::new(""))
}

fn eval_core_proc_print_flush(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Core proc 'print_flush' takes 0 arguments"));
    }

    io::stdout().flush().map_err(|err| e.lang_error("eval", &format!("Failed to flush stdout: {}", err)))?;
    Ok(EvalResult::new(""))
}

fn eval_core_proc_input_read_line(_context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Core proc 'input_read_line' takes exactly 1 argument"));
    }

    let first_param = e.get(0)?;
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

fn eval_core_proc_eval_to_str(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'eval_to_str' takes exactly 1 argument"));
    }

    let path = "eval".to_string(); // Placeholder path
    let source_expr = eval_expr(context, e.get(1)?)?;
    if source_expr.is_throw {
        return Ok(source_expr); // Propagate throw
    }

    let str_source = format!("mode script; {}", source_expr.value);
    return main_run(false, context, &path, str_source, Vec::new())
}

fn eval_core_proc_runfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
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

fn eval_core_proc_import(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'import' expects a single parameter"));
    }

    let result = eval_expr(context, e.get(1)?)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }

    let original_path = context.path.clone();
    let path = format!("{}{}", result.value, ".til");

    // If imported already, use the cache
    match context.imports_done.get(&path) {
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
    context.imports_done.insert(path, result.clone());
    context.path = original_path;
    return result
}

fn eval_core_proc_readfile(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'readfile' expects a single parameter"));
    }

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

fn eval_core_exit(e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'exit' expects a single parameter"));
    }

    let e_exit_code = e.get(1)?;
    let exit_code = match &e_exit_code.node_type {
        NodeType::LLiteral(Literal::Number(my_li64)) => my_li64.parse::<i64>()
            .map_err(|err| e.lang_error("eval", &format!("Invalid number literal '{}': {}", *my_li64, err)))?,
        node_type => return Err(e.lang_error("eval", &format!("calling core proc 'exit', but found {:?} instead of literal i64 exit code.", node_type))),
    };

    std::process::exit(exit_code as i32);
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &SFuncDef, name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {

    let mut function_context = context.clone();
    let has_multi_arg = func_proc_has_multi_arg(func_def);
    if !has_multi_arg && func_def.args.len() != e.params.len() - 1 {
        return Err(e.lang_error("eval", &format!("func '{}' expected {} args, but {} were provided.",
                                                 name, func_def.args.len(), e.params.len() - 1)))
    }
    if has_multi_arg && func_def.args.len() > e.params.len() - 1 {
        return Err(e.lang_error( "eval", &format!("func '{}' expected at least {} args, but {} were provided.",
                                                  name, func_def.args.len(), e.params.len() - 1)));
    }

    let mut param_index = 1;
    let mut mut_args: Vec<(String, String, ValueType)> = Vec::new(); // (arg_name, source_name, type)

    for arg in &func_def.args {
        function_context.symbols.insert(arg.name.to_string(), SymbolInfo {value_type: arg.value_type.clone(), is_mut: arg.is_mut});
        match &arg.value_type {
            ValueType::TMulti(ref multi_value_type) => {
                let variadic_args = &e.params[param_index..];
                let mut values = Vec::new();
                for expr in variadic_args {
                    let result = eval_expr(context, expr)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let val = result.value;
                    values.push(val);
                }

                // All array types now use the generic Array
                let array_type_name = "Array".to_string();

                function_context.symbols.insert(arg.name.to_string(), SymbolInfo {
                    value_type: ValueType::TCustom(array_type_name),
                    is_mut: arg.is_mut,
                });
                function_context.insert_array(&arg.name, &multi_value_type, &values, e)?;

                // We've consumed all remaining parameters, break out of loop
                break;
            },
            ValueType::TCustom(ref custom_type_name) => {
                let current_arg = e.get(param_index)?;
                let result = eval_expr(context, &current_arg)?;
                if result.is_throw {
                    return Ok(result); // Propagate throw
                }
                let result_str = result.value;

                // Resolve Dynamic to actual type first
                let custom_type_name = &match custom_type_name.as_str() {
                    "Dynamic" => value_type_to_str(&get_value_type(context, &current_arg)?),
                    _ => custom_type_name.clone(),
                };

                // Now push to mut_args with the resolved type
                if arg.is_mut {
                    match &current_arg.node_type {
                        NodeType::Identifier(id_) => {
                            mut_args.push((arg.name.clone(), id_.clone(), ValueType::TCustom(custom_type_name.clone())));
                        },
                        _ => {
                            return Err(e.lang_error("eval", "mut arguments must be passed as identifiers"))
                        }
                    }
                }

                match custom_type_name.as_str() {
                    "I64" => {
                        function_context.insert_i64(&arg.name, &result_str, e)?;
                    },
                    "U8" => {
                        function_context.insert_u8(&arg.name, &result_str, e)?;
                    },
                    "Bool" => {
                        function_context.insert_bool(&arg.name, &result_str, e)?;
                    },
                    "Str" => {
                        function_context.insert_string(&arg.name, &result_str, e)?;
                    },
                    _ => {
                        let custom_symbol = function_context.symbols.get(custom_type_name).ok_or_else(|| {
                            return e.lang_error("eval", &format!( "Undefined symbol for custom type '{}'", custom_type_name))
                        })?;
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                function_context.insert_enum(&arg.name, &custom_type_name, &result_str, e)?;
                            },
                            ValueType::TType(TTypeDef::TStructDef) => {
                                if current_arg.params.len() > 0 {
                                    return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only name of struct instances allowed for struct arguments for now.",
                                                                             &arg.name, &custom_type_name)))
                                }
                                match &current_arg.node_type {
                                    NodeType::Identifier(id_) => {
                                        // If source and dest have the same name, we need to save the source offsets
                                        // before insert_struct overwrites them
                                        let (saved_offsets, temp_src_key) = if id_ == &arg.name {
                                            let mut offsets = Vec::new();

                                            // Save all arena_index entries that start with the struct name
                                            // This includes the base offset and all nested field offsets
                                            let prefix = format!("{}.", id_);
                                            for (key, offset) in function_context.arena_index.iter() {
                                                if key == id_ || key.starts_with(&prefix) {
                                                    offsets.push((key.clone(), *offset));
                                                }
                                            }

                                            (Some(offsets), Some(format!("__temp_src_{}", id_)))
                                        } else {
                                            (None, None)
                                        };

                                        function_context.insert_struct(&arg.name, &custom_type_name, e)?;

                                        // If we saved offsets, restore them with temp keys for copy_fields
                                        if let (Some(offsets), Some(temp_key)) = (saved_offsets, temp_src_key) {
                                            for (orig_key, offset) in offsets.iter() {
                                                let new_key = if orig_key == id_ {
                                                    temp_key.clone()
                                                } else if orig_key.starts_with(&format!("{}.", id_)) {
                                                    format!("{}{}", temp_key, &orig_key[id_.len()..])
                                                } else {
                                                    orig_key.clone()
                                                };
                                                function_context.arena_index.insert(new_key, *offset);
                                            }

                                            function_context.copy_fields(&custom_type_name, &temp_key, &arg.name, e)?;

                                            // Clean up temp keys
                                            for (orig_key, _) in offsets.iter() {
                                                let new_key = if orig_key == id_ {
                                                    temp_key.clone()
                                                } else if orig_key.starts_with(&format!("{}.", id_)) {
                                                    format!("{}{}", temp_key, &orig_key[id_.len()..])
                                                } else {
                                                    orig_key.clone()
                                                };
                                                function_context.arena_index.remove(&new_key);
                                            }
                                        } else {
                                            function_context.copy_fields(&custom_type_name, &id_, &arg.name, e)?;
                                        }
                                    },
                                    _ => {
                                        return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only names of struct instances allowed for struct arguments for now.",
                                                                                 &arg.name, &custom_type_name)))
                                    },
                                }
                            },
                            _ => {
                                return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Custom types can only be struct or enum.",
                                                                         &arg.name, &custom_type_name)))
                            },
                        }
                    },
                }

            },

            _ => {
                return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only enum custom types allowed for now.",
                                                         &arg.name, value_type_to_str(&arg.value_type))))
            },
        }

        param_index += 1;
    }

    let result = eval_body(&mut function_context, &func_def.body)?;
    if result.is_throw {
        return Ok(result); // Propagate throw
    }
    let result_str = result.value;

    for (arg_name, source_name, value_type) in mut_args {
        match value_type {
            ValueType::TCustom(ref type_name) if type_name == "I64" => {
                let val = function_context.get_i64(&arg_name, e)?;
                context.insert_i64(&source_name, &val.to_string(), e)?;
            },
            ValueType::TCustom(ref type_name) if type_name == "U8" => {
                let val = function_context.get_u8(&arg_name, e)?;
                context.insert_u8(&source_name, &val.to_string(), e)?;
            },
            ValueType::TCustom(ref type_name) if type_name == "Str" => {
                let val = function_context.get_string(&arg_name, e)?;
                context.insert_string(&source_name, &val.to_string(), e)?;
            },
            ValueType::TCustom(ref type_name) => {
                let symbol_info = match context.symbols.get(type_name) {
                    Some(symbol_info_) => symbol_info_,
                    None => {
                        return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an mut argument. Undefined symbol.", arg_name, type_name)))
                    },
                };
                match &symbol_info.value_type {
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        let val = function_context.get_enum(&arg_name, e)?;
                        context.insert_enum(&source_name, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name), e)?;
                    },
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // TODO this can be simplified once we pass all args by reference
                        if let Some(offset) = function_context.arena_index.get(&arg_name) {
                            context.arena_index.insert(source_name.to_string(), *offset);
                            context.map_instance_fields(type_name, &source_name, e)?;
                        } else {
                            return Err(e.lang_error("eval", &format!("Missing struct arena index for argument '{}'", arg_name)));
                        }
                    },
                    _ => {
                        // TODO support functions and types (ie enum_defs struct_defs) as arguments
                        return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Not an enum or struct, but a '{}'.",
                                                                 arg_name, type_name, value_type_to_str(&symbol_info.value_type))))
                    },
                }

            },
            _ => {
                return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as a mut argument. Only structs and enums allowed for now.",
                                                         arg_name, value_type_to_str(&value_type))))
            }
        }
    }

    // If function returns a user-defined struct, copy fields back to context as temp return val
    if func_def.returns.len() == 1 {
        if let ValueType::TCustom(ref custom_type_name) = func_def.returns[0] {
            // Skip core types like I64, Bool, String, U8
            match custom_type_name.as_str() {
                "I64" | "U8" | "Bool" | "Str" => { /* Do nothing for core types */ },
                _ => {

                    if let Some(custom_symbol) = function_context.symbols.get(custom_type_name) {
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                let return_instance = format!("{}{}", RETURN_INSTANCE_NAME, Arena::g().temp_id_counter);
                                Arena::g().temp_id_counter += 1;

                                // Insert the temporary return variable into the symbols table (temporary solution)
                                context.symbols.insert(return_instance.to_string(), SymbolInfo {
                                    value_type: ValueType::TCustom(custom_type_name.to_string()),
                                    is_mut: true,
                                });

                                if let Some(offset) = function_context.arena_index.get(&result_str) {
                                    context.arena_index.insert(return_instance.to_string(), *offset);
                                } else {
                                    return Err(e.lang_error("eval", &format!("Missing arena index for return value '{}'", result_str)));
                                }
                                context.map_instance_fields(custom_type_name, &return_instance, e)?;
                                return Ok(EvalResult::new_return(&return_instance))
                            },
                            _ => {
                                // Not a struct return, ignore
                            }
                        }
                    }
                },

            }
        }
    }

    return Ok(EvalResult::new(&result_str))
}

fn eval_core_func_proc_call(name: &str, context: &mut Context, e: &Expr, is_proc: bool) -> Result<EvalResult, String> {
    return match name {
        "loc" => eval_core_func_loc(context, e),
        "size_of" => eval_core_func_size_of(context, &e),
        "type_as_str" => eval_core_func_type_as_str(context, &e),
        "to_ptr" => eval_core_func_to_ptr(context, &e),
        "malloc" => eval_core_func_malloc(context, &e),
        "free" => eval_core_func_free(context, &e),
        "memset" => eval_core_func_memset(context, &e),
        "memcpy" => eval_core_func_memcpy(context, &e),
        "lt" => eval_core_func_lt(context, &e),
        "gt" => eval_core_func_gt(context, &e),
        "add" => eval_core_func_add(context, &e),
        "sub" => eval_core_func_sub(context, &e),
        "mul" => eval_core_func_mul(context, &e),
        "div" => eval_core_func_div(context, &e),
        "mod" => eval_core_func_mod(context, &e),
        "str_to_i64" => eval_core_func_str_to_i64(context, &e),
        "i64_to_str" => eval_core_func_i64_to_str(context, &e),
        "enum_to_str" => eval_core_func_enum_to_str(context, &e),
        "u8_to_i64" => eval_core_func_u8_to_i64(context, &e),
        "i64_to_u8" => eval_core_func_i64_to_u8(context, &e),
        "eval_to_str" => eval_core_proc_eval_to_str(context, &e),
        "exit" => eval_core_exit(&e),
        "import" => Ok(EvalResult::new("")), // REM Should already be imported in init_context
        "input_read_line" => eval_core_proc_input_read_line(context, &e),
        "single_print" => eval_core_proc_single_print(context, &e),
        "print_flush" => eval_core_proc_print_flush(context, &e),
        "readfile" => eval_core_proc_readfile(context, &e),
        "runfile" => eval_core_proc_runfile(context, &e),
        _ => {
            if is_proc {
                Err(e.lang_error("eval", &format!("Core procedure '{}' not implemented.", name)))
            } else {
                Err(e.lang_error("eval", &format!("Core function '{}' not implemented.", name)))
            }
        },
    }
}

fn eval_func_proc_call(name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.node_type != NodeType::FCall {
        return Err(e.lang_error("eval", "eval_func_proc_call: Expected FCall node type"));
    }
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Err(e.lang_error("eval", "eval_func_proc_call: Expected FCall with at least one param for the Identifier")),
    };

    if context.struct_defs.contains_key(name) {
        // TODO allow instantiations with arguments
        let id_expr = e.get(0)?;
        if id_expr.params.len() == 0 {
            let id_name = match &id_expr.node_type {
                NodeType::Identifier(s) => s,
                _ => return Err(e.todo_error("eval", "Expected identifier name for struct instantiation")),
            };
            context.insert_struct(&id_name, &name, e)?;
            return Ok(EvalResult::new(match id_name.as_str() {
                "Bool" => "false",
                "U8" | "I64" => "0",
                "Str" => "",
                _ => id_name, // TODO Where is the struct being inserted in this case? Is this returned value even used?
            }))
        }
    }

    let combined_name = &get_combined_name(func_expr)?;
    let mut new_fcall_e = e.clone();
    let func_def = match get_func_def_for_fcall_with_expr(&context, &mut new_fcall_e)? {
        Some(func_def_) => func_def_,
        None  => {
            return Err(e.lang_error("eval", "eval_func_proc_call: Instantiations should be handled already"))
        },
    };
    if func_def.is_ext() {
        // External/core functions are treated specially
        let is_proc = func_def.is_proc();
        let parts: Vec<&str> = combined_name.split('.').collect();
        let last_name = match parts.last() {
            Some(last_name_) => last_name_,
            None => {
                return Err(e.lang_error("eval", "Somehow function without name"))
            }
        };
        return eval_core_func_proc_call(&last_name, context, &new_fcall_e, is_proc)
    }
    return eval_user_func_proc_call(&func_def, &combined_name, context, &new_fcall_e)
}

fn eval_declaration(declaration: &Declaration, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let inner_e = e.get(0)?;
    let mut value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error("eval", &error_string));
        },
    };
    if declaration.value_type != ValueType::TCustom(INFER_TYPE.to_string()) {
        if declaration.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
            value_type = declaration.value_type.clone();
        } else if value_type != declaration.value_type {
            return Err(e.lang_error("eval", &format!("'{}' declared of type {} but initialized to type {:?}.", declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type))));
        }
    }

    if e.params.len() != 1 {
        return Err(e.lang_error("eval", "Declarations can have only one child expression"))
    }

    match value_type {
        ValueType::TCustom(s) if s == INFER_TYPE => {
            return Err(e.lang_error("eval", &format!("'{}' declared of type '{}' but still to infer type '{}'",
                                                     declaration.name, value_type_to_str(&declaration.value_type), &s)));
        },
        ValueType::TType(TTypeDef::TEnumDef) => {
            match &inner_e.node_type {
                NodeType::EnumDef(enum_def) => {
                    context.enum_defs.insert(declaration.name.clone(), enum_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error("eval", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                              &declaration.name, value_type_to_str(&declaration.value_type)))),
            }
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            match &inner_e.node_type {
                NodeType::StructDef(struct_def) => {
                    context.struct_defs.insert(declaration.name.to_string(), struct_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    for (_, member_decl) in &struct_def.members {
                        if !member_decl.is_mut {
                            let combined_name = format!("{}.{}", declaration.name, member_decl.name);
                            let default_value = match struct_def.default_values.get(&member_decl.name) {
                                Some(_default_value) => _default_value,
                                None => {
                                    return Err(e.lang_error("eval", &format!("Struct member '{}.{}' expected to have default value.",
                                                                             &declaration.name, &member_decl.name)));
                                },
                            };
                            let member_value_type = match &member_decl.value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    match get_value_type(&context, &default_value) {
                                        Ok(val_type) => val_type,
                                        Err(error_string) => {
                                            return Err(e.lang_error("eval", &error_string));
                                        },
                                    }
                                },
                                _ => member_decl.value_type.clone(),
                            };

                            match member_value_type {
                                ValueType::TCustom(s) if s == INFER_TYPE => {
                                    return Err(e.lang_error("eval", &format!("Cannot infer type of '{}.{}', but it should be inferred already.",
                                                                             &declaration.name, &member_decl.name)));
                                },
                                ValueType::TCustom(type_name) => {
                                    let result = eval_expr(context, default_value)?;
                                    if result.is_throw {
                                        return Ok(result); // Propagate throw
                                    }
                                    let expr_result_str = result.value;
                                    match type_name.as_str() {
                                        "I64" => {
                                            context.insert_i64(&combined_name, &expr_result_str, e)?;
                                        },
                                        "U8" => {
                                            context.insert_u8(&combined_name, &expr_result_str, e)?;
                                        },
                                        "Bool" => {
                                            context.insert_bool(&combined_name, &expr_result_str, e)?;
                                        },
                                        "Str" => {
                                            context.insert_string(&combined_name, &expr_result_str, e)?;
                                        },
                                        _ => {
                                            return Err(e.todo_error("eval", &format!("Cannot declare '{}.{}' of custom type '{}'",
                                                                                     &declaration.name,
                                                                                     &member_decl.name,
                                                                                     type_name)));
                                        },
                                    }
                                },
                                ValueType::TFunction(_) => {
                                    match &default_value.node_type {
                                        NodeType::FuncDef(func_def) => {
                                            context.funcs.insert(combined_name.to_string(), func_def.clone());
                                        },
                                        _ => {
                                            return Err(e.lang_error("eval", &format!("Cannot declare '{}.{}' of type '{}', expected '{}' definition.",
                                                                                     &declaration.name,
                                                                                     &member_decl.name,
                                                                                     value_type_to_str(&member_value_type),
                                                                                     value_type_to_str(&member_decl.value_type))));
                                        },
                                    }
                                },
                               _ => {
                                    return Err(e.todo_error("eval", &format!("Cannot declare '{}.{}' of type '{}'",
                                                                             &declaration.name,
                                                                             &member_decl.name,
                                                                             value_type_to_str(&member_decl.value_type))));
                                },
                            }

                            context.symbols.insert(combined_name.to_string(),
                                                   SymbolInfo{value_type: member_decl.value_type.clone(), is_mut: member_decl.is_mut});
                        }
                    }
                    return Ok(EvalResult::new(""));
                },
                _ => return Err(e.lang_error("eval", &format!("Cannot declare {} of type {:?}, expected struct definition.",
                                                              &declaration.name, &declaration.value_type))),
            }
        },
        ValueType::TFunction(_) => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(declaration.name.to_string(), func_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return Ok(EvalResult::new(""))
                },

                _ => return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}', expected '{}' definition.",
                                                         &declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type)))),
            }
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_i64(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                "U8" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_u8(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                "Bool" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_bool(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_string(&declaration.name, &expr_result_str, e)?;
                    return Ok(EvalResult::new(""))
                },
                _ => {
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    let custom_symbol = match context.symbols.get(custom_type_name) {
                        Some(sym) => sym,
                        None => return Err(e.lang_error("eval", &format!("Symbol '{}' not found in context", custom_type_name))),
                    };
                    if custom_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                        let result = eval_expr(context, inner_e)?;
                        if result.is_throw {
                            return Ok(result); // Propagate throw
                        }
                        let enum_expr_result_str = &result.value;
                        context.insert_enum(&declaration.name, custom_type_name, enum_expr_result_str, e)?;

                    } else if custom_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        // Special case for instantiation
                        if inner_e.node_type == NodeType::FCall && inner_e.params.len() == 1 {
                            if let NodeType::Identifier(potentially_struct_name) = &inner_e.params[0].node_type {
                                if inner_e.params[0].params.is_empty() {
                                    if context.struct_defs.contains_key(potentially_struct_name) {
                                        context.insert_struct(&declaration.name, custom_type_name, e)?;
                                        return Ok(EvalResult::new(""))
                                    }
                                }
                            }
                        }
                        // otherwise continue, it's a function that returns a struct
                        let result = eval_expr(context, inner_e)?;
                        if result.is_throw {
                            return Ok(result); // Propagate throw
                        }
                        let expr_result_str = result.value;
                        if let Some(offset) = context.arena_index.get(&expr_result_str) {
                            context.arena_index.insert(declaration.name.to_string(), *offset);
                        } else {
                            return Err(e.lang_error("eval", &format!("Could not find arena index for '{}'", expr_result_str)));
                        }
                        context.map_instance_fields(custom_type_name, &declaration.name, e)?;
                    } else {
                        return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}'. Only 'enum' and 'struct' custom types allowed.",
                                                            &declaration.name, value_type_to_str(&custom_symbol.value_type))))
                    }
                    return Ok(EvalResult::new(""))
                },
            }
        },
        ValueType::TMulti(_) => {
            return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}'",
                                                &declaration.name, value_type_to_str(&declaration.value_type))))
        },
    }
}

fn eval_assignment(var_name: &str, context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let symbol_info = match context.symbols.get(var_name) {
        Some(sym) => sym,
        None => return Err(e.lang_error("eval", &format!("Symbol '{}' not found in context", var_name))),
    };
    if !symbol_info.is_mut {
        return Err(e.lang_error("eval", &format!("in eval_assignment, while assigning to '{}': Assignments can only be to mut values. Offending expr: {:?}", var_name, e)));
    }
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", &format!("in eval_assignment, while assigning to '{}': assignments must take exactly one value", var_name)));
    }

    let inner_e = e.get(0)?;
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error("eval", &error_string));
        },
    };
    match value_type {
        ValueType::TCustom(s) if s == INFER_TYPE => {
            return Err(e.lang_error("eval", &format!("Cannot assign {}, type should already be inferred of type '{:?}'.", &var_name, &symbol_info.value_type)));
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_i64(var_name, &expr_result_str, e)?;
                },
                "U8" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_u8(var_name, &expr_result_str, e)?;
                },
                "Bool" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_bool(var_name, &expr_result_str, e)?;
                },
                "Str" => {
                    let result = eval_expr(context, inner_e)?;
                    if result.is_throw {
                        return Ok(result); // Propagate throw
                    }
                    let expr_result_str = result.value;
                    context.insert_string(var_name, &expr_result_str, e)?;
                },
                _ => {
                    let custom_symbol_info = match context.symbols.get(custom_type_name) {
                        Some(symbol_info) => symbol_info,
                        None => return Err(inner_e.lang_error("eval", &format!("Unknown custom type '{}'", custom_type_name))),
                    };
                    match &custom_symbol_info.value_type {
                        ValueType::TType(TTypeDef::TEnumDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            context.insert_enum(var_name, &custom_type_name, &expr_result_str, e)?;
                        },
                        ValueType::TType(TTypeDef::TStructDef) => {
                            let result = eval_expr(context, inner_e)?;
                            if result.is_throw {
                                return Ok(result); // Propagate throw
                            }
                            let expr_result_str = result.value;
                            context.copy_fields(custom_type_name, &expr_result_str, var_name, inner_e)?;
                        },
                        other_value_type => {
                            return Err(inner_e.lang_error("eval", &format!("Cannot assign '{}' of custom type '{}' of value type '{}'.",
                                                                           &var_name, custom_type_name, value_type_to_str(&other_value_type))))
                        },
                    }
                },
            }
            return Ok(EvalResult::new(""))
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            return Err(e.todo_error("eval", &format!("Cannot assign '{}' of type '{}'", &var_name, value_type_to_str(&value_type))))
        },
        ValueType::TFunction(_) => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(var_name.to_string(), func_def.clone());
                    Ok(EvalResult::new(""))
                },
                _ => Err(e.lang_error("eval", &format!("Cannot assign '{}' to function type '{}'",
                                                       &var_name, value_type_to_str(&value_type)))),
            }
        },

        ValueType::TType(TTypeDef::TEnumDef) | ValueType::TMulti(_) => {
            Err(e.lang_error("eval", &format!("Cannot assign '{}' of type '{}'.", &var_name, value_type_to_str(&value_type))))
        },
    }
}

fn eval_identifier_expr_struct_member(name: &str, inner_name: &str, context: &Context, inner_e: &Expr, member_decl: &Declaration) -> Result<EvalResult, String> {
    return match member_decl.value_type {
        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let result = context.get_i64(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "U8" => {
                    let result = context.get_u8(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "Bool" => {
                    let result = context.get_bool(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                "Str" => {
                    let result = context.get_string(&format!("{}.{}", name, inner_name), inner_e)?;
                    return Ok(EvalResult::new(&result.to_string()))
                },
                _ => Err(inner_e.lang_error("eval", &format!("evaluating member '{}.{}' of custom type '{}' is not supported yet",
                                                             name, inner_name, value_type_to_str(&member_decl.value_type)))),
            }
        },
        _ => Err(inner_e.lang_error("eval", &format!("struct '{}' has no const (static) member '{}' of struct value type '{}'",
                                                     name, inner_name, value_type_to_str(&member_decl.value_type)))),
    }
}

fn eval_identifier_expr_struct(name: &str, context: &Context, e: &Expr) -> Result<EvalResult, String> {
    let struct_def = match context.struct_defs.get(name) {
        Some(def) => def,
        None => return Err(e.lang_error("eval", &format!("Struct '{}' not found in context", name))),
    };
    let inner_e = e.get(0)?;
    match &inner_e.node_type {
        NodeType::Identifier(inner_name) => {
            match struct_def.members.iter().find(|(k, _)| k == inner_name).map(|(_, v)| v) {
                Some(member_decl) => {
                    return eval_identifier_expr_struct_member(name, inner_name, context, inner_e, member_decl);
                },
                None => {
                    return Err(e.lang_error("eval", &format!("struct '{}' has no member '{}' j", name, inner_name)));
                },
            }
        },
        _ => {
            return Err(e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name)));
        },
    }
}

fn eval_custom_expr(e: &Expr, context: &Context, name: &str, custom_type_name: &str) -> Result<EvalResult, String> {
    let custom_symbol = match context.symbols.get(custom_type_name) {
        Some(sym) => sym,
        None => return Err(e.lang_error("eval", &format!("Argument '{}' is of undefined type {}.", name, custom_type_name))),
    };
    match custom_symbol.value_type {
        ValueType::TType(TTypeDef::TEnumDef) => {
            let enum_val = context.get_enum(name, e)?;
            return Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name)))
        },
        ValueType::TType(TTypeDef::TStructDef) => {
            if e.params.len() == 0 {
                return Ok(EvalResult::new(name));
            }

            let mut current_name = name.to_string();
            let mut current_type = ValueType::TCustom(custom_type_name.to_string());

            for inner_e in &e.params {
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        match current_type {
                            ValueType::TType(TTypeDef::TStructDef) => {
                                return Err(inner_e.todo_error("eval", &format!("'{}': StructDef cannot be a field yet", current_name)));
                            },
                            ValueType::TCustom(ref custom_type_name) => {
                                if let Some(custom_symbol) = context.symbols.get(custom_type_name) {
                                    match custom_symbol.value_type {
                                        ValueType::TType(TTypeDef::TStructDef) => {
                                            let struct_def = match context.struct_defs.get(custom_type_name) {
                                                Some(def) => def,
                                                None => return Err(e.lang_error("eval", &format!("Struct '{}' not found in context", custom_type_name))),
                                            };
                                            match struct_def.members.iter().find(|(k, _)| k == inner_name).map(|(_, v)| v) {
                                                Some(member_decl) => {
                                                    current_type = member_decl.value_type.clone();
                                                    current_name = format!("{}.{}", current_name, inner_name);
                                                },
                                                None => return Err(inner_e.lang_error("eval", &format!("Struct '{}' has no member '{}' k", value_type_to_str(&current_type), inner_name))),
                                            }
                                        },
                                        ValueType::TType(TTypeDef::TEnumDef) => {
                                            return Err(inner_e.lang_error("eval", &format!("Enum '{}' does not support nested members", current_name)));
                                        },
                                        _ => return Err(inner_e.lang_error("eval", "Custom types cannot have nested members")),
                                    }
                                } else {
                                    return Err(inner_e.lang_error("eval", &format!("Custom type '{}' not found in symbols", custom_type_name)));
                                }
                            },
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                return Err(inner_e.lang_error("eval", &format!("Enum '{}' does not support nested members", current_name)));
                            },
                            _ => return Err(inner_e.lang_error("eval", &format!("Unexpected type for '{}', cannot access member '{}'", current_name, inner_name))),
                        }
                    },
                    _ => return Err(inner_e.lang_error("eval", &format!("Expected identifier, found {:?}", inner_e.node_type))),
                }
            }

            let inner_e = match e.params.last() {
                Some(expr) => expr,
                None => return Err(e.lang_error("eval", "eval_custom_expr: Expected at least one parameter")),
            };
            match current_type {
                ValueType::TCustom(ref custom_type_name) => {
                    match custom_type_name.as_str() {
                        "I64" => match context.get_i64(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "U8" => match context.get_u8(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "Bool" => match context.get_bool(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        "Str" => match context.get_string(&current_name, e)? {
                            result => Ok(EvalResult::new(&result.to_string())),
                        },
                        _ => {
                            let custom_type_name = &value_type_to_str(&current_type);
                            let custom_symbol_info = match context.symbols.get(custom_type_name) {
                                Some(symbol_info) => symbol_info,
                                None => return Err(inner_e.lang_error("eval", &format!("Unknown custom type '{}'", custom_type_name))),
                            };
                            match &custom_symbol_info.value_type {
                                ValueType::TType(TTypeDef::TEnumDef) => {
                                    let enum_val = context.get_enum(&current_name, inner_e)?;
                                    return Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name)))
                                },
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    return Ok(EvalResult::new(&current_name))
                                },
                                _ => Err(inner_e.todo_error("eval", &format!("Cannot access '{}'. Fields of custom type '{}' not implemented", current_name, custom_type_name))),
                            }
                        },
                    }
                },
                _ => Err(e.lang_error("eval", &format!("Invalid type for '{}'.", current_name))),
            }
        },
        _ => Err(e.lang_error("eval", &format!("'{}' of type: '{}': custom types are supposed to be struct or enum, found '{}'.", name, custom_type_name, value_type_to_str(&custom_symbol.value_type)))),
    }
}

fn eval_identifier_expr(name: &str, context: &Context, e: &Expr) -> Result<EvalResult, String> {
    match context.symbols.get(name) {
        Some(symbol_info) => match &symbol_info.value_type {
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                return Ok(EvalResult::new(name));
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                // let enum_def = match context.enum_defs.get(name) {
                //     Some(def) => def,
                //     None => return Err(e.lang_error("eval", &format!("Enum '{}' not found in context", name))),
                // };
                let inner_e = e.get(0)?;
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        // TODO check that inner_name is in enum_def
                        // TODO check if that inner_name has an optional type
                        return Ok(EvalResult::new(&format!("{}.{}", name, inner_name)));
                    },
                    _ => {
                        return Err(e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name)));
                    },
                }
            },
            ValueType::TType(TTypeDef::TStructDef) => {
                return eval_identifier_expr_struct(name, context, e)
            }
            ValueType::TCustom(s) if s == INFER_TYPE => {
                return Err(e.lang_error("eval", &format!("Can't infer the type of identifier '{}'.", name)));
            },
            ValueType::TCustom(ref custom_type_name) => {
                match custom_type_name.as_str() {
                    "I64" => {
                        let val = context.get_i64(name, e)?;
                        return Ok(EvalResult::new(&val.to_string()))
                    },
                    "U8" => {
                        let val = context.get_u8(name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Bool" => {
                        let val = context.get_bool(name, e)?;
                        return Ok(EvalResult::new(&val.to_string()));
                    },
                    "Str" => {
                        if e.params.len() == 0 {
                            let val = context.get_string(name, e)?;
                            return Ok(EvalResult::new(&val.to_string()));
                        }
                        return eval_custom_expr(e, context, name, custom_type_name);
                    },
                    _ => {
                        return eval_custom_expr(e, context, name, custom_type_name);
                    },
                }
            },
            _ => {
                return Err(e.todo_error("eval", &format!("Can't use identifier '{}'. Type {:?} not supported yet.", name, symbol_info.value_type)));
            },
        },
        None => {
            return Err(e.lang_error("eval", &format!("Undefined symbol '{}'. This should have been caught in the compile phase.", name)));
        },
    }
}

fn eval_body(mut context: &mut Context, statements: &Vec<Expr>) -> Result<EvalResult, String> {
    let mut i = 0;
    let mut pending_throw: Option<EvalResult> = None;

    while i < statements.len() {
        let stmt = &statements[i];

        if let Some(throw_result) = &pending_throw {
            if let NodeType::Catch = stmt.node_type {
                if stmt.params.len() == 3 {
                    let type_expr = &stmt.params[1];
                    let type_name = match &type_expr.node_type {
                        NodeType::Identifier(name) => name,
                        _ => return Err(stmt.lang_error("eval", "Catch type must be an identifier")),
                    };
                    if let Some(thrown_type) = &throw_result.thrown_type {
                        if type_name == thrown_type {
                            let body_expr = &stmt.params[2];
                            let result = eval_body(&mut context, &body_expr.params)?;
                            if result.is_return {
                                return Ok(result);
                            } else if result.is_throw {
                                pending_throw = Some(result);
                            } else {
                                pending_throw = None;
                            }
                        }
                    }
                }
            }
        } else {
            // If no pending throw, ignore catch statements
            if NodeType::Catch != stmt.node_type {
                let result = eval_expr(&mut context, stmt)?;
                if result.is_return {
                    return Ok(result);
                } else if result.is_throw {
                    pending_throw = Some(result);
                }
            }
        }

        i += 1;
    }

    if let Some(final_throw) = pending_throw {
        return Ok(final_throw);
    }

    Ok(EvalResult::new(""))
}

fn eval_expr(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match &e.node_type {
        NodeType::Body => eval_body(context, &e.params),
        NodeType::LLiteral(Literal::Bool(lbool)) => Ok(EvalResult::new(lbool)),
        NodeType::LLiteral(Literal::Number(li64)) => Ok(EvalResult::new(li64)),
        NodeType::LLiteral(Literal::Str(lstring)) => Ok(EvalResult::new(lstring)),
        NodeType::LLiteral(Literal::List(llist)) => Ok(EvalResult::new(llist)),
        NodeType::FCall => {
            let f_name = get_func_name_in_call(&e);
            eval_func_proc_call(&f_name, context, &e)
        },
        NodeType::Declaration(declaration) => {
            eval_declaration(&declaration, context, &e)
        },
        NodeType::Assignment(var_name) => {
            eval_assignment(&var_name, context, &e)
        },
        NodeType::Identifier(name) => eval_identifier_expr(&name, &context, &e),
        NodeType::If => {
            if e.params.len() != 2 && e.params.len() != 3 {
                return Err(e.lang_error("eval", "if nodes must have 2 or 3 parameters."))
            }
            let cond_expr = e.get(0)?;
            let result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond)
            }
            if result_cond.value.parse::<bool>().map_err(
                |err| cond_expr.lang_error("eval", &format!("Expected bool, got '{}': {}", result_cond.value, err)))? {
                return eval_expr(context, e.get(1)?)
            } else if e.params.len() == 3 {
                return eval_expr(context, e.get(2)?)
            } else {
                return Ok(EvalResult::new(""))
            }
        },
        NodeType::While => {
            if e.params.len() != 2 {
                return Err(e.lang_error("eval", "while nodes must have exactly 2 parameters."))
            }
            let mut cond_expr = e.get(0)?;
            let mut result_cond = eval_expr(context, cond_expr)?;
            if result_cond.is_throw {
                return Ok(result_cond.clone())
            }
            while result_cond.value.parse::<bool>().map_err(
                |err| cond_expr.lang_error("eval", &format!("Expected bool, got '{}': {}", result_cond.value, err)))? {
                let result = eval_expr(context, e.get(1)?)?;
                if result.is_return || result.is_throw {
                    return Ok(result)
                }
                cond_expr = e.get(0)?;
                result_cond = eval_expr(context, cond_expr)?;
                if result_cond.is_throw {
                    return Ok(result_cond)
                }
            }
            Ok(EvalResult::new(""))
        },
        NodeType::Switch => {
            if e.params.len() < 3 {
                return Err(e.lang_error("eval", "switch nodes must have at least 3 parameters."));
            }
            let to_switch = e.get(0)?;
            let value_type = get_value_type(&context, &to_switch)?;
            let result_to_switch = eval_expr(context, &to_switch)?;
            if result_to_switch.is_throw {
                return Ok(result_to_switch);
            }

            let mut param_it = 1;
            while param_it < e.params.len() {
                let case = e.get(param_it)?;
                if case.node_type == NodeType::DefaultCase {
                    param_it += 1;
                    return eval_expr(context, e.get(param_it)?);
                }

                let case_type = get_value_type(&context, &case)?;
                let vt_str = value_type_to_str(&value_type);
                let ct_str = value_type_to_str(&case_type);
                if ct_str != vt_str && ct_str != format!("{}Range", vt_str) {
                    return Err(e.lang_error("eval", &format!("switch value type {:?}, case value type {:?}", value_type, case_type)));
                }

                let is_match = match &case.node_type {
                    NodeType::Range => {
                        let start = eval_expr(context, &case.params[0])?;
                        if start.is_throw {
                            return Ok(start);
                        }
                        let end = eval_expr(context, &case.params[1])?;
                        if end.is_throw {
                            return Ok(end);
                        }
                        match &value_type {
                            ValueType::TCustom(s) if s == "I64" || s == "U8" => {
                                let val = result_to_switch.value.parse::<i64>();
                                let start_val = start.value.parse::<i64>();
                                let end_val = end.value.parse::<i64>();

                                if let (Ok(val), Ok(start_val), Ok(end_val)) = (val, start_val, end_val) {
                                    val >= start_val && val <= end_val
                                } else {
                                    false
                                }
                            }
                            _ => {
                                // Lexicographical comparisons for Str
                                result_to_switch.value >= start.value && result_to_switch.value <= end.value
                            }
                        }
                    }
                    _ => {
                        let result_case = eval_expr(context, &case)?;
                        if result_case.is_throw {
                            return Ok(result_case);
                        }
                        result_to_switch.value == result_case.value
                    }
                };

                param_it += 1;
                if is_match {
                    return eval_expr(context, e.get(param_it)?);
                }
                param_it += 1;
            }
            return Ok(EvalResult::new(""))
        },
        NodeType::Return => {
            if e.params.len() == 0 {
                return Ok(EvalResult::new_return(""))
            } else if e.params.len() > 1 {
                return Err(e.lang_error("eval", "multiple return values not implemented yet"))
            } else {
                let result = eval_expr(context, e.get(0)?)?;
                if result.is_throw {
                    return Ok(result)
                }
                return Ok(EvalResult::new_return(&result.value))
            }
        },
        NodeType::Throw => {
            if e.params.len() != 1 {
                return Err(e.lang_error("eval", "Throw can only return one value. This should have been caught before"))
            } else {
                let param_expr = e.get(0)?;
                let result = eval_expr(context, param_expr)?;
                if result.is_throw {
                    return Ok(result)
                }
                let thrown_type = get_value_type(context, param_expr)?;
                return Ok(EvalResult::new_throw(&result.value, thrown_type))
            }
        },
        NodeType::Catch => {
            return Err(e.lang_error("eval", "Catch statements should always be evaluated within bodies."))
        },
        _ => Err(e.lang_error("eval", &format!("Not implemented yet, found node type {:?}.", e.node_type))),
    }
}

// ---------- to ast (aka code_gen lisp-like syntax)

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
            let f_name = get_func_name_in_call(&e);
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

fn main_run(print_extra: bool, context: &mut Context, path: &String, source: String, main_args: Vec<String>) -> Result<EvalResult, String> {

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
        match eval_core_proc_import(context, &import_fcall_expr) {
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

    let mut errors = init_context(context, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return Err(format!("Compiler errors: {} declaration errors found", errors.len()));
    }
    errors.extend(basic_mode_checks(&context, &e));

    // For modes that require a main proc, add an implicit call to main
    if context.mode.needs_main_proc {
        let mut main_params = Vec::new();
        main_params.push(Expr{node_type: NodeType::Identifier("main".to_string()), line: 0, col: 0, params: Vec::new()});
        for str_arg in main_args {
            main_params.push(Expr{node_type: NodeType::LLiteral(Literal::Str(str_arg)), line: 0, col: 0, params: Vec::new()});
        }
        e.params.push(Expr{node_type: NodeType::FCall, line: 0, col: 0, params: main_params});
    }
    errors.extend(check_types(context, &e));

    // Check throw/catch and return things in the root body of the file (for modes script and test, for example)
    let func_def = SFuncDef{args: vec![], body: vec![], function_type: FunctionType::FTProc, returns: vec![], throws: vec![]};
    let mut thrown_types = vec![];
    let mut return_found = false;
    errors.extend(check_body_returns_throws(context, &e, &func_def, e.params.as_slice(), &mut thrown_types, &mut return_found));

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

    return match eval_expr(context, &e) {
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
        eval_core_proc_import(&mut context, &import_fcall_expr)?;
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
    let run_result = main_run(!is_import, context, &path, source, main_args)?;

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
