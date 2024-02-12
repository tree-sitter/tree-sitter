#![allow(dead_code)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]

#[cfg(feature = "bindgen")]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(not(feature = "bindgen"))]
include!("./bindings.rs");

#[cfg(unix)]
extern "C" {
    pub(crate) fn _ts_dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}

#[cfg(windows)]
extern "C" {
    pub(crate) fn _ts_dup(handle: *mut std::os::raw::c_void) -> std::os::raw::c_int;
}

use crate::{
    Language, LookaheadIterator, Node, Parser, Query, QueryCursor, QueryError, Tree, TreeCursor,
};
use std::{marker::PhantomData, mem::ManuallyDrop, ptr::NonNull, str};

impl Language {
    /// Reconstructs a [`Language`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(ptr: *const TSLanguage) -> Self {
        Self(ptr)
    }

    /// Consumes the [`Language`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> *const TSLanguage {
        ManuallyDrop::new(self).0
    }
}

impl Parser {
    /// Reconstructs a [`Parser`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(ptr: *mut TSParser) -> Self {
        Self(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [`Parser`], returning a raw pointer to the underlying C structure.
    ///
    /// # Safety
    ///
    /// It's a caller responsibility to adjust parser's state
    /// like disable logging or dot graphs printing if this
    /// may cause issues like use after free.
    #[must_use]
    pub fn into_raw(self) -> *mut TSParser {
        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl Tree {
    /// Reconstructs a [`Tree`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(ptr: *mut TSTree) -> Self {
        Self(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [`Tree`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> *mut TSTree {
        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl<'tree> Node<'tree> {
    /// Reconstructs a [`Node`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(raw: TSNode) -> Node<'tree> {
        Self(raw, PhantomData)
    }

    /// Consumes the [`Node`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> TSNode {
        ManuallyDrop::new(self).0
    }
}

impl<'a> TreeCursor<'a> {
    /// Reconstructs a [`TreeCursor`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(raw: TSTreeCursor) -> TreeCursor<'a> {
        Self(raw, PhantomData)
    }

    /// Consumes the [`TreeCursor`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> TSTreeCursor {
        ManuallyDrop::new(self).0
    }
}

impl Query {
    /// Reconstructs a [`Query`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSQuery, source: &str) -> Result<Self, QueryError> {
        Self::from_raw_parts(ptr, source)
    }

    /// Consumes the [`Query`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> *mut TSQuery {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}

impl QueryCursor {
    /// Reconstructs a [`QueryCursor`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(ptr: *mut TSQueryCursor) -> Self {
        Self {
            ptr: NonNull::new_unchecked(ptr),
        }
    }

    /// Consumes the [`QueryCursor`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> *mut TSQueryCursor {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}

impl LookaheadIterator {
    /// Reconstructs a [`LookaheadIterator`] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    #[must_use]
    pub const unsafe fn from_raw(ptr: *mut TSLookaheadIterator) -> Self {
        Self(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [`LookaheadIterator`], returning a raw pointer to the underlying C structure.
    #[must_use]
    pub fn into_raw(self) -> *mut TSLookaheadIterator {
        ManuallyDrop::new(self).0.as_ptr()
    }
}
