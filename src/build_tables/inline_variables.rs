use super::item::ParseItem;
use crate::grammars::{Production, SyntaxGrammar};
use std::collections::HashMap;

pub(crate) struct InlinedProductionMap {
    pub inlined_productions: Vec<Production>,
    item_map: HashMap<ParseItem, Vec<u32>>,
}

impl InlinedProductionMap {
    pub fn new(grammar: &SyntaxGrammar) -> Self {
        let mut result = Self {
            inlined_productions: Vec::new(),
            item_map: HashMap::new(),
        };

        let mut items_to_process = Vec::new();
        for (variable_index, variable) in grammar.variables.iter().enumerate() {
            for production_index in 0..variable.productions.len() {
                items_to_process.push(ParseItem::Normal {
                    variable_index: variable_index as u32,
                    production_index: production_index as u32,
                    step_index: 0,
                });
                while !items_to_process.is_empty() {
                    let mut i = 0;
                    while i < items_to_process.len() {
                        let item = &items_to_process[i];
                        if let Some(step) = item.step(grammar, &result) {
                            if grammar.variables_to_inline.contains(&step.symbol) {
                                let inlined_items = result
                                    .inline(*item, grammar)
                                    .into_iter()
                                    .map(|production_index| ParseItem::Inlined {
                                        variable_index: item.variable_index(),
                                        production_index: *production_index,
                                        step_index: item.step_index() as u32,
                                    })
                                    .collect::<Vec<_>>();
                                items_to_process.splice(i..i + 1, inlined_items);
                            } else {
                                items_to_process[i] = item.successor();
                                i += 1;
                            }
                        } else {
                            items_to_process.remove(i);
                        }
                    }
                }
            }
        }

        result
    }

    pub fn inlined_items<'a>(
        &'a self,
        item: ParseItem,
    ) -> Option<impl Iterator<Item = ParseItem> + 'a> {
        self.item_map.get(&item).map(|production_indices| {
            production_indices
                .iter()
                .cloned()
                .map(move |production_index| ParseItem::Inlined {
                    variable_index: item.variable_index(),
                    production_index,
                    step_index: item.step_index() as u32,
                })
        })
    }

    fn inline(&mut self, item: ParseItem, grammar: &SyntaxGrammar) -> &Vec<u32> {
        let step_index = item.step_index();
        let mut productions_to_add = grammar.variables
            [item.step(grammar, self).unwrap().symbol.index]
            .productions
            .clone();

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
                let mut inlined_production = item.production(grammar, &self).clone();
                inlined_production.steps.splice(
                    step_index..step_index + 1,
                    production_to_add.steps.iter().cloned(),
                );
                self.inlined_productions
                    .iter()
                    .position(|p| *p == inlined_production)
                    .unwrap_or({
                        self.inlined_productions.push(inlined_production);
                        self.inlined_productions.len() - 1
                    }) as u32
            })
            .collect();

        self.item_map.entry(item).or_insert(result)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::grammars::{ProductionStep, SyntaxVariable, VariableType};
    use crate::rules::Symbol;

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
                    name: "var0".to_string(),
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
                    name: "var1".to_string(),
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

        let inline_map = InlinedProductionMap::new(&grammar);

        // Nothing to inline at step 0.
        assert_eq!(
            display_items(
                inline_map.inlined_items(ParseItem::Normal {
                    variable_index: 0,
                    production_index: 0,
                    step_index: 0
                }),
                &grammar,
                &inline_map
            ),
            None
        );

        // Inlining variable 1 yields two productions.
        assert_eq!(
            display_items(
                inline_map.inlined_items(ParseItem::Normal {
                    variable_index: 0,
                    production_index: 0,
                    step_index: 1
                }),
                &grammar,
                &inline_map
            ),
            Some(vec![
                "terminal-10 • terminal-12 terminal-13 terminal-11".to_string(),
                "terminal-10 • terminal-14 terminal-11".to_string(),
            ])
        );
    }

    #[test]
    fn test_nested_inlining() {
        let grammar = SyntaxGrammar {
            variables: vec![
                SyntaxVariable {
                    name: "var0".to_string(),
                    kind: VariableType::Named,
                    productions: vec![
                        Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(10)),
                                ProductionStep::new(Symbol::non_terminal(1)), // inlined
                                ProductionStep::new(Symbol::terminal(11)),
                                ProductionStep::new(Symbol::non_terminal(2)), // inlined
                                ProductionStep::new(Symbol::terminal(12)),
                            ],
                        },
                    ],
                },
                SyntaxVariable {
                    name: "var1".to_string(),
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
                    name: "var2".to_string(),
                    kind: VariableType::Named,
                    productions: vec![Production {
                        dynamic_precedence: 0,
                        steps: vec![ProductionStep::new(Symbol::terminal(15))],
                    }],
                },
                SyntaxVariable {
                    name: "var3".to_string(),
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

        let inline_map = InlinedProductionMap::new(&grammar);

        let items = inline_map.inlined_items(ParseItem::Normal {
            variable_index: 0,
            production_index: 0,
            step_index: 1
        }).unwrap().collect::<Vec<_>>();

        assert_eq!(
            display_items(Some(items.iter().cloned()), &grammar, &inline_map),
            Some(vec![
                "terminal-10 • terminal-13 terminal-11 non-terminal-2 terminal-12".to_string(),
                "terminal-10 • terminal-16 terminal-14 terminal-11 non-terminal-2 terminal-12".to_string()
            ])
        );

        let item = items[0].successor().successor();
        assert_eq!(
            display_items(Some([item].iter().cloned()), &grammar, &inline_map),
            Some(vec![
                "terminal-10 terminal-13 terminal-11 • non-terminal-2 terminal-12".to_string(),
            ])
        );

        assert_eq!(
            display_items(inline_map.inlined_items(item), &grammar, &inline_map),
            Some(vec![
                "terminal-10 terminal-13 terminal-11 • terminal-15 terminal-12".to_string(),
            ])
        );
    }

    fn display_items(
        items: Option<impl Iterator<Item = ParseItem>>,
        grammar: &SyntaxGrammar,
        inline_map: &InlinedProductionMap,
    ) -> Option<Vec<String>> {
        items.map(|items| {
            items
                .map(|item| format!("{}", item.with(grammar, inline_map)))
                .collect()
        })
    }
}
