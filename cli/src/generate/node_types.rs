use super::grammars::{LexicalGrammar, SyntaxGrammar, VariableType};
use super::rules::{Alias, AliasMap, Symbol, SymbolType};
use crate::error::{Error, Result};
use serde_derive::Serialize;
use std::collections::{BTreeMap, HashMap, HashSet};
use std::mem;

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

#[derive(Debug, Serialize, PartialEq, Eq, PartialOrd, Ord)]
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
///    * `multiple` - Can `N` nodes have multiple named child with no field?
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
                        && (!child_type_is_visible(&child_type)
                            || syntax_grammar.variables_to_inline.contains(&child_symbol))
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

    for supertype_symbol in &syntax_grammar.supertype_symbols {
        result[supertype_symbol.index]
            .child_types
            .retain(child_type_is_visible);
    }

    // Update all of the node type lists to account for node visiblity:
    // * Wherever possible, repalce lists of subtypes with their supertypes.
    // * Remove other hidden node types.
    for i in 0..result.len() {
        let mut variable_info = VariableInfo::default();
        mem::swap(&mut variable_info, &mut result[i]);

        // For each named field, make the `types` list more concise by replacing sets of
        // subtypes with a single supertype. Also remove any hidden node types.
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

        // Do the same thing for the children without fields.
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
            subtypes.sort_unstable();
            subtypes.dedup();
            node_type_json.subtypes = Some(subtypes);
        } else if variable.kind.is_visible()
            && !syntax_grammar.variables_to_inline.contains(&symbol)
        {
            for alias in aliases_by_symbol
                .get(&Symbol::non_terminal(i))
                .unwrap_or(&HashSet::new())
            {
                let kind;
                let is_named;
                if let Some(alias) = alias {
                    kind = &alias.value;
                    is_named = alias.is_named;
                } else {
                    kind = &variable.name;
                    is_named = variable.kind == VariableType::Named;
                }

                let node_type_json =
                    node_types_json
                        .entry(kind.clone())
                        .or_insert_with(|| NodeInfoJSON {
                            kind: kind.clone(),
                            named: is_named,
                            fields: None,
                            children: None,
                            subtypes: None,
                        });
                let mut fields_json = BTreeMap::new();
                for (field, field_info) in info.fields.iter() {
                    let field_info_json =
                        fields_json.entry(field.clone()).or_insert(FieldInfoJSON {
                            multiple: false,
                            required: true,
                            types: Vec::new(),
                        });

                    field_info_json.multiple |= field_info.quantity.multiple;
                    field_info_json.required &= field_info.quantity.required;
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
                        multiple: info.children_without_fields.quantity.multiple,
                        required: info.children_without_fields.quantity.required,
                        types: children_types,
                    });
                }
            }
        }
    }

    let mut result = node_types_json.into_iter().map(|e| e.1).collect::<Vec<_>>();

    for (i, variable) in lexical_grammar.variables.iter().enumerate() {
        for alias in aliases_by_symbol
            .get(&Symbol::terminal(i))
            .unwrap_or(&HashSet::new())
        {
            let kind;
            let is_named;
            if let Some(alias) = alias {
                kind = &alias.value;
                is_named = alias.is_named;
            } else {
                kind = &variable.name;
                is_named = variable.kind == VariableType::Named;
            }

            if variable.kind == VariableType::Named {
                result.push(NodeInfoJSON {
                    kind: kind.clone(),
                    named: is_named,
                    fields: None,
                    children: None,
                    subtypes: None,
                });
            } else if variable.kind == VariableType::Anonymous {
                result.push(NodeInfoJSON {
                    kind: kind.clone(),
                    named: is_named,
                    fields: None,
                    children: None,
                    subtypes: None,
                });
            }
        }
    }

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

        //
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
        let variable_info = get_variable_info(&syntax_grammar, &lexical_grammar).unwrap();
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
