// Arena: Low-level memory management
// Simple bump allocator with get/set/put/reserve operations.
// Rust EvalArena must be 2x TIL EvalArena for `rstil interpret src/til.til interpret`.
// TIL equivalent: src/std/arena.til

pub const ARENA_SIZE: usize = 16777216;  // 16MB

static mut ARENA_MEMORY: [u8; ARENA_SIZE] = [0; ARENA_SIZE];

pub struct Arena {
    pub _len: usize,
}

impl Arena {
    /// Create a new Arena
    pub fn new() -> Arena {
        Arena {
            _len: 1,  // Reserve first address 0 (invalid), malloc always >0
        }
    }

    /// Get current used length of arena memory
    pub fn len(&self) -> usize {
        return self._len;
    }

    /// Get size in bytes (same as len for Arena)
    pub fn size(&self) -> usize {
        return self._len;
    }

    /// Append bytes to arena, return offset where they were placed
    pub fn put(&mut self, bytes: &[u8]) -> Result<usize, String> {
        let offset = self._len;
        let new_len = offset + bytes.len();
        if new_len > ARENA_SIZE { return Err("arena overflow".to_string()); }
        unsafe {
            ARENA_MEMORY[offset..new_len].copy_from_slice(bytes);
        }
        self._len = new_len;
        return Ok(offset);
    }

    /// Read bytes from arena at offset
    pub fn get(&self, offset: usize, len: usize) -> &[u8] {
        unsafe {
            return &ARENA_MEMORY[offset..offset + len];
        }
    }

    /// Write bytes to arena at offset
    pub fn set(&mut self, offset: usize, bytes: &[u8]) -> Result<(), String> {
        let end = offset + bytes.len();
        if end > ARENA_SIZE { return Err("arena overflow".to_string()); }
        unsafe {
            ARENA_MEMORY[offset..end].copy_from_slice(bytes);
        }
        Ok(())
    }

    /// Reserve space in arena, return offset where space was allocated
    pub fn reserve(&mut self, size: usize) -> Result<usize, String> {
        let offset = self._len;
        let new_len = offset + size;
        if new_len > ARENA_SIZE { return Err("arena overflow".to_string()); }
        self._len = new_len;
        return Ok(offset);
    }
}
