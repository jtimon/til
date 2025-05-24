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
const SELF_HOSTED_PATH     : &str = "src/cil.cil";
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
// static mut ARENA: Vec<u8> = vec![0]; // Apparently we can't use a global without having to put "unsafe" everywhere
impl Arena {
    // This function gives access to the singleton instance of Arena
    fn g() -> &'static mut Arena {
        unsafe { // TODO research if we can do "safe" singletons in rust before self hosting, just out of curiosity
            static mut INSTANCE: Option<Arena> = None;

            // Lazy initialization of the singleton instance
            if INSTANCE.is_none() {
                INSTANCE = Some(Arena {
                    memory: vec![0], // REM: first address 0 is reserved (invalid), malloc always >0
                    temp_id_counter: 0, // A temporary ugly hack for return values
                });
            }

            // Unwrap the instance and return a mutable reference
            return INSTANCE.as_mut().unwrap()
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
}

impl Context {
    fn new(path: &String, mode_name: &str) -> Context {
        return Context {
            path: path.to_string(),
            mode: mode_from_name(mode_name).unwrap(),
            symbols: HashMap::new(),
            funcs: HashMap::new(),
            enum_defs: HashMap::new(),
            struct_defs: HashMap::new(),
            arena_index: HashMap::new(),
        };
    }

    fn get_i64(self: &Context, id: &str) -> Option<i64> {
        return match self.arena_index.get(id) {
            Some(&offset) => Some(i64::from_ne_bytes(Arena::g().memory[offset..offset + 8].try_into().unwrap())),
            None => None,
        }
    }

    fn insert_i64(self: &mut Context, id: &str, i64_str: &String) -> Option<i64> {
        let v = i64_str.parse::<i64>().unwrap();
        let bytes = v.to_ne_bytes();

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                let old_value = i64::from_ne_bytes(Arena::g().memory[offset..offset + 8].try_into().unwrap());
                Arena::g().memory[offset..offset + 8].copy_from_slice(&bytes);
                return Some(old_value);
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&bytes);
                self.arena_index.insert(id.to_string(), offset);
                return None;
            }
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(&bytes);
        return self.arena_index.insert(id.to_string(), offset).map(|old_offset| i64::from_ne_bytes(Arena::g().memory[old_offset..old_offset + 8].try_into().unwrap()));
    }

    fn get_u8(self: &Context, id: &str) -> Option<u8> {
        return match self.arena_index.get(id) {
            Some(&offset) => Some(Arena::g().memory[offset]),
            None => None,
        }
    }

    fn insert_u8(self: &mut Context, id: &str, u8_str: &String) -> Option<u8> {
        let v = u8_str.parse::<u8>().unwrap();

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                let old = Arena::g().memory[offset];
                Arena::g().memory[offset] = v;
                return Some(old);
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.push(v);
                self.arena_index.insert(id.to_string(), offset);
                return None;
            }
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.push(v);
        return self.arena_index.insert(id.to_string(), offset).map(|old_offset| Arena::g().memory[old_offset]);
    }

    fn get_bool(self: &Context, id: &str) -> Option<bool> {
        return match self.arena_index.get(id) {
            Some(&offset) => Some(Arena::g().memory[offset] == 0),
            None => None,
        }
    }

    fn insert_bool(self: &mut Context, id: &str, bool_str: &String) -> Option<bool> {
        let is_mut = match self.symbols.get(id) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return None,
        };
        let bool_to_insert = bool_str.parse::<bool>().unwrap();
        let stored = if bool_to_insert { 0 } else { 1 }; // TODO why this is backwards?

        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                let old = Arena::g().memory[offset];
                Arena::g().memory[offset] = stored;
                return Some(old == 0);
            } else {
                let offset = Arena::g().memory.len();
                Arena::g().memory.push(stored);
                self.arena_index.insert(id.to_string(), offset);
                return None;
            }
        }

        let offset = Arena::g().memory.len();
        Arena::g().memory.push(stored);

        // Insert Bool data field too
        let field_id = format!("{}.data", id);
        self.symbols.insert(field_id.clone(), SymbolInfo {
            value_type: ValueType::TCustom("U8".to_string()),
            is_mut: is_mut,
        });
        self.arena_index.insert(field_id, offset);

        return self.arena_index.insert(id.to_string(), offset).map(|old_offset| Arena::g().memory[old_offset] == 0);
    }

    fn map_instance_fields(&mut self, custom_type_name: &str, instance_name: &str) -> bool {
        let struct_def = match self.struct_defs.get(custom_type_name) {
            Some(def) => def,
            None => return false,
        };

        let is_mut = match self.symbols.get(instance_name) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return false,
        };

        let base_offset = match self.arena_index.get(instance_name) {
            Some(offset) => *offset,
            None => return false,
        };

        let members: Vec<(String, Declaration)> = struct_def
            .members
            .iter()
            .map(|(k, v)| (k.clone(), v.clone()))
            .collect();

        let mut current_offset = 0;
        for (field_name, decl) in members {
            if decl.is_mut {
                let combined_name = format!("{}.{}", instance_name, field_name);
                self.arena_index.insert(combined_name.to_string(), base_offset + current_offset);
                self.symbols.insert(
                    combined_name.clone(),
                    SymbolInfo {
                        value_type: decl.value_type.clone(),
                        is_mut: is_mut,
                    },
                );

                if let ValueType::TCustom(type_name) = &decl.value_type {
                    if self.struct_defs.contains_key(type_name) {
                        if !self.map_instance_fields(type_name, &combined_name) {
                            println!("ERROR: Failed to map nested struct field '{}'", combined_name);
                            return false;
                        }
                    }
                }

                let field_size = match &decl.value_type {
                    ValueType::TCustom(name) => match self.get_type_size(name) {
                        Ok(size) => size,
                        Err(_) => return false,
                    },
                    _ => return false,
                };

                current_offset += field_size;
            }
        }

        return true
    }

    // TODO all args should be passed as pointers/references and we wouldn't need this
    fn copy_fields(self: &mut Context, custom_type_name: &str, src: &str, dest: &str) -> bool {
        let struct_def = match self.struct_defs.get(custom_type_name) {
            Some(def) => def,
            None => return false,
        };

        let is_mut = match self.symbols.get(dest) {
            Some(info) => info.is_mut,
            None => return false,
        };

        let dest_base_offset = match self.arena_index.get(dest) {
            Some(offset) => *offset,
            None => return false,
        };

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
                ValueType::TCustom(name) => match self.get_type_size(name.as_str()) {
                    Ok(size) => size,
                    Err(_) => return false,
                },
                _ => return false,
            };

            let src_key = format!("{}.{}", src, field_name);
            let dest_key = format!("{}.{}", dest, field_name);

            let src_offset = match self.arena_index.get(&src_key) {
                Some(offset) => *offset,
                None => return false,
            };

            let dest_offset = dest_base_offset + current_offset;

            // Ensure mappings for the destination field
            self.arena_index.insert(dest_key.clone(), dest_offset);
            self.symbols.insert(dest_key.clone(), SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut,
            });

            // Copy the actual memory bytes
            Arena::g().memory.copy_within(src_offset..src_offset + field_size, dest_offset);

            if let ValueType::TCustom(type_name) = &decl.value_type {
                if self.struct_defs.contains_key(type_name.as_str()) {
                    if !self.copy_fields(type_name.as_str(), &src_key, &dest_key) {
                        println!("ERROR: Failed to recursively copy field '{}'", dest_key);
                        return false;
                    }
                }
            }

            current_offset += field_size;
        }

        return true
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

    fn insert_struct(self: &mut Context, id: &str, custom_type_name: &str) -> bool {
        // Lookup the struct definition
        let struct_def = match self.struct_defs.get(custom_type_name) {
            Some(struct_def_) => struct_def_.clone(),
            None => return false,
        };

        // Determine mutability from symbols table
        let is_mut = match self.symbols.get(id) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => {
                println!("ERROR: insert_struct: id '{}' for struct '{}' not found in symbols", id, custom_type_name);
                return false
            },
        };

        // Calculate total size (for now no alignment)
        let mut total_size = 0;
        let mut field_offsets = HashMap::new();

        for (member_name, decl) in struct_def.members.iter() {
            if !decl.is_mut {
                continue; // skip non-mut fields
            }

            let field_size = match &decl.value_type {
                ValueType::TCustom(type_name) => {
                    match self.get_type_size(type_name) {
                        Ok(type_size) => type_size,
                        Err(msg) => {
                            println!("ERROR: {}", msg);
                            return false;
                        },
                    }
                },
                _ => {
                    println!("ERROR: Unsupported value type in struct");
                    return false;
                }
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

            let field_offset = field_offsets.get(member_name).unwrap();

            let default_expr = struct_def.default_values.get(member_name);
            let default_value = match default_expr {
                Some(e) => eval_expr(self, e).unwrap().value,
                None => {
                    println!("ERROR: Missing default value for field '{}'", member_name);
                    return false;
                }
            };

            match &decl.value_type {
                ValueType::TCustom(type_name) => {
                    if let Some(enum_def) = self.enum_defs.get(type_name) {
                        // Handle enums properly
                        let parts: Vec<&str> = default_value.split('.').collect();
                        if parts.len() != 2 || parts[0] != type_name {
                            println!("ERROR: Invalid enum default value '{}' for field '{}'", default_value, member_name);
                            return false;
                        }
                        let variant = parts[1];
                        let index = match enum_def.enum_map.keys().position(|v| v == variant) {
                            Some(i) => i as i64,
                            None => {
                                println!("ERROR: Unknown enum variant '{}' in default value for field '{}'", variant, member_name);
                                return false;
                            }
                        };
                        let bytes = index.to_ne_bytes();
                        Arena::g().memory[offset + field_offset..offset + field_offset + 8].copy_from_slice(&bytes);
                    } else {
                        match type_name.as_str() {
                            "U8" => {
                                let v = match default_value.parse::<u8>() {
                                    Ok(val) => val,
                                    Err(_) => {
                                        println!("ERROR: Invalid U8 default value '{}' for field '{}'", default_value, member_name);
                                        return false;
                                    }
                                };
                                Arena::g().memory[offset + field_offset] = v;
                            },
                            "I64" => {
                                let v = match default_value.parse::<i64>() {
                                    Ok(val) => val,
                                    Err(_) => {
                                        println!("ERROR: Invalid I64 default value '{}' for field '{}'", default_value, member_name);
                                        return false;
                                    }
                                };
                                let bytes = v.to_ne_bytes();
                                Arena::g().memory[offset + field_offset..offset + field_offset + 8].copy_from_slice(&bytes);
                            },
                            _ => {
                                if self.struct_defs.contains_key(type_name) {
                                    // Nested struct: set up its fields recursively
                                    let combined_name = format!("{}.{}", id, member_name);
                                    self.symbols.insert(
                                        combined_name.clone(),
                                        SymbolInfo {
                                            value_type: ValueType::TCustom(type_name.clone()),
                                            is_mut: true,
                                        },
                                    );
                                    self.arena_index.insert(combined_name.clone(), offset + field_offset);
                                    if !self.insert_struct(&combined_name, type_name) {
                                        println!("ERROR: Failed to initialize nested struct '{}.{}'", id, member_name);
                                        return false;
                                    }
                                } else {
                                    println!("ERROR: Unknown field type '{}'", type_name);
                                    return false;
                                }
                            },
                        }
                    }
                },
                _ => {
                    println!("ERROR: Unsupported field value type '{}'", value_type_to_str(&decl.value_type));
                    return false;
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

        return true;
    }

    fn get_string(&self, id: &str) -> Option<String> {
        let c_string_offset = match self.arena_index.get(&format!("{}.c_string", id)) {
            Some(offset) => *offset,
            None => {
                println!("ERROR: get_string: missing field '{}.c_string'", id);
                return None;
            },
        };
        let cap_offset = match self.arena_index.get(&format!("{}.cap", id)) {
            Some(offset) => *offset,
            None => {
                println!("ERROR: get_string: missing field '{}.cap'", id);
                return None;
            },
        };

        // Validate memory bounds
        if c_string_offset + 8 > Arena::g().memory.len() || cap_offset + 8 > Arena::g().memory.len() {
            println!("ERROR: get_string: field offsets out of bounds for '{}'", id);
            return None;
        }

        let c_string_ptr_bytes = &Arena::g().memory[c_string_offset..c_string_offset + 8];
        let c_string_ptr = i64::from_ne_bytes(c_string_ptr_bytes.try_into().unwrap()) as usize;

        let cap_bytes = &Arena::g().memory[cap_offset..cap_offset + 8];
        let length = i64::from_ne_bytes(cap_bytes.try_into().unwrap()) as usize;

        if c_string_ptr + length > Arena::g().memory.len() {
            println!("ERROR: get_string: String content out of bounds for '{}'", id);
            return None;
        }

        let bytes = &Arena::g().memory[c_string_ptr..c_string_ptr + length];
        Some(String::from_utf8_lossy(bytes).to_string())
    }

    fn insert_string(&mut self, id: &str, value_str: &String) -> Option<String> {
        // Insert the struct, expect it to define `.c_string` and `.cap`
        if !self.insert_struct(id, "Str") {
            println!("ERROR: insert_string: Failed to insert struct '{}'", id);
            return None;
        }

        // Look up field offsets
        let cap_offset = match self.arena_index.get(&format!("{}.cap", id)) {
            Some(&offset) => offset,
            None => {
                println!("ERROR: insert_string: missing arena_index entry for '{}.cap'", id);
                return None;
            }
        };
        let c_string_offset = match self.arena_index.get(&format!("{}.c_string", id)) {
            Some(&offset) => offset,
            None => {
                println!("ERROR: insert_string: missing arena_index entry for '{}.c_string'", id);
                return None;
            }
        };

        // Allocate and store string bytes at the end of the arena
        let string_offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(value_str.as_bytes());
        Arena::g().memory.push(0); // null terminator

        // Check for overlap
        let max_struct_field = cap_offset.max(c_string_offset) + 8;
        if string_offset < max_struct_field {
            println!(
                "WARNING: insert_string: string_offset {} overlaps with struct fields ending at {}",
                string_offset, max_struct_field
            );
        }

        // Store string pointer and length
        let string_offset_bytes = (string_offset as i64).to_ne_bytes();
        let len_bytes = (value_str.len() as i64).to_ne_bytes();

        if c_string_offset + 8 > Arena::g().memory.len() || cap_offset + 8 > Arena::g().memory.len() {
            println!(
                "ERROR: insert_string: field offset out of bounds. Memory size: {}",
                Arena::g().memory.len()
            );
            return None;
        }

        Arena::g().memory[c_string_offset..c_string_offset + 8].copy_from_slice(&string_offset_bytes);
        Arena::g().memory[cap_offset..cap_offset + 8].copy_from_slice(&len_bytes);

        Some(value_str.clone())
    }

    fn get_enum(self: &Context, id: &str) -> Option<EnumVal> {
        // Look up the symbol information for the id
        let symbol_info = match self.symbols.get(id) {
            Some(symbol) => symbol,
            None => return None, // If no symbol found, return None
        };

        // Check if the symbol corresponds to a custom type (enum type)
        let enum_type = match &symbol_info.value_type {
            ValueType::TCustom(custom_type_name) => custom_type_name,
            _ => return None, // If it's not a custom type (enum), return None
        };

        // Get the offset for the enum value from the arena index
        let offset = match self.arena_index.get(id) {
            Some(&offset) => offset,
            None => return None, // If no offset is found, return None
        };

        // Retrieve the i64 value (enum value) from memory
        let enum_value_bytes = &Arena::g().memory[offset..offset + 8];
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into().unwrap());

        // Look up the enum definition from `self.enum_defs` using the enum type
        let enum_def = match self.enum_defs.get(enum_type) {
            Some(def) => def,
            None => return None, // If no enum definition is found, return None
        };

        // Use the variant_pos_to_str function to get the enum variant name based on the position
        let enum_name = match enum_def.variant_pos_to_str(enum_value) {
            Ok(enum_name_) => enum_name_,
            Err(error_string) => {
                println!("{error_string}");
                return None;
            }
        };

        // Return an EnumVal with the enum type and name
        Some(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name: enum_name.to_string(),
        })
    }

    fn insert_enum(self: &mut Context, id: &str, enum_type: &str, pre_normalized_enum_name: &str) -> Option<EnumVal> {
        // Look up the enum definition from `self.enum_defs`
        let enum_def = match self.enum_defs.get(enum_type) {
            Some(def) => def,
            None => return None, // If no enum definition is found, return None
        };

        // Normalize the enum_name: remove the type name prefix (e.g., "ExampleEnum." -> "")
        let enum_name = match pre_normalized_enum_name.split('.').last() {
            Some(name) => name,
            None => {
                println!("Error: Invalid enum name format '{}'", pre_normalized_enum_name);
                return None
            },
        };

        let enum_value = enum_def.get_variant_pos(enum_name);

        // If the id represents a field (e.g., struct field), we should update it in the arena
        let is_field = id.contains('.');
        if is_field {
            if let Some(&offset) = self.arena_index.get(id) {
                // Update existing field in the arena with the new enum value
                Arena::g().memory[offset..offset + 8].copy_from_slice(&enum_value.to_le_bytes());
            } else {
                // Insert as a new field in the arena
                let offset = Arena::g().memory.len();
                Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes()); // store the i64 enum value directly
                self.arena_index.insert(id.to_string(), offset);
            }
            return Some(EnumVal {
                enum_type: enum_type.to_string(),
                enum_name: enum_name.to_string(),
            })
        }

        // Insert as a new enum in the arena memory
        let offset = Arena::g().memory.len();
        Arena::g().memory.extend_from_slice(&enum_value.to_le_bytes()); // store the i64 enum value directly
        self.arena_index.insert(id.to_string(), offset);

        // Return the EnumVal with the enum type and enum name for reference
        return Some(EnumVal {
            enum_type: enum_type.to_string(),
            enum_name: enum_name.to_string(),
        })
    }

    pub fn insert_array(&mut self, name: &str, elem_type: &str, values: &Vec<String>) {
        let array_type = format!("{}Array", elem_type);

        if !self.insert_struct(name, &array_type) {
            println!("ERROR: insert_array: failed to insert struct '{}'", array_type);
            return;
        }

        let len = values.len() as i64;
        let elem_size = match self.get_type_size(elem_type) {
            Ok(sz) => sz,
            Err(msg) => {
                println!("ERROR: {}", msg);
                return;
            },
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
                        Err(_) => {
                            println!("ERROR: insert_array: invalid U8 '{}'", val);
                            return;
                        }
                    }
                },
                "I64" => {
                    match val.parse::<i64>() {
                        Ok(n) => {
                            let bytes = n.to_ne_bytes();
                            Arena::g().memory[offset..offset+8].copy_from_slice(&bytes);
                        },
                        Err(_) => {
                            println!("ERROR: insert_array: invalid I64 '{}'", val);
                            return;
                        }
                    }
                },
                "Str" => {
                    for (i, val) in values.iter().enumerate() {
                        let offset = ptr + i * elem_size;

                        let temp_id = format!("{}.{}", name, i);
                        self.symbols.insert(temp_id.clone(), SymbolInfo {
                            value_type: ValueType::TCustom("Str".to_string()),
                            is_mut: false,
                        });

                        if self.insert_string(&temp_id, val).is_none() {
                            println!("ERROR: insert_array: insert_string failed for '{}'", temp_id);
                            return;
                        }

                        let str_offset = match self.arena_index.get(&temp_id) {
                            Some(&off) => off,
                            None => {
                                println!("ERROR: insert_array: missing arena offset for '{}'", temp_id);
                                return;
                            }
                        };

                        Arena::g().memory[offset..offset + elem_size]
                            .copy_from_slice(&Arena::g().memory[str_offset..str_offset + elem_size]);
                    }
                }

                _ => {
                    println!("ERROR: insert_array: unsupported element type '{}'", elem_type);
                    return;
                }
            }
        }

        // Write ptr, len, cap, is_dyn using arena_index
        let ptr_offset = match self.arena_index.get(&format!("{}.ptr", name)) {
            Some(o) => *o,
            None => {
                println!("ERROR: insert_array: missing .ptr field offset");
                return;
            }
        };
        Arena::g().memory[ptr_offset..ptr_offset+8].copy_from_slice(&(ptr as i64).to_ne_bytes());

        let len_bytes = len.to_ne_bytes();
        for field in &["len", "cap"] {
            if let Some(field_offset) = self.arena_index.get(&format!("{}.{}", name, field)) {
                Arena::g().memory[*field_offset..*field_offset+8].copy_from_slice(&len_bytes);
            } else {
                println!("ERROR: insert_array: missing .{} field offset", field);
                return;
            }
        }

        if let Some(is_dyn_offset) = self.arena_index.get(&format!("{}.is_dyn", name)) {
            Arena::g().memory[*is_dyn_offset] = 0; // false
        } else {
            println!("ERROR: insert_array: missing .is_dyn field offset");
        }
    }

}

fn get_func_name_in_call(e: &Expr) -> String {
    assert!(e.node_type == NodeType::FCall);
    assert!(e.params.len() > 0);
    match &e.get(0).node_type {
        NodeType::Identifier(f_name) => return f_name.clone(),
        _ => return e.lang_error("assert", &format!("panic calling get_func_name_in_call(), this should never happen.")),
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

fn get_func_def_for_fcall(context: &Context, fcall_expr: &Expr) -> Result<Option<SFuncDef>, String> {
    if fcall_expr.node_type != NodeType::FCall {
        return Err(fcall_expr.error("type", "Expected FCall node type"));
    }

    let func_expr = match fcall_expr.params.first() {
        Some(expr) => expr,
        None => return Ok(None),
    };

    match &func_expr.node_type {
        NodeType::Identifier(_) => {
            let combined_name = get_combined_name(func_expr)?;
            if let Some(func_def) = context.funcs.get(&combined_name) {
                Ok(Some(func_def.clone()))
            } else {
                Ok(None) // Incomplete for now; additional lookup logic could go here
            }
        },
        _ => Ok(None), // Silently ignore unsupported expressions
    }
}

fn value_type_func_proc(e: &Expr, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.returns.len() {
        0 => {
            return Err(e.error("type", &format!("func '{}' does not return anything", name)));
        },
        1 => {
            match func_def.returns.get(0).unwrap() {
                ValueType::TCustom(type_str) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                _ => return Err(e.error("type", &format!("func '{}' returns unsupported type {}",
                                                         name, value_type_to_str(func_def.returns.get(0).unwrap())))),
            }
        },
        _ => {
            return Err(e.todo_error("type", &format!("func '{}' returns multiple values", name)));
        },
    }
}

fn get_ufcs_fcall_value_type(context: &Context, e: &Expr, f_name: &String, id_expr: &Expr, symbol: &SymbolInfo) -> Result<ValueType, String> {
    let after_dot = match id_expr.params.get(0) {
        Some(_after_dot) => _after_dot,
        None => {
            return Err(e.error("type", &format!("Cannot call '{}', it is not a function or struct, it is a '{}'",
                                                &f_name, value_type_to_str(&symbol.value_type))));
        },
    };

    match &after_dot.node_type {
        NodeType::Identifier(after_dot_name) => {
            if context.funcs.contains_key(after_dot_name) {
                return value_type_func_proc(&e, &f_name, &context.funcs.get(after_dot_name).unwrap())
            }
            return Err(e.lang_error("type", &format!("expected function name after '{}.' found '{}'", f_name, after_dot_name)));
        },
        _ => {
            return Err(e.error("type", &format!("expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
        },
    }
}

fn get_fcall_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {

    let f_name = get_func_name_in_call(&e);
    if context.funcs.contains_key(&f_name) {
        return value_type_func_proc(&e, &f_name, &context.funcs.get(&f_name).unwrap())
    } else if context.symbols.contains_key(&f_name) {

        let symbol = context.symbols.get(&f_name).unwrap();
        let id_expr = e.get(0);
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
                        let member_decl = match struct_def.members.get(after_dot_name) {
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
                        let member_decl = match struct_def.members.get(after_dot_name) {
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
        NodeType::LLiteral(Literal::List(_)) => Ok(ValueType::TList),
        NodeType::FuncDef(func_def) => match func_def.function_type {
            FunctionType::FTFunc | FunctionType::FTFuncExt => Ok(ValueType::TFunction(FunctionType::FTFunc)),
            FunctionType::FTProc | FunctionType::FTProcExt => Ok(ValueType::TFunction(FunctionType::FTProc)),
            FunctionType::FTMacro => Ok(ValueType::TFunction(FunctionType::FTMacro)),
        },
        NodeType::EnumDef(_) => Ok(ValueType::TType(TTypeDef::TEnumDef)),
        NodeType::StructDef(_) => Ok(ValueType::TType(TTypeDef::TStructDef)),
        NodeType::FCall => get_fcall_value_type(context, e),

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

                        match struct_def.members.get(member_name) {
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

                        match struct_def.members.get(member_name) {
                            Some(decl) => {
                                current_type = decl.value_type.clone();
                            },
                            None => return Err(e.error("type", &format!("Struct '{}' has no member '{}' f", custom_type_name, member_name))),
                        }
                    },
                    ValueType::TMulti(variadic_type_name) => {
                        return Ok(ValueType::TMulti(variadic_type_name.to_string()))
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
                let _ = eval_core_proc_import(context, &e);
            }
        },
        NodeType::Declaration(decl) => {
            if context.funcs.contains_key(&decl.name) || context.symbols.contains_key(&decl.name) {
                errors.push(e.error("type", &format!("'{}' already declared.", decl.name)));
            }
            assert!(e.params.len() == 1, "{} ERROR: in init_context, while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            let inner_e = e.get(0);
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
                    assert!(inner_e.params.len() == 0, "{} ERROR: while declaring {}: enum declarations don't have any parameters in the tree.", LANG_NAME,
                            decl.name);
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
                    assert!(inner_e.params.len() == 0, "{} ERROR: while declaring {}, struct declarations must have exactly 0 params.", LANG_NAME, decl.name);
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
                                    let member_value_type = get_value_type(&context, member_expr).unwrap_or(ValueType::ToInferType);
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

                ValueType::TList |
                ValueType::TMulti(_) | ValueType::TCustom(_) | ValueType::ToInferType => {
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
                    return true;
                }
            }
            false
        },
        NodeType::StructDef(_) => {
            // TODO default values could try to call procs
            false
        },
        NodeType::EnumDef(_) => {
            false
        },
        NodeType::LLiteral(Literal::Bool(_)) => false,
        NodeType::LLiteral(Literal::Number(_)) => false,
        NodeType::LLiteral(Literal::List(_)) => false,
        NodeType::LLiteral(Literal::Str(_)) => false,
        NodeType::DefaultCase => false,
        NodeType::Identifier(_) => false,
        NodeType::FCall => {
            // TODO the arguments of a function call can also call procedures
            let f_name = get_func_name_in_call(&e);
            return context.funcs.contains_key(&f_name) && context.funcs.get(&f_name).unwrap().is_proc()
        },
        NodeType::Declaration(decl) => {
            assert!(e.params.len() == 1, "{} ERROR: while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            is_expr_calling_procs(&context, &e.get(0))
        },
        NodeType::Assignment(var_name) => {
            assert!(e.params.len() == 1, "{} ERROR: while assigning {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
            is_expr_calling_procs(&context, &e.get(0))
        }
        NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(&context, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return | NodeType::Throw => {
            for it_e in &e.params {
                if is_expr_calling_procs(&context, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::Catch => todo!(),
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
    assert!(e.params.len() == 0, "{} ERROR: in check_types(): enum declarations don't have any parameters in the tree.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

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

fn check_if_statement(mut context: &mut Context, e: &Expr) -> Vec<String> {
    assert!(e.params.len() == 2 || e.params.len() == 3, "{} ERROR: if nodes must have 2 or 3 parameters.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
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
        errors.extend(check_types(&mut context, &p));
    }
    return errors;
}

fn check_while_statement(mut context: &mut Context, e: &Expr) -> Vec<String> {
    assert!(e.params.len() == 2, "{} ERROR: while nodes must have exactly 2 parameters.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
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
        errors.extend(check_types(&mut context, &p));
    }
    return errors;
}

fn check_fcall(context: &Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();
    let f_name = get_func_name_in_call(e);
    let func_def;

    if context.funcs.contains_key(&f_name) {
        func_def = context.funcs.get(&f_name).unwrap();
    } else if let Some(symbol) = context.symbols.get(&f_name) {
        match &symbol.value_type {
            ValueType::TType(TTypeDef::TStructDef) => {
                let struct_def = match context.struct_defs.get(&f_name) {
                    Some(def) => def,
                    None => {
                        errors.push(e.error("type", &format!("struct '{}' not found in context", f_name)));
                        return errors;
                    },
                };

                assert!(e.params.len() > 0);
                if e.params.get(0).unwrap().params.len() == 0 {
                    return errors; // NOTE: This is to allow struct instantiation with no arguments
                }

                let after_dot = e.get(0).get(0);
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_value = match struct_def.default_values.get(after_dot_name) {
                            Some(val) => val,
                            None => {
                                errors.push(e.error("type", &format!("struct '{}' has no member '{}' g", f_name, after_dot_name)));
                                return errors;
                            },
                        };
                        match &member_value.node_type {
                            NodeType::FuncDef(f) => {
                                func_def = f;
                            },
                            _ => {
                                errors.push(e.error("type", &format!("Cannot call '{}.{}', it is a '{:?}', not a function.",
                                    f_name, after_dot_name, member_value.node_type)));
                                return errors;
                            },
                        }
                    },
                    _ => {
                        errors.push(e.error("type", &format!("expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                        return errors;
                    },
                }
            },
            ValueType::TCustom(type_name) => {
                let struct_def = match context.struct_defs.get(type_name) {
                    Some(def) => def,
                    None => {
                        errors.push(e.error("type", &format!("type '{}' not found in context", type_name)));
                        return errors;
                    },
                };

                let after_dot = e.get(0).get(0);
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_value = match struct_def.default_values.get(after_dot_name) {
                            Some(val) => val,
                            None => {
                                errors.push(e.error("type", &format!("struct '{}' has no member '{}' h", type_name, after_dot_name)));
                                return errors;
                            },
                        };
                        match &member_value.node_type {
                            NodeType::FuncDef(_) => {
                                let full_name = format!("{}.{}", type_name, after_dot_name);
                                match context.funcs.get(&full_name) {
                                    Some(_func_def_) => {
                                        let id_expr = Expr::new_clone(NodeType::Identifier(full_name.clone()), e.get(0), vec![]);
                                        let mut new_params = vec![Expr::new_clone(NodeType::Identifier(f_name.clone()), e, vec![])];
                                        new_params.extend(e.params[1..].iter().cloned());
                                        let mut new_e = Expr::new_clone(NodeType::FCall, e, new_params);
                                        new_e.params.insert(0, id_expr);
                                        return check_fcall(context, &new_e);
                                    },
                                    None => {
                                        errors.push(e.error("type", &format!("method '{}' not found in context", full_name)));
                                        return errors;
                                    },
                                }
                            },
                            _ => {
                                errors.push(e.error("type", &format!("Cannot call '{}.{}', it is a '{:?}', not a function.",
                                    type_name, after_dot_name, member_value.node_type)));
                                return errors;
                            },
                        }
                    },
                    _ => {
                        errors.push(e.error("type", &format!("expected identifier after '{}.' found {:?}", f_name, after_dot.node_type)));
                        return errors;
                    },
                }
            },
            _ => {
                errors.push(e.error("type", &format!("Cannot call '{}', it is a '{:?}', not a function nor a struct.", f_name, symbol.value_type)));
                return errors;
            },
        }
    } else {
        errors.push(e.error("type", &format!("Undefined function or struct '{}'", f_name)));
        return errors;
    }

    if func_def.args.len() == 0 && e.params.len() - 1 > 0 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects 0 args, but {} were provided.", f_name, e.params.len() - 1)));
        return errors;
    }
    let has_multi_arg = func_proc_has_multi_arg(func_def);
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
        let arg = func_def.args.get(std::cmp::min(i, max_arg_def - 1)).unwrap();
        let expected_type = &match &arg.value_type {
            ValueType::TMulti(inner_type_name) => str_to_value_type(&inner_type_name.clone()),
            _ => arg.value_type.clone(),
        };
        let found_type = match get_value_type(&context, e.get(i + 1)) {
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

fn check_func_proc_types(func_def: &SFuncDef, mut context: &mut Context, e: &Expr) -> Vec<String> {
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
            ValueType::TMulti(multi_type) => {
                if arg.is_mut {
                    errors.push(e.error("type", &format!("Variadic argument '{}' cannot be 'mut'.", &arg.name)));
                }
                if i != func_def.args.len() - 1 {
                    errors.push(e.error("type", &format!("Variadic argument '{}' must be the last.", &arg.name)));
                }
                has_variadic = true;

                context.symbols.insert(arg.name.clone(), SymbolInfo {
                    value_type: ValueType::TCustom(format!("{}Array", multi_type)),
                    is_mut: false,
                });
            },
            ValueType::TCustom(ref custom_type_name) => {
                let _custom_symbol = match context.symbols.get(custom_type_name) {
                    Some(custom_symbol_) => custom_symbol_,
                    None => {
                        errors.push(e.error("type", &format!("Argument '{}' is of undefined type '{}'.", &arg.name, &custom_type_name)));
                        return errors
                    },
                };
                // TODO check more type stuff

                context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
            },
            _ => {
                context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
            },
        }
    }

    // Don't check the bodies of external functions
    if func_def.is_ext() {
        return errors;
    }

    let mut return_found = false;
    let mut thrown_types = HashSet::new();
    errors.extend(check_body_returns_throws(&mut context, e, func_def, &func_def.body, &mut thrown_types, &mut return_found));

    if !return_found && func_def.returns.len() > 0 {
        errors.push(e.error("type", "No return statments found in function that returns "));
    }

    for declared_throw in &func_def.throws {
        let declared_str = value_type_to_str(declared_throw);
        if !thrown_types.contains(&declared_str) {
            errors.push(e.error("warning", &format!("It looks like `{}` is declared in the throws section, but this function never throws it.\nSuggestion: You can remove it to improve readability.", declared_str)));

        }
    }

    if func_def.function_type == FunctionType::FTFunc || func_def.function_type == FunctionType::FTFuncExt {
        if func_def.returns.len() == 0 && func_def.throws.len() == 0 {
            errors.push(e.error("type", "funcs must return or throw something, use a proc instead"));
        }
    }
    // TODO should macros be allowed to call procs?
    if !func_def.is_proc() {
        for se in &func_def.body {
            if is_expr_calling_procs(&context, &se) {
                errors.push(se.error("type", "funcs cannot call procs."));
            }
        }
    }

    return errors
}

fn check_body_returns_throws(context: &mut Context, e: &Expr, func_def: &SFuncDef, body: &[Expr], thrown_types: &mut HashSet<String>, return_found: &mut bool) -> Vec<String> {

    let mut errors = vec![];
    let returns_len = func_def.returns.len();

    for p in body.iter() {
        match &p.node_type {
            NodeType::Return => {
                *return_found = true;
                if returns_len != p.params.len() {
                    errors.push(p.error("type", &format!("Returning {} values when {} were expected.", p.params.len(), returns_len)));
                    errors.push(e.error("type", "Suggestion: Update returns section here"));
                } else {
                    for i in 0..p.params.len() {
                        let expected_value_type = func_def.returns.get(i).unwrap();
                        let return_val_e = p.params.get(i).unwrap();
                        match get_value_type(&context, return_val_e) {
                            Ok(actual_value_type) => {
                                if expected_value_type != &actual_value_type {
                                    errors.push(return_val_e.error("type", &format!("Return value in pos {} expected to be {:?}, but found {:?} instead",
                                                                                    i, expected_value_type, actual_value_type)));
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
                // Ensure there is exactly one throw parameter
                if p.params.len() != 1 {
                    errors.push(p.error("type", "Throw statement must have exactly one parameter."));
                } else {
                    let throw_param = &p.params[0];
                    match get_value_type(&context, throw_param) {
                        Ok(thrown_type) => {
                            // Track the thrown type as a string
                            thrown_types.insert(value_type_to_str(&thrown_type));

                            // Check if the thrown type is declared in the throws section
                            if !func_def.throws.contains(&thrown_type) {
                                errors.push(throw_param.error("type", &format!("Type '{}' thrown but not declared in throws section", value_type_to_str(&thrown_type))));
                                errors.push(e.error("type", "Suggestion: Update throws section here"));
                            }
                        },
                        Err(err) => {
                            errors.push(err);
                        }
                    }
                }
            },
            NodeType::FCall => {
                match get_func_def_for_fcall(&context, p) {
                    Ok(Some(called_func_def)) => {
                        for called_throw in &called_func_def.throws {
                            let called_throw_str = value_type_to_str(called_throw);
                            if func_def.throws.contains(called_throw) {
                                thrown_types.insert(called_throw_str);
                            } else {
                                errors.push(p.error("type", &format!(
                                    "Function throws '{}', but it is not declared in this function's throws section.",
                                    called_throw_str
                                )));
                                errors.push(e.error("type", "Suggestion: Update throws section here"));
                            }
                        }
                    },
                    Ok(None) => {
                        // TODO throw error from here?
                        // Do nothing — unsupported expression or no function target
                    },
                    Err(reason) => {
                        errors.push(p.error("type", &reason));
                    }
                }
            }

            NodeType::While => {
                if let Some(cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(cond_expr), thrown_types, return_found));
                }
                if let Some(body_expr) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, thrown_types, return_found));
                }
            }
            NodeType::If => {
                if let Some(cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(cond_expr), thrown_types, return_found));
                }
                if let Some(then_block) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &then_block.params, thrown_types, return_found));
                }
                if let Some(else_block) = p.params.get(2) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &else_block.params, thrown_types, return_found));
                }
            }
            NodeType::Switch => {
                // Analyze the switch expression itself (could throw)
                if let Some(switch_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(switch_expr), thrown_types, return_found));
                }

                let mut i = 1;
                while i + 1 < p.params.len() {
                    let case_expr = &p.params[i];
                    let body_expr = &p.params[i + 1];

                    // Check case expression and the body block
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(case_expr), thrown_types, return_found));
                    errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, thrown_types, return_found));

                    i += 2;
                }
            }

            _ => {},
        }
        errors.extend(check_types(context, &p));
    }

    return errors
}

fn check_catch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors = Vec::new();

    if e.params.len() != 3 {
        errors.push(e.error("type", "Catch node must have three parameters: variable, type, and body."));
        return errors;
    }

    let err_var_expr = &e.params[0];
    let err_type_expr = &e.params[1];
    let body_expr = &e.params[2];

    let var_name = match &err_var_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_var_expr.error("type", "First catch param must be an identifier"));
            return errors;
        }
    };

    let type_name = match &err_type_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_type_expr.error("type", "Second catch param must be a type identifier"));
            return errors;
        }
    };

    // Confirm that the type exists in the context (as done for function args)
    if context.symbols.get(&type_name).is_none() {
        errors.push(e.error("type", &format!("Catch refers to undefined type '{}'", &type_name)));
        return errors;
    }

    // Create scoped context for catch body
    let mut temp_context = context.clone();
    temp_context.symbols.insert(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name),
        is_mut: false,
    });

    errors.extend(check_types(&mut temp_context, body_expr));

    errors
}

fn check_declaration(mut context: &mut Context, e: &Expr, decl: &Declaration) -> Vec<String> {
    assert!(e.params.len() == 1, "{} ERROR: in declaration of {} declaration nodes must exactly 1 parameter.", LANG_NAME, decl.name);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
    if !context.symbols.contains_key(&decl.name) {
        let mut value_type = decl.value_type.clone();
        if value_type == ValueType::ToInferType {
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
            ValueType::ToInferType => {
                errors.push(e.lang_error("type", &format!("Cannot infer the declaration type of {}", decl.name)));
                return errors;
            },
            ValueType::TCustom(custom_type) => {
                match context.struct_defs.get(&custom_type) {
                    Some(_struct_def) => {
                        context.insert_struct(&decl.name, &custom_type);
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
    errors.extend(check_types(&mut context, &inner_e));

    return errors
}

fn check_assignment(mut context: &mut Context, e: &Expr, var_name: &str) -> Vec<String> {
    assert!(e.params.len() == 1, "{} ERROR: in assignment to {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
    let mut errors : Vec<String> = Vec::new();

    if context.funcs.contains_key(var_name)  {
        errors.push(e.error("type", &format!("function '{}' cannot be assigned to.", var_name)));
    } else if context.symbols.contains_key(var_name) {
        let symbol_info = context.symbols.get(var_name).unwrap();
        if !symbol_info.is_mut {
            errors.push(e.error("type", &format!("Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", var_name)));
        }
    } else {
        errors.push(e.error("type", &format!("Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                                             var_name, var_name, var_name)));
    }
    errors.extend(check_types(&mut context, &e.get(0)));
    return errors
}

fn check_switch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    let switch_expr_type = match get_value_type(context, e.get(0)) {
        Ok(t) => t,
        Err(err) => {
            errors.push(err);
            return errors
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

fn check_struct_def(_context: &mut Context, e: &Expr, struct_def: &SStructDef) -> Vec<String> {
    assert!(e.params.len() == 0, "{} ERROR: in check_struct_def(): struct declarations must take exactly 0 params.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    for (member_name, _member_decl) in &struct_def.members {
        // TODO check types for members inside structs too
        match struct_def.default_values.get(member_name) {
            Some(inner_e) => {
                // println!("inner_e {:?}", inner_e);
                match &inner_e.node_type {
                    // If the member's default value is a function (method), type check it
                    NodeType::FuncDef(_func_def) => {
                        // println!("DEBUG: Check members that are function definitions, got inner_e: {:?}", inner_e);
                        // println!("func_def {:?}", func_def);
                        // let mut function_context = context.clone();
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

fn check_types(mut context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.extend(check_types(&mut context, &p));
            }
        },
        NodeType::EnumDef(enum_def) => {
            errors.extend(check_enum_def(&e, enum_def));
        },
        NodeType::StructDef(struct_def) => {
            errors.extend(check_struct_def(&mut context, &e, struct_def));
        },
        NodeType::If => {
            errors.extend(check_if_statement(&mut context, &e));
        },
        NodeType::While => {
            errors.extend(check_while_statement(&mut context, &e));
        },
        NodeType::Switch => {
            errors.extend(check_switch_statement(&mut context, &e));
        },
        NodeType::FCall => {
            errors.extend(check_fcall(&context, &e));
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
            errors.extend(check_declaration(&mut context, &e, decl));
        },
        NodeType::Assignment(var_name) => {
            errors.extend(check_assignment(&mut context, &e, var_name));
        },
        NodeType::Return | NodeType::Throw => {
            for return_val in &e.params {
                errors.extend(check_types(&mut context, &return_val));
            }
        },
        NodeType::Catch => {
            errors.extend(check_catch_statement(&mut context, &e));
        }

        NodeType::LLiteral(Literal::Number(_)) | NodeType::LLiteral(Literal::List(_)) |
        NodeType::LLiteral(Literal::Bool(_)) | NodeType::LLiteral(Literal::Str(_)) | NodeType::DefaultCase => {},
    }

    return errors
}

// ---------- eval (interpreter)

#[derive(Clone, Debug)]
struct EvalResult {
    value: String,
    is_return: bool,
    is_throw: bool,
}

impl EvalResult {
    fn new(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: false}
    }

    fn new_return(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: true, is_throw: false}
    }

    fn new_throw(value: &str) -> EvalResult {
        return EvalResult{value: value.to_string(), is_return: false, is_throw: true}
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

fn eval_core_func_malloc(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'malloc' takes exactly 1 argument"))
    }

    let size_str = eval_expr(&mut context, e.get(1))?.value;
    let size = size_str.parse::<usize>().unwrap();

    let offset = Arena::g().memory.len(); // take *current* end of arena

    if size > 0 {
        Arena::g().memory.resize(offset + size, 0); // extend safely
    }

    return Ok(EvalResult::new(&offset.to_string()))
}

fn eval_core_func_free(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'free' takes exactly 1 argument"))
    }

    let _ptr_str = eval_expr(&mut context, e.get(1))?.value;
    // REM: Free does nothing in arena model (for now).

    return Ok(EvalResult::new(""))
}

fn eval_core_func_memset(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memset' takes exactly 3 arguments"))
    }

    let dest_str = eval_expr(context, e.get(1))?.value;
    let value_str = eval_expr(context, e.get(2))?.value;
    let size_str = eval_expr(context, e.get(3))?.value;

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

fn eval_core_func_memcpy(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 4 {
        return Err(e.lang_error("eval", "Core func 'memcpy' takes exactly 3 arguments"))
    }

    let dest_str = eval_expr(&mut context, e.get(1))?.value;
    let src_str = eval_expr(&mut context, e.get(2))?.value;
    let size_str = eval_expr(&mut context, e.get(3))?.value;

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

    let identifier_expr = e.get(1);
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

    let type_expr = e.get(1);
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

    let type_expr = e.get(1);
    match &type_expr.node_type {
        NodeType::Identifier(type_name) => {
            Ok(EvalResult::new(&format!("{}", type_name)))
        },
        node_type => Err(e.lang_error("eval", &format!("calling core func type_as_str, but found '{:?}' instead of identifier.",
                                                       node_type))),
    }
}

fn eval_core_func_lt(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'lt' takes exactly 2 arguments"))
    }
    let a = eval_expr(&mut context, e.get(1))?.value.parse::<i64>().unwrap();
    let b = eval_expr(&mut context, e.get(2))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&(a < b).to_string()))
}

fn eval_core_func_gt(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'gt' takes exactly 2 arguments"))
    }
    let a = eval_expr(&mut context, e.get(1))?.value.parse::<i64>().unwrap();
    let b = eval_expr(&mut context, e.get(2))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&(a > b).to_string()))
}

fn eval_core_func_add(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'add' takes exactly 2 arguments"))
    }
    let a = eval_expr(&mut context, e.get(1))?.value.parse::<i64>().unwrap();
    let b = eval_expr(&mut context, e.get(2))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&(a + b).to_string()))
}

fn eval_core_func_sub(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'sub' takes exactly 2 arguments"))
    }
    let a = eval_expr(&mut context, e.get(1))?.value.parse::<i64>().unwrap();
    let b = eval_expr(&mut context, e.get(2))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&(a - b).to_string()))
}

fn eval_core_func_mul(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'mul' takes exactly 2 arguments"))
    }
    let a = eval_expr(&mut context, e.get(1))?.value.parse::<i64>().unwrap();
    let b = eval_expr(&mut context, e.get(2))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&(a * b).to_string()))
}

fn eval_core_func_div(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 3 {
        return Err(e.lang_error("eval", "Core func 'div' takes exactly 2 arguments"))
    }
    let a = eval_expr(&mut context, e.get(1))?.value.parse::<i64>().unwrap();
    let b = eval_expr(&mut context, e.get(2))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&(a / b).to_string()))
}

fn eval_core_func_str_to_i64(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'str_to_i64' takes exactly 1 argument"))
    }
    let a = eval_expr(&mut context, &e.get(1))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&a.to_string()))
}

fn eval_core_func_i64_to_str(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'i64_to_str' takes exactly 1 argument"))
    }
    let val = eval_expr(&mut context, e.get(1))?.value;
    Ok(EvalResult::new(&val))
}

fn eval_core_func_enum_to_str(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'enum_to_str' takes exactly 1 argument"))
    }
    let val = eval_expr(&mut context, e.get(1))?.value;
    Ok(EvalResult::new(&val))
}

fn eval_core_func_u8_to_i64(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'u8_to_i64' takes exactly 1 argument"))
    }
    let a = eval_expr(&mut context, &e.get(1))?.value.parse::<i64>().unwrap();
    Ok(EvalResult::new(&a.to_string()))
}

fn eval_core_func_i64_to_u8(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core func 'i64_to_u8' takes exactly 1 argument"))
    }
    let val = eval_expr(&mut context, e.get(1))?.value;
    Ok(EvalResult::new(&val))
}

// ---------- core procs implementations for eval

fn eval_core_proc_single_print(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'single_print' takes exactly 1 argument"));
    }

    let result = eval_expr(&mut context, &e.get(1))?;
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

    let first_param = e.get(0);
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

fn eval_core_proc_eval_to_str(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'eval_to_str' takes exactly 1 argument"));
    }

    let path = "eval".to_string(); // Placeholder path
    let source_expr = eval_expr(&mut context, e.get(1))?;
    let str_source = format!("mode script; {}", source_expr.value);

    let result = main_run(false, &mut context, &path, str_source, Vec::new());

    Ok(EvalResult::new(&result))
}

fn eval_core_proc_runfile(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() < 2 {
        return Err(e.lang_error("eval", "Core proc 'runfile' expects at least 1 parameter"));
    }

    let path = eval_expr(&mut context, e.get(1))?.value;
    let mut main_args = Vec::new();
    for i in 2..e.params.len() {
        main_args.push(eval_expr(&mut context, e.get(i))?.value);
    }

    match run_file(&path, main_args) {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error_string) => Err(e.error("eval", &format!("While running file {path}: {error_string}"))),
    }
}

fn eval_core_proc_import(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'import' expects a single parameter"));
    }

    let path = format!("{}{}", eval_expr(&mut context, e.get(1))?.value, ".cil");

    match run_file_with_context(true, &mut context, &path, Vec::new()) {
        Ok(_) => Ok(EvalResult::new("")),
        Err(error_string) => Err(e.error("eval", &format!("While trying to import {path}: {error_string}"))),
    }
}

fn eval_core_proc_readfile(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if e.params.len() != 2 {
        return Err(e.lang_error("eval", "Core proc 'readfile' expects a single parameter"));
    }

    let path = eval_expr(&mut context, e.get(1))?.value;
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

    let e_exit_code = e.get(1);
    let exit_code = match &e_exit_code.node_type {
        NodeType::LLiteral(Literal::Number(my_li64)) => *my_li64,
        node_type => return Err(e.lang_error("eval", &format!("calling core proc 'exit', but found {:?} instead of literal i64 exit code.", node_type))),
    };

    std::process::exit(exit_code as i32);
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &SFuncDef, name: &str, mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {

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
                    let val = eval_expr(&mut context, expr)?.value;
                    values.push(val);
                }

                function_context.symbols.insert(arg.name.to_string(), SymbolInfo {
                    value_type: ValueType::TCustom(format!("{}Array", &multi_value_type)),
                    is_mut: arg.is_mut,
                });
                function_context.insert_array(&arg.name, &multi_value_type, &values);

                // We've consumed all remaining parameters, break out of loop
                break;
            },
            ValueType::TCustom(ref custom_type_name) => {
                let current_arg = e.get(param_index);
                let result = eval_expr(&mut context, &current_arg)?.value;

                if arg.is_mut {
                    match &current_arg.node_type {
                        NodeType::Identifier(id_) => {
                            mut_args.push((arg.name.clone(), id_.clone(), arg.value_type.clone()));
                        },
                        _ => {
                            return Err(e.lang_error("eval", "mut arguments must be passed as identifiers"))
                        }
                    }
                }

                match custom_type_name.as_str() {
                    "I64" => {
                        function_context.insert_i64(&arg.name, &result);
                    },
                    "U8" => {
                        function_context.insert_u8(&arg.name, &result);
                    },
                    "Bool" => {
                        function_context.insert_bool(&arg.name, &result);
                    },
                    "Str" => {
                        function_context.insert_string(&arg.name, &result);
                    },
                    _ => {
                        let custom_symbol = function_context.symbols.get(custom_type_name).ok_or_else(|| {
                            return e.lang_error("eval", &format!( "Undefined symbol for custom type '{}'", custom_type_name))
                        })?;
                        match custom_symbol.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                if function_context.insert_enum(&arg.name, &custom_type_name, &result).is_none() {
                                    return Err(e.lang_error("eval", &format!("Arg enum: Unable to insert enum '{}' of custom type '{}' with value '{}'.",
                                                                             &arg.name, &custom_type_name, &result)))
                                }
                            },
                            ValueType::TType(TTypeDef::TStructDef) => {
                                if !function_context.insert_struct(&arg.name, &custom_type_name) {
                                    return Err(e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an argument.",
                                                                             &arg.name, &custom_type_name)))
                                }
                                if current_arg.params.len() > 0 {
                                    return Err(e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only name of struct instances allowed for struct arguments for now.",
                                                                             &arg.name, &custom_type_name)))
                                }
                                match &current_arg.node_type {
                                    NodeType::Identifier(id_) => {
                                        if !function_context.copy_fields(&custom_type_name, &id_, &arg.name) {
                                            return Err(e.todo_error("eval", &format!("While copying fields from '{}' to '{}' of type '{}'",
                                                                                     &id_, &arg.name, &custom_type_name)))
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

    let result = eval_body(&mut function_context, &func_def.body)?.value;

    for (arg_name, source_name, value_type) in mut_args {
        match value_type {
            ValueType::TCustom(ref type_name) if type_name == "I64" => {
                let val = function_context.get_i64(&arg_name).unwrap();
                context.insert_i64(&source_name, &val.to_string());
            },
            ValueType::TCustom(ref type_name) if type_name == "U8" => {
                let val = function_context.get_u8(&arg_name).unwrap();
                context.insert_u8(&source_name, &val.to_string());
            },
            ValueType::TCustom(ref type_name) if type_name == "Str" => {
                let val = function_context.get_string(&arg_name).unwrap();
                context.insert_string(&source_name, &val);
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
                        let val = function_context.get_enum(&arg_name).unwrap();
                        context.insert_enum(&source_name, &val.enum_type, &format!("{}.{}", val.enum_type, val.enum_name));
                    },
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // TODO this can be simplified once we pass all args by reference
                        context.arena_index.insert(source_name.to_string(), *function_context.arena_index.get(&arg_name).unwrap());
                        context.map_instance_fields(type_name, &source_name);
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

                                context.arena_index.insert(return_instance.to_string(), *function_context.arena_index.get(&result).unwrap());
                                context.map_instance_fields(custom_type_name, &return_instance);
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

    return Ok(EvalResult::new(&result))
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

fn eval_func_proc_call_try_ufcs(context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    // TODO Handle UFCS in check_types instead of waiting for invalid types to be discovered during evaluation
    let id_expr = e.get(0);
    let name = get_func_name_in_call(&e);
    if id_expr.params.len() == 0 { // TODO Do we really need this check?
        return Err(e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name)));
    }

    let after_dot = match id_expr.params.get(0) {
        Some(ad) => ad,
        None => return Err(e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name))),
    };

    let after_dot_name = match &after_dot.node_type {
        NodeType::Identifier(f_name_) => f_name_.clone(),
        _ => return Err(e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name))),
    };

    let id_expr_name = format!("{}.{}", name, after_dot_name);

    let new_e = Expr::new_clone(NodeType::Identifier(after_dot_name.clone()), e.get(0), Vec::new());
    let extra_arg_e = Expr::new_clone(NodeType::Identifier(name.to_string()), e, Vec::new());

    let mut new_args = vec![new_e, extra_arg_e];
    new_args.extend_from_slice(&e.params[1..]);

    let new_fcall_e = Expr::new_clone(NodeType::FCall, e.get(0), new_args);

    let func_def = match context.funcs.get(&after_dot_name) {
        Some(func_def_) => func_def_.clone(),
        None => return Err(after_dot.lang_error("eval", &format!("Cannot call '{}'. Undefined function.", after_dot_name))),
    };

    eval_user_func_proc_call(&func_def, &id_expr_name, context, &new_fcall_e)
}

fn eval_func_proc_call(name: &str, mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    if context.funcs.contains_key(name) {
        let func_def = &context.funcs.get(name).unwrap().clone();
        if func_def.is_ext() {
            let is_proc = func_def.is_proc();
            return eval_core_func_proc_call(&name, &mut context, &e, is_proc)
        }
        return eval_user_func_proc_call(func_def, &name, &mut context, &e)
    } else if context.struct_defs.contains_key(name) {
        let struct_def = context.struct_defs.get(name).unwrap();
        let id_expr = e.get(0);
        if id_expr.params.len() == 0 {
            let id_name = match &id_expr.node_type {
                NodeType::Identifier(s) => s,
                _ => return Err(e.todo_error("eval", "Expected identifier name for struct instantiation")),
            };
            context.insert_struct(&id_name, &name);
            return Ok(EvalResult::new(match id_name.as_str() {
                "Bool" => "false",
                "U8" | "I64" => "0",
                "Str" => "",
                _ => id_name, // TODO Where is the struct being inserted in this case? Is this returned value even used?
            }))
        }

        let after_dot = match id_expr.params.get(0) {
            Some(_after_dot) => _after_dot,
            None => {
                return Err(e.todo_error("eval", &format!("Cannot instantiate '{}'. Not implemented yet.", name)))
            },
        };
        match &after_dot.node_type {
            NodeType::Identifier(after_dot_name) => {
                let _member_decl = match struct_def.members.get(after_dot_name) {
                    Some(_member) => _member,
                    None => {
                        return Err(e.lang_error("eval", &format!("struct '{}' has no member '{}' i", name, after_dot_name)))
                    },
                };
                let combined_name = format!("{}.{}", name, after_dot_name);
                if !context.funcs.contains_key(&combined_name) {
                    return Err(e.lang_error("eval", &format!("method '{}' not found in context", combined_name)))
                }

                let func_def = &context.funcs.get(&combined_name).unwrap().clone();
                return eval_user_func_proc_call(func_def, &name, &mut context, &e)
            },
            _ => {
                return Err(e.lang_error("eval", &format!("expected identifier after '{}.' found {:?}", name, after_dot.node_type)))
            },
        }
    } else if context.symbols.contains_key(name) {
        let symbol = context.symbols.get(name).unwrap();
        match &symbol.value_type {
            ValueType::TCustom(custom_type_name) => {
                let struct_def = match context.struct_defs.get(custom_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e);
                    },
                };

                let id_expr = e.get(0);
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e) // This is used for 'StructName()' kind of instantiations
                    },
                };

                let after_dot_name = match &after_dot.node_type {
                    NodeType::Identifier(f_name_) => f_name_.clone(),
                    _ => return eval_func_proc_call_try_ufcs(&mut context, &e),
                };

                let member_default_value = match struct_def.default_values.get(&after_dot_name) {
                    Some(_member) => _member,
                    None => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e)
                    },
                };

                // check that the function is a method in the struct, and if not try regular UFCS
                let id_expr_name = match &member_default_value.node_type {
                    NodeType::FuncDef(_func_def) => {
                        format!("{}.{}", custom_type_name, after_dot_name)
                    },
                    _  => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e)
                    },
                };

                let new_e = Expr::new_clone(NodeType::Identifier(id_expr_name.clone()), e.get(0), Vec::new());
                let extra_arg_e = Expr::new_clone(NodeType::Identifier(name.to_string()), e, Vec::new());
                let mut new_args = Vec::new();
                new_args.push(new_e);
                new_args.push(extra_arg_e);
                new_args.extend(e.params[1..].to_vec());
                let new_fcall_e = Expr::new_clone(NodeType::FCall, e.get(0), new_args);
                let func_def = &context.funcs.get(&id_expr_name).unwrap().clone();
                return eval_user_func_proc_call(func_def, &id_expr_name, &mut context, &new_fcall_e)
            },
            _ => {
                return eval_func_proc_call_try_ufcs(&mut context, &e)
            },
        }

    } else {
        return Err(e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name)))
    }
}

fn eval_declaration(declaration: &Declaration, mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let inner_e = e.get(0);
    let mut value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error("eval", &error_string));
        },
    };
    if declaration.value_type != ValueType::ToInferType {
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
        ValueType::ToInferType => {
            return Err(e.lang_error("eval", &format!("'{}' declared of type '{}' but still to infer type '{}'",
                                                     declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type))));
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
                            let member_value_type = match member_decl.value_type {
                                ValueType::ToInferType => {
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
                                ValueType::TCustom(type_name) => {
                                    match type_name.as_str() {
                                        "I64" => {
                                            let expr_result_str = eval_expr(&mut context, default_value).unwrap().value;
                                            context.insert_i64(&combined_name, &expr_result_str);
                                        },
                                        "U8" => {
                                            let expr_result_str = eval_expr(&mut context, default_value).unwrap().value;
                                            context.insert_u8(&combined_name, &expr_result_str);
                                        },
                                        "Bool" => {
                                            let expr_result_str = eval_expr(&mut context, default_value).unwrap().value;
                                            context.insert_bool(&combined_name, &expr_result_str);
                                        },
                                        "Str" => {
                                            let expr_result_str = eval_expr(&mut context, default_value).unwrap().value;
                                            context.insert_string(&combined_name, &expr_result_str);
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
                                ValueType::ToInferType => {
                                    return Err(e.lang_error("eval", &format!("Cannot infer type of '{}.{}', but it should be inferred already.",
                                                                             &declaration.name, &member_decl.name)));
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
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_i64(&declaration.name, &expr_result_str);
                    return Ok(EvalResult::new(""))
                },
                "U8" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_u8(&declaration.name, &expr_result_str);
                    return Ok(EvalResult::new(""))
                },
                "Bool" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_bool(&declaration.name, &expr_result_str);
                    return Ok(EvalResult::new(""))
                },
                "Str" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    context.insert_string(&declaration.name, &expr_result_str);
                    return Ok(EvalResult::new(""))
                },
                _ => {
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    let custom_symbol = context.symbols.get(custom_type_name).unwrap();
                    if custom_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                        let enum_expr_result_str = &eval_expr(&mut context, inner_e)?.value;
                        if context.insert_enum(&declaration.name, custom_type_name, enum_expr_result_str).is_none() {
                            return Err(inner_e.lang_error("eval", &format!("Declare enum: Unable to insert enum '{}' of custom type '{}' with value '{}'.", &declaration.name, custom_type_name, enum_expr_result_str)))
                        }
                    } else if custom_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        // Special case for instantiation
                        if inner_e.node_type == NodeType::FCall && inner_e.params.len() == 1 {
                            if let NodeType::Identifier(potentially_struct_name) = &inner_e.params[0].node_type {
                                if inner_e.params[0].params.is_empty() {
                                    if context.struct_defs.contains_key(potentially_struct_name) {
                                        if !context.insert_struct(&declaration.name, custom_type_name) {
                                            return Err(e.error("eval", &format!("Failure trying to declare '{}' of struct type '{}'", &declaration.name, custom_type_name)));
                                        }
                                        return Ok(EvalResult::new(""))
                                    }
                                }
                            }
                        }
                        // otherwise continue, it's a function that returns a struct
                        let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                        context.arena_index.insert(declaration.name.to_string(), *context.arena_index.get(&expr_result_str).unwrap());
                        context.map_instance_fields(custom_type_name, &declaration.name);
                    } else {
                        return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}'. Only 'enum' and 'struct' custom types allowed.",
                                                            &declaration.name, value_type_to_str(&custom_symbol.value_type))))
                    }
                    return Ok(EvalResult::new(""))
                },
            }
        },
        ValueType::TList | ValueType::TMulti(_) => {
            return Err(e.error("eval", &format!("Cannot declare '{}' of type '{}'",
                                                &declaration.name, value_type_to_str(&declaration.value_type))))
        },
    }
}

fn eval_assignment(var_name: &str, mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    let symbol_info = context.symbols.get(var_name).unwrap();
    if !symbol_info.is_mut {
        return Err(e.lang_error("eval", &format!("in eval_assignment, while assigning to '{}': Assignments can only be to mut values. Offending expr: {:?}", var_name, e)));
    }
    if e.params.len() != 1 {
        return Err(e.lang_error("eval", &format!("in eval_assignment, while assigning to '{}': assignments must take exactly one value", var_name)));
    }

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error("eval", &error_string));
        },
    };
    match value_type {
        ValueType::ToInferType => {
            return Err(e.lang_error("eval", &format!("Cannot assign {}, type should already be inferred of type '{:?}'.", &var_name, &symbol_info.value_type)));
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.insert_i64(var_name, &expr_result_str);
                },
                "U8" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.insert_u8(var_name, &expr_result_str);
                },
                "Bool" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.insert_bool(var_name, &expr_result_str);
                },
                "Str" => {
                    let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                    context.insert_string(var_name, &expr_result_str);
                },
                _ => {
                    match &context.symbols.get(custom_type_name).unwrap().value_type {
                        ValueType::TType(TTypeDef::TEnumDef) => {
                            let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                            if context.insert_enum(var_name, &custom_type_name, &expr_result_str).is_none() {
                                return Err(inner_e.lang_error("eval", &format!("Assign enum: Unable to insert enum '{}' of custom type '{}' with value '{}'.", var_name, &custom_type_name, &expr_result_str)))
                            }
                        },
                        ValueType::TType(TTypeDef::TStructDef) => {
                            let expr_result_str = eval_expr(&mut context, inner_e)?.value;
                            if !context.copy_fields(custom_type_name, &expr_result_str, var_name) {
                                return Err(inner_e.lang_error("eval", &format!("Assign struct: Failed to copy fields from '{}' to '{}'", expr_result_str, var_name)));
                            }
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

        ValueType::TList | ValueType::TType(TTypeDef::TEnumDef) | ValueType::TMulti(_) => {
            Err(e.lang_error("eval", &format!("Cannot assign '{}' of type '{}'.", &var_name, value_type_to_str(&value_type))))
        },
    }
}

fn eval_identifier_expr_struct_member(name: &str, inner_name: &str, context: &Context, inner_e: &Expr, member_decl: &Declaration) -> Result<EvalResult, String> {
    return match member_decl.value_type {
        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    match context.get_i64(&format!("{}.{}", name, inner_name)) {
                        Some(result) => Ok(EvalResult::new(&result.to_string())),
                        None => Err(inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))),
                    }
                },
                "U8" => {
                    match context.get_u8(&format!("{}.{}", name, inner_name)) {
                        Some(result) => Ok(EvalResult::new(&result.to_string())),
                        None => Err(inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))),
                    }
                },
                "Bool" => {
                    match context.get_bool(&format!("{}.{}", name, inner_name)) {
                        Some(result) => Ok(EvalResult::new(&result.to_string())),
                        None => Err(inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))),
                    }
                },
                "Str" => {
                    match context.get_string(&format!("{}.{}", name, inner_name)) {
                        Some(result_str) => Ok(EvalResult::new(&result_str)),
                        None => Err(inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))),
                    }
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
    assert!(e.params.len() > 0, "{} eval ERROR: struct type '{}' can't be used as a primary expression.", LANG_NAME, name);

    let struct_def = context.struct_defs.get(name).unwrap();
    let inner_e = e.get(0);
    match &inner_e.node_type {
        NodeType::Identifier(inner_name) => {
            match struct_def.members.get(inner_name) {
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
    if !context.symbols.contains_key(custom_type_name) {
        return Err(e.lang_error("eval", &format!("Argument '{}' is of undefined type {}.", name, custom_type_name)));
    }
    let custom_symbol = context.symbols.get(custom_type_name).unwrap();
    match custom_symbol.value_type {
        ValueType::TType(TTypeDef::TEnumDef) => {
            match context.get_enum(name) {
                Some(enum_val) => Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name))),
                None => Err(e.lang_error("eval", &format!("Enum '{}' not found for custom type '{}'.", name, custom_type_name))),
            }
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
                                            let struct_def = context.struct_defs.get(custom_type_name).unwrap();
                                            match struct_def.members.get(inner_name) {
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

            let inner_e = e.params.last().unwrap();
            match current_type {
                ValueType::TCustom(ref custom_type_name) => {
                    match custom_type_name.as_str() {
                        "I64" => match context.get_i64(&current_name) {
                            Some(result) => Ok(EvalResult::new(&result.to_string())),
                            None => Err(e.lang_error("eval", &format!("Value not set for '{}'", current_name))),
                        },
                        "U8" => match context.get_u8(&current_name) {
                            Some(result) => Ok(EvalResult::new(&result.to_string())),
                            None => Err(e.lang_error("eval", &format!("Value not set for '{}'", current_name))),
                        },
                        "Bool" => match context.get_bool(&current_name) {
                            Some(result) => Ok(EvalResult::new(&result.to_string())),
                            None => Err(e.lang_error("eval", &format!("Value not set for '{}'", current_name))),
                        },
                        "Str" => match context.get_string(&current_name) {
                            Some(result) => Ok(EvalResult::new(&result)),
                            None => Err(e.lang_error("eval", &format!("Value not set for '{}'", current_name))),
                        },
                        _ => match context.symbols.get(&value_type_to_str(&current_type)).unwrap().value_type {
                            ValueType::TType(TTypeDef::TEnumDef) => {
                                match context.get_enum(&current_name) {
                                    Some(enum_val) => Ok(EvalResult::new(&format!("{}.{}", custom_type_name, enum_val.enum_name))),
                                    None => Err(inner_e.lang_error("eval", &format!("Value not set for field '{}'", current_name))),
                                }
                            },
                            ValueType::TType(TTypeDef::TStructDef) => {
                                Ok(EvalResult::new(&current_name))
                            },
                            _ => Err(inner_e.todo_error("eval", &format!("Cannot access '{}'. Fields of custom type '{}' not implemented", current_name, custom_type_name))),
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
        Some(symbol_info) => match symbol_info.value_type {
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                return Ok(EvalResult::new(name));
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                assert!(e.params.len() > 0, "{} eval ERROR: enum type '{}' can't be used as a primary expression.", LANG_NAME, name);
                // let enum_def = context.enum_defs.get(name).unwrap();
                let inner_e = e.get(0);
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
            ValueType::ToInferType => {
                return Err(e.lang_error("eval", &format!("Can't infer the type of identifier '{}'.", name)));
            },
            ValueType::TCustom(ref custom_type_name) => {
                match custom_type_name.as_str() {
                    "I64" => {
                        if let Some(val) = context.get_i64(name) {
                            return Ok(EvalResult::new(&val.to_string()));
                        } else {
                            return Err(e.lang_error("eval", &format!("Identifier '{}' not found as I64.", name)));
                        }
                    },
                    "U8" => {
                        if let Some(val) = context.get_u8(name) {
                            return Ok(EvalResult::new(&val.to_string()));
                        } else {
                            return Err(e.lang_error("eval", &format!("Identifier '{}' not found as U8.", name)));
                        }
                    },
                    "Bool" => {
                        if let Some(val) = context.get_bool(name) {
                            return Ok(EvalResult::new(&val.to_string()));
                        } else {
                            return Err(e.lang_error("eval", &format!("Identifier '{}' not found as Bool.", name)));
                        }
                    },
                    "Str" => {
                        if e.params.len() == 0 {
                            if let Some(val) = context.get_string(name) {
                                return Ok(EvalResult::new(&val));
                            } else {
                                return Err(e.lang_error("eval", &format!("Identifier '{}' not found as Str.", name)));
                            }
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
    for se in statements.iter() {
        let stmt_result = eval_expr(&mut context, &se)?;
        if stmt_result.is_return || stmt_result.is_throw {
            return Ok(stmt_result);
        }
    }
    return Ok(EvalResult::new(""))
}

fn eval_expr(mut context: &mut Context, e: &Expr) -> Result<EvalResult, String> {
    match &e.node_type {
        NodeType::Body => eval_body(&mut context, &e.params),
        NodeType::LLiteral(Literal::Bool(bool_value)) => Ok(EvalResult::new(&bool_value.to_string())),
        NodeType::LLiteral(Literal::Number(li64)) => Ok(EvalResult::new(&li64.to_string())),
        NodeType::LLiteral(Literal::Str(lstring)) => Ok(EvalResult::new(lstring)),
        NodeType::LLiteral(Literal::List(list_str_)) => Ok(EvalResult::new(list_str_)),
        NodeType::FCall => {
            let f_name = get_func_name_in_call(&e);
            eval_func_proc_call(&f_name, &mut context, &e)
        },
        NodeType::Declaration(declaration) => {
            eval_declaration(&declaration, &mut context, &e)
        },
        NodeType::Assignment(var_name) => {
            eval_assignment(&var_name, &mut context, &e)
        },
        NodeType::Identifier(name) => eval_identifier_expr(&name, &context, &e),
        NodeType::If => {
            assert!(e.params.len() == 2 || e.params.len() == 3, "{} eval ERROR: if nodes must have 2 or 3 parameters.", LANG_NAME);
            let result_cond = eval_expr(&mut context, &e.get(0))?;
            if result_cond.is_throw {
                return Ok(result_cond)
            }
            if result_cond.value.parse::<bool>().unwrap() {
                eval_expr(&mut context, &e.get(1))
            } else if e.params.len() == 3 {
                eval_expr(&mut context, &e.get(2))
            } else {
                Ok(EvalResult::new(""))
            }
        },
        NodeType::While => {
            assert!(e.params.len() == 2, "{} eval ERROR: while nodes must have exactly 2 parameters.", LANG_NAME);
            let mut result_cond = eval_expr(&mut context, &e.get(0))?;
            if result_cond.is_throw {
                return Ok(result_cond.clone())
            }
            while result_cond.value.parse::<bool>().unwrap() {
                let result = eval_expr(&mut context, &e.get(1))?;
                if result.is_return || result.is_throw {
                    return Ok(result)
                }
                result_cond = eval_expr(&mut context, &e.get(0))?;
                if result_cond.is_throw {
                    return Ok(result_cond)
                }
            }
            Ok(EvalResult::new(""))
        },
        NodeType::Switch => {
            assert!(e.params.len() >= 3, "{} eval ERROR: switch nodes must have at least 3 parameters.", LANG_NAME);
            let to_switch = e.get(0);
            let value_type = get_value_type(&context, &to_switch)?;
            let result_to_switch = eval_expr(&mut context, &to_switch)?;
            if result_to_switch.is_throw {
                return Ok(result_to_switch)
            }
            let mut param_it = 1;
            while param_it < e.params.len() {
                let case = e.get(param_it);
                if case.node_type == NodeType::DefaultCase {
                    param_it += 1;
                    return eval_expr(&mut context, &e.get(param_it));
                }
                let case_type = get_value_type(&context, &case)?;
                if value_type != case_type {
                    return Err(e.lang_error("eval", &format!("switch value type {:?}, case value type {:?}", value_type, case_type)));
                }
                let result_case = eval_expr(&mut context, &case)?;
                if result_case.is_throw {
                    return Ok(result_case)
                }
                param_it += 1;
                if result_to_switch.value == result_case.value {
                    return eval_expr(&mut context, &e.get(param_it));
                }
                param_it += 1;
            }
            Ok(EvalResult::new(""))
        },
        NodeType::Return => {
            if e.params.len() == 0 {
                Ok(EvalResult::new_return(""))
            } else if e.params.len() > 1 {
                Err(e.lang_error("eval", "multiple return values not implemented yet"))
            } else {
                let result = eval_expr(&mut context, &e.get(0))?;
                if result.is_throw {
                    return Ok(result)
                }
                Ok(EvalResult::new_return(&result.value))
            }
        },
        NodeType::Throw => {
            if e.params.len() != 1 {
                Err(e.lang_error("eval", "Throw can only return one value. This should have been caught before"))
            } else {
                let result = eval_expr(&mut context, &e.get(0))?;
                Ok(EvalResult::new_throw(&result.value))
            }
        },
        NodeType::Catch => {
            Ok(EvalResult::new("")) // TODO eval_expr for catch
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
        NodeType::Declaration(decl) => {
            ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::Assignment(var_name) => {
            ast_str.push_str(&format!("(set {} {})", var_name, to_ast_str(&e.get(0))));
            return ast_str;
        },
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
        NodeType::If => {
            ast_str.push_str(&format!("(if {})", to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::While => {
            ast_str.push_str(&format!("(while {})", to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::Switch => {
            ast_str.push_str(&format!("(switch {})", to_ast_str(&e.get(0))));
            return ast_str;
        },
        _ => todo!(),
    }
}

// ---------- main binary

// TODO return Result<String, String>, so that imports that fail can be treated accordingly
fn main_run(print_extra: bool, mut context: &mut Context, path: &String, source: String, main_args: Vec<String>) -> String {

    let mut lexer = match lexer_from_source(&path, source) {
        Ok(_result) => _result,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };

    let mode = match parse_mode(&path, &mut lexer) {
        Ok(mode_) => mode_,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };
    context.mode = mode;
    if print_extra {
        println!("Mode: {}", context.mode.name);
    }

    if context.mode.name == "test" {
        match run_file_with_context(true, &mut context, &"src/core/modes/test.cil".to_string(), Vec::new()) {
            Ok(_) => {},
            Err(error_string) => {
                return format!("{}:{}", &path, error_string);
            },
        }
    }

    let mut e: Expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };
    if !SKIP_AST {
        println!("AST: \n{}", to_ast_str(&e));
    }

    let mut errors = init_context(&mut context, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} declaration errors found", errors.len());
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
    errors.extend(check_types(&mut context, &e)); // TODO remove mut from context arg

    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} type errors found", errors.len());
    }

    return match eval_expr(&mut context, &e) {
        Ok(eval_result) => eval_result.value,
        Err(err) => format!("{}:{}", path, err),
    }
}

// ---------- main, usage, args, etc

fn run_file(path: &String, main_args: Vec<String>) -> Result<(), String> {
    let mut context = Context::new(path, DEFAULT_MODE);
    run_file_with_context(true, &mut context, &"src/core/core.cil".to_string(), Vec::new())?;
    run_file_with_context(false, &mut context, &path, main_args)?;
    return Ok(())
}

fn run_file_with_context(is_import: bool, mut context: &mut Context, path: &String, main_args: Vec<String>) -> Result<(), String> {
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
    let run_result = main_run(!is_import, &mut context, &path, source, main_args);
    if run_result != "" {
        println!("{}", run_result);
    }

    if is_import && !can_be_imported(&context.mode) {
        return Err(format!("file '{path}' of mode '{}' cannot be imported", context.mode.name))
    }
    context.mode = previous_mode; // restore the context mode of the calling file
    return Ok(())
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
        Err(error_string) => {
            println!("ERROR: While running file {path}");
            println!("{error_string}");
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
