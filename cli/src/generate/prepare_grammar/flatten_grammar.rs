use crate::generate::{
    grammars::{Production, ProductionStep, SyntaxGrammar, SyntaxVariable, Variable},
    prepare_grammar::ExtractedSyntaxGrammar,
    rules::{Alias, Associativity, Precedence, Rule, Symbol, TokenSet},
};
use anyhow::{anyhow, Result};

struct RuleFlattener {
    production: Production,
    precedence_stack: Vec<Precedence>,
    associativity_stack: Vec<Associativity>,
    reserved_word_stack: Vec<TokenSet>,
    alias_stack: Vec<Alias>,
    field_name_stack: Vec<String>,
}

impl RuleFlattener {
    fn new() -> Self {
        Self {
            production: Production {
                steps: Vec::new(),
                dynamic_precedence: 0,
            },
            precedence_stack: Vec::new(),
            associativity_stack: Vec::new(),
            reserved_word_stack: Vec::new(),
            alias_stack: Vec::new(),
            field_name_stack: Vec::new(),
        }
    }

    fn flatten_variable(&mut self, variable: Variable) -> Result<SyntaxVariable> {
        let mut productions = Vec::new();
        for rule in extract_choices(variable.rule) {
            let production = self.flatten_rule(rule);
            if !productions.contains(&production) {
                productions.push(production);
            }
        }
        Ok(SyntaxVariable {
            name: variable.name,
            kind: variable.kind,
            productions,
        })
    }

    fn flatten_rule(&mut self, rule: Rule) -> Production {
        self.production = Production::default();
        self.alias_stack.clear();
        self.reserved_word_stack.clear();
        self.precedence_stack.clear();
        self.associativity_stack.clear();
        self.field_name_stack.clear();
        self.apply(rule, true);
        self.production.clone()
    }

    fn apply(&mut self, rule: Rule, at_end: bool) -> bool {
        match rule {
            Rule::Seq(members) => {
                let mut result = false;
                let last_index = members.len() - 1;
                for (i, member) in members.into_iter().enumerate() {
                    result |= self.apply(member, i == last_index && at_end);
                }
                result
            }
            Rule::Metadata { rule, params } => {
                let mut has_precedence = false;
                if !params.precedence.is_none() {
                    has_precedence = true;
                    self.precedence_stack.push(params.precedence);
                }

                let mut has_associativity = false;
                if let Some(associativity) = params.associativity {
                    has_associativity = true;
                    self.associativity_stack.push(associativity);
                }

                let mut has_alias = false;
                if let Some(alias) = params.alias {
                    has_alias = true;
                    self.alias_stack.push(alias);
                }

                let mut has_field_name = false;
                if let Some(field_name) = params.field_name {
                    has_field_name = true;
                    self.field_name_stack.push(field_name);
                }

                if params.dynamic_precedence.abs() > self.production.dynamic_precedence.abs() {
                    self.production.dynamic_precedence = params.dynamic_precedence;
                }

                let did_push = self.apply(*rule, at_end);

                if has_precedence {
                    self.precedence_stack.pop();
                    if did_push && !at_end {
                        self.production.steps.last_mut().unwrap().precedence = self
                            .precedence_stack
                            .last()
                            .cloned()
                            .unwrap_or(Precedence::None);
                    }
                }

                if has_associativity {
                    self.associativity_stack.pop();
                    if did_push && !at_end {
                        self.production.steps.last_mut().unwrap().associativity =
                            self.associativity_stack.last().cloned();
                    }
                }

                if has_alias {
                    self.alias_stack.pop();
                }

                if has_field_name {
                    self.field_name_stack.pop();
                }

                did_push
            }
            Rule::Reserved {
                rule,
                reserved_words,
            } => {
                self.reserved_word_stack
                    .push(rules_to_token_set(reserved_words));
                let did_push = self.apply(*rule, at_end);
                self.reserved_word_stack.pop();
                did_push
            }
            Rule::Symbol(symbol) => {
                self.production.steps.push(ProductionStep {
                    symbol,
                    precedence: self
                        .precedence_stack
                        .last()
                        .cloned()
                        .unwrap_or(Precedence::None),
                    associativity: self.associativity_stack.last().cloned(),
                    reserved_words: self.reserved_word_stack.last().cloned().map(Box::new),
                    alias: self.alias_stack.last().cloned(),
                    field_name: self.field_name_stack.last().cloned(),
                });
                true
            }
            _ => false,
        }
    }
}

fn rules_to_token_set(rules: Vec<Rule>) -> TokenSet {
    rules
        .into_iter()
        .filter_map(|rule| {
            if let Rule::Symbol(s) = rule {
                Some(s)
            } else {
                None
            }
        })
        .collect()
}

fn extract_choices(rule: Rule) -> Vec<Rule> {
    match rule {
        Rule::Seq(elements) => {
            let mut result = vec![Rule::Blank];
            for element in elements {
                let extraction = extract_choices(element);
                let mut next_result = Vec::new();
                for entry in result {
                    for extraction_entry in extraction.iter() {
                        next_result.push(Rule::Seq(vec![entry.clone(), extraction_entry.clone()]));
                    }
                }
                result = next_result;
            }
            result
        }
        Rule::Choice(elements) => {
            let mut result = Vec::new();
            for element in elements {
                for rule in extract_choices(element) {
                    result.push(rule);
                }
            }
            result
        }
        Rule::Metadata { rule, params } => extract_choices(*rule)
            .into_iter()
            .map(|rule| Rule::Metadata {
                rule: Box::new(rule),
                params: params.clone(),
            })
            .collect(),
        Rule::Reserved {
            rule,
            reserved_words,
        } => extract_choices(*rule)
            .into_iter()
            .map(|rule| Rule::Reserved {
                rule: Box::new(rule),
                reserved_words: reserved_words.clone(),
            })
            .collect(),
        _ => vec![rule],
    }
}

fn symbol_is_used(variables: &Vec<SyntaxVariable>, symbol: Symbol) -> bool {
    for variable in variables {
        for production in &variable.productions {
            for step in &production.steps {
                if step.symbol == symbol {
                    return true;
                }
            }
        }
    }
    false
}

pub(super) fn flatten_grammar(grammar: ExtractedSyntaxGrammar) -> Result<SyntaxGrammar> {
    let mut flattener = RuleFlattener::new();
    let variables = grammar
        .variables
        .into_iter()
        .map(|variable| flattener.flatten_variable(variable))
        .collect::<Result<Vec<_>>>()?;

    for (i, variable) in variables.iter().enumerate() {
        for production in &variable.productions {
            if production.steps.is_empty() && symbol_is_used(&variables, Symbol::non_terminal(i)) {
                return Err(anyhow!(
                    "The rule `{}` matches the empty string.

Tree-sitter does not support syntactic rules that match the empty string
unless they are used only as the grammar's start rule.
",
                    variable.name
                ));
            }
        }
    }
    Ok(SyntaxGrammar {
        extra_symbols: grammar.extra_symbols,
        expected_conflicts: grammar.expected_conflicts,
        variables_to_inline: grammar.variables_to_inline,
        precedence_orderings: grammar.precedence_orderings,
        external_tokens: grammar.external_tokens,
        supertype_symbols: grammar.supertype_symbols,
        word_token: grammar.word_token,
        reserved_words: grammar.reserved_words.into_iter().collect(),
        variables,
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::grammars::VariableType;
    use crate::generate::rules::Symbol;

    #[test]
    fn test_flatten_grammar() {
        let mut flattener = RuleFlattener::new();
        let result = flattener
            .flatten_variable(Variable {
                name: "test".to_string(),
                kind: VariableType::Named,
                rule: Rule::seq(vec![
                    Rule::non_terminal(1),
                    Rule::prec_left(
                        Precedence::Integer(101),
                        Rule::seq(vec![
                            Rule::non_terminal(2),
                            Rule::choice(vec![
                                Rule::prec_right(
                                    Precedence::Integer(102),
                                    Rule::seq(vec![Rule::non_terminal(3), Rule::non_terminal(4)]),
                                ),
                                Rule::non_terminal(5),
                            ]),
                            Rule::non_terminal(6),
                        ]),
                    ),
                    Rule::non_terminal(7),
                ]),
            })
            .unwrap();

        assert_eq!(
            result.productions,
            vec![
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::non_terminal(1)),
                        ProductionStep::new(Symbol::non_terminal(2))
                            .with_prec(Precedence::Integer(101), Some(Associativity::Left)),
                        ProductionStep::new(Symbol::non_terminal(3))
                            .with_prec(Precedence::Integer(102), Some(Associativity::Right)),
                        ProductionStep::new(Symbol::non_terminal(4))
                            .with_prec(Precedence::Integer(101), Some(Associativity::Left)),
                        ProductionStep::new(Symbol::non_terminal(6)),
                        ProductionStep::new(Symbol::non_terminal(7)),
                    ]
                },
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::non_terminal(1)),
                        ProductionStep::new(Symbol::non_terminal(2))
                            .with_prec(Precedence::Integer(101), Some(Associativity::Left)),
                        ProductionStep::new(Symbol::non_terminal(5))
                            .with_prec(Precedence::Integer(101), Some(Associativity::Left)),
                        ProductionStep::new(Symbol::non_terminal(6)),
                        ProductionStep::new(Symbol::non_terminal(7)),
                    ]
                },
            ]
        );
    }

    #[test]
    fn test_flatten_grammar_with_maximum_dynamic_precedence() {
        let mut flattener = RuleFlattener::new();
        let result = flattener
            .flatten_variable(Variable {
                name: "test".to_string(),
                kind: VariableType::Named,
                rule: Rule::seq(vec![
                    Rule::non_terminal(1),
                    Rule::prec_dynamic(
                        101,
                        Rule::seq(vec![
                            Rule::non_terminal(2),
                            Rule::choice(vec![
                                Rule::prec_dynamic(
                                    102,
                                    Rule::seq(vec![Rule::non_terminal(3), Rule::non_terminal(4)]),
                                ),
                                Rule::non_terminal(5),
                            ]),
                            Rule::non_terminal(6),
                        ]),
                    ),
                    Rule::non_terminal(7),
                ]),
            })
            .unwrap();

        assert_eq!(
            result.productions,
            vec![
                Production {
                    dynamic_precedence: 102,
                    steps: vec![
                        ProductionStep::new(Symbol::non_terminal(1)),
                        ProductionStep::new(Symbol::non_terminal(2)),
                        ProductionStep::new(Symbol::non_terminal(3)),
                        ProductionStep::new(Symbol::non_terminal(4)),
                        ProductionStep::new(Symbol::non_terminal(6)),
                        ProductionStep::new(Symbol::non_terminal(7)),
                    ],
                },
                Production {
                    dynamic_precedence: 101,
                    steps: vec![
                        ProductionStep::new(Symbol::non_terminal(1)),
                        ProductionStep::new(Symbol::non_terminal(2)),
                        ProductionStep::new(Symbol::non_terminal(5)),
                        ProductionStep::new(Symbol::non_terminal(6)),
                        ProductionStep::new(Symbol::non_terminal(7)),
                    ],
                },
            ]
        );
    }

    #[test]
    fn test_flatten_grammar_with_final_precedence() {
        let mut flattener = RuleFlattener::new();
        let result = flattener
            .flatten_variable(Variable {
                name: "test".to_string(),
                kind: VariableType::Named,
                rule: Rule::prec_left(
                    Precedence::Integer(101),
                    Rule::seq(vec![Rule::non_terminal(1), Rule::non_terminal(2)]),
                ),
            })
            .unwrap();

        assert_eq!(
            result.productions,
            vec![Production {
                dynamic_precedence: 0,
                steps: vec![
                    ProductionStep::new(Symbol::non_terminal(1))
                        .with_prec(Precedence::Integer(101), Some(Associativity::Left)),
                    ProductionStep::new(Symbol::non_terminal(2))
                        .with_prec(Precedence::Integer(101), Some(Associativity::Left)),
                ]
            }]
        );

        let result = flattener
            .flatten_variable(Variable {
                name: "test".to_string(),
                kind: VariableType::Named,
                rule: Rule::prec_left(
                    Precedence::Integer(101),
                    Rule::seq(vec![Rule::non_terminal(1)]),
                ),
            })
            .unwrap();

        assert_eq!(
            result.productions,
            vec![Production {
                dynamic_precedence: 0,
                steps: vec![ProductionStep::new(Symbol::non_terminal(1))
                    .with_prec(Precedence::Integer(101), Some(Associativity::Left)),]
            }]
        );
    }

    #[test]
    fn test_flatten_grammar_with_field_names() {
        let mut flattener = RuleFlattener::new();
        let result = flattener
            .flatten_variable(Variable {
                name: "test".to_string(),
                kind: VariableType::Named,
                rule: Rule::seq(vec![
                    Rule::field("first-thing".to_string(), Rule::terminal(1)),
                    Rule::terminal(2),
                    Rule::choice(vec![
                        Rule::Blank,
                        Rule::field("second-thing".to_string(), Rule::terminal(3)),
                    ]),
                ]),
            })
            .unwrap();

        assert_eq!(
            result.productions,
            vec![
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::terminal(1)).with_field_name("first-thing"),
                        ProductionStep::new(Symbol::terminal(2))
                    ]
                },
                Production {
                    dynamic_precedence: 0,
                    steps: vec![
                        ProductionStep::new(Symbol::terminal(1)).with_field_name("first-thing"),
                        ProductionStep::new(Symbol::terminal(2)),
                        ProductionStep::new(Symbol::terminal(3)).with_field_name("second-thing"),
                    ]
                },
            ]
        );
    }
}
