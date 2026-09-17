//! Intermediate representation used during lowering.

use rustc_hash::FxHashMap;

use crate::rules::RuleId;
use crate::strpool::StrId;

use super::super::ModuleId;
use super::super::ast::ChildRange;

/// Index into the lowering value pool.
#[derive(Clone, Copy, PartialEq, Eq)]
pub struct ValueId(pub u32);

#[derive(Clone, Copy, Debug)]
pub enum Value {
    Int(i32),
    Str(StrId),
    Rule(RuleId),
    /// Index into [`IrPools::object_pool`].
    Object(u32),
    /// Range into [`IrPools::value_children`].
    List(ChildRange),
    /// Range into [`IrPools::value_children`].
    Tuple(ChildRange),
    Module(ModuleId),
}

/// Pools holding the intermediate IR being built during lowering. Indices
/// (`ValueId`, `StrId`, `ChildRange`) are stable for the lifetime
/// of the parse call so the cross-grammar [`LoweringState::lets`] cache
/// can keep referencing earlier-grammar entries.
#[derive(Default)]
pub struct IrPools {
    pub values: Vec<Value>,
    pub value_children: Vec<ValueId>,
    pub object_pool: Vec<FxHashMap<StrId, ValueId>>,
}
