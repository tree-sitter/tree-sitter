use crate::grammars::{InlinedProductionMap, Production, ProductionStep, SyntaxGrammar};
use hashbrown::HashMap;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
struct ProductionStepId {
    variable_index: Option<usize>,
    production_index: usize,
    step_index: usize,
}

struct InlinedProductionMapBuilder {
    production_indices_by_step_id: HashMap<ProductionStepId, Vec<usize>>,
    productions: Vec<Production>,
}

impl ProductionStepId {
    pub fn successor(&self) -> Self {
        Self {
            variable_index: self.variable_index,
            production_index: self.production_index,
            step_index: self.step_index + 1,
        }
    }
}

fn production_for_id<'a>(
    map: &'a InlinedProductionMapBuilder,
    id: ProductionStepId,
    grammar: &'a SyntaxGrammar,
) -> &'a Production {
    if let Some(variable_index) = id.variable_index {
        &grammar.variables[variable_index].productions[id.production_index]
    } else {
        &map.productions[id.production_index]
    }
}

fn production_step_for_id<'a>(
    map: &'a InlinedProductionMapBuilder,
    id: ProductionStepId,
    grammar: &'a SyntaxGrammar,
) -> Option<&'a ProductionStep> {
    production_for_id(map, id, grammar).steps.get(id.step_index)
}

fn inline<'a>(
    map: &'a mut InlinedProductionMapBuilder,
    step_id: ProductionStepId,
    grammar: &'a SyntaxGrammar,
) -> &'a Vec<usize> {
    let step = production_step_for_id(map, step_id, grammar).unwrap();
    let mut productions_to_add = grammar.variables[step.symbol.index].productions.clone();

    let mut i = 0;
    while i < productions_to_add.len() {
        if let Some(first_symbol) = productions_to_add[i].first_symbol() {
            if grammar.variables_to_inline.contains(&first_symbol) {
                // Remove the production from the vector, replacing it with a placeholder.
                let production = productions_to_add
                    .splice(i..i + 1, [Production::default()].iter().cloned())
                    .next()
                    .unwrap();

                // Replace the placeholder with the inlined productions.
                productions_to_add.splice(
                    i..i + 1,
                    grammar.variables[first_symbol.index]
                        .productions
                        .iter()
                        .map(|p| {
                            let mut p = p.clone();
                            p.steps.extend(production.steps[1..].iter().cloned());
                            p
                        }),
                );
                continue;
            }
        }
        i += 1;
    }

    let result = productions_to_add
        .into_iter()
        .map(|production_to_add| {
            let mut inlined_production = production_for_id(&map, step_id, grammar).clone();
            let removed_step = inlined_production
                .steps
                .splice(
                    step_id.step_index..step_id.step_index + 1,
                    production_to_add.steps.iter().cloned(),
                )
                .next()
                .unwrap();
            let inserted_steps = &mut inlined_production.steps
                [step_id.step_index..step_id.step_index + production_to_add.steps.len()];
            if let Some(alias) = removed_step.alias {
                for inserted_step in inserted_steps.iter_mut() {
                    inserted_step.alias = Some(alias.clone());
                }
            }
            if let Some(last_inserted_step) = inserted_steps.last_mut() {
                last_inserted_step.precedence = removed_step.precedence;
                last_inserted_step.associativity = removed_step.associativity;
            }
            map.productions
                .iter()
                .position(|p| *p == inlined_production)
                .unwrap_or({
                    map.productions.push(inlined_production);
                    map.productions.len() - 1
                })
        })
        .collect();

    map.production_indices_by_step_id
        .entry(step_id)
        .or_insert(result)
}

pub(super) fn process_inlines(grammar: &SyntaxGrammar) -> InlinedProductionMap {
    let mut result = InlinedProductionMapBuilder {
        productions: Vec::new(),
        production_indices_by_step_id: HashMap::new(),
    };

    let mut step_ids_to_process = Vec::new();
    for (variable_index, variable) in grammar.variables.iter().enumerate() {
        for production_index in 0..variable.productions.len() {
            step_ids_to_process.push(ProductionStepId {
                variable_index: Some(variable_index),
                production_index,
                step_index: 0,
            });
            while !step_ids_to_process.is_empty() {
                let mut i = 0;
                while i < step_ids_to_process.len() {
                    let step_id = step_ids_to_process[i];
                    if let Some(step) = production_step_for_id(&result, step_id, grammar) {
                        if grammar.variables_to_inline.contains(&step.symbol) {
                            let inlined_step_ids = inline(&mut result, step_id, grammar)
                                .into_iter()
                                .cloned()
                                .map(|production_index| ProductionStepId {
                                    variable_index: None,
                                    production_index,
                                    step_index: step_id.step_index,
                                })
                                .collect::<Vec<_>>();
                            step_ids_to_process.splice(i..i + 1, inlined_step_ids);
                        } else {
                            step_ids_to_process[i] = step_id.successor();
                            i += 1;
                        }
                    } else {
                        step_ids_to_process.remove(i);
                    }
                }
            }
        }
    }

    // result
    let productions = result.productions;
    let production_indices_by_step_id = result.production_indices_by_step_id;

    let production_map = production_indices_by_step_id
        .into_iter()
        .map(|(step_id, production_indices)| {
            let production = if let Some(variable_index) = step_id.variable_index {
                &grammar.variables[variable_index].productions[step_id.production_index]
            } else {
                &productions[step_id.production_index]
            } as *const Production;
            ((production, step_id.step_index as u32), production_indices)
        })
        .collect();

    InlinedProductionMap { productions, production_map }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::grammars::{ProductionStep, SyntaxVariable, VariableType};
    use crate::rules::{Associativity, Symbol};

    #[test]
    fn test_basic_inlining() {
        let grammar = SyntaxGrammar {
            expected_conflicts: Vec::new(),
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            word_token: None,
            variables_to_inline: vec![Symbol::non_terminal(1)],
            variables: vec![
                SyntaxVariable {
                    name: "non-terminal-0".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            ProductionStep::new(Symbol::terminal(10)),
                            ProductionStep::new(Symbol::non_terminal(1)), // inlined
                            ProductionStep::new(Symbol::terminal(11)),
                        ],
                    }],
                },
                SyntaxVariable {
                    name: "non-terminal-1".to_string(),
                    kind: VariableType::Named,
                    productions: vec![
                        Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(12)),
                                ProductionStep::new(Symbol::terminal(13)),
                            ],
                        },
                        Production {
                            dynamic_precedence: 0,
                            steps: vec![ProductionStep::new(Symbol::terminal(14))],
                        },
                    ],
                },
            ],
        };
        let inline_map = process_inlines(&grammar);

        // Nothing to inline at step 0.
        assert!(inline_map
            .inlined_productions(&grammar.variables[0].productions[0], 0)
            .is_none());

        // Inlining variable 1 yields two productions.
        assert_eq!(
            inline_map
            .inlined_productions(&grammar.variables[0].productions[0], 1)
                .unwrap()
                .cloned()
                .collect::<Vec<_>>(),
            vec![
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::terminal(10)),
                        ProductionStep::new(Symbol::terminal(12)),
                        ProductionStep::new(Symbol::terminal(13)),
                        ProductionStep::new(Symbol::terminal(11)),
                    ],
                },
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::terminal(10)),
                        ProductionStep::new(Symbol::terminal(14)),
                        ProductionStep::new(Symbol::terminal(11)),
                    ],
                },
            ]
        );
    }

    #[test]
    fn test_nested_inlining() {
        let grammar = SyntaxGrammar {
            variables: vec![
                SyntaxVariable {
                    name: "non-terminal-0".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            ProductionStep::new(Symbol::terminal(10)),
                            ProductionStep::new(Symbol::non_terminal(1)), // inlined
                            ProductionStep::new(Symbol::terminal(11)),
                            ProductionStep::new(Symbol::non_terminal(2)), // inlined
                            ProductionStep::new(Symbol::terminal(12)),
                        ],
                    }],
                },
                SyntaxVariable {
                    name: "non-terminal-1".to_string(),
                    kind: VariableType::Named,
                    productions: vec![
                        Production {
                            dynamic_precedence: 0,
                            steps: vec![ProductionStep::new(Symbol::terminal(13))],
                        },
                        Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::non_terminal(3)), // inlined
                                ProductionStep::new(Symbol::terminal(14)),
                            ],
                        },
                    ],
                },
                SyntaxVariable {
                    name: "non-terminal-2".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![ProductionStep::new(Symbol::terminal(15))],
                    }],
                },
                SyntaxVariable {
                    name: "non-terminal-3".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![ProductionStep::new(Symbol::terminal(16))],
                    }],
                },
            ],
            variables_to_inline: vec![
                Symbol::non_terminal(1),
                Symbol::non_terminal(2),
                Symbol::non_terminal(3),
            ],
            expected_conflicts: Vec::new(),
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            word_token: None,
        };
        let inline_map = process_inlines(&grammar);

        let productions: Vec<&Production> = inline_map
            .inlined_productions(&grammar.variables[0].productions[0], 1)
            .unwrap()
            .collect();

        assert_eq!(
            productions.iter().cloned().cloned().collect::<Vec<_>>(),
            vec![
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::terminal(10)),
                        ProductionStep::new(Symbol::terminal(13)),
                        ProductionStep::new(Symbol::terminal(11)),
                        ProductionStep::new(Symbol::non_terminal(2)),
                        ProductionStep::new(Symbol::terminal(12)),
                    ],
                },
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::terminal(10)),
                        ProductionStep::new(Symbol::terminal(16)),
                        ProductionStep::new(Symbol::terminal(14)),
                        ProductionStep::new(Symbol::terminal(11)),
                        ProductionStep::new(Symbol::non_terminal(2)),
                        ProductionStep::new(Symbol::terminal(12)),
                    ],
                },
            ]
        );

        assert_eq!(
            inline_map
                .inlined_productions(productions[0], 3)
                .unwrap()
                .cloned()
                .collect::<Vec<_>>(),
            vec![Production {
                dynamic_precedence: 0,
                steps: vec![
                    ProductionStep::new(Symbol::terminal(10)),
                    ProductionStep::new(Symbol::terminal(13)),
                    ProductionStep::new(Symbol::terminal(11)),
                    ProductionStep::new(Symbol::terminal(15)),
                    ProductionStep::new(Symbol::terminal(12)),
                ],
            },]
        );
    }

    #[test]
    fn test_inlining_with_precedence_and_alias() {
        let grammar = SyntaxGrammar {
            variables_to_inline: vec![Symbol::non_terminal(1), Symbol::non_terminal(2)],
            variables: vec![
                SyntaxVariable {
                    name: "non-terminal-0".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            // inlined
                            ProductionStep::new(Symbol::non_terminal(1))
                                .with_prec(1, Some(Associativity::Left)),
                            ProductionStep::new(Symbol::terminal(10)),
                            // inlined
                            ProductionStep::new(Symbol::non_terminal(2))
                                .with_alias("outer_alias", true),
                        ],
                    }],
                },
                SyntaxVariable {
                    name: "non-terminal-1".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![
                            ProductionStep::new(Symbol::terminal(11))
                                .with_prec(2, None)
                                .with_alias("inner_alias", true),
                            ProductionStep::new(Symbol::terminal(12)).with_prec(3, None),
                        ],
                    }],
                },
                SyntaxVariable {
                    name: "non-terminal-2".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![ProductionStep::new(Symbol::terminal(13))],
                    }],
                },
            ],
            expected_conflicts: Vec::new(),
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            word_token: None,
        };

        let inline_map = process_inlines(&grammar);

        let productions: Vec<_> = inline_map
            .inlined_productions(&grammar.variables[0].productions[0], 0)
            .unwrap()
            .collect();

        assert_eq!(
            productions.iter().cloned().cloned().collect::<Vec<_>>(),
            vec![Production {
                dynamic_precedence: 0,
                steps: vec![
                    // The first step in the inlined production retains its precedence
                    // and alias.
                    ProductionStep::new(Symbol::terminal(11))
                        .with_prec(2, None)
                        .with_alias("inner_alias", true),
                    // The final step of the inlined production inherits the precedence of
                    // the inlined step.
                    ProductionStep::new(Symbol::terminal(12))
                        .with_prec(1, Some(Associativity::Left)),
                    ProductionStep::new(Symbol::terminal(10)),
                    ProductionStep::new(Symbol::non_terminal(2))
                        .with_alias("outer_alias", true),
                ]
            }],
        );

        assert_eq!(
            inline_map
                .inlined_productions(productions[0], 3)
                .unwrap()
                .cloned()
                .collect::<Vec<_>>(),
            vec![Production {
                dynamic_precedence: 0,
                steps: vec![
                    ProductionStep::new(Symbol::terminal(11))
                        .with_prec(2, None)
                        .with_alias("inner_alias", true),
                    ProductionStep::new(Symbol::terminal(12))
                        .with_prec(1, Some(Associativity::Left)),
                    ProductionStep::new(Symbol::terminal(10)),
                    // All steps of the inlined production inherit their alias from the
                    // inlined step.
                    ProductionStep::new(Symbol::terminal(13)).with_alias("outer_alias", true),
                ]
            }],
        );
    }
}
