use crate::error::{Error, Result};
use crate::rules::{Rule, Symbol};
use crate::grammars::{InputGrammar, InputVariable, VariableType};
use std::rc::Rc;
use super::InternedGrammar;

pub(super) fn intern_symbols(grammar: &InputGrammar) -> Result<InternedGrammar> {
    let interner = Interner { grammar };

    if variable_type_for_name(&grammar.variables[0].name) == VariableType::Hidden {
        return Err(Error::GrammarError("Grammar's start rule must be visible".to_string()));
    }

    let mut variables = Vec::with_capacity(grammar.variables.len());
    for variable in grammar.variables.iter() {
        variables.push(InputVariable {
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
        external_tokens.push(InputVariable { name, kind, rule });
    }

    let mut extra_tokens = Vec::with_capacity(grammar.extra_tokens.len());
    for extra_token in grammar.extra_tokens.iter() {
        extra_tokens.push(interner.intern_rule(extra_token)?);
    }

    let mut expected_conflicts = Vec::new();
    for conflict in grammar.expected_conflicts.iter() {
        let mut interned_conflict = Vec::with_capacity(conflict.len());
        for name in conflict {
            interned_conflict.push(interner
                .intern_name(&name)
                .ok_or_else(|| symbol_error(name))?
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
        word_token = Some(interner
            .intern_name(&name)
            .ok_or_else(|| symbol_error(&name))?
        );
    }

    Ok(InternedGrammar {
        variables,
        external_tokens,
        extra_tokens,
        expected_conflicts,
        variables_to_inline,
        word_token,
    })
}

struct Interner<'a> {
    grammar: &'a InputGrammar
}

impl<'a> Interner<'a> {
    fn intern_rule(&self, rule: &Rule) -> Result<Rule> {
        match rule {
            Rule::Choice { elements } => {
                let mut result = Vec::with_capacity(elements.len());
                for element in elements {
                    result.push(self.intern_rule(element)?);
                }
                Ok(Rule::Choice { elements: result })
            },

            Rule::Seq { left, right } =>
                Ok(Rule::Seq {
                    left: Rc::new(self.intern_rule(left)?),
                    right: Rc::new(self.intern_rule(right)?),
                }),

            Rule::Repeat(content) =>
                Ok(Rule::Repeat(Rc::new(self.intern_rule(content)?))),

            Rule::Metadata { rule, params } =>
                Ok(Rule::Metadata {
                    rule: Rc::new(self.intern_rule(rule)?),
                    params: params.clone()
                }),

            Rule::NamedSymbol(name) => {
                if let Some(symbol) = self.intern_name(&name) {
                    Ok(Rule::Symbol(symbol))
                } else {
                    Err(symbol_error(name))
                }
            },

            _ => Ok(rule.clone())

        }
    }

    fn intern_name(&self, symbol: &str) -> Option<Symbol> {
        for (i, variable) in self.grammar.variables.iter().enumerate() {
            if variable.name == symbol {
                return Some(Symbol::non_terminal(i))
            }
        }

        for (i, external_token) in self.grammar.external_tokens.iter().enumerate() {
            if let Rule::NamedSymbol(name) = external_token {
                if name == symbol {
                    return Some(Symbol::external(i))
                }
            }
        }

        return None
    }
}

fn symbol_error(name: &str) -> Error {
    Error::SymbolError(format!("Undefined symbol '{}'", name))
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
            InputVariable::named("x", Rule::choice(vec![
                Rule::named("y"),
                Rule::named("_z"),
            ])),
            InputVariable::named("y", Rule::named("_z")),
            InputVariable::named("_z", Rule::string("a")),
        ])).unwrap();

        assert_eq!(grammar.variables, vec![
            InputVariable::named("x", Rule::choice(vec![
                Rule::non_terminal(1),
                Rule::non_terminal(2),
            ])),
            InputVariable::named("y", Rule::non_terminal(2)),
            InputVariable::hidden("_z", Rule::string("a")),
        ]);
    }

    #[test]
    fn test_interning_external_token_names() {
        // Variable `y` is both an internal and an external token.
        // Variable `z` is just an external token.
        let mut input_grammar = build_grammar(vec![
            InputVariable::named("w", Rule::choice(vec![
                Rule::named("x"),
                Rule::named("y"),
                Rule::named("z"),
            ])),
            InputVariable::named("x", Rule::string("a")),
            InputVariable::named("y", Rule::string("b")),
        ]);
        input_grammar.external_tokens.extend(vec![
            Rule::named("y"),
            Rule::named("z"),
        ]);

        let grammar = intern_symbols(&input_grammar).unwrap();

        // Variable `y` is referred to by its internal index.
        // Variable `z` is referred to by its external index.
        assert_eq!(grammar.variables, vec![
            InputVariable::named("w", Rule::choice(vec![
                Rule::non_terminal(1),
                Rule::non_terminal(2),
                Rule::external(1),
            ])),
            InputVariable::named("x", Rule::string("a")),
            InputVariable::named("y", Rule::string("b")),
        ]);

        // The external token for `y` refers back to its internal index.
        assert_eq!(grammar.external_tokens, vec![
            InputVariable::named("y", Rule::non_terminal(2)),
            InputVariable::named("z", Rule::external(1)),
        ]);
    }

    #[test]
    fn test_grammar_with_undefined_symbols() {
        let result = intern_symbols(&build_grammar(vec![
            InputVariable::named("x", Rule::named("y")),
        ]));

        match result {
            Err(Error::SymbolError(message)) => assert_eq!(message, "Undefined symbol 'y'"),
            _ => panic!("Expected an error but got none"),
        }
    }

    fn build_grammar(variables: Vec<InputVariable>) -> InputGrammar {
        InputGrammar {
            variables,
            name: "the_language".to_string(),
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
        }
    }
}
