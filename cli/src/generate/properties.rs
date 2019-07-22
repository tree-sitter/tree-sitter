use crate::error::{Error, Result};
use crate::generate::dedup::split_state_id_groups;
use rsass;
use rsass::sass::Value;
use rsass::selectors::SelectorPart;
use serde_derive::Serialize;
use std::cmp::Ordering;
use std::collections::hash_map::Entry;
use std::collections::{btree_map, BTreeMap, HashMap, HashSet, VecDeque};
use std::fmt::{self, Write};
use std::hash::{Hash, Hasher};
use std::mem;
use std::path::{Path, PathBuf};
use tree_sitter::{self, PropertyStateJSON, PropertyTransitionJSON};

#[derive(Clone, Debug, PartialEq, Eq, Serialize)]
#[serde(untagged)]
pub(crate) enum PropertyValue {
    Number(isize),
    Boolean(bool),
    String(String),
    Object(PropertySet),
    Array(Vec<PropertyValue>),
}

type PropertySet = BTreeMap<String, PropertyValue>;
type PropertySheetJSON = tree_sitter::PropertySheetJSON<PropertySet>;
type StateId = usize;
type PropertySetId = usize;

#[derive(Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct SelectorStep {
    kind: Option<String>,
    field: Option<String>,
    child_index: Option<usize>,
    text_pattern: Option<String>,
    is_named: Option<bool>,
    is_immediate: bool,
}

#[derive(PartialEq, Eq, PartialOrd, Ord)]
struct Selector(Vec<SelectorStep>);

#[derive(Debug, PartialEq, Eq)]
struct Rule {
    selectors: Vec<Selector>,
    properties: PropertySet,
}

#[derive(Clone, Copy, Debug)]
struct Item<'a> {
    rule_id: u32,
    selector: &'a Selector,
    step_id: u32,
}

#[derive(Clone, PartialEq, Eq)]
struct ItemSet<'a>(Vec<Item<'a>>);

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
struct SelectorMatch {
    specificity: u32,
    rule_id: u32,
}

struct Builder<'a> {
    rules: &'a Vec<Rule>,
    output: PropertySheetJSON,
    start_item_set: ItemSet<'a>,
    token_names: &'a HashSet<String>,
    ids_by_item_set: HashMap<ItemSet<'a>, StateId>,
    item_set_queue: VecDeque<(ItemSet<'a>, StateId)>,
    item_set_list: Vec<ItemSet<'a>>,
}

impl<'a> Item<'a> {
    fn next_step(&self) -> Option<&SelectorStep> {
        self.selector.0.get(self.step_id as usize)
    }

    fn is_done(&self) -> bool {
        self.step_id as usize == self.selector.0.len()
    }
}

impl<'a> Ord for Item<'a> {
    fn cmp(&self, other: &Item) -> Ordering {
        self.rule_id
            .cmp(&other.rule_id)
            .then_with(|| self.selector.0.len().cmp(&other.selector.0.len()))
            .then_with(|| {
                for (i, step) in self
                    .selector
                    .0
                    .iter()
                    .enumerate()
                    .skip(self.step_id as usize)
                {
                    let result = step.cmp(&other.selector.0[i]);
                    if result != Ordering::Equal {
                        return result;
                    }
                }
                Ordering::Equal
            })
    }
}

impl<'a> PartialOrd for Item<'a> {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl<'a> Hash for Item<'a> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_u32(self.rule_id);
        hasher.write_usize(self.selector.0.len());
        for step in &self.selector.0[self.step_id as usize..] {
            step.hash(hasher);
        }
    }
}

impl<'a> PartialEq for Item<'a> {
    fn eq(&self, other: &Self) -> bool {
        if self.rule_id != other.rule_id || self.selector.0.len() != other.selector.0.len() {
            return false;
        }

        for (i, step) in self
            .selector
            .0
            .iter()
            .enumerate()
            .skip(self.step_id as usize)
        {
            if *step != other.selector.0[i] {
                return false;
            }
        }

        true
    }
}

impl<'a> Eq for Item<'a> {}

impl<'a> Hash for ItemSet<'a> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_usize(self.0.len());
        for item in &self.0 {
            item.hash(hasher);
        }
    }
}

impl<'a> ItemSet<'a> {
    fn new() -> Self {
        ItemSet(Vec::new())
    }

    fn insert(&mut self, item: Item<'a>) {
        match self.0.binary_search(&item) {
            Err(i) => self.0.insert(i, item),
            _ => {}
        }
    }
}

impl<'a> Builder<'a> {
    fn new(rules: &'a Vec<Rule>, token_names: &'a HashSet<String>) -> Self {
        Builder {
            rules,
            start_item_set: ItemSet::new(),
            item_set_list: Vec::new(),
            output: PropertySheetJSON {
                states: Vec::new(),
                property_sets: Vec::new(),
            },
            token_names,
            ids_by_item_set: HashMap::new(),
            item_set_queue: VecDeque::new(),
        }
    }

    fn build(mut self) -> PropertySheetJSON {
        for (i, rule) in self.rules.iter().enumerate() {
            for selector in &rule.selectors {
                self.start_item_set.insert(Item {
                    rule_id: i as u32,
                    selector,
                    step_id: 0,
                });
            }
        }

        self.add_state(ItemSet::new());
        self.output.states[0].id = Some(0);
        while let Some((item_set, state_id)) = self.item_set_queue.pop_front() {
            self.populate_state(item_set, state_id);
        }

        self.remove_duplicate_states();

        for (i, state) in self.output.states.iter_mut().enumerate() {
            state.id = Some(i);
        }

        self.output
    }

    fn add_state(&mut self, item_set: ItemSet<'a>) -> StateId {
        match self.ids_by_item_set.entry(item_set) {
            Entry::Occupied(o) => *o.get(),
            Entry::Vacant(v) => {
                let state_id = self.output.states.len();
                self.output.states.push(PropertyStateJSON {
                    id: None,
                    transitions: Vec::new(),
                    property_set_id: 0,
                    default_next_state_id: 0,
                });
                self.item_set_queue.push_back((v.key().clone(), state_id));
                v.insert(state_id);
                state_id
            }
        }
    }

    fn add_property_set(&mut self, properties: PropertySet) -> PropertySetId {
        if let Some(index) = self
            .output
            .property_sets
            .iter()
            .position(|i| *i == properties)
        {
            index
        } else {
            self.output.property_sets.push(properties);
            self.output.property_sets.len() - 1
        }
    }

    fn populate_state(&mut self, item_set: ItemSet<'a>, state_id: StateId) {
        let is_start_state = state_id == 0;
        let mut transitions: HashMap<PropertyTransitionJSON, u32> = HashMap::new();
        let mut selector_matches = Vec::new();

        // First, compute all of the possible state transition conditions for
        // this state, and all of the rules that are currently matching.
        for item in item_set.0.iter().chain(self.start_item_set.0.iter()) {
            // If this item has more elements remaining in its selector, then
            // add a state transition based on the next step.
            if let Some(step) = item.next_step() {
                transitions
                    .entry(PropertyTransitionJSON {
                        kind: step.kind.clone(),
                        field: step.field.clone(),
                        named: step.is_named,
                        index: step.child_index,
                        text: step.text_pattern.clone(),
                        state_id: 0,
                    })
                    .and_modify(|rule_id| {
                        if item.rule_id > *rule_id {
                            *rule_id = item.rule_id;
                        }
                    })
                    .or_insert(item.rule_id);
            }
            // If the item has matched its entire selector, then the item's
            // properties are applicable to this state.
            else {
                selector_matches.push(SelectorMatch {
                    rule_id: item.rule_id,
                    specificity: selector_specificity(item.selector),
                });
            }
        }

        // Compute the merged properties that apply in the current state.
        // Sort the matching property sets by ascending specificity and by
        // their order in the sheet. This way, more specific selectors and later
        // rules will override less specific selectors and earlier rules.
        let mut properties = PropertySet::new();
        selector_matches.sort_unstable_by(|a, b| {
            (a.specificity.cmp(&b.specificity)).then_with(|| a.rule_id.cmp(&b.rule_id))
        });
        selector_matches.dedup();
        for selector_match in selector_matches {
            let rule = &self.rules[selector_match.rule_id as usize];
            for (property, value) in &rule.properties {
                properties.insert(property.clone(), value.clone());
            }
        }
        self.output.states[state_id].property_set_id = self.add_property_set(properties);

        // If there are multiple transitions that could *both* match (e.g. one based on a
        // a node type and one based on a field name), then create an additional transition
        // for the intersection of the two.
        let mut i = 0;
        let mut transition_list = transitions.into_iter().collect::<Vec<_>>();
        while i < transition_list.len() {
            for j in 0..i {
                if let Some(intersection) =
                    self.intersect_transitions(&transition_list[j].0, &transition_list[i].0)
                {
                    transition_list.push((
                        intersection,
                        u32::max(transition_list[i].1, transition_list[j].1),
                    ));
                }
            }
            i += 1;
        }

        // Ensure that for a given node type, more specific transitions are tried
        // first, and in the event of a tie, transitions corresponding to later rules
        // in the cascade are tried first. Also, sort the non-intersecting transitions
        // by name to guarantee a deterministic order.
        transition_list.sort_by(|a, b| {
            (transition_specificity(&b.0).cmp(&transition_specificity(&a.0)))
                .then_with(|| b.1.cmp(&a.1))
                .then_with(|| a.0.kind.cmp(&b.0.kind))
                .then_with(|| a.0.named.cmp(&b.0.named))
                .then_with(|| a.0.field.cmp(&b.0.field))
        });

        // For eacy possible state transition, compute the set of items in that transition's
        // destination state.
        i = 0;
        while i < transition_list.len() {
            let transition = &mut transition_list[i].0;
            let transition_is_leaf = transition.named == Some(false)
                || transition
                    .kind
                    .as_ref()
                    .map_or(false, |kind| self.token_names.contains(kind));

            let mut next_item_set = ItemSet::new();
            let mut transition_differs_from_start_state = false;
            for item in item_set.0.iter().chain(self.start_item_set.0.iter()) {
                if let Some(next_step) = item.next_step() {
                    // If the next step of the item's selector satisfies this transition,
                    // advance the item to the next part of its selector and add the
                    // resulting item to this transition's destination state.
                    if step_matches_transition(next_step, transition) {
                        let next_item = Item {
                            rule_id: item.rule_id,
                            selector: item.selector,
                            step_id: item.step_id + 1,
                        };
                        if !transition_is_leaf || next_item.is_done() {
                            next_item_set.insert(next_item);
                            if item.step_id > 0 {
                                transition_differs_from_start_state = true;
                            }
                        }
                    }

                    // If the next step of the item is not an immediate child, then
                    // include this item in this transition's destination state, because
                    // the next step of the item might match a descendant node.
                    if !transition_is_leaf && !next_step.is_immediate && item.step_id > 0 {
                        next_item_set.insert(*item);
                        transition_differs_from_start_state = true;
                    }
                }
            }

            if (is_start_state || transition_differs_from_start_state)
                && !next_item_set.0.is_empty()
            {
                transition.state_id = self.add_state(next_item_set);
                if is_start_state || !self.output.states[0].transitions.contains(&transition) {
                    i += 1;
                    continue;
                }
            }
            transition_list.remove(i);
        }

        self.output.states[state_id]
            .transitions
            .extend(transition_list.into_iter().map(|i| i.0));

        // Compute the default successor item set - the item set that
        // we should advance to if the next element doesn't match any
        // of the next elements in the item set's selectors.
        let mut default_next_item_set = ItemSet::new();
        for item in &item_set.0 {
            let next_step = item.selector.0.get(item.step_id as usize);
            if let Some(step) = next_step {
                if !step.is_immediate {
                    default_next_item_set.insert(*item);
                }
            }
        }
        self.output.states[state_id].default_next_state_id = self.add_state(default_next_item_set);

        self.item_set_list.push(item_set);
    }

    fn intersect_transitions(
        &self,
        left: &PropertyTransitionJSON,
        right: &PropertyTransitionJSON,
    ) -> Option<PropertyTransitionJSON> {
        let mut left_contributes = false;
        let mut right_contributes = false;
        let mut result = left.clone();

        if let Some(left_kind) = &left.kind {
            if let Some(right_kind) = &right.kind {
                if left_kind != right_kind || left.named != right.named {
                    return None;
                }
            } else {
                left_contributes = true;
            }
        } else if let Some(right_kind) = &right.kind {
            result.kind = Some(right_kind.clone());
            result.named = right.named;
            right_contributes = true;
        }

        if let Some(left_field) = &left.field {
            if let Some(right_field) = &right.field {
                if left_field != right_field {
                    return None;
                }
            } else {
                left_contributes = true;
            }
        } else if let Some(right_field) = &right.field {
            result.field = Some(right_field.clone());
            right_contributes = true;
        }

        if let Some(left_text) = &left.text {
            if let Some(right_text) = &right.text {
                if left_text != right_text {
                    return None;
                }
            } else {
                left_contributes = true;
            }
        } else if let Some(right_text) = &right.text {
            result.text = Some(right_text.clone());
            right_contributes = true;
        }

        if let Some(left_index) = &left.index {
            if let Some(right_index) = &right.index {
                if left_index != right_index {
                    return None;
                }
            } else {
                left_contributes = true;
            }
        } else if let Some(right_index) = &right.index {
            result.index = Some(right_index.clone());
            right_contributes = true;
        }

        if left_contributes && right_contributes {
            Some(result)
        } else {
            None
        }
    }

    fn remove_duplicate_states(&mut self) {
        let mut state_ids_by_properties = HashMap::new();
        for (i, state) in self.output.states.iter().enumerate() {
            state_ids_by_properties
                .entry(state.property_set_id)
                .or_insert(Vec::new())
                .push(i);
        }
        let mut state_ids_by_group_id = state_ids_by_properties
            .into_iter()
            .map(|e| e.1)
            .collect::<Vec<_>>();
        state_ids_by_group_id.sort();
        let start_group_index = state_ids_by_group_id
            .iter()
            .position(|g| g.contains(&0))
            .unwrap();
        state_ids_by_group_id.swap(start_group_index, 0);

        let mut group_ids_by_state_id = vec![0; self.output.states.len()];
        for (group_id, state_ids) in state_ids_by_group_id.iter().enumerate() {
            for state_id in state_ids {
                group_ids_by_state_id[*state_id] = group_id;
            }
        }

        while split_state_id_groups(
            &self.output.states,
            &mut state_ids_by_group_id,
            &mut group_ids_by_state_id,
            0,
            property_states_differ,
        ) {
            continue;
        }

        let mut new_states = Vec::with_capacity(state_ids_by_group_id.len());
        for state_ids in state_ids_by_group_id.iter() {
            let mut new_state = PropertyStateJSON::default();
            mem::swap(&mut new_state, &mut self.output.states[state_ids[0]]);
            for transition in new_state.transitions.iter_mut() {
                transition.state_id = group_ids_by_state_id[transition.state_id];
            }
            new_state.default_next_state_id =
                group_ids_by_state_id[new_state.default_next_state_id];
            new_states.push(new_state);
        }
        self.output.states = new_states;
    }
}

fn property_states_differ(
    left: &PropertyStateJSON,
    right: &PropertyStateJSON,
    group_ids_by_state_id: &Vec<usize>,
) -> bool {
    if group_ids_by_state_id[left.default_next_state_id]
        != group_ids_by_state_id[right.default_next_state_id]
    {
        return true;
    }

    left.transitions
        .iter()
        .zip(right.transitions.iter())
        .any(|(left, right)| {
            left.kind != right.kind
                || left.named != right.named
                || left.index != right.index
                || left.field != right.field
                || left.text != right.text
                || group_ids_by_state_id[left.state_id] != group_ids_by_state_id[right.state_id]
        })
}

fn selector_specificity(selector: &Selector) -> u32 {
    let mut result = 0;
    for step in &selector.0 {
        if step.kind.is_some() {
            result += 1;
        }
        if step.field.is_some() {
            result += 1;
        }
        if step.child_index.is_some() {
            result += 1;
        }
        if step.text_pattern.is_some() {
            result += 1;
        }
    }
    result
}

fn transition_specificity(transition: &PropertyTransitionJSON) -> u32 {
    let mut result = 0;
    if transition.kind.is_some() {
        result += 1;
    }
    if transition.field.is_some() {
        result += 1;
    }
    if transition.index.is_some() {
        result += 1;
    }
    if transition.text.is_some() {
        result += 1;
    }
    result
}

fn step_matches_transition(step: &SelectorStep, transition: &PropertyTransitionJSON) -> bool {
    step.kind
        .as_ref()
        .map_or(true, |kind| transition.kind.as_ref() == Some(kind))
        && step
            .is_named
            .map_or(true, |named| transition.named == Some(named))
        && step
            .field
            .as_ref()
            .map_or(true, |field| transition.field.as_ref() == Some(field))
        && step
            .child_index
            .map_or(true, |index| transition.index == Some(index))
        && step
            .text_pattern
            .as_ref()
            .map_or(true, |text| transition.text.as_ref() == Some(text))
}

impl fmt::Debug for SelectorStep {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        if self.is_immediate {
            write!(f, "> ")?;
        }
        write!(f, "(")?;
        if let Some(kind) = &self.kind {
            if self.is_named.unwrap() {
                write!(f, "{}", kind)?;
            } else {
                write!(f, "[token='{}']", kind)?;
            }
        }
        if let Some(field) = &self.field {
            write!(f, ".{}", field)?;
        }
        if let Some(n) = self.child_index {
            write!(f, ":nth-child({})", n)?;
        }
        if let Some(t) = &self.text_pattern {
            write!(f, "[text='{}']", t)?;
        }
        write!(f, ")")?;
        Ok(())
    }
}

impl fmt::Debug for Selector {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[")?;
        for (i, step) in self.0.iter().enumerate() {
            if step.is_immediate {
                write!(f, " > ")?;
            } else if i > 0 {
                write!(f, " ")?;
            }
            write!(f, "{:?}", step)?;
        }
        write!(f, " (specificity: {})]", selector_specificity(self))?;
        Ok(())
    }
}

pub(crate) fn generate_property_sheet(
    path: impl AsRef<Path>,
    css: &str,
    token_names: &HashSet<String>,
) -> Result<PropertySheetJSON> {
    let rules = parse_property_sheet(path.as_ref(), &css)?;
    Ok(Builder::new(&rules, token_names).build())
}

fn parse_property_sheet(path: &Path, css: &str) -> Result<Vec<Rule>> {
    let mut schema_paths = Vec::new();
    let mut items = rsass::parse_scss_data(css.as_bytes())?;
    process_at_rules(&mut items, &mut schema_paths, path)?;
    let mut result = Vec::new();
    let selector_prefixes = vec![Vec::new()];
    parse_sass_items(items, &selector_prefixes, &mut result)?;
    Ok(result)
}

fn parse_sass_items(
    items: Vec<rsass::Item>,
    selector_prefixes: &Vec<Vec<SelectorStep>>,
    result: &mut Vec<Rule>,
) -> Result<()> {
    let mut properties = PropertySet::new();
    for item in items {
        match item {
            rsass::Item::None | rsass::Item::Comment(_) => {}
            rsass::Item::Property(name, value) => {
                let value = parse_sass_value(&value)?;
                match properties.entry(name.to_string()) {
                    btree_map::Entry::Vacant(v) => {
                        v.insert(value);
                    }
                    btree_map::Entry::Occupied(mut o) => {
                        let existing_value = o.get_mut();
                        if let PropertyValue::Array(items) = existing_value {
                            items.push(value);
                            continue;
                        } else {
                            let v = existing_value.clone();
                            *existing_value = PropertyValue::Array(vec![v, value]);
                        }
                    }
                }
            }
            rsass::Item::Rule(selectors, items) => {
                let mut full_selectors = Vec::new();
                for prefix in selector_prefixes {
                    for selector in &selectors.s {
                        let mut prefix = prefix.clone();
                        let mut operator_was_immediate: Option<bool> = Some(false);
                        for part in &selector.0 {
                            match part {
                                SelectorPart::BackRef => {
                                    operator_was_immediate = None;
                                }
                                SelectorPart::Simple(value) => {
                                    if let Some(value) = value.single_raw() {
                                        for (i, value) in value.split('.').enumerate() {
                                            if value.is_empty() {
                                                continue;
                                            }
                                            let value = value.to_string();
                                            check_node_kind(&value)?;
                                            if i > 0 {
                                                if let Some(immediate) = operator_was_immediate {
                                                    prefix.push(SelectorStep {
                                                        kind: None,
                                                        field: Some(value),
                                                        is_named: None,
                                                        child_index: None,
                                                        text_pattern: None,
                                                        is_immediate: immediate,
                                                    })
                                                } else {
                                                    prefix.last_mut().unwrap().field = Some(value);
                                                }
                                            } else {
                                                if let Some(immediate) = operator_was_immediate {
                                                    prefix.push(SelectorStep {
                                                        kind: Some(value.to_string()),
                                                        field: None,
                                                        child_index: None,
                                                        text_pattern: None,
                                                        is_named: Some(true),
                                                        is_immediate: immediate,
                                                    });
                                                } else {
                                                    return Error::err(format!("Node type {} must be separated by whitespace or the `>` operator", value));
                                                }
                                            }
                                            operator_was_immediate = None;
                                        }
                                    } else {
                                        return Err(interpolation_error());
                                    }
                                    operator_was_immediate = None;
                                }
                                SelectorPart::Attribute { name, val, .. } => {
                                    match name.single_raw() {
                                        None => return Err(interpolation_error()),
                                        Some("text") => {
                                            if operator_was_immediate.is_some() {
                                                return Error::err("The `text` attribute must be used in combination with a node type or field".to_string());
                                            }
                                            if let Some(last_step) = prefix.last_mut() {
                                                last_step.text_pattern =
                                                    Some(get_string_value(val.to_string())?)
                                            }
                                        }
                                        Some("token") => {
                                            if let Some(immediate) = operator_was_immediate {
                                                prefix.push(SelectorStep {
                                                    kind: Some(get_string_value(val.to_string())?),
                                                    field: None,
                                                    is_named: Some(false),
                                                    child_index: None,
                                                    text_pattern: None,
                                                    is_immediate: immediate,
                                                });
                                                operator_was_immediate = None;
                                            } else {
                                                return Error::err("The `token` attribute canot be used in combination with a node type".to_string());
                                            }
                                        }
                                        _ => {
                                            return Error::err(format!(
                                                "Unsupported attribute {}",
                                                part
                                            ));
                                        }
                                    }
                                }
                                SelectorPart::PseudoElement { .. } => {
                                    return Error::err(
                                        "Pseudo elements are not supported".to_string(),
                                    );
                                }
                                SelectorPart::Pseudo { name, arg } => match name.single_raw() {
                                    None => return Err(interpolation_error()),
                                    Some("nth-child") => {
                                        if let Some(arg) = arg {
                                            let mut arg_str = String::new();
                                            write!(&mut arg_str, "{}", arg).unwrap();
                                            if let Some(last_step) = prefix.last_mut() {
                                                if let Ok(i) = usize::from_str_radix(&arg_str, 10) {
                                                    last_step.child_index = Some(i);
                                                } else {
                                                    return Error::err(format!(
                                                        "Invalid child index {}",
                                                        arg
                                                    ));
                                                }
                                            }
                                        }
                                    }
                                    _ => {
                                        return Error::err(format!(
                                            "Unsupported pseudo-class {}",
                                            part
                                        ));
                                    }
                                },
                                SelectorPart::Descendant => {
                                    operator_was_immediate = Some(false);
                                }
                                SelectorPart::RelOp(operator) => {
                                    let operator = *operator as char;
                                    if operator == '>' {
                                        operator_was_immediate = Some(true);
                                    } else {
                                        return Error::err(format!(
                                            "Unsupported operator {}",
                                            operator
                                        ));
                                    }
                                }
                            }
                        }
                        full_selectors.push(prefix);
                    }
                }
                parse_sass_items(items, &full_selectors, result)?;
            }
            _ => return Error::err(format!("Unsupported syntax type {:?}", item)),
        }
    }

    if !properties.is_empty() {
        result.push(Rule {
            selectors: selector_prefixes.iter().cloned().map(Selector).collect(),
            properties,
        });
    }

    Ok(())
}

fn process_at_rules(
    items: &mut Vec<rsass::Item>,
    schema_paths: &mut Vec<PathBuf>,
    path: &Path,
) -> Result<()> {
    let mut i = 0;
    while i < items.len() {
        match &items[i] {
            rsass::Item::Import(arg) => {
                if let Some(s) = get_sass_string(arg) {
                    let import_path = resolve_path(path, s)?;
                    let mut imported_items = rsass::parse_scss_file(&import_path)?;
                    process_at_rules(&mut imported_items, schema_paths, &import_path)?;
                    items.splice(i..(i + 1), imported_items);
                    continue;
                } else {
                    return Err(Error::new("@import arguments must be strings".to_string()));
                }
            }
            rsass::Item::AtRule { name, args, .. } => match name.as_str() {
                "schema" => {
                    if let Some(s) = get_sass_string(args) {
                        let schema_path = resolve_path(path, s)?;
                        schema_paths.push(schema_path);
                        items.remove(i);
                        continue;
                    } else {
                        return Error::err("@schema arguments must be strings".to_string());
                    }
                }
                _ => return Error::err(format!("Unsupported at-rule '{}'", name)),
            },
            _ => {}
        }
        i += 1;
    }
    Ok(())
}

fn parse_sass_value(value: &Value) -> Result<PropertyValue> {
    match value {
        Value::Literal(s) => {
            if let Some(s) = s.single_raw() {
                Ok(PropertyValue::String(s.to_string()))
            } else {
                Err(interpolation_error())
            }
        }
        Value::Call(name, raw_args) => {
            if let Some(name) = name.single_raw() {
                let mut args = Vec::new();
                for (_, arg) in raw_args.iter() {
                    args.push(parse_sass_value(arg)?);
                }
                let mut result = PropertySet::new();
                result.insert("name".to_string(), PropertyValue::String(name.to_string()));
                result.insert("args".to_string(), PropertyValue::Array(args));
                Ok(PropertyValue::Object(result))
            } else {
                Err(Error::new(
                    "String interpolation is not supported".to_string(),
                ))
            }
        }
        Value::List(elements, ..) => {
            let mut result = Vec::new();
            for element in elements {
                result.push(parse_sass_value(element)?);
            }
            Ok(PropertyValue::Array(result))
        }
        Value::Color(_, Some(name)) => Ok(PropertyValue::String(name.clone())),
        Value::Numeric(n, _) => Ok(PropertyValue::Number(n.to_integer())),
        Value::True => Ok(PropertyValue::Boolean(true)),
        Value::False => Ok(PropertyValue::Boolean(false)),
        _ => Err(Error::new(format!(
            "Property values must be strings or function calls. Got {:?}",
            value
        ))),
    }
}

fn get_sass_string(value: &Value) -> Option<&str> {
    if let Value::Literal(s) = value {
        s.single_raw()
    } else {
        None
    }
}

fn resolve_path(base: &Path, p: &str) -> Result<PathBuf> {
    let path = Path::new(p);
    let mut base = base.to_owned();
    base.pop();
    if path.starts_with(".") {
        base.push(path);
        if base.exists() {
            return Ok(base);
        }
    } else {
        loop {
            let mut result = base.clone();
            result.push("node_modules");
            result.push(path);
            if result.exists() {
                return Ok(result);
            }
            if !base.pop() {
                break;
            }
        }
    }
    Err(Error::new(format!("Could not resolve import path `{}`", p)))
}

fn check_node_kind(name: &String) -> Result<()> {
    for c in name.chars() {
        if !c.is_alphanumeric() && c != '_' {
            return Err(Error::new(format!("Invalid identifier '{}'", name)));
        }
    }
    Ok(())
}

fn get_string_value(mut s: String) -> Result<String> {
    if s.starts_with("'") && s.ends_with("'") || s.starts_with('"') && s.ends_with('"') {
        s.pop();
        s.remove(0);
        Ok(s)
    } else {
        Err(Error::new(format!("Unsupported string literal {}", s)))
    }
}

fn interpolation_error() -> Error {
    Error::new("String interpolation is not supported".to_string())
}

#[cfg(test)]
mod tests {
    use super::*;
    use regex::Regex;
    use std::fs;
    use tempfile::TempDir;

    #[test]
    fn test_property_sheet_with_immediate_child_and_descendant_selectors() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                f1 {
                  color: red;

                  & > f2 {
                    color: green;
                  }

                  & f3 {
                    color: blue;
                  }
                }

                f2 {
                  color: indigo;
                  height: 2;
                }

                f3 {
                  color: violet;
                  height: 3;
                }
            ",
            &HashSet::new(),
        )
        .unwrap();

        // f1 single-element selector
        assert_eq!(
            *query_simple(&sheet, vec!["f1"]),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f2", "f1"]),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f2", "f3", "f1"]),
            props(&[("color", string("red"))])
        );

        // f2 single-element selector
        assert_eq!(
            *query_simple(&sheet, vec!["f2"]),
            props(&[("color", string("indigo")), ("height", num(2))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f2", "f2"]),
            props(&[("color", string("indigo")), ("height", num(2))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f1", "f3", "f2"]),
            props(&[("color", string("indigo")), ("height", num(2))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f1", "f6", "f2"]),
            props(&[("color", string("indigo")), ("height", num(2))])
        );

        // f3 single-element selector
        assert_eq!(
            *query_simple(&sheet, vec!["f3"]),
            props(&[("color", string("violet")), ("height", num(3))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f2", "f3"]),
            props(&[("color", string("violet")), ("height", num(3))])
        );

        // f2 child selector
        assert_eq!(
            *query_simple(&sheet, vec!["f1", "f2"]),
            props(&[("color", string("green")), ("height", num(2))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f2", "f1", "f2"]),
            props(&[("color", string("green")), ("height", num(2))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f3", "f1", "f2"]),
            props(&[("color", string("green")), ("height", num(2))])
        );

        // f3 descendant selector
        assert_eq!(
            *query_simple(&sheet, vec!["f1", "f3"]),
            props(&[("color", string("blue")), ("height", num(3))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f1", "f2", "f3"]),
            props(&[("color", string("blue")), ("height", num(3))])
        );
        assert_eq!(
            *query_simple(&sheet, vec!["f1", "f6", "f7", "f8", "f3"]),
            props(&[("color", string("blue")), ("height", num(3))])
        );

        // no match
        assert_eq!(*query_simple(&sheet, vec!["f1", "f3", "f4"]), props(&[]));
        assert_eq!(*query_simple(&sheet, vec!["f1", "f2", "f5"]), props(&[]));
    }

    #[test]
    fn test_property_sheet_with_text_attribute() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                f1 {
                  color: red;

                  &[text='^[A-Z]'] {
                    color: green;
                  }

                  &[text='^[A-Z_]+$'] {
                    color: blue;
                  }
                }

                f2[text='^[A-Z_]+$'] {
                  color: purple;
                }
            ",
            &HashSet::new(),
        )
        .unwrap();

        assert_eq!(
            *query(&sheet, vec![("f1", None, true, 0)], "abc"),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", None, true, 0)], "Abc"),
            props(&[("color", string("green"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", None, true, 0)], "AB_CD"),
            props(&[("color", string("blue"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f2", None, true, 0)], "Abc"),
            props(&[])
        );
        assert_eq!(
            *query(&sheet, vec![("f2", None, true, 0)], "ABC"),
            props(&[("color", string("purple"))])
        );
    }

    #[test]
    fn test_property_sheet_with_fields() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                a {
                    color: red;
                    &.x {
                        color: green;
                        b {
                            color: blue;
                            &.y { color: yellow; }
                        }
                    }
                    b { color: orange; }
                    b.y { color: indigo; }
                }
                .x { color: violet; }
            ",
            &HashSet::new(),
        )
        .unwrap();

        assert_eq!(
            *query(&sheet, vec![("a", None, true, 0)], ""),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query(&sheet, vec![("a", Some("x"), true, 0)], ""),
            props(&[("color", string("green"))])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("a", Some("x"), true, 0), ("b", None, true, 0)],
                ""
            ),
            props(&[("color", string("blue"))])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("a", Some("x"), true, 0), ("b", Some("y"), true, 0)],
                ""
            ),
            props(&[("color", string("yellow"))])
        );
        assert_eq!(
            *query(&sheet, vec![("b", Some("x"), true, 0)], ""),
            props(&[("color", string("violet"))])
        );
        assert_eq!(
            *query(&sheet, vec![("a", None, true, 0), ("b", None, true, 0)], ""),
            props(&[("color", string("orange"))])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("a", None, true, 0), ("b", Some("y"), true, 0)],
                ""
            ),
            props(&[("color", string("indigo"))])
        );
    }

    #[test]
    fn test_property_sheet_with_cascade_ordering_as_tie_breaker() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                f1 f2:nth-child(1) { color: red; }
                f1:nth-child(1) f2 { color: green; }
                f1 f2[text='a'] { color: blue; }
                f1 f2[text='b'] { color: violet; }
            ",
            &HashSet::new(),
        )
        .unwrap();

        assert_eq!(
            *query(
                &sheet,
                vec![("f1", None, true, 0), ("f2", None, true, 0)],
                "x"
            ),
            props(&[])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("f1", None, true, 0), ("f2", None, true, 1)],
                "x"
            ),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("f1", None, true, 1), ("f2", None, true, 1)],
                "x"
            ),
            props(&[("color", string("green"))])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("f1", None, true, 1), ("f2", None, true, 1)],
                "a"
            ),
            props(&[("color", string("blue"))])
        );
        assert_eq!(
            *query(
                &sheet,
                vec![("f1", None, true, 1), ("f2", None, true, 1)],
                "ab"
            ),
            props(&[("color", string("violet"))])
        );
    }

    #[test]
    fn test_property_sheet_with_css_function_calls() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                a {
                  b: f();
                  c: f(g(h), i, \"j\", 10);
                }
            ",
            &HashSet::new(),
        )
        .unwrap();

        let p = query_simple(&sheet, vec!["a"]);

        assert_eq!(
            p["b"],
            object(&[("name", string("f")), ("args", array(vec![])),])
        );

        assert_eq!(
            p["c"],
            object(&[
                ("name", string("f")),
                (
                    "args",
                    array(vec![
                        object(&[("name", string("g")), ("args", array(vec![string("h"),]))]),
                        string("i"),
                        string("j"),
                        num(10),
                    ])
                ),
            ])
        );

        // Handle differently-formatted calls
        let sheet2 = generate_property_sheet(
            "foo.css",
            "
                a {
                  b: f();
                  c: f(
                      g(h),
                      i,
                      \"j\",
                      10
                  );
                }
            ",
            &HashSet::new(),
        )
        .unwrap();

        assert_eq!(
            query_simple(&sheet2, vec!["a"])["c"],
            query_simple(&sheet, vec!["a"])["c"]
        );
    }

    #[test]
    fn test_property_sheet_with_array_by_declaring_property_multiple_times() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                a {
                  b: 'foo';
                  b: 'bar';
                  b: 'baz';
                  c: f(g());
                  c: h();
                }
            ",
            &HashSet::new(),
        )
        .unwrap();

        let p = query_simple(&sheet, vec!["a"]);

        assert_eq!(
            p["b"],
            array(vec![string("foo"), string("bar"), string("baz"),])
        );

        assert_eq!(
            p["c"],
            array(vec![
                object(&[
                    ("name", string("f")),
                    (
                        "args",
                        array(vec![object(&[
                            ("name", string("g")),
                            ("args", array(vec![])),
                        ])])
                    )
                ]),
                object(&[("name", string("h")), ("args", array(vec![])),]),
            ]),
        );
    }

    #[test]
    fn test_property_sheet_with_imports() {
        let repo_dir = TempDir::new().unwrap();
        let properties_dir = repo_dir.path().join("properties");
        let dependency_properties_dir = repo_dir
            .path()
            .join("node_modules")
            .join("the-dependency")
            .join("properties");
        fs::create_dir_all(&properties_dir).unwrap();
        fs::create_dir_all(&dependency_properties_dir).unwrap();
        let sheet_path1 = properties_dir.join("sheet1.css");
        let sheet_path2 = properties_dir.join("sheet2.css");
        let dependency_sheet_path1 = dependency_properties_dir.join("dependency-sheet1.css");
        let dependency_sheet_path2 = dependency_properties_dir.join("dependency-sheet2.css");

        fs::write(
            sheet_path2,
            r#"
            a { x: '1'; }
            "#,
        )
        .unwrap();
        fs::write(
            dependency_sheet_path1,
            r#"
            @import "./dependency-sheet2.css";
            a { y: '2'; }
            "#,
        )
        .unwrap();
        fs::write(
            dependency_sheet_path2,
            r#"
            b { x: '3'; }
            "#,
        )
        .unwrap();
        let sheet = generate_property_sheet(
            sheet_path1,
            r#"
            @import "./sheet2.css";
            @import "the-dependency/properties/dependency-sheet1.css";
            b { y: '4'; }
            "#,
            &HashSet::new(),
        )
        .unwrap();

        let a = query_simple(&sheet, vec!["a"]);
        assert_eq!(a["x"], string("1"),);
        assert_eq!(a["y"], string("2"),);
        let b = query_simple(&sheet, vec!["b"]);
        assert_eq!(b["x"], string("3"),);
        assert_eq!(b["y"], string("4"),);
    }

    fn query_simple<'a>(
        sheet: &'a PropertySheetJSON,
        node_stack: Vec<&'static str>,
    ) -> &'a PropertySet {
        query(
            sheet,
            node_stack.into_iter().map(|s| (s, None, true, 0)).collect(),
            "",
        )
    }

    fn query<'a>(
        sheet: &'a PropertySheetJSON,
        node_stack: Vec<(&'static str, Option<&'static str>, bool, usize)>,
        leaf_text: &str,
    ) -> &'a PropertySet {
        let mut state_id = 0;
        for (kind, field, is_named, child_index) in node_stack {
            let state = &sheet.states[state_id];
            state_id = state
                .transitions
                .iter()
                .chain(sheet.states[0].transitions.iter())
                .find(|transition| {
                    transition.kind.as_ref().map_or(true, |k| k == kind)
                        && transition.named.map_or(true, |n| n == is_named)
                        && transition.field.as_ref().map_or(true, |f| field == Some(f))
                        && transition.index.map_or(true, |index| index == child_index)
                        && (transition
                            .text
                            .as_ref()
                            .map_or(true, |text| Regex::new(text).unwrap().is_match(leaf_text)))
                })
                .map_or(state.default_next_state_id, |t| t.state_id);
        }
        &sheet.property_sets[sheet.states[state_id].property_set_id]
    }

    fn array(s: Vec<PropertyValue>) -> PropertyValue {
        PropertyValue::Array(s)
    }

    fn object<'a>(s: &'a [(&'a str, PropertyValue)]) -> PropertyValue {
        PropertyValue::Object(
            s.into_iter()
                .map(|(a, b)| (a.to_string(), b.clone()))
                .collect(),
        )
    }

    fn string(s: &str) -> PropertyValue {
        PropertyValue::String(s.to_string())
    }

    fn num(n: isize) -> PropertyValue {
        PropertyValue::Number(n)
    }

    fn props<'a>(s: &'a [(&'a str, PropertyValue)]) -> PropertySet {
        s.into_iter()
            .map(|(a, b)| (a.to_string(), b.clone()))
            .collect()
    }
}
