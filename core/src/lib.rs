#![allow(dead_code)]
#![allow(mutable_transmutes)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(unused_assignments)]
#![allow(unused_mut)]

#[macro_use]
extern crate c2rust_bitfields;
extern crate once_cell;

pub mod api;
mod get_changed_ranges;
mod language;
mod lexer;
mod node;
mod parser;
mod query;
mod reusable_node;
mod stack;
mod subtree;
mod tree;
mod tree_cursor;
mod util;

#[cfg(feature = "capi")]
mod capi;

pub use api::*;

#[cfg(feature = "capi")]
pub use capi::*;

use reusable_node::*;
