use std::hash::{Hash, Hasher};

/// A bit vector backed by Vec<u64> that supports efficient word-level bulk
/// operations. Token sets are OR'd together many of times and doing this at
/// the word level rather than bit-by-bit is much faster.
#[derive(Clone, Default)]
pub struct BitVec {
    pub(crate) data: Vec<u64>,
    num_bits: usize,
}

impl BitVec {
    pub const fn new() -> Self {
        Self {
            data: Vec::new(),
            num_bits: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.num_bits
    }

    pub fn get(&self, index: usize) -> Option<bool> {
        if index >= self.num_bits {
            return None;
        }
        Some(self.data[index / 64] >> (index % 64) & 1 != 0)
    }

    pub fn set(&mut self, index: usize, val: bool) {
        let word_idx = index / 64;
        let bit_idx = index % 64;
        if val {
            self.data[word_idx] |= 1u64 << bit_idx;
        } else {
            self.data[word_idx] &= !(1u64 << bit_idx);
        }
    }

    pub fn resize(&mut self, new_len: usize, val: bool) {
        let fill = if val { !0u64 } else { 0u64 };
        self.data.resize((new_len + 63) / 64, fill);
        self.num_bits = new_len;
    }

    pub fn last(&self) -> Option<bool> {
        if self.num_bits == 0 {
            return None;
        }
        self.get(self.num_bits - 1)
    }

    pub fn pop(&mut self) -> Option<bool> {
        if self.num_bits == 0 {
            return None;
        }
        self.num_bits -= 1;
        let word_idx = self.num_bits / 64;
        let bit_idx = self.num_bits % 64;
        let val = self.data[word_idx] >> bit_idx & 1 != 0;
        if val {
            self.data[word_idx] &= !(1u64 << bit_idx);
        }
        self.data.truncate((self.num_bits + 63) / 64);
        Some(val)
    }

    /// Word-level OR: self |= other. Returns true if any new bits were set.
    pub fn insert_all(&mut self, other: &Self) -> bool {
        if other.data.len() > self.data.len() {
            self.data.resize(other.data.len(), 0);
        }
        if other.num_bits > self.num_bits {
            self.num_bits = other.num_bits;
        }
        let mut changed = false;
        for (sw, &ow) in self.data.iter_mut().zip(other.data.iter()) {
            let new_bits = ow & !*sw;
            if new_bits != 0 {
                *sw |= ow;
                changed = true;
            }
        }
        changed
    }
}

impl PartialEq for BitVec {
    fn eq(&self, other: &Self) -> bool {
        let max_len = self.data.len().max(other.data.len());
        for i in 0..max_len {
            if self.data.get(i).copied().unwrap_or(0) != other.data.get(i).copied().unwrap_or(0) {
                return false;
            }
        }
        true
    }
}

impl Eq for BitVec {}

impl Hash for BitVec {
    fn hash<H: Hasher>(&self, state: &mut H) {
        let effective_len = self
            .data
            .iter()
            .rposition(|&w| w != 0)
            .map_or(0, |i| i + 1);
        self.data[..effective_len].hash(state);
    }
}

impl Ord for BitVec {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        let max_len = self.data.len().max(other.data.len());
        for i in 0..max_len {
            let a = self.data.get(i).copied().unwrap_or(0);
            let b = other.data.get(i).copied().unwrap_or(0);
            if a != b {
                let first_diff = (a ^ b).trailing_zeros();
                return if (a >> first_diff) & 1 != 0 {
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
        if self.data[index / 64] >> (index % 64) & 1 != 0 {
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
