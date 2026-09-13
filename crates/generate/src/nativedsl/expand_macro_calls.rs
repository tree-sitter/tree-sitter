//! Inlines top-level rule-set macro invocations.
//!
//! Each `Node::Call` at item position becomes one `Node::ExpandedRule` per decl
//! in the macro's body. Each `ExpandedRule` records the shared body and the call's
//! args in an [`Expansion`], and lower binds the args before lowering the body
//! (the expression-macro mechanism). Only the rule *name* is materialized here,
//! since resolve needs it.
//!
//! Local calls are expanded before child modules load. Qualified rule-set calls
//! are expanded in a late pass once child modules are available.

use rustc_hash::{FxHashMap, FxHashSet};
use serde::{Deserialize, Serialize};
use thiserror::Error;

use super::{
    ExpandError, Export, Note, NoteMessage,
    ast::{Expansion, IdentKind, MacroId, MacroKind, ModuleContext, Node, NodeId, SharedAst, Span},
    lexer::is_ident_str,
};
use crate::{
    nativedsl::{
        DocumentId, DocumentSpan, Module,
        resolve::{DeferredQualifiedCall, QualifiedTarget},
    },
    strpool::{StrId, StrPool},
};

#[derive(Debug, PartialEq, Eq, Serialize, Deserialize, Error)]
pub enum ExpandErrorKind {
    #[error("unknown macro '{0}'")]
    UnknownMacro(String),
    #[error(
        "'{0}' is an expression macro and cannot be invoked at top level; \
         use it inside a rule body instead"
    )]
    ExpressionMacroAsItem(String),
    #[error("macro '{macro_name}': expected {expected} arguments, got {got}")]
    ArgCountMismatch {
        macro_name: String,
        expected: usize,
        got: usize,
    },
    #[error("computed rule name expression must be a string literal, parameter, or concat(...)")]
    NonStringInName,
    #[error("'{0}' is not a rule-set macro and cannot be invoked at top level")]
    NotARuleSetMacro(String),
    #[error("computed rule name '{0}' is not a valid identifier")]
    InvalidRuleName(String),
}

#[derive(Clone, Copy)]
struct MacroCallSite {
    macro_id: MacroId,
    name_id: StrId,
    call_id: NodeId,
    root_slot: usize,
}

pub fn expand_macro_calls(
    shared: &mut SharedAst,
    strs: &mut StrPool,
    ctx: &mut ModuleContext,
) -> Result<(), ExpandError> {
    // Walk only the original indices. Each Call writes its first expanded rule
    // into its own slot. The rest are pushed to the end. A call whose set has
    // zero decls (empty or fully cfg-gated) leaves its Call node in the slot.
    let original_len = ctx.root_items.len();
    let mut name_buf = String::new();
    // Built on the first local call
    let mut tables = None;
    // Set when a call is left in `root_items` unexpanded.
    let mut unexpanded = false;
    for i in 0..original_len {
        let id = ctx.root_items[i];
        let Node::Call { name, .. } = *shared.arena.get(id) else {
            continue;
        };
        if matches!(shared.arena.get(name), Node::QualifiedAccess { .. }) {
            // Qualified calls are resolved and expanded after child modules load.
            continue;
        }
        expect_pat!(
            Node::Ident(IdentKind::Unresolved(name_id)),
            *shared.arena.get(name)
        );
        let (macros, duplicates) = tables.get_or_insert_with(|| collect_macros(shared, ctx));
        // A name declared by more than one top-level macro is rejected by resolve
        // as a duplicate. Skip expanding its calls and let `collect_decls` reject.
        if duplicates.contains(&name_id) {
            unexpanded = true;
            continue;
        }
        let Some(&macro_id) = macros.get(&name_id) else {
            let mut err = ExpandError::new(
                ExpandErrorKind::UnknownMacro(strs.resolve(name_id).to_owned()),
                ctx.document,
                shared.arena.span(name),
            );
            if let Some(&cfg_node) = ctx.cfg_dropped.get(&name_id)
                && let Node::Cfg { name: flag, .. } = *shared.arena.get(cfg_node)
            {
                err.add_note(ctx.note(
                    NoteMessage::GatedByDisabledCfg(strs.resolve(flag).to_owned()),
                    shared.arena.span(cfg_node),
                ));
            }
            return Err(err);
        };
        let n_decls = expand_call_with_id(
            shared,
            strs,
            ctx,
            MacroCallSite {
                macro_id,
                name_id,
                call_id: id,
                root_slot: i,
            },
            ctx.document,
            &mut name_buf,
        )?;
        unexpanded |= n_decls == 0;
    }
    // A zero-decl expansion contributes nothing, so drop any unqualified Call
    // left in place. Qualified calls remain for the late expansion pass.
    if unexpanded {
        ctx.root_items.retain(|&id| match shared.arena.get(id) {
            Node::Call { name, .. } => {
                matches!(shared.arena.get(*name), Node::QualifiedAccess { .. })
            }
            _ => true,
        });
    }
    Ok(())
}

/// Expand rule-set calls whose macro is exported by an imported or inherited
/// module. Child modules must already be loaded before this function runs.
///
/// The rules produced are the `ExpandedRule` nodes pushed here, which
/// `register_expanded_decls` reads back off the module's late node range.
pub(crate) fn expand_qualified_macro_calls(
    shared: &mut SharedAst,
    strs: &mut StrPool,
    ctx: &mut ModuleContext,
    modules: &[Module],
    calls: &[DeferredQualifiedCall],
) -> Result<(), ExpandError> {
    let mut name_buf = String::new();
    // When a rule set macro's expanded body is empty
    let mut empty_expansion = false;
    for &DeferredQualifiedCall {
        slot,
        call_id,
        target,
    } in calls
    {
        let Some(QualifiedTarget {
            module,
            member,
            export,
        }) = target
        else {
            // The receiver never resolved to a module. The call stays in
            // `root_items` for resolve and typecheck to diagnose.
            continue;
        };
        expect_pat!(Node::Call { name, .. }, *shared.arena.get(call_id));
        // `@name(...)` only invokes a rule set macro, anything else is a kind mismatch.
        let Export::RuleSetMacro(macro_id) = export else {
            let member_name = strs.resolve(member).to_owned();
            let kind = if matches!(export, Export::ExpressionMacro(_)) {
                ExpandErrorKind::ExpressionMacroAsItem(member_name)
            } else {
                ExpandErrorKind::NotARuleSetMacro(member_name)
            };
            let mut err = ExpandError::new(kind, ctx.document, shared.arena.span(name));
            let def = &modules[usize::from(module)];
            if let Some(decl) = export_decl_span(shared, def, member) {
                err.add_note(def.ctx().note(NoteMessage::DefinedHere, decl));
            }
            return Err(err);
        };
        let n_decls = expand_call_with_id(
            shared,
            strs,
            ctx,
            MacroCallSite {
                macro_id,
                name_id: member,
                call_id,
                root_slot: slot,
            },
            modules[usize::from(module)].ctx().document,
            &mut name_buf,
        )?;
        empty_expansion |= n_decls == 0;
    }
    if empty_expansion {
        ctx.root_items
            .retain(|&id| !calls.iter().any(|c| c.target.is_some() && c.call_id == id));
    }
    Ok(())
}

/// The local top-level macro table (name -> id) plus the set of names declared
/// by more than one `rules`/`macro`, built in one scan. Replaces a `macro_index`
/// carried on the ctx: it's needed only here, after cfg gating, so deriving it
/// from the surviving `root_items` keeps it off the parser/cfg side tables.
fn collect_macros(
    shared: &SharedAst,
    ctx: &ModuleContext,
) -> (FxHashMap<StrId, MacroId>, FxHashSet<StrId>) {
    let mut macros: FxHashMap<StrId, MacroId> = FxHashMap::default();
    let mut dups: FxHashSet<StrId> = FxHashSet::default();
    for &id in &ctx.root_items {
        if let Node::Macro(macro_id) = *shared.arena.get(id) {
            let name = shared.pools.get_macro(macro_id).name.value;
            if macros.insert(name, macro_id).is_some() {
                dups.insert(name);
            }
        }
    }
    (macros, dups)
}

/// Materialize one `ExpandedRule` per decl in the macro's body, returning how
/// many.
fn expand_call_with_id(
    shared: &mut SharedAst,
    strs: &mut StrPool,
    ctx: &mut ModuleContext,
    call: MacroCallSite,
    // document where the macro was defined
    def_document: DocumentId,
    name_buf: &mut String,
) -> Result<u16, ExpandError> {
    let MacroCallSite {
        macro_id,
        name_id,
        call_id,
        root_slot,
    } = call;
    expect_pat!(Node::Call { name, args }, *shared.arena.get(call_id));
    let name_span = shared.arena.span(name);
    // Snapshot before recursive calls reborrow shared mutably.
    let config = shared.pools.get_macro(macro_id);
    let kind = config.kind;
    let param_count = config.params.len as usize;
    let body_id = config.body;
    let def_name_span = config.name.span;
    let MacroKind::RuleSet = kind else {
        return Err(ExpandError::new(
            ExpandErrorKind::ExpressionMacroAsItem(strs.resolve(name_id).to_owned()),
            ctx.document,
            name_span,
        ));
    };
    expect_pat!(Node::RuleSet(rule_range), *shared.arena.get(body_id));
    if args.len as usize != param_count {
        return Err(ExpandError::with_note(
            ExpandErrorKind::ArgCountMismatch {
                macro_name: strs.resolve(name_id).to_owned(),
                expected: param_count,
                got: args.len as usize,
            },
            ctx.document,
            shared.arena.span(call_id),
            Note {
                message: NoteMessage::DefinedHere,
                location: DocumentSpan::new(def_document, def_name_span),
            },
        ));
    }
    // Read template decls by absolute index. Each instance records the shared
    // template body + the call's args, and lower binds the args on the macro-arg
    // stack before lowering the body (the same mechanism expression macros use).
    // Only the rule *name* is materialized now, since resolve needs it to
    // register the generated rule.
    let call_span = shared.arena.span(call_id);
    let args_start = args.start as usize;
    let rule_start = rule_range.start as usize;
    let rule_end = rule_start + rule_range.len as usize;
    for (offset, i) in (rule_start..rule_end).enumerate() {
        let rule_id = shared.pools.children[i];
        let (is_override, name, body) = match *shared.arena.get(rule_id) {
            Node::Rule {
                is_override,
                name,
                body,
            } => (is_override, name, body),
            Node::ComputedRule {
                is_override,
                name_expr,
                body,
            } => {
                let name_span = shared.arena.span(name_expr);
                let name = eval_name(
                    shared,
                    strs,
                    def_document,
                    args_start,
                    name_expr,
                    name_span,
                    name_buf,
                )?;
                (is_override, name, body)
            }
            // Parser only places Rule/ComputedRule in a RuleSet body.
            _ => unreachable!(),
        };
        let expand_id = shared.pools.push_expansion(Expansion {
            is_override,
            name,
            macro_id,
            body,
            args,
        });
        let expanded = shared.arena.push(Node::ExpandedRule(expand_id), call_span);
        if offset == 0 {
            ctx.root_items[root_slot] = expanded;
        } else {
            ctx.root_items.push(expanded);
        }
    }
    // Evaluate this macro's computed-name references under the call's args and
    // record them for resolve to validate.
    let sym_refs = shared.pools.get_macro(macro_id).sym_refs;
    for &sym_ref in shared.pools.child_slice(sym_refs) {
        expect_pat!(Node::SymRef { expr }, *shared.arena.get(sym_ref));
        let span = shared.arena.span(sym_ref);
        let name = eval_name(shared, strs, def_document, args_start, expr, span, name_buf)?;
        ctx.computed_refs
            .push((name, DocumentSpan::new(def_document, span)));
    }
    Ok(rule_range.len)
}

/// Accepts string literals, macro params (resolved into args), and
/// `concat(...)` of those. Typecheck catches non-str_t at definition
/// time; this errors at expand time for shapes outside the limited
/// compile-time evaluator subset (e.g. references to lets).
fn eval_name(
    shared: &SharedAst,
    strs: &mut StrPool,
    document: DocumentId,
    args_start: usize,
    node_id: NodeId,
    name_expr_span: Span,
    name_buf: &mut String,
) -> Result<StrId, ExpandError> {
    name_buf.clear();
    eval_name_into(shared, strs, document, args_start, node_id, name_buf)?;
    if !is_ident_str(name_buf) {
        return Err(ExpandError::new(
            ExpandErrorKind::InvalidRuleName(std::mem::take(name_buf)),
            document,
            name_expr_span,
        ));
    }
    Ok(strs.intern(name_buf))
}

/// Build a computed rule name (`@<expr>`) at expand time, before resolve - so
/// only the early-evaluable subset works: string literals, the macro's params,
/// and `concat` of those. A `let` can't be read here (lets run at lower); pass
/// it as a macro param instead.
fn eval_name_into(
    shared: &SharedAst,
    strs: &StrPool,
    document: DocumentId,
    args_start: usize,
    node_id: NodeId,
    out: &mut String,
) -> Result<(), ExpandError> {
    let node = *shared.arena.get(node_id);
    let span = shared.arena.span(node_id);
    match node {
        Node::StringLit(sid) => {
            out.push_str(strs.resolve(sid));
            Ok(())
        }
        Node::MacroParam { index, .. } => {
            let arg_id = shared.pools.children[args_start + index as usize];
            eval_name_into(shared, strs, document, args_start, arg_id, out)
        }
        Node::Concat(range) => {
            let start = range.start as usize;
            let end = start + range.len as usize;
            for i in start..end {
                let child = shared.pools.children[i];
                eval_name_into(shared, strs, document, args_start, child, out)?;
            }
            Ok(())
        }
        _ => Err(ExpandError::new(
            ExpandErrorKind::NonStringInName,
            document,
            span,
        )),
    }
}

/// Span of `member`'s declaration in `module`, to anchor a `DefinedHere` note.
fn export_decl_span(shared: &SharedAst, module: &Module, member: StrId) -> Option<Span> {
    module.ctx().root_items.iter().find_map(|&id| {
        let name = match *shared.arena.get(id) {
            Node::Let { name, .. } | Node::Rule { name, .. } => name,
            Node::Macro(macro_id) => shared.pools.get_macro(macro_id).name.value,
            Node::ExpandedRule(expand_id) => shared.pools.get_expansion(expand_id).name,
            _ => return None,
        };
        (name == member).then(|| shared.arena.span(id))
    })
}
