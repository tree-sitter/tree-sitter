use super::grammars::{LexicalGrammar, SyntaxGrammar, VariableType};
use super::rules::{Alias, AliasMap, Symbol, SymbolType};
use crate::error::{Error, Result};
use serde_derive::Serialize;
use std::collections::{BTreeMap, HashMap, HashSet};

#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub(crate) enum ChildType {
    Normal(Symbol),
    Aliased(Alias),
}

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub(crate) struct FieldInfo {
    pub quantity: ChildQuantity,
    pub types: Vec<ChildType>,
}

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub(crate) struct VariableInfo {
    pub fields: HashMap<String, FieldInfo>,
    pub child_types: Vec<ChildType>,
    pub children_without_fields: FieldInfo,
    pub has_multi_step_production: bool,
}

#[derive(Debug, Serialize, PartialEq, Eq, Default, PartialOrd, Ord)]
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

#[derive(Clone, Debug, Serialize, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub(crate) struct NodeTypeJSON {
    #[serde(rename = "type")]
    kind: String,
    named: bool,
}

#[derive(Debug, Serialize, PartialEq, Eq, PartialOrd, Ord)]
pub(crate) struct FieldInfoJSON {
    multiple: bool,
    required: bool,
    types: Vec<NodeTypeJSON>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct ChildQuantity {
    exists: bool,
    required: bool,
    multiple: bool,
}

impl Default for FieldInfoJSON {
    fn default() -> Self {
        FieldInfoJSON {
            multiple: false,
            required: true,
            types: Vec::new(),
        }
    }
}

impl Default for ChildQuantity {
    fn default() -> Self {
        Self::zero()
    }
}

impl ChildQuantity {
    fn zero() -> Self {
        ChildQuantity {
            exists: false,
            required: false,
            multiple: false,
        }
    }

    fn one() -> Self {
        ChildQuantity {
            exists: true,
            required: true,
            multiple: false,
        }
    }

    fn append(&mut self, other: ChildQuantity) {
        if other.exists {
            if self.exists || other.multiple {
                self.multiple = true;
            }
            if other.required {
                self.required = true;
            }
            self.exists = true;
        }
    }

    fn union(&mut self, other: ChildQuantity) -> bool {
        let mut result = false;
        if !self.exists && other.exists {
            result = true;
            self.exists = true;
        }
        if self.required && !other.required {
            result = true;
            self.required = false;
        }
        if !self.multiple && other.multiple {
            result = true;
            self.multiple = true;
        }
        result
    }
}

/// Compute a summary of the public-facing structure of each variable in the
/// grammar. Each variable in the grammar corresponds to a distinct public-facing
/// node type.
///
/// The information collected about each node type `N` is:
/// 1. `child_types` - The types of visible children that can appear within `N`.
/// 2. `fields` - The fields that `N` can have. Data regarding each field:
///    * `types` - The types of visible children the field can contain.
///    * `optional` - Do `N` nodes always have this field?
///    * `multiple` - Can `N` nodes have multiple children for this field?
/// 3. `children_without_fields` - The *other* named children of `N` that are
///    not associated with fields. Data regarding these children:
///    * `types` - The types of named children with no field.
///    * `optional` - Do `N` nodes always have at least one named child with no field?
///    * `multiple` - Can `N` nodes have multiple named children with no field?
///
/// Each summary must account for some indirect factors:
/// 1. hidden nodes. When a parent node `N` has a hidden child `C`, the visible
///    children of `C` *appear* to be direct children of `N`.
/// 2. aliases. If a parent node type `M` is aliased as some other type `N`,
///    then nodes which *appear* to have type `N` may have internal structure based
///    on `M`.
pub(crate) fn get_variable_info(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
) -> Result<Vec<VariableInfo>> {
    let child_type_is_visible = |t: &ChildType| {
        variable_type_for_child_type(t, syntax_grammar, lexical_grammar) >= VariableType::Anonymous
    };

    let child_type_is_named = |t: &ChildType| {
        variable_type_for_child_type(t, syntax_grammar, lexical_grammar) == VariableType::Named
    };

    // Each variable's summary can depend on the summaries of other hidden variables,
    // and variables can have mutually recursive structure. So we compute the summaries
    // iteratively, in a loop that terminates only when more changes are possible.
    let mut did_change = true;
    let mut all_initialized = false;
    let mut result = vec![VariableInfo::default(); syntax_grammar.variables.len()];
    while did_change {
        did_change = false;

        for (i, variable) in syntax_grammar.variables.iter().enumerate() {
            let mut variable_info = result[i].clone();

            // Within a variable, consider each production separately. For each
            // production, determine which children and fields can occur, and how many
            // times they can occur.
            for (production_index, production) in variable.productions.iter().enumerate() {
                let mut field_quantities = HashMap::new();
                let mut children_without_fields_quantity = ChildQuantity::zero();
                let mut has_uninitialized_invisible_children = false;

                if production.steps.len() > 1 {
                    variable_info.has_multi_step_production = true;
                }

                for step in &production.steps {
                    let child_symbol = step.symbol;
                    let child_type = if let Some(alias) = &step.alias {
                        ChildType::Aliased(alias.clone())
                    } else if let Some(alias) = simple_aliases.get(&step.symbol) {
                        ChildType::Aliased(alias.clone())
                    } else {
                        ChildType::Normal(child_symbol)
                    };

                    // Record all of the types of direct children.
                    did_change |= sorted_vec_insert(&mut variable_info.child_types, &child_type);

                    // Record all of the field names that occur.
                    if let Some(field_name) = &step.field_name {
                        // Record how many times each field occurs in this production.
                        field_quantities
                            .entry(field_name)
                            .or_insert(ChildQuantity::zero())
                            .append(ChildQuantity::one());

                        // Record the types of children for this field.
                        let field_info =
                            variable_info.fields.entry(field_name.clone()).or_insert({
                                let mut info = FieldInfo {
                                    types: Vec::new(),
                                    quantity: ChildQuantity::one(),
                                };

                                // If this field did *not* occur in an earlier production,
                                // then it is not required.
                                if production_index > 0 {
                                    info.quantity.required = false;
                                }
                                info
                            });
                        did_change |= sorted_vec_insert(&mut field_info.types, &child_type);
                    }
                    // Record named children without fields.
                    else if child_type_is_named(&child_type) {
                        // Record how many named children without fields occur in this production.
                        children_without_fields_quantity.append(ChildQuantity::one());

                        // Record the types of all of the named children without fields.
                        let children_info = &mut variable_info.children_without_fields;
                        if children_info.types.is_empty() {
                            children_info.quantity = ChildQuantity::one();
                        }
                        did_change |= sorted_vec_insert(&mut children_info.types, &child_type);
                    }

                    // Inherit information from any hidden children.
                    if child_symbol.is_non_terminal()
                        && !syntax_grammar.supertype_symbols.contains(&child_symbol)
                        && step.alias.is_none()
                        && !child_type_is_visible(&child_type)
                    {
                        let child_variable_info = &result[child_symbol.index];

                        // If a hidden child can have multiple children, then this
                        // node can appear to have multiple children.
                        if child_variable_info.has_multi_step_production {
                            variable_info.has_multi_step_production = true;
                        }

                        // Inherit fields from this hidden child
                        for (field_name, child_field_info) in &child_variable_info.fields {
                            field_quantities
                                .entry(field_name)
                                .or_insert(ChildQuantity::zero())
                                .append(child_field_info.quantity);
                            let field_info = variable_info
                                .fields
                                .entry(field_name.clone())
                                .or_insert(FieldInfo {
                                    types: Vec::new(),
                                    quantity: ChildQuantity::one(),
                                });
                            for child_type in &child_field_info.types {
                                sorted_vec_insert(&mut field_info.types, &child_type);
                            }
                        }

                        // Inherit child types from this hidden child
                        for child_type in &child_variable_info.child_types {
                            did_change |=
                                sorted_vec_insert(&mut variable_info.child_types, child_type);
                        }

                        // If any field points to this hidden child, inherit child types
                        // for the field.
                        if let Some(field_name) = &step.field_name {
                            let field_info = variable_info.fields.get_mut(field_name).unwrap();
                            for child_type in &child_variable_info.child_types {
                                did_change |= sorted_vec_insert(&mut field_info.types, &child_type);
                            }
                        }
                        // Inherit info about children without fields from this hidden child.
                        else {
                            let grandchildren_info = &child_variable_info.children_without_fields;
                            if !grandchildren_info.types.is_empty() {
                                children_without_fields_quantity
                                    .append(grandchildren_info.quantity);

                                if variable_info.children_without_fields.types.is_empty() {
                                    variable_info.children_without_fields.quantity =
                                        ChildQuantity::one();
                                }

                                for child_type in &grandchildren_info.types {
                                    did_change |= sorted_vec_insert(
                                        &mut variable_info.children_without_fields.types,
                                        &child_type,
                                    );
                                }
                            }
                        }
                    }

                    // Note whether or not this production contains children whose summaries
                    // have not yet been computed.
                    if child_symbol.index >= i && !all_initialized {
                        has_uninitialized_invisible_children = true;
                    }
                }

                // If this production's children all have had their summaries initialized,
                // then expand the quantity information with all of the possibilities introduced
                // by this production.
                if !has_uninitialized_invisible_children {
                    did_change |= variable_info
                        .children_without_fields
                        .quantity
                        .union(children_without_fields_quantity);

                    for (field_name, info) in variable_info.fields.iter_mut() {
                        did_change |= info.quantity.union(
                            field_quantities
                                .get(field_name)
                                .cloned()
                                .unwrap_or(ChildQuantity::zero()),
                        );
                    }
                }
            }

            result[i] = variable_info;
        }

        all_initialized = true;
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

    // Update all of the node type lists to eliminate hidden nodes.
    for supertype_symbol in &syntax_grammar.supertype_symbols {
        result[supertype_symbol.index]
            .child_types
            .retain(child_type_is_visible);
    }
    for variable_info in result.iter_mut() {
        for (_, field_info) in variable_info.fields.iter_mut() {
            field_info.types.retain(child_type_is_visible);
        }
        variable_info
            .children_without_fields
            .types
            .retain(child_type_is_visible);
    }

    Ok(result)
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

    let populate_field_info_json = |json: &mut FieldInfoJSON, info: &FieldInfo| {
        if info.types.len() > 0 {
            json.multiple |= info.quantity.multiple;
            json.required &= info.quantity.required;
            json.types
                .extend(info.types.iter().map(child_type_to_node_type));
            json.types.sort_unstable();
            json.types.dedup();
        } else {
            json.required = false;
        }
    };

    let mut aliases_by_symbol = HashMap::new();
    for (symbol, alias) in simple_aliases {
        aliases_by_symbol.insert(*symbol, {
            let mut aliases = HashSet::new();
            aliases.insert(Some(alias.clone()));
            aliases
        });
    }
    for variable in &syntax_grammar.variables {
        for production in &variable.productions {
            for step in &production.steps {
                if !simple_aliases.contains_key(&step.symbol) {
                    aliases_by_symbol
                        .entry(step.symbol)
                        .or_insert(HashSet::new())
                        .insert(step.alias.clone());
                }
            }
        }
    }
    aliases_by_symbol.insert(
        Symbol::non_terminal(0),
        [None].into_iter().cloned().collect(),
    );

    let mut subtype_map = HashMap::new();
    for (i, info) in variable_info.iter().enumerate() {
        let symbol = Symbol::non_terminal(i);
        let variable = &syntax_grammar.variables[i];
        if syntax_grammar.supertype_symbols.contains(&symbol) {
            let node_type_json =
                node_types_json
                    .entry(variable.name.clone())
                    .or_insert_with(|| NodeInfoJSON {
                        kind: variable.name.clone(),
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
            subtype_map.insert(
                NodeTypeJSON {
                    kind: node_type_json.kind.clone(),
                    named: true,
                },
                subtypes.clone(),
            );
            subtypes.sort_unstable();
            subtypes.dedup();
            node_type_json.subtypes = Some(subtypes);
        } else if !syntax_grammar.variables_to_inline.contains(&symbol) {
            // If a rule is aliased under multiple names, then its information
            // contributes to multiple entries in the final JSON.
            for alias in aliases_by_symbol
                .get(&Symbol::non_terminal(i))
                .unwrap_or(&HashSet::new())
            {
                let kind;
                let is_named;
                if let Some(alias) = alias {
                    kind = &alias.value;
                    is_named = alias.is_named;
                } else if variable.kind.is_visible() {
                    kind = &variable.name;
                    is_named = variable.kind == VariableType::Named;
                } else {
                    continue;
                }

                // There may already be an entry with this name, because multiple
                // rules may be aliased with the same name.
                let node_type_json =
                    node_types_json
                        .entry(kind.clone())
                        .or_insert_with(|| NodeInfoJSON {
                            kind: kind.clone(),
                            named: is_named,
                            fields: Some(BTreeMap::new()),
                            children: None,
                            subtypes: None,
                        });

                let fields_json = node_type_json.fields.as_mut().unwrap();
                for (field, field_info) in info.fields.iter() {
                    populate_field_info_json(
                        &mut fields_json
                            .entry(field.clone())
                            .or_insert(FieldInfoJSON::default()),
                        field_info,
                    );
                }
                for (existing_field, field_json) in fields_json.iter_mut() {
                    if !info.fields.contains_key(existing_field) {
                        field_json.required = false;
                    }
                }

                populate_field_info_json(
                    node_type_json
                        .children
                        .get_or_insert(FieldInfoJSON::default()),
                    &info.children_without_fields,
                );
            }
        }
    }

    for (_, node_type_json) in node_types_json.iter_mut() {
        if node_type_json
            .children
            .as_ref()
            .map_or(false, |c| c.types.is_empty())
        {
            node_type_json.children = None;
        }

        if let Some(children) = &mut node_type_json.children {
            process_supertypes(children, &subtype_map);
        }
        if let Some(fields) = &mut node_type_json.fields {
            for (_, field_info) in fields.iter_mut() {
                process_supertypes(field_info, &subtype_map);
            }
        }
    }

    let mut anonymous_node_types = Vec::new();

    let empty = HashSet::new();
    let regular_tokens = lexical_grammar
        .variables
        .iter()
        .enumerate()
        .flat_map(|(i, variable)| {
            aliases_by_symbol
                .get(&Symbol::terminal(i))
                .unwrap_or(&empty)
                .iter()
                .map(move |alias| {
                    if let Some(alias) = alias {
                        (&alias.value, alias.kind())
                    } else {
                        (&variable.name, variable.kind)
                    }
                })
        });
    let external_tokens =
        syntax_grammar
            .external_tokens
            .iter()
            .enumerate()
            .flat_map(|(i, token)| {
                aliases_by_symbol
                    .get(&Symbol::external(i))
                    .unwrap_or(&empty)
                    .iter()
                    .map(move |alias| {
                        if let Some(alias) = alias {
                            (&alias.value, alias.kind())
                        } else {
                            (&token.name, token.kind)
                        }
                    })
            });

    for (name, kind) in regular_tokens.chain(external_tokens) {
        match kind {
            VariableType::Named => {
                let node_type_json = node_types_json.entry(name.clone()).or_insert(NodeInfoJSON {
                    kind: name.clone(),
                    named: true,
                    fields: None,
                    children: None,
                    subtypes: None,
                });
                if let Some(children) = &mut node_type_json.children {
                    children.required = false;
                }
                if let Some(fields) = &mut node_type_json.fields {
                    for (_, field) in fields.iter_mut() {
                        field.required = false;
                    }
                }
            }
            VariableType::Anonymous => anonymous_node_types.push(NodeInfoJSON {
                kind: name.clone(),
                named: false,
                fields: None,
                children: None,
                subtypes: None,
            }),
            _ => {}
        }
    }

    let mut result = node_types_json.into_iter().map(|e| e.1).collect::<Vec<_>>();
    result.extend(anonymous_node_types.into_iter());
    result.sort_unstable_by(|a, b| {
        b.subtypes
            .is_some()
            .cmp(&a.subtypes.is_some())
            .then_with(|| {
                let a_is_leaf = a.children.is_none() && a.fields.is_none();
                let b_is_leaf = b.children.is_none() && b.fields.is_none();
                a_is_leaf.cmp(&b_is_leaf)
            })
            .then_with(|| a.kind.cmp(&b.kind))
    });
    result.dedup();
    result
}

fn process_supertypes(
    info: &mut FieldInfoJSON,
    subtype_map: &HashMap<NodeTypeJSON, Vec<NodeTypeJSON>>,
) {
    for (supertype, subtypes) in subtype_map {
        if info.types.contains(supertype) {
            info.types.retain(|t| !subtypes.contains(t));
        }
    }
}

fn variable_type_for_child_type(
    child_type: &ChildType,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
) -> VariableType {
    match child_type {
        ChildType::Aliased(alias) => alias.kind(),
        ChildType::Normal(symbol) => {
            if syntax_grammar.supertype_symbols.contains(&symbol) {
                VariableType::Named
            } else if syntax_grammar.variables_to_inline.contains(&symbol) {
                VariableType::Hidden
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

fn sorted_vec_insert<T>(vec: &mut Vec<T>, value: &T) -> bool
where
    T: Clone + Eq + Ord,
{
    if let Err(i) = vec.binary_search(&value) {
        vec.insert(i, value.clone());
        true
    } else {
        false
    }
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
            extra_symbols: Vec::new(),
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
            extra_symbols: Vec::new(),
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
            extra_symbols: Vec::new(),
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
    fn test_node_types_with_inlined_rules() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            word_token: None,
            extra_symbols: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: vec!["v2".to_string()],
            supertype_symbols: vec![],
            variables: vec![
                Variable {
                    name: "v1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![Rule::named("v2"), Rule::named("v3")]),
                },
                // v2 should not appear in the node types, since it is inlined
                Variable {
                    name: "v2".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::alias(Rule::string("a"), "x".to_string(), true),
                },
                Variable {
                    name: "v3".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("b"),
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
                            kind: "v3".to_string(),
                            named: true,
                        },
                        NodeTypeJSON {
                            kind: "x".to_string(),
                            named: true,
                        },
                    ]
                }),
                fields: Some(BTreeMap::new()),
            }
        );
    }

    #[test]
    fn test_node_types_for_aliased_nodes() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            extra_symbols: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
            supertype_symbols: vec![],
            variables: vec![
                Variable {
                    name: "thing".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![Rule::named("type"), Rule::named("expression")]),
                },
                Variable {
                    name: "type".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![
                        Rule::alias(
                            Rule::named("identifier"),
                            "type_identifier".to_string(),
                            true,
                        ),
                        Rule::string("void"),
                    ]),
                },
                Variable {
                    name: "expression".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![
                        Rule::named("identifier"),
                        Rule::alias(
                            Rule::named("foo_identifier"),
                            "identifier".to_string(),
                            true,
                        ),
                    ]),
                },
                Variable {
                    name: "identifier".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("\\w+"),
                },
                Variable {
                    name: "foo_identifier".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("[\\w-]+"),
                },
            ],
        });

        assert_eq!(node_types.iter().find(|t| t.kind == "foo_identifier"), None);
        assert_eq!(
            node_types.iter().find(|t| t.kind == "identifier"),
            Some(&NodeInfoJSON {
                kind: "identifier".to_string(),
                named: true,
                subtypes: None,
                children: None,
                fields: None,
            })
        );
        assert_eq!(
            node_types.iter().find(|t| t.kind == "type_identifier"),
            Some(&NodeInfoJSON {
                kind: "type_identifier".to_string(),
                named: true,
                subtypes: None,
                children: None,
                fields: None,
            })
        );
    }

    #[test]
    fn test_node_types_with_multiple_valued_fields() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            extra_symbols: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
            supertype_symbols: vec![],
            variables: vec![
                Variable {
                    name: "a".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![
                        Rule::choice(vec![
                            Rule::Blank,
                            Rule::repeat(Rule::field("f1".to_string(), Rule::named("b"))),
                        ]),
                        Rule::repeat(Rule::named("c")),
                    ]),
                },
                Variable {
                    name: "b".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("b"),
                },
                Variable {
                    name: "c".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("c"),
                },
            ],
        });

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "a".to_string(),
                named: true,
                subtypes: None,
                children: Some(FieldInfoJSON {
                    multiple: true,
                    required: true,
                    types: vec![NodeTypeJSON {
                        kind: "c".to_string(),
                        named: true,
                    },]
                }),
                fields: Some(
                    vec![(
                        "f1".to_string(),
                        FieldInfoJSON {
                            multiple: true,
                            required: false,
                            types: vec![NodeTypeJSON {
                                kind: "b".to_string(),
                                named: true,
                            }]
                        }
                    )]
                    .into_iter()
                    .collect()
                ),
            }
        );
    }

    #[test]
    fn test_node_types_with_named_aliases() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            extra_symbols: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
            supertype_symbols: vec![],
            variables: vec![
                Variable {
                    name: "expression".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![Rule::named("yield"), Rule::named("argument_list")]),
                },
                Variable {
                    name: "yield".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::Seq(vec![Rule::string("YIELD")]),
                },
                Variable {
                    name: "argument_list".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![
                        Rule::named("x"),
                        Rule::alias(Rule::named("b"), "expression".to_string(), true),
                    ]),
                },
                Variable {
                    name: "b".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![
                        Rule::field("f".to_string(), Rule::string("B")),
                        Rule::named("c"),
                    ]),
                },
                Variable {
                    name: "c".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![Rule::string("C")]),
                },
                Variable {
                    name: "x".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![Rule::string("X")]),
                },
            ],
        });

        assert_eq!(
            node_types.iter().map(|n| &n.kind).collect::<Vec<_>>(),
            &[
                "argument_list",
                "c",
                "expression",
                "x",
                "yield",
                "B",
                "C",
                "X",
                "YIELD"
            ]
        );
        assert_eq!(
            node_types[2],
            NodeInfoJSON {
                kind: "expression".to_string(),
                named: true,
                subtypes: None,
                children: Some(FieldInfoJSON {
                    multiple: false,
                    required: false,
                    types: vec![
                        NodeTypeJSON {
                            kind: "argument_list".to_string(),
                            named: true,
                        },
                        NodeTypeJSON {
                            kind: "c".to_string(),
                            named: true,
                        },
                        NodeTypeJSON {
                            kind: "yield".to_string(),
                            named: true,
                        },
                    ]
                }),
                fields: Some(
                    vec![(
                        "f".to_string(),
                        FieldInfoJSON {
                            required: false,
                            multiple: false,
                            types: vec![NodeTypeJSON {
                                named: false,
                                kind: "B".to_string(),
                            }]
                        }
                    )]
                    .into_iter()
                    .collect()
                ),
            }
        );
    }

    #[test]
    fn test_node_types_with_tokens_aliased_to_match_rules() {
        let node_types = get_node_types(InputGrammar {
            name: String::new(),
            extra_symbols: Vec::new(),
            external_tokens: Vec::new(),
            expected_conflicts: Vec::new(),
            variables_to_inline: Vec::new(),
            word_token: None,
            supertype_symbols: vec![],
            variables: vec![
                Variable {
                    name: "a".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![Rule::named("b"), Rule::named("c")]),
                },
                // Ordinarily, `b` nodes have two named `c` children.
                Variable {
                    name: "b".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![Rule::named("c"), Rule::string("B"), Rule::named("c")]),
                },
                Variable {
                    name: "c".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::choice(vec![
                        Rule::string("C"),
                        // This token is aliased as a `b`, which will produce a `b` node
                        // with no children.
                        Rule::alias(Rule::string("D"), "b".to_string(), true),
                    ]),
                },
            ],
        });

        assert_eq!(
            node_types.iter().map(|n| &n.kind).collect::<Vec<_>>(),
            &["a", "b", "c", "B", "C"]
        );
        assert_eq!(
            node_types[1],
            NodeInfoJSON {
                kind: "b".to_string(),
                named: true,
                subtypes: None,
                children: Some(FieldInfoJSON {
                    multiple: true,
                    required: false,
                    types: vec![NodeTypeJSON {
                        kind: "c".to_string(),
                        named: true,
                    }]
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
            &AliasMap::new(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: true,
                        multiple: false,
                    },
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
                    quantity: ChildQuantity {
                        exists: true,
                        required: false,
                        multiple: false,
                    },
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
                        productions: vec![
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![
                                    ProductionStep::new(Symbol::terminal(0)),
                                    ProductionStep::new(Symbol::non_terminal(1)),
                                    ProductionStep::new(Symbol::terminal(1)),
                                ],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::non_terminal(1))],
                            },
                        ],
                    },
                    // Hidden node with fields
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(2)).with_alias(".", false),
                                ProductionStep::new(Symbol::terminal(3)).with_field_name("field1"),
                            ],
                        }],
                    },
                ],
                vec![],
            ),
            &build_lexical_grammar(),
            &AliasMap::new(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: true,
                        multiple: false,
                    },
                    types: vec![ChildType::Normal(Symbol::terminal(3))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );

        assert_eq!(
            variable_info[0].children_without_fields,
            FieldInfo {
                quantity: ChildQuantity {
                    exists: true,
                    required: false,
                    multiple: true,
                },
                types: vec![
                    ChildType::Normal(Symbol::terminal(0)),
                    ChildType::Normal(Symbol::terminal(1)),
                ],
            }
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
            &AliasMap::new(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: true,
                        multiple: false,
                    },
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
        let variable_info =
            get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases).unwrap();
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
