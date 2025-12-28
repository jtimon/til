#![allow(static_mut_refs)]

// Arena: Low-level memory management
// Simple bump allocator with get/set/put/reserve operations.
// TIL equivalent: src/std/arena.til

static mut ARENA_MEMORY: Vec<u8> = Vec::new();

pub struct Arena;

impl Arena {
    pub const INITIAL_CAPACITY: usize = 32768;  // 32KB

    /// Create a new Arena
    pub fn new() -> Arena {
        unsafe {
            if ARENA_MEMORY.is_empty() {
                ARENA_MEMORY.reserve(Self::INITIAL_CAPACITY);
                ARENA_MEMORY.push(0);  // REM: first address 0 is reserved (invalid), malloc always >0
            }
        }
        Arena
    }

    /// Get current used length of arena memory
    pub fn len(&self) -> usize {
        unsafe { ARENA_MEMORY.len() }
    }

    /// Get size in bytes (same as len for Arena)
    #[allow(dead_code)]
    pub fn size(&self) -> usize {
        unsafe { ARENA_MEMORY.len() }
    }

    /// Append bytes to arena, return offset where they were placed
    pub fn put(&mut self, bytes: &[u8]) -> Result<usize, String> {
        let offset = unsafe { ARENA_MEMORY.len() };
        unsafe { ARENA_MEMORY.extend_from_slice(bytes); }
        Ok(offset)
    }

    /// Read bytes from arena at offset
    pub fn get(&self, offset: usize, len: usize) -> &[u8] {
        unsafe { &ARENA_MEMORY[offset..offset + len] }
    }

    /// Write bytes to arena at offset
    pub fn set(&mut self, offset: usize, bytes: &[u8]) -> Result<(), String> {
        unsafe { ARENA_MEMORY[offset..offset + bytes.len()].copy_from_slice(bytes); }
        Ok(())
    }

    /// Reserve space in arena, return offset where space was allocated
    pub fn reserve(&mut self, size: usize) -> Result<usize, String> {
        let offset = unsafe { ARENA_MEMORY.len() };
        unsafe { ARENA_MEMORY.extend(std::iter::repeat(0u8).take(size)); }
        Ok(offset)
    }
}
