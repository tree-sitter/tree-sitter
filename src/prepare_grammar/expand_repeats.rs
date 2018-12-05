use crate::rules::{Rule, Symbol};
use crate::grammars::{InputVariable, VariableType};
use std::collections::HashMap;
use std::mem;
use std::rc::Rc;
use super::ExtractedGrammar;

struct Expander {
    variable_name: String,
    repeat_count_in_variable: usize,
    preceding_symbol_count: usize,
    auxiliary_variables: Vec<InputVariable>,
    existing_repeats: HashMap<Rule, Symbol>
}

impl Expander {
    fn expand_variable(&mut self, variable: &mut InputVariable) {
        self.variable_name.clear();
        self.variable_name.push_str(&variable.name);
        self.repeat_count_in_variable = 0;
        let mut rule = Rule::Blank;
        mem::swap(&mut rule, &mut variable.rule);
        variable.rule = self.expand_rule(&rule);
    }

    fn expand_rule(&mut self, rule: &Rule) -> Rule {
        match rule {
            Rule::Choice { elements } =>
                Rule::Choice {
                    elements: elements.iter().map(|element| self.expand_rule(element)).collect()
                },

            Rule::Seq { left, right } =>
                Rule::Seq {
                    left: Rc::new(self.expand_rule(left)),
                    right: Rc::new(self.expand_rule(right)),
                },

            Rule::Repeat(content) => {
                let inner_rule = self.expand_rule(content);

                if let Some(existing_symbol) = self.existing_repeats.get(&inner_rule) {
                    return Rule::Symbol(*existing_symbol);
                }

                self.repeat_count_in_variable += 1;
                let rule_name = format!("{}_repeat{}", self.variable_name, self.repeat_count_in_variable);
                let repeat_symbol = Symbol::non_terminal(self.preceding_symbol_count + self.auxiliary_variables.len());
                let rc_symbol = Rc::new(Rule::Symbol(repeat_symbol));
                self.existing_repeats.insert(inner_rule.clone(), repeat_symbol);
                self.auxiliary_variables.push(InputVariable {
                    name: rule_name,
                    kind: VariableType::Auxiliary,
                    rule: Rule::Choice {
                        elements: vec![
                            Rule::Seq {
                                left: rc_symbol.clone(),
                                right: rc_symbol
                            },
                            inner_rule
                        ],
                    },
                });

                Rule::Symbol(repeat_symbol)
            }

            Rule::Metadata { rule, params } => Rule::Metadata {
                rule: Rc::new(self.expand_rule(rule)),
                params: params.clone()
            },

            _ => rule.clone()
        }
    }
}

pub(super) fn expand_repeats(mut grammar: ExtractedGrammar) -> ExtractedGrammar {
    let mut expander = Expander {
        variable_name: String::new(),
        repeat_count_in_variable: 0,
        preceding_symbol_count: grammar.variables.len(),
        auxiliary_variables: Vec::new(),
        existing_repeats: HashMap::new(),
    };

    for mut variable in grammar.variables.iter_mut() {
        expander.expand_variable(&mut variable);
    }

    grammar.variables.extend(expander.auxiliary_variables.into_iter());
    grammar
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_basic_repeat_expansion() {
        // Repeats nested inside of sequences and choices are expanded.
        let grammar = expand_repeats(build_grammar(vec![
            InputVariable::named("rule0", Rule::seq(vec![
                Rule::terminal(10),
                Rule::choice(vec![
                    Rule::repeat(Rule::terminal(11)),
                    Rule::repeat(Rule::terminal(12)),
                ]),
                Rule::terminal(13),
            ])),
        ]));

        assert_eq!(grammar.variables, vec![
            InputVariable::named("rule0", Rule::seq(vec![
                Rule::terminal(10),
                Rule::choice(vec![
                    Rule::non_terminal(1),
                    Rule::non_terminal(2),
                ]),
                Rule::terminal(13),
            ])),
            InputVariable::auxiliary("rule0_repeat1", Rule::choice(vec![
                Rule::seq(vec![
                    Rule::non_terminal(1),
                    Rule::non_terminal(1),
                ]),
                Rule::terminal(11),
            ])),
            InputVariable::auxiliary("rule0_repeat2", Rule::choice(vec![
                Rule::seq(vec![
                    Rule::non_terminal(2),
                    Rule::non_terminal(2),
                ]),
                Rule::terminal(12),
            ])),
        ]);
    }

    #[test]
    fn test_repeat_deduplication() {
        // Terminal 4 appears inside of a repeat in three different places.
        let grammar = expand_repeats(build_grammar(vec![
            InputVariable::named("rule0", Rule::choice(vec![
                Rule::seq(vec![ Rule::terminal(1), Rule::repeat(Rule::terminal(4)) ]),
                Rule::seq(vec![ Rule::terminal(2), Rule::repeat(Rule::terminal(4)) ]),
            ])),
            InputVariable::named("rule1", Rule::seq(vec![
                Rule::terminal(3),
                Rule::repeat(Rule::terminal(4)),
            ])),
        ]));

        // Only one auxiliary rule is created for repeating terminal 4.
        assert_eq!(grammar.variables, vec![
            InputVariable::named("rule0", Rule::choice(vec![
                Rule::seq(vec![ Rule::terminal(1), Rule::non_terminal(2) ]),
                Rule::seq(vec![ Rule::terminal(2), Rule::non_terminal(2) ]),
            ])),
            InputVariable::named("rule1", Rule::seq(vec![
                Rule::terminal(3),
                Rule::non_terminal(2),
            ])),
            InputVariable::auxiliary("rule0_repeat1", Rule::choice(vec![
                Rule::seq(vec![
                    Rule::non_terminal(2),
                    Rule::non_terminal(2),
                ]),
                Rule::terminal(4),
            ]))
        ]);
    }

    #[test]
    fn test_expansion_of_nested_repeats() {
        let grammar = expand_repeats(build_grammar(vec![
            InputVariable::named("rule0", Rule::seq(vec![
                Rule::terminal(10),
                Rule::repeat(Rule::seq(vec![
                    Rule::terminal(11),
                    Rule::repeat(Rule::terminal(12))
                ])),
            ])),
        ]));

        assert_eq!(grammar.variables, vec![
            InputVariable::named("rule0", Rule::seq(vec![
                Rule::terminal(10),
                Rule::non_terminal(2),
            ])),
            InputVariable::auxiliary("rule0_repeat1", Rule::choice(vec![
                Rule::seq(vec![
                    Rule::non_terminal(1),
                    Rule::non_terminal(1),
                ]),
                Rule::terminal(12),
            ])),
            InputVariable::auxiliary("rule0_repeat2", Rule::choice(vec![
                Rule::seq(vec![
                    Rule::non_terminal(2),
                    Rule::non_terminal(2),
                ]),
                Rule::seq(vec![
                    Rule::terminal(11),
                    Rule::non_terminal(1),
                ]),
            ])),
        ]);
    }

    fn build_grammar(variables: Vec<InputVariable>) -> ExtractedGrammar {
        ExtractedGrammar {
            variables,
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
        }
    }
}
