#![allow(dead_code)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]

include!("./bindings.rs");

extern "C" {
    pub(crate) fn dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}

use crate::{Language, Node, Parser, Query, QueryCursor, QueryError, Tree, TreeCursor};
use std::{marker::PhantomData, mem::ManuallyDrop, ptr::NonNull, str};

impl Language {
    /// Reconstructs a [Language] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSLanguage) -> Language {
        Language(ptr)
    }

    /// Consumes the [Language], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *const TSLanguage {
        ManuallyDrop::new(self).0
    }
}

impl Parser {
    /// Reconstructs a [Parser] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSParser) -> Parser {
        Parser(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [Parser], returning a raw pointer to the underlying C structure.
    pub fn into_raw(mut self) -> *mut TSParser {
        self.stop_printing_dot_graphs();
        self.set_logger(None);

        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl Tree {
    /// Reconstructs a [Tree] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSTree) -> Tree {
        Tree(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [Tree], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSTree {
        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl<'tree> Node<'tree> {
    /// Reconstructs a [Node] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSNode) -> Node<'tree> {
        Node(*ptr, PhantomData)
    }

    /// Consumes the [Node], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSNode {
        &mut ManuallyDrop::new(self).0
    }
}

impl<'a> TreeCursor<'a> {
    /// Reconstructs a [TreeCursor] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSTreeCursor) -> TreeCursor<'a> {
        TreeCursor(*ptr, PhantomData)
    }

    /// Consumes the [TreeCursor], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSTreeCursor {
        &mut ManuallyDrop::new(self).0
    }
}

impl Query {
    /// Reconstructs a [Query] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSQuery, source: &str) -> Result<Query, QueryError> {
        Query::from_raw_parts(ptr, source)
    }

    /// Consumes the [Query], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSQuery {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}

impl QueryCursor {
    /// Reconstructs a [QueryCursor] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSQueryCursor) -> QueryCursor {
        QueryCursor {
            ptr: NonNull::new_unchecked(ptr),
        }
    }

    /// Consumes the [QueryCursor], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSQueryCursor {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}
