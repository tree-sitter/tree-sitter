//! Walks the typed AST, emitting [`Rule`] nodes directly into the loader-wide
//! [`RulePool`]. [`super`] assembles the resulting ids into a
//! [`LoweredGrammar`](crate::nativedsl::LoweredGrammar).

use std::path::PathBuf;

use rustc_hash::FxHashMap;

use super::{
    super::{
        LowerError, Module, ModuleId, NoteMessage,
        ast::{
            BinOp, ChildRange, ConfigField, ExpandId, ForId, IdentKind, MacroId, ModuleContext,
            Node, NodeId, ObjectField, PrecKind, RepeatKind, SharedAst, Span,
        },
    },
    CallFrame, ForFrame, LetState, LowerErrorKind, LowerResult, LoweringState, MAX_CALL_DEPTH,
    repr::{Value, ValueId},
};

use crate::{
    grammars::{PrecedenceEntry, ReservedWordContext},
    nativedsl::DocumentMap,
    rules::{Alias, Associativity, MetadataParams, Precedence, Rule, RuleId, RulePool},
    strpool::StrId,
};

/// One item on the lowering work stack.
#[derive(Clone, Copy)]
pub(super) enum Task {
    Expr(NodeId),
    Rule(NodeId),
    SpreadValues(NodeId),
    SpreadRules(NodeId),
    Combine(NodeId),
    WrapRule,
    ExtractRule,
}

/// Per-grammar evaluation wrapper around long-lived [`LoweringState`].
pub(super) struct Evaluator<'a, 'ast> {
    pub state: &'a mut LoweringState,
    pub pool: &'a mut RulePool,
    pub shared: &'ast SharedAst,
    /// Modules already loaded before this evaluation. The module being lowered
    /// ("root") is not in this slice; it lives in `root_ctx`. Its module id is
    /// `previous.len()` (== `root_id`).
    previous: &'a [Module],
    documents: &'a DocumentMap,
    pub(crate) root_ctx: &'a ModuleContext,
    root_id: ModuleId,
    /// May equal `root_id` (current module) or index into `previous`.
    current_module: ModuleId,
}

impl<'a, 'ast> Evaluator<'a, 'ast> {
    pub fn new(
        state: &'a mut LoweringState,
        pool: &'a mut RulePool,
        shared: &'ast SharedAst,
        previous: &'a [Module],
        documents: &'a DocumentMap,
        root_ctx: &'a ModuleContext,
    ) -> Self {
        // The loader bounds the module count to u8 before lowering runs.
        debug_assert!(u8::try_from(previous.len()).is_ok());
        let root_id = ModuleId::from(previous.len() as u8);
        state.reset_per_grammar();
        Self {
            state,
            pool,
            shared,
            previous,
            documents,
            root_ctx,
            root_id,
            current_module: root_id,
        }
    }

    /// Evaluate a let and its unresolved dependencies.
    pub fn eval_let(&mut self, let_id: NodeId) -> LowerResult<ValueId> {
        if let Some(LetState::Resolved(val)) = self.state.lets.get(&let_id).copied() {
            return Ok(val);
        }
        self.state.lets.insert(let_id, LetState::InProgress);

        let mut stack = vec![let_id];
        while let Some(&cur) = stack.last() {
            expect_pat!(Node::Let { value, .. }, *self.shared.arena.get(cur));
            let dep = self.shared.first_unresolved_let_dep(
                value,
                |id| matches!(self.state.lets.get(&id), Some(LetState::Resolved(_))),
                &mut self.state.scratch.dep_walk,
            );

            if let Some((dep, reference)) = dep {
                // Resolved lets were filtered above, so an existing entry is in progress.
                if self.state.lets.insert(dep, LetState::InProgress).is_some() {
                    let span = self.shared.arena.span(reference);
                    return Err(self.circular_let_error(dep, span));
                }
                stack.push(dep);
                continue;
            }

            let val = self.eval_expr(value)?;
            self.state.lets.insert(cur, LetState::Resolved(val));
            stack.pop();
        }

        match self.state.lets[&let_id] {
            LetState::Resolved(val) => Ok(val),
            LetState::InProgress => unreachable!(),
        }
    }

    fn circular_let_error(&self, let_id: NodeId, reference: Span) -> LowerError {
        expect_pat!(Node::Let { name, .. }, *self.shared.arena.get(let_id));
        let mut err = self.err(
            LowerErrorKind::CircularLet(self.pool.resolve(name).to_owned()),
            self.shared.arena.span(let_id),
        );
        err.add_note(
            self.module_ctx(self.current_module)
                .note(NoteMessage::SelfReferenceHere, reference),
        );
        err
    }

    fn module_ctx(&self, idx: ModuleId) -> &'a ModuleContext {
        if idx == self.root_id {
            self.root_ctx
        } else {
            self.previous[usize::from(idx)].ctx()
        }
    }

    fn err(&self, kind: LowerErrorKind, span: Span) -> LowerError {
        let ctx = self.module_ctx(self.current_module);
        LowerError::new(kind, ctx.document, span)
    }

    fn checked_len(&self, n: usize, span: Span) -> LowerResult<u16> {
        u16::try_from(n).map_err(|_| self.err(LowerErrorKind::TooManyChildren(n), span))
    }

    fn alloc_val(&mut self, val: Value) -> ValueId {
        let id = ValueId(self.state.ir.values.len() as u32);
        self.state.ir.values.push(val);
        id
    }

    fn get_val(&self, id: ValueId) -> &Value {
        // SAFETY: id came from `alloc_val`, which hands out sequential indices into
        // `self.state.ir.values`. That pool is append-only and never reset for the
        // life of the `LoweringState`.
        unsafe { self.state.ir.values.get_unchecked(id.0 as usize) }
    }

    fn alloc_list(&mut self, items: &[ValueId]) -> ValueId {
        let start = self.state.ir.value_children.len() as u32;
        self.state.ir.value_children.extend_from_slice(items);
        self.finish_list(start, items.len())
    }

    fn finish_list(&mut self, start: u32, len: usize) -> ValueId {
        // Config list fields were bounded when their source module was lowered.
        debug_assert!(u16::try_from(len).is_ok());
        self.alloc_val(Value::List(ChildRange::new(start, len as u16)))
    }

    fn alloc_object(&mut self, map: FxHashMap<StrId, ValueId>) -> ValueId {
        let idx = self.state.ir.object_pool.len() as u32;
        self.state.ir.object_pool.push(map);
        self.alloc_val(Value::Object(idx))
    }

    fn list_items(&self, v: ValueId) -> &[ValueId] {
        &self.state.ir.value_children[self.list_range(v).as_range()]
    }

    fn list_range(&self, v: ValueId) -> ChildRange {
        expect_pat!(Value::List(range), *self.get_val(v));
        range
    }

    fn str_id(&self, v: ValueId) -> StrId {
        expect_pat!(Value::Str(s), *self.get_val(v));
        s
    }

    fn int_val(&self, v: ValueId) -> i32 {
        expect_pat!(Value::Int(n), *self.get_val(v));
        n
    }

    fn finish_seq(&mut self, base: usize) -> RuleId {
        let rule = self.pool.seq(&self.state.scratch.rule_scratch[base..]);
        self.state.scratch.rule_scratch.truncate(base);
        rule
    }

    fn finish_choice(&mut self, base: usize) -> RuleId {
        let rule = self.pool.choice(&self.state.scratch.rule_scratch[base..]);
        self.state.scratch.rule_scratch.truncate(base);
        rule
    }

    fn alloc_rule(&mut self, rule: Rule) -> RuleId {
        self.pool.push_node(rule)
    }

    fn metadata(&mut self, inner: RuleId, f: impl FnOnce(&mut MetadataParams)) -> RuleId {
        if let Rule::Metadata { params, rule } = self.pool.node(inner) {
            let mut p = self.pool.params(params);
            if !p.is_token {
                f(&mut p);
                let params = self.pool.push_params(p);
                return self.alloc_rule(Rule::Metadata { params, rule });
            }
        }
        let mut p = MetadataParams::default();
        f(&mut p);
        let params = self.pool.push_params(p);
        self.alloc_rule(Rule::Metadata {
            params,
            rule: inner,
        })
    }

    fn get_rule(&self, id: RuleId) -> Rule {
        self.pool.node(id)
    }

    fn owned_symbol_val(&mut self, name: StrId) -> ValueId {
        let rid = self.alloc_rule(Rule::NamedSymbol(name));
        self.alloc_val(Value::Rule(rid))
    }

    pub fn eval_rule_list(&mut self, id: NodeId) -> LowerResult<Vec<RuleId>> {
        let vid = self.eval_expr(id)?;
        let range = self.list_range(vid);
        let mut rules = Vec::with_capacity(range.len as usize);
        for i in range.as_range() {
            let v = self.state.ir.value_children[i];
            rules.push(self.value_to_rule(v));
        }
        Ok(rules)
    }

    fn value_to_rule(&mut self, id: ValueId) -> RuleId {
        match *self.get_val(id) {
            Value::Rule(rid) => rid,
            Value::Str(sid) => self.alloc_rule(Rule::String(sid)),
            // Guarded by typecheck: only rule-like values reach here.
            _ => unreachable!(),
        }
    }

    fn rule_name(&self, v: ValueId, span: Span) -> LowerResult<StrId> {
        let Value::Rule(rid) = *self.get_val(v) else {
            return Err(self.err(LowerErrorKind::ExpectedRuleName, span));
        };
        let Rule::NamedSymbol(sid) = self.get_rule(rid) else {
            return Err(self.err(LowerErrorKind::ExpectedRuleName, span));
        };
        Ok(sid)
    }

    pub fn eval_name_list(&mut self, id: NodeId) -> LowerResult<Vec<StrId>> {
        let vid = self.eval_expr(id)?;
        let span = self.shared.arena.span(id);
        let items = self.list_items(vid);
        items.iter().map(|&v| self.rule_name(v, span)).collect()
    }

    pub fn eval_conflicts(&mut self, id: NodeId) -> LowerResult<Vec<Vec<StrId>>> {
        let vid = self.eval_expr(id)?;
        let span = self.shared.arena.span(id);
        let outer = self.list_items(vid);
        outer
            .iter()
            .map(|&group_vid| {
                let inner = self.list_items(group_vid);
                inner.iter().map(|&v| self.rule_name(v, span)).collect()
            })
            .collect()
    }

    pub fn eval_precedences(&mut self, id: NodeId) -> LowerResult<Vec<Vec<PrecedenceEntry>>> {
        let vid = self.eval_expr(id)?;
        let span = self.shared.arena.span(id);
        let outer = self.list_items(vid);
        outer
            .iter()
            .map(|&group_vid| {
                let inner = self.list_items(group_vid);
                inner
                    .iter()
                    .map(|&v| match *self.get_val(v) {
                        Value::Str(sid) => Ok(PrecedenceEntry::Name(sid)),
                        Value::Rule(_) => Ok(PrecedenceEntry::Symbol(self.rule_name(v, span)?)),
                        _ => unreachable!(),
                    })
                    .collect()
            })
            .collect()
    }

    pub fn eval_rule_name(&mut self, id: NodeId) -> LowerResult<StrId> {
        let rid = self.lower_to_rule(id)?;
        match self.get_rule(rid) {
            Rule::NamedSymbol(sid) => Ok(sid),
            _ => Err(self.err(LowerErrorKind::ExpectedRuleName, self.shared.arena.span(id))),
        }
    }

    pub fn eval_reserved(&mut self, id: NodeId) -> LowerResult<Vec<ReservedWordContext>> {
        expect_pat!(Node::Object(range), self.shared.arena.get(id));
        self.shared
            .pools
            .get_object(*range)
            .iter()
            .map(
                |&ObjectField {
                     name: name_span,
                     value: val_id,
                 }| {
                    let words = self.eval_rule_list(val_id)?;
                    Ok(ReservedWordContext {
                        name: name_span.value,
                        roots: words,
                    })
                },
            )
            .collect()
    }

    fn eval_grammar_config(
        &mut self,
        mod_idx: ModuleId,
        field: ConfigField,
        span: Span,
    ) -> LowerResult<ValueId> {
        use ConfigField as C;
        let grammar = self.previous[usize::from(mod_idx)].lowered().unwrap();
        let val = match field {
            C::Language => self.alloc_val(Value::Str(grammar.name)),
            C::Extras => self.rule_list_val(&grammar.extra_roots),
            C::Externals => self.rule_list_val(&grammar.external_roots),
            C::Inline => self.symbol_list_val(&grammar.inline_names),
            C::Supertypes => self.symbol_list_val(&grammar.supertype_names),
            C::Conflicts => {
                let vals: Vec<ValueId> = grammar
                    .conflict_names
                    .iter()
                    .map(|g| self.symbol_list_val(g))
                    .collect::<Vec<_>>();
                self.alloc_list(&vals)
            }
            C::Precedences => {
                let vals: Vec<ValueId> = grammar
                    .precedence_orderings
                    .iter()
                    .map(|group| {
                        let inner_start = self.state.ir.value_children.len() as u32;
                        for entry in group {
                            let vid = match entry {
                                PrecedenceEntry::Name(s) => self.alloc_val(Value::Str(*s)),
                                PrecedenceEntry::Symbol(s) => self.owned_symbol_val(*s),
                            };
                            self.state.ir.value_children.push(vid);
                        }
                        self.finish_list(inner_start, group.len())
                    })
                    .collect::<Vec<_>>();
                self.alloc_list(&vals)
            }
            C::Word => {
                if let Some(name) = &grammar.word_name {
                    self.owned_symbol_val(*name)
                } else {
                    return Err(self.err(LowerErrorKind::ConfigFieldUnset, span));
                }
            }
            C::Start => match grammar.variables.first() {
                Some(first) => self.owned_symbol_val(first.name),
                None => return Err(self.err(LowerErrorKind::ConfigFieldUnset, span)),
            },
            C::Reserved => {
                let n = grammar.reserved_sets.len();
                let mut map = FxHashMap::with_capacity_and_hasher(n, rustc_hash::FxBuildHasher);
                for rwc in &grammar.reserved_sets {
                    let words_vid = self.rule_list_val(&rwc.roots);
                    map.insert(rwc.name, words_vid);
                }
                self.alloc_object(map)
            }
            C::Inherits | C::Flags => unreachable!(),
        };
        Ok(val)
    }

    fn rule_list_val(&mut self, rules_data: &[RuleId]) -> ValueId {
        let start = self.state.ir.value_children.len() as u32;
        self.state.ir.value_children.reserve(rules_data.len());
        for &rid in rules_data {
            let vid = self.alloc_val(Value::Rule(rid));
            self.state.ir.value_children.push(vid);
        }
        self.finish_list(start, rules_data.len())
    }

    fn symbol_list_val(&mut self, names: &[StrId]) -> ValueId {
        let start = self.state.ir.value_children.len() as u32;
        self.state.ir.value_children.reserve(names.len());
        for &name in names {
            let vid = self.owned_symbol_val(name);
            self.state.ir.value_children.push(vid);
        }
        self.finish_list(start, names.len())
    }

    /// Evaluate an expression node to a [`ValueId`].
    pub fn eval_expr(&mut self, id: NodeId) -> LowerResult<ValueId> {
        // Re-entrant walks share the work stack and stop at their own base.
        let work_base = self.state.scratch.work.len();
        self.push_task(Task::Expr(id));
        self.drive(work_base)?;
        Ok(self.pop_val())
    }

    pub fn lower_to_rule(&mut self, id: NodeId) -> LowerResult<RuleId> {
        let work_base = self.state.scratch.work.len();
        self.push_task(Task::Rule(id));
        self.drive(work_base)?;
        Ok(self.pop_rule())
    }

    fn drive(&mut self, work_base: usize) -> LowerResult<()> {
        while self.state.scratch.work.len() > work_base {
            let task = self.state.scratch.work.pop().unwrap();
            self.step(task)?;
        }
        Ok(())
    }

    fn step(&mut self, task: Task) -> LowerResult<()> {
        match task {
            Task::Expr(id) => self.dispatch_expr(id),
            Task::Rule(id) => {
                self.dispatch_rule(id);
                Ok(())
            }
            Task::SpreadValues(node) => {
                expect_pat!(Node::For { for_id, body }, *self.shared.arena.get(node));
                self.expand_for_values(for_id, body)
            }
            Task::SpreadRules(node) => {
                expect_pat!(Node::For { for_id, body }, *self.shared.arena.get(node));
                self.expand_for_rules(for_id, body)
            }
            Task::Combine(id) => self.combine(id),
            Task::WrapRule => {
                let rid = self.pop_rule();
                self.push_val(Value::Rule(rid));
                Ok(())
            }
            Task::ExtractRule => {
                let vid = self.pop_val();
                let rid = self.value_to_rule(vid);
                self.push_rule_id(rid);
                Ok(())
            }
        }
    }

    fn pop_val(&mut self) -> ValueId {
        self.state.scratch.val_scratch.pop().unwrap()
    }

    fn pop_rule(&mut self) -> RuleId {
        self.state.scratch.rule_scratch.pop().unwrap()
    }

    fn push_val(&mut self, val: Value) {
        let id = self.alloc_val(val);
        self.state.scratch.val_scratch.push(id);
    }

    fn push_val_id(&mut self, id: ValueId) {
        self.state.scratch.val_scratch.push(id);
    }

    fn push_rule(&mut self, rule: Rule) {
        let id = self.alloc_rule(rule);
        self.state.scratch.rule_scratch.push(id);
    }

    fn push_rule_id(&mut self, id: RuleId) {
        self.state.scratch.rule_scratch.push(id);
    }

    fn push_combine(&mut self, id: NodeId) {
        self.push_task(Task::Combine(id));
    }

    fn push_combine_var(&mut self, id: NodeId, base: usize) {
        self.state.scratch.combine_bases.push(base as u32);
        self.push_task(Task::Combine(id));
    }

    fn push_unary_combine(&mut self, id: NodeId, child: Task) {
        self.push_combine(id);
        self.push_task(child);
    }

    fn push_task(&mut self, task: Task) {
        self.state.scratch.work.push(task);
    }

    fn try_leaf_rule(&mut self, id: NodeId) -> Option<RuleId> {
        let rule = match self.shared.arena.get(id) {
            Node::Ident(IdentKind::Rule(name)) => Rule::NamedSymbol(*name),
            Node::StringLit(sid) => Rule::String(*sid),
            Node::Blank => Rule::Blank,
            Node::Eof => Rule::Eof,
            _ => return None,
        };
        Some(self.alloc_rule(rule))
    }

    fn try_push_leaf_rule(&mut self, id: NodeId) -> bool {
        match self.try_leaf_rule(id) {
            Some(rid) => {
                self.push_rule_id(rid);
                true
            }
            None => false,
        }
    }

    fn dispatch_expr(&mut self, id: NodeId) -> LowerResult<()> {
        let span = self.shared.arena.span(id);
        match self.shared.arena.get(id) {
            Node::IntLit(n) => {
                let v = i32::try_from(*n)
                    .map_err(|_| self.err(LowerErrorKind::IntegerOverflow(*n), span))?;
                self.push_val(Value::Int(v));
            }
            Node::StringLit(sid) => self.push_val(Value::Str(*sid)),
            Node::Neg(inner) => {
                // Special-case Neg over a literal so the most negative i32
                // (-i32::MIN as positive overflows i32, but fits in i64) is
                // reachable as `-2147483648`.
                if let Node::IntLit(m) = *self.shared.arena.get(*inner) {
                    let neg = -m;
                    let v = i32::try_from(neg)
                        .map_err(|_| self.err(LowerErrorKind::IntegerOverflow(neg), span))?;
                    self.push_val(Value::Int(v));
                } else {
                    self.push_unary_combine(id, Task::Expr(*inner));
                }
            }
            &Node::BinOp { lhs, rhs, .. } => {
                self.push_combine(id);
                self.push_task(Task::Expr(rhs));
                self.push_task(Task::Expr(lhs));
            }
            Node::Ident(IdentKind::Rule(name)) => {
                let rid = self.alloc_rule(Rule::NamedSymbol(*name));
                self.push_val(Value::Rule(rid));
            }
            Node::MacroParam { index, .. } => {
                let base = usize::from(*self.state.scratch.macro_arg_bases.last().unwrap());
                let v = self.state.scratch.macro_args[base + usize::from(*index)];
                self.push_val_id(v);
            }
            Node::ForBinding { for_id, index, .. } => {
                let (for_id, index) = (*for_id, usize::from(*index));
                let base = self
                    .state
                    .scratch
                    .for_binding_frames
                    .iter()
                    .rev()
                    .find(|frame| frame.for_id == for_id)
                    .unwrap()
                    .values_base as usize;
                let v = self.state.scratch.for_binding_values[base + index];
                self.push_val_id(v);
            }
            &Node::Ident(IdentKind::Var(let_id)) => {
                let val = match self.state.lets.get(&let_id).copied() {
                    Some(LetState::InProgress) => {
                        return Err(self.circular_let_error(let_id, span));
                    }
                    Some(LetState::Resolved(val)) => val,
                    None => self.eval_let(let_id)?,
                };
                self.push_val_id(val);
            }
            &Node::GrammarConfig { module, .. } => self.push_unary_combine(id, Task::Expr(module)),
            Node::Inherit { module, .. } | Node::Import { module, .. } => {
                let global_id = module.unwrap();
                self.push_val(Value::Module(global_id));
            }
            &Node::Append { left, right } => {
                self.push_combine(id);
                self.push_task(Task::Expr(right));
                self.push_task(Task::Expr(left));
            }
            &Node::FieldAccess { obj, .. } => self.push_unary_combine(id, Task::Expr(obj)),
            &Node::ModuleRule { rule, .. } => self.push_val(Value::Rule(rule)),
            &Node::Object(range) => {
                let base = self.state.scratch.val_scratch.len();
                self.push_combine_var(id, base);
                for field in self.shared.pools.get_object(range).iter().rev() {
                    self.push_task(Task::Expr(field.value));
                }
            }
            &Node::List(range) | &Node::Tuple(range) => {
                let base = self.state.scratch.val_scratch.len();
                self.push_combine_var(id, base);
                for &item in self.shared.pools.child_slice(range).iter().rev() {
                    let task = match self.shared.arena.get(item) {
                        Node::For { .. } => Task::SpreadValues(item),
                        _ => Task::Expr(item),
                    };
                    self.push_task(task);
                }
            }
            &Node::Concat(range) => {
                let base = self.state.scratch.val_scratch.len();
                self.push_combine_var(id, base);
                for &part in self.shared.pools.child_slice(range).iter().rev() {
                    self.push_task(Task::Expr(part));
                }
            }
            &Node::DynRegex { pattern, flags } => {
                let base = self.state.scratch.val_scratch.len();
                self.push_combine_var(id, base);
                // pattern lands at [base], the optional flags (if any) at [base + 1].
                if let Some(flags) = flags {
                    self.push_task(Task::Expr(flags));
                }
                self.push_task(Task::Expr(pattern));
            }
            &Node::Call { name, args } => {
                expect_pat!(
                    Node::Ident(IdentKind::Macro(macro_id)),
                    self.shared.arena.get(name)
                );
                // Macro expansion stays recursive, bounded by MAX_CALL_DEPTH.
                let v = self.invoke_macro(*macro_id, args, span)?;
                self.push_val_id(v);
            }
            #[rustfmt::skip]
            Node::SymRef { .. } | Node::SeqOrChoice { .. } | Node::Repeat { .. }
            | Node::Blank | Node::Field { .. } | Node::Alias { .. } | Node::Eof
            | Node::Token { .. } | Node::Prec { .. } | Node::Reserved { .. } => {
                self.push_task(Task::WrapRule);
                self.push_task(Task::Rule(id));
            }
            // Non-expression nodes never reach lower.
            _ => unreachable!(),
        }
        Ok(())
    }

    fn dispatch_rule(&mut self, id: NodeId) {
        match self.shared.arena.get(id) {
            Node::Ident(IdentKind::Rule(name)) => self.push_rule(Rule::NamedSymbol(*name)),
            &Node::ModuleRule { rule, .. } => self.push_rule_id(rule),
            Node::StringLit(sid) => self.push_rule(Rule::String(*sid)),
            Node::Blank => self.push_rule(Rule::Blank),
            Node::Eof => self.push_rule(Rule::Eof),
            &Node::SymRef { expr } => self.push_unary_combine(id, Task::Expr(expr)),
            &Node::SeqOrChoice { seq, range } => {
                let items = self.shared.pools.child_slice(range);
                let base = self.state.scratch.rule_scratch.len();
                // Fast path for the common all-leaf sequence/choice case.
                let mut i = 0;
                while i < items.len() && self.try_push_leaf_rule(items[i]) {
                    i += 1;
                }
                if i == items.len() {
                    let rule = if seq {
                        self.finish_seq(base)
                    } else {
                        self.finish_choice(base)
                    };
                    self.push_rule_id(rule);
                    return;
                }
                // Push remaining members reversed so they run in source order.
                self.push_combine_var(id, base);
                for &item in items[i..].iter().rev() {
                    let task = match self.shared.arena.get(item) {
                        Node::For { .. } => Task::SpreadRules(item),
                        _ => Task::Rule(item),
                    };
                    self.push_task(task);
                }
            }
            &Node::Token { immediate, inner } => {
                if let Some(c) = self.try_leaf_rule(inner) {
                    let rule = self.metadata(c, |p| {
                        p.is_token = true;
                        p.is_main_token = immediate;
                    });
                    self.push_rule_id(rule);
                } else {
                    self.push_unary_combine(id, Task::Rule(inner));
                }
            }
            &Node::Field { name, content } => {
                if let Some(c) = self.try_leaf_rule(content) {
                    let rule = self.metadata(c, |p| p.field = Some(name));
                    self.push_rule_id(rule);
                } else {
                    self.push_unary_combine(id, Task::Rule(content));
                }
            }
            &Node::Reserved { context, content } => {
                if let Some(c) = self.try_leaf_rule(content) {
                    self.push_rule(Rule::Reserved {
                        rule: c,
                        ctx: context,
                    });
                } else {
                    self.push_unary_combine(id, Task::Rule(content));
                }
            }
            &Node::Repeat { inner, .. } => self.push_unary_combine(id, Task::Rule(inner)),
            &Node::Prec { value, content, .. } => {
                self.push_combine(id);
                self.push_task(Task::Rule(content));
                self.push_task(Task::Expr(value));
            }
            &Node::Alias { content, target } => {
                self.push_combine(id);
                self.push_task(Task::Rule(content));
                if !matches!(
                    self.shared.arena.get(target),
                    Node::Ident(IdentKind::Rule(_))
                ) {
                    self.push_task(Task::Expr(target));
                }
            }
            // Dynamic rule-valued expressions are evaluated before extraction.
            // Typecheck rejects every other remaining node in a rule context.
            _ => {
                self.push_task(Task::ExtractRule);
                self.push_task(Task::Expr(id));
            }
        }
    }

    fn pop_combine_base(&mut self) -> usize {
        self.state.scratch.combine_bases.pop().unwrap() as usize
    }

    fn combine(&mut self, id: NodeId) -> LowerResult<()> {
        let span = self.shared.arena.span(id);
        match self.shared.arena.get(id) {
            Node::Neg(_) => {
                let v = self.pop_val();
                let n = self.int_val(v);
                let neg = n.checked_neg().ok_or_else(|| {
                    self.err(LowerErrorKind::IntegerOverflow(-i64::from(n)), span)
                })?;
                self.push_val(Value::Int(neg));
            }
            &Node::BinOp { op, .. } => {
                // rhs was pushed last, so it pops first.
                let rv = self.pop_val();
                let lv = self.pop_val();
                let l = self.int_val(lv);
                let r = self.int_val(rv);
                let (narrow, wide) = match op {
                    BinOp::Add => (l.checked_add(r), i64::from(l) + i64::from(r)),
                    BinOp::Sub => (l.checked_sub(r), i64::from(l) - i64::from(r)),
                };
                let v =
                    narrow.ok_or_else(|| self.err(LowerErrorKind::IntegerOverflow(wide), span))?;
                self.push_val(Value::Int(v));
            }
            Node::Append { .. } => {
                let rv = self.pop_val();
                let lv = self.pop_val();
                let lr = self.list_range(lv);
                let rr = self.list_range(rv);
                let start = self.state.ir.value_children.len() as u32;
                let total = usize::from(lr.len) + usize::from(rr.len);
                let len = self.checked_len(total, span)?;
                self.state
                    .ir
                    .value_children
                    .extend_from_within(lr.as_range());
                self.state
                    .ir
                    .value_children
                    .extend_from_within(rr.as_range());
                self.push_val(Value::List(ChildRange::new(start, len)));
            }
            &Node::GrammarConfig { field, .. } => {
                let mod_val = self.pop_val();
                expect_pat!(Value::Module(mod_idx), *self.get_val(mod_val));
                let v = self.eval_grammar_config(mod_idx, field, span)?;
                self.push_val_id(v);
            }
            &Node::FieldAccess { field, .. } => {
                let obj_val = self.pop_val();
                expect_pat!(Value::Object(idx), *self.get_val(obj_val));
                let map = &self.state.ir.object_pool[idx as usize];
                let v = map.get(&field).copied().ok_or_else(|| {
                    let mut available: Vec<String> = map
                        .keys()
                        .map(|&k| self.pool.resolve(k).to_string())
                        .collect();
                    available.sort_unstable();
                    self.err(
                        LowerErrorKind::FieldNotFound {
                            field: self.pool.resolve(field).to_string(),
                            available,
                        },
                        span,
                    )
                })?;
                self.push_val_id(v);
            }
            &Node::Object(range) => {
                let base = self.pop_combine_base();
                let fields = self.shared.pools.get_object(range);
                let mut map =
                    FxHashMap::with_capacity_and_hasher(fields.len(), rustc_hash::FxBuildHasher);
                for (i, field) in fields.iter().enumerate() {
                    map.insert(field.name.value, self.state.scratch.val_scratch[base + i]);
                }
                self.state.scratch.val_scratch.truncate(base);
                let obj = self.alloc_object(map);
                self.push_val_id(obj);
            }
            node @ (&Node::List(_) | &Node::Tuple(_)) => {
                let base = self.pop_combine_base();
                let is_list = matches!(node, Node::List(_));
                let start = self.state.ir.value_children.len() as u32;
                let count = self.state.scratch.val_scratch.len() - base;
                let len = if is_list {
                    self.checked_len(count, span)?
                } else {
                    // Typecheck limits tuples to eight elements.
                    count as u16
                };
                self.state
                    .ir
                    .value_children
                    .extend_from_slice(&self.state.scratch.val_scratch[base..]);
                self.state.scratch.val_scratch.truncate(base);
                let range = ChildRange::new(start, len);
                self.push_val(if is_list {
                    Value::List(range)
                } else {
                    Value::Tuple(range)
                });
            }
            Node::Concat(_) => {
                let base = self.pop_combine_base();
                let mut result = std::mem::take(&mut self.state.scratch.concat_buf);
                for &vid in &self.state.scratch.val_scratch[base..] {
                    result.push_str(self.pool.resolve(self.str_id(vid)));
                }
                self.state.scratch.val_scratch.truncate(base);
                let sid = self.pool.intern(&result);
                result.clear();
                self.state.scratch.concat_buf = result;
                self.push_val(Value::Str(sid));
            }
            Node::DynRegex { .. } => {
                let base = self.pop_combine_base();
                let pattern_vid = self.state.scratch.val_scratch[base];
                let flags_vid = self.state.scratch.val_scratch.get(base + 1).copied();
                self.state.scratch.val_scratch.truncate(base);
                let ps = self.str_id(pattern_vid);
                let fs =
                    flags_vid.map_or(crate::strpool::StrPool::EMPTY_STR_ID, |fv| self.str_id(fv));
                let rid = self.alloc_rule(Rule::Pattern(ps, fs));
                self.push_val(Value::Rule(rid));
            }
            &Node::SymRef { .. } => {
                let vid = self.pop_val();
                let name = self.str_id(vid);
                self.push_rule(Rule::NamedSymbol(name));
            }
            &Node::SeqOrChoice { seq, .. } => {
                let base = self.pop_combine_base();
                let rule = if seq {
                    self.finish_seq(base)
                } else {
                    self.finish_choice(base)
                };
                self.push_rule_id(rule);
            }
            &Node::Repeat { kind, .. } => {
                let inner = self.pop_rule();
                if kind == RepeatKind::OneOrMore {
                    self.push_rule(Rule::Repeat(inner));
                } else {
                    let first = if kind == RepeatKind::ZeroOrMore {
                        self.alloc_rule(Rule::Repeat(inner))
                    } else {
                        inner
                    };
                    let blank = self.alloc_rule(Rule::Blank);
                    let base = self.state.scratch.rule_scratch.len();
                    self.state.scratch.rule_scratch.push(first);
                    self.state.scratch.rule_scratch.push(blank);
                    let rule = self.finish_choice(base);
                    self.push_rule_id(rule);
                }
            }
            &Node::Field { name, .. } => {
                let inner = self.pop_rule();
                let rule = self.metadata(inner, |p| p.field = Some(name));
                self.push_rule_id(rule);
            }
            &Node::Token { immediate, .. } => {
                let inner = self.pop_rule();
                let rule = self.metadata(inner, |p| {
                    p.is_token = true;
                    p.is_main_token = immediate;
                });
                self.push_rule_id(rule);
            }
            &Node::Reserved { context, .. } => {
                let inner = self.pop_rule();
                self.push_rule(Rule::Reserved {
                    rule: inner,
                    ctx: context,
                });
            }
            &Node::Prec { kind, .. } => {
                let vid = self.pop_val();
                let inner = self.pop_rule();
                if kind == PrecKind::Dynamic {
                    let n = self.int_val(vid);
                    let rule = self.metadata(inner, |p| p.dynamic_precedence = n);
                    self.push_rule_id(rule);
                } else {
                    let precedence = match *self.get_val(vid) {
                        Value::Int(n) => Precedence::Integer(n),
                        Value::Str(s) => Precedence::Name(s),
                        // Guarded by typecheck: static precedence is int or str.
                        _ => unreachable!(),
                    };
                    let associativity = match kind {
                        PrecKind::Left => Some(Associativity::Left),
                        PrecKind::Right => Some(Associativity::Right),
                        _ => None,
                    };
                    let rule = self.metadata(inner, |p| {
                        p.precedence = precedence;
                        if let Some(assoc) = associativity {
                            p.associativity = Some(assoc);
                        }
                    });
                    self.push_rule_id(rule);
                }
            }
            &Node::Alias { target, .. } => {
                if let &Node::Ident(IdentKind::Rule(value)) = self.shared.arena.get(target) {
                    let inner = self.pop_rule();
                    let rule = self.metadata(inner, |p| {
                        p.alias = Some(Alias {
                            value,
                            is_named: true,
                        });
                    });
                    self.push_rule_id(rule);
                } else {
                    let vid = self.pop_val();
                    let inner = self.pop_rule();
                    match *self.get_val(vid) {
                        Value::Str(value) => {
                            let rule = self.metadata(inner, |p| {
                                p.alias = Some(Alias {
                                    value,
                                    is_named: false,
                                });
                            });
                            self.push_rule_id(rule);
                        }
                        Value::Rule(rid) => {
                            let value = match self.get_rule(rid) {
                                Rule::NamedSymbol(s) => s,
                                _ => Err(self.err(
                                    LowerErrorKind::ExpectedRuleName,
                                    self.shared.arena.span(target),
                                ))?,
                            };
                            let rule = self.metadata(inner, |p| {
                                p.alias = Some(Alias {
                                    value,
                                    is_named: true,
                                });
                            });
                            self.push_rule_id(rule);
                        }
                        // Guarded by typecheck: only str or rule-name targets pass.
                        _ => unreachable!(),
                    }
                }
            }
            // Combine is only enqueued for the compound nodes handled above.
            _ => unreachable!(),
        }
        Ok(())
    }

    fn push_call(&mut self, name: StrId, call_span: Span) -> LowerResult<()> {
        // Push first so the trace includes the call that trips the limit.
        self.state.scratch.call_stack.push(CallFrame {
            name,
            call_span,
            caller_mod: self.current_module,
        });
        if self.state.scratch.call_stack.len() > usize::from(MAX_CALL_DEPTH) {
            let root = self.state.scratch.call_stack[0];
            let trace = self.build_call_trace();
            let ctx = self.module_ctx(root.caller_mod);
            return Err(LowerError::new(
                LowerErrorKind::CallDepthExceeded(trace),
                ctx.document,
                root.call_span,
            ));
        }
        Ok(())
    }

    fn build_call_trace(&self) -> Vec<(String, PathBuf, usize, usize)> {
        self.state
            .scratch
            .call_stack
            .iter()
            .map(|frame| {
                let name = self.pool.resolve(frame.name).to_string();
                let call_ctx = self.module_ctx(frame.caller_mod);
                let document = self.documents.document(call_ctx.document);
                let offset = frame.call_span.start as usize;
                let bytes = &document.text().as_bytes()[..offset];
                let line = memchr::memchr_iter(b'\n', bytes).count() + 1;
                let col = offset - memchr::memrchr(b'\n', bytes).map_or(0, |i| i + 1) + 1;
                (name, document.path().to_owned(), line, col)
            })
            .collect()
    }

    fn bind_args_and<R>(
        &mut self,
        name: StrId,
        def_module: ModuleId,
        args: ChildRange,
        span: Span,
        body_eval: impl FnOnce(&mut Self) -> LowerResult<R>,
    ) -> LowerResult<R> {
        // Args evaluate in the caller's macro context, before callee bindings.
        stack_scope!(
            self.state.scratch.macro_args => args_base,
            self.state.scratch.call_stack => _call_base,
            self.state.scratch.macro_arg_bases => _bases_base;
            {
                self.push_call(name, span)?;
                for &arg_id in self.shared.pools.child_slice(args) {
                    let v = self.eval_expr(arg_id)?;
                    self.state.scratch.macro_args.push(v);
                }
                self.state.scratch.macro_arg_bases.push(args_base as u16);
                let saved = self.current_module;
                self.current_module = def_module;
                let result = body_eval(self);
                self.current_module = saved;
                result
            }
        )
    }

    fn invoke_macro(
        &mut self,
        macro_id: MacroId,
        args: ChildRange,
        span: Span,
    ) -> LowerResult<ValueId> {
        let config = self.shared.pools.get_macro(macro_id);
        let (name, body, def_module) = (config.name.value, config.body, config.def_module());
        self.bind_args_and(name, def_module, args, span, |e| e.eval_expr(body))
    }

    pub(super) fn lower_expansion(
        &mut self,
        expand_id: ExpandId,
        span: Span,
    ) -> LowerResult<RuleId> {
        let exp = *self.shared.pools.get_expansion(expand_id);
        let config = self.shared.pools.get_macro(exp.macro_id);
        let (name, def_module) = (config.name, config.def_module());
        self.bind_args_and(name.value, def_module, exp.args, span, |e| {
            e.lower_to_rule(exp.body)
        })
    }

    fn expand_for_rules(&mut self, for_id: ForId, body: NodeId) -> LowerResult<()> {
        self.expand_for(for_id, body, &mut |evaluator, leaf| {
            let rule_id = evaluator.lower_to_rule(leaf)?;
            evaluator.state.scratch.rule_scratch.push(rule_id);
            Ok(())
        })
    }

    fn expand_for_values(&mut self, for_id: ForId, body: NodeId) -> LowerResult<()> {
        self.expand_for(for_id, body, &mut |evaluator, leaf| {
            let value_id = evaluator.eval_expr(leaf)?;
            evaluator.state.scratch.val_scratch.push(value_id);
            Ok(())
        })
    }

    /// Expand a spread-position `for`, recursively flattening nested `for` bodies
    /// and passing each terminal body to `emit`.
    fn expand_for<Emit>(&mut self, for_id: ForId, body: NodeId, emit: &mut Emit) -> LowerResult<()>
    where
        Emit: FnMut(&mut Self, NodeId) -> LowerResult<()>,
    {
        let for_config = self.shared.pools.get_for(for_id);
        let iterable = for_config.iterable;
        let n_bindings = usize::from(for_config.bindings.len);
        // A loop's bindings are not in scope for its own iterable. Same-name references
        // there belong to an outer loop.
        let iter_vid = self.eval_expr(iterable)?;
        let iter_range = self.list_range(iter_vid);
        let nested_for = match *self.shared.arena.get(body) {
            Node::For { for_id, body } => Some((for_id, body)),
            _ => None,
        };

        stack_scope!(
            self.state.scratch.for_binding_values => base,
            self.state.scratch.for_binding_frames => _frames_base;
            {
                let values_base = u32::try_from(base).unwrap();
                self.state.scratch.for_binding_frames.push(ForFrame {
                    for_id,
                    values_base,
                });
                for item_index in iter_range.as_range() {
                    let item_id = self.state.ir.value_children[item_index];

                    // Rebuild the binding row before entering the body.
                    self.state.scratch.for_binding_values.truncate(base);
                    if n_bindings == 1 {
                        self.state.scratch.for_binding_values.push(item_id);
                    } else {
                        self.push_for_tuple_bindings(item_id);
                    }

                    if let Some((inner, inner_body)) = nested_for {
                        self.expand_for(inner, inner_body, emit)?;
                    } else {
                        emit(self, body)?;
                    }
                }
                Ok(())
            }
        )
    }

    fn push_for_tuple_bindings(&mut self, item_id: ValueId) {
        // Typecheck guarantees tuple destructuring shape and arity.
        expect_pat!(Value::Tuple(range), *self.get_val(item_id));
        let values = &self.state.ir.value_children[range.as_range()];
        self.state
            .scratch
            .for_binding_values
            .extend_from_slice(values);
    }
}
