use super::grammars::{InputGrammar, Variable, VariableType};
use super::rules::Rule;
use crate::error::Result;
use serde_derive::Deserialize;
use serde_json::{Map, Value};

#[derive(Deserialize)]
#[serde(tag = "type")]
#[allow(non_camel_case_types)]
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
        value: i32,
        content: Box<RuleJSON>,
    },
    PREC_RIGHT {
        value: i32,
        content: Box<RuleJSON>,
    },
    PREC {
        value: i32,
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
pub(crate) struct GrammarJSON {
    pub(crate) name: String,
    rules: Map<String, Value>,
    conflicts: Option<Vec<Vec<String>>>,
    externals: Option<Vec<RuleJSON>>,
    extras: Option<Vec<RuleJSON>>,
    inline: Option<Vec<String>>,
    supertypes: Option<Vec<String>>,
    word: Option<String>,
}

pub(crate) fn parse_grammar(input: &str) -> Result<InputGrammar> {
    let grammar_json: GrammarJSON = serde_json::from_str(&input)?;

    let mut variables = Vec::with_capacity(grammar_json.rules.len());
    for (name, value) in grammar_json.rules {
        variables.push(Variable {
            name: name.to_owned(),
            kind: VariableType::Named,
            rule: parse_rule(serde_json::from_value(value)?),
        })
    }

    let extra_symbols = grammar_json
        .extras
        .unwrap_or(Vec::new())
        .into_iter()
        .map(parse_rule)
        .collect();
    let external_tokens = grammar_json
        .externals
        .unwrap_or(Vec::new())
        .into_iter()
        .map(parse_rule)
        .collect();
    let expected_conflicts = grammar_json.conflicts.unwrap_or(Vec::new());
    let variables_to_inline = grammar_json.inline.unwrap_or(Vec::new());
    let supertype_symbols = grammar_json.supertypes.unwrap_or(Vec::new());

    Ok(InputGrammar {
        name: grammar_json.name,
        word_token: grammar_json.word,
        variables,
        extra_symbols,
        expected_conflicts,
        external_tokens,
        supertype_symbols,
        variables_to_inline,
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
        RuleJSON::PATTERN { value } => Rule::Pattern(value),
        RuleJSON::SYMBOL { name } => Rule::NamedSymbol(name),
        RuleJSON::CHOICE { members } => Rule::choice(members.into_iter().map(parse_rule).collect()),
        RuleJSON::FIELD { content, name } => Rule::field(name, parse_rule(*content)),
        RuleJSON::SEQ { members } => Rule::seq(members.into_iter().map(parse_rule).collect()),
        RuleJSON::REPEAT1 { content } => Rule::repeat(parse_rule(*content)),
        RuleJSON::REPEAT { content } => {
            Rule::choice(vec![Rule::repeat(parse_rule(*content)), Rule::Blank])
        }
        RuleJSON::PREC { value, content } => Rule::prec(value, parse_rule(*content)),
        RuleJSON::PREC_LEFT { value, content } => Rule::prec_left(value, parse_rule(*content)),
        RuleJSON::PREC_RIGHT { value, content } => Rule::prec_right(value, parse_rule(*content)),
        RuleJSON::PREC_DYNAMIC { value, content } => {
            Rule::prec_dynamic(value, parse_rule(*content))
        }
        RuleJSON::TOKEN { content } => Rule::token(parse_rule(*content)),
        RuleJSON::IMMEDIATE_TOKEN { content } => Rule::immediate_token(parse_rule(*content)),
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
