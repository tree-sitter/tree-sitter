use rustc_hash::FxHashMap;

use crate::{
    grammars::{LexicalGrammar, PrecedenceEntry, SyntaxGrammar, VariableType},
    rules::SymbolView,
};

/// The partial order on lexical tokens induced by symbol precedence entries.
///
/// Only explicit paths imply a preference: unrelated tokens retain the normal
/// lexical tie-breaking behavior.
#[derive(Debug)]
pub struct TokenPrecedence {
    reachable: Vec<Vec<usize>>,
}

impl TokenPrecedence {
    /// Return the indices of all tokens belonging to explicit precedence cycles.
    pub fn new(
        syntax_grammar: &SyntaxGrammar,
        lexical_grammar: &LexicalGrammar,
    ) -> Result<Self, Vec<usize>> {
        let mut tokens_by_name = FxHashMap::default();
        for (index, variable) in lexical_grammar.variables.iter().enumerate() {
            // Anonymous names are token text, not grammar rule names. Auxiliary
            // names are generated implementation details.
            if matches!(variable.kind, VariableType::Named | VariableType::Hidden) {
                tokens_by_name
                    .entry(variable.name)
                    .or_insert_with(Vec::new)
                    .push(index);
            }
        }
        let syntax_by_name: FxHashMap<_, _> = syntax_grammar
            .variables
            .iter()
            .enumerate()
            .filter(|(_, variable)| {
                matches!(variable.kind, VariableType::Named | VariableType::Hidden)
            })
            .map(|(index, variable)| (variable.name, index))
            .collect();

        let mut edges = vec![Vec::new(); lexical_grammar.variables.len()];
        for ordering in &syntax_grammar.precedence_orderings {
            let entries: Vec<_> = ordering
                .iter()
                .filter_map(|entry| {
                    let PrecedenceEntry::Symbol(name) = entry else {
                        return None;
                    };
                    let tokens = tokens_by_name.entry(*name).or_insert_with(|| {
                        syntax_by_name
                            .get(name)
                            .map_or_else(Vec::new, |&index| wrapper_tokens(syntax_grammar, index))
                    });
                    Some(tokens.clone())
                })
                .collect();
            for (position, higher_tokens) in entries.iter().enumerate() {
                for lower_tokens in &entries[position + 1..] {
                    for &higher in higher_tokens {
                        for &lower in lower_tokens {
                            // Distinct rule names can denote the same deduplicated
                            // token. Such aliases cannot introduce a self-cycle.
                            if higher != lower {
                                edges[higher].push(lower);
                            }
                        }
                    }
                }
            }
        }
        for successors in &mut edges {
            successors.sort_unstable();
            successors.dedup();
        }

        let mut reachable = Vec::with_capacity(edges.len());
        let mut cycles = Vec::new();
        for origin in 0..edges.len() {
            let mut visited = vec![false; edges.len()];
            let mut pending = edges[origin].clone();
            while let Some(token) = pending.pop() {
                if !visited[token] {
                    visited[token] = true;
                    pending.extend_from_slice(&edges[token]);
                }
            }
            if visited[origin] {
                cycles.push(origin);
            }
            reachable.push(
                visited
                    .into_iter()
                    .enumerate()
                    .filter_map(|(token, visited)| visited.then_some(token))
                    .collect(),
            );
        }
        if cycles.is_empty() {
            Ok(Self { reachable })
        } else {
            Err(cycles)
        }
    }

    #[must_use]
    pub fn prefers(&self, higher: usize, lower: usize) -> bool {
        self.reachable[higher].binary_search(&lower).is_ok()
    }
}

/// Resolve retained syntax rules, including wrappers left by token deduplication.
/// Every reachable alternative must be unary and refer only to internal
/// terminals or unit chains. The visited set handles recursive unit choices
/// without recursion or dependence on variable order.
fn wrapper_tokens(grammar: &SyntaxGrammar, index: usize) -> Vec<usize> {
    let mut tokens = Vec::new();
    let mut visited = vec![false; grammar.variables.len()];
    let mut pending = vec![index];
    while let Some(variable) = pending.pop() {
        if visited[variable] {
            continue;
        }
        visited[variable] = true;
        let productions = grammar.variable_prod_ids(variable);
        if productions.is_empty() {
            return Vec::new();
        }
        for production in productions {
            let [step] = grammar.production(production).steps else {
                return Vec::new();
            };
            match step.symbol().view() {
                SymbolView::Terminal(token) => tokens.push(usize::from(token)),
                SymbolView::NonTerminal(variable) => pending.push(usize::from(variable)),
                _ => return Vec::new(),
            }
        }
    }
    tokens.sort_unstable();
    tokens.dedup();
    tokens
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        grammars::{LexicalVariable, Production, ProductionStep, SyntaxVariable},
        rules::{ExternalTokenIndex, NonTerminalIndex, Precedence, Symbol, TerminalIndex},
        strpool::StrId,
    };

    fn name(index: u32) -> StrId {
        StrId::from_raw(index)
    }

    fn symbol(index: u32) -> PrecedenceEntry {
        PrecedenceEntry::Symbol(name(index))
    }

    fn terminal(index: u32) -> Symbol {
        TerminalIndex::new(index).symbol()
    }

    fn non_terminal(index: u32) -> Symbol {
        NonTerminalIndex::new(index).symbol()
    }

    fn lexical(kinds: &[VariableType]) -> LexicalGrammar {
        LexicalGrammar {
            variables: kinds
                .iter()
                .enumerate()
                .map(|(index, &kind)| LexicalVariable {
                    name: name(index as u32 + 1),
                    kind,
                    implicit_precedence: 0,
                    start_state: 0,
                    token_start_state: 0,
                })
                .collect(),
            ..Default::default()
        }
    }

    fn add_variable(grammar: &mut SyntaxGrammar, id: u32, alternatives: &[Vec<Symbol>]) {
        grammar.variables.push(SyntaxVariable {
            name: name(id),
            kind: VariableType::Named,
        });
        let start = grammar.productions.len() as u32;
        for symbols in alternatives {
            let steps_start = grammar.steps.len() as u32;
            grammar.steps.extend(symbols.iter().map(|&symbol| {
                ProductionStep::pack(symbol, Precedence::None, None, None, None, 0)
            }));
            grammar.productions.push(Production {
                steps_start,
                steps_len: symbols.len() as u32,
                dynamic_precedence: 0,
                requires_eof_lookahead: false,
            });
        }
        grammar
            .var_prods
            .push((start, grammar.productions.len() as u32));
    }

    #[test]
    fn direct_named_and_hidden_tokens() {
        let lexical = lexical(&[VariableType::Named, VariableType::Hidden]);
        let syntax = SyntaxGrammar {
            precedence_orderings: vec![vec![symbol(1), symbol(2)]],
            ..Default::default()
        };
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        assert!(order.prefers(0, 1));
        assert!(!order.prefers(1, 0));
        assert!(!order.prefers(0, 0));
    }

    #[test]
    fn transitive_order_does_not_order_unrelated_tokens() {
        let lexical = lexical(&[VariableType::Named; 4]);
        let syntax = SyntaxGrammar {
            precedence_orderings: vec![vec![symbol(1), symbol(2)], vec![symbol(2), symbol(3)]],
            ..Default::default()
        };
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        assert!(order.prefers(0, 2));
        for token in 0..4 {
            assert!(!order.prefers(token, 3));
            assert!(!order.prefers(3, token));
        }
    }

    #[test]
    fn reports_only_cycle_members_across_lists() {
        let lexical = lexical(&[VariableType::Named; 5]);
        let mut syntax = SyntaxGrammar {
            precedence_orderings: vec![
                vec![symbol(4), symbol(1), symbol(2)],
                vec![symbol(2), symbol(3)],
                vec![symbol(3), symbol(1), symbol(5)],
            ],
            ..Default::default()
        };
        assert_eq!(
            TokenPrecedence::new(&syntax, &lexical).unwrap_err(),
            [0, 1, 2]
        );
        syntax.precedence_orderings = vec![vec![symbol(1), symbol(2)], vec![symbol(2), symbol(1)]];
        assert_eq!(TokenPrecedence::new(&syntax, &lexical).unwrap_err(), [0, 1]);
    }

    #[test]
    fn unary_choices_and_chains_resolve_deduplicated_tokens() {
        let lexical = lexical(&[
            VariableType::Named,
            VariableType::Anonymous,
            VariableType::Named,
        ]);
        let mut syntax = SyntaxGrammar::default();
        add_variable(&mut syntax, 10, &[vec![non_terminal(1)]]);
        add_variable(&mut syntax, 11, &[vec![terminal(0)], vec![non_terminal(2)]]);
        add_variable(&mut syntax, 12, &[vec![terminal(1)]]);
        add_variable(&mut syntax, 13, &[vec![terminal(0)]]);
        syntax.precedence_orderings = vec![
            vec![symbol(10), symbol(3)],
            // Both aliases of token 0, including its direct name, are no-ops.
            vec![symbol(1), symbol(13), symbol(1)],
        ];
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        assert!(order.prefers(0, 2));
        assert!(order.prefers(1, 2));
        assert!(!order.prefers(0, 1));
        assert!(!order.prefers(1, 0));
    }

    #[test]
    fn syntax_only_alternatives_are_ignored_even_through_wrappers() {
        let lexical = lexical(&[VariableType::Named; 2]);
        let mut syntax = SyntaxGrammar::default();
        add_variable(
            &mut syntax,
            10,
            &[vec![terminal(0)], vec![terminal(0), terminal(1)]],
        );
        add_variable(&mut syntax, 11, &[vec![terminal(0)], vec![]]);
        add_variable(
            &mut syntax,
            12,
            &[vec![terminal(0)], vec![ExternalTokenIndex::new(0).symbol()]],
        );
        add_variable(&mut syntax, 13, &[vec![non_terminal(0)]]);
        add_variable(&mut syntax, 14, &[]);
        syntax.precedence_orderings = (10..=14)
            .map(|id| vec![symbol(2), symbol(id), symbol(1)])
            .collect();
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        // The real lexical entries still relate across ignored parse entries.
        assert!(order.prefers(1, 0));
        assert!(!order.prefers(0, 1));
    }

    #[test]
    fn named_precedences_remain_parse_only() {
        let lexical = lexical(&[VariableType::Named; 3]);
        let syntax = SyntaxGrammar {
            precedence_orderings: vec![vec![symbol(1), PrecedenceEntry::Name(name(2)), symbol(3)]],
            ..Default::default()
        };
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        assert!(order.prefers(0, 2));
        assert!(!order.prefers(0, 1));
        assert!(!order.prefers(1, 2));
    }

    #[test]
    fn anonymous_text_and_auxiliary_names_do_not_name_rules() {
        let lexical = lexical(&[
            VariableType::Anonymous,
            VariableType::Auxiliary,
            VariableType::Named,
        ]);
        let mut syntax = SyntaxGrammar::default();
        // A syntax rule happens to have the same name as token 0's text.
        add_variable(&mut syntax, 1, &[vec![terminal(2), terminal(2)]]);
        syntax.precedence_orderings = vec![vec![symbol(1), symbol(2), symbol(3)]];
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        for higher in 0..3 {
            for lower in 0..3 {
                assert!(!order.prefers(higher, lower));
            }
        }
    }

    #[test]
    fn recursive_unit_choices_terminate() {
        let lexical = lexical(&[VariableType::Named; 2]);
        let mut syntax = SyntaxGrammar::default();
        add_variable(&mut syntax, 10, &[vec![non_terminal(1)]]);
        add_variable(&mut syntax, 11, &[vec![non_terminal(0)], vec![terminal(0)]]);
        add_variable(&mut syntax, 12, &[vec![non_terminal(2)]]);
        syntax.precedence_orderings = vec![vec![symbol(10), symbol(12), symbol(2)]];
        let order = TokenPrecedence::new(&syntax, &lexical).unwrap();
        assert!(order.prefers(0, 1));
        assert!(!order.prefers(1, 0));
    }
}
