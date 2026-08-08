use rustc_hash::FxHashMap;

use crate::{
    grammars::{InputGrammar, Variable, VariableType},
    prepare_grammar::extract_tokens::ExtractedGrammarMeta,
    rules::{Rule, RuleId, RulePool, Symbol},
    strpool::StrId,
};

#[derive(Default)]
struct Expander {
    preceding: usize,
    aux: Vec<Variable>,
    memo: FxHashMap<u64, Vec<(RuleId, Symbol)>>,
    stack: Vec<Task>,
}

#[derive(Copy, Clone)]
enum Task {
    Visit(RuleId),
    Expand { id: RuleId, content: RuleId },
}

impl Expander {
    /// Post-order repeat expansion over one root. Children expand first, and `Reserved`
    /// nodes are not descended.
    fn expand_root(
        &mut self,
        pool: &mut RulePool,
        root: RuleId,
        var_name: StrId,
        aux_repeat_counter: &mut u32,
    ) {
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
                    // non-terminal indices `preceding..`.
                    let symbol = Symbol::non_terminal(self.preceding + self.aux.len());
                    self.memo.entry(hash).or_default().push((content, symbol));
                    let root = wrap_in_binary_tree(pool, symbol, content);
                    self.aux.push(Variable { name, root });
                    pool.set_node(id, Rule::from(symbol));
                }
            }
        }
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

pub(super) fn expand_repeats(grammar: &mut InputGrammar, meta: &mut ExtractedGrammarMeta) {
    let mut expander = Expander {
        preceding: grammar.variables.len(),
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
            expander.expand_root(&mut grammar.pool, content, name, &mut aux_repeat_count);
            grammar.variables[i].root =
                wrap_in_binary_tree(&mut grammar.pool, Symbol::non_terminal(i), content);
            meta.kinds[i] = VariableType::Auxiliary;
            meta.inline.retain(|s| *s != Symbol::non_terminal(i));
            continue;
        }

        expander.expand_root(&mut grammar.pool, root, name, &mut aux_repeat_count);
    }
    for var in expander.aux {
        grammar.variables.push(var);
        meta.kinds.push(VariableType::Auxiliary);
    }
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
        expand_repeats(&mut grammar, &mut meta);
        (grammar, meta)
    }
}
