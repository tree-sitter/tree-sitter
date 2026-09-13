use crate::{
    nativedsl::{
        ContainerKind, DataTy, InnerTy, ModuleTy, Note, NoteMessage, Ty, TypeError, TypeErrorKind,
        ast::{
            ForId, IdentKind, MacroId, MacroKind, ModuleContext, Node, NodeId, ObjectField, Param,
            PrecKind, SharedAst, Span, Spanned,
        },
        diagnostic::suggest_name,
        resolve::resolve_module_ref,
        typecheck::{
            Constraint, LetState, TypeEnv, TypeResult,
            types::{ScalarTy, TUPLE_MAX_ARITY, TUPLE_MIN_ARITY, TupleSig, TupleSigError},
        },
    },
    strpool::{StrId, StrPool},
};

/// Immutable state threaded through the typecheck walk.
#[derive(Clone, Copy)]
pub(super) struct Cx<'a> {
    pub shared: &'a SharedAst,
    pub ctx: &'a ModuleContext,
    pub source: &'a str,
    pub strs: &'a StrPool,
}

impl<'a> Cx<'a> {
    const fn error(self, kind: TypeErrorKind, span: Span) -> TypeError {
        TypeError::new(kind, self.ctx.document, span)
    }

    fn with_note(self, kind: TypeErrorKind, span: Span, note: Note) -> TypeError {
        TypeError::with_note(kind, self.ctx.document, span, note)
    }

    fn text(self, span: Span) -> &'a str {
        span.resolve(self.source)
    }
}

type CheckFn = fn(Cx<'_>, NodeId, &mut TypeEnv) -> TypeResult<()>;

pub(super) fn check_item(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    let Cx { shared, ctx, .. } = cx;
    match shared.arena.get(id) {
        Node::Grammar => {
            // INVARIANT: validate_grammar enforces `grammar_config.is_some()`
            let config = ctx.grammar_config.as_ref().unwrap();
            if let Some(inherits_id) = config.inherits {
                let ty = type_of(cx, inherits_id, env, Constraint::None)?;
                let base = ctx.inherit_module(&shared.arena);
                if !matches!(
                    ty,
                    Ty::Module(ModuleTy::Grammar(module))
                    if base.is_some_and(|(expected, _)| module == expected)
                ) {
                    let mut error = cx.error(
                        TypeErrorKind::InheritsMustReferenceBase,
                        shared.arena.span(inherits_id),
                    );
                    if let Some((_, span)) = base {
                        error.add_note(ctx.note(NoteMessage::BaseInheritedHere, span));
                    }
                    return Err(error);
                }
            }
            for id in [config.extras, config.externals].into_iter().flatten() {
                expect_list(cx, id, env, expect_rule, Ty::LIST_RULE)?;
            }
            for id in [config.inline, config.supertypes].into_iter().flatten() {
                expect_name_list(cx, id, env)?;
            }
            if let Some(id) = config.conflicts {
                expect_list(cx, id, env, expect_name_list, Ty::LIST_LIST_RULE)?;
            }
            if let Some(id) = config.precedences {
                expect_list(
                    cx,
                    id,
                    env,
                    |cx, id, env| expect_list(cx, id, env, expect_name_or_str, Ty::LIST_RULE),
                    Ty::LIST_LIST_RULE,
                )?;
            }
            if let Some(id) = config.word {
                expect_name_ref(cx, id, env)?;
            }
            if let Some(id) = config.start {
                expect_name_ref(cx, id, env)?;
            }
            if let Some(id) = config.reserved {
                expect_reserved(cx, id, env)?;
            }
            if let Some(id) = config.flags {
                expect_pat!(Node::Object(range), shared.arena.get(id));
                check_duplicate_names(
                    cx,
                    shared.pools.get_object(*range),
                    |f| f.name,
                    TypeErrorKind::DuplicateObjectKey,
                )?;
            }
            Ok(())
        }
        Node::Let { .. } => {
            _ = type_of_let(cx, id, env)?;
            Ok(())
        }
        Node::Macro(macro_id) => {
            let config = shared.pools.get_macro(*macro_id);
            let params = config.params;
            let kind = config.kind;
            let name = config.name;
            let body = config.body;
            check_duplicate_names(
                cx,
                shared.pools.param_slice(params),
                |p| p.name,
                TypeErrorKind::DuplicateParameter,
            )?;
            for p in shared.pools.param_slice(params) {
                reject_module_type(cx, p.ty, p.name.span)?;
            }
            match kind {
                MacroKind::Expression(return_ty) => {
                    reject_module_type(cx, return_ty, name.span)?;
                    type_of(cx, body, env, Constraint::Exact(return_ty))?;
                }
                MacroKind::RuleSet => check_rule_set_body(cx, body, env)?,
            }
            Ok(())
        }
        Node::Rule { body, .. } => expect_rule(cx, *body, env),
        &Node::ExpandedRule(expand_id) => {
            let exp = *shared.pools.get_expansion(expand_id);
            let params = shared.pools.get_macro(exp.macro_id).params;
            for (i, &arg) in shared.pools.child_slice(exp.args).iter().enumerate() {
                let ty = shared.pools.param_slice(params)[i].ty;
                type_of(cx, arg, env, Constraint::Exact(ty))?;
            }
            Ok(())
        }
        Node::Call { .. } => {
            type_of(cx, id, env, Constraint::None)?;
            Ok(())
        }
        Node::Forward { .. } => Ok(()),
        // Dispatcher only calls this for top-level item nodes.
        _ => unreachable!(),
    }
}

/// Type a `let` and any transitively referenced `let`s, memoizing each.
fn type_of_let(cx: Cx<'_>, let_id: NodeId, env: &mut TypeEnv) -> TypeResult<Ty> {
    let Cx {
        shared, ctx, strs, ..
    } = cx;
    if let Some(LetState::Resolved(ty)) = env.lets.get(&let_id).copied() {
        return Ok(ty);
    }
    env.lets.insert(let_id, LetState::InProgress);
    let mut stack = vec![let_id];
    while let Some(&cur) = stack.last() {
        let Node::Let { value, .. } = *shared.arena.get(cur) else {
            // Only let ids are pushed onto this stack.
            unreachable!()
        };
        if let Some((dep, reference)) = shared.first_unresolved_let_dep(
            value,
            |id| matches!(env.lets.get(&id), Some(LetState::Resolved(_))),
            &mut env.dep_walk,
        ) {
            // Resolved lets were filtered above, so an existing entry is in progress.
            if env.lets.insert(dep, LetState::InProgress).is_some() {
                let Node::Let { name, .. } = *shared.arena.get(dep) else {
                    // `first_unresolved_let_dep` only reports let dependencies.
                    unreachable!()
                };
                return Err(cx.with_note(
                    TypeErrorKind::CircularLet(strs.resolve(name).to_string()),
                    shared.arena.span(dep),
                    ctx.note(NoteMessage::SelfReferenceHere, shared.arena.span(reference)),
                ));
            }
            stack.push(dep);
            continue;
        }
        let constraint = ctx
            .let_types
            .get(&cur)
            .copied()
            .map_or(Constraint::None, Constraint::Exact);
        let inferred = type_of(cx, value, env, constraint)?;
        env.lets.insert(cur, LetState::Resolved(inferred));
        stack.pop();
    }

    match env.lets[&let_id] {
        LetState::Resolved(ty) => Ok(ty),
        LetState::InProgress => unreachable!(),
    }
}

fn let_object_fields(shared: &SharedAst, let_id: NodeId) -> Option<&[ObjectField]> {
    expect_pat!(Node::Let { value, .. }, *shared.arena.get(let_id));
    match *shared.arena.get(value) {
        Node::Object(range) => Some(shared.pools.get_object(range)),
        _ => None,
    }
}

/// Typecheck rule decls inside a rule-set macro body at definition time.
fn check_rule_set_body(cx: Cx<'_>, body_id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    let Cx { shared, .. } = cx;
    let Node::RuleSet(range) = shared.arena.get(body_id) else {
        unreachable!()
    };
    for &decl_id in shared.pools.child_slice(*range) {
        match shared.arena.get(decl_id) {
            Node::Rule { body, .. } => expect_rule(cx, *body, env)?,
            Node::ComputedRule {
                name_expr, body, ..
            } => {
                type_of(cx, *name_expr, env, Constraint::Exact(Ty::STR))?;
                expect_rule(cx, *body, env)?;
            }
            _ => unreachable!(),
        }
    }
    Ok(())
}

/// Check a list config field.
fn expect_list(
    cx: Cx<'_>,
    id: NodeId,
    env: &mut TypeEnv,
    check_elem: CheckFn,
    expected: Ty,
) -> TypeResult<()> {
    let Cx { shared, .. } = cx;
    if let Node::List(range) = shared.arena.get(id) {
        let leaf =
            |cx: Cx<'_>, id: NodeId, env: &mut TypeEnv| check_elem(cx, id, env).map(|()| Ty::RULE);
        for &child in shared.pools.child_slice(*range) {
            check_spread_item(cx, child, env, leaf)?;
        }
        return Ok(());
    }
    type_of(cx, id, env, Constraint::Exact(expected))?;
    Ok(())
}

fn expect_name_list(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    expect_list(cx, id, env, expect_name_ref, Ty::LIST_RULE)
}

fn expect_name_ref(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    let Cx {
        shared, ctx, strs, ..
    } = cx;
    match shared.arena.get(id) {
        Node::Ident(IdentKind::Rule(_)) => Ok(()),
        Node::Ident(IdentKind::Var(_))
        | Node::FieldAccess { .. }
        | Node::GrammarConfig { .. }
        | Node::MacroParam { .. }
        | Node::ForBinding { .. } => {
            type_of(cx, id, env, Constraint::Strict(Ty::RULE))?;
            Ok(())
        }
        // A qualified ref names a rule but is not a name here; suggest the
        // bare name, which is in scope.
        Node::ModuleRule { member, .. } => {
            let span = shared.arena.span(id);
            Err(cx.with_note(
                TypeErrorKind::ExpectedRuleName,
                span,
                ctx.note(
                    NoteMessage::UseBareName(strs.resolve(*member).to_string()),
                    span,
                ),
            ))
        }
        _ => Err(cx.error(TypeErrorKind::ExpectedRuleName, shared.arena.span(id))),
    }
}

fn expect_name_or_str(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    let Cx { shared, .. } = cx;
    if matches!(shared.arena.get(id), Node::StringLit(_)) {
        return Ok(());
    }
    expect_name_ref(cx, id, env)
}

/// Check the `reserved` config field.
fn expect_reserved(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    let Cx { shared, .. } = cx;
    let Node::Object(range) = shared.arena.get(id) else {
        return Err(cx.error(TypeErrorKind::ReservedMustBeLiteral, shared.arena.span(id)));
    };
    let fields = shared.pools.get_object(*range);
    check_duplicate_names(cx, fields, |f| f.name, TypeErrorKind::DuplicateObjectKey)?;
    for &ObjectField { value: val_id, .. } in fields {
        expect_list(cx, val_id, env, expect_rule, Ty::LIST_RULE)?;
    }
    Ok(())
}

fn expect_rule(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv) -> TypeResult<()> {
    type_of(cx, id, env, Constraint::Exact(Ty::RULE))?;
    Ok(())
}

/// What a position asks of the expression being typed: the constraint to
/// enforce, and whether the resulting type is pushed onto `results` for a
/// parent [`Work::Combine`] to fold. Every `Work` variant carries one, and a
/// spread propagates its own demand down to the leaves it expands into.
#[derive(Clone, Copy)]
pub(super) struct Demand {
    expected: Constraint,
    emit: bool,
}

impl Demand {
    /// Check against `expected` and discard the resulting type.
    const fn checking(expected: Constraint) -> Self {
        Self {
            expected,
            emit: false,
        }
    }

    /// Check against `expected` and emit the type for a parent to fold.
    const fn emitting(expected: Constraint) -> Self {
        Self {
            expected,
            emit: true,
        }
    }
}

#[derive(Clone, Copy)]
pub(super) enum Work {
    /// Type `id` under `demand`.
    Eval { id: NodeId, demand: Demand },
    /// Type a spread-position item, propagating `demand` to its leaves.
    Spread { id: NodeId, demand: Demand },
    /// Continue a `for` after its iterable type has been emitted. Match that type
    /// against the bindings, then schedule the body as another spread.
    ForBody { node: NodeId, demand: Demand },
    /// Fold a combining node's emitted child types.
    Combine { id: NodeId, demand: Demand },
}

const _: () = assert!(std::mem::size_of::<Work>() == 16);

/// Type a node.
fn type_of(cx: Cx<'_>, id: NodeId, env: &mut TypeEnv, expected: Constraint) -> TypeResult<Ty> {
    let work_base = env.work.len();
    let results_base = env.results.len();
    push_eval(&mut env.work, id, Demand::emitting(expected));
    match drive(cx, env, work_base) {
        Ok(()) => Ok(pop_result(&mut env.results)),
        Err(e) => {
            env.work.truncate(work_base);
            env.results.truncate(results_base);
            Err(e)
        }
    }
}

/// Run the iterative traversal until the work stack returns to `work_base`.
fn drive(cx: Cx<'_>, env: &mut TypeEnv, work_base: usize) -> TypeResult<()> {
    let Cx { shared, .. } = cx;
    while env.work.len() > work_base {
        match env.work.pop().unwrap() {
            Work::Eval { mut id, mut demand } => {
                while let Some((next_id, next_demand)) = eval(cx, env, id, demand)? {
                    id = next_id;
                    demand = next_demand;
                }
            }
            Work::Spread { id, demand } => {
                schedule_for(cx, id, demand, &mut env.work)?;
            }
            Work::ForBody { node, demand } => {
                let iter_ty = pop_result(&mut env.results);
                expect_pat!(Node::For { for_id, body }, *shared.arena.get(node));
                match_for_elem(cx, shared, for_id, iter_ty)?;
                push_spread_item(shared, body, demand, &mut env.work);
            }
            Work::Combine { id, demand } => {
                combine(cx, env, id, demand)?;
            }
        }
    }
    Ok(())
}

type Descent = Option<(NodeId, Demand)>;

/// Handle a [`Work::Eval`].
fn eval(cx: Cx<'_>, env: &mut TypeEnv, id: NodeId, demand: Demand) -> TypeResult<Descent> {
    let Cx { shared, strs, .. } = cx;
    let Demand { expected, emit } = demand;
    let span = shared.arena.span(id);
    Ok(match *shared.arena.get(id) {
        Node::IntLit(_) => {
            enforce_leaf(cx, &mut env.results, demand, Ty::INT, span)?;
            None
        }
        Node::StringLit(_) => {
            enforce_leaf(cx, &mut env.results, demand, Ty::STR, span)?;
            None
        }
        Node::Ident(IdentKind::Rule(_)) | Node::Blank | Node::Eof | Node::ModuleRule { .. } => {
            enforce_leaf(cx, &mut env.results, demand, Ty::RULE, span)?;
            None
        }
        Node::Import { module, .. } => {
            let idx = module.unwrap();
            enforce_leaf(
                cx,
                &mut env.results,
                demand,
                Ty::Module(ModuleTy::Library(idx)),
                span,
            )?;
            None
        }
        Node::Inherit { module, .. } => {
            let idx = module.unwrap();
            enforce_leaf(
                cx,
                &mut env.results,
                demand,
                Ty::Module(ModuleTy::Grammar(idx)),
                span,
            )?;
            None
        }
        Node::MacroParam { ty, .. } | Node::ForBinding { ty, .. } => {
            enforce_leaf(cx, &mut env.results, demand, ty, span)?;
            None
        }
        Node::Ident(IdentKind::Macro(_)) => {
            return Err(cx.error(
                TypeErrorKind::MacroUsedAsValue(cx.text(span).to_string()),
                span,
            ));
        }
        // Type the referenced let on demand (it may be defined later or chain
        // through other lets). type_of_let resolves chains iteratively and
        // reports any self-reference cycle.
        Node::Ident(IdentKind::Var(let_id)) => {
            let ty = type_of_let(cx, let_id, env)?;
            enforce_leaf(cx, &mut env.results, demand, ty, span)?;
            None
        }
        Node::SymRef { expr } => {
            enforce_leaf(cx, &mut env.results, demand, Ty::RULE, span)?;
            Some((expr, Demand::checking(Constraint::Exact(Ty::STR))))
        }
        Node::Neg(inner) => {
            enforce_leaf(cx, &mut env.results, demand, Ty::INT, span)?;
            Some((inner, Demand::checking(Constraint::Exact(Ty::INT))))
        }
        Node::Repeat { inner, .. }
        | Node::Token { inner, .. }
        | Node::Field { content: inner, .. }
        | Node::Reserved { content: inner, .. } => {
            enforce_leaf(cx, &mut env.results, demand, Ty::RULE, span)?;
            Some((inner, Demand::checking(Constraint::Exact(Ty::RULE))))
        }
        Node::BinOp { lhs, rhs, .. } => {
            enforce_leaf(cx, &mut env.results, demand, Ty::INT, span)?;
            push_eval(
                &mut env.work,
                rhs,
                Demand::checking(Constraint::Exact(Ty::INT)),
            );
            Some((lhs, Demand::checking(Constraint::Exact(Ty::INT))))
        }
        Node::Prec {
            kind,
            value,
            content,
        } => {
            let value_expected = if kind == PrecKind::Dynamic {
                Constraint::Exact(Ty::INT)
            } else {
                Constraint::IntOrStr
            };
            enforce_leaf(cx, &mut env.results, demand, Ty::RULE, span)?;
            push_eval(
                &mut env.work,
                content,
                Demand::checking(Constraint::Exact(Ty::RULE)),
            );
            Some((value, Demand::checking(value_expected)))
        }
        Node::DynRegex { pattern, flags } => {
            enforce_leaf(cx, &mut env.results, demand, Ty::RULE, span)?;
            if let Some(fid) = flags {
                push_eval(
                    &mut env.work,
                    fid,
                    Demand::checking(Constraint::Exact(Ty::STR)),
                );
            }
            Some((pattern, Demand::checking(Constraint::Exact(Ty::STR))))
        }
        Node::Concat(range) => {
            enforce_leaf(cx, &mut env.results, demand, Ty::STR, span)?;
            descend_eval(
                shared.pools.child_slice(range),
                Constraint::Exact(Ty::STR),
                &mut env.work,
            )
        }
        Node::SeqOrChoice { range, .. } => {
            enforce_leaf(cx, &mut env.results, demand, Ty::RULE, span)?;
            for &member in shared.pools.child_slice(range).iter().rev() {
                push_spread_item(
                    shared,
                    member,
                    Demand::checking(Constraint::RuleLike),
                    &mut env.work,
                );
            }
            None
        }
        Node::Append { left, right } => {
            let (left_evaled, right_evaled) = append_operands(shared, left, right, expected);
            push_combine(&mut env.work, id, demand);
            if right_evaled {
                push_eval(&mut env.work, right, Demand::emitting(expected));
            }
            if left_evaled {
                push_eval(&mut env.work, left, Demand::emitting(expected));
            }
            None
        }
        Node::FieldAccess { obj, .. } => {
            push_combine(&mut env.work, id, demand);
            push_eval(&mut env.work, obj, Demand::emitting(Constraint::AnyObject));
            None
        }
        Node::QualifiedAccess { obj, .. } => {
            push_combine(&mut env.work, id, demand);
            push_eval(&mut env.work, obj, Demand::emitting(Constraint::None));
            None
        }
        Node::GrammarConfig { module, .. } => {
            push_combine(&mut env.work, id, demand);
            // No demand on the module expr: Exact(ANY_GRAMMAR) here would reject
            // imports with a generic mismatch before the combine arm can issue
            // GrammarConfigRequiresInherit with its inherit() suggestion. The arm
            // classifies all three cases (grammar, library, non-module) itself.
            push_eval(&mut env.work, module, Demand::emitting(Constraint::None));
            None
        }
        Node::Alias { content, target } => {
            push_combine(&mut env.work, id, demand);
            push_eval(&mut env.work, target, Demand::emitting(Constraint::None));
            push_eval(
                &mut env.work,
                content,
                Demand::checking(Constraint::Exact(Ty::RULE)),
            );
            None
        }
        Node::Object(range) => {
            let fields = shared.pools.get_object(range);
            if fields.is_empty() {
                let ty = empty_container_result(cx, expected, ContainerKind::Object, span)?;
                if emit {
                    env.results.push(ty);
                }
                return Ok(None);
            }
            check_duplicate_names(cx, fields, |f| f.name, TypeErrorKind::DuplicateObjectKey)?;
            let value_expected = expected.object_value();
            push_combine(&mut env.work, id, demand);
            for f in fields.iter().rev() {
                push_eval(&mut env.work, f.value, Demand::emitting(value_expected));
            }
            None
        }
        Node::List(range) => {
            let items = shared.pools.child_slice(range);
            if items.is_empty() {
                let ty = empty_container_result(cx, expected, ContainerKind::List, span)?;
                if emit {
                    env.results.push(ty);
                }
                return Ok(None);
            }
            let elem_expected = expected.elem();
            push_combine(&mut env.work, id, demand);
            for &item in items.iter().rev() {
                push_spread_item(shared, item, Demand::emitting(elem_expected), &mut env.work);
            }
            None
        }
        Node::Tuple(range) => {
            let items = shared.pools.child_slice(range);
            let n = items.len();
            if !(TUPLE_MIN_ARITY..=TUPLE_MAX_ARITY).contains(&n) {
                return Err(cx.error(TypeErrorKind::TupleArityInvalid(n), span));
            }
            push_combine(&mut env.work, id, demand);
            for &item in items.iter().rev() {
                push_eval(&mut env.work, item, Demand::emitting(Constraint::None));
            }
            None
        }
        Node::Call { name, args } => {
            // Resolve leaves a qualified name intact only when its receiver does
            // not resolve to a module. Type the receiver first so that the error
            // identifies _that_ cause rather than the callee name.
            if let Node::QualifiedAccess {
                obj,
                member,
                member_offset,
            } = *shared.arena.get(name)
            {
                let obj_ty = type_of(cx, obj, env, Constraint::None)?;
                if !matches!(obj_ty, Ty::Module(_)) {
                    return Err(cx.error(
                        TypeErrorKind::MemberAccessRequiresModule(obj_ty),
                        shared.arena.span(obj),
                    ));
                }
                let member = strs.resolve(member);
                return Err(cx.error(
                    TypeErrorKind::ImportMacroNotFound(member.to_string()),
                    Span::new(member_offset, member_offset + member.len() as u32),
                ));
            }
            let macro_id = resolve_macro_name(cx, name, span)?;
            let args = shared.pools.child_slice(args);
            enqueue_macro_call(cx, macro_id, id, args, demand, &mut env.work)?;
            None
        }
        Node::For { .. } => {
            push_combine(&mut env.work, id, demand);
            schedule_for(
                cx,
                id,
                Demand::checking(Constraint::Exact(Ty::RULE)),
                &mut env.work,
            )?;
            None
        }
        // Non-expression nodes never reach `type_of`.
        _ => unreachable!(),
    })
}

fn descend_eval(children: &[NodeId], c: Constraint, work: &mut Vec<Work>) -> Descent {
    let (&first, rest) = children.split_first()?;
    for &child in rest.iter().rev() {
        push_eval(work, child, Demand::checking(c));
    }
    Some((first, Demand::checking(c)))
}

fn append_operands(
    shared: &SharedAst,
    left: NodeId,
    right: NodeId,
    expected: Constraint,
) -> (bool, bool) {
    let is_list_anno = matches!(expected, Constraint::Exact(t) if t.is_list());
    (
        !is_empty_list(shared, left) || is_list_anno,
        !is_empty_list(shared, right) || is_list_anno,
    )
}

fn is_empty_list(shared: &SharedAst, id: NodeId) -> bool {
    matches!(shared.arena.get(id), Node::List(r) if shared.pools.child_slice(*r).is_empty())
}

/// Handle a [`Work::Combine`].
fn combine(cx: Cx<'_>, env: &mut TypeEnv, id: NodeId, demand: Demand) -> TypeResult<()> {
    let Cx {
        shared, ctx, strs, ..
    } = cx;
    let Demand { expected, emit } = demand;
    let span = shared.arena.span(id);
    let ty = match *shared.arena.get(id) {
        Node::List(range) => {
            let items = shared.pools.child_slice(range);
            let base = env.results.len() - items.len();
            let mut widest = env.results[base];
            for (k, &item) in items.iter().enumerate().skip(1) {
                let got = env.results[base + k];
                widest = widest.widen(got).ok_or_else(|| {
                    cx.error(
                        TypeErrorKind::ListElementTypeMismatch { first: widest, got },
                        shared.arena.span(item),
                    )
                })?;
            }
            env.results.truncate(base);
            widest
                .to_list()
                .ok_or_else(|| cx.error(TypeErrorKind::InvalidListElement(widest), span))?
        }
        Node::Object(range) => {
            let fields = shared.pools.get_object(range);
            let base = env.results.len() - fields.len();
            let mut widest = env.results[base];
            for (k, field) in fields.iter().enumerate().skip(1) {
                let got = env.results[base + k];
                widest = widest.widen(got).ok_or_else(|| {
                    cx.error(
                        TypeErrorKind::ObjectFieldTypeMismatch { first: widest, got },
                        shared.arena.span(field.value),
                    )
                })?;
            }
            env.results.truncate(base);
            let invalid = || {
                cx.error(
                    TypeErrorKind::InvalidObjectValue(widest),
                    shared.arena.span(fields[0].value),
                )
            };
            let Ty::Data(d) = widest else {
                return Err(invalid());
            };
            let inner = InnerTy::try_from(d).map_err(|()| invalid())?;
            Ty::Data(DataTy::Object(inner))
        }
        Node::Tuple(range) => {
            let items = shared.pools.child_slice(range);
            let n = items.len();
            let base = env.results.len() - n;
            let mut scalars = [ScalarTy::Rule; TUPLE_MAX_ARITY];
            for (k, &item) in items.iter().enumerate() {
                let got = env.results[base + k];
                let Ty::Data(DataTy::Scalar(s)) = got else {
                    return Err(cx.error(
                        TypeErrorKind::TupleElementNotScalar(got),
                        shared.arena.span(item),
                    ));
                };
                scalars[k] = s;
            }
            env.results.truncate(base);
            let sig = TupleSig::new(&scalars[..n]).map_err(|TupleSigError(bad)| {
                cx.error(TypeErrorKind::TupleArityInvalid(bad), span)
            })?;
            Ty::Data(DataTy::Tuple(sig))
        }
        Node::Append { left, right } => {
            let (left_evaled, right_evaled) = append_operands(shared, left, right, expected);
            let r_ty = right_evaled.then(|| pop_result(&mut env.results));
            let l_ty = left_evaled.then(|| pop_result(&mut env.results));
            match (l_ty, r_ty) {
                (Some(l), Some(r)) => {
                    if !l.is_list() {
                        return Err(cx.error(
                            TypeErrorKind::AppendRequiresList(l),
                            shared.arena.span(left),
                        ));
                    }
                    if !r.is_list() {
                        return Err(mismatch(cx, l, r, shared.arena.span(right)));
                    }
                    l.widen(r)
                        .ok_or_else(|| mismatch(cx, l, r, shared.arena.span(right)))?
                }
                (Some(t), None) | (None, Some(t)) => {
                    if !t.is_list() {
                        return Err(cx.error(TypeErrorKind::AppendRequiresList(t), span));
                    }
                    t
                }
                (None, None) => {
                    return Err(cx.error(
                        TypeErrorKind::EmptyContainerNeedsAnnotation(ContainerKind::List),
                        span,
                    ));
                }
            }
        }
        Node::Call { name, .. } => macro_call_result(cx, name, span)?,
        Node::GrammarConfig { module, field } => {
            let module_ty = pop_result(&mut env.results);
            match module_ty {
                Ty::Module(ModuleTy::Grammar(_) | ModuleTy::AnyGrammar) => {}
                Ty::Module(ModuleTy::Library(_) | ModuleTy::AnyLibrary) => {
                    let err_kind = TypeErrorKind::GrammarConfigRequiresInherit;
                    let arg_span = shared.arena.span(module);
                    if let Some(ref_id) = resolve_module_ref(&shared.arena, module)
                        && let Node::Import { path, .. } = shared.arena.get(ref_id)
                    {
                        let path_text = cx.text(*path);
                        return Err(cx.with_note(
                            err_kind,
                            arg_span,
                            ctx.note(
                                NoteMessage::DidYouMean(format!("inherit(\"{path_text}\")")),
                                shared.arena.span(ref_id),
                            ),
                        ));
                    }
                    return Err(cx.error(err_kind, arg_span));
                }
                got => {
                    return Err(mismatch(
                        cx,
                        Ty::ANY_GRAMMAR,
                        got,
                        shared.arena.span(module),
                    ));
                }
            }
            use crate::nativedsl::ast::ConfigField as C;
            match field {
                C::Language => Ty::STR,
                C::Extras | C::Externals | C::Inline | C::Supertypes => Ty::LIST_RULE,
                C::Conflicts | C::Precedences => Ty::LIST_LIST_RULE,
                C::Word | C::Start => Ty::RULE,
                C::Reserved => Ty::OBJ_LIST_RULE,
                C::Inherits | C::Flags => unreachable!(),
            }
        }
        Node::FieldAccess { obj, field } => {
            let obj_ty = pop_result(&mut env.results);
            let inner = obj_ty.object_inner().unwrap();
            // Field names are checkable only when the object's shape is known statically:
            // a literal, or a variable bound to a literal
            let known_fields = match *shared.arena.get(obj) {
                Node::Ident(IdentKind::Var(let_id)) => let_object_fields(shared, let_id),
                Node::Object(range) => Some(shared.pools.get_object(range)),
                _ => None,
            };
            if let Some(fields) = known_fields
                && !fields.iter().any(|f| f.name.value == field)
            {
                let available = fields
                    .iter()
                    .map(|f| strs.resolve(f.name.value).to_string())
                    .collect();
                return Err(cx.error(
                    TypeErrorKind::FieldNotFound {
                        field: strs.resolve(field).to_string(),
                        available,
                    },
                    span,
                ));
            }
            Ty::from(inner)
        }
        Node::Alias { target, .. } => {
            let target_ty = pop_result(&mut env.results);
            if let Node::ModuleRule { member, .. } = shared.arena.get(target) {
                let target_span = shared.arena.span(target);
                return Err(cx.with_note(
                    TypeErrorKind::InvalidAliasTarget(target_ty),
                    target_span,
                    ctx.note(
                        NoteMessage::UseBareName(strs.resolve(*member).to_string()),
                        target_span,
                    ),
                ));
            }
            let is_valid = matches!(
                shared.arena.get(target),
                Node::Ident(IdentKind::Rule(_) | IdentKind::Var(_))
                    | Node::MacroParam { .. }
                    | Node::ForBinding { .. }
                    | Node::QualifiedAccess { .. }
                    | Node::FieldAccess { .. }
                    | Node::GrammarConfig { .. }
            ) || target_ty == Ty::STR;
            if !target_ty.is_rule_like() || !is_valid {
                return Err(cx.error(
                    TypeErrorKind::InvalidAliasTarget(target_ty),
                    shared.arena.span(target),
                ));
            }
            Ty::RULE
        }
        Node::QualifiedAccess { .. } => {
            let obj_ty = pop_result(&mut env.results);
            return Err(cx.error(TypeErrorKind::MemberAccessRequiresModule(obj_ty), span));
        }
        Node::For { .. } => return Err(cx.error(TypeErrorKind::BoundForLoop, span)),
        _ => unreachable!(),
    };
    enforce(cx, expected, ty, span)?;
    if emit {
        env.results.push(ty);
    }
    Ok(())
}

fn macro_call_result(cx: Cx<'_>, name: NodeId, span: Span) -> TypeResult<Ty> {
    let Cx { shared, .. } = cx;
    let Node::Ident(IdentKind::Macro(macro_id)) = *shared.arena.get(name) else {
        // Call names are resolved before the combine step is queued.
        unreachable!()
    };
    match shared.pools.get_macro(macro_id).kind {
        MacroKind::Expression(return_ty) => Ok(return_ty),
        MacroKind::RuleSet => Err(cx.error(
            TypeErrorKind::RuleSetMacroInExpressionContext(
                cx.text(shared.arena.span(name)).to_string(),
            ),
            span,
        )),
    }
}

fn push_spread_item(shared: &SharedAst, id: NodeId, demand: Demand, work: &mut Vec<Work>) {
    if matches!(shared.arena.get(id), Node::For { .. }) {
        work.push(Work::Spread { id, demand });
    } else {
        push_eval(work, id, demand);
    }
}

/// Schedule a `for` iterable followed by the continuation that checks its element
/// type and schedules the body.
fn schedule_for(cx: Cx<'_>, node: NodeId, demand: Demand, work: &mut Vec<Work>) -> TypeResult<()> {
    let Cx { shared, .. } = cx;
    expect_pat!(Node::For { for_id, body }, *shared.arena.get(node));
    let iterable = validate_for_header(cx, for_id, body)?;
    if is_empty_list(shared, iterable) {
        push_spread_item(shared, body, demand, work);
        return Ok(());
    }
    work.push(Work::ForBody { node, demand });
    push_eval(work, iterable, Demand::emitting(Constraint::None));
    Ok(())
}

fn resolve_macro_name(cx: Cx<'_>, name: NodeId, span: Span) -> TypeResult<MacroId> {
    let Cx {
        shared, ctx, strs, ..
    } = cx;
    if let Node::Ident(IdentKind::Macro(macro_id)) = *shared.arena.get(name) {
        return Ok(macro_id);
    }
    let macro_name = cx.text(shared.arena.span(name));
    let kind = TypeErrorKind::UndefinedMacro(macro_name.to_string());
    let macros = ctx.root_items.iter().filter_map(|&id| {
        if let Node::Macro(mid) = shared.arena.get(id) {
            Some(strs.resolve(shared.pools.get_macro(*mid).name.value))
        } else {
            None
        }
    });
    let mut err = cx.error(kind, span);
    if let Some(suggestion) = suggest_name(macro_name, macros) {
        err.add_note(ctx.note(NoteMessage::DidYouMean(suggestion.to_string()), span));
    }
    Err(err)
}

fn enqueue_macro_call(
    cx: Cx<'_>,
    macro_id: MacroId,
    node: NodeId,
    args: &[NodeId],
    demand: Demand,
    work: &mut Vec<Work>,
) -> TypeResult<()> {
    let Cx { shared, strs, .. } = cx;
    let config = shared.pools.get_macro(macro_id);
    let params = config.params;
    if args.len() != params.len as usize {
        return Err(cx.error(
            TypeErrorKind::ArgCountMismatch {
                macro_name: strs.resolve(config.name.value).to_string(),
                expected: params.len as usize,
                got: args.len(),
            },
            shared.arena.span(node),
        ));
    }
    push_combine(work, node, demand);
    // Push args reversed so they execute left-to-right (matching the recursive
    // order: the first ill-typed argument is reported first).
    for (i, &arg) in args.iter().enumerate().rev() {
        let ty = shared.pools.param_slice(params)[i].ty;
        push_eval(work, arg, Demand::checking(Constraint::Exact(ty)));
    }
    Ok(())
}

fn enforce(cx: Cx<'_>, expected: Constraint, ty: Ty, span: Span) -> TypeResult<()> {
    if expected == Constraint::None {
        return Ok(());
    }
    if !expected.satisfies(ty) {
        let kind = match expected {
            Constraint::Exact(t) | Constraint::Strict(t) => TypeErrorKind::TypeMismatch {
                expected: t,
                got: ty,
            },
            _ => TypeErrorKind::ConstraintMismatch { expected, got: ty },
        };
        return Err(cx.error(kind, span));
    }
    Ok(())
}

fn enforce_leaf(
    cx: Cx<'_>,
    results: &mut Vec<Ty>,
    demand: Demand,
    ty: Ty,
    span: Span,
) -> TypeResult<()> {
    enforce(cx, demand.expected, ty, span)?;
    if demand.emit {
        results.push(ty);
    }
    Ok(())
}

#[inline]
fn pop_result(results: &mut Vec<Ty>) -> Ty {
    // SAFETY: combine steps are queued behind their emitting children, so the
    // result is present.
    results.pop().unwrap()
}

fn push_eval(work: &mut Vec<Work>, id: NodeId, demand: Demand) {
    work.push(Work::Eval { id, demand });
}

fn push_combine(work: &mut Vec<Work>, id: NodeId, demand: Demand) {
    work.push(Work::Combine { id, demand });
}

fn check_spread_item<Leaf>(
    cx: Cx<'_>,
    item: NodeId,
    env: &mut TypeEnv,
    leaf: Leaf,
) -> TypeResult<Ty>
where
    Leaf: Fn(Cx<'_>, NodeId, &mut TypeEnv) -> TypeResult<Ty>,
{
    let Cx { shared, .. } = cx;
    let mut curr_item = item;
    loop {
        let Node::For { for_id, body } = *shared.arena.get(curr_item) else {
            return leaf(cx, curr_item, env);
        };
        let iterable = validate_for_header(cx, for_id, body)?;
        if !is_empty_list(shared, iterable) {
            let iter_ty = type_of(cx, iterable, env, Constraint::None)?;
            match_for_elem(cx, shared, for_id, iter_ty)?;
        }
        curr_item = body;
    }
}

/// Validate the binding declarations in a `for` header and return the iterable
/// expression node for subsequent type checking.
fn validate_for_header(cx: Cx<'_>, for_id: ForId, body: NodeId) -> TypeResult<NodeId> {
    let Cx { shared, .. } = cx;
    let config = shared.pools.get_for(for_id);
    let bindings = shared.pools.param_slice(config.bindings);
    let body_span = shared.arena.span(body);

    if bindings.is_empty() {
        return Err(cx.error(TypeErrorKind::EmptyForBindings, body_span));
    }
    check_duplicate_names(cx, bindings, |p| p.name, TypeErrorKind::DuplicateBinding)?;
    if bindings.len() >= 2 {
        for param in bindings {
            if !matches!(param.ty, Ty::Data(DataTy::Scalar(_))) {
                return Err(cx.error(
                    TypeErrorKind::TupleElementNotScalar(param.ty),
                    param.name.span,
                ));
            }
        }
    }
    Ok(config.iterable)
}

fn match_for_elem(cx: Cx<'_>, shared: &SharedAst, for_id: ForId, iter_ty: Ty) -> TypeResult<()> {
    let config = shared.pools.get_for(for_id);
    let bindings = shared.pools.param_slice(config.bindings);
    let iterable = config.iterable;
    let Some(elem_ty) = iter_ty.list_elem() else {
        return Err(cx.error(
            TypeErrorKind::ForRequiresList(iter_ty),
            shared.arena.span(iterable),
        ));
    };
    if bindings.len() == 1 {
        let Param { name, ty: declared } = bindings[0];
        if !elem_ty.is_compatible(declared) {
            return Err(mismatch(cx, declared, elem_ty, name.span));
        }
    } else {
        let Ty::Data(DataTy::Tuple(sig)) = elem_ty else {
            return Err(cx.error(
                TypeErrorKind::ForRequiresTuples,
                shared.arena.span(iterable),
            ));
        };
        if sig.arity() != bindings.len() {
            return Err(cx.error(
                TypeErrorKind::ForBindingCountMismatch {
                    bindings: bindings.len(),
                    tuple_elements: sig.arity(),
                },
                shared.arena.span(iterable),
            ));
        }
        for (i, param) in bindings.iter().enumerate() {
            let elem_scalar = Ty::Data(DataTy::Scalar(sig.elem(i)));
            if !elem_scalar.is_compatible(param.ty) {
                return Err(mismatch(cx, param.ty, elem_scalar, param.name.span));
            }
        }
    }
    Ok(())
}

fn empty_container_result(
    cx: Cx<'_>,
    expected: Constraint,
    kind: ContainerKind,
    span: Span,
) -> TypeResult<Ty> {
    let matches_kind = |ty: Ty| match kind {
        ContainerKind::List => ty.is_list(),
        ContainerKind::Object => ty.is_object(),
    };
    match expected {
        Constraint::Exact(ty) if matches_kind(ty) => Ok(ty),
        Constraint::Exact(declared) => Err(cx.error(
            TypeErrorKind::EmptyContainerAnnotationMismatch { declared, kind },
            span,
        )),
        _ => Err(cx.error(TypeErrorKind::EmptyContainerNeedsAnnotation(kind), span)),
    }
}

const fn mismatch(cx: Cx<'_>, expected: Ty, got: Ty, span: Span) -> TypeError {
    cx.error(TypeErrorKind::TypeMismatch { expected, got }, span)
}

const fn reject_module_type(cx: Cx<'_>, ty: Ty, span: Span) -> TypeResult<()> {
    if matches!(ty, Ty::Module(_)) {
        return Err(cx.error(TypeErrorKind::ModuleTypeNotAllowed, span));
    }
    Ok(())
}

fn check_duplicate_names<T>(
    cx: Cx<'_>,
    items: &[T],
    name_of: impl Fn(&T) -> Spanned<StrId>,
    make_kind: impl Fn(String) -> TypeErrorKind,
) -> TypeResult<()> {
    let Cx { ctx, strs, .. } = cx;
    for i in 1..items.len() {
        let curr = name_of(&items[i]);
        for prev in &items[..i] {
            let prev_name = name_of(prev);
            if prev_name.value == curr.value {
                return Err(cx.with_note(
                    make_kind(strs.resolve(curr.value).to_string()),
                    curr.span,
                    ctx.note(NoteMessage::FirstDefinedHere, prev_name.span),
                ));
            }
        }
    }
    Ok(())
}
