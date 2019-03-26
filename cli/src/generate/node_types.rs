use super::grammars::{LexicalGrammar, SyntaxGrammar, VariableType};
use super::rules::{AliasMap, Symbol, SymbolType};
use super::tables::{ChildType, VariableInfo};
use serde_derive::Serialize;
use std::collections::BTreeMap;

#[derive(Debug, Serialize, PartialEq, Eq, Default)]
pub(crate) struct NodeInfoJSON {
    #[serde(rename = "type")]
    name: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    fields: Option<BTreeMap<String, FieldInfoJSON>>,
    #[serde(skip_serializing_if = "Option::is_none")]
    subtypes: Option<Vec<NodeTypeJSON>>,
}

#[derive(Debug, Serialize, PartialEq, Eq, PartialOrd, Ord)]
pub(crate) struct NodeTypeJSON {
    #[serde(rename = "type")]
    kind: String,
    named: bool,
}

#[derive(Debug, Serialize, PartialEq, Eq)]
pub(crate) struct FieldInfoJSON {
    multiple: bool,
    required: bool,
    types: Vec<NodeTypeJSON>,
}

pub(crate) fn generate_node_types_json(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    variable_info: &Vec<VariableInfo>,
) -> Vec<NodeInfoJSON> {
    let mut node_types_json = BTreeMap::new();

    let child_type_to_node_type = |child_type: &ChildType| match child_type {
        ChildType::Aliased(alias) => NodeTypeJSON {
            kind: alias.value.clone(),
            named: alias.is_named,
        },
        ChildType::Normal(symbol) => {
            if let Some(alias) = simple_aliases.get(&symbol) {
                NodeTypeJSON {
                    kind: alias.value.clone(),
                    named: alias.is_named,
                }
            } else {
                match symbol.kind {
                    SymbolType::NonTerminal => {
                        let variable = &syntax_grammar.variables[symbol.index];
                        NodeTypeJSON {
                            kind: variable.name.clone(),
                            named: variable.kind != VariableType::Anonymous,
                        }
                    }
                    SymbolType::Terminal => {
                        let variable = &lexical_grammar.variables[symbol.index];
                        NodeTypeJSON {
                            kind: variable.name.clone(),
                            named: variable.kind != VariableType::Anonymous,
                        }
                    }
                    SymbolType::External => {
                        let variable = &syntax_grammar.external_tokens[symbol.index];
                        NodeTypeJSON {
                            kind: variable.name.clone(),
                            named: variable.kind != VariableType::Anonymous,
                        }
                    }
                    _ => panic!("Unexpected symbol type"),
                }
            }
        }
    };

    for (i, info) in variable_info.iter().enumerate() {
        let symbol = Symbol::non_terminal(i);
        let variable = &syntax_grammar.variables[i];
        let name = simple_aliases
            .get(&Symbol::non_terminal(i))
            .map_or(&variable.name, |alias| &alias.value);

        if syntax_grammar.supertype_symbols.contains(&symbol) {
            let node_type_json =
                node_types_json
                    .entry(name.clone())
                    .or_insert_with(|| NodeInfoJSON {
                        name: name.clone(),
                        fields: None,
                        subtypes: None,
                    });
            let mut subtypes = info
                .child_types
                .iter()
                .map(child_type_to_node_type)
                .collect::<Vec<_>>();
            subtypes.sort_unstable();
            subtypes.dedup();
            node_type_json.subtypes = Some(subtypes);
        } else if variable.kind.is_visible() {
            let node_type_json =
                node_types_json
                    .entry(name.clone())
                    .or_insert_with(|| NodeInfoJSON {
                        name: name.clone(),
                        fields: None,
                        subtypes: None,
                    });
            let mut fields_json = BTreeMap::new();
            for (field, field_info) in info.fields.iter() {
                let field_info_json = fields_json.entry(field.clone()).or_insert(FieldInfoJSON {
                    multiple: false,
                    required: true,
                    types: Vec::new(),
                });

                field_info_json.multiple |= field_info.multiple;
                field_info_json.required &= field_info.required;
                field_info_json
                    .types
                    .extend(field_info.types.iter().map(child_type_to_node_type));
                field_info_json.types.sort_unstable();
                field_info_json.types.dedup();
            }
            node_type_json.fields = Some(fields_json);
        }
    }

    node_types_json.into_iter().map(|e| e.1).collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::build_tables::build_parse_table::get_variable_info;
    use crate::generate::grammars::{InputGrammar, Variable, VariableType};
    use crate::generate::prepare_grammar::prepare_grammar;
    use crate::generate::rules::Rule;

    #[test]
    fn test_node_types_simple() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
            supertype_symbols: vec![],
            variables: vec![
                Variable {
                    name: "v1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![
                        Rule::field("f1".to_string(), Rule::named("v2")),
                        Rule::field("f2".to_string(), Rule::string(";")),
                    ]),
                },
                Variable {
                    name: "v2".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("x"),
                },
            ],
        });

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                name: "v1".to_string(),
                subtypes: None,
                fields: Some(
                    vec![
                        (
                            "f1".to_string(),
                            FieldInfoJSON {
                                multiple: false,
                                required: true,
                                types: vec![NodeTypeJSON {
                                    kind: "v2".to_string(),
                                    named: true,
                                }]
                            }
                        ),
                        (
                            "f2".to_string(),
                            FieldInfoJSON {
                                multiple: false,
                                required: true,
                                types: vec![NodeTypeJSON {
                                    kind: ";".to_string(),
                                    named: false,
                                }]
                            }
                        ),
                    ]
                    .into_iter()
                    .collect()
                )
            }
        );
    }

    #[test]
    fn test_node_types_with_supertypes() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            extra_tokens: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
            supertype_symbols: vec!["_v2".to_string()],
            variables: vec![
                Variable {
                    name: "v1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::field("f1".to_string(), Rule::named("_v2")),
                },
                Variable {
                    name: "_v2".to_string(),
                    kind: VariableType::Hidden,
                    rule: Rule::choice(vec![
                        Rule::named("v3"),
                        Rule::named("v4"),
                        Rule::string("*"),
                    ]),
                },
                Variable {
                    name: "v3".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("x"),
                },
                Variable {
                    name: "v4".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("y"),
                },
            ],
        });

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                name: "_v2".to_string(),
                fields: None,
                subtypes: Some(vec![
                    NodeTypeJSON {
                        kind: "*".to_string(),
                        named: false,
                    },
                    NodeTypeJSON {
                        kind: "v3".to_string(),
                        named: true,
                    },
                    NodeTypeJSON {
                        kind: "v4".to_string(),
                        named: true,
                    },
                ]),
            }
        );
        assert_eq!(
            node_types[1],
            NodeInfoJSON {
                name: "v1".to_string(),
                subtypes: None,
                fields: Some(
                    vec![(
                        "f1".to_string(),
                        FieldInfoJSON {
                            multiple: false,
                            required: true,
                            types: vec![NodeTypeJSON {
                                kind: "_v2".to_string(),
                                named: true,
                            }]
                        }
                    ),]
                    .into_iter()
                    .collect()
                )
            }
        );
    }

    fn get_node_types(grammar: InputGrammar) -> Vec<NodeInfoJSON> {
        let (syntax_grammar, lexical_grammar, _, simple_aliases) =
            prepare_grammar(&grammar).unwrap();
        let variable_info = get_variable_info(&syntax_grammar, &lexical_grammar).unwrap();
        generate_node_types_json(
            &syntax_grammar,
            &lexical_grammar,
            &simple_aliases,
            &variable_info,
        )
    }
}
