#![allow(dead_code)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]

include!("./bindings.rs");

extern "C" {
    pub(crate) fn dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}

use crate::{Language, Node, Parser, Query, QueryCursor, Tree, TreeCursor};
use std::mem::ManuallyDrop;

impl Language {
    /// Consumes the [Language], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *const TSLanguage {
        ManuallyDrop::new(self).0
    }
}

impl Parser {
    /// Consumes the [Parser], returning a raw pointer to the underlying C structure.
    pub fn into_raw(mut self) -> *mut TSParser {
        self.stop_printing_dot_graphs();
        self.set_logger(None);

        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl Tree {
    /// Consumes the [Tree], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSTree {
        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl<'tree> Node<'tree> {
    /// Consumes the [Node], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSNode {
        &mut ManuallyDrop::new(self).0
    }
}

impl<'a> TreeCursor<'a> {
    /// Consumes the [TreeCursor], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSTreeCursor {
        &mut ManuallyDrop::new(self).0
    }
}

impl Query {
    /// Consumes the [Query], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSQuery {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}

impl QueryCursor {
    /// Consumes the [QueryCursor], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSQueryCursor {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}
