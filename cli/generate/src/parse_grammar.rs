use std::collections::HashSet;

use anyhow::{anyhow, Result};
use serde::Deserialize;
use serde_json::{Map, Value};

use super::{
    grammars::{InputGrammar, PrecedenceEntry, Variable, VariableType},
    rules::{Precedence, Rule},
};

#[derive(Deserialize)]
#[serde(tag = "type")]
#[allow(non_camel_case_types)]
#[allow(clippy::upper_case_acronyms)]
enum RuleJSON {
    ALIAS {
        content: Box<RuleJSON>,
        named: bool,
        value: String,
    },
    BLANK,
    STRING {
        value: String,
    },
    PATTERN {
        value: String,
        flags: Option<String>,
    },
    SYMBOL {
        name: String,
    },
    CHOICE {
        members: Vec<RuleJSON>,
    },
    FIELD {
        name: String,
        content: Box<RuleJSON>,
    },
    SEQ {
        members: Vec<RuleJSON>,
    },
    REPEAT {
        content: Box<RuleJSON>,
    },
    REPEAT1 {
        content: Box<RuleJSON>,
    },
    PREC_DYNAMIC {
        value: i32,
        content: Box<RuleJSON>,
    },
    PREC_LEFT {
        value: PrecedenceValueJSON,
        content: Box<RuleJSON>,
    },
    PREC_RIGHT {
        value: PrecedenceValueJSON,
        content: Box<RuleJSON>,
    },
    PREC {
        value: PrecedenceValueJSON,
        content: Box<RuleJSON>,
    },
    TOKEN {
        content: Box<RuleJSON>,
    },
    IMMEDIATE_TOKEN {
        content: Box<RuleJSON>,
    },
}

#[derive(Deserialize)]
#[serde(untagged)]
enum PrecedenceValueJSON {
    Integer(i32),
    Name(String),
}

#[derive(Deserialize)]
pub struct GrammarJSON {
    pub name: String,
    rules: Map<String, Value>,
    #[serde(default)]
    precedences: Vec<Vec<RuleJSON>>,
    #[serde(default)]
    conflicts: Vec<Vec<String>>,
    #[serde(default)]
    externals: Vec<RuleJSON>,
    #[serde(default)]
    extras: Vec<RuleJSON>,
    #[serde(default)]
    inline: Vec<String>,
    #[serde(default)]
    supertypes: Vec<String>,
    word: Option<String>,
}

fn rule_is_referenced(rule: &Rule, target: &str) -> bool {
    match rule {
        Rule::NamedSymbol(name) => name == target,
        Rule::Choice(rules) | Rule::Seq(rules) => {
            rules.iter().any(|r| rule_is_referenced(r, target))
        }
        Rule::Metadata { rule, .. } => rule_is_referenced(rule, target),
        Rule::Repeat(inner) => rule_is_referenced(inner, target),
        Rule::Blank | Rule::String(_) | Rule::Pattern(_, _) | Rule::Symbol(_) => false,
    }
}

fn variable_is_used(
    grammar_rules: &[(String, Rule)],
    other_rules: (&[Rule], &[Rule]),
    target_name: &str,
    in_progress: &mut HashSet<String>,
) -> bool {
    let root = &grammar_rules.first().unwrap().0;
    if target_name == root {
        return true;
    }

    if other_rules
        .0
        .iter()
        .chain(other_rules.1.iter())
        .any(|rule| rule_is_referenced(rule, target_name))
    {
        return true;
    }

    in_progress.insert(target_name.to_string());
    let result = grammar_rules
        .iter()
        .filter(|(key, _)| *key != target_name)
        .any(|(name, rule)| {
            if !rule_is_referenced(rule, target_name) || in_progress.contains(name) {
                return false;
            }
            variable_is_used(grammar_rules, other_rules, name, in_progress)
        });
    in_progress.remove(target_name);

    result
}

pub(crate) fn parse_grammar(input: &str) -> Result<InputGrammar> {
    let mut grammar_json = serde_json::from_str::<GrammarJSON>(input)?;

    let mut extra_symbols =
        grammar_json
            .extras
            .into_iter()
            .try_fold(Vec::new(), |mut acc, item| {
                let rule = parse_rule(item);
                if let Rule::String(ref value) = rule {
                    if value.is_empty() {
                        return Err(anyhow!(
                            "Rules in the `extras` array must not contain empty strings"
                        ));
                    }
                }
                acc.push(rule);
                Ok(acc)
            })?;

    let mut external_tokens = grammar_json
        .externals
        .into_iter()
        .map(parse_rule)
        .collect::<Vec<_>>();

    let mut precedence_orderings = Vec::with_capacity(grammar_json.precedences.len());
    for list in grammar_json.precedences {
        let mut ordering = Vec::with_capacity(list.len());
        for entry in list {
            ordering.push(match entry {
                RuleJSON::STRING { value } => PrecedenceEntry::Name(value),
                RuleJSON::SYMBOL { name } => PrecedenceEntry::Symbol(name),
                _ => {
                    return Err(anyhow!(
                        "Invalid rule in precedences array. Only strings and symbols are allowed"
                    ))
                }
            });
        }
        precedence_orderings.push(ordering);
    }

    let mut variables = Vec::with_capacity(grammar_json.rules.len());

    let rules = grammar_json
        .rules
        .into_iter()
        .map(|(n, r)| Ok((n, parse_rule(serde_json::from_value(r)?))))
        .collect::<Result<Vec<_>>>()?;

    let mut in_progress = HashSet::new();

    for (name, rule) in &rules {
        if !variable_is_used(
            &rules,
            (&extra_symbols, &external_tokens),
            name,
            &mut in_progress,
        ) && grammar_json.word.as_ref().is_some_and(|w| w != name)
        {
            grammar_json.conflicts.retain(|r| !r.contains(name));
            grammar_json.supertypes.retain(|r| r != name);
            grammar_json.inline.retain(|r| r != name);
            extra_symbols.retain(|r| !rule_is_referenced(r, name));
            external_tokens.retain(|r| !rule_is_referenced(r, name));
            precedence_orderings.retain(|r| {
                !r.iter().any(|e| {
                    let PrecedenceEntry::Symbol(s) = e else {
                        return false;
                    };
                    s == name
                })
            });
            continue;
        }
        variables.push(Variable {
            name: name.clone(),
            kind: VariableType::Named,
            rule: rule.clone(),
        });
    }

    Ok(InputGrammar {
        name: grammar_json.name,
        word_token: grammar_json.word,
        expected_conflicts: grammar_json.conflicts,
        supertype_symbols: grammar_json.supertypes,
        variables_to_inline: grammar_json.inline,
        precedence_orderings,
        variables,
        extra_symbols,
        external_tokens,
    })
}

fn parse_rule(json: RuleJSON) -> Rule {
    match json {
        RuleJSON::ALIAS {
            content,
            value,
            named,
        } => Rule::alias(parse_rule(*content), value, named),
        RuleJSON::BLANK => Rule::Blank,
        RuleJSON::STRING { value } => Rule::String(value),
        RuleJSON::PATTERN { value, flags } => Rule::Pattern(
            value,
            flags.map_or(String::new(), |f| {
                f.matches(|c| {
                    if c == 'i' {
                        true
                    } else {
                        // silently ignore unicode flags
                        if c != 'u' && c != 'v' {
                            eprintln!("Warning: unsupported flag {c}");
                        }
                        false
                    }
                })
                .collect()
            }),
        ),
        RuleJSON::SYMBOL { name } => Rule::NamedSymbol(name),
        RuleJSON::CHOICE { members } => Rule::choice(members.into_iter().map(parse_rule).collect()),
        RuleJSON::FIELD { content, name } => Rule::field(name, parse_rule(*content)),
        RuleJSON::SEQ { members } => Rule::seq(members.into_iter().map(parse_rule).collect()),
        RuleJSON::REPEAT1 { content } => Rule::repeat(parse_rule(*content)),
        RuleJSON::REPEAT { content } => {
            Rule::choice(vec![Rule::repeat(parse_rule(*content)), Rule::Blank])
        }
        RuleJSON::PREC { value, content } => Rule::prec(value.into(), parse_rule(*content)),
        RuleJSON::PREC_LEFT { value, content } => {
            Rule::prec_left(value.into(), parse_rule(*content))
        }
        RuleJSON::PREC_RIGHT { value, content } => {
            Rule::prec_right(value.into(), parse_rule(*content))
        }
        RuleJSON::PREC_DYNAMIC { value, content } => {
            Rule::prec_dynamic(value, parse_rule(*content))
        }
        RuleJSON::TOKEN { content } => Rule::token(parse_rule(*content)),
        RuleJSON::IMMEDIATE_TOKEN { content } => Rule::immediate_token(parse_rule(*content)),
    }
}

impl From<PrecedenceValueJSON> for Precedence {
    fn from(val: PrecedenceValueJSON) -> Self {
        match val {
            PrecedenceValueJSON::Integer(i) => Self::Integer(i),
            PrecedenceValueJSON::Name(i) => Self::Name(i),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_grammar() {
        let grammar = parse_grammar(
            r#"{
            "name": "my_lang",
            "rules": {
                "file": {
                    "type": "REPEAT1",
                    "content": {
                        "type": "SYMBOL",
                        "name": "statement"
                    }
                },
                "statement": {
                    "type": "STRING",
                    "value": "foo"
                }
            }
        }"#,
        )
        .unwrap();

        assert_eq!(grammar.name, "my_lang");
        assert_eq!(
            grammar.variables,
            vec![
                Variable {
                    name: "file".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::repeat(Rule::NamedSymbol("statement".to_string()))
                },
                Variable {
                    name: "statement".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::String("foo".to_string())
                },
            ]
        );
    }
}
