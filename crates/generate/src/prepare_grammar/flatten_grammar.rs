use rustc_hash::FxHashMap;
use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::{
    grammars::{
        InputGrammar, Production, ProductionStep, ProductionStore, SyntaxGrammar, SyntaxVariable,
    },
    prepare_grammar::extract_tokens::ExtractedGrammarMeta,
    rules::{
        Alias, Associativity, Precedence, Rule, RuleId, RulePool, Symbol, SymbolType, TokenSet,
    },
    strpool::{StrId, StrPool},
};

pub type FlattenGrammarResult<T> = Result<T, FlattenGrammarError>;

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub enum FlattenGrammarError {
    #[error("No such reserved word set: {0}")]
    NoReservedWordSet(String),
    #[error("Reserved word set count {0} exceeds the maximum of {max}", max = u16::MAX)]
    TooManyReservedWordSets(usize),
    #[error(
        "The rule `{0}` matches the empty string.

Tree-sitter does not support syntactic rules that match the empty string
unless they are used only as the grammar's start rule.
"
    )]
    EmptyString(String),
    #[error("Rule `{0}` cannot be inlined because it contains a reference to itself")]
    RecursiveInline(String),
}

#[derive(Clone, Copy, Default)]
struct FlattenCtx {
    prec: Precedence,
    assoc: Option<Associativity>,
    alias: Option<Alias>,
    field: Option<StrId>,
    reserved: u16,
}

/// Selects one branch at each choice encountered during a root-to-leaf walk. After
/// a production is emitted, `advance` increments this path like a mixed-radix counter.
/// Later decisions are discarded because choosing an earlier branch can expose a
/// different set of nested choices.
#[derive(Default)]
struct ChoiceCursor {
    decisions: Vec<u32>,
    arities: Vec<u32>,
    depth: usize,
}

impl ChoiceCursor {
    /// Begin a new walk for a new variable.
    fn reset(&mut self) {
        self.decisions.clear();
        self.arities.clear();
        self.depth = 0;
    }

    /// Begin a new walk for the same variable as a previous walk
    fn begin_path(&mut self) {
        self.arities.clear();
        self.depth = 0;
    }

    /// Called at each choice. Selects which path to take, and records the decision.
    fn select(&mut self, len: u32) -> u32 {
        debug_assert!(len > 0);
        let selected = self.decisions.get(self.depth).copied().unwrap_or(0);
        debug_assert!(selected < len);
        self.arities.push(len);
        self.depth += 1;
        selected
    }

    /// Find the latest path that we can advance and discard every decision after it.
    /// Returns whether a new path could be found.
    fn advance(&mut self) -> bool {
        for depth in (0..self.arities.len()).rev() {
            let selected = self.decisions.get(depth).copied().unwrap_or(0);
            if selected + 1 < self.arities[depth] {
                self.decisions.resize(depth + 1, 0);
                self.decisions[depth] = selected + 1;
                return true;
            }
        }
        false
    }
}

/// Reusable scratch for enumerating and flattening one production path at a time.
#[derive(Default)]
pub(super) struct FlattenState {
    steps: Vec<ProductionStep>,
    choices: ChoiceCursor,
    dyn_prec: i32,
    dead: bool,
}

impl FlattenState {
    fn reset_variable(&mut self) {
        self.choices.reset();
        self.reset_path();
    }

    fn reset_path(&mut self) {
        self.steps.clear();
        self.dyn_prec = 0;
        self.dead = false;
        self.choices.begin_path();
    }

    fn push_step(&mut self, kind: SymbolType, index: u32, ctx: FlattenCtx) {
        self.steps.push(ProductionStep::pack(
            Symbol { kind, index },
            ctx.prec,
            ctx.assoc,
            ctx.alias,
            ctx.field,
            ctx.reserved,
        ));
    }

    fn restore_outer_prec(&mut self, outer: Precedence) {
        let step = self.steps.last_mut().unwrap();
        step.set_precedence(outer);
    }

    fn restore_outer_assoc(&mut self, outer: Option<Associativity>) {
        let step = self.steps.last_mut().unwrap();
        step.set_associativity(outer);
    }
}

/// Flatten one deterministic path. Choices only select a child, the outer loop in
/// the caller enumerates subsequent paths from the root.
fn apply(
    pool: &RulePool,
    reserved_ids: &FxHashMap<StrId, u16>,
    node: RuleId,
    f_ctx: FlattenCtx,
    at_end: bool,
    st: &mut FlattenState,
) -> FlattenGrammarResult<bool> {
    match pool.node(node) {
        Rule::Sym { kind, index } => {
            st.push_step(kind, index, f_ctx);
            Ok(true)
        }
        Rule::Seq(range) => {
            let children = pool.child_slice(range);
            let mut did_push = false;
            for (i, &child) in children.iter().enumerate() {
                did_push |= apply(
                    pool,
                    reserved_ids,
                    child,
                    f_ctx,
                    at_end && i + 1 == children.len(),
                    st,
                )?;
                if st.dead {
                    break;
                }
            }
            Ok(did_push)
        }
        Rule::Choice(range) => {
            // An empty choice matches nothing, so no production can contain it.
            if range.len == 0 {
                st.dead = true;
                return Ok(false);
            }
            let selected = st.choices.select(range.len);
            let child = pool.child_slice(range)[selected as usize];
            apply(pool, reserved_ids, child, f_ctx, at_end, st)
        }
        Rule::Metadata { params, rule } => {
            let params = pool.params(params);
            let mut inner_ctx = f_ctx;
            if params.precedence != Precedence::None {
                inner_ctx.prec = params.precedence;
            }
            if params.associativity.is_some() {
                inner_ctx.assoc = params.associativity;
            }
            if params.alias.is_some() {
                inner_ctx.alias = params.alias;
            }
            if params.field.is_some() {
                inner_ctx.field = params.field;
            }
            if params.dynamic_precedence.abs() > st.dyn_prec.abs() {
                st.dyn_prec = params.dynamic_precedence;
            }

            let did_push = apply(pool, reserved_ids, rule, inner_ctx, at_end, st)?;
            // A step's prec/assoc governs the parse position just _after_ it, so the
            // regions's last step owns the gap past it. If more steps follow, that gap
            // is outside the region and reverts to the outer context. At the production's
            // tail the gap is the reduce and keeps the region's own value.
            if did_push && !at_end {
                if params.precedence != Precedence::None {
                    st.restore_outer_prec(f_ctx.prec);
                }
                if params.associativity.is_some() {
                    st.restore_outer_assoc(f_ctx.assoc);
                }
            }
            Ok(did_push)
        }
        Rule::Reserved { rule, ctx } => {
            let Some(&reserved) = reserved_ids.get(&ctx) else {
                return Err(FlattenGrammarError::NoReservedWordSet(
                    pool.resolve(ctx).to_string(),
                ));
            };
            let inner = FlattenCtx { reserved, ..f_ctx };
            apply(pool, reserved_ids, rule, inner, at_end, st)
        }
        _ => Ok(false),
    }
}

/// Append the completed path as a production unless this variable already has an
/// identical one.
fn emit(st: &FlattenState, out: &mut ProductionStore, prod_start: u32) {
    for p in &out.productions[prod_start as usize..] {
        if p.dynamic_precedence == st.dyn_prec && out.steps[p.step_range()] == st.steps[..] {
            return;
        }
    }
    let steps_start = out.steps.len() as u32;
    out.steps.extend_from_slice(&st.steps);
    out.productions.push(Production {
        steps_start,
        steps_len: st.steps.len() as u32,
        dynamic_precedence: st.dyn_prec,
    });
}

pub(super) fn flatten_grammar(
    g: &InputGrammar,
    meta: &ExtractedGrammarMeta,
    st: &mut FlattenState,
    out: &mut ProductionStore,
) -> FlattenGrammarResult<()> {
    if meta.reserved_sets.len() > usize::from(u16::MAX) {
        Err(FlattenGrammarError::TooManyReservedWordSets(
            meta.reserved_sets.len(),
        ))?;
    }
    // Last wins on duplicate names.
    let reserved_ids: FxHashMap<StrId, u16> = meta
        .reserved_sets
        .iter()
        .enumerate()
        .map(|(i, (name, _))| (*name, i as u16))
        .collect();
    for v in &g.variables {
        let prod_start = out.productions.len() as u32;
        st.reset_variable();
        loop {
            apply(
                &g.pool,
                &reserved_ids,
                v.root,
                FlattenCtx::default(),
                true,
                st,
            )?;
            if !st.dead {
                emit(st, out, prod_start);
            }
            if !st.choices.advance() {
                break;
            }
            st.reset_path();
        }
        out.var_prods
            .push((prod_start, out.productions.len() as u32));
    }
    check(g, meta, out)
}

/// Post-flatten checks. No empty productions used in variables, and no recursive inlines.
fn check(
    g: &InputGrammar,
    meta: &ExtractedGrammarMeta,
    out: &ProductionStore,
) -> FlattenGrammarResult<()> {
    for (i, &(p_start, p_end)) in out.var_prods.iter().enumerate() {
        let symbol = Symbol::non_terminal(i);
        let used = out.steps.iter().any(|s| s.symbol() == symbol);
        let inlined = meta.inline.contains(&symbol);
        for p in &out.productions[p_start as usize..p_end as usize] {
            if used && p.steps_len == 0 {
                Err(FlattenGrammarError::EmptyString(
                    g.pool.resolve(g.variables[i].name).to_string(),
                ))?;
            }
            if inlined
                && out.steps[p.step_range()]
                    .iter()
                    .any(|s| s.symbol() == symbol)
            {
                Err(FlattenGrammarError::RecursiveInline(
                    g.pool.resolve(g.variables[i].name).to_string(),
                ))?;
            }
        }
    }
    Ok(())
}

pub(super) fn assemble_syntax_grammar(
    g: InputGrammar,
    meta: ExtractedGrammarMeta,
    out: ProductionStore,
) -> (SyntaxGrammar, StrPool) {
    let mut reserved_word_sets = meta
        .reserved_sets
        .iter()
        .map(|(_, symbols)| symbols.iter().copied().collect())
        .collect::<Vec<_>>();
    if reserved_word_sets.is_empty() {
        reserved_word_sets.push(TokenSet::default());
    }
    let variables = g
        .variables
        .iter()
        .zip(&meta.kinds)
        .map(|(v, &kind)| SyntaxVariable { name: v.name, kind })
        .collect::<Vec<_>>();

    let interner = g.pool.into_interner();

    (
        SyntaxGrammar {
            variables,
            extra_symbols: meta.extra_symbols,
            expected_conflicts: meta.conflicts,
            external_tokens: meta.external_tokens,
            supertype_symbols: meta.supertypes,
            variables_to_inline: meta.inline,
            word_token: meta.word,
            precedence_orderings: g.precedence_orderings,
            reserved_word_sets,

            steps: out.steps,
            productions: out.productions,
            var_prods: out.var_prods,
        },
        interner,
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::grammars::{Variable, VariableType};

    #[test]
    fn test_flatten_grammar() {
        let (grammar, interner) = flatten_named(|p| {
            let nt1 = non_term(p, 1);
            let nt2 = non_term(p, 2);
            let nt3 = non_term(p, 3);
            let nt4 = non_term(p, 4);
            let nt5 = non_term(p, 5);
            let nt6 = non_term(p, 6);
            let nt7 = non_term(p, 7);
            let inner = {
                let s = p.seq(&[nt3, nt4]);
                p.prec_right(Precedence::Integer(102), s)
            };
            let choice = p.choice(&[inner, nt5]);
            let pl = {
                let s = p.seq(&[nt2, choice, nt6]);
                p.prec_left(Precedence::Integer(101), s)
            };
            p.seq(&[nt1, pl, nt7])
        })
        .unwrap();

        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![
                ProdView {
                    dyn_prec: 0,
                    steps: vec![
                        StepView::new(Symbol::non_terminal(1)),
                        StepView::new(Symbol::non_terminal(2))
                            .prec(Precedence::Integer(101))
                            .assoc(Some(Associativity::Left)),
                        StepView::new(Symbol::non_terminal(3))
                            .prec(Precedence::Integer(102))
                            .assoc(Some(Associativity::Right)),
                        StepView::new(Symbol::non_terminal(4))
                            .prec(Precedence::Integer(101))
                            .assoc(Some(Associativity::Left)),
                        StepView::new(Symbol::non_terminal(6)),
                        StepView::new(Symbol::non_terminal(7)),
                    ]
                },
                ProdView {
                    dyn_prec: 0,
                    steps: vec![
                        StepView::new(Symbol::non_terminal(1)),
                        StepView::new(Symbol::non_terminal(2))
                            .prec(Precedence::Integer(101))
                            .assoc(Some(Associativity::Left)),
                        StepView::new(Symbol::non_terminal(5))
                            .prec(Precedence::Integer(101))
                            .assoc(Some(Associativity::Left)),
                        StepView::new(Symbol::non_terminal(6)),
                        StepView::new(Symbol::non_terminal(7)),
                    ]
                },
            ]
        );
    }

    #[test]
    fn test_flatten_grammar_with_maximum_dynamic_precedence() {
        let (grammar, interner) = flatten_named(|p| {
            let nt1 = non_term(p, 1);
            let nt2 = non_term(p, 2);
            let nt3 = non_term(p, 3);
            let nt4 = non_term(p, 4);
            let nt5 = non_term(p, 5);
            let nt6 = non_term(p, 6);
            let nt7 = non_term(p, 7);
            let inner = {
                let s = p.seq(&[nt3, nt4]);
                p.prec_dynamic(102, s)
            };
            let choice = p.choice(&[inner, nt5]);
            let pd = {
                let s = p.seq(&[nt2, choice, nt6]);
                p.prec_dynamic(101, s)
            };
            p.seq(&[nt1, pd, nt7])
        })
        .unwrap();

        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![
                ProdView {
                    dyn_prec: 102,
                    steps: vec![
                        StepView::new(Symbol::non_terminal(1)),
                        StepView::new(Symbol::non_terminal(2)),
                        StepView::new(Symbol::non_terminal(3)),
                        StepView::new(Symbol::non_terminal(4)),
                        StepView::new(Symbol::non_terminal(6)),
                        StepView::new(Symbol::non_terminal(7)),
                    ]
                },
                ProdView {
                    dyn_prec: 101,
                    steps: vec![
                        StepView::new(Symbol::non_terminal(1)),
                        StepView::new(Symbol::non_terminal(2)),
                        StepView::new(Symbol::non_terminal(5)),
                        StepView::new(Symbol::non_terminal(6)),
                        StepView::new(Symbol::non_terminal(7)),
                    ]
                },
            ]
        );
    }

    #[test]
    fn test_flatten_grammar_with_final_precedence() {
        let (grammar, interner) = flatten_named(|p| {
            let nt1 = non_term(p, 1);
            let nt2 = non_term(p, 2);
            let s = p.seq(&[nt1, nt2]);
            p.prec_left(Precedence::Integer(101), s)
        })
        .unwrap();
        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![ProdView {
                dyn_prec: 0,
                steps: vec![
                    StepView::new(Symbol::non_terminal(1))
                        .prec(Precedence::Integer(101))
                        .assoc(Some(Associativity::Left)),
                    StepView::new(Symbol::non_terminal(2))
                        .prec(Precedence::Integer(101))
                        .assoc(Some(Associativity::Left)),
                ]
            }]
        );

        let (grammar, interner) = flatten_named(|p| {
            let nt1 = non_term(p, 1);
            let s = p.seq(&[nt1]);
            p.prec_left(Precedence::Integer(101), s)
        })
        .unwrap();
        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![ProdView {
                dyn_prec: 0,
                steps: vec![
                    StepView::new(Symbol::non_terminal(1))
                        .prec(Precedence::Integer(101))
                        .assoc(Some(Associativity::Left)),
                ]
            }]
        );
    }

    #[test]
    fn test_flatten_grammar_with_field_names() {
        let (grammar, interner) = flatten_named(|p| {
            let t1 = term(p, 1);
            let f1 = {
                let n = p.intern("first-thing");
                p.field(n, t1)
            };
            let t2 = term(p, 2);
            let t3 = term(p, 3);
            let f2 = {
                let n = p.intern("second-thing");
                p.field(n, t3)
            };
            let blank = p.blank();
            let choice = p.choice(&[blank, f2]);
            p.seq(&[f1, t2, choice])
        })
        .unwrap();

        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![
                ProdView {
                    dyn_prec: 0,
                    steps: vec![
                        StepView::new(Symbol::terminal(1)).field("first-thing"),
                        StepView::new(Symbol::terminal(2)),
                    ]
                },
                ProdView {
                    dyn_prec: 0,
                    steps: vec![
                        StepView::new(Symbol::terminal(1)).field("first-thing"),
                        StepView::new(Symbol::terminal(2)),
                        StepView::new(Symbol::terminal(3)).field("second-thing"),
                    ]
                },
            ]
        );
    }

    #[test]
    fn test_precedence_inherited_through_inner_metadata() {
        // A prec region inherited by an inner symbol that carries _different_ metadata
        // (field).
        let (grammar, interner) = flatten_named(|p| {
            let a = term(p, 1);
            let b = term(p, 2);
            let bf = {
                let n = p.intern("f");
                p.field(n, b)
            };
            let s = p.seq(&[a, bf]);
            p.prec(Precedence::Integer(5), s)
        })
        .unwrap();

        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![ProdView {
                dyn_prec: 0,
                steps: vec![
                    StepView::new(Symbol::terminal(1)).prec(Precedence::Integer(5)),
                    StepView::new(Symbol::terminal(2))
                        .prec(Precedence::Integer(5))
                        .field("f"),
                ]
            }]
        );
    }

    #[test]
    fn test_flatten_grammar_with_recursive_inline_variable() {
        let mut pool = RulePool::default();
        let nt0 = non_term(&mut pool, 0);
        let nt1 = non_term(&mut pool, 1);
        let nt2 = non_term(&mut pool, 2);
        let root = pool.seq(&[nt0, nt1, nt2]);
        let name = pool.intern("test");
        let pg = InputGrammar {
            pool,
            variables: vec![Variable { name, root }],
            ..Default::default()
        };
        let meta = ExtractedGrammarMeta {
            kinds: vec![VariableType::Named],
            inline: vec![Symbol::non_terminal(0)],
            ..Default::default()
        };
        assert_eq!(
            run(pg, meta).unwrap_err(),
            FlattenGrammarError::RecursiveInline("test".to_string())
        );
    }

    #[test]
    fn test_flatten_grammar_with_unknown_reserved() {
        // Unknown reserved context
        let err = flatten_named(|p| {
            let t1 = term(p, 1);
            let ctx = p.intern("nope");
            p.reserved(t1, ctx)
        })
        .unwrap_err();
        assert_eq!(
            err,
            FlattenGrammarError::NoReservedWordSet("nope".to_string())
        );
    }

    #[test]
    fn test_flatten_grammar_with_empty_production() {
        // Empty production in used variable (`a` refs `b`, `b` is empty)
        let mut pool = RulePool::default();
        let a_root = non_term(&mut pool, 1);
        let b_root = pool.blank();
        let (a, b) = (pool.intern("a"), pool.intern("b"));
        let pg = InputGrammar {
            pool,
            variables: vec![
                Variable {
                    name: a,
                    root: a_root,
                },
                Variable {
                    name: b,
                    root: b_root,
                },
            ],
            ..Default::default()
        };
        let meta = ExtractedGrammarMeta {
            kinds: vec![VariableType::Named, VariableType::Named],
            ..Default::default()
        };
        assert_eq!(
            run(pg, meta).unwrap_err(),
            FlattenGrammarError::EmptyString("b".to_string())
        );
    }

    #[test]
    fn test_flatten_grammar_with_empty_choice() {
        let (grammar, interner) = flatten_named(|p| {
            let prefix = term(p, 1);
            let empty = p.choice(&[]);
            let tail_a = term(p, 2);
            let tail_b = term(p, 3);
            let tail = p.choice(&[tail_a, tail_b]);
            let dead = p.seq(&[prefix, empty, tail]);
            let live = term(p, 4);
            p.choice(&[dead, live])
        })
        .unwrap();

        assert_eq!(
            prods(&grammar, 0, &interner),
            vec![ProdView {
                dyn_prec: 0,
                steps: vec![StepView::new(Symbol::terminal(4))],
            }]
        );

        let (grammar, interner) = flatten_named(|p| p.choice(&[])).unwrap();
        assert!(prods(&grammar, 0, &interner).is_empty());
    }

    fn term(p: &mut RulePool, i: u32) -> RuleId {
        p.push_node(Rule::Sym {
            kind: SymbolType::Terminal,
            index: i,
        })
    }
    fn non_term(p: &mut RulePool, i: u32) -> RuleId {
        p.push_node(Rule::Sym {
            kind: SymbolType::NonTerminal,
            index: i,
        })
    }

    #[derive(Debug, PartialEq)]
    struct StepView {
        symbol: Symbol,
        prec: Precedence,
        assoc: Option<Associativity>,
        alias: Option<Alias>,
        field: Option<String>,
        reserved: u16,
    }

    impl StepView {
        fn new(symbol: Symbol) -> Self {
            Self {
                symbol,
                prec: Precedence::None,
                assoc: None,
                alias: None,
                field: None,
                reserved: 0,
            }
        }
        fn prec(mut self, prec: Precedence) -> Self {
            self.prec = prec;
            self
        }
        fn assoc(mut self, assoc: Option<Associativity>) -> Self {
            self.assoc = assoc;
            self
        }
        fn field(mut self, name: &str) -> Self {
            self.field = Some(name.to_string());
            self
        }
    }

    #[derive(Debug, PartialEq)]
    struct ProdView {
        dyn_prec: i32,
        steps: Vec<StepView>,
    }

    fn run(
        g: InputGrammar,
        meta: ExtractedGrammarMeta,
    ) -> FlattenGrammarResult<(SyntaxGrammar, StrPool)> {
        let mut st = FlattenState::default();
        let mut out = ProductionStore::default();
        flatten_grammar(&g, &meta, &mut st, &mut out)?;
        Ok(assemble_syntax_grammar(g, meta, out))
    }

    fn flatten_named(
        build: impl FnOnce(&mut RulePool) -> RuleId,
    ) -> FlattenGrammarResult<(SyntaxGrammar, StrPool)> {
        let mut pool = RulePool::default();
        let root = build(&mut pool);
        let name = pool.intern("test");
        let pg = InputGrammar {
            pool,
            variables: vec![Variable { name, root }],
            ..Default::default()
        };
        let meta = ExtractedGrammarMeta {
            kinds: vec![VariableType::Named],
            ..Default::default()
        };
        run(pg, meta)
    }

    /// Unpack a variable's productions from the pooled output into comparable views.
    fn prods(grammar: &SyntaxGrammar, var: usize, interner: &StrPool) -> Vec<ProdView> {
        let (p_start, p_end) = grammar.var_prods[var];
        grammar.productions[p_start as usize..p_end as usize]
            .iter()
            .map(|p| ProdView {
                dyn_prec: p.dynamic_precedence,
                steps: grammar.steps[p.step_range()]
                    .iter()
                    .map(|&s| StepView {
                        symbol: s.symbol(),
                        prec: s.precedence(),
                        assoc: s.associativity(),
                        alias: s.alias(),
                        field: s.field().map(|f| interner.resolve(f).to_string()),
                        reserved: s.reserved,
                    })
                    .collect(),
            })
            .collect()
    }
}
