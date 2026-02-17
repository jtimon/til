use std::collections::HashMap;
use std::convert::TryInto;
use crate::rs::init::{Context, SymbolInfo, EnumVal, ScopeFrame, ScopeType};
use crate::rs::parser::{Expr, ValueType, TTypeDef, value_type_to_str, NodeType, Literal};
// EvalHeap: Memory management for the TIL interpreter

pub struct EvalHeap {
    pub temp_id_counter: usize,
    pub default_instances: HashMap<String, usize>,  // type name -> heap pointer of default template
    heap_blocks: HashMap<usize, usize>,  // ptr -> size for heap-allocated blocks
    total_heap_bytes: usize,  // running total of heap bytes allocated
}

pub struct EvalHeapMapping {
    pub name: String,
    pub offset: usize,
}

pub struct SymbolEntry {
    pub name: String,
    pub info: SymbolInfo,
}

/// Result from insert_struct_core containing mappings to be stored
pub struct StructInsertResult {
    pub heap_mappings: Vec<EvalHeapMapping>,
    pub symbols: Vec<SymbolEntry>,
}

/// Result from insert_string_core containing string offset and length bytes
pub struct StringInsertInfo {
    pub string_offset_bytes: [u8; 8],
    pub len_bytes: [u8; 8],
}

/// Result from insert_enum_core containing optional mapping and enum value
pub struct EnumInsertResult {
    pub mapping: Option<EvalHeapMapping>,
    pub enum_val: EnumVal,
}

// Bug #133: Structs for extracting heap contents for serialization to static arrays
/// Contents of a Vec for serialization to static C arrays
pub struct VecContents {
    pub element_type_name: String,
    pub type_size: usize,
    pub element_bytes: Vec<Vec<u8>>,
}

// heap memory (starts at 1 to avoid NULL confusion)
// REM: first address 0 is reserved (invalid), malloc always >0
impl EvalHeap {
    // This function gives access to the singleton instance of EvalHeap
    #[allow(static_mut_refs)]
    pub fn g() -> &'static mut EvalHeap {
        unsafe { // TODO research if we can do "safe" singletons in rust before self hosting, just out of curiosity
            static mut INSTANCE: Option<EvalHeap> = None;

            // Lazy initialization of the singleton instance
            INSTANCE.get_or_insert_with(|| EvalHeap {
                temp_id_counter: 0, // A temporary ugly hack for return values
                default_instances: HashMap::new(),
                heap_blocks: HashMap::new(),
                total_heap_bytes: 0,
            })
        }
    }

    /// Total heap bytes allocated
    pub fn len(&self) -> usize {
        self.total_heap_bytes
    }

    /// Read bytes at offset (raw pointer access)
    pub fn get(&self, offset: usize, len: usize) -> &[u8] {
        if offset == 0 || len == 0 {
            return &[];
        }
        unsafe { std::slice::from_raw_parts(offset as *const u8, len) }
    }

    /// Write bytes at offset (raw memcpy)
    pub fn set(&mut self, offset: usize, bytes: &[u8]) -> Result<(), String> {
        unsafe {
            std::ptr::copy_nonoverlapping(bytes.as_ptr(), offset as *mut u8, bytes.len());
        }
        Ok(())
    }

    /// Issue #163: Allocate zeroed memory on the heap, return raw pointer as offset
    pub fn heap_alloc(&mut self, size: usize) -> Result<usize, String> {
        // Zero-size structs get 1 byte so we have a unique address
        let alloc_size = if size == 0 { 1 } else { size };
        let layout = std::alloc::Layout::from_size_align(alloc_size, 8)
            .map_err(|_| "heap_alloc: bad layout".to_string())?;
        let ptr = unsafe { std::alloc::alloc_zeroed(layout) } as usize;
        if ptr == 0 {
            return Err("heap_alloc: allocation failed".to_string());
        }
        self.heap_blocks.insert(ptr, alloc_size);
        self.total_heap_bytes += alloc_size;
        Ok(ptr)
    }

    /// Issue #163: Free a heap-allocated block
    pub fn heap_free(&mut self, ptr: usize) {
        if let Some(size) = self.heap_blocks.remove(&ptr) {
            let layout = std::alloc::Layout::from_size_align(size, 8).unwrap();
            unsafe { std::alloc::dealloc(ptr as *mut u8, layout); }
        }
    }

    // === EVAL-PHASE MEMORY OPERATIONS ===
    // These methods manage runtime memory allocation and access
    // They take Context as parameter to access type info and heap_index

    /// Check if id refers to an instance field (e.g., "myStruct.field") vs a type constant
    pub fn is_instance_field(ctx: &Context, id: &str) -> bool {
        if !id.contains('.') { return false; }
        let base = id.split('.').next().unwrap();
        ctx.scope_stack.lookup_symbol(base).map_or(false, |sym| {
            !matches!(sym.value_type, ValueType::TType(_))
        })
    }

    pub fn get_u8(ctx: &Context, id: &str, e: &Expr) -> Result<u8, String> {
        // Bug #160: Deterministic dispatch based on identifier structure
        // Use is_instance_field to distinguish field paths from type constants (e.g., Ptr.NULL)
        let offset = if Self::is_instance_field(ctx, id) {
            // Instance field path - ALWAYS calculate offset dynamically
            ctx.get_field_offset(id).map_err(|err| {
                e.lang_error(&ctx.path, "context", &format!("get_u8: {}", err))
            })?
        } else {
            // Variable or type constant - try direct lookup first
            // If not found and path has dots, use get_field_offset (for namespace field subpaths)
            match ctx.scope_stack.lookup_var(id) {
                Some(offset) => offset,
                None => {
                    if id.contains('.') {
                        ctx.get_field_offset(id).map_err(|err| {
                            e.lang_error(&ctx.path, "context", &format!("get_u8 fallback: {}", err))
                        })?
                    } else {
                        return Err(e.lang_error(&ctx.path, "context", &format!("u8 not found for id '{}'", id)));
                    }
                }
            }
        };

        Ok(EvalHeap::g().get(offset, 1)[0])
    }

    pub fn get_i64(ctx: &Context, id: &str, e: &Expr) -> Result<i64, String> {
        // Bug #160: Deterministic dispatch based on identifier structure
        // Use is_instance_field to distinguish field paths from type constants (e.g., Ptr.NULL)
        let offset = if Self::is_instance_field(ctx, id) {
            // Instance field path - ALWAYS calculate offset dynamically
            ctx.get_field_offset(id).map_err(|err| {
                e.lang_error(&ctx.path, "context", &format!("get_i64: {}", err))
            })?
        } else {
            // Variable or type constant - try direct lookup first
            // If not found and path has dots, use get_field_offset (for namespace field subpaths)
            match ctx.scope_stack.lookup_var(id) {
                Some(offset) => offset,
                None => {
                    if id.contains('.') {
                        ctx.get_field_offset(id).map_err(|err| {
                            e.lang_error(&ctx.path, "context", &format!("get_i64 fallback: {}", err))
                        })?
                    } else {
                        return Err(e.lang_error(&ctx.path, "context", &format!("i64 not found for id '{}'", id)));
                    }
                }
            }
        };

        match EvalHeap::g().get(offset, 8).try_into() {
            Ok(bytes) => {
                let result = i64::from_ne_bytes(bytes);
                Ok(result)
            },
            Err(_) => Err(e.lang_error(&ctx.path, "context", &format!("Invalid i64 read for id '{}'", id))),
        }
    }

    /// Core logic for insert_i64 - returns Some(offset) if caller needs to store it, None if already handled
    fn insert_i64_core(ctx: &Context, id: &str, i64_str: &String, e: &Expr) -> Result<Option<usize>, String> {
        let v = i64_str.parse::<i64>()
            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("Invalid i64 literal '{}'", i64_str)))?;
        let bytes = v.to_ne_bytes();

        if Self::is_instance_field(ctx, id) {
            // Bug #160: Deterministic dispatch - field paths ALWAYS use get_field_offset
            let field_offset = ctx.get_field_offset(id).map_err(|err| {
                e.lang_error(&ctx.path, "context", &format!("insert_i64: {}", err))
            })?;

            EvalHeap::g().set(field_offset, &bytes)?;
            return Ok(None)
        }

        // For non-instance fields (including struct constants like Vec.INIT_CAP), create new entry
        let offset = EvalHeap::g().heap_alloc(8)?;
        EvalHeap::g().set(offset, &bytes)?;
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
            frame.heap_index.insert(id.to_string(), offset);
        }
        Ok(())
    }

    // REM: Can't be moved to TIL until compilation - needs way to calculate size from TIL declarations
    fn insert_u8_core(ctx: &Context, id: &str, u8_str: &String, e: &Expr) -> Result<Option<usize>, String> {
        let v = u8_str.parse::<u8>()
            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("Invalid u8 literal '{}'", u8_str)))?;

        if Self::is_instance_field(ctx, id) {
            // Bug #160: Deterministic dispatch - field paths ALWAYS use get_field_offset
            let field_offset = ctx.get_field_offset(id).map_err(|err| {
                e.lang_error(&ctx.path, "context", &format!("insert_u8: {}", err))
            })?;
            EvalHeap::g().set(field_offset, &[v])?;
            return Ok(None)
        }

        let offset = EvalHeap::g().heap_alloc(1)?;
        EvalHeap::g().set(offset, &[v])?;
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
            frame.heap_index.insert(id.to_string(), offset);
        }
        Ok(())
    }

    // TODO all args should be passed as pointers/references and we wouldn't need this
    /// Core logic for insert_struct - does all the work but returns mappings instead of inserting them
    pub fn insert_struct_core(ctx: &mut Context, id: &str, custom_type_name: &str, existing_offset: Option<usize>, defaults: &HashMap<String, String>, e: &Expr) -> Result<StructInsertResult, String> {
        let mut result = StructInsertResult {
            heap_mappings: Vec::new(),
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
            None => EvalHeap::g().heap_alloc(total_size)?,
        };
        result.heap_mappings.push(EvalHeapMapping { name: id.to_string(), offset });

        // Temporarily register base var so get_field_offset works during field initialization
        ctx.scope_stack.insert_var(id.to_string(), offset);
        ctx.scope_stack.declare_symbol(id.to_string(), SymbolInfo {
            value_type: ValueType::TCustom(custom_type_name.to_string()),
            is_mut: true,
            is_copy: false,
            is_own: false,
            is_comptime_const: false,
        });

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
                        let index = match enum_def.variants.iter().position(|v| v.name == variant) {
                            Some(i) => i as i64,
                            None => return Err(e.lang_error(&ctx.path, "context", &format!("insert_struct: Unknown enum variant '{}' for field '{}'", variant, decl.name))),
                        };
                        EvalHeap::g().set(offset + field_offset, &index.to_ne_bytes())?;
                    } else {
                        match type_name.as_str() {
                            "U8" => {
                                let u8_val = default_value.parse::<u8>().map_err(|_| {
                                    e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid U8 default value '{}' for field '{}'", default_value, decl.name))
                                })?;
                                EvalHeap::g().set(offset + field_offset, &[u8_val])?;
                            },
                            "I64" => {
                                let i64_val = default_value.parse::<i64>().map_err(|_| {
                                    e.lang_error(&ctx.path, "context", &format!("insert_struct: Invalid I64 default value '{}' for field '{}'", default_value, decl.name))
                                })?;
                                EvalHeap::g().set(offset + field_offset, &i64_val.to_ne_bytes())?;
                            },
                            _ => {
                                if ctx.scope_stack.has_struct(type_name) {
                                    let nested_combined_name = format!("{}.{}", id, decl.name);
                                    let nested_symbol = SymbolInfo {
                                        value_type: ValueType::TCustom(type_name.clone()),
                                        is_mut: true,
                                        is_copy: false,
                                        is_own: false,
                                        is_comptime_const: false,
                                    };
                                    // Must declare symbol BEFORE recursive call (needed for is_mut lookup)
                                    ctx.scope_stack.declare_symbol(nested_combined_name.clone(), nested_symbol.clone());
                                    result.symbols.push(SymbolEntry { name: nested_combined_name.clone(), info: nested_symbol });

                                    // Special case: Str field initialization
                                    if type_name == "Str" {
                                        // Register inline offset BEFORE insert_string so it writes to the inline space
                                        let str_field_offset = offset + field_offset;
                                        result.heap_mappings.push(EvalHeapMapping { name: nested_combined_name.clone(), offset: str_field_offset });
                                        EvalHeap::insert_string(ctx, &nested_combined_name, &default_value, e)?;
                                    } else {
                                        // Use existing offset for nested struct (inline allocation)
                                        let nested_field_offset = offset + field_offset;
                                        result.heap_mappings.push(EvalHeapMapping { name: nested_combined_name.clone(), offset: nested_field_offset });
                                        // Extract nested defaults (field.subfield -> subfield)
                                        let prefix = format!("{}.", decl.name);
                                        let nested_defaults: HashMap<String, String> = defaults.iter()
                                            .filter_map(|(k, v)| k.strip_prefix(&prefix).map(|rest| (rest.to_string(), v.clone())))
                                            .collect();
                                        let nested_result = EvalHeap::insert_struct_core(ctx, &nested_combined_name, type_name, Some(nested_field_offset), &nested_defaults, e)
                                            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("insert_struct: Failed to initialize nested struct '{}.{}'", id, decl.name)))?;
                                        // Collect nested mappings (but they're already inserted by the temp inserts above)
                                        result.heap_mappings.extend(nested_result.heap_mappings);
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

            // Bug #160: Removed field heap_mappings.push - offsets are now calculated dynamically
            // Symbol still needed for type checking
            let combined_name = format!("{}.{}", id, decl.name);
            result.symbols.push(SymbolEntry { name: combined_name, info: SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut,
                is_copy: false,
                is_own: false,
                is_comptime_const: false,
            }});
            }
        }

        // Remove temp registration (caller will apply the final mappings)
        ctx.scope_stack.remove_var(id);
        ctx.scope_stack.remove_symbol(id);

        Ok(result)
    }

    /// Generate heap mappings and symbols for a struct without writing bytes.
    /// Used for template-based insertion where bytes are already memcpy'd.
    fn generate_struct_mappings(ctx: &mut Context, id: &str, custom_type_name: &str, base_offset: usize, e: &Expr) -> Result<StructInsertResult, String> {
        let mut result = StructInsertResult {
            heap_mappings: Vec::new(),
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
        result.heap_mappings.push(EvalHeapMapping { name: id.to_string(), offset: base_offset });

        // Generate symbols for each field (Bug #160: no longer generate field heap mappings)
        for decl in struct_def.members.iter() {
            if decl.is_mut {
                let field_rel_offset = field_offsets.get(&decl.name).copied().unwrap_or(0);
                let field_abs_offset = base_offset + field_rel_offset;
                let combined_name = format!("{}.{}", id, decl.name);

                // Bug #160: Removed heap_mappings.push - offsets are now calculated dynamically
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
                        if ctx.scope_stack.has_struct(type_name) {
                            // Declare nested symbol first
                            ctx.scope_stack.declare_symbol(combined_name.clone(), SymbolInfo {
                                value_type: ValueType::TCustom(type_name.clone()),
                                is_mut: true,
                                is_copy: false,
                                is_own: false,
                                is_comptime_const: false,
                            });
                            let nested = EvalHeap::generate_struct_mappings(ctx, &combined_name, type_name, field_abs_offset, e)?;
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
        let new_offset = EvalHeap::g().heap_alloc(struct_size)?;

        // memcpy from template
        let data = EvalHeap::g().get(template_offset, struct_size).to_vec();
        EvalHeap::g().set(new_offset, &data)?;

        // Generate and apply mappings
        let result = EvalHeap::generate_struct_mappings(ctx, id, custom_type_name, new_offset, e)?;
        for m in result.heap_mappings {
            ctx.scope_stack.frames.last_mut().unwrap().heap_index.insert(m.name, m.offset);
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
        let new_offset = EvalHeap::g().heap_alloc(struct_size)?;

        // memcpy from template
        let data = EvalHeap::g().get(template_offset, struct_size).to_vec();
        EvalHeap::g().set(new_offset, &data)?;

        // Temporarily push frame for generate_struct_mappings
        let empty_frame = ScopeFrame {
            heap_index: std::collections::HashMap::new(),
            symbols: std::collections::HashMap::new(),
            funcs: std::collections::HashMap::new(),
            enums: std::collections::HashMap::new(),
            structs: std::collections::HashMap::new(),
            scope_type: ScopeType::Function,
        };
        let taken_frame = std::mem::replace(frame, empty_frame);
        ctx.scope_stack.frames.push(taken_frame);

        let result = EvalHeap::generate_struct_mappings(ctx, id, custom_type_name, new_offset, e);

        // Pop frame back
        *frame = ctx.scope_stack.frames.pop().unwrap();

        let result = result?;
        for m in result.heap_mappings {
            frame.heap_index.insert(m.name, m.offset);
        }
        for s in result.symbols {
            frame.symbols.insert(s.name, s.info);
        }

        Ok(())
    }

    /// Core logic for insert_string - returns Some(StringInsertInfo) if caller needs to create struct, None if already handled
    fn insert_string_core(ctx: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<Option<StringInsertInfo>, String> {
        let is_field = Self::is_instance_field(ctx, id);

        // Allocate string data (heap_alloc returns zeroed memory, so null terminator is free)
        let string_offset = EvalHeap::g().heap_alloc(value_str.len() + 1)?;
        EvalHeap::g().set(string_offset, value_str.as_bytes())?;
        let string_offset_bytes = (string_offset as i64).to_ne_bytes();
        let len_bytes = (value_str.len() as i64).to_ne_bytes();

        if is_field {
            if let Ok(base_offset) = ctx.get_field_offset(id) {
                if let Some(existing_str_def) = ctx.scope_stack.lookup_struct("Str") {
                    let members = existing_str_def.members.clone();
                    let mut existing_offset = 0;

                    for existing_decl in members.iter() {
                        if existing_decl.is_mut {
                            let existing_type_size = ctx.get_type_size( &value_type_to_str(&existing_decl.value_type))?;
                            let absolute_offset = base_offset + existing_offset;
                            if existing_decl.name == "c_string" {
                                EvalHeap::g().set(absolute_offset, &string_offset_bytes)?;
                            } else if existing_decl.name == "_len" {
                                EvalHeap::g().set(absolute_offset, &len_bytes)?;
                            }

                            existing_offset += existing_type_size;
                        }
                    }
                    return Ok(None)
                }
                return Err(e.lang_error(&ctx.path, "context", "ERROR: 'Str' struct definition not found"))
            }

            // Not yet inserted - insert fresh inlined Str
            if let Some(str_def) = ctx.scope_stack.lookup_struct("Str") {
                let members = str_def.members.clone();

                // Calculate total Str struct size
                let mut str_size = 0;
                for decl in members.iter() {
                    if decl.is_mut {
                        str_size += ctx.get_type_size(&value_type_to_str(&decl.value_type))?;
                    }
                }

                let struct_offset = EvalHeap::g().heap_alloc(str_size)?;
                let mut current_offset = 0;

                for decl in members.iter() {
                    if decl.is_mut {
                        let type_size = ctx.get_type_size(&value_type_to_str(&decl.value_type))?;

                        if decl.name == "c_string" {
                            EvalHeap::g().set(struct_offset + current_offset, &string_offset_bytes)?;
                        } else if decl.name == "_len" {
                            EvalHeap::g().set(struct_offset + current_offset, &len_bytes)?;
                        }

                        current_offset += type_size;
                    }
                }

                ctx.scope_stack.frames.last_mut().unwrap().heap_index.insert(id.to_string(), struct_offset);
                return Ok(None)
            }
            return Err(e.lang_error(&ctx.path, "context", "'Str' struct definition not found"))
        }

        Ok(Some(StringInsertInfo { string_offset_bytes, len_bytes }))
    }

    pub fn insert_string(ctx: &mut Context, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(info) = Self::insert_string_core(ctx, id, value_str, e)? {
            // Create Str struct from template
            let template_offset = EvalHeap::g().default_instances.get("Str")
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string", "Str template not found - ensure str.til is imported"))?;
            EvalHeap::insert_struct(ctx, id, "Str", template_offset, e)?;
            // Bug #160: Use get_field_offset instead of lookup_var for field paths
            let c_string_offset = ctx.get_field_offset(&format!("{}.c_string", id))
                .map_err(|err| e.lang_error(&ctx.path, "insert_string", &format!("missing '{}.c_string': {}", id, err)))?;
            let len_offset = ctx.get_field_offset(&format!("{}._len", id))
                .map_err(|err| e.lang_error(&ctx.path, "insert_string", &format!("missing '{}._len': {}", id, err)))?;
            EvalHeap::g().set(c_string_offset, &info.string_offset_bytes)?;
            EvalHeap::g().set(len_offset, &info.len_bytes)?;
        }
        Ok(())
    }

    pub fn insert_string_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, value_str: &String, e: &Expr) -> Result<(), String> {
        if let Some(info) = Self::insert_string_core(ctx, id, value_str, e)? {
            // Create Str struct from template
            // During compile-time evaluation (builder path), the Str template may not exist
            // because the interpreter never evaluated struct declarations. This is OK for
            // macros with Type parameters - the type name is only used in AST construction,
            // not read as a runtime Str value.
            let template_offset = match EvalHeap::g().default_instances.get("Str").copied() {
                Some(offset) => offset,
                None => return Ok(()),
            };
            EvalHeap::insert_struct_into_frame(ctx, frame, id, "Str", template_offset, e)?;
            // Bug #160: Calculate field offsets from base offset in frame
            // The base struct was just inserted into frame.heap_index
            let base_offset = frame.heap_index.get(id)
                .copied()
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string_into_frame", &format!("missing '{}' in frame", id)))?;
            // Str layout: c_string (Ptr), _len (I64), cap (I64)
            // Get field offsets from struct definition
            let str_def = ctx.scope_stack.lookup_struct("Str")
                .ok_or_else(|| e.lang_error(&ctx.path, "insert_string_into_frame", "Str struct not found"))?;
            let mut c_string_rel_offset = 0usize;
            let mut len_rel_offset = 0usize;
            let mut current_offset = 0usize;
            for decl in &str_def.members {
                if decl.is_mut {
                    if decl.name == "c_string" {
                        c_string_rel_offset = current_offset;
                    } else if decl.name == "_len" {
                        len_rel_offset = current_offset;
                    }
                    let field_size = match &decl.value_type {
                        ValueType::TCustom(type_name) => ctx.get_type_size(type_name)?,
                        _ => return Err(e.lang_error(&ctx.path, "insert_string_into_frame", "unexpected field type")),
                    };
                    current_offset += field_size;
                }
            }
            let c_string_offset = base_offset + c_string_rel_offset;
            let len_offset = base_offset + len_rel_offset;
            EvalHeap::g().set(c_string_offset, &info.string_offset_bytes)?;
            EvalHeap::g().set(len_offset, &info.len_bytes)?;
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
                EvalHeap::insert_i64(ctx, var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "U8" => {
                EvalHeap::insert_u8(ctx, var_name, &value.to_string(), e)
            },
            ValueType::TCustom(type_name) if type_name == "Str" => {
                EvalHeap::insert_string(ctx, var_name, &value.to_string(), e)
            },
            _ => Err(e.lang_error(&ctx.path, "eval", &format!("insert_primitive: Unsupported type {:?}", value_type)))
        }
    }

    pub fn get_enum_at_offset(ctx: &Context, enum_type: &str, offset: usize, e: &Expr) -> Result<EnumVal, String> {

        // Read enum from a specific offset (used for nested enum payloads)
        let enum_value_bytes = EvalHeap::g().get(offset, 8);
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
                let payload_size = EvalHeap::get_payload_size_for_type(ctx, vtype, offset + 8, e)?;
                if payload_size > 0 {
                    let payload_offset = offset + 8;
                    let payload_bytes = EvalHeap::g().get(payload_offset, payload_size).to_vec();
                    (Some(payload_bytes), Some(vtype.clone()))
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
                                let inner_enum = EvalHeap::get_enum_at_offset(ctx, type_name, offset, e)?;
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

        // Bug #160: Deterministic dispatch based on identifier structure
        // Use is_instance_field to distinguish field paths from type constants
        let offset = if Self::is_instance_field(ctx, id) {
            // Instance field path - ALWAYS calculate offset dynamically
            ctx.get_field_offset(id)
                .map_err(|err| e.lang_error(&ctx.path, "context", &format!("get_enum: {}", err)))?
        } else {
            // Variable or type constant - ALWAYS direct lookup
            ctx.scope_stack.lookup_var(id)
                .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum: EvalHeap index for '{}' not found", id)))?
        };

        let enum_value_bytes = EvalHeap::g().get(offset, 8);
        let enum_value = i64::from_le_bytes(enum_value_bytes.try_into()
                                            .map_err(|_| e.lang_error(&ctx.path, "context", &format!("get_enum: Failed to convert bytes to i64 for '{}'", id)))?);

        let enum_def = ctx.scope_stack.lookup_enum(&enum_type)
            .ok_or_else(|| e.lang_error(&ctx.path, "context", &format!("get_enum: Enum definition for '{}' not found", enum_type)))?;

        let enum_name = Context::variant_pos_to_str(enum_def, enum_value, &ctx.path, e)?;

        // Check if this variant has a payload type
        let variant_payload_type = enum_def.get(&enum_name);
        let (payload_data, payload_type) = match variant_payload_type {
            Some(Some(vtype)) => {
                // This variant has a payload, read it from heap
                let payload_size = match vtype {
                    ValueType::TCustom(type_name) if type_name == "I64" => 8,
                    ValueType::TCustom(type_name) if type_name == "Str" => {
                        ctx.get_type_size("Str").unwrap_or(0)
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
                                        let inner_enum = EvalHeap::get_enum_at_offset(ctx, type_name, offset + 8, e)?;
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
                    let payload_bytes = EvalHeap::g().get(payload_offset, payload_size).to_vec();
                    (Some(payload_bytes), Some(vtype.clone()))
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
        let mapping = {
            // Bug #160: Deterministic dispatch - instance fields use get_field_offset for in-place update
            if Self::is_instance_field(ctx, id) {
                let offset = ctx.get_field_offset(id)?;
                // Update existing enum value in-place (no new mapping needed)
                EvalHeap::g().set(offset, &enum_value.to_le_bytes())?;
                if let Some(payload_bytes) = &payload_data {
                    if payload_bytes.len() + 8 <= max_enum_size {
                        EvalHeap::g().set(offset + 8, &payload_bytes)?;
                    }
                }
                None
            } else {
                // Allocate max enum size (zeroed), write tag and payload
                let new_enum_offset = EvalHeap::g().heap_alloc(max_enum_size)?;
                EvalHeap::g().set(new_enum_offset, &enum_value.to_le_bytes())?;
                if let Some(payload_bytes) = &payload_data {
                    if payload_bytes.len() + 8 <= max_enum_size {
                        EvalHeap::g().set(new_enum_offset + 8, &payload_bytes)?;
                    }
                }
                // padding: heap_alloc returns zeroed memory
                Some(EvalHeapMapping { name: id.to_string(), offset: new_enum_offset })
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
            ctx.scope_stack.frames.last_mut().unwrap().heap_index.insert(m.name, m.offset);
        }
        Ok(result.enum_val)
    }

    pub fn insert_enum_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, id: &str, enum_type: &str, pre_normalized_enum_name: &str, e: &Expr) -> Result<EnumVal, String> {
        // Temporarily push frame so symbol lookups work in core function
        let empty_frame = ScopeFrame {
            heap_index: std::collections::HashMap::new(),
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
            frame.heap_index.insert(m.name, m.offset);
        }
        Ok(result.enum_val)
    }

    /// Insert an Array for variadic arguments into a function frame.
    /// Uses insert_struct_into_frame internally.
    pub fn insert_array_into_frame(ctx: &mut Context, frame: &mut ScopeFrame, name: &str, elem_type: &str, values: &Vec<String>, e: &Expr) -> Result<(), String> {
        // Create Array struct using template
        let template_offset = EvalHeap::g().default_instances.get("Array").copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array_into_frame", "Array template not found - ensure array.til is imported"))?;
        Self::insert_struct_into_frame(ctx, frame, name, "Array", template_offset, e)?;

        let len = values.len() as i64;
        let elem_size = ctx.get_type_size(elem_type)?;
        let total_size = (len as usize) * elem_size;

        // Allocate memory for elements
        let ptr = EvalHeap::g().heap_alloc(total_size)?;

        // Write values into allocated buffer
        for (i, val) in values.iter().enumerate() {
            let offset = ptr + i * elem_size;
            match elem_type {
                "U8" => {
                    let byte = val.parse::<u8>()
                        .map_err(|err| e.lang_error(&ctx.path, "insert_array", &format!("invalid U8 '{}'", err)))?;
                    EvalHeap::g().set(offset, &[byte])?;
                },
                "I64" => {
                    let n = val.parse::<i64>()
                        .map_err(|err| e.lang_error(&ctx.path, "insert_array", &format!("invalid I64 '{}'", err)))?;
                    EvalHeap::g().set(offset, &n.to_ne_bytes())?;
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
                    let str_offset = frame.heap_index.get(&temp_id).copied()
                        .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing Str offset for '{}'", temp_id)))?;
                    let data = EvalHeap::g().get(str_offset, elem_size).to_vec();
                    EvalHeap::g().set(offset, &data)?;
                },
                _ => {
                    // Struct element - val is identifier, copy from source
                    let src_offset = ctx.scope_stack.lookup_var(val)
                        .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("struct source '{}' not found", val)))?;
                    let data = EvalHeap::g().get(src_offset, elem_size).to_vec();
                    EvalHeap::g().set(offset, &data)?;
                }
            }
        }

        // Bug #160: Calculate field offsets from base offset in frame
        let base_offset = frame.heap_index.get(name).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", &format!("missing base offset for '{}'", name)))?;
        let array_def = ctx.scope_stack.lookup_struct("Array")
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", "Array struct definition not found"))?;

        // Calculate relative offsets for each field
        let mut type_name_rel_offset = 0usize;
        let mut type_size_rel_offset = 0usize;
        let mut ptr_rel_offset = 0usize;
        let mut len_rel_offset = 0usize;
        let mut current_offset = 0usize;
        for decl in &array_def.members {
            if decl.is_mut {
                let field_size = match &decl.value_type {
                    ValueType::TCustom(t) => ctx.get_type_size(t)?,
                    _ => return Err(e.lang_error(&ctx.path, "insert_array", "unsupported field type")),
                };
                match &decl.name[..] {
                    "type_name" => type_name_rel_offset = current_offset,
                    "type_size" => type_size_rel_offset = current_offset,
                    "ptr" => ptr_rel_offset = current_offset,
                    "_len" => len_rel_offset = current_offset,
                    _ => {}
                }
                current_offset += field_size;
            }
        }

        // Update Array fields using calculated offsets
        let ptr_offset = base_offset + ptr_rel_offset;
        EvalHeap::g().set(ptr_offset, &(ptr as i64).to_ne_bytes())?;

        let len_offset = base_offset + len_rel_offset;
        EvalHeap::g().set(len_offset, &len.to_ne_bytes())?;

        let type_size_offset = base_offset + type_size_rel_offset;
        EvalHeap::g().set(type_size_offset, &(elem_size as i64).to_ne_bytes())?;

        // Set type_name field (it's a Str)
        let temp_type_name_id = format!("{}_type_name_temp", name);
        frame.symbols.insert(temp_type_name_id.clone(), SymbolInfo {
            value_type: ValueType::TCustom("Str".to_string()),
            is_mut: false,
            is_copy: false,
            is_own: false,
            is_comptime_const: false,
        });
        Self::insert_string_into_frame(ctx, frame, &temp_type_name_id, &elem_type.to_string(), e)?;
        let temp_str_offset = frame.heap_index.get(&temp_type_name_id).copied()
            .ok_or_else(|| e.lang_error(&ctx.path, "insert_array", "missing type_name temp Str offset"))?;
        let type_name_offset = base_offset + type_name_rel_offset;
        let str_size = ctx.get_type_size("Str")?;
        let data = EvalHeap::g().get(temp_str_offset, str_size).to_vec();
        EvalHeap::g().set(type_name_offset, &data)?;

        Ok(())
    }

    /// Convert a struct instance stored in EvalHeap to a struct literal Expr.
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
            .ok_or_else(|| e.lang_error(&ctx.path, "heap",
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

        Ok(Expr::new_explicit(NodeType::FCall(false), params, 0, 0))
    }

    /// Helper: read a field value from EvalHeap and convert to literal Expr
    fn field_to_literal(
        ctx: &Context,
        field_id: &str,
        value_type: &ValueType,
        e: &Expr,
    ) -> Result<Expr, String> {
        match value_type {
            ValueType::TCustom(ref t) if t == "I64" => {
                let i64_val = Self::get_i64(ctx, field_id, e)?;
                Ok(Expr::new_explicit(NodeType::LLiteral(Literal::Number(i64_val.to_string())), vec![], 0, 0))
            },
            ValueType::TCustom(ref t) if t == "U8" => {
                let u8_val = Self::get_u8(ctx, field_id, e)?;
                Ok(Expr::new_explicit(NodeType::LLiteral(Literal::Number(u8_val.to_string())), vec![], 0, 0))
            },
            ValueType::TCustom(ref nested_type) => {
                // Check if nested struct
                if ctx.scope_stack.has_struct(nested_type) {
                    return Self::to_struct_literal(ctx, field_id, nested_type, e);
                }
                Err(e.lang_error(&ctx.path, "heap", &format!("to_struct_literal: unsupported nested type '{}'", nested_type)))
            },
            _ => Err(e.lang_error(&ctx.path, "heap", &format!("to_struct_literal: unsupported field type '{}'", value_type_to_str(value_type)))),
        }
    }

    // Bug #133: Extract heap contents for serialization to static arrays
    // ============================================================

    /// Extract the contents of a Vec instance from heap memory.
    /// Returns the element type name, size, and raw bytes for each element.
    pub fn extract_vec_contents(ctx: &Context, instance_name: &str) -> Result<VecContents, String> {
        // Get Vec base offset
        let vec_offset = ctx.scope_stack.lookup_var(instance_name)
            .ok_or_else(|| format!("extract_vec_contents: instance '{}' not found", instance_name))?;

        // Vec layout: type_name (Str), type_size (I64), ptr (Ptr), _len (I64), cap (I64)
        // Get sizes
        let str_size = ctx.get_type_size("Str")?;
        let ptr_size = ctx.get_type_size("Ptr")?;

        // Read type_name (Str) - need to extract the string value
        let type_name_offset = vec_offset;
        let type_name_str = Self::extract_str_at_offset(ctx, type_name_offset)?;

        // Read type_size (I64) - after Str
        let type_size_offset = vec_offset + str_size;
        let type_size_bytes: [u8; 8] = EvalHeap::g().get(type_size_offset, 8).try_into()
            .map_err(|_| "extract_vec_contents: failed to read type_size")?;
        let type_size = i64::from_ne_bytes(type_size_bytes) as usize;

        // Read ptr.data (I64) - after type_size
        let ptr_offset = type_size_offset + 8;
        let ptr_bytes: [u8; 8] = EvalHeap::g().get(ptr_offset, 8).try_into()
            .map_err(|_| "extract_vec_contents: failed to read ptr")?;
        let data_ptr = i64::from_ne_bytes(ptr_bytes) as usize;

        // Read _len (I64) - after ptr (Ptr is 16 bytes: data + is_borrowed)
        let len_offset = ptr_offset + ptr_size;
        let len_bytes: [u8; 8] = EvalHeap::g().get(len_offset, 8).try_into()
            .map_err(|_| "extract_vec_contents: failed to read _len")?;
        let len = i64::from_ne_bytes(len_bytes) as usize;

        // Extract element bytes
        let mut element_bytes = Vec::new();
        for i in 0..len {
            let elem_offset = data_ptr + (i * type_size);
            let bytes = EvalHeap::g().get(elem_offset, type_size).to_vec();
            element_bytes.push(bytes);
        }

        Ok(VecContents {
            element_type_name: type_name_str,
            type_size,
            element_bytes,
        })
    }

    /// Extract string data from Str raw bytes.
    /// Used for nested types where we have the Str struct bytes directly.
    pub fn extract_str_from_bytes(ctx: &Context, str_bytes: &[u8]) -> Result<String, String> {
        let ptr_size = ctx.get_type_size("Ptr")?;

        // Read c_string.data (first 8 bytes)
        let c_string_ptr_bytes: [u8; 8] = str_bytes[..8].try_into()
            .map_err(|_| "extract_str_from_bytes: failed to read c_string ptr")?;
        let c_string_ptr = i64::from_ne_bytes(c_string_ptr_bytes) as usize;

        // Read _len (I64) - after c_string Ptr
        let len_bytes: [u8; 8] = str_bytes[ptr_size..ptr_size+8].try_into()
            .map_err(|_| "extract_str_from_bytes: failed to read _len")?;
        let len = i64::from_ne_bytes(len_bytes) as usize;

        // Read the actual string bytes from heap
        if c_string_ptr == 0 || len == 0 {
            return Ok(String::new());
        }
        let string_bytes = EvalHeap::g().get(c_string_ptr, len);
        String::from_utf8(string_bytes.to_vec())
            .map_err(|_| "extract_str_from_bytes: invalid UTF-8 in string".to_string())
    }

    /// Extract string data from a Str at a given offset.
    /// Used by extract_vec_contents for type_name and for Vec<Str> elements.
    fn extract_str_at_offset(ctx: &Context, str_offset: usize) -> Result<String, String> {
        // Str layout: c_string (Ptr), _len (I64), cap (I64)
        let ptr_size = ctx.get_type_size("Ptr")?;

        // Read c_string.data (first field of Ptr)
        let c_string_ptr_bytes: [u8; 8] = EvalHeap::g().get(str_offset, 8).try_into()
            .map_err(|_| "extract_str_at_offset: failed to read c_string ptr")?;
        let c_string_ptr = i64::from_ne_bytes(c_string_ptr_bytes) as usize;

        // Read _len (I64) - after c_string Ptr
        let len_offset = str_offset + ptr_size;
        let len_bytes: [u8; 8] = EvalHeap::g().get(len_offset, 8).try_into()
            .map_err(|_| "extract_str_at_offset: failed to read _len")?;
        let len = i64::from_ne_bytes(len_bytes) as usize;

        // Read the actual string bytes
        if c_string_ptr == 0 || len == 0 {
            return Ok(String::new());
        }
        let string_bytes = EvalHeap::g().get(c_string_ptr, len);
        String::from_utf8(string_bytes.to_vec())
            .map_err(|_| "extract_str_at_offset: invalid UTF-8 in string".to_string())
    }

    /// Check if a type requires heap serialization (contains Ptr fields that point to heap data)
    pub fn type_needs_heap_serialization(ctx: &Context, type_name: &str) -> bool {
        match type_name {
            "Vec" | "List" => true,
            // Str doesn't need it because string literals are already static in C
            // (the c_string pointer points to string literal data)
            _ => {
                // Check if this is a struct with Vec/List fields
                if let Some(struct_def) = ctx.scope_stack.lookup_struct(type_name) {
                    for member in &struct_def.members {
                        if member.is_mut {
                            if let ValueType::TCustom(field_type) = &member.value_type {
                                if Self::type_needs_heap_serialization(ctx, field_type) {
                                    return true;
                                }
                            }
                        }
                    }
                }
                false
            }
        }
    }
}
