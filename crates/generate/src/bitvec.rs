use std::{
    hash::{Hash, Hasher},
    ptr,
};

const ARENA_CHUNK_WORDS: usize = 128 * 1024 / std::mem::size_of::<u64>();

struct WordArena {
    chunks: Vec<Vec<u64>>,
    offset: usize,
    /// Freed blocks grouped by size (number of words). Checked before
    /// bump-allocating so that dropped `BitVec`s can be reused immediately.
    free_list: Vec<(usize, Vec<*mut u64>)>,
}

impl WordArena {
    const fn new() -> Self {
        Self {
            chunks: Vec::new(),
            offset: ARENA_CHUNK_WORDS, // forces first alloc to create a chunk
            free_list: Vec::new(),
        }
    }

    #[inline]
    fn alloc(&mut self, n_words: usize) -> *mut u64 {
        if n_words == 0 {
            return std::ptr::NonNull::<u64>::dangling().as_ptr();
        }
        // Check the free list before bump-allocating.
        if let Some((_, bucket)) = self.free_list.iter_mut().find(|(s, _)| *s == n_words)
            && let Some(ptr) = bucket.pop()
        {
            return ptr;
        }
        if self.offset + n_words > ARENA_CHUNK_WORDS {
            let size = ARENA_CHUNK_WORDS.max(n_words);
            self.chunks.push(vec![0u64; size]);
            self.offset = 0;
        }
        let chunk = self.chunks.last_mut().unwrap();
        // SAFETY: Either a new chunk was just created with len = ARENA_CHUNK_WORDS.max(n_words),
        // in which case offset = 0 and n_words <= len; or an existing chunk is reused, in which
        // case offset + n_words <= ARENA_CHUNK_WORDS <= chunk.len().
        let ptr = unsafe { chunk.as_mut_ptr().add(self.offset) };
        self.offset += n_words;
        ptr
    }

    #[inline]
    fn free(&mut self, ptr: *mut u64, n_words: usize, used_words: usize) {
        if n_words == 0 {
            return;
        }
        // Zero only the in-use words; the rest are already zero by the BitVec
        // invariant (data[words_in_use..capacity] is always zero).
        // SAFETY: ptr was returned by alloc(n_words) and is valid for n_words
        // words; used_words <= n_words.
        if used_words > 0 {
            unsafe { std::slice::from_raw_parts_mut(ptr, used_words).fill(0) };
        }
        if let Some((_, bucket)) = self.free_list.iter_mut().find(|(s, _)| *s == n_words) {
            bucket.push(ptr);
        } else {
            self.free_list.push((n_words, vec![ptr]));
        }
    }
}

thread_local! {
    static WORD_ARENA: std::cell::RefCell<WordArena> = const { std::cell::RefCell::new(WordArena::new()) };
}

#[inline]
fn arena_alloc(n_words: usize) -> *mut u64 {
    WORD_ARENA.with(|a| a.borrow_mut().alloc(n_words))
}

#[inline]
fn arena_free(ptr: *mut u64, n_words: usize, used_words: usize) {
    WORD_ARENA.with(|a| a.borrow_mut().free(ptr, n_words, used_words));
}

/// A bit vector whose backing `u64` words are bump-allocated from a global
/// arena. Token sets are OR'd together many times and doing this at the word
/// level rather than bit-by-bit is much faster.
pub struct BitVec {
    /// Pointer into arena chunk data. Dangling when `capacity == 0`.
    data: *mut u64,
    num_bits: u32,
    /// Number of allocated words (_not_ bytes) in the arena region.
    capacity: u32,
}

impl BitVec {
    pub const fn new() -> Self {
        Self {
            data: ptr::NonNull::dangling().as_ptr(),
            num_bits: 0,
            capacity: 0,
        }
    }

    pub fn with_capacity(n_bits: usize) -> Self {
        let n_words = n_bits.div_ceil(64);
        if n_words == 0 {
            return Self::new();
        }
        Self {
            data: arena_alloc(n_words),
            num_bits: 0,
            capacity: n_words as u32,
        }
    }

    #[inline]
    const fn words_in_use(&self) -> usize {
        (self.num_bits as usize).div_ceil(64)
    }

    /// View the in-use words as a slice.
    #[inline]
    pub const fn as_slice(&self) -> &[u64] {
        let n = self.words_in_use();
        if n == 0 {
            &[]
        } else {
            // SAFETY: data points to at least `capacity` valid words, and
            // words_in_use() <= capacity.
            unsafe { std::slice::from_raw_parts(self.data, n) }
        }
    }

    /// View all `capacity` allocated words as a mutable slice.
    #[inline]
    const fn as_full_slice_mut(&mut self) -> &mut [u64] {
        let n = self.capacity as usize;
        if n == 0 {
            return &mut [];
        }
        // SAFETY: data points to `capacity` valid words.
        unsafe { std::slice::from_raw_parts_mut(self.data, n) }
    }

    pub const fn len(&self) -> usize {
        self.num_bits as usize
    }

    pub fn get(&self, index: usize) -> Option<bool> {
        if index >= self.num_bits as usize {
            return None;
        }
        Some(self.as_slice()[index / 64] >> (index % 64) & 1 != 0)
    }

    pub fn set(&mut self, index: usize, val: bool) {
        let word_idx = index / 64;
        let bit_idx = index % 64;
        let words = self.as_full_slice_mut();
        if val {
            words[word_idx] |= 1u64 << bit_idx;
        } else {
            words[word_idx] &= !(1u64 << bit_idx);
        }
    }

    /// Grow the backing storage so that the arena region holds at least
    /// `n_words` words, copying existing data into the new region.
    fn ensure_words(&mut self, n_words: usize) {
        if n_words > self.capacity as usize {
            let new_cap = n_words.max((self.capacity as usize) * 2);
            let new_data = arena_alloc(new_cap);
            let old = self.words_in_use();
            if old > 0 {
                // SAFETY: new_data points to new_cap valid zeroed words; old <= capacity.
                let dst = unsafe { std::slice::from_raw_parts_mut(new_data, old) };
                dst.copy_from_slice(self.as_slice());
            }
            let old_cap = self.capacity;
            let old_data = self.data;
            self.data = new_data;
            self.capacity = new_cap as u32;
            arena_free(old_data, old_cap as usize, old);
        }
    }

    pub fn resize(&mut self, new_len: usize, val: bool) {
        let new_words = new_len.div_ceil(64);
        let old_words = self.words_in_use();
        self.ensure_words(new_words);
        let fill = if val { !0u64 } else { 0u64 };
        let words = self.as_full_slice_mut();
        if new_words > old_words {
            words[old_words..new_words].fill(fill);
            // When setting bits to true, clear any bits in the last word that
            // fall beyond new_len to preserve the invariant that bits >= num_bits
            // are always zero.
            if val && !new_len.is_multiple_of(64) {
                let mask = (1u64 << (new_len % 64)) - 1;
                words[new_words - 1] &= mask;
            }
        } else if new_words < old_words {
            // Zero out truncated words so stale data is never visible.
            words[new_words..old_words].fill(0);
        }
        self.num_bits = new_len as u32;
    }

    pub fn last(&self) -> Option<bool> {
        if self.num_bits == 0 {
            return None;
        }
        self.get(self.num_bits as usize - 1)
    }

    pub fn pop(&mut self) -> Option<bool> {
        if self.num_bits == 0 {
            return None;
        }
        self.num_bits -= 1;
        let word_idx = self.num_bits as usize / 64;
        let bit_idx = self.num_bits as usize % 64;
        let new_words_in_use = self.words_in_use();
        let words = self.as_full_slice_mut();
        let val = words[word_idx] >> bit_idx & 1 != 0;
        if val {
            words[word_idx] &= !(1u64 << bit_idx);
        }
        // Zero out the word if it's no longer in use.
        if word_idx >= new_words_in_use {
            words[word_idx] = 0;
        }
        Some(val)
    }

    /// Word-level OR: self |= other. Returns true if any new bits were set.
    pub fn insert_all(&mut self, other: &Self) -> bool {
        let other_words = other.words_in_use();
        if other_words == 0 {
            return false;
        }
        let self_words = self.words_in_use();
        if other_words > self.capacity as usize {
            // Need a larger arena region.
            let new_data = arena_alloc(other_words);
            if self_words > 0 {
                // SAFETY: new_data points to other_words valid zeroed words; self_words <= capacity.
                let dst = unsafe { std::slice::from_raw_parts_mut(new_data, self_words) };
                dst.copy_from_slice(self.as_slice());
            }
            // Arena memory is pre-zeroed, so words self_words..other_words are already 0.
            let old_cap = self.capacity;
            let old_data = self.data;
            self.data = new_data;
            self.capacity = other_words as u32;
            arena_free(old_data, old_cap as usize, self_words);
        } else if other_words > self_words {
            // Have capacity, but clear any stale data in the region we're about to OR into.
            self.as_full_slice_mut()[self_words..other_words].fill(0);
        }
        if other.num_bits > self.num_bits {
            self.num_bits = other.num_bits;
        }
        let other_slice = other.as_slice();
        let self_slice = &mut self.as_full_slice_mut()[..other_words];
        let mut any_new = 0u64;
        for (sw, &ow) in self_slice.iter_mut().zip(other_slice) {
            let new_bits = ow & !*sw;
            *sw |= ow;
            any_new |= new_bits;
        }
        any_new != 0
    }
}

impl Drop for BitVec {
    fn drop(&mut self) {
        if self.capacity > 0 {
            arena_free(self.data, self.capacity as usize, self.words_in_use());
        }
    }
}

impl Default for BitVec {
    fn default() -> Self {
        Self::new()
    }
}

impl Clone for BitVec {
    fn clone(&self) -> Self {
        let words = self.words_in_use();
        if words == 0 {
            return Self::new();
        }
        let new_data = arena_alloc(words);
        // SAFETY: new_data points to `words` valid zeroed words.
        let dst = unsafe { std::slice::from_raw_parts_mut(new_data, words) };
        dst.copy_from_slice(self.as_slice());
        Self {
            data: new_data,
            num_bits: self.num_bits,
            capacity: words as u32,
        }
    }
}

impl PartialEq for BitVec {
    fn eq(&self, other: &Self) -> bool {
        let a = self.as_slice();
        let b = other.as_slice();
        let max_len = a.len().max(b.len());
        for i in 0..max_len {
            if a.get(i).copied().unwrap_or(0) != b.get(i).copied().unwrap_or(0) {
                return false;
            }
        }
        true
    }
}

impl Eq for BitVec {}

impl Hash for BitVec {
    fn hash<H: Hasher>(&self, state: &mut H) {
        let data = self.as_slice();
        let effective_len = data.iter().rposition(|&w| w != 0).map_or(0, |i| i + 1);
        data[..effective_len].hash(state);
    }
}

impl Ord for BitVec {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        let a = self.as_slice();
        let b = other.as_slice();
        let max_len = a.len().max(b.len());
        for i in 0..max_len {
            let aw = a.get(i).copied().unwrap_or(0);
            let bw = b.get(i).copied().unwrap_or(0);
            if aw != bw {
                let first_diff = (aw ^ bw).trailing_zeros();
                return if (aw >> first_diff) & 1 != 0 {
                    std::cmp::Ordering::Greater
                } else {
                    std::cmp::Ordering::Less
                };
            }
        }
        std::cmp::Ordering::Equal
    }
}

impl PartialOrd for BitVec {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl std::ops::Index<usize> for BitVec {
    type Output = bool;

    fn index(&self, index: usize) -> &Self::Output {
        static TRUE: bool = true;
        static FALSE: bool = false;
        if self.as_slice()[index / 64] >> (index % 64) & 1 != 0 {
            &TRUE
        } else {
            &FALSE
        }
    }
}

/// Iterator that yields only the indices of set bits, skipping zero words
/// entirely and using `trailing_zeros()` within each word.
pub struct SetBitsIter<'a> {
    data: &'a [u64],
    word_idx: usize,
    current_word: u64,
}

impl<'a> SetBitsIter<'a> {
    pub fn new(data: &'a [u64]) -> Self {
        Self {
            data,
            word_idx: 0,
            current_word: data.first().copied().unwrap_or(0),
        }
    }
}

impl Iterator for SetBitsIter<'_> {
    type Item = usize;

    fn next(&mut self) -> Option<usize> {
        while self.current_word == 0 {
            self.word_idx += 1;
            if self.word_idx >= self.data.len() {
                return None;
            }
            self.current_word = self.data[self.word_idx];
        }
        let bit = self.current_word.trailing_zeros() as usize;
        self.current_word &= self.current_word - 1; // clear lowest set bit
        Some(self.word_idx * 64 + bit)
    }
}
