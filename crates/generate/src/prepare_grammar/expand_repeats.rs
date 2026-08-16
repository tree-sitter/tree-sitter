use rustc_hash::FxHashMap;
use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::{
    grammars::{InputGrammar, Variable, VariableType},
    prepare_grammar::extract_tokens::ExtractedGrammarMeta,
    rules::{Rule, RuleId, RulePool, Symbol, SymbolType},
    strpool::{StrId, StrPool},
};

#[derive(Default)]
struct Expander {
    preceding: usize,
    aux: Vec<Variable>,
    memo: FxHashMap<u64, Vec<(RuleId, Symbol)>>,
    stack: Vec<Task>,
    zero_width: ZeroWidth,
}

#[derive(Copy, Clone)]
enum Task {
    Visit(RuleId),
    Expand { id: RuleId, content: RuleId },
}

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
#[error("Rule `{0}` contains a repetition that can match the empty string at end of input")]
pub struct ExpandRepeatsError(pub String);

impl Expander {
    /// Post-order repeat expansion over one root. Children expand first, and `Reserved`
    /// nodes are not descended.
    fn expand_root(
        &mut self,
        pool: &mut RulePool,
        root: RuleId,
        var_name: StrId,
        aux_repeat_counter: &mut u32,
    ) -> Result<(), ExpandRepeatsError> {
        self.stack.clear();
        self.stack.push(Task::Visit(root));
        'walk: while let Some(task) = self.stack.pop() {
            match task {
                Task::Visit(id) => match pool.node(id) {
                    Rule::Repeat(content) => {
                        self.stack.push(Task::Expand { id, content });
                        self.stack.push(Task::Visit(content));
                    }
                    // For choices, sequences, and metadata, descend into the child rules,
                    // replacing any nested repetitions.
                    Rule::Seq(range) | Rule::Choice(range) => {
                        let base = self.stack.len();
                        for &c in pool.child_slice(range) {
                            self.stack.push(Task::Visit(c));
                        }
                        self.stack[base..].reverse();
                    }
                    Rule::Metadata { rule, .. } => self.stack.push(Task::Visit(rule)),
                    _ => {} // For primitive rules, don't change anything.
                },
                Task::Expand { id, content } => {
                    let width = self.zero_width.eval(pool, content);
                    if width.eof_nullable {
                        return Err(ExpandRepeatsError(pool.resolve(var_name).to_string()));
                    }
                    // For repetitions, introduce an auxiliary rule that contains the
                    // repeated content, but can also contain a recursive binary tree structure.
                    let hash = pool.subtree_hash(content);
                    if let Some(candidates) = self.memo.get(&hash) {
                        for &(node, symbol) in candidates {
                            if pool.subtree_eq(node, content) {
                                pool.set_node(id, Rule::from(symbol));
                                continue 'walk;
                            }
                        }
                    }
                    *aux_repeat_counter += 1;
                    let name = format!("{}_repeat{aux_repeat_counter}", pool.resolve(var_name));
                    let name = pool.intern(&name);
                    // Aux rules are appended after the original variables, so they occupy
                    // non-terminal indices `preceding..`. The aux stands for `Repeat(content)`,
                    // which matches zero width exactly when `content` does.
                    let symbol = Symbol::non_terminal(self.preceding + self.aux.len());
                    self.zero_width.push_variable(width);
                    self.memo.entry(hash).or_default().push((content, symbol));
                    let root = wrap_in_binary_tree(pool, symbol, content);
                    self.aux.push(Variable { name, root });
                    pool.set_node(id, Rule::from(symbol));
                }
            }
        }
        Ok(())
    }
}

/// Whether a rule can match zero characters, with and without crossing an `eof()`.
#[derive(Clone, Copy, Default, PartialEq, Eq, Debug)]
struct Width {
    nullable: bool,
    eof_nullable: bool,
}

impl Width {
    /// Fold `other` in, reporting whether that set anything new to `true`.
    fn merge(&mut self, other: Self) -> bool {
        let before = *self;
        self.nullable |= other.nullable;
        self.eof_nullable |= other.eof_nullable;
        *self != before
    }
}

#[derive(Clone, Copy)]
enum Visit {
    Enter(RuleId),
    Exit(RuleId),
}

/// Zero width analysis over the rule pool.
///
/// `by_variable` is seeded by a fixpoint over the whole grammar before any expansion,
/// which makes results indepedent of the order in which rules are declared.
#[derive(Default)]
struct ZeroWidth {
    by_variable: Vec<Width>,
    stack: Vec<Visit>,
    values: Vec<Width>,
}

impl ZeroWidth {
    /// Seed `by_variable` with every rule's width, as a least fixpoint.
    ///
    /// [`Self::eval`] reads a nonterminal's width from this table, but rules can
    /// reference each other cyclically. Every rule starts at "matches nothing", and
    /// all of them are re-evaluated against the current table until a full pass
    /// changes nothing. Starting there prevents a cycle from marking itself. A rule
    /// that reaches itself reads back  "matches nothing", so flags are only set by
    /// a path that truly matches zero width.
    fn new(pool: &RulePool, variables: &[Variable]) -> Self {
        let mut this = Self {
            by_variable: vec![Width::default(); variables.len()],
            stack: Vec::new(),
            values: Vec::new(),
        };
        loop {
            let mut changed = false;
            for (i, v) in variables.iter().enumerate() {
                let width = this.eval(pool, v.root);
                changed |= this.by_variable[i].merge(width);
            }
            if !changed {
                break;
            }
        }
        this
    }

    /// Record the width of a newly created auxiliary rule.
    fn push_variable(&mut self, width: Width) {
        self.by_variable.push(width);
    }

    /// Post-order walk of the subtree at `root`, combining children into their parent.
    fn eval(&mut self, pool: &RulePool, root: RuleId) -> Width {
        self.stack.clear();
        self.values.clear();
        self.stack.push(Visit::Enter(root));
        while let Some(step) = self.stack.pop() {
            match step {
                Visit::Enter(id) => match pool.node(id) {
                    Rule::Seq(range) | Rule::Choice(range) => {
                        self.stack.push(Visit::Exit(id));
                        for &c in pool.child_slice(range) {
                            self.stack.push(Visit::Enter(c));
                        }
                    }
                    Rule::Repeat(rule)
                    | Rule::Metadata { rule, .. }
                    | Rule::Reserved { rule, .. } => {
                        self.stack.push(Visit::Exit(id));
                        self.stack.push(Visit::Enter(rule));
                    }
                    Rule::Blank => self.values.push(Width {
                        nullable: true,
                        eof_nullable: false,
                    }),
                    Rule::String(s) => self.values.push(Width {
                        nullable: s == StrPool::EMPTY_STR_ID,
                        eof_nullable: false,
                    }),
                    Rule::Eof => self.values.push(Width {
                        nullable: false,
                        eof_nullable: true,
                    }),
                    Rule::Sym { kind, index } => {
                        let width = match kind {
                            SymbolType::End => Width {
                                nullable: false,
                                eof_nullable: true,
                            },
                            SymbolType::NonTerminal => self
                                .by_variable
                                .get(index as usize)
                                .copied()
                                .unwrap_or_default(),
                            // External scanners decide at runtime how far to advance
                            // and may return a zero width token, so this must count
                            // as nullable.
                            //
                            // A scanner may gate itself on `lexer->eof`, but there's
                            // no way to determine that here. Assuming so would reject
                            // every grammar that `repeat`s an external.
                            SymbolType::External => Width {
                                nullable: true,
                                eof_nullable: false,
                            },
                            // `expand_tokens` rejects tokens that match the empty string
                            SymbolType::Terminal => Width::default(),
                            // Lookahead marker that `build_parse_table` inserts for nonterminal
                            // extras _after_ this pass runs.
                            SymbolType::EndOfNonTerminalExtra => unreachable!(),
                        };
                        self.values.push(width);
                    }
                    // `extract_tokens` hoists every `Pattern` into the lexical grammar and
                    // leaves a terminal symbol in its place. Only syntactic  (non
                    // lexical grammar) rules are walked here.
                    Rule::Pattern(..)
                    // `intern_symbols` resolves every `NamedSymbol` to a `Sym`
                    | Rule::NamedSymbol(_) => unreachable!(),
                },
                Visit::Exit(id) => match pool.node(id) {
                    Rule::Choice(range) => {
                        let base = self.values.len() - range.len as usize;
                        let mut width = Width::default();
                        for child in self.values.drain(base..) {
                            width.nullable |= child.nullable;
                            width.eof_nullable |= child.eof_nullable;
                        }
                        self.values.push(width);
                    }
                    Rule::Seq(range) => {
                        let base = self.values.len() - range.len as usize;
                        let mut nullable = true; // matches empty iff every element does
                        let mut any_eof = false; // matches eof if any element does
                        let mut all_zero_width = true; // every element matches empty or via `eof()`
                        for child in self.values.drain(base..) {
                            nullable &= child.nullable;
                            any_eof |= child.eof_nullable;
                            all_zero_width &= child.nullable || child.eof_nullable;
                        }
                        self.values.push(Width {
                            nullable,
                            eof_nullable: all_zero_width && any_eof,
                        });
                    }
                    // Each of these wraps a single child whose width is both already on the
                    // stack and exactly this (the wrapper) node's width:
                    //
                    // - `Repeat` is one or more, so it matches zero width exactly when its
                    //   content does. Zero or more comes in  as `Choice(Repeat, Blank)` from
                    //   `parse_grammar`, so that blank gives the nullable case instead of here.
                    // - `Metadata` carries wrapping data that doesn't change how much input is
                    //   matched. Its `token` forms are already replaced by terminals in
                    //   `extrac_tokens`.
                    // - `Reserved` only names the reserved word set for a its child.
                    Rule::Repeat(_) | Rule::Metadata { .. } | Rule::Reserved { .. } => {}
                    // Every other rule is a leaf. `Enter` pushed its width directly and
                    // never queued an `Exit`.
                    _ => unreachable!(),
                },
            }
        }
        self.values.pop().unwrap_or_default()
    }
}

/// Build a repeat aux body of `choice(seq(sym, sym), inner)`
fn wrap_in_binary_tree(pool: &mut RulePool, symbol: Symbol, inner: RuleId) -> RuleId {
    let s1 = pool.push_node(Rule::from(symbol));
    let s2 = pool.push_node(Rule::from(symbol));
    let range = pool.push_children(&[s1, s2]);
    let seq = pool.push_node(Rule::Seq(range));
    let mut elements = vec![seq];
    let mut stack = vec![inner];
    while let Some(id) = stack.pop() {
        if let Rule::Choice(range) = pool.node(id) {
            let base = stack.len();
            stack.extend_from_slice(pool.child_slice(range));
            stack[base..].reverse();
        } else if !elements.iter().any(|&e| pool.subtree_eq(e, id)) {
            elements.push(id);
        }
    }
    if elements.len() == 1 {
        elements[0]
    } else {
        let range = pool.push_children(&elements);
        pool.push_node(Rule::Choice(range))
    }
}

pub(super) fn expand_repeats(
    grammar: &mut InputGrammar,
    meta: &mut ExtractedGrammarMeta,
) -> Result<(), ExpandRepeatsError> {
    let mut expander = Expander {
        preceding: grammar.variables.len(),
        zero_width: ZeroWidth::new(&grammar.pool, &grammar.variables),
        ..Default::default()
    };
    for i in 0..grammar.variables.len() {
        let Variable { name, root } = grammar.variables[i];
        let mut aux_repeat_count = 0;

        // A hidden variable with a top level repetition becomes its own recursive binary
        // tree instead of gaining an auxiliary rule, and can no longer be inlined.
        if meta.kinds[i] == VariableType::Hidden
            && let Rule::Repeat(content) = grammar.pool.node(root)
        {
            if expander
                .zero_width
                .eval(&grammar.pool, content)
                .eof_nullable
            {
                return Err(ExpandRepeatsError(grammar.pool.resolve(name).to_string()));
            }
            expander.expand_root(&mut grammar.pool, content, name, &mut aux_repeat_count)?;
            grammar.variables[i].root =
                wrap_in_binary_tree(&mut grammar.pool, Symbol::non_terminal(i), content);
            meta.kinds[i] = VariableType::Auxiliary;
            meta.inline.retain(|s| *s != Symbol::non_terminal(i));
            continue;
        }

        expander.expand_root(&mut grammar.pool, root, name, &mut aux_repeat_count)?;
    }
    for var in expander.aux {
        grammar.variables.push(var);
        meta.kinds.push(VariableType::Auxiliary);
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use crate::rules::SymbolType;

    use super::*;

    #[test]
    fn test_basic_repeat_expansion() {
        // Repeats nested inside of sequences and choices are expanded.
        let mut pool = RulePool::default();
        let r0 = {
            let a = term(&mut pool, 10);
            let ch = {
                let r1 = {
                    let t = term(&mut pool, 11);
                    pool.repeat(t)
                };
                let r2 = {
                    let t = term(&mut pool, 12);
                    pool.repeat(t)
                };
                pool.choice(&[r1, r2])
            };
            let b = term(&mut pool, 13);
            pool.seq(&[a, ch, b])
        };
        let name = pool.intern("rule0");
        let (mut grammar, meta) = expand(
            pool,
            vec![Variable { name, root: r0 }],
            vec![VariableType::Named],
        );

        let names = grammar
            .variables
            .iter()
            .map(|v| grammar.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule0", "rule0_repeat1", "rule0_repeat2"]);
        assert_eq!(
            meta.kinds,
            [
                VariableType::Named,
                VariableType::Auxiliary,
                VariableType::Auxiliary
            ]
        );

        // rule0: seq(terminal(10), choice(non_terminal(1), non_terminal(2)), terminal(13))
        let e0 = {
            let pool = &mut grammar.pool;
            let (a, b) = (term(pool, 10), term(pool, 13));
            let ch = {
                let (x, y) = (non_term(pool, 1), non_term(pool, 2));
                pool.choice(&[x, y])
            };
            pool.seq(&[a, ch, b])
        };
        assert!(grammar.pool.subtree_eq(grammar.variables[0].root, e0));

        // rule0_repeat1: choice(seq(nt1, nt1), terminal(11))
        let e1 = {
            let p = &mut grammar.pool;
            let sq = {
                let (x, y) = (non_term(p, 1), non_term(p, 1));
                p.seq(&[x, y])
            };
            let t = term(p, 11);
            p.choice(&[sq, t])
        };
        assert!(grammar.pool.subtree_eq(grammar.variables[1].root, e1));

        // rule0_repeat2: choice(seq(nt2, nt2), terminal(12))
        let e2 = {
            let p = &mut grammar.pool;
            let sq = {
                let (x, y) = (non_term(p, 2), non_term(p, 2));
                p.seq(&[x, y])
            };
            let t = term(p, 12);
            p.choice(&[sq, t])
        };
        assert!(grammar.pool.subtree_eq(grammar.variables[2].root, e2));
    }

    #[test]
    fn test_repeat_deduplication() {
        // repeat(terminal(4)) appears in 3 places. Only one aux rule is made
        let mut pool = RulePool::default();
        let r0 = {
            let s1 = {
                let t = term(&mut pool, 1);
                let r = {
                    let x = term(&mut pool, 4);
                    pool.repeat(x)
                };
                pool.seq(&[t, r])
            };
            let s2 = {
                let t = term(&mut pool, 2);
                let r = {
                    let x = term(&mut pool, 4);
                    pool.repeat(x)
                };
                pool.seq(&[t, r])
            };
            pool.choice(&[s1, s2])
        };
        let r1 = {
            let t = term(&mut pool, 3);
            let r = {
                let x = term(&mut pool, 4);
                pool.repeat(x)
            };
            pool.seq(&[t, r])
        };
        let (n0, n1) = (pool.intern("rule0"), pool.intern("rule1"));
        let variables = vec![
            Variable { name: n0, root: r0 },
            Variable { name: n1, root: r1 },
        ];
        let (mut g, meta) = expand(pool, variables, vec![VariableType::Named; 2]);

        let names = g
            .variables
            .iter()
            .map(|v| g.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule0", "rule1", "rule0_repeat1"]);
        assert_eq!(
            meta.kinds,
            [
                VariableType::Named,
                VariableType::Named,
                VariableType::Auxiliary
            ]
        );

        // rule0: choice(seq(t1, nt2), sseq(t2, nt2))
        let e0 = {
            let p = &mut g.pool;
            let s1 = {
                let (t, n) = (term(p, 1), non_term(p, 2));
                p.seq(&[t, n])
            };
            let s2 = {
                let (t, n) = (term(p, 2), non_term(p, 2));
                p.seq(&[t, n])
            };
            p.choice(&[s1, s2])
        };
        assert!(g.pool.subtree_eq(g.variables[0].root, e0));
        // rule1: seq(t3, nt2)
        let e1 = {
            let p = &mut g.pool;
            let (t, n) = (term(p, 3), non_term(p, 2));
            p.seq(&[t, n])
        };
        assert!(g.pool.subtree_eq(g.variables[1].root, e1));
        // rule0_repeat1: choice(seq(nt2, nt2), terminal(4))
        let e2 = {
            let p = &mut g.pool;
            let sq = {
                let (x, y) = (non_term(p, 2), non_term(p, 2));
                p.seq(&[x, y])
            };
            let t = term(p, 4);
            p.choice(&[sq, t])
        };
        assert!(g.pool.subtree_eq(g.variables[2].root, e2));
    }

    #[test]
    fn test_expansion_of_nested_repeats() {
        // Nested repeats expand inside out. The inner one becomes `rule0_repeat1` (nt1),
        // and then outer one (now referencing it) becomes rule0_repeat2
        let mut pool = RulePool::default();
        let r0 = {
            let t10 = term(&mut pool, 10);
            let outer = {
                let t11 = term(&mut pool, 11);
                let inner = {
                    let t = term(&mut pool, 12);
                    pool.repeat(t)
                };
                let content = pool.seq(&[t11, inner]);
                pool.repeat(content)
            };
            pool.seq(&[t10, outer])
        };
        let name = pool.intern("rule0");
        let (mut g, meta) = expand(
            pool,
            vec![Variable { name, root: r0 }],
            vec![VariableType::Named],
        );

        let names = g
            .variables
            .iter()
            .map(|v| g.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule0", "rule0_repeat1", "rule0_repeat2"]);
        assert_eq!(
            meta.kinds,
            [
                VariableType::Named,
                VariableType::Auxiliary,
                VariableType::Auxiliary
            ]
        );

        // rule0: seq(terminal(10), non_terminal(2))
        let e0 = {
            let p = &mut g.pool;
            let (t, n) = (term(p, 10), non_term(p, 2));
            p.seq(&[t, n])
        };
        assert!(g.pool.subtree_eq(g.variables[0].root, e0));
        // rule0_repeat2 (outer): choice(seq(nt2, nt2), seq(terminal(11), nt1))
        let e2 = {
            let p = &mut g.pool;
            let sq1 = {
                let (x, y) = (non_term(p, 2), non_term(p, 2));
                p.seq(&[x, y])
            };
            let sq2 = {
                let (t, n) = (term(p, 11), non_term(p, 1));
                p.seq(&[t, n])
            };
            p.choice(&[sq1, sq2])
        };
        assert!(g.pool.subtree_eq(g.variables[2].root, e2));
    }

    #[test]
    fn test_expansion_of_repeats_at_top_of_hidden_rules() {
        // A hidden rule whos whole body is a repeat becomes its own recursive binary
        // tree (using its own symbol) instead of gaining a separate aux rule, and is
        // reclassified as Axuiliary.
        let mut pool = RulePool::default();
        let r0 = non_term(&mut pool, 1);
        let r1 = {
            let ch = {
                let (a, b) = (term(&mut pool, 11), term(&mut pool, 12));
                pool.choice(&[a, b])
            };
            pool.repeat(ch)
        };
        let (n0, n1) = (pool.intern("rule0"), pool.intern("_rule1"));
        let variables = vec![
            Variable { name: n0, root: r0 },
            Variable { name: n1, root: r1 },
        ];
        let (mut g, meta) = expand(
            pool,
            variables,
            vec![VariableType::Named, VariableType::Hidden],
        );

        // No separate aux rule: _rule1 absorbed during recursion
        let names = g
            .variables
            .iter()
            .map(|v| g.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule0", "_rule1"]);
        assert_eq!(meta.kinds, [VariableType::Named, VariableType::Auxiliary]);

        // rule0: non_terminal(1) (unchanged)
        assert_eq!(
            g.pool.node(g.variables[0].root),
            Rule::Sym {
                kind: SymbolType::NonTerminal,
                index: 1
            }
        );

        // _rule1: choice(seq(nt1, nt1), terminal(11), terminal(12)) (inner choice flattened)
        let e1 = {
            let p = &mut g.pool;
            let sq = {
                let (x, y) = (non_term(p, 1), non_term(p, 1));
                p.seq(&[x, y])
            };
            let (a, b) = (term(p, 11), term(p, 12));
            p.choice(&[sq, a, b])
        };
        assert!(g.pool.subtree_eq(g.variables[1].root, e1));
    }

    #[test]
    fn test_rejects_repeat_of_eof_helper_rule() {
        // rule0: repeat(non_terminal(1)); rule1: eof()
        let mut pool = RulePool::default();
        let r0 = {
            let n = non_term(&mut pool, 1);
            pool.repeat(n)
        };
        let r1 = pool.push_node(Rule::Eof);
        let (n0, n1) = (pool.intern("rule0"), pool.intern("rule1"));
        let mut grammar = InputGrammar {
            pool,
            variables: vec![
                Variable { name: n0, root: r0 },
                Variable { name: n1, root: r1 },
            ],
            ..Default::default()
        };
        let mut meta = ExtractedGrammarMeta {
            kinds: vec![VariableType::Named; 2],
            ..Default::default()
        };
        assert_eq!(
            expand_repeats(&mut grammar, &mut meta).unwrap_err(),
            ExpandRepeatsError("rule0".to_string())
        );
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

    fn expand(
        pool: RulePool,
        variables: Vec<Variable>,
        kinds: Vec<VariableType>,
    ) -> (InputGrammar, ExtractedGrammarMeta) {
        let mut grammar = InputGrammar {
            pool,
            variables,
            ..Default::default()
        };
        let mut meta = ExtractedGrammarMeta {
            kinds,
            ..Default::default()
        };
        expand_repeats(&mut grammar, &mut meta).unwrap();
        (grammar, meta)
    }
}
