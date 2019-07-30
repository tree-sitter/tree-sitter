use super::grammars::{
    InlinedProductionMap, LexicalGrammar, Production, ProductionStep, SyntaxGrammar,
    SyntaxVariable, VariableType,
};
use super::rules::{Alias, AliasMap, Symbol, SymbolType};
use crate::error::{Error, Result};
use hashbrown::HashMap;
use serde_derive::Serialize;
use std::collections::BTreeMap;
use std::mem;

#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub(crate) enum ChildType {
    Normal(Symbol),
    Aliased(Alias),
}

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub(crate) struct FieldInfo {
    pub required: bool,
    pub multiple: bool,
    pub types: Vec<ChildType>,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub(crate) struct VariableInfo {
    pub fields: HashMap<String, FieldInfo>,
    pub child_types: Vec<ChildType>,
    pub children_without_fields: FieldInfo,
    pub has_multi_step_production: bool,
}

#[derive(Debug, Serialize, PartialEq, Eq, Default)]
pub(crate) struct NodeInfoJSON {
    #[serde(rename = "type")]
    kind: String,
    named: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    fields: Option<BTreeMap<String, FieldInfoJSON>>,
    #[serde(skip_serializing_if = "Option::is_none")]
    children: Option<FieldInfoJSON>,
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

pub(crate) fn get_variable_info(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    inlines: &InlinedProductionMap,
) -> Result<Vec<VariableInfo>> {
    let mut result = Vec::new();

    // Determine which field names and child node types can appear directly
    // within each type of node.
    let mut steps = Vec::new();
    for (i, variable) in syntax_grammar.variables.iter().enumerate() {
        let mut info = VariableInfo {
            fields: HashMap::new(),
            child_types: Vec::new(),
            children_without_fields: FieldInfo {
                multiple: false,
                required: true,
                types: Vec::new(),
            },
            has_multi_step_production: false,
        };

        steps.clear();
        if get_all_child_steps(variable, inlines, &mut steps) > 1 {
            info.has_multi_step_production = true;
        }

        let is_recursive = steps.iter().any(|s| s.symbol == Symbol::non_terminal(i));

        for step in &steps {
            let child_type = if let Some(alias) = &step.alias {
                ChildType::Aliased(alias.clone())
            } else {
                ChildType::Normal(step.symbol)
            };

            if let Some(field_name) = &step.field_name {
                let field_info = info.fields.entry(field_name.clone()).or_insert(FieldInfo {
                    multiple: false,
                    required: true,
                    types: Vec::new(),
                });
                field_info.multiple |= is_recursive;
                if let Err(i) = field_info.types.binary_search(&child_type) {
                    field_info.types.insert(i, child_type.clone());
                }
            } else if variable_type_for_child_type(&child_type, syntax_grammar, lexical_grammar)
                == VariableType::Named
            {
                let children_info = &mut info.children_without_fields;
                children_info.multiple |= is_recursive;
                if let Err(i) = children_info.types.binary_search(&child_type) {
                    children_info.types.insert(i, child_type.clone());
                }
            }

            if let Err(i) = info.child_types.binary_search(&child_type) {
                info.child_types.insert(i, child_type.clone());
            }
        }

        for production in &variable.productions {
            let production_fields: Vec<&String> = production
                .steps
                .iter()
                .filter_map(|s| s.field_name.as_ref())
                .collect();
            for (field_name, field_info) in info.fields.iter_mut() {
                let mut occurrence_count = 0;
                for f in &production_fields {
                    if *f == field_name {
                        occurrence_count += 1;
                    }
                }
                if occurrence_count == 0 {
                    field_info.required = false;
                }
                if occurrence_count > 1 {
                    field_info.multiple = true;
                }
            }

            let named_children_without_fields_count = production
                .steps
                .iter()
                .filter(|s| {
                    if s.field_name.is_some() {
                        false
                    } else if let Some(alias) = &s.alias {
                        alias.is_named
                    } else if s.symbol.is_non_terminal() {
                        true
                    } else if s.symbol.is_external() {
                        syntax_grammar.external_tokens[s.symbol.index].kind == VariableType::Named
                    } else {
                        lexical_grammar.variables[s.symbol.index].kind == VariableType::Named
                    }
                })
                .count();
            if named_children_without_fields_count == 0 {
                info.children_without_fields.required = false;
            }
            if named_children_without_fields_count > 1 {
                info.children_without_fields.multiple = true;
            }
        }

        result.push(info);
    }

    // Expand each node type's information recursively to inherit the properties of
    // hidden children.
    let mut done = false;
    while !done {
        done = true;
        for (i, variable) in syntax_grammar.variables.iter().enumerate() {
            // Move this variable's info out of the vector so it can be modified
            // while reading from other entries of the vector.
            let mut variable_info = VariableInfo::default();
            mem::swap(&mut variable_info, &mut result[i]);

            steps.clear();
            get_all_child_steps(variable, inlines, &mut steps);

            for step in &steps {
                let child_symbol = step.symbol;
                if step.alias.is_none()
                    && child_symbol.kind == SymbolType::NonTerminal
                    && !syntax_grammar.variables[child_symbol.index]
                        .kind
                        .is_visible()
                    && !syntax_grammar.supertype_symbols.contains(&child_symbol)
                {
                    let child_variable_info = &result[child_symbol.index];

                    // If a hidden child can have multiple children, then this
                    // node can appear to have multiple children.
                    if child_variable_info.has_multi_step_production {
                        variable_info.has_multi_step_production = true;
                    }

                    // Inherit fields from this hidden child
                    for (field_name, child_field_info) in &child_variable_info.fields {
                        let field_info = variable_info
                            .fields
                            .entry(field_name.clone())
                            .or_insert_with(|| {
                                done = false;
                                child_field_info.clone()
                            });
                        if child_field_info.multiple && !field_info.multiple {
                            field_info.multiple = child_field_info.multiple;
                            done = false;
                        }
                        if !child_field_info.required && field_info.required {
                            field_info.required = child_field_info.required;
                            done = false;
                        }
                        for child_type in &child_field_info.types {
                            if let Err(i) = field_info.types.binary_search(&child_type) {
                                field_info.types.insert(i, child_type.clone());
                                done = false;
                            }
                        }
                    }

                    // Inherit child types from this hidden child
                    for child_type in &child_variable_info.child_types {
                        if let Err(i) = variable_info.child_types.binary_search(&child_type) {
                            variable_info.child_types.insert(i, child_type.clone());
                            done = false;
                        }
                    }

                    // If any field points to this hidden child, inherit child types
                    // for the field.
                    if let Some(field_name) = &step.field_name {
                        let field_info = variable_info.fields.get_mut(field_name).unwrap();
                        for child_type in &child_variable_info.child_types {
                            if let Err(i) = field_info.types.binary_search(&child_type) {
                                field_info.types.insert(i, child_type.clone());
                                done = false;
                            }
                        }
                    } else {
                        // Inherit child types without fields from this hidden child
                        // Inherit info about children w/o fields from this hidden child
                        let grandchildren_info = &child_variable_info.children_without_fields;
                        if grandchildren_info.multiple
                            && !variable_info.children_without_fields.multiple
                        {
                            variable_info.children_without_fields.multiple = true;
                            done = false;
                        }
                        // if !grandchildren_info.required
                        //     && variable_info.children_without_fields.required
                        // {
                        //     variable_info.children_without_fields.required = false;
                        //     done = false;
                        // }
                        for child_type in &grandchildren_info.types {
                            if let Err(i) = variable_info
                                .children_without_fields
                                .types
                                .binary_search(&child_type)
                            {
                                variable_info
                                    .children_without_fields
                                    .types
                                    .insert(i, child_type.clone());
                                done = false;
                            }
                        }
                    }
                }
            }

            // Move this variable's info back into the vector.
            result[i] = variable_info;
        }
    }

    for supertype_symbol in &syntax_grammar.supertype_symbols {
        let variable = &syntax_grammar.variables[supertype_symbol.index];
        if variable.kind != VariableType::Hidden {
            return Err(Error::grammar(&format!(
                "Supertype symbols must be hidden, but `{}` is not",
                variable.name
            )));
        }

        if result[supertype_symbol.index].has_multi_step_production {
            return Err(Error::grammar(&format!(
                "Supertype symbols must always have a single visible child, but `{}` can have multiple",
                variable.name
            )));
        }
    }

    let child_type_is_visible = |t: &ChildType| {
        variable_type_for_child_type(t, syntax_grammar, lexical_grammar) >= VariableType::Anonymous
    };

    for supertype_symbol in &syntax_grammar.supertype_symbols {
        result[supertype_symbol.index]
            .child_types
            .retain(child_type_is_visible);
    }

    for i in 0..result.len() {
        let mut variable_info = VariableInfo::default();
        mem::swap(&mut variable_info, &mut result[i]);

        // For each field, make the `types` list more concise by replacing sets of
        // subtypes with a single supertype.
        for (_, field_info) in variable_info.fields.iter_mut() {
            for supertype_symbol in &syntax_grammar.supertype_symbols {
                sorted_vec_replace(
                    &mut field_info.types,
                    &result[supertype_symbol.index].child_types,
                    ChildType::Normal(*supertype_symbol),
                );
            }

            field_info.types.retain(child_type_is_visible);
        }

        for supertype_symbol in &syntax_grammar.supertype_symbols {
            sorted_vec_replace(
                &mut variable_info.children_without_fields.types,
                &result[supertype_symbol.index].child_types,
                ChildType::Normal(*supertype_symbol),
            );
        }

        variable_info
            .children_without_fields
            .types
            .retain(child_type_is_visible);

        result[i] = variable_info;
    }

    Ok(result)
}

// Summarize information about this variable's possible children by walking
// all of its productions.
fn get_all_child_steps(
    variable: &SyntaxVariable,
    inlines: &InlinedProductionMap,
    output: &mut Vec<ProductionStep>,
) -> usize {
    // For each of the given variable's productions, insert all of the reachable steps
    // into the output vector, and return the longest possible production length.
    return variable
        .productions
        .iter()
        .map(|p| process_production(inlines, p, 0, output))
        .max()
        .unwrap_or(0);

    // For the given production suffix, add all of the remaining steps into the output
    // vector and return the longest possible production length.
    fn process_production(
        inlines: &InlinedProductionMap,
        production: &Production,
        step_index: usize,
        output: &mut Vec<ProductionStep>,
    ) -> usize {
        let mut max_length = production.steps.len();

        // Process each of the remaining steps of the production.
        for (i, step) in production.steps.iter().enumerate().skip(step_index) {
            // If this step is inlined, then process the corresponding suffixes of
            // all of the inlined productions instead.
            if let Some(inlined_productions) = inlines.inlined_productions(production, i as u32) {
                for inlined_production in inlined_productions {
                    let length = process_production(inlines, inlined_production, i, output);
                    if length > max_length {
                        max_length = length;
                    }
                }
                break;
            }

            // Otherwise, insert this step into the output vector unless it is already
            // present.
            if let Err(i) = output.binary_search(step) {
                output.insert(i, step.clone());
            }
        }

        return max_length;
    }
}

fn variable_type_for_child_type(
    child_type: &ChildType,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
) -> VariableType {
    match child_type {
        ChildType::Aliased(alias) => {
            if alias.is_named {
                VariableType::Named
            } else {
                VariableType::Anonymous
            }
        }
        ChildType::Normal(symbol) => {
            if syntax_grammar.supertype_symbols.contains(&symbol) {
                return VariableType::Named;
            } else {
                match symbol.kind {
                    SymbolType::NonTerminal => syntax_grammar.variables[symbol.index].kind,
                    SymbolType::Terminal => lexical_grammar.variables[symbol.index].kind,
                    SymbolType::External => syntax_grammar.external_tokens[symbol.index].kind,
                    _ => VariableType::Hidden,
                }
            }
        }
    }
}

fn sorted_vec_replace<T>(left: &mut Vec<T>, right: &Vec<T>, value: T) -> bool
where
    T: Eq + Ord,
{
    if left.len() == 0 {
        return false;
    }

    let mut i = 0;
    for right_elem in right.iter() {
        while left[i] < *right_elem {
            i += 1;
            if i == left.len() {
                return false;
            }
        }
        if left[i] != *right_elem {
            return false;
        }
    }

    i = 0;
    left.retain(|left_elem| {
        if i == right.len() {
            return true;
        }
        while right[i] < *left_elem {
            i += 1;
            if i == right.len() {
                return true;
            }
        }
        right[i] != *left_elem
    });

    if let Err(i) = left.binary_search(&value) {
        left.insert(i, value);
    }

    true
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
                        kind: name.clone(),
                        named: true,
                        fields: None,
                        children: None,
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
        } else if variable.kind.is_visible()
            && !syntax_grammar.variables_to_inline.contains(&symbol)
        {
            let node_type_json =
                node_types_json
                    .entry(name.clone())
                    .or_insert_with(|| NodeInfoJSON {
                        kind: name.clone(),
                        named: true,
                        fields: None,
                        children: None,
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
            let mut children_types = info
                .children_without_fields
                .types
                .iter()
                .map(child_type_to_node_type)
                .collect::<Vec<_>>();
            if children_types.len() > 0 {
                children_types.sort_unstable();
                children_types.dedup();
                node_type_json.children = Some(FieldInfoJSON {
                    multiple: info.children_without_fields.multiple,
                    required: info.children_without_fields.required,
                    types: children_types,
                });
            }
        }
    }

    let mut result = node_types_json.into_iter().map(|e| e.1).collect::<Vec<_>>();

    for variable in &lexical_grammar.variables {
        if variable.kind == VariableType::Named {
            result.push(NodeInfoJSON {
                kind: variable.name.clone(),
                named: true,
                fields: None,
                children: None,
                subtypes: None,
            });
        } else if variable.kind == VariableType::Anonymous {
            result.push(NodeInfoJSON {
                kind: variable.name.clone(),
                named: false,
                fields: None,
                children: None,
                subtypes: None,
            });
        }
    }

    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::grammars::{
        InputGrammar, LexicalVariable, Production, ProductionStep, SyntaxVariable, Variable,
    };
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
                kind: "v1".to_string(),
                named: true,
                subtypes: None,
                children: None,
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
        assert_eq!(
            node_types[1],
            NodeInfoJSON {
                kind: ";".to_string(),
                named: false,
                subtypes: None,
                children: None,
                fields: None
            }
        );
        assert_eq!(
            node_types[2],
            NodeInfoJSON {
                kind: "v2".to_string(),
                named: true,
                subtypes: None,
                children: None,
                fields: None
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
                kind: "_v2".to_string(),
                named: true,
                fields: None,
                children: None,
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
                kind: "v1".to_string(),
                named: true,
                subtypes: None,
                children: None,
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

    #[test]
    fn test_node_types_for_children_without_fields() {
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
                        Rule::named("v2"),
                        Rule::field("f1".to_string(), Rule::named("v3")),
                        Rule::named("v4"),
                    ]),
                },
                Variable {
                    name: "v2".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![
                        Rule::string("{"),
                        Rule::choice(vec![Rule::named("v3"), Rule::Blank]),
                        Rule::string("}"),
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
                kind: "v1".to_string(),
                named: true,
                subtypes: None,
                children: Some(FieldInfoJSON {
                    multiple: true,
                    required: true,
                    types: vec![
                        NodeTypeJSON {
                            kind: "v2".to_string(),
                            named: true,
                        },
                        NodeTypeJSON {
                            kind: "v4".to_string(),
                            named: true,
                        },
                    ]
                }),
                fields: Some(
                    vec![(
                        "f1".to_string(),
                        FieldInfoJSON {
                            multiple: false,
                            required: true,
                            types: vec![NodeTypeJSON {
                                kind: "v3".to_string(),
                                named: true,
                            }]
                        }
                    ),]
                    .into_iter()
                    .collect()
                )
            }
        );
        assert_eq!(
            node_types[1],
            NodeInfoJSON {
                kind: "v2".to_string(),
                named: true,
                subtypes: None,
                children: Some(FieldInfoJSON {
                    multiple: false,
                    required: false,
                    types: vec![NodeTypeJSON {
                        kind: "v3".to_string(),
                        named: true,
                    },]
                }),
                fields: Some(BTreeMap::new()),
            }
        );
    }

    #[test]
    fn test_get_variable_info() {
        let variable_info = get_variable_info(
            &build_syntax_grammar(
                vec![
                    // Required field `field1` has only one node type.
                    SyntaxVariable {
                        name: "rule0".to_string(),
                        kind: VariableType::Named,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(0)),
                                ProductionStep::new(Symbol::non_terminal(1))
                                    .with_field_name("field1"),
                            ],
                        }],
                    },
                    // Hidden node
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![ProductionStep::new(Symbol::terminal(1))],
                        }],
                    },
                    // Optional field `field2` can have two possible node types.
                    SyntaxVariable {
                        name: "rule2".to_string(),
                        kind: VariableType::Named,
                        productions: vec![
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::terminal(0))],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![
                                    ProductionStep::new(Symbol::terminal(0)),
                                    ProductionStep::new(Symbol::terminal(2))
                                        .with_field_name("field2"),
                                ],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![
                                    ProductionStep::new(Symbol::terminal(0)),
                                    ProductionStep::new(Symbol::terminal(3))
                                        .with_field_name("field2"),
                                ],
                            },
                        ],
                    },
                ],
                vec![],
            ),
            &build_lexical_grammar(),
            &InlinedProductionMap::default(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    required: true,
                    multiple: false,
                    types: vec![ChildType::Normal(Symbol::terminal(1))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );

        assert_eq!(
            variable_info[2].fields,
            vec![(
                "field2".to_string(),
                FieldInfo {
                    required: false,
                    multiple: false,
                    types: vec![
                        ChildType::Normal(Symbol::terminal(2)),
                        ChildType::Normal(Symbol::terminal(3)),
                    ],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );
    }

    #[test]
    fn test_get_variable_info_with_inherited_fields() {
        let variable_info = get_variable_info(
            &build_syntax_grammar(
                vec![
                    SyntaxVariable {
                        name: "rule0".to_string(),
                        kind: VariableType::Named,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(0)),
                                ProductionStep::new(Symbol::non_terminal(1)),
                                ProductionStep::new(Symbol::terminal(1)),
                            ],
                        }],
                    },
                    // Hidden node with fields
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(2)),
                                ProductionStep::new(Symbol::terminal(3)).with_field_name("field1"),
                            ],
                        }],
                    },
                ],
                vec![],
            ),
            &build_lexical_grammar(),
            &InlinedProductionMap::default(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    required: true,
                    multiple: false,
                    types: vec![ChildType::Normal(Symbol::terminal(3))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );
    }

    #[test]
    fn test_get_variable_info_with_supertypes() {
        let variable_info = get_variable_info(
            &build_syntax_grammar(
                vec![
                    SyntaxVariable {
                        name: "rule0".to_string(),
                        kind: VariableType::Named,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(0)),
                                ProductionStep::new(Symbol::non_terminal(1))
                                    .with_field_name("field1"),
                                ProductionStep::new(Symbol::terminal(1)),
                            ],
                        }],
                    },
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::terminal(2))],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::terminal(3))],
                            },
                        ],
                    },
                ],
                // _rule1 is a supertype
                vec![Symbol::non_terminal(1)],
            ),
            &build_lexical_grammar(),
            &InlinedProductionMap::default(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    required: true,
                    multiple: false,
                    types: vec![ChildType::Normal(Symbol::non_terminal(1))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );
    }

    fn get_node_types(grammar: InputGrammar) -> Vec<NodeInfoJSON> {
        let (syntax_grammar, lexical_grammar, _, simple_aliases) =
            prepare_grammar(&grammar).unwrap();
        let variable_info = get_variable_info(
            &syntax_grammar,
            &lexical_grammar,
            &InlinedProductionMap::default(),
        )
        .unwrap();
        generate_node_types_json(
            &syntax_grammar,
            &lexical_grammar,
            &simple_aliases,
            &variable_info,
        )
    }

    fn build_syntax_grammar(
        variables: Vec<SyntaxVariable>,
        supertype_symbols: Vec<Symbol>,
    ) -> SyntaxGrammar {
        let mut syntax_grammar = SyntaxGrammar::default();
        syntax_grammar.variables = variables;
        syntax_grammar.supertype_symbols = supertype_symbols;
        syntax_grammar
    }

    fn build_lexical_grammar() -> LexicalGrammar {
        let mut lexical_grammar = LexicalGrammar::default();
        for i in 0..10 {
            lexical_grammar.variables.push(LexicalVariable {
                name: format!("token_{}", i),
                kind: VariableType::Named,
                implicit_precedence: 0,
                start_state: 0,
            });
        }
        lexical_grammar
    }
}
