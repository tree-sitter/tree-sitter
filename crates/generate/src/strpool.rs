use std::{num::NonZeroU32, rc::Rc};

use rustc_hash::FxHashMap;

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

#[derive(Clone, Debug)]
pub struct StrPool {
    strs: Vec<Rc<str>>,
    str_ids: FxHashMap<Rc<str>, StrId>,
}

impl Default for StrPool {
    fn default() -> Self {
        let mut pool = Self {
            strs: Vec::default(),
            str_ids: FxHashMap::default(),
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
        if let Some(&id) = self.str_ids.get(s) {
            return id;
        }
        let owned: Rc<str> = Rc::from(s);
        let id = StrId(NonZeroU32::new(self.strs.len() as u32 + 1).unwrap());
        self.strs.push(Rc::clone(&owned));
        self.str_ids.insert(owned, id);
        id
    }

    #[must_use]
    pub fn resolve(&self, id: StrId) -> &str {
        &self.strs[id.index()]
    }
}
