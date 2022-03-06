use super::InternedGrammar;
use crate::generate::grammars::{InputGrammar, Variable, VariableType};
use crate::generate::rules::{Rule, Symbol};
use anyhow::{anyhow, Result};

pub(super) fn intern_symbols(grammar: &InputGrammar) -> Result<InternedGrammar> {
    let interner = Interner { grammar };

    if variable_type_for_name(&grammar.variables[0].name) == VariableType::Hidden {
        return Err(anyhow!("A grammar's start rule must be visible."));
    }

    let mut variables = Vec::with_capacity(grammar.variables.len());
    for variable in grammar.variables.iter() {
        variables.push(Variable {
            name: variable.name.clone(),
            kind: variable_type_for_name(&variable.name),
            rule: interner.intern_rule(&variable.rule)?,
        });
    }

    let mut external_tokens = Vec::with_capacity(grammar.external_tokens.len());
    for external_token in grammar.external_tokens.iter() {
        let rule = interner.intern_rule(&external_token)?;
        let (name, kind) = if let Rule::NamedSymbol(name) = external_token {
            (name.clone(), variable_type_for_name(&name))
        } else {
            (String::new(), VariableType::Anonymous)
        };
        external_tokens.push(Variable { name, kind, rule });
    }

    let mut extra_symbols = Vec::with_capacity(grammar.extra_symbols.len());
    for extra_token in grammar.extra_symbols.iter() {
        extra_symbols.push(interner.intern_rule(extra_token)?);
    }

    let mut supertype_symbols = Vec::with_capacity(grammar.supertype_symbols.len());
    for supertype_symbol_name in grammar.supertype_symbols.iter() {
        supertype_symbols.push(
            interner
                .intern_name(supertype_symbol_name)
                .ok_or_else(|| anyhow!("Undefined symbol `{}`", supertype_symbol_name))?,
        );
    }

    let mut expected_conflicts = Vec::new();
    for conflict in grammar.expected_conflicts.iter() {
        let mut interned_conflict = Vec::with_capacity(conflict.len());
        for name in conflict {
            interned_conflict.push(
                interner
                    .intern_name(&name)
                    .ok_or_else(|| anyhow!("Undefined symbol `{}`", name))?,
            );
        }
        expected_conflicts.push(interned_conflict);
    }

    let mut variables_to_inline = Vec::new();
    for name in grammar.variables_to_inline.iter() {
        if let Some(symbol) = interner.intern_name(&name) {
            variables_to_inline.push(symbol);
        }
    }

    let mut word_token = None;
    if let Some(name) = grammar.word_token.as_ref() {
        word_token = Some(
            interner
                .intern_name(&name)
                .ok_or_else(|| anyhow!("Undefined symbol `{}`", &name))?,
        );
    }

    for (i, variable) in variables.iter_mut().enumerate() {
        if supertype_symbols.contains(&Symbol::non_terminal(i)) {
            variable.kind = VariableType::Hidden;
        }
    }

    Ok(InternedGrammar {
        variables,
        external_tokens,
        extra_symbols,
        expected_conflicts,
        variables_to_inline,
        supertype_symbols,
        word_token,
        precedence_orderings: grammar.precedence_orderings.clone(),
    })
}

struct Interner<'a> {
    grammar: &'a InputGrammar,
}

impl<'a> Interner<'a> {
    fn intern_rule(&self, rule: &Rule) -> Result<Rule> {
        match rule {
            Rule::Choice(elements) => {
                let mut result = Vec::with_capacity(elements.len());
                for element in elements {
                    result.push(self.intern_rule(element)?);
                }
                Ok(Rule::Choice(result))
            }
            Rule::Seq(elements) => {
                let mut result = Vec::with_capacity(elements.len());
                for element in elements {
                    result.push(self.intern_rule(element)?);
                }
                Ok(Rule::Seq(result))
            }
            Rule::Repeat(content) => Ok(Rule::Repeat(Box::new(self.intern_rule(content)?))),
            Rule::Metadata { rule, params } => Ok(Rule::Metadata {
                rule: Box::new(self.intern_rule(rule)?),
                params: params.clone(),
            }),

            Rule::NamedSymbol(name) => {
                if let Some(symbol) = self.intern_name(&name) {
                    Ok(Rule::Symbol(symbol))
                } else {
                    Err(anyhow!("Undefined symbol `{}`", name))
                }
            }

            _ => Ok(rule.clone()),
        }
    }

    fn intern_name(&self, symbol: &str) -> Option<Symbol> {
        for (i, variable) in self.grammar.variables.iter().enumerate() {
            if variable.name == symbol {
                return Some(Symbol::non_terminal(i));
            }
        }

        for (i, external_token) in self.grammar.external_tokens.iter().enumerate() {
            if let Rule::NamedSymbol(name) = external_token {
                if name == symbol {
                    return Some(Symbol::external(i));
                }
            }
        }

        return None;
    }
}

fn variable_type_for_name(name: &str) -> VariableType {
    if name.starts_with("_") {
        VariableType::Hidden
    } else {
        VariableType::Named
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_basic_repeat_expansion() {
        let grammar = intern_symbols(&build_grammar(vec![
            Variable::named("x", Rule::choice(vec![Rule::named("y"), Rule::named("_z")])),
            Variable::named("y", Rule::named("_z")),
            Variable::named("_z", Rule::string("a")),
        ]))
        .unwrap();

        assert_eq!(
            grammar.variables,
            vec![
                Variable::named(
                    "x",
                    Rule::choice(vec![Rule::non_terminal(1), Rule::non_terminal(2),])
                ),
                Variable::named("y", Rule::non_terminal(2)),
                Variable::hidden("_z", Rule::string("a")),
            ]
        );
    }

    #[test]
    fn test_interning_external_token_names() {
        // Variable `y` is both an internal and an external token.
        // Variable `z` is just an external token.
        let mut input_grammar = build_grammar(vec![
            Variable::named(
                "w",
                Rule::choice(vec![Rule::named("x"), Rule::named("y"), Rule::named("z")]),
            ),
            Variable::named("x", Rule::string("a")),
            Variable::named("y", Rule::string("b")),
        ]);
        input_grammar
            .external_tokens
            .extend(vec![Rule::named("y"), Rule::named("z")]);

        let grammar = intern_symbols(&input_grammar).unwrap();

        // Variable `y` is referred to by its internal index.
        // Variable `z` is referred to by its external index.
        assert_eq!(
            grammar.variables,
            vec![
                Variable::named(
                    "w",
                    Rule::choice(vec![
                        Rule::non_terminal(1),
                        Rule::non_terminal(2),
                        Rule::external(1),
                    ])
                ),
                Variable::named("x", Rule::string("a")),
                Variable::named("y", Rule::string("b")),
            ]
        );

        // The external token for `y` refers back to its internal index.
        assert_eq!(
            grammar.external_tokens,
            vec![
                Variable::named("y", Rule::non_terminal(2)),
                Variable::named("z", Rule::external(1)),
            ]
        );
    }

    #[test]
    fn test_grammar_with_undefined_symbols() {
        let result = intern_symbols(&build_grammar(vec![Variable::named("x", Rule::named("y"))]));

        match result {
            Err(e) => assert_eq!(e.to_string(), "Undefined symbol `y`"),
            _ => panic!("Expected an error but got none"),
        }
    }

    fn build_grammar(variables: Vec<Variable>) -> InputGrammar {
        InputGrammar {
            variables,
            name: "the_language".to_string(),
            ..Default::default()
        }
    }
}
