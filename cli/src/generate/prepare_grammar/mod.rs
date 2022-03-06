mod expand_repeats;
mod expand_tokens;
mod extract_default_aliases;
mod extract_tokens;
mod flatten_grammar;
mod intern_symbols;
mod process_inlines;

pub(crate) use self::expand_tokens::expand_tokens;

use self::expand_repeats::expand_repeats;
use self::extract_default_aliases::extract_default_aliases;
use self::extract_tokens::extract_tokens;
use self::flatten_grammar::flatten_grammar;
use self::intern_symbols::intern_symbols;
use self::process_inlines::process_inlines;
use super::grammars::{
    ExternalToken, InlinedProductionMap, InputGrammar, LexicalGrammar, PrecedenceEntry,
    SyntaxGrammar, Variable,
};
use super::rules::{AliasMap, Precedence, Rule, Symbol};
use anyhow::{anyhow, Result};
use std::{
    cmp::Ordering,
    collections::{hash_map, HashMap, HashSet},
    mem,
};

pub(crate) struct IntermediateGrammar<T, U> {
    variables: Vec<Variable>,
    extra_symbols: Vec<T>,
    expected_conflicts: Vec<Vec<Symbol>>,
    precedence_orderings: Vec<Vec<PrecedenceEntry>>,
    external_tokens: Vec<U>,
    variables_to_inline: Vec<Symbol>,
    supertype_symbols: Vec<Symbol>,
    word_token: Option<Symbol>,
}

pub(crate) type InternedGrammar = IntermediateGrammar<Rule, Variable>;

pub(crate) type ExtractedSyntaxGrammar = IntermediateGrammar<Symbol, ExternalToken>;

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct ExtractedLexicalGrammar {
    pub variables: Vec<Variable>,
    pub separators: Vec<Rule>,
}

impl<T, U> Default for IntermediateGrammar<T, U> {
    fn default() -> Self {
        Self {
            variables: Default::default(),
            extra_symbols: Default::default(),
            expected_conflicts: Default::default(),
            precedence_orderings: Default::default(),
            external_tokens: Default::default(),
            variables_to_inline: Default::default(),
            supertype_symbols: Default::default(),
            word_token: Default::default(),
        }
    }
}

/// Transform an input grammar into separate components that are ready
/// for parse table construction.
pub(crate) fn prepare_grammar(
    input_grammar: &InputGrammar,
) -> Result<(
    SyntaxGrammar,
    LexicalGrammar,
    InlinedProductionMap,
    AliasMap,
)> {
    validate_precedences(input_grammar)?;

    let interned_grammar = intern_symbols(input_grammar)?;
    let (syntax_grammar, lexical_grammar) = extract_tokens(interned_grammar)?;
    let syntax_grammar = expand_repeats(syntax_grammar);
    let mut syntax_grammar = flatten_grammar(syntax_grammar)?;
    let lexical_grammar = expand_tokens(lexical_grammar)?;
    let default_aliases = extract_default_aliases(&mut syntax_grammar, &lexical_grammar);
    let inlines = process_inlines(&syntax_grammar, &lexical_grammar)?;
    Ok((syntax_grammar, lexical_grammar, inlines, default_aliases))
}

/// Check that all of the named precedences used in the grammar are declared
/// within the `precedences` lists, and also that there are no conflicting
/// precedence orderings declared in those lists.
fn validate_precedences(grammar: &InputGrammar) -> Result<()> {
    // For any two precedence names `a` and `b`, if `a` comes before `b`
    // in some list, then it cannot come *after* `b` in any list.
    let mut pairs = HashMap::new();
    for list in &grammar.precedence_orderings {
        for (i, mut entry1) in list.iter().enumerate() {
            for mut entry2 in list.iter().skip(i + 1) {
                if entry2 == entry1 {
                    continue;
                }
                let mut ordering = Ordering::Greater;
                if entry1 > entry2 {
                    ordering = Ordering::Less;
                    mem::swap(&mut entry1, &mut entry2);
                }
                match pairs.entry((entry1, entry2)) {
                    hash_map::Entry::Vacant(e) => {
                        e.insert(ordering);
                    }
                    hash_map::Entry::Occupied(e) => {
                        if e.get() != &ordering {
                            return Err(anyhow!(
                                "Conflicting orderings for precedences {} and {}",
                                entry1,
                                entry2
                            ));
                        }
                    }
                }
            }
        }
    }

    // Check that no rule contains a named precedence that is not present in
    // any of the `precedences` lists.
    fn validate(rule_name: &str, rule: &Rule, names: &HashSet<&String>) -> Result<()> {
        match rule {
            Rule::Repeat(rule) => validate(rule_name, rule, names),
            Rule::Seq(elements) | Rule::Choice(elements) => elements
                .iter()
                .map(|e| validate(rule_name, e, names))
                .collect(),
            Rule::Metadata { rule, params } => {
                if let Precedence::Name(n) = &params.precedence {
                    if !names.contains(n) {
                        return Err(anyhow!(
                            "Undeclared precedence '{}' in rule '{}'",
                            n,
                            rule_name
                        ));
                    }
                }
                validate(rule_name, rule, names)?;
                Ok(())
            }
            _ => Ok(()),
        }
    }

    let precedence_names = grammar
        .precedence_orderings
        .iter()
        .flat_map(|l| l.iter())
        .filter_map(|p| {
            if let PrecedenceEntry::Name(n) = p {
                Some(n)
            } else {
                None
            }
        })
        .collect::<HashSet<&String>>();
    for variable in &grammar.variables {
        validate(&variable.name, &variable.rule, &precedence_names)?;
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::grammars::{InputGrammar, Variable, VariableType};

    #[test]
    fn test_validate_precedences_with_undeclared_precedence() {
        let grammar = InputGrammar {
            precedence_orderings: vec![
                vec![
                    PrecedenceEntry::Name("a".to_string()),
                    PrecedenceEntry::Name("b".to_string()),
                ],
                vec![
                    PrecedenceEntry::Name("b".to_string()),
                    PrecedenceEntry::Name("c".to_string()),
                    PrecedenceEntry::Name("d".to_string()),
                ],
            ],
            variables: vec![
                Variable {
                    name: "v1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::Seq(vec![
                        Rule::prec_left(Precedence::Name("b".to_string()), Rule::string("w")),
                        Rule::prec(Precedence::Name("c".to_string()), Rule::string("x")),
                    ]),
                },
                Variable {
                    name: "v2".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::repeat(Rule::Choice(vec![
                        Rule::prec_left(Precedence::Name("omg".to_string()), Rule::string("y")),
                        Rule::prec(Precedence::Name("c".to_string()), Rule::string("z")),
                    ])),
                },
            ],
            ..Default::default()
        };

        let result = validate_precedences(&grammar);
        assert_eq!(
            result.unwrap_err().to_string(),
            "Undeclared precedence 'omg' in rule 'v2'",
        );
    }

    #[test]
    fn test_validate_precedences_with_conflicting_order() {
        let grammar = InputGrammar {
            precedence_orderings: vec![
                vec![
                    PrecedenceEntry::Name("a".to_string()),
                    PrecedenceEntry::Name("b".to_string()),
                ],
                vec![
                    PrecedenceEntry::Name("b".to_string()),
                    PrecedenceEntry::Name("c".to_string()),
                    PrecedenceEntry::Name("a".to_string()),
                ],
            ],
            variables: vec![
                Variable {
                    name: "v1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::Seq(vec![
                        Rule::prec_left(Precedence::Name("b".to_string()), Rule::string("w")),
                        Rule::prec(Precedence::Name("c".to_string()), Rule::string("x")),
                    ]),
                },
                Variable {
                    name: "v2".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::repeat(Rule::Choice(vec![
                        Rule::prec_left(Precedence::Name("a".to_string()), Rule::string("y")),
                        Rule::prec(Precedence::Name("c".to_string()), Rule::string("z")),
                    ])),
                },
            ],
            ..Default::default()
        };

        let result = validate_precedences(&grammar);
        assert_eq!(
            result.unwrap_err().to_string(),
            "Conflicting orderings for precedences 'a' and 'b'",
        );
    }
}
