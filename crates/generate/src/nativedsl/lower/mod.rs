//! Lowering pass: evaluates the typed AST into a
//! [`LoweredGrammar`](crate::nativedsl::LoweredGrammar).
//!
//! Pipeline:
//! 1. `evaluate` walks the root grammar's items, emitting rules into the shared
//!    `RulePool` and values into the `repr::IrPools` value pool.
//! 2. `build_grammar` consumes the [`EvalResult`] and the optional inherited base
//!    grammar, materializing a final
//!    [`LoweredGrammar`](crate::nativedsl::LoweredGrammar) with overrides
//!    applied and unset fields inherited.

mod error;
mod evaluator;
mod repr;

use rustc_hash::{FxBuildHasher, FxHashMap, FxHashSet};

use crate::{
    grammars::{PrecedenceEntry, ReservedWordContext, Variable},
    nativedsl::{DocumentMap, ImportedRule, LoweredGrammar, Module, ast::ModuleContext},
    rules::{Rule, RuleId, RulePool},
    strpool::{StrId, StrPool},
};

use super::{
    LowerError, ModuleId, Note, NoteMessage,
    ast::{ForId, Node, NodeId, SharedAst, Span, Spanned},
};

pub use error::{DisallowedItemKind, LowerErrorKind, LowerResult};

use evaluator::{Evaluator, Task};
use repr::{IrPools, ValueId};

const MAX_CALL_DEPTH: u16 = 128;

/// One stack frame for the macro-call trace.
#[derive(Clone, Copy)]
pub(super) struct CallFrame {
    /// The macro's name.
    pub name: StrId,
    /// Span of the call site in the caller's module.
    pub call_span: Span,
    pub caller_mod: ModuleId,
}

/// Binding slots for an active `for` loop.
#[derive(Clone, Copy)]
struct ForFrame {
    for_id: ForId,
    /// Base offset into [`Scratch::for_binding_values`].
    values_base: u32,
}

const _: () = assert!(std::mem::size_of::<ForFrame>() == 8);

/// Long-lived state shared across grammar lowerings in one `parse_native_dsl`
/// call.
///
/// Each module's let bindings are evaluated eagerly when it is lowered. The `lets`
/// cache, keyed by `Let` node id, then serves cross-module reads without re-evaluating.
/// `scratch` persists across grammars to reuse allocated capacity but its contents
/// are cleared between them.
#[derive(Default)]
pub struct LoweringState {
    pub(super) ir: IrPools,
    // Cross-grammar cache: let states keyed by their `Let` node id, shared across
    // every module's evaluation in one run.
    lets: FxHashMap<NodeId, LetState>,
    scratch: Scratch,
}

/// The state of a let binding as it progresses through lowering.
#[derive(Clone, Copy)]
enum LetState {
    InProgress,
    Resolved(ValueId),
}

/// Per-grammar scratch buffers. Cleared (capacity retained) at the start of
/// each grammar lowering via [`Scratch::clear`].
#[allow(clippy::struct_field_names)]
#[derive(Default)]
struct Scratch {
    call_stack: Vec<CallFrame>,
    /// Work stack driving the iterative expression/rule evaluation in
    /// [`evaluator`]; shared across walks (re-entrant macro/for/let evaluation
    /// nests on it via base offsets) so its capacity is retained.
    work: Vec<Task>,
    /// Scratch for `first_unresolved_let_dep`.
    dep_walk: Vec<NodeId>,
    macro_args: Vec<ValueId>,
    /// Bases into `macro_args`. Lowered calls have at most `u8::MAX` arguments
    /// and nesting is limited to `MAX_CALL_DEPTH`, so every base fits in `u16`.
    macro_arg_bases: Vec<u16>,
    for_binding_values: Vec<ValueId>,
    for_binding_frames: Vec<ForFrame>,
    val_scratch: Vec<ValueId>,
    rule_scratch: Vec<RuleId>,
    concat_buf: String,
    /// Result-stack bases for variable-arity [`Task::Combine`]s, kept out of the
    /// `Task` itself so the work stack stays 8 bytes/entry. Combines nest LIFO, so
    /// this is a plain stack.
    combine_bases: Vec<u32>,
}

impl Scratch {
    fn clear(&mut self) {
        self.call_stack.clear();
        self.work.clear();
        self.dep_walk.clear();
        self.macro_args.clear();
        self.macro_arg_bases.clear();
        self.for_binding_values.clear();
        self.for_binding_frames.clear();
        self.val_scratch.clear();
        self.rule_scratch.clear();
        self.concat_buf.clear();
        self.combine_bases.clear();
    }
}

impl LoweringState {
    fn reset_per_grammar(&mut self) {
        self.scratch.clear();
    }
}

struct EvalResult {
    language: StrId,
    rules: Vec<Variable>,
    overrides: Vec<(StrId, RuleId, Span)>,
    extras: Option<Vec<RuleId>>,
    externals: Option<Vec<RuleId>>,
    inline: Option<Vec<StrId>>,
    supertypes: Option<Vec<StrId>>,
    word: Option<StrId>,
    start: Option<(StrId, Span)>,
    conflicts: Option<Vec<Vec<StrId>>>,
    precedences: Option<Vec<Vec<PrecedenceEntry>>>,
    reserved: Option<Vec<ReservedWordContext>>,
}

/// Lower a resolved and type-checked grammar module, merging its inherited grammar
/// and imported rules.
pub fn lower_grammar(
    state: &mut LoweringState,
    pool: &mut RulePool,
    shared: &SharedAst,
    previous: &[Module],
    documents: &DocumentMap,
    current: &ModuleContext,
    imported_rules: &[ImportedRule],
) -> LowerResult<LoweredGrammar> {
    let base_grammar = current
        .inherit_module(&shared.arena)
        .and_then(|(idx, _)| previous[usize::from(idx)].lowered());
    let result = evaluate(state, pool, shared, previous, documents, current)?;
    let grammar = build_grammar(current, pool, result, base_grammar, imported_rules)?;
    let stack = &mut state.scratch.rule_scratch;
    check_symbol_completeness(shared, current, previous, pool, &grammar, stack)?;
    Ok(grammar)
}

/// Every `NamedSymbol` a grammar references must resolve to a definition.
/// An `expect` forward-decl makes a name *referenceable* without defining it,
/// so an unfulfilled `expect` must be caught.
fn check_symbol_completeness(
    shared: &SharedAst,
    current: &ModuleContext,
    previous: &[Module],
    pool: &RulePool,
    grammar: &LoweredGrammar,
    stack: &mut Vec<RuleId>,
) -> LowerResult<()> {
    if !current.has_forward_decls && !previous.iter().any(|m| m.ctx().has_forward_decls) {
        return Ok(());
    }
    let mut defined: FxHashSet<StrId> = grammar.variables.iter().map(|v| v.name).collect();
    for &ext in &grammar.external_roots {
        if let Rule::NamedSymbol(name) = pool.node(ext) {
            defined.insert(name);
        }
    }
    let mut undefined: Vec<StrId> = Vec::new();
    for v in &grammar.variables {
        collect_undefined(pool, v.root, &defined, &mut undefined, stack);
    }
    if undefined.is_empty() {
        return Ok(());
    }
    Err(undefined_symbols_error(
        shared,
        current,
        previous,
        pool.strs(),
        undefined,
    ))
}

/// Push every `NamedSymbol` in `root` whose name is absent from `defined` into
/// `out`. Walks with an explicit stack (order is irrelevant - `out` is sorted and
/// deduped by the caller) so a deeply nested rule cannot overflow the native stack.
fn collect_undefined(
    pool: &RulePool,
    root: RuleId,
    defined: &FxHashSet<StrId>,
    out: &mut Vec<StrId>,
    stack: &mut Vec<RuleId>,
) {
    stack.clear();
    stack.push(root);
    while let Some(id) = stack.pop() {
        match pool.node(id) {
            Rule::NamedSymbol(name) if !defined.contains(&name) => out.push(name),
            Rule::Seq(range) | Rule::Choice(range) => {
                stack.extend_from_slice(pool.child_slice(range));
            }
            Rule::Metadata { rule, .. } | Rule::Repeat(rule) | Rule::Reserved { rule, .. } => {
                stack.push(rule);
            }
            Rule::NamedSymbol(_)
            | Rule::Blank
            | Rule::Eof
            | Rule::String(_)
            | Rule::Pattern(..)
            | Rule::Sym { .. } => {}
        }
    }
}

/// Build the error for one or more dangling `names`.
fn undefined_symbols_error(
    shared: &SharedAst,
    current: &ModuleContext,
    previous: &[Module],
    strs: &StrPool,
    mut names: Vec<StrId>,
) -> LowerError {
    names.sort_unstable_by_key(|&n| strs.resolve(n));
    names.dedup();
    let kind = LowerErrorKind::UndefinedSymbols(
        names.iter().map(|&n| strs.resolve(n).to_string()).collect(),
    );
    let mut notes = names
        .iter()
        .filter_map(|&name| forward_decl_note(shared, current, previous, name));
    let Some(primary) = notes.next() else {
        // No `expect` behind any dangling symbol: anchor at the grammar block,
        // which `validate_grammar` guarantees is present in a grammar module.
        let block = current
            .root_items
            .iter()
            .find(|&&id| matches!(shared.arena.get(id), Node::Grammar));
        return match block {
            Some(&id) => LowerError::new(kind, current.document, shared.arena.span(id)),
            None => LowerError::without_span(kind, current.document),
        };
    };
    let mut err = LowerError::new(kind, primary.location.document, primary.location.span);
    for note in notes {
        err.add_note(note);
    }
    err
}

/// A `forward-declared here` note anchored at the `expect <name>` decl, searched
/// in this grammar then any imported library so the note renders against the file
/// that made the promise. `None` if no `expect` declares `name`.
fn forward_decl_note(
    shared: &SharedAst,
    current: &ModuleContext,
    previous: &[Module],
    name: StrId,
) -> Option<Note> {
    if let Some(span) = forward_decl_span(shared, current, name) {
        return Some(current.note(NoteMessage::ForwardDeclaredHere, span));
    }
    previous.iter().find_map(|module| match module {
        Module::Library { ctx, .. } => forward_decl_span(shared, ctx, name)
            .map(|span| ctx.note(NoteMessage::ForwardDeclaredHere, span)),
        Module::Grammar { .. } => None,
    })
}

/// Span of an `expect <name>` forward-decl in `ctx`, if one is present.
fn forward_decl_span(shared: &SharedAst, ctx: &ModuleContext, name: StrId) -> Option<Span> {
    ctx.root_items
        .iter()
        .find_map(|&id| match *shared.arena.get(id) {
            Node::Forward { name: decl } if decl == name => Some(shared.arena.span(id)),
            _ => None,
        })
}

/// One lowered top-level item, tagged so grammar lowering can separate overrides
/// and library lowering can reject them. Built in source order.
struct LoweredItem {
    variable: Variable,
    is_override: bool,
    /// Attribution span for an override (the rule name, or the macro call site).
    span: Span,
}

/// Walk `root_items`, evaluating lets and lowering each rule / expanded rule to
/// a `RuleId` in source order. Shared by grammar and library lowering; the caller
/// decides what to do with the `override`-tagged items.
fn lower_items(eval: &mut Evaluator) -> LowerResult<Vec<LoweredItem>> {
    let mut items = Vec::with_capacity(eval.root_ctx.root_items.len());
    for &item_id in &eval.root_ctx.root_items {
        match eval.shared.arena.get(item_id) {
            // Grammar block (config is read separately), macros, and externals
            // register names but don't materialize a rule here.
            Node::Grammar | Node::Macro(_) | Node::Forward { .. } => {}
            Node::Let { .. } => {
                eval.eval_let(item_id)?;
            }
            &Node::Rule {
                is_override,
                name,
                body,
            } => {
                let root = eval.lower_to_rule(body)?;
                items.push(LoweredItem {
                    variable: Variable { name, root },
                    is_override,
                    span: eval.shared.arena.span(item_id),
                });
            }
            &Node::ExpandedRule(expand_id) => {
                let exp = *eval.shared.pools.get_expansion(expand_id);
                // expand_macro_calls sets the item span to the macro call site,
                // used for override attribution diagnostics.
                let span = eval.shared.arena.span(item_id);
                let root = eval.lower_expansion(expand_id, span)?;
                items.push(LoweredItem {
                    variable: Variable {
                        name: exp.name,
                        root,
                    },
                    is_override: exp.is_override,
                    span,
                });
            }
            _ => unreachable!(),
        }
    }
    Ok(items)
}

/// Lower a library module's rules into a name-keyed list.
///   - Lets/macros are evaluated through the same Evaluator as grammar lowering;
///   - `external` decls and macros register names but don't materialize. Grammar
///     blocks and direct override rules are rejected by validation; an override
///     reaching the top level via a called macro is rejected below.
pub fn lower_library(
    state: &mut LoweringState,
    pool: &mut RulePool,
    shared: &SharedAst,
    previous: &[super::Module],
    documents: &DocumentMap,
    current: &super::ModuleContext,
) -> LowerResult<Vec<Variable>> {
    let mut eval = Evaluator::new(state, pool, shared, previous, documents, current);
    let mut rules = Vec::new();
    for it in lower_items(&mut eval)? {
        if it.is_override {
            // A library can't inherit, so an `override` reaching its top level via
            // a called rules-macro (a direct `override rule` is rejected earlier
            // by validate_import_items) has nothing to override. Reject it rather
            // than silently demoting it to a plain rule.
            return Err(LowerError::new(
                LowerErrorKind::ModuleDisallowedItem(DisallowedItemKind::OverrideRule),
                current.document,
                it.span,
            ));
        }
        rules.push(it.variable);
    }
    Ok(rules)
}

fn evaluate(
    state: &mut LoweringState,
    pool: &mut RulePool,
    shared: &SharedAst,
    previous: &[super::Module],
    documents: &DocumentMap,
    ctx: &super::ModuleContext,
) -> LowerResult<EvalResult> {
    let mut eval = Evaluator::new(state, pool, shared, previous, documents, ctx);
    let mut rules = Vec::new();
    let mut overrides: Vec<(StrId, RuleId, Span)> = Vec::new();
    for it in lower_items(&mut eval)? {
        if it.is_override {
            overrides.push((it.variable.name, it.variable.root, it.span));
        } else {
            rules.push(it.variable);
        }
    }
    // grammar_config is guaranteed present by `validate_grammar`, language
    // is guaranteed present by the parser (`MissingLanguageField` error).
    let config = ctx.grammar_config.as_ref().unwrap();
    let language = config.language.unwrap();

    Ok(EvalResult {
        language,
        rules,
        overrides,
        extras: config
            .extras
            .map(|id| eval.eval_rule_list(id))
            .transpose()?,
        externals: config
            .externals
            .map(|id| eval.eval_rule_list(id))
            .transpose()?,
        inline: config
            .inline
            .map(|id| eval.eval_name_list(id))
            .transpose()?,
        supertypes: config
            .supertypes
            .map(|id| eval.eval_name_list(id))
            .transpose()?,
        word: config.word.map(|id| eval.eval_rule_name(id)).transpose()?,
        start: config
            .start
            .map(|id| Ok((eval.eval_rule_name(id)?, shared.arena.span(id))))
            .transpose()?,
        conflicts: config
            .conflicts
            .map(|id| eval.eval_conflicts(id))
            .transpose()?,
        precedences: config
            .precedences
            .map(|id| eval.eval_precedences(id))
            .transpose()?,
        reserved: config
            .reserved
            .map(|id| eval.eval_reserved(id))
            .transpose()?,
    })
}

/// Inherit a config field: the child's value replaces the base's entirely if
/// present, else the base's is inherited. Generic over the field via `field`,
/// which is more concise than threading a slice through all five call sites.
fn inherit<T: Clone>(
    overridden: Option<Vec<T>>,
    base: Option<&LoweredGrammar>,
    field: fn(&LoweredGrammar) -> &[T],
) -> Vec<T> {
    overridden.unwrap_or_else(|| base.map_or_else(Vec::new, |b| field(b).to_vec()))
}

/// Merge the child's `reserved` onto the base's, unlike the replace-by-default
/// of every other field: keep base sets in base order (so the first/default set
/// is preserved), override an existing set by name in place, and append the
/// child's new sets. Matches dsl.js, which assigns `reserved[name] = ...` over a
/// copy of the base's reserved object.
fn merge_reserved(
    overridden: Option<Vec<ReservedWordContext>>,
    base: Option<&[ReservedWordContext]>,
) -> Vec<ReservedWordContext> {
    let base = base.unwrap_or(&[]);
    let Some(mut children) = overridden else {
        return base.to_vec();
    };
    let mut merged = Vec::with_capacity(base.len() + children.len());
    for b in base {
        if let Some(pos) = children.iter().position(|c| c.name == b.name) {
            merged.push(children.remove(pos));
        } else {
            merged.push(b.clone());
        }
    }
    merged.append(&mut children);
    merged
}

fn build_grammar(
    ctx: &ModuleContext,
    pool: &mut RulePool,
    result: EvalResult,
    base: Option<&LoweredGrammar>,
    imported_rules: &[ImportedRule],
) -> LowerResult<LoweredGrammar> {
    let mut overrides: FxHashMap<StrId, Spanned<RuleId>> =
        FxHashMap::with_capacity_and_hasher(result.overrides.len(), FxBuildHasher);
    for (name, rule, span) in result.overrides {
        overrides.insert(name, Spanned::new(rule, span));
    }

    let mut variables = Vec::with_capacity(
        base.map_or(0, |b| b.variables.len()) + result.rules.len() + imported_rules.len(),
    );

    // Add base rules first to preserve the inherited grammar's start rule.
    if let Some(base) = base {
        for v in &base.variables {
            if let Some(Spanned { value: rule, .. }) = overrides.remove(&v.name) {
                variables.push(Variable {
                    name: v.name,
                    root: rule,
                });
            } else {
                variables.push(*v);
            }
        }
    }

    variables.extend(result.rules);

    // Imported library rules can also be override targets.
    for ir in imported_rules {
        let final_rule = overrides.remove(&ir.name).map_or(ir.rule, |s| s.value);
        variables.push(Variable {
            name: ir.name,
            root: final_rule,
        });
    }

    if !overrides.is_empty() {
        // Names (sorted) go in the message; each override's location becomes a
        // located snippet - the first (in source order) as the primary span,
        // the rest as `override declared here` notes. This gets all locations
        // through the generic note machinery, no renderer special-casing.
        let mut entries: Vec<(StrId, Span)> = overrides
            .into_iter()
            .map(|(name, s)| (name, s.span))
            .collect();
        entries.sort_unstable_by_key(|(_, span)| span.start);
        let mut names: Vec<String> = entries
            .iter()
            .map(|(name, _)| pool.resolve(*name).to_string())
            .collect();
        names.sort_unstable();
        let (_, primary) = entries[0];
        let mut err = LowerError::new(
            LowerErrorKind::OverrideRuleNotFound(names),
            ctx.document,
            primary,
        );
        for (_, span) in &entries[1..] {
            err.add_note(ctx.note(NoteMessage::OverrideDeclaredHere, *span));
        }
        return Err(err);
    }

    // Tree-sitter's start symbol is `variables[0]` (a non-terminal), so honor
    // `start: <rule>` by rotating the named rule into position 0. Inherited,
    // local, and library rules are all in `variables`. An external token is a
    // valid rule reference but lives in `external_tokens`, not `variables`, so
    // it can't be the start symbol.
    if let Some((name, span)) = result.start {
        let pos = variables
            .iter()
            .position(|v| v.name == name)
            .ok_or_else(|| {
                LowerError::new(
                    LowerErrorKind::ExternalCannotBeStart(pool.resolve(name).to_string()),
                    ctx.document,
                    span,
                )
            })?;
        if pos != 0 {
            let v = variables.remove(pos);
            variables.insert(0, v);
        }
    }

    // Default extras matches grammar.js (dsl.js:254): `[/\s/]` applied
    // when neither the grammar nor its base specifies extras.
    let extra_roots = match (result.extras, base) {
        (Some(e), _) => e,
        (None, Some(b)) => b.extra_roots.clone(),
        (None, None) => {
            let value = pool.intern("\\s");
            let flags = StrPool::EMPTY_STR_ID;
            vec![pool.push_node(Rule::Pattern(value, flags))]
        }
    };

    Ok(LoweredGrammar {
        name: result.language,
        variables,
        extra_roots,
        reserved_sets: merge_reserved(result.reserved, base.map(|b| b.reserved_sets.as_slice())),
        external_roots: inherit(result.externals, base, |b| &b.external_roots),
        supertype_names: inherit(result.supertypes, base, |b| &b.supertype_names),
        conflict_names: inherit(result.conflicts, base, |b| &b.conflict_names),
        inline_names: inherit(result.inline, base, |b| &b.inline_names),
        word_name: result.word.or_else(|| base.and_then(|b| b.word_name)),
        precedence_orderings: inherit(result.precedences, base, |b| &b.precedence_orderings),
    })
}
