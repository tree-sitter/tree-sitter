//! Pre-typecheck name resolution for the native grammar DSL.
//!
//! The loader runs these phases over one module, in order:
//!
//! - [`collect_decls`] registers the names the module's own items declare
//! - [`resolve_qualified_call_targets`] resolves the callee of every top-level
//!   `@mod::name(..)`, which `expand_macro_calls` then inlines
//! - [`register_expanded_decls`] registers the names those expansions produced
//! - [`finish_decls`] adds inherited, imported, external, and forward names
//! - [`resolve_with_decls`] rewrites `Ident(Unresolved)` nodes to
//!   `Ident(Rule | Var(_) | Macro(_))` and resolves `mod::name` accesses

use rustc_hash::{FxBuildHasher, FxHashMap, FxHashSet};
use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::{
    nativedsl::{
        DocumentSpan, Export, ImportedRule, LoweredGrammar, Module, ModuleId, Note, NoteMessage,
        ResolveError,
        ast::{
            AstPools, IdentKind, MacroId, ModuleContext, Node, NodeArena, NodeId, SharedAst, Span,
            Spanned,
        },
        diagnostic::suggest_name,
    },
    rules::{Rule, RulePool},
    strpool::{StrId, StrPool},
};

use std::collections::hash_map::Entry;

pub type ResolveResult<T> = Result<T, ResolveError>;

#[derive(Debug, PartialEq, Eq, Serialize, Deserialize, Error)]
pub enum ResolveErrorKind {
    #[error("imported module has no member '{0}'")]
    ImportMemberNotFound(String),
    #[error("duplicate declaration '{0}'")]
    DuplicateDeclaration(String),
    #[error("unknown identifier '{0}'")]
    UnknownIdentifier(String),
    #[error("computed rule name '{0}' does not name a rule")]
    ComputedNameNotARule(String),
    #[error("let '{0}' is defined in terms of itself")]
    CircularLet(String),
    #[error(
        "`externals` must be a list of token names, strings, or `regexp()` expressions, \
       formed with list literals, `append()`, or variable/config references"
    )]
    InvalidExternalsExpression,
}

/// Intermediate resolve environment used during phase 1. Maps declaration
/// names to their resolved kind (for Ident rewriting) and span
/// (for duplicate checking / "first defined here" notes). The kind never
/// stores [`IdentKind::Unresolved`] - by the time a name reaches the table
/// we know what it resolves to.
type Decls = FxHashMap<StrId, Spanned<DeclKind>>;

pub(crate) struct CollectedDecls {
    decls: Decls,
    override_names: FxHashSet<StrId>,
    deferred_qualified_calls: Vec<DeferredQualifiedCall>,
}

impl CollectedDecls {
    #[must_use]
    pub(crate) const fn has_qualified_calls(&self) -> bool {
        !self.deferred_qualified_calls.is_empty()
    }

    pub(crate) fn qualified_calls(&self) -> &[DeferredQualifiedCall] {
        &self.deferred_qualified_calls
    }
}

/// A top-level `@mod::name(..)`, left for expansion once child modules load.
pub(crate) struct DeferredQualifiedCall {
    /// Index of the call in `root_items`.
    pub slot: usize,
    pub call_id: NodeId,
    /// Filled in by [`resolve_qualified_call_targets`], and left `None` when
    /// the receiver does not name a module.
    pub target: Option<QualifiedTarget>,
}

/// A top level qualified call's resolved callee.
#[derive(Clone, Copy)]
pub(crate) struct QualifiedTarget {
    /// Module the receiver names, the one declaring `member`.
    pub module: ModuleId,
    /// Member name after `::`.
    pub member: StrId,
    pub export: Export,
}

/// What a declared name denotes
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum DeclKind {
    Rule,
    Var(NodeId),
    Macro(MacroId),
}

impl DeclKind {
    /// The [`IdentKind`] a reference to `name` takes on once it resolves.
    const fn to_ident(self, name: StrId) -> IdentKind {
        match self {
            Self::Rule => IdentKind::Rule(name),
            Self::Var(id) => IdentKind::Var(id),
            Self::Macro(id) => IdentKind::Macro(id),
        }
    }
}

/// Read-only context threaded through the pass-2 resolve walk
/// ([`resolve_item`] / [`resolve_expr`] / [`resolve_children`]).
struct ResolveCtx<'a> {
    pools: &'a AstPools,
    ctx: &'a ModuleContext,
    strs: &'a StrPool,
    decls: &'a Decls,
    modules: &'a [Module],
}

pub(crate) fn resolve_with_decls(
    shared: &mut SharedAst,
    ctx: &ModuleContext,
    pool: &RulePool,
    modules: &[Module],
    collected: &CollectedDecls,
) -> ResolveResult<()> {
    let decls = &collected.decls;

    let rcx = ResolveCtx {
        pools: &shared.pools,
        ctx,
        strs: pool.strs(),
        decls,
        modules,
    };

    // Validate computed-name references (`@<expr>`), evaluated under each call's
    // args at expand, against the complete name table.
    for &(name, at) in &ctx.computed_refs {
        // Must resolve to a rule: lower emits a NamedSymbol for whatever name
        // this is, so a let/macro match would lower a dangling symbol.
        match rcx.decls.get(&name).map(|d| d.value) {
            Some(DeclKind::Rule) => {}
            Some(_) => Err(ResolveError::new(
                ResolveErrorKind::ComputedNameNotARule(rcx.strs.resolve(name).to_string()),
                at.document,
                at.span,
            ))?,
            None => Err(unknown_ident_error(&rcx, rcx.strs.resolve(name), at))?,
        }
    }

    let mut stack = Vec::with_capacity(ctx.root_items.len());
    for &item_id in &ctx.root_items {
        resolve_item(&mut shared.arena, &rcx, item_id, &mut stack)?;
    }

    Ok(())
}

/// Resolve the targets of top-level qualified calls before late expansion.
///
/// Receivers that cannot be resolved yet, or that do not name a module, are left
/// deferred. The call's `target` stays `None` and the call survives into
/// `root_items`, where `resolve_with_decls` and typecheck diagnose it against the
/// full declaration table.
pub(crate) fn resolve_qualified_call_targets(
    shared: &mut SharedAst,
    ctx: &ModuleContext,
    pool: &RulePool,
    modules: &[Module],
    collected: &mut CollectedDecls,
) -> ResolveResult<()> {
    let rcx = ResolveCtx {
        pools: &shared.pools,
        ctx,
        strs: pool.strs(),
        decls: &collected.decls,
        modules,
    };
    let mut stack = Vec::new();

    for DeferredQualifiedCall {
        call_id, target, ..
    } in &mut collected.deferred_qualified_calls
    {
        expect_pat!(Node::Call { name, .. }, *shared.arena.get(*call_id));
        expect_pat!(
            Node::QualifiedAccess {
                obj,
                member,
                member_offset,
            },
            *shared.arena.get(name)
        );

        // Resolve nested qualified accesses and the initial module alias before
        // looking up the final member. Failures defer to be caught by `resolve_with_decls`
        // and typecheck against the full declaration table.
        if resolve_expr(&mut shared.arena, &rcx, obj, &mut stack).is_err() {
            continue;
        }
        // Follow `let` aliases to the underlying import/inherit, resolving each
        // value on demand: this pass runs before resolve_with_decls, so alias
        // values may still be unresolved. A chain longer than the arena has
        // cycled. Let typecheck report the cycle on the surviving call.
        let mut module = None;
        let mut target_id = obj;
        for _ in 0..shared.arena.len() {
            match *shared.arena.get(target_id) {
                Node::Ident(IdentKind::Var(let_id)) => {
                    expect_pat!(Node::Let { value, .. }, *shared.arena.get(let_id));
                    if resolve_expr(&mut shared.arena, &rcx, value, &mut stack).is_err() {
                        break;
                    }
                    target_id = value;
                }
                Node::Inherit { module: idx, .. } | Node::Import { module: idx, .. } => {
                    module = idx;
                    break;
                }
                _ => break,
            }
        }
        let Some(module) = module else {
            continue;
        };
        *target = Some(resolve_qualified_member(
            &rcx,
            &mut shared.arena,
            module,
            name,
            member,
            member_offset,
        )?);
    }

    Ok(())
}

fn insert_decl(
    decls: &mut Decls,
    strs: &StrPool,
    name: StrId,
    kind: DeclKind,
    span: Span,
    ctx: &ModuleContext,
) -> ResolveResult<()> {
    match decls.entry(name) {
        Entry::Occupied(entry) => {
            let existing = entry.get().span;
            let (duplicate, first) = if existing.start > span.start {
                (existing, span)
            } else {
                (span, existing)
            };
            Err(ResolveError::with_note(
                ResolveErrorKind::DuplicateDeclaration(strs.resolve(name).to_string()),
                ctx.document,
                duplicate,
                ctx.note(NoteMessage::FirstDefinedHere, first),
            ))
        }
        Entry::Vacant(entry) => {
            entry.insert(Spanned::new(kind, span));
            Ok(())
        }
    }
}

/// Pass 1: scan top-level items and register all declared names.
///
/// Rules, let-bindings, macros, and external tokens in the grammar block
/// all occupy the same namespace. Duplicate names are rejected.
///
/// `base` is the inherited grammar (if any). Its rule names are registered
/// before the externals walk so that an `externals` field referencing an
/// inherited rule is correctly identified as a known name rather than being
/// re-registered as a fresh external token.
pub(crate) fn collect_decls(
    shared: &mut SharedAst,
    ctx: &ModuleContext,
    pool: &RulePool,
    base: Option<(&LoweredGrammar, Span)>,
    imported_rules: &[ImportedRule],
    current_module: ModuleId,
) -> ResolveResult<CollectedDecls> {
    let root_items = &ctx.root_items;
    let external_capacity = ctx
        .grammar_config
        .as_ref()
        .and_then(|config| config.externals)
        .and_then(|id| shared.arena.get(id).child_range())
        .map_or(0, |range| range.len as usize);
    let decl_capacity = root_items.len()
        + base.map_or(0, |(grammar, _)| grammar.variables.len())
        + imported_rules.len()
        + external_capacity;
    let mut decls = FxHashMap::with_capacity_and_hasher(decl_capacity, FxBuildHasher);
    let mut override_names = FxHashSet::default();
    let mut deferred_qualified_calls = Vec::new();

    // Register rules, macros, and lets upfront (forward references allowed).
    for (slot, &item_id) in root_items.iter().enumerate() {
        let span = shared.arena.span(item_id);
        match shared.arena.get(item_id) {
            Node::Rule {
                name, is_override, ..
            } => {
                insert_decl(&mut decls, pool.strs(), *name, DeclKind::Rule, span, ctx)?;
                if *is_override {
                    override_names.insert(*name);
                }
            }
            Node::ExpandedRule(expand_id) => {
                let exp = shared.pools.get_expansion(*expand_id);
                insert_decl(&mut decls, pool.strs(), exp.name, DeclKind::Rule, span, ctx)?;
                if exp.is_override {
                    override_names.insert(exp.name);
                }
            }
            Node::Macro(macro_id) => {
                shared
                    .pools
                    .get_macro_mut(*macro_id)
                    .set_def_module(current_module);
                let config = shared.pools.get_macro(*macro_id);
                insert_decl(
                    &mut decls,
                    pool.strs(),
                    config.name.value,
                    DeclKind::Macro(*macro_id),
                    span,
                    ctx,
                )?;
            }
            Node::Let { name, .. } => {
                insert_decl(
                    &mut decls,
                    pool.strs(),
                    *name,
                    DeclKind::Var(item_id),
                    span,
                    ctx,
                )?;
            }
            Node::Call { name, .. }
                if matches!(shared.arena.get(*name), Node::QualifiedAccess { .. }) =>
            {
                deferred_qualified_calls.push(DeferredQualifiedCall {
                    slot,
                    call_id: item_id,
                    target: None,
                });
            }
            // Forward-declarations are registered after all real declarations.
            _ => {}
        }
    }

    Ok(CollectedDecls {
        decls,
        override_names,
        deferred_qualified_calls,
    })
}

pub(crate) fn finish_decls(
    collected: &mut CollectedDecls,
    shared: &SharedAst,
    ctx: &ModuleContext,
    pool: &RulePool,
    base: Option<(&LoweredGrammar, Span)>,
    imported_rules: &[ImportedRule],
) -> ResolveResult<()> {
    let decls = &mut collected.decls;
    let override_names = &mut collected.override_names;

    // Register inherited rule names. Collisions with local non-`override` rules error
    if let Some((base_grammar, inherit_span)) = base {
        for var in &base_grammar.variables {
            // The first source of an overridden name coexists with the override
            // (claim it by removing). A later source is no longer skipped and so
            // collides as a duplicate, exactly as it would without the override.
            if override_names.remove(&var.name) {
                continue;
            }
            insert_decl(
                decls,
                pool.strs(),
                var.name,
                DeclKind::Rule,
                inherit_span,
                ctx,
            )?;
        }
        // Inherited named external tokens are referenceable by bare name, like
        // inherited rules. Anonymous externals have no name to bring into scope.
        // A base rule may also appear in `externals`, so skip names already
        // registered by the rule loop.
        let mut base_variable_names: Option<FxHashSet<StrId>> = None;
        for ext in &base_grammar.external_roots {
            if let Rule::NamedSymbol(name) = pool.node(*ext)
                && !override_names.contains(&name)
            {
                let base_variable_names = base_variable_names
                    .get_or_insert_with(|| base_grammar.variables.iter().map(|v| v.name).collect());
                if base_variable_names.contains(&name) {
                    continue;
                }
                insert_decl(decls, pool.strs(), name, DeclKind::Rule, inherit_span, ctx)?;
            }
        }
    }

    // Register bare names for every transitively imported library rule.
    for ir in imported_rules {
        // First source of an overridden name claims the override. A later
        // source is no longer skipped and collides (see the base loop above).
        if !override_names.remove(&ir.name) {
            insert_decl(
                decls,
                pool.strs(),
                ir.name,
                DeclKind::Rule,
                ir.ref_span,
                ctx,
            )?;
        }
    }

    // Pre-register external token names. Externals are the only config field
    // that introduces names not declared as rules in the grammar file.
    if let Some(config) = &ctx.grammar_config
        && let Some(ext_id) = config.externals
    {
        let mut ec = ExternalNameCtx {
            shared,
            ctx,
            strs: pool.strs(),
            decls,
            expanding_lets: FxHashSet::default(),
        };
        ec.collect(ext_id)?;
    }

    // Forward-declarations name a symbol provided elsewhere. Register them only
    // when no real declaration fulfilled the name; lower reports unfulfilled
    // declarations during its symbol-completeness check.
    if ctx.has_forward_decls {
        for &item_id in &ctx.root_items {
            let Node::Forward { name } = shared.arena.get(item_id) else {
                continue;
            };
            let span = shared.arena.span(item_id);
            decls
                .entry(*name)
                .or_insert_with(|| Spanned::new(DeclKind::Rule, span));
        }
    }

    Ok(())
}

/// Register the rules that qualified rule-set expansion produced, reading them
/// back off the nodes it pushed. Runs before [`finish_decls`], so a generated
/// `override rule` still claims its inherited name.
pub(crate) fn register_expanded_decls(
    collected: &mut CollectedDecls,
    shared: &SharedAst,
    strs: &StrPool,
    ctx: &ModuleContext,
) -> ResolveResult<()> {
    for (id, node) in ctx.late_nodes(&shared.arena) {
        expect_pat!(Node::ExpandedRule(expand_id), *node);
        let exp = shared.pools.get_expansion(expand_id);
        let span = shared.arena.span(id);
        insert_decl(
            &mut collected.decls,
            strs,
            exp.name,
            DeclKind::Rule,
            span,
            ctx,
        )?;
        if exp.is_override {
            collected.override_names.insert(exp.name);
        }
    }
    Ok(())
}

/// State for recursively collecting external token names.
struct ExternalNameCtx<'a> {
    shared: &'a SharedAst,
    ctx: &'a ModuleContext,
    strs: &'a StrPool,
    decls: &'a mut Decls,
    /// `let` names currently being expanded; reentry indicates a cycle.
    expanding_lets: FxHashSet<StrId>,
}

impl ExternalNameCtx<'_> {
    /// Recursively collect external token names from an expression.
    fn collect(&mut self, id: NodeId) -> ResolveResult<()> {
        match *self.shared.arena.get(id) {
            // Bare identifier: follow a let, ignore an already-declared name, or
            // register an unknown name as a new external token.
            Node::Ident(IdentKind::Unresolved(name)) => {
                match self.decls.get(&name).map(|d| d.value) {
                    Some(DeclKind::Var(let_id)) => {
                        if !self.expanding_lets.insert(name) {
                            return Err(ResolveError::with_note(
                                ResolveErrorKind::CircularLet(self.strs.resolve(name).to_string()),
                                self.ctx.document,
                                self.shared.arena.span(let_id),
                                self.ctx.note(
                                    NoteMessage::SelfReferenceHere,
                                    self.shared.arena.span(id),
                                ),
                            ));
                        }
                        expect_pat!(Node::Let { value, .. }, *self.shared.arena.get(let_id));
                        self.collect(value)?;
                        self.expanding_lets.remove(&name);
                    }
                    None => insert_decl(
                        self.decls,
                        self.strs,
                        name,
                        DeclKind::Rule,
                        self.shared.arena.span(id),
                        self.ctx,
                    )?,
                    Some(_) => {}
                }
            }
            Node::List(range) | Node::Tuple(range) => {
                for &child in self.shared.pools.child_slice(range) {
                    self.collect(child)?;
                }
            }
            Node::Append { left, right } => {
                self.collect(left)?;
                self.collect(right)?;
            }
            // Literals and config references don't introduce names.
            #[rustfmt::skip]
            Node::StringLit(_) | Node::IntLit(_) | Node::DynRegex { .. } | Node::GrammarConfig { .. }
            | Node::FieldAccess { .. } | Node::QualifiedAccess { .. } => {}
            // Anything else is not a valid `externals` expression.
            _ => Err(ResolveError::new(
                ResolveErrorKind::InvalidExternalsExpression,
                self.ctx.document,
                self.shared.arena.span(id),
            ))?,
        }
        Ok(())
    }
}

/// Pass 2: resolve identifiers within a single top-level item.
fn resolve_item(
    arena: &mut NodeArena,
    rcx: &ResolveCtx,
    item_id: NodeId,
    stack: &mut Vec<Resolve>,
) -> ResolveResult<()> {
    match arena.get(item_id) {
        Node::Grammar => {
            // INVARIANT: set during grammar block parsing, always present here
            let grammar_config = rcx.ctx.grammar_config.as_ref().unwrap();
            for (_, id) in grammar_config.node_fields() {
                resolve_expr(arena, rcx, id, stack)?;
            }
            Ok(())
        }
        &Node::Rule { body: inner, .. } | &Node::Let { value: inner, .. } => {
            resolve_expr(arena, rcx, inner, stack)
        }
        &Node::Call { name, args } => {
            resolve_expr(arena, rcx, name, stack)?;
            for &arg in rcx.pools.child_slice(args) {
                resolve_expr(arena, rcx, arg, stack)?;
            }
            Ok(())
        }
        // The template body is shared and resolved once via the Macro item,
        // here we only resolve the call's args (module-scope expressions).
        &Node::ExpandedRule(expand_id) => {
            let args = rcx.pools.get_expansion(expand_id).args;
            for &arg in rcx.pools.child_slice(args) {
                resolve_expr(arena, rcx, arg, stack)?;
            }
            Ok(())
        }
        Node::Macro(macro_id) => {
            let macro_cfg = rcx.pools.get_macro(*macro_id);
            let body = macro_cfg.body;
            // Resolve the body once: an expression body directly, a rule-set body
            // through resolve_children -> each Rule/ComputedRule decl.
            resolve_expr(arena, rcx, body, stack)
        }
        _ => Ok(()),
    }
}

/// Work item for the iterative [`resolve_expr`] traversal.
#[derive(Clone, Copy)]
enum Resolve {
    /// Resolve this node: rewrite an ident, or schedule its children.
    Node(NodeId),
    /// Resolve a `::` access's member/macro name, once its object subtree is
    /// resolved (so the object's module is known).
    Member(NodeId),
}

/// Resolve identifiers within an expression. Uses an explicit stack rather than
/// recursion so a deeply nested expression cannot overflow the native stack. The
/// `stack` scratch is reused across calls; single-child / first-child links are
/// followed directly, so only branch children take a stack round-trip.
fn resolve_expr(
    arena: &mut NodeArena,
    rcx: &ResolveCtx,
    root: NodeId,
    stack: &mut Vec<Resolve>,
) -> ResolveResult<()> {
    stack.clear();
    stack.push(Resolve::Node(root));
    while let Some(work) = stack.pop() {
        match work {
            Resolve::Node(mut id) => {
                while let Some(next) = resolve_node(arena, rcx, id, stack)? {
                    id = next;
                }
            }
            Resolve::Member(id) => resolve_member(arena, rcx, id)?,
        }
    }
    Ok(())
}

/// Resolve one node in place (rewriting an ident), push its branch children onto
/// `stack` (reversed, to pop in source order), and return its first child to
/// descend into directly (no stack round-trip). The node is read once; an alias
/// target and a `::` member/name are resolved specially.
fn resolve_node(
    arena: &mut NodeArena,
    rcx: &ResolveCtx,
    id: NodeId,
    stack: &mut Vec<Resolve>,
) -> ResolveResult<Option<NodeId>> {
    // Push children after the first (reversed) and return the first to descend into.
    fn descend(stack: &mut Vec<Resolve>, children: &[NodeId]) -> Option<NodeId> {
        let (&first, rest) = children.split_first()?;
        stack.extend(rest.iter().rev().map(|&c| Resolve::Node(c)));
        Some(first)
    }
    // SAFETY: every id comes from a child slice or the root, all valid arena ids.
    Ok(match unsafe { *arena.get_unchecked(id) } {
        // Local bindings are emitted as MacroParam/ForBinding by the parser, so
        // any remaining `Ident(Unresolved)` is a top-level reference.
        Node::Ident(IdentKind::Unresolved(name)) => {
            let Some(&Spanned { value: kind, .. }) = rcx.decls.get(&name) else {
                let at = DocumentSpan::new(rcx.ctx.document, arena.span(id));
                return Err(unknown_ident_error(rcx, rcx.strs.resolve(name), at));
            };
            arena.resolve_as(id, kind.to_ident(name));
            None
        }
        // Alias target: a bare identifier resolves against `decls` like any other
        // (a `let` to its value, a rule to a named-symbol reference). Only an
        // UNDECLARED bare identifier becomes a named-alias rule reference,
        // mirroring grammar.js `alias($.x, $.undeclared)`.
        Node::Alias { content, target } => {
            if let Node::Ident(IdentKind::Unresolved(name)) = *arena.get(target) {
                let kind = rcx
                    .decls
                    .get(&name)
                    .map_or(IdentKind::Rule(name), |s| s.value.to_ident(name));
                arena.resolve_as(target, kind);
            } else {
                stack.push(Resolve::Node(target));
            }
            Some(content)
        }
        // `::` access: the member/macro name resolves after the object subtree,
        // so push `Member` below the object and descend into the object.
        Node::QualifiedAccess { obj, .. } => {
            stack.push(Resolve::Member(id));
            Some(obj)
        }
        #[rustfmt::skip]
        Node::SeqOrChoice { range, .. } | Node::List(range) | Node::Tuple(range)
        | Node::Concat(range) | Node::RuleSet(range) => descend(stack, rcx.pools.child_slice(range)),
        Node::Call { name, args } => {
            stack.extend(
                rcx.pools
                    .child_slice(args)
                    .iter()
                    .rev()
                    .map(|&c| Resolve::Node(c)),
            );
            Some(name)
        }
        Node::Object(range) => match rcx.pools.get_object(range).split_first() {
            Some((first, rest)) => {
                stack.extend(rest.iter().rev().map(|f| Resolve::Node(f.value)));
                Some(first.value)
            }
            None => None,
        },
        Node::For { for_id, body } => {
            let config = rcx.pools.get_for(for_id);
            stack.push(Resolve::Node(body));
            Some(config.iterable)
        }
        #[rustfmt::skip]
        Node::ComputedRule { name_expr: a, body: b, .. } | Node::Append { left: a, right: b }
        | Node::BinOp { lhs: a, rhs: b, .. } | Node::Prec { value: a, content: b, .. } => {
            stack.push(Resolve::Node(b));
            Some(a)
        }
        Node::DynRegex { pattern, flags } => {
            if let Some(f) = flags {
                stack.push(Resolve::Node(f));
            }
            Some(pattern)
        }
        #[rustfmt::skip]
        Node::Repeat { inner: c, .. } | Node::Token { inner: c, .. } | Node::Neg(c)
        | Node::GrammarConfig { module: c, .. } | Node::Field { content: c, .. }
        | Node::Reserved { content: c, .. } | Node::Rule { body: c, .. }
        | Node::SymRef { expr: c } | Node::FieldAccess { obj: c, .. } => Some(c),
        _ => None,
    })
}

/// Resolve a `::` member after its object has been resolved.
fn resolve_member(arena: &mut NodeArena, rcx: &ResolveCtx, id: NodeId) -> ResolveResult<()> {
    expect_pat!(
        Node::QualifiedAccess {
            obj,
            member,
            member_offset,
        },
        *arena.get(id)
    );
    // None when obj isn't a module ref; the type checker reports the error.
    if let Some(idx) = resolve_module_id(arena, obj) {
        // The resolved target is only needed by the deferred top-level-call pass
        _ = resolve_qualified_member(rcx, arena, idx, id, member, member_offset)?;
    }
    Ok(())
}

/// Resolve a `QualifiedAccess { obj, member }` against the target module's
/// export table:
///   - `let` -> `Ident(Var)`
///   - expression/rule-set macro -> `Ident(Macro)`
///   - lowered rule / external -> `ModuleRule`
///   - not found -> error
fn resolve_qualified_member(
    rcx: &ResolveCtx,
    arena: &mut NodeArena,
    module: ModuleId,
    node_id: NodeId,
    member: StrId,
    member_offset: u32,
) -> ResolveResult<QualifiedTarget> {
    let target = &rcx.modules[usize::from(module)];
    let Some(export) = target.export(member) else {
        let member_len = rcx.strs.resolve(member).len() as u32;
        let member_span = Span::new(member_offset, member_offset + member_len);
        return Err(import_member_not_found(rcx, target, member, member_span));
    };

    match export {
        Export::Variable(let_id) => arena.set(node_id, Node::Ident(IdentKind::Var(let_id))),
        Export::ExpressionMacro(macro_id) | Export::RuleSetMacro(macro_id) => {
            arena.set(node_id, Node::Ident(IdentKind::Macro(macro_id)));
        }
        Export::Rule(rule) => arena.set(
            node_id,
            Node::ModuleRule {
                module,
                member,
                rule,
            },
        ),
    }

    Ok(QualifiedTarget {
        module,
        member,
        export,
    })
}

/// Build an `ImportMemberNotFound` error, attaching a "did you mean" note when appropriate
fn import_member_not_found(
    rcx: &ResolveCtx,
    target: &Module,
    name: StrId,
    span: Span,
) -> ResolveError {
    let name = rcx.strs.resolve(name);
    let kind = ResolveErrorKind::ImportMemberNotFound(name.to_string());
    let candidates = target.export_keys().map(|id| rcx.strs.resolve(id));
    if let Some(suggestion) = suggest_name(name, candidates) {
        return ResolveError::with_note(
            kind,
            rcx.ctx.document,
            span,
            rcx.ctx
                .note(NoteMessage::DidYouMean(suggestion.to_string()), span),
        );
    }
    ResolveError::new(kind, rcx.ctx.document, span)
}

/// Follow a chain of `Ident(Var(_))` -> `Let { value }` bindings until we hit
/// an `Import` or `Inherit`, returning its module id.
fn resolve_module_id(arena: &NodeArena, obj: NodeId) -> Option<ModuleId> {
    let ref_id = resolve_module_ref(arena, obj)?;
    match arena.get(ref_id) {
        Node::Inherit {
            module: Some(idx), ..
        }
        | Node::Import {
            module: Some(idx), ..
        } => Some(*idx),
        _ => None,
    }
}

/// Walk `Ident(Var) -> Let.value` chains to find the underlying `Import` or `Inherit`
/// node. A self-referential or mutually-recursive `let` (e.g. `let a = a`) bails with
/// `None`. The cycle is then reported by typecheck (`CircularLet`).
pub(super) fn resolve_module_ref(arena: &NodeArena, mut obj: NodeId) -> Option<NodeId> {
    // A chain longer than the arena has necessarily revisited a let, i.e. cycled.
    for _ in 0..arena.len() {
        match arena.get(obj) {
            Node::Ident(IdentKind::Var(let_id)) => {
                expect_pat!(Node::Let { value, .. }, arena.get(*let_id));
                obj = *value;
            }
            Node::Inherit { .. } | Node::Import { .. } => return Some(obj),
            _ => return None,
        }
    }
    None
}

/// Build an `UnknownIdentifier` error, attaching a "did you mean" note if appropriate.
fn unknown_ident_error(rcx: &ResolveCtx, name: &str, at: DocumentSpan) -> ResolveError {
    let kind = ResolveErrorKind::UnknownIdentifier(name.to_string());
    let candidates = rcx.decls.keys().map(|&id| rcx.strs.resolve(id)).chain(
        super::lexer::TokenKind::EXPRESSION_KEYWORD_NAMES
            .iter()
            .copied(),
    );
    if let Some(suggestion) = suggest_name(name, candidates) {
        return ResolveError::with_note(
            kind,
            at.document,
            at.span,
            Note {
                message: NoteMessage::DidYouMean(suggestion.to_string()),
                location: at,
            },
        );
    }
    ResolveError::new(kind, at.document, at.span)
}
