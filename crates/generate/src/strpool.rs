use std::{hash::BuildHasher as _, num::NonZeroU32};

use hashbrown::{HashTable, hash_table::Entry};
use rustc_hash::FxBuildHasher;

/// Interned string id, a 1-based index into the pool's string table
#[derive(Clone, Copy, PartialEq, PartialOrd, Ord, Hash, Debug, Eq)]
pub struct StrId(NonZeroU32);

impl StrId {
    /// Dense 0-based index (ids are 1-based).
    #[must_use]
    pub const fn index(self) -> usize {
        self.0.get() as usize - 1
    }

    /// The raw 1-based id, for packed encodings where 0 means "none".
    #[must_use]
    pub const fn raw(self) -> u32 {
        self.0.get()
    }

    /// Inverse of [`Self::raw`]. Caller must pass a value produced by `raw`.
    ///
    /// # Panics
    ///
    /// Panics if `raw` is 0. The resulting [`StrId`] is not guaranteed to belong
    /// to any particular pool.
    #[must_use]
    pub const fn from_raw(raw: u32) -> Self {
        Self(NonZeroU32::new(raw).unwrap())
    }
}

impl Default for StrId {
    fn default() -> Self {
        StrPool::EMPTY_STR_ID
    }
}

/// Byte ranges for interned strings.
#[derive(Clone, Copy, Debug)]
struct StrSpan {
    start: u32,
    end: u32,
}

/// An append-only pool containing UTF-8 strings. Supports up to [`u32::MAX`] bytes
/// of unique strings.
#[derive(Clone, Debug)]
pub struct StrPool {
    /// Bytes of _every_ interned string, concatenated in intern order.
    buf: String,
    /// Byte ranges into `buf` for each string, indexed by [`StrId::index`]
    spans: Vec<StrSpan>,
    /// [`StrId`]s of every interned string
    ids: HashTable<StrId>,
}

impl Default for StrPool {
    fn default() -> Self {
        let mut pool = Self {
            buf: String::new(),
            spans: Vec::new(),
            ids: HashTable::default(),
        };
        let empty_id = pool.intern("");
        debug_assert_eq!(empty_id, Self::EMPTY_STR_ID);
        let end_id = pool.intern("end");
        debug_assert_eq!(end_id, Self::END_NAME_ID);
        pool
    }
}

impl StrPool {
    pub const EMPTY_STR_ID: StrId = StrId::from_raw(1);
    pub const END_NAME_ID: StrId = StrId::from_raw(2);

    pub fn intern(&mut self, s: &str) -> StrId {
        let Self { buf, spans, ids } = self;
        let hash = FxBuildHasher.hash_one(s);
        match ids.entry(
            hash,
            |&id| Self::span_str(buf, spans, id) == s,
            |&id| FxBuildHasher.hash_one(Self::span_str(buf, spans, id)),
        ) {
            Entry::Occupied(entry) => *entry.get(),
            Entry::Vacant(entry) => {
                // The pool is specialized for use only in the generate crate. A
                // pool that has accumulated more than 4GB of data is not a use
                // case we support.
                let start = buf.len();
                let end = start
                    .checked_add(s.len())
                    .and_then(|end| u32::try_from(end).ok())
                    .unwrap();
                // The first two `StrId`s bootstrap `""` and `"end"`. After that,
                // every new string is unique and nonempty, so the entry count remains
                // strictly below the buffer length. The checked `end` bound then
                // also proves that the next 1-based `StrId` fits in a `u32`.
                let raw = spans.len() as u32 + 1;
                // Checking the end proves that both the `start` and `end` fit.
                let start = start as u32;

                // SAFETY: `raw` >= 1
                let id = StrId(unsafe { NonZeroU32::new_unchecked(raw) });
                let span = StrSpan { start, end };

                buf.push_str(s);
                spans.push(span);
                entry.insert(id);
                id
            }
        }
    }

    #[must_use]
    pub fn resolve(&self, id: StrId) -> &str {
        Self::span_str(&self.buf, &self.spans, id)
    }

    fn span_str<'a>(buf: &'a str, spans: &[StrSpan], id: StrId) -> &'a str {
        let span = spans[id.index()];
        let range = span.start as usize..span.end as usize;
        // SAFETY: Spans are private and are only added by `intern`, where `start`
        // and `end` are the buffer lengths before and after appending a complete
        // `str`. Both offsets are therefore in bounds and on UTF-8 boundaries.
        unsafe { buf.get_unchecked(range) }
    }
}
