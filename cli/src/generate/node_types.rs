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
                            named: variable.kind == VariableType::Named,
                        }
                    }
                    SymbolType::Terminal => {
                        let variable = &lexical_grammar.variables[symbol.index];
                        NodeTypeJSON {
                            kind: variable.name.clone(),
                            named: variable.kind == VariableType::Named,
                        }
                    }
                    SymbolType::External => {
                        let variable = &syntax_grammar.external_tokens[symbol.index];
                        NodeTypeJSON {
                            kind: variable.name.clone(),
                            named: variable.kind == VariableType::Named,
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
