use std::collections::{BTreeMap, BTreeSet};

use rustc_hash::FxHashMap;
#[cfg(feature = "load")]
use rustc_hash::FxHashSet;

use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::strpool::StrPool;

use super::{
    grammars::{LexicalGrammar, SyntaxGrammar, VariableType},
    rules::{Alias, AliasMap, Symbol, SymbolType},
    strpool::StrId,
};

#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum ChildType {
    Normal(Symbol),
    Aliased(Alias),
}

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct FieldInfo {
    pub quantity: ChildQuantity,
    pub types: Vec<ChildType>,
}

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct VariableInfo {
    pub fields: FxHashMap<StrId, FieldInfo>,
    pub children: FieldInfo,
    pub children_without_fields: FieldInfo,
    pub has_multi_step_production: bool,
}

#[derive(Debug, Serialize, PartialEq, Eq, Default, PartialOrd, Ord)]
#[cfg(feature = "load")]
pub struct NodeInfoJSON {
    #[serde(rename = "type")]
    kind: String,
    named: bool,
    #[serde(skip_serializing_if = "std::ops::Not::not")]
    root: bool,
    #[serde(skip_serializing_if = "std::ops::Not::not")]
    extra: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    fields: Option<BTreeMap<String, FieldInfoJSON>>,
    #[serde(skip_serializing_if = "Option::is_none")]
    children: Option<FieldInfoJSON>,
    #[serde(skip_serializing_if = "Option::is_none")]
    subtypes: Option<Vec<NodeTypeJSON>>,
}

#[derive(Clone, Debug, Serialize, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[cfg(feature = "load")]
pub struct NodeTypeJSON {
    #[serde(rename = "type")]
    kind: String,
    named: bool,
}

#[derive(Debug, Serialize, PartialEq, Eq, PartialOrd, Ord)]
#[cfg(feature = "load")]
pub struct FieldInfoJSON {
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

#[cfg(feature = "load")]
impl Default for FieldInfoJSON {
    fn default() -> Self {
        Self {
            multiple: false,
            required: true,
            types: Vec::new(),
        }
    }
}

impl Default for ChildQuantity {
    fn default() -> Self {
        Self::one()
    }
}

impl ChildQuantity {
    #[must_use]
    const fn zero() -> Self {
        Self {
            exists: false,
            required: false,
            multiple: false,
        }
    }

    #[must_use]
    const fn one() -> Self {
        Self {
            exists: true,
            required: true,
            multiple: false,
        }
    }

    const fn append(&mut self, other: Self) {
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

    const fn union(&mut self, other: Self) -> bool {
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

pub type VariableInfoResult<T> = Result<T, VariableInfoError>;

#[derive(Debug, Error, Serialize, Deserialize)]
pub enum VariableInfoError {
    #[error(transparent)]
    InvalidSupertype(InvalidSupertypeError),
}

#[derive(Debug, Error, Serialize, Deserialize)]
pub struct InvalidSupertypeError {
    supertype: String,
    child: Option<String>,
}

impl std::fmt::Display for InvalidSupertypeError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let supertype = &self.supertype;
        write!(
            f,
            "Supertypes must have a single visible child, but `{supertype}` can have multiple."
        )?;

        if let Some(child) = &self.child {
            write!(
                f,
                " The hidden child `{child}` can expand into multiple nodes. Consider making `{child}` visible."
            )?;
        }

        Ok(())
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
/// 3. `children_without_fields` - The *other* named children of `N` that are not associated with
///    fields. Data regarding these children:
///    * `types` - The types of named children with no field.
///    * `optional` - Do `N` nodes always have at least one named child with no field?
///    * `multiple` - Can `N` nodes have multiple named children with no field?
///
/// Each summary must account for some indirect factors:
/// 1. hidden nodes. When a parent node `N` has a hidden child `C`, the visible children of `C`
///    *appear* to be direct children of `N`.
/// 2. aliases. If a parent node type `M` is aliased as some other type `N`, then nodes which
///    *appear* to have type `N` may have internal structure based on `M`.
pub fn get_variable_info(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    default_aliases: &AliasMap,
    str_pool: &StrPool,
) -> VariableInfoResult<Vec<VariableInfo>> {
    let child_type_is_visible = |t: &ChildType| {
        variable_type_for_child_type(t, syntax_grammar, lexical_grammar) >= VariableType::Anonymous
    };

    let child_type_is_named = |t: &ChildType| {
        variable_type_for_child_type(t, syntax_grammar, lexical_grammar) == VariableType::Named
    };

    // Each variable's summary can depend on the summaries of other hidden variables,
    // and variables can have mutually recursive structure. So we compute the summaries
    // iteratively, in a loop that terminates only when no more changes are possible.
    let mut did_change = true;
    let mut all_initialized = false;
    let mut result = vec![VariableInfo::default(); syntax_grammar.variables.len()];
    while did_change {
        did_change = false;

        for i in 0..syntax_grammar.variables.len() {
            let mut variable_info = result[i].clone();

            // Examine each of the variable's productions. The variable's child types can be
            // immediately combined across all productions, but the child quantities must be
            // recorded separately for each production.
            for prod_id in syntax_grammar.variable_prod_ids(i) {
                let production = syntax_grammar.production(prod_id);
                let mut production_field_quantities = FxHashMap::default();
                let mut production_children_quantity = ChildQuantity::zero();
                let mut production_children_without_fields_quantity = ChildQuantity::zero();
                let mut production_has_uninitialized_invisible_children = false;

                if production.steps.len() > 1 {
                    variable_info.has_multi_step_production = true;
                }

                for step in production.steps {
                    let child_symbol = step.symbol();
                    let child_type = step.child_type(default_aliases);

                    let child_is_hidden = !child_type_is_visible(&child_type)
                        && !syntax_grammar.supertype_symbols.contains(&child_symbol);

                    // Maintain the set of all child types for this variable, and the quantity of
                    // visible children in this production.
                    did_change |=
                        extend_sorted(&mut variable_info.children.types, Some(&child_type));
                    if !child_is_hidden {
                        production_children_quantity.append(ChildQuantity::one());
                    }

                    // Maintain the set of child types associated with each field, and the quantity
                    // of children associated with each field in this production.
                    if let Some(field_name) = step.field() {
                        let field_info = variable_info
                            .fields
                            .entry(field_name)
                            .or_insert_with(FieldInfo::default);
                        did_change |= extend_sorted(&mut field_info.types, Some(&child_type));

                        let production_field_quantity = production_field_quantities
                            .entry(field_name)
                            .or_insert_with(ChildQuantity::zero);

                        // Inherit the types and quantities of hidden children associated with
                        // fields.
                        if child_is_hidden && child_symbol.is_non_terminal() {
                            let child_variable_info = &result[child_symbol.index as usize];
                            did_change |= extend_sorted(
                                &mut field_info.types,
                                &child_variable_info.children.types,
                            );
                            production_field_quantity.append(child_variable_info.children.quantity);
                        } else {
                            production_field_quantity.append(ChildQuantity::one());
                        }
                    }
                    // Maintain the set of named children without fields within this variable.
                    else if child_type_is_named(&child_type) {
                        production_children_without_fields_quantity.append(ChildQuantity::one());
                        did_change |= extend_sorted(
                            &mut variable_info.children_without_fields.types,
                            Some(&child_type),
                        );
                    }

                    // Inherit all child information from hidden children.
                    if child_is_hidden && child_symbol.is_non_terminal() {
                        let child_variable_info = &result[child_symbol.index as usize];

                        // If a hidden child can have multiple children, then its parent node can
                        // appear to have multiple children.
                        if child_variable_info.has_multi_step_production {
                            variable_info.has_multi_step_production = true;
                        }

                        // If a hidden child has fields, then the parent node can appear to have
                        // those same fields.
                        for (&field_name, child_field_info) in &child_variable_info.fields {
                            production_field_quantities
                                .entry(field_name)
                                .or_insert_with(ChildQuantity::zero)
                                .append(child_field_info.quantity);
                            did_change |= extend_sorted(
                                &mut variable_info
                                    .fields
                                    .entry(field_name)
                                    .or_insert_with(FieldInfo::default)
                                    .types,
                                &child_field_info.types,
                            );
                        }

                        // If a hidden child has children, then the parent node can appear to have
                        // those same children.
                        production_children_quantity.append(child_variable_info.children.quantity);
                        did_change |= extend_sorted(
                            &mut variable_info.children.types,
                            &child_variable_info.children.types,
                        );

                        // If a hidden child can have named children without fields, then the parent
                        // node can appear to have those same children.
                        if step.field().is_none() {
                            let grandchildren_info = &child_variable_info.children_without_fields;
                            if !grandchildren_info.types.is_empty() {
                                production_children_without_fields_quantity
                                    .append(child_variable_info.children_without_fields.quantity);
                                did_change |= extend_sorted(
                                    &mut variable_info.children_without_fields.types,
                                    &child_variable_info.children_without_fields.types,
                                );
                            }
                        }
                    }

                    // Note whether or not this production contains children whose summaries
                    // have not yet been computed.
                    if child_symbol.index as usize >= i && !all_initialized {
                        production_has_uninitialized_invisible_children = true;
                    }
                }

                // If this production's children all have had their summaries initialized,
                // then expand the quantity information with all of the possibilities introduced
                // by this production.
                if !production_has_uninitialized_invisible_children {
                    did_change |= variable_info
                        .children
                        .quantity
                        .union(production_children_quantity);

                    did_change |= variable_info
                        .children_without_fields
                        .quantity
                        .union(production_children_without_fields_quantity);

                    for (field_name, info) in &mut variable_info.fields {
                        did_change |= info.quantity.union(
                            production_field_quantities
                                .get(field_name)
                                .copied()
                                .unwrap_or_else(ChildQuantity::zero),
                        );
                    }
                }
            }

            result[i] = variable_info;
        }

        all_initialized = true;
    }

    for supertype_symbol in &syntax_grammar.supertype_symbols {
        if result[supertype_symbol.index as usize].has_multi_step_production {
            let variable = &syntax_grammar.variables[supertype_symbol.index as usize];
            // A symbol can have a multi-step production either directly or via an inlined
            // anonymous child. In the latter case, we can report a more specific error.

            let hidden_child_name = syntax_grammar
                .variable_prod_ids(supertype_symbol.index as usize)
                .filter(|&prod_id| syntax_grammar.production(prod_id).steps.len() == 1)
                .find_map(|prod_id| {
                    let step = syntax_grammar.production(prod_id).steps[0];
                    let child_symbol = step.symbol();
                    let child_type = step.child_type(default_aliases);
                    let child_is_hidden = !child_type_is_visible(&child_type)
                        && !syntax_grammar.supertype_symbols.contains(&child_symbol);
                    (child_is_hidden
                        && child_symbol.is_non_terminal()
                        && result[child_symbol.index as usize].has_multi_step_production)
                        .then(|| {
                            str_pool
                                .resolve(syntax_grammar.variables[child_symbol.index as usize].name)
                                .to_string()
                        })
                });

            Err(VariableInfoError::InvalidSupertype(InvalidSupertypeError {
                supertype: str_pool.resolve(variable.name).to_string(),
                child: hidden_child_name,
            }))?;
        }
    }

    // Update all of the node type lists to eliminate hidden nodes.
    for supertype_symbol in &syntax_grammar.supertype_symbols {
        result[supertype_symbol.index as usize]
            .children
            .types
            .retain(child_type_is_visible);
    }
    for variable_info in &mut result {
        for field_info in variable_info.fields.values_mut() {
            field_info.types.retain(child_type_is_visible);
        }
        variable_info.fields.retain(|_, v| !v.types.is_empty());
        variable_info
            .children_without_fields
            .types
            .retain(child_type_is_visible);
    }

    Ok(result)
}

fn get_aliases_by_symbol(
    syntax_grammar: &SyntaxGrammar,
    default_aliases: &AliasMap,
) -> FxHashMap<Symbol, BTreeSet<Option<Alias>>> {
    let mut aliases_by_symbol = FxHashMap::default();
    for (symbol, &alias) in default_aliases {
        aliases_by_symbol.insert(*symbol, {
            let mut aliases = BTreeSet::new();
            aliases.insert(Some(alias));
            aliases
        });
    }
    for extra_symbol in &syntax_grammar.extra_symbols {
        if !default_aliases.contains_key(extra_symbol) {
            aliases_by_symbol
                .entry(*extra_symbol)
                .or_insert_with(BTreeSet::new)
                .insert(None);
        }
    }
    for i in 0..syntax_grammar.variables.len() {
        for prod_id in syntax_grammar.variable_prod_ids(i) {
            for step in syntax_grammar.production(prod_id).steps {
                aliases_by_symbol
                    .entry(step.symbol())
                    .or_insert_with(BTreeSet::new)
                    .insert(
                        step.alias()
                            .as_ref()
                            .or_else(|| default_aliases.get(&step.symbol()))
                            .copied(),
                    );
            }
        }
    }
    aliases_by_symbol.insert(
        Symbol::non_terminal(0),
        std::iter::once(&None).copied().collect(),
    );
    aliases_by_symbol
}

pub fn get_supertype_symbol_map(
    syntax_grammar: &SyntaxGrammar,
    default_aliases: &AliasMap,
    variable_info: &[VariableInfo],
) -> BTreeMap<Symbol, Vec<ChildType>> {
    let aliases_by_symbol = get_aliases_by_symbol(syntax_grammar, default_aliases);
    let mut supertype_symbol_map = BTreeMap::new();

    let mut symbols_by_alias = FxHashMap::default();
    for (symbol, aliases) in &aliases_by_symbol {
        for alias in aliases.iter().flatten() {
            symbols_by_alias
                .entry(alias)
                .or_insert_with(Vec::new)
                .push(*symbol);
        }
    }

    for (i, info) in variable_info.iter().enumerate() {
        let symbol = Symbol::non_terminal(i);
        if syntax_grammar.supertype_symbols.contains(&symbol) {
            let subtypes = info.children.types.clone();
            supertype_symbol_map.insert(symbol, subtypes);
        }
    }
    supertype_symbol_map
}

#[cfg(feature = "load")]
pub type SuperTypeCycleResult<T> = Result<T, SuperTypeCycleError>;

#[derive(Debug, Error, Serialize, Deserialize)]
pub struct SuperTypeCycleError {
    items: Vec<String>,
}

impl std::fmt::Display for SuperTypeCycleError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Dependency cycle detected in node types:")?;
        for (i, item) in self.items.iter().enumerate() {
            write!(f, " {item}")?;
            if i < self.items.len() - 1 {
                write!(f, ",")?;
            }
        }

        Ok(())
    }
}

#[cfg(feature = "load")]
pub fn generate_node_types_json(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    default_aliases: &AliasMap,
    variable_info: &[VariableInfo],
    str_pool: &StrPool,
) -> SuperTypeCycleResult<Vec<NodeInfoJSON>> {
    let mut node_types_json = BTreeMap::new();

    let child_type_to_node_type = |child_type: &ChildType| match child_type {
        ChildType::Aliased(alias) => NodeTypeJSON {
            kind: str_pool.resolve(alias.value).to_string(),
            named: alias.is_named,
        },
        ChildType::Normal(symbol) => {
            if let Some(alias) = default_aliases.get(symbol) {
                NodeTypeJSON {
                    kind: str_pool.resolve(alias.value).to_string(),
                    named: alias.is_named,
                }
            } else {
                match symbol.kind {
                    SymbolType::NonTerminal => {
                        let variable = &syntax_grammar.variables[symbol.index as usize];
                        NodeTypeJSON {
                            kind: str_pool.resolve(variable.name).to_string(),
                            named: variable.kind != VariableType::Anonymous,
                        }
                    }
                    SymbolType::Terminal => {
                        let variable = &lexical_grammar.variables[symbol.index as usize];
                        NodeTypeJSON {
                            kind: str_pool.resolve(variable.name).to_string(),
                            named: variable.kind != VariableType::Anonymous,
                        }
                    }
                    SymbolType::External => {
                        let variable = &syntax_grammar.external_tokens[symbol.index as usize];
                        NodeTypeJSON {
                            kind: str_pool.resolve(variable.name).to_string(),
                            named: variable.kind != VariableType::Anonymous,
                        }
                    }
                    _ => panic!("Unexpected symbol type"),
                }
            }
        }
    };

    let populate_field_info_json = |json: &mut FieldInfoJSON, info: &FieldInfo| {
        if info.types.is_empty() {
            json.required = false;
        } else {
            json.multiple |= info.quantity.multiple;
            json.required &= info.quantity.required;
            json.types
                .extend(info.types.iter().map(child_type_to_node_type));
            json.types.sort_unstable();
            json.types.dedup();
        }
    };

    let aliases_by_symbol = get_aliases_by_symbol(syntax_grammar, default_aliases);

    let empty = BTreeSet::new();
    let extra_names = syntax_grammar
        .extra_symbols
        .iter()
        .flat_map(|symbol| {
            aliases_by_symbol
                .get(symbol)
                .unwrap_or(&empty)
                .iter()
                .map(|alias| {
                    alias.as_ref().map_or_else(
                        || match symbol.kind {
                            SymbolType::NonTerminal => {
                                &syntax_grammar.variables[symbol.index as usize].name
                            }
                            SymbolType::Terminal => {
                                &lexical_grammar.variables[symbol.index as usize].name
                            }
                            SymbolType::External => {
                                &syntax_grammar.external_tokens[symbol.index as usize].name
                            }
                            _ => unreachable!(),
                        },
                        |alias| &alias.value,
                    )
                })
        })
        .collect::<FxHashSet<_>>();

    let mut subtype_map = Vec::new();
    for (i, info) in variable_info.iter().enumerate() {
        let symbol = Symbol::non_terminal(i);
        let variable = &syntax_grammar.variables[i];
        if syntax_grammar.supertype_symbols.contains(&symbol) {
            let node_type_json =
                node_types_json
                    .entry(variable.name)
                    .or_insert_with(|| NodeInfoJSON {
                        kind: str_pool.resolve(variable.name).to_string(),
                        named: true,
                        root: false,
                        extra: extra_names.contains(&variable.name),
                        fields: None,
                        children: None,
                        subtypes: None,
                    });
            let mut subtypes = info
                .children
                .types
                .iter()
                .map(child_type_to_node_type)
                .collect::<Vec<_>>();
            subtypes.sort_unstable();
            subtypes.dedup();
            let supertype = NodeTypeJSON {
                kind: node_type_json.kind.clone(),
                named: true,
            };

            // We only add to the subtype map if there are visible subtypes.
            // A supertype may have zero subtypes if its children are all
            // hidden (e.g., wrapping a hidden external token).
            if !subtypes.is_empty() {
                subtype_map.push((supertype, subtypes.clone()));
            }
            node_type_json.subtypes = Some(subtypes);
        } else if !syntax_grammar.variables_to_inline.contains(&symbol) {
            // If a rule is aliased under multiple names, then its information
            // contributes to multiple entries in the final JSON.
            for alias in aliases_by_symbol.get(&symbol).unwrap_or(&BTreeSet::new()) {
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
                let mut node_type_existed = true;
                let node_type_json = node_types_json.entry(*kind).or_insert_with(|| {
                    node_type_existed = false;
                    NodeInfoJSON {
                        kind: str_pool.resolve(*kind).to_string(),
                        named: is_named,
                        root: i == 0,
                        extra: extra_names.contains(&kind),
                        fields: Some(BTreeMap::new()),
                        children: None,
                        subtypes: None,
                    }
                });

                let fields_json = node_type_json.fields.as_mut().unwrap();
                for (new_field, field_info) in &info.fields {
                    let field_json = fields_json
                        .entry(str_pool.resolve(*new_field).to_string())
                        .or_insert_with(|| {
                            // If another rule is aliased with the same name, and does *not* have this
                            // field, then this field cannot be required.
                            let mut field_json = FieldInfoJSON::default();
                            if node_type_existed {
                                field_json.required = false;
                            }
                            field_json
                        });
                    populate_field_info_json(field_json, field_info);
                }

                // If another rule is aliased with the same name, any fields that aren't present in
                // this cannot be required.
                for (existing_field, field_json) in fields_json.iter_mut() {
                    if !info
                        .fields
                        .keys()
                        .any(|&f| str_pool.resolve(f).eq(existing_field))
                    {
                        field_json.required = false;
                    }
                }

                populate_field_info_json(
                    node_type_json
                        .children
                        .get_or_insert_with(FieldInfoJSON::default),
                    &info.children_without_fields,
                );
            }
        }
    }

    // Handle aliases that don't correspond to any existing named type.
    // These are aliases that are only used as aliases and never as direct references.
    for (symbol, aliases) in &aliases_by_symbol {
        for alias in aliases.iter().flatten() {
            // Check if this alias name already exists in node_types_json
            if !node_types_json.contains_key(&alias.value) {
                // This alias doesn't correspond to any existing type, so we need to create one

                let info = &variable_info[symbol.index];

                let mut node_type_existed = true;
                let node_type_json =
                    node_types_json
                        .entry(alias.value.clone())
                        .or_insert_with(|| {
                            node_type_existed = false;
                            NodeInfoJSON {
                                kind: alias.value.clone(),
                                named: alias.is_named,
                                root: false,
                                extra: false,
                                fields: Some(BTreeMap::new()),
                                children: None,
                                subtypes: None,
                            }
                        });

                let fields_json = node_type_json.fields.as_mut().unwrap();
                for (new_field, field_info) in &info.fields {
                    let field_json = fields_json.entry(new_field.clone()).or_insert_with(|| {
                        // If another rule is aliased with the same name, and does *not* have this
                        // field, then this field cannot be required.
                        let mut field_json = FieldInfoJSON::default();
                        if node_type_existed {
                            field_json.required = false;
                        }
                        field_json
                    });
                    populate_field_info_json(field_json, field_info);
                }

                // If another rule is aliased with the same name, any fields that aren't present in
                // this cannot be required.
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

    // Sort the subtype map topologically so that subtypes are listed before their supertypes.
    let mut sorted_kinds = Vec::with_capacity(subtype_map.len());
    let mut top_sort = topological_sort::TopologicalSort::<String>::new();
    for (supertype, subtypes) in &subtype_map {
        for subtype in subtypes {
            top_sort.add_dependency(subtype.kind.clone(), supertype.kind.clone());
        }
    }
    loop {
        let mut next_kinds = top_sort.pop_all();
        match (next_kinds.is_empty(), top_sort.is_empty()) {
            (true, true) => break,
            (true, false) => {
                let mut items = top_sort.collect::<Vec<String>>();
                items.sort();
                return Err(SuperTypeCycleError { items });
            }
            (false, _) => {
                next_kinds.sort();
                sorted_kinds.extend(next_kinds);
            }
        }
    }
    subtype_map.sort_by(|a, b| {
        let a_idx = sorted_kinds.iter().position(|n| n.eq(&a.0.kind)).unwrap();
        let b_idx = sorted_kinds.iter().position(|n| n.eq(&b.0.kind)).unwrap();
        a_idx.cmp(&b_idx)
    });

    for node_type_json in node_types_json.values_mut() {
        if node_type_json
            .children
            .as_ref()
            .is_some_and(|c| c.types.is_empty())
        {
            node_type_json.children = None;
        }

        if let Some(children) = &mut node_type_json.children {
            process_supertypes(children, &subtype_map);
        }
        if let Some(fields) = &mut node_type_json.fields {
            for field_info in fields.values_mut() {
                process_supertypes(field_info, &subtype_map);
            }
        }
    }

    let mut anonymous_node_types = Vec::new();

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
                    alias
                        .as_ref()
                        .map_or((&variable.name, variable.kind), |alias| {
                            (&alias.value, alias.kind())
                        })
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
                        alias.as_ref().map_or((&token.name, token.kind), |alias| {
                            (&alias.value, alias.kind())
                        })
                    })
            });

    for (&name, kind) in regular_tokens.chain(external_tokens) {
        match kind {
            VariableType::Named => {
                let node_type_json = node_types_json.entry(name).or_insert_with(|| NodeInfoJSON {
                    kind: str_pool.resolve(name).to_string(),
                    named: true,
                    root: false,
                    extra: extra_names.contains(&name),
                    fields: None,
                    children: None,
                    subtypes: None,
                });
                if let Some(children) = &mut node_type_json.children {
                    children.required = false;
                }
                if let Some(fields) = &mut node_type_json.fields {
                    for field in fields.values_mut() {
                        field.required = false;
                    }
                }
            }
            VariableType::Anonymous => anonymous_node_types.push(NodeInfoJSON {
                kind: str_pool.resolve(name).to_string(),
                named: false,
                root: false,
                extra: extra_names.contains(&name),
                fields: None,
                children: None,
                subtypes: None,
            }),
            _ => {}
        }
    }

    let mut result = node_types_json.into_iter().map(|e| e.1).collect::<Vec<_>>();
    result.extend(anonymous_node_types);
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
            .then_with(|| a.named.cmp(&b.named))
            .then_with(|| a.root.cmp(&b.root))
            .then_with(|| a.extra.cmp(&b.extra))
    });
    result.dedup();
    Ok(result)
}

#[cfg(feature = "load")]
fn process_supertypes(info: &mut FieldInfoJSON, subtype_map: &[(NodeTypeJSON, Vec<NodeTypeJSON>)]) {
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
            if syntax_grammar.supertype_symbols.contains(symbol) {
                VariableType::Named
            } else if syntax_grammar.variables_to_inline.contains(symbol) {
                VariableType::Hidden
            } else {
                let symbol_index = symbol.index as usize;
                match symbol.kind {
                    SymbolType::NonTerminal => syntax_grammar.variables[symbol_index].kind,
                    SymbolType::Terminal => lexical_grammar.variables[symbol_index].kind,
                    SymbolType::External => syntax_grammar.external_tokens[symbol_index].kind,
                    _ => VariableType::Hidden,
                }
            }
        }
    }
}

fn extend_sorted<'a, T>(vec: &mut Vec<T>, values: impl IntoIterator<Item = &'a T>) -> bool
where
    T: 'a + Clone + Eq + Ord,
{
    values.into_iter().fold(false, |acc, value| {
        if let Err(i) = vec.binary_search(value) {
            vec.insert(i, value.clone());
            true
        } else {
            acc
        }
    })
}

#[cfg(all(test, feature = "load"))]
mod tests {
    use super::*;
    use crate::{
        grammars::{
            InputGrammar, LexicalVariable, Production, ProductionStep, SyntaxVariable, Variable,
        },
        prepare_grammar::{PreparedGrammar, prepare_grammar},
        rules::{Alias, Precedence, Rule, RuleId, RulePool},
        strpool::StrPool,
    };

    #[test]
    fn test_node_types_simple() {
        let mut pool = RulePool::default();
        let v1 = {
            let f1 = {
                let v2 = named(&mut pool, "v2");
                field(&mut pool, "f1", v2)
            };
            let f2 = {
                let semi = string(&mut pool, ";");
                field(&mut pool, "f2", semi)
            };
            pool.seq(&[f1, f2])
        };
        let v2 = string(&mut pool, "x");
        let v3 = string(&mut pool, "y");
        let node_types = get_node_types(InputGrammar {
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                Variable {
                    name: pool.intern("v2"),
                    root: v2,
                },
                // This rule is not reachable from the start symbol
                // so it won't be present in the node_types
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(node_types.len(), 3);

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "v1".to_string(),
                named: true,
                root: true,
                extra: false,
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
                root: false,
                extra: false,
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
                root: false,
                extra: false,
                subtypes: None,
                children: None,
                fields: None
            }
        );
    }

    #[test]
    fn test_node_types_simple_extras() {
        let mut pool = RulePool::default();
        let v1 = {
            let f1 = {
                let v2 = named(&mut pool, "v2");
                field(&mut pool, "f1", v2)
            };
            let f2 = {
                let semi = string(&mut pool, ";");
                field(&mut pool, "f2", semi)
            };
            pool.seq(&[f1, f2])
        };
        let v2 = string(&mut pool, "x");
        let v3 = string(&mut pool, "y");
        let extra = named(&mut pool, "v3");
        let node_types = get_node_types(InputGrammar {
            extra_roots: vec![extra],
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                Variable {
                    name: pool.intern("v2"),
                    root: v2,
                },
                // This rule is not reachable from the start symbol, but
                // it is reachable from the 'extra_symbols' so it
                // should be present in the node_types.
                // But because it's only a literal, it will get replaced by
                // a lexical variable.
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(node_types.len(), 4);

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "v1".to_string(),
                named: true,
                root: true,
                extra: false,
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
                root: false,
                extra: false,
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
                root: false,
                extra: false,
                subtypes: None,
                children: None,
                fields: None
            }
        );
        assert_eq!(
            node_types[3],
            NodeInfoJSON {
                kind: "v3".to_string(),
                named: true,
                root: false,
                extra: true,
                subtypes: None,
                children: None,
                fields: None
            }
        );
    }

    #[test]
    fn test_node_types_deeper_extras() {
        let mut pool = RulePool::default();
        let v1 = {
            let f1 = {
                let v2 = named(&mut pool, "v2");
                field(&mut pool, "f1", v2)
            };
            let f2 = {
                let semi = string(&mut pool, ";");
                field(&mut pool, "f2", semi)
            };
            pool.seq(&[f1, f2])
        };
        let v2 = string(&mut pool, "x");
        let v3 = {
            let y = string(&mut pool, "y");
            let z = {
                let z = string(&mut pool, "z");
                pool.repeat(z)
            };
            pool.seq(&[y, z])
        };
        let extra = named(&mut pool, "v3");
        let node_types = get_node_types(InputGrammar {
            extra_roots: vec![extra],
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                Variable {
                    name: pool.intern("v2"),
                    root: v2,
                },
                // This rule is not reachable from the start symbol, but
                // it is reachable from the 'extra_symbols' so it
                // should be present in the node_types.
                // Because it is not just a literal, it won't get replaced
                // by a lexical variable.
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(node_types.len(), 6);

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "v1".to_string(),
                named: true,
                root: true,
                extra: false,
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
                kind: "v3".to_string(),
                named: true,
                root: false,
                extra: true,
                subtypes: None,
                children: None,
                fields: Some(BTreeMap::default())
            }
        );
        assert_eq!(
            node_types[2],
            NodeInfoJSON {
                kind: ";".to_string(),
                named: false,
                root: false,
                extra: false,
                subtypes: None,
                children: None,
                fields: None
            }
        );
        assert_eq!(
            node_types[3],
            NodeInfoJSON {
                kind: "v2".to_string(),
                named: true,
                root: false,
                extra: false,
                subtypes: None,
                children: None,
                fields: None
            }
        );
    }

    #[test]
    fn test_node_types_with_supertypes() {
        let mut pool = RulePool::default();
        let v1 = {
            let inner = named(&mut pool, "_v2");
            field(&mut pool, "f1", inner)
        };
        let v2 = {
            let (a, b, c) = (
                named(&mut pool, "v3"),
                named(&mut pool, "v4"),
                string(&mut pool, "*"),
            );
            pool.choice(&[a, b, c])
        };
        let v3 = string(&mut pool, "x");
        let v4 = string(&mut pool, "y");
        let node_types = get_node_types(InputGrammar {
            supertype_names: vec![pool.intern("_v2")],
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                Variable {
                    name: pool.intern("_v2"),
                    root: v2,
                },
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
                Variable {
                    name: pool.intern("v4"),
                    root: v4,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "_v2".to_string(),
                named: true,
                root: false,
                extra: false,
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
                root: true,
                extra: false,
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

    /// A supertype whose only child is a hidden external token
    /// xgust not cause generation to panic. The subtype map must
    /// skip entries with empty subtypes to avoid a lookup failure
    /// in the topological sort.
    #[test]
    fn test_node_types_supertype_with_only_hidden_child() {
        let mut pool = RulePool::default();
        let v1 = {
            let (a, b) = (named(&mut pool, "_type_a"), named(&mut pool, "_type_b"));
            pool.seq(&[a, b])
        };
        let type_a = {
            let (a, b) = (named(&mut pool, "v2"), named(&mut pool, "v3"));
            pool.choice(&[a, b])
        };
        let v2 = string(&mut pool, "x");
        let v3 = string(&mut pool, "y");
        let type_b = external(&mut pool, 0);
        let hidden_ext = named(&mut pool, "_hidden_ext");
        let node_types = get_node_types(InputGrammar {
            supertype_names: vec![pool.intern("_type_a"), pool.intern("_type_b")],
            external_roots: vec![hidden_ext],
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                // Supertype A: a normal choice of named subtypes
                Variable {
                    name: pool.intern("_type_a"),
                    root: type_a,
                },
                Variable {
                    name: pool.intern("v2"),
                    root: v2,
                },
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
                // Supertype B: a hidden external token with no subtypes
                Variable {
                    name: pool.intern("_type_b"),
                    root: type_b,
                },
            ],
            pool,
            ..Default::default()
        });
        assert!(node_types.is_ok());
    }

    #[test]
    fn test_node_types_for_children_without_fields() {
        let mut pool = RulePool::default();
        let v1 = {
            let a = named(&mut pool, "v2");
            let f1 = {
                let v3 = named(&mut pool, "v3");
                field(&mut pool, "f1", v3)
            };
            let c = named(&mut pool, "v4");
            pool.seq(&[a, f1, c])
        };
        let v2 = {
            let open = string(&mut pool, "{");
            let mid = {
                let v3 = named(&mut pool, "v3");
                let blank = pool.blank();
                pool.choice(&[v3, blank])
            };
            let close = string(&mut pool, "}");
            pool.seq(&[open, mid, close])
        };
        let v3 = string(&mut pool, "x");
        let v4 = string(&mut pool, "y");
        let node_types = get_node_types(InputGrammar {
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                Variable {
                    name: pool.intern("v2"),
                    root: v2,
                },
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
                Variable {
                    name: pool.intern("v4"),
                    root: v4,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "v1".to_string(),
                named: true,
                root: true,
                extra: false,
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
                root: false,
                extra: false,
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
        let mut pool = RulePool::default();
        let v1 = {
            let (a, b) = (named(&mut pool, "v2"), named(&mut pool, "v3"));
            pool.seq(&[a, b])
        };
        let v2 = {
            let a = string(&mut pool, "a");
            alias(&mut pool, a, "x", true)
        };
        let v3 = string(&mut pool, "b");
        let node_types = get_node_types(InputGrammar {
            inline_names: vec![pool.intern("v2")],
            variables: vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1,
                },
                // v2 should not appear in the node types, since it is inlined
                Variable {
                    name: pool.intern("v2"),
                    root: v2,
                },
                Variable {
                    name: pool.intern("v3"),
                    root: v3,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "v1".to_string(),
                named: true,
                root: true,
                extra: false,
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
        let mut pool = RulePool::default();
        let thing = {
            let (a, b) = (named(&mut pool, "type"), named(&mut pool, "expression"));
            pool.choice(&[a, b])
        };
        let ty = {
            let id = {
                let inner = named(&mut pool, "identifier");
                alias(&mut pool, inner, "type_identifier", true)
            };
            let void = string(&mut pool, "void");
            pool.choice(&[id, void])
        };
        let expression = {
            let id = named(&mut pool, "identifier");
            let foo = {
                let inner = named(&mut pool, "foo_identifier");
                alias(&mut pool, inner, "identifier", true)
            };
            pool.choice(&[id, foo])
        };
        let identifier = pattern(&mut pool, "\\w+");
        let foo_identifier = pattern(&mut pool, "[\\w-]+");
        let node_types = get_node_types(InputGrammar {
            variables: vec![
                Variable {
                    name: pool.intern("thing"),
                    root: thing,
                },
                Variable {
                    name: pool.intern("type"),
                    root: ty,
                },
                Variable {
                    name: pool.intern("expression"),
                    root: expression,
                },
                Variable {
                    name: pool.intern("identifier"),
                    root: identifier,
                },
                Variable {
                    name: pool.intern("foo_identifier"),
                    root: foo_identifier,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(node_types.iter().find(|t| t.kind == "foo_identifier"), None);
        assert_eq!(
            node_types.iter().find(|t| t.kind == "identifier"),
            Some(&NodeInfoJSON {
                kind: "identifier".to_string(),
                named: true,
                root: false,
                extra: false,
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
                root: false,
                extra: false,
                subtypes: None,
                children: None,
                fields: None,
            })
        );
    }

    #[test]
    fn test_node_types_with_multiple_valued_fields() {
        let mut pool = RulePool::default();
        let a = {
            let first = {
                let blank = pool.blank();
                let rep = {
                    let f1 = {
                        let b = named(&mut pool, "b");
                        field(&mut pool, "f1", b)
                    };
                    pool.repeat(f1)
                };
                pool.choice(&[blank, rep])
            };
            let second = {
                let c = named(&mut pool, "c");
                pool.repeat(c)
            };
            pool.seq(&[first, second])
        };
        let b = string(&mut pool, "b");
        let c = string(&mut pool, "c");
        let node_types = get_node_types(InputGrammar {
            variables: vec![
                Variable {
                    name: pool.intern("a"),
                    root: a,
                },
                Variable {
                    name: pool.intern("b"),
                    root: b,
                },
                Variable {
                    name: pool.intern("c"),
                    root: c,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            node_types[0],
            NodeInfoJSON {
                kind: "a".to_string(),
                named: true,
                root: true,
                extra: false,
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
    fn test_node_types_with_fields_on_hidden_tokens() {
        let mut pool = RulePool::default();
        let script = {
            let a = {
                let pat = pattern(&mut pool, "hi");
                field(&mut pool, "a", pat)
            };
            let b = {
                let pat = pattern(&mut pool, "bye");
                field(&mut pool, "b", pat)
            };
            pool.seq(&[a, b])
        };
        let node_types = get_node_types(InputGrammar {
            variables: vec![Variable {
                name: pool.intern("script"),
                root: script,
            }],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            node_types,
            [NodeInfoJSON {
                kind: "script".to_string(),
                named: true,
                root: true,
                extra: false,
                fields: Some(BTreeMap::new()),
                children: None,
                subtypes: None
            }]
        );
    }

    #[test]
    fn test_node_types_with_multiple_rules_same_alias_name() {
        let mut pool = RulePool::default();
        let script = {
            let a = named(&mut pool, "a");
            let b = {
                let inner = named(&mut pool, "b");
                alias(&mut pool, inner, "a", true)
            };
            pool.choice(&[a, b])
        };
        let a = {
            let f1 = {
                let s = string(&mut pool, "1");
                field(&mut pool, "f1", s)
            };
            let f2 = {
                let s = string(&mut pool, "2");
                field(&mut pool, "f2", s)
            };
            pool.seq(&[f1, f2])
        };
        let b = {
            let f2a = {
                let s = string(&mut pool, "22");
                field(&mut pool, "f2", s)
            };
            let f2b = {
                let s = string(&mut pool, "222");
                field(&mut pool, "f2", s)
            };
            let f3 = {
                let s = string(&mut pool, "3");
                field(&mut pool, "f3", s)
            };
            pool.seq(&[f2a, f2b, f3])
        };
        let node_types = get_node_types(InputGrammar {
            variables: vec![
                Variable {
                    name: pool.intern("script"),
                    root: script,
                },
                Variable {
                    name: pool.intern("a"),
                    root: a,
                },
                Variable {
                    name: pool.intern("b"),
                    root: b,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            &node_types
                .iter()
                .map(|t| t.kind.as_str())
                .collect::<Vec<_>>(),
            &["a", "script", "1", "2", "22", "222", "3"]
        );

        assert_eq!(
            &node_types[0..2],
            &[
                // A combination of the types for `a` and `b`.
                NodeInfoJSON {
                    kind: "a".to_string(),
                    named: true,
                    root: false,
                    extra: false,
                    subtypes: None,
                    children: None,
                    fields: Some(
                        vec![
                            (
                                "f1".to_string(),
                                FieldInfoJSON {
                                    multiple: false,
                                    required: false,
                                    types: vec![NodeTypeJSON {
                                        kind: "1".to_string(),
                                        named: false,
                                    }]
                                }
                            ),
                            (
                                "f2".to_string(),
                                FieldInfoJSON {
                                    multiple: true,
                                    required: true,
                                    types: vec![
                                        NodeTypeJSON {
                                            kind: "2".to_string(),
                                            named: false,
                                        },
                                        NodeTypeJSON {
                                            kind: "22".to_string(),
                                            named: false,
                                        },
                                        NodeTypeJSON {
                                            kind: "222".to_string(),
                                            named: false,
                                        }
                                    ]
                                },
                            ),
                            (
                                "f3".to_string(),
                                FieldInfoJSON {
                                    multiple: false,
                                    required: false,
                                    types: vec![NodeTypeJSON {
                                        kind: "3".to_string(),
                                        named: false,
                                    }]
                                }
                            ),
                        ]
                        .into_iter()
                        .collect()
                    ),
                },
                NodeInfoJSON {
                    kind: "script".to_string(),
                    named: true,
                    root: true,
                    extra: false,
                    subtypes: None,
                    // Only one node
                    children: Some(FieldInfoJSON {
                        multiple: false,
                        required: true,
                        types: vec![NodeTypeJSON {
                            kind: "a".to_string(),
                            named: true,
                        }]
                    }),
                    fields: Some(BTreeMap::new()),
                }
            ]
        );
    }

    #[test]
    fn test_node_types_with_tokens_aliased_to_match_rules() {
        let mut pool = RulePool::default();
        let a = {
            let (b, c) = (named(&mut pool, "b"), named(&mut pool, "c"));
            pool.seq(&[b, c])
        };
        let b = {
            let (c1, mid, c2) = (
                named(&mut pool, "c"),
                string(&mut pool, "B"),
                named(&mut pool, "c"),
            );
            pool.seq(&[c1, mid, c2])
        };
        let c = {
            let cc = string(&mut pool, "C");
            let d = {
                // This token is aliased as a `b`, which will produce a `b` node
                // with no children.
                let inner = string(&mut pool, "D");
                alias(&mut pool, inner, "b", true)
            };
            pool.choice(&[cc, d])
        };

        // above Alias D
        let node_types = get_node_types(InputGrammar {
            variables: vec![
                Variable {
                    name: pool.intern("a"),
                    root: a,
                },
                // Ordinarily, `b` nodes have two named `c` children.
                Variable {
                    name: pool.intern("b"),
                    root: b,
                },
                Variable {
                    name: pool.intern("c"),
                    root: c,
                },
            ],
            pool,
            ..Default::default()
        })
        .unwrap();

        assert_eq!(
            node_types.iter().map(|n| &n.kind).collect::<Vec<_>>(),
            &["a", "b", "c", "B", "C"]
        );
        assert_eq!(
            node_types[1],
            NodeInfoJSON {
                kind: "b".to_string(),
                named: true,
                root: false,
                extra: false,
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
        let mut interner = StrPool::default();
        let field1 = interner.intern("field1");
        let field2 = interner.intern("field2");
        let lexical_grammar = build_lexical_grammar(&mut interner);
        let grammar = build_syntax_grammar(
            &mut interner,
            vec![
                // Required field `field1` has only one node type.
                (
                    "rule0",
                    VariableType::Named,
                    vec![vec![
                        step(Symbol::terminal(0), None),
                        step(Symbol::non_terminal(1), Some(field1)),
                    ]],
                ),
                // Hidden node
                (
                    "_rule1",
                    VariableType::Hidden,
                    vec![vec![step(Symbol::terminal(1), None)]],
                ),
                // Optional field `field2` can have two possible node types.
                (
                    "rule2",
                    VariableType::Named,
                    vec![
                        vec![step(Symbol::terminal(0), None)],
                        vec![
                            step(Symbol::terminal(0), None),
                            step(Symbol::terminal(2), Some(field2)),
                        ],
                        vec![
                            step(Symbol::terminal(0), None),
                            step(Symbol::terminal(3), Some(field2)),
                        ],
                    ],
                ),
            ],
            vec![],
        );
        let variable_info =
            get_variable_info(&grammar, &lexical_grammar, &AliasMap::new(), &interner).unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                field1,
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: true,
                        multiple: false
                    },
                    types: vec![ChildType::Normal(Symbol::terminal(1))]
                }
            )]
            .into_iter()
            .collect()
        );
        assert_eq!(
            variable_info[2].fields,
            vec![(
                field2,
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: false,
                        multiple: false
                    },
                    types: vec![
                        ChildType::Normal(Symbol::terminal(2)),
                        ChildType::Normal(Symbol::terminal(3))
                    ]
                }
            )]
            .into_iter()
            .collect()
        );
    }

    #[test]
    fn test_get_variable_info_with_repetitions_inside_fields() {
        let mut interner = StrPool::default();
        let field1 = interner.intern("field1");
        let lexical_grammar = build_lexical_grammar(&mut interner);
        let grammar = build_syntax_grammar(
            &mut interner,
            vec![
                // Field associated with a repetiation.
                (
                    "rule0",
                    VariableType::Named,
                    vec![vec![step(Symbol::non_terminal(1), Some(field1))], vec![]],
                ),
                (
                    "_rule0_repeat",
                    VariableType::Hidden,
                    vec![
                        vec![step(Symbol::terminal(1), None)],
                        vec![
                            step(Symbol::non_terminal(1), None),
                            step(Symbol::non_terminal(1), None),
                        ],
                    ],
                ),
            ],
            vec![],
        );
        let variable_info =
            get_variable_info(&grammar, &lexical_grammar, &AliasMap::new(), &interner).unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                field1,
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: false,
                        multiple: true
                    },
                    types: vec![ChildType::Normal(Symbol::terminal(1))],
                }
            )]
            .into_iter()
            .collect()
        );
    }

    #[test]
    fn test_get_variable_info_with_inherited_fields() {
        let mut interner = StrPool::default();
        let field1 = interner.intern("field1");
        let dot = interner.intern(".");
        let lexical_grammar = build_lexical_grammar(&mut interner);
        let grammar = build_syntax_grammar(
            &mut interner,
            vec![
                (
                    "rule0",
                    VariableType::Named,
                    vec![
                        vec![
                            step(Symbol::terminal(0), None),
                            step(Symbol::non_terminal(1), None),
                            step(Symbol::terminal(1), None),
                        ],
                        vec![step(Symbol::non_terminal(1), None)],
                    ],
                ),
                // Hidden node with fields
                (
                    "_rule1",
                    VariableType::Hidden,
                    vec![vec![
                        ProductionStep::pack(
                            Symbol::terminal(2),
                            Precedence::None,
                            None,
                            Some(Alias {
                                value: dot,
                                is_named: false,
                            }),
                            None,
                            ProductionStep::NO_RESERVED_WORDS,
                        ),
                        step(Symbol::terminal(3), Some(field1)),
                    ]],
                ),
            ],
            vec![],
        );
        let variable_info =
            get_variable_info(&grammar, &lexical_grammar, &AliasMap::new(), &interner).unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                field1,
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: true,
                        multiple: false
                    },
                    types: vec![ChildType::Normal(Symbol::terminal(3))]
                }
            )]
            .into_iter()
            .collect()
        );
        assert_eq!(
            variable_info[0].children_without_fields,
            FieldInfo {
                quantity: ChildQuantity {
                    exists: true,
                    required: false,
                    multiple: true
                },
                types: vec![
                    ChildType::Normal(Symbol::terminal(0)),
                    ChildType::Normal(Symbol::terminal(1))
                ]
            }
        );
    }

    #[test]
    fn test_get_variable_info_with_supertypes() {
        let mut interner = StrPool::default();
        let field1 = interner.intern("field1");
        let lexical_grammar = build_lexical_grammar(&mut interner);
        let grammar = build_syntax_grammar(
            &mut interner,
            vec![
                (
                    "rule0",
                    VariableType::Named,
                    vec![vec![
                        step(Symbol::terminal(0), None),
                        step(Symbol::non_terminal(1), Some(field1)),
                        step(Symbol::terminal(1), None),
                    ]],
                ),
                (
                    "_rule1",
                    VariableType::Hidden,
                    vec![
                        vec![step(Symbol::terminal(2), None)],
                        vec![step(Symbol::terminal(3), None)],
                    ],
                ),
            ],
            // _rule1 is a supertype
            vec![Symbol::non_terminal(1)],
        );
        let variable_info =
            get_variable_info(&grammar, &lexical_grammar, &AliasMap::new(), &interner).unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                field1,
                FieldInfo {
                    quantity: ChildQuantity {
                        exists: true,
                        required: true,
                        multiple: false
                    },
                    types: vec![ChildType::Normal(Symbol::non_terminal(1))]
                }
            )]
            .into_iter()
            .collect()
        );
    }

    fn get_node_types(grammar: InputGrammar) -> SuperTypeCycleResult<Vec<NodeInfoJSON>> {
        let PreparedGrammar {
            syntax_grammar,
            lexical_grammar,
            default_aliases,
            str_pool,
            ..
        } = prepare_grammar(grammar, &mut Vec::new()).unwrap();
        let variable_info = get_variable_info(
            &syntax_grammar,
            &lexical_grammar,
            &default_aliases,
            &str_pool,
        )
        .unwrap();
        generate_node_types_json(
            &syntax_grammar,
            &lexical_grammar,
            &default_aliases,
            &variable_info,
            &str_pool,
        )
    }

    fn named(p: &mut RulePool, name: &str) -> RuleId {
        let name = p.intern(name);
        p.named_symbol(name)
    }
    fn string(p: &mut RulePool, value: &str) -> RuleId {
        let value = p.intern(value);
        p.string(value)
    }
    fn pattern(p: &mut RulePool, value: &str) -> RuleId {
        let (value, flags) = (p.intern(value), p.intern(""));
        p.pattern(value, flags)
    }
    fn field(p: &mut RulePool, name: &str, content: RuleId) -> RuleId {
        let name = p.intern(name);
        p.field(name, content)
    }
    fn alias(p: &mut RulePool, content: RuleId, value: &str, is_named: bool) -> RuleId {
        let value = p.intern(value);
        p.alias(content, value, is_named)
    }
    fn external(p: &mut RulePool, index: u32) -> RuleId {
        p.push_node(Rule::Sym {
            kind: SymbolType::External,
            index,
        })
    }

    fn build_syntax_grammar(
        interner: &mut StrPool,
        variables: Vec<(&str, VariableType, Vec<Vec<ProductionStep>>)>,
        supertype_symbols: Vec<Symbol>,
    ) -> SyntaxGrammar {
        let (mut steps, mut productions, mut var_prods, mut vars) =
            (Vec::new(), Vec::new(), Vec::new(), Vec::new());
        for (name, kind, prods) in variables {
            let prod_start = productions.len() as u32;
            for prod_steps in prods {
                let steps_start = steps.len() as u32;
                steps.extend(prod_steps);
                productions.push(Production {
                    steps_start,
                    steps_len: steps.len() as u32 - steps_start,
                    dynamic_precedence: 0,
                });
            }
            var_prods.push((prod_start, productions.len() as u32));
            vars.push(SyntaxVariable {
                name: interner.intern(name),
                kind,
            });
        }
        SyntaxGrammar {
            variables: vars,
            supertype_symbols,
            steps,
            productions,
            var_prods,
            ..Default::default()
        }
    }

    fn build_lexical_grammar(interner: &mut StrPool) -> LexicalGrammar {
        let mut lexical_grammar = LexicalGrammar::default();
        for i in 0..10 {
            lexical_grammar.variables.push(LexicalVariable {
                name: interner.intern(&format!("token_{i}")),
                kind: VariableType::Named,
                implicit_precedence: 0,
                start_state: 0,
            });
        }
        lexical_grammar
    }

    fn step(symbol: Symbol, field: Option<StrId>) -> ProductionStep {
        ProductionStep::pack(
            symbol,
            Precedence::None,
            None,
            None,
            field,
            ProductionStep::NO_RESERVED_WORDS,
        )
    }
}
