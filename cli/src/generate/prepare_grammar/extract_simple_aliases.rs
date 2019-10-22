use crate::generate::grammars::{LexicalGrammar, SyntaxGrammar};
use crate::generate::rules::{Alias, AliasMap, Symbol, SymbolType};

#[derive(Clone, Default)]
struct SymbolStatus {
    alias: Option<Alias>,
    conflicting: bool,
}

pub(super) fn extract_simple_aliases(
    syntax_grammar: &mut SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
) -> AliasMap {
    // Determine which symbols in the grammars are *always* aliased to a single name.
    let mut terminal_status_list = vec![SymbolStatus::default(); lexical_grammar.variables.len()];
    let mut non_terminal_status_list =
        vec![SymbolStatus::default(); syntax_grammar.variables.len()];
    let mut external_status_list =
        vec![SymbolStatus::default(); syntax_grammar.external_tokens.len()];
    for variable in syntax_grammar.variables.iter() {
        for production in variable.productions.iter() {
            for step in production.steps.iter() {
                let mut status = match step.symbol {
                    Symbol {
                        kind: SymbolType::External,
                        index,
                    } => &mut external_status_list[index],
                    Symbol {
                        kind: SymbolType::NonTerminal,
                        index,
                    } => &mut non_terminal_status_list[index],
                    Symbol {
                        kind: SymbolType::Terminal,
                        index,
                    } => &mut terminal_status_list[index],
                    Symbol {
                        kind: SymbolType::End,
                        ..
                    } => panic!("Unexpected end token"),
                };

                if step.alias.is_none() {
                    status.alias = None;
                    status.conflicting = true;
                }

                if !status.conflicting {
                    if status.alias.is_none() {
                        status.alias = step.alias.clone();
                    } else if status.alias != step.alias {
                        status.alias = None;
                        status.conflicting = true;
                    }
                }
            }
        }
    }

    // Remove the aliases for those symbols.
    for variable in syntax_grammar.variables.iter_mut() {
        for production in variable.productions.iter_mut() {
            for step in production.steps.iter_mut() {
                let status = match step.symbol {
                    Symbol {
                        kind: SymbolType::External,
                        index,
                    } => &external_status_list[index],
                    Symbol {
                        kind: SymbolType::NonTerminal,
                        index,
                    } => &non_terminal_status_list[index],
                    Symbol {
                        kind: SymbolType::Terminal,
                        index,
                    } => &terminal_status_list[index],
                    Symbol {
                        kind: SymbolType::End,
                        ..
                    } => panic!("Unexpected end token"),
                };

                if status.alias.is_some() {
                    step.alias = None;
                }
            }
        }
    }

    // Populate a map of the symbols to their aliases.
    let mut result = AliasMap::new();
    for (i, status) in terminal_status_list.into_iter().enumerate() {
        if let Some(alias) = status.alias {
            result.insert(Symbol::terminal(i), alias);
        }
    }
    for (i, status) in non_terminal_status_list.into_iter().enumerate() {
        if let Some(alias) = status.alias {
            result.insert(Symbol::non_terminal(i), alias);
        }
    }
    for (i, status) in external_status_list.into_iter().enumerate() {
        if let Some(alias) = status.alias {
            result.insert(Symbol::external(i), alias);
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::grammars::{
        LexicalVariable, Production, ProductionStep, SyntaxVariable, VariableType,
    };
    use crate::generate::nfa::Nfa;

    #[test]
    fn test_extract_simple_aliases() {
        let mut syntax_grammar = SyntaxGrammar {
            variables: vec![
                SyntaxVariable {
                    name: "v1".to_owned(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            ProductionStep::new(Symbol::terminal(0)).with_alias("a1", true),
                            ProductionStep::new(Symbol::terminal(1)).with_alias("a2", true),
                            ProductionStep::new(Symbol::terminal(2)).with_alias("a3", true),
                        ],
                    }],
                },
                SyntaxVariable {
                    name: "v2".to_owned(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            // Token 0 is always aliased as "a1".
                            ProductionStep::new(Symbol::terminal(0)).with_alias("a1", true),
                            // Token 1 is aliased above, but not here.
                            ProductionStep::new(Symbol::terminal(1)),
                            // Token 2 is aliased differently than above.
                            ProductionStep::new(Symbol::terminal(2)).with_alias("a4", true),
                        ],
                    }],
                },
            ],
            extra_symbols: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            supertype_symbols: Vec::new(),
            external_tokens: Vec::new(),
            word_token: None,
        };

        let lexical_grammar = LexicalGrammar {
            nfa: Nfa::new(),
            variables: vec![
                LexicalVariable {
                    name: "t1".to_string(),
                    kind: VariableType::Anonymous,
                    implicit_precedence: 0,
                    start_state: 0,
                },
                LexicalVariable {
                    name: "t2".to_string(),
                    kind: VariableType::Anonymous,
                    implicit_precedence: 0,
                    start_state: 0,
                },
                LexicalVariable {
                    name: "t3".to_string(),
                    kind: VariableType::Anonymous,
                    implicit_precedence: 0,
                    start_state: 0,
                },
            ],
        };

        let simple_aliases = extract_simple_aliases(&mut syntax_grammar, &lexical_grammar);
        assert_eq!(simple_aliases.len(), 1);
        assert_eq!(
            simple_aliases[&Symbol::terminal(0)],
            Alias {
                value: "a1".to_string(),
                is_named: true,
            }
        );

        assert_eq!(
            syntax_grammar.variables,
            vec![
                SyntaxVariable {
                    name: "v1".to_owned(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            // 'Simple' alias removed
                            ProductionStep::new(Symbol::terminal(0)),
                            // Other aliases unchanged
                            ProductionStep::new(Symbol::terminal(1)).with_alias("a2", true),
                            ProductionStep::new(Symbol::terminal(2)).with_alias("a3", true),
                        ],
                    },],
                },
                SyntaxVariable {
                    name: "v2".to_owned(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            ProductionStep::new(Symbol::terminal(0)),
                            ProductionStep::new(Symbol::terminal(1)),
                            ProductionStep::new(Symbol::terminal(2)).with_alias("a4", true),
                        ],
                    },],
                },
            ]
        );
    }
}
