//! Arena-based AST for the native grammar DSL.
//!
//! Split across:
//!
//! - [`span`]: source [`Span`]s and span-tagged [`Spanned`] values.
//! - [`node`]: the core [`Node`] enum and its payload data.
//! - [`arena`]: [`NodeId`] handles and the backing [`NodeArena`].
//! - [`pools`]: side-table handles/containers and their element types.
//! - [`module`]: per-module parser output ([`ModuleContext`], [`GrammarConfig`]).

mod arena;
mod module;
mod node;
mod pools;
mod span;

pub use arena::{NodeArena, NodeId};
pub use module::{ConfigField, GrammarConfig, ModuleContext};
pub use node::{BinOp, IdentKind, Node, PrecKind, RepeatKind};
pub use pools::{
    AstPools, ChildRange, ExpandId, Expansion, ForConfig, ForId, MacroConfig, MacroId, MacroKind,
    ObjectField, Param, SharedAst,
};
pub use span::{Span, Spanned};
