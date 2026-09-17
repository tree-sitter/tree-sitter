//! Type checking for the native grammar DSL. Entry point is [`check`],
//! invoked after [`super::resolve`] has resolved identifiers.

mod check;
mod error;
pub mod types;

pub use error::{TypeErrorKind, TypeResult};
pub use types::{Constraint, DataTy, ElemTy, InnerTy, ModuleTy, ScalarTy, TupleSig, Ty};

use rustc_hash::FxHashMap;
use serde::{Deserialize, Serialize};

use check::check_item;

use crate::strpool::StrPool;

use super::ast::{ModuleContext, NodeId, SharedAst};

#[derive(Clone, Default)]
pub struct TypeEnv {
    lets: FxHashMap<NodeId, LetState>,
    /// Scratch for `first_unresolved_let_dep`.
    dep_walk: Vec<NodeId>,
    /// Shared work and results stacks for the iterative `type_of` walk. They
    /// live here (rather than per-call) so every walk - including re-entrant
    /// ones - reuses the same capacity-retaining buffers via base-offset
    /// tracking, keeping the traversal off the allocator's hot path.
    work: Vec<check::Work>,
    results: Vec<Ty>,
}

/// The state of a let binding as it progresses through type checking.
#[derive(Clone, Copy)]
enum LetState {
    InProgress,
    Resolved(Ty),
}

/// Walks root items and type-checks the now-resolved AST.
///
/// # Errors
///
/// Returns a `TypeError` on typecheck failure.
pub fn check(
    shared: &SharedAst,
    ctx: &ModuleContext,
    source: &str,
    env: &mut TypeEnv,
    strs: &StrPool,
) -> TypeResult<()> {
    let cx = check::Cx {
        shared,
        ctx,
        source,
        strs,
    };
    for &item_id in &ctx.root_items {
        check_item(cx, item_id, env)?;
    }
    Ok(())
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub enum ContainerKind {
    List,
    Object,
}

impl std::fmt::Display for ContainerKind {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(match self {
            Self::List => "list",
            Self::Object => "object",
        })
    }
}
