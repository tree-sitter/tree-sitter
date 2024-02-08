use super::grammars::{InputGrammar, PrecedenceEntry, Variable, VariableType};
use super::rules::{Precedence, Rule};
use anyhow::{anyhow, Result};
use serde::Deserialize;
use serde_json::{Map, Value};

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
pub(crate) struct GrammarJSON {
    pub(crate) name: String,
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

pub(crate) fn parse_grammar(input: &str) -> Result<InputGrammar> {
    let grammar_json: GrammarJSON = serde_json::from_str(input)?;

    let mut variables = Vec::with_capacity(grammar_json.rules.len());
    for (name, value) in grammar_json.rules {
        variables.push(Variable {
            name: name.clone(),
            kind: VariableType::Named,
            rule: parse_rule(serde_json::from_value(value)?),
        });
    }

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

    let extra_symbols = grammar_json.extras.into_iter().map(parse_rule).collect();
    let external_tokens = grammar_json.externals.into_iter().map(parse_rule).collect();

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
                f.chars()
                    .filter(|c| {
                        if *c == 'i' {
                            *c != 'u' // silently ignore unicode flag
                        } else {
                            eprintln!("Warning: unsupported flag {c}");
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
