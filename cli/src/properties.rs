use crate::error::{Error, Result};
use log::info;
use rsass;
use rsass::sass::Value;
use serde_derive::Serialize;
use std::collections::hash_map::Entry;
use std::collections::{btree_map, BTreeMap, HashMap, VecDeque};
use std::fmt::{self, Write};
use std::fs::{self, File};
use std::io::BufWriter;
use std::path::{Path, PathBuf};
use tree_sitter::{self, PropertyStateJSON, PropertyTransitionJSON};

#[derive(Clone, Debug, PartialEq, Eq, Serialize)]
#[serde(untagged)]
enum PropertyValue {
    Number(isize),
    String(String),
    Object(PropertySet),
    Array(Vec<PropertyValue>),
}

type PropertySet = BTreeMap<String, PropertyValue>;
type PropertySheetJSON = tree_sitter::PropertySheetJSON<PropertySet>;
type StateId = usize;
type PropertySetId = usize;

#[derive(Clone, PartialEq, Eq)]
struct SelectorStep {
    kind: String,
    is_named: bool,
    is_immediate: bool,
    child_index: Option<usize>,
    text_pattern: Option<String>,
}

#[derive(PartialEq, Eq)]
struct Selector(Vec<SelectorStep>);

#[derive(Debug, PartialEq, Eq)]
struct Rule {
    selectors: Vec<Selector>,
    properties: PropertySet,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct Item {
    rule_id: u32,
    selector_id: u32,
    step_id: u32,
}

#[derive(Clone, PartialEq, Eq, Hash)]
struct ItemSet(Vec<Item>);

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
struct SelectorMatch {
    specificity: u32,
    rule_id: u32,
}

struct Builder {
    rules: Vec<Rule>,
    output: PropertySheetJSON,
    ids_by_item_set: HashMap<ItemSet, StateId>,
    item_set_queue: VecDeque<(ItemSet, StateId)>,
}

impl ItemSet {
    fn new() -> Self {
        ItemSet(Vec::new())
    }

    fn insert(&mut self, item: Item) {
        match self.0.binary_search(&item) {
            Err(i) => self.0.insert(i, item),
            _ => {}
        }
    }
}

impl<'a> IntoIterator for &'a ItemSet {
    type Item = &'a Item;
    type IntoIter = std::slice::Iter<'a, Item>;
    fn into_iter(self) -> Self::IntoIter {
        self.0.iter()
    }
}

impl Builder {
    fn new(rules: Vec<Rule>) -> Self {
        Builder {
            rules,
            output: PropertySheetJSON {
                states: Vec::new(),
                property_sets: Vec::new(),
            },
            ids_by_item_set: HashMap::new(),
            item_set_queue: VecDeque::new(),
        }
    }

    fn build(mut self) -> PropertySheetJSON {
        let mut start_item_set = ItemSet::new();
        for (i, rule) in self.rules.iter().enumerate() {
            for j in 0..rule.selectors.len() {
                start_item_set.insert(Item {
                    rule_id: i as u32,
                    selector_id: j as u32,
                    step_id: 0,
                });
            }
        }

        self.add_state(start_item_set);
        while let Some((item_set, state_id)) = self.item_set_queue.pop_front() {
            self.populate_state(item_set, state_id);
        }

        self.remove_duplicate_states();

        for (i, state) in self.output.states.iter_mut().enumerate() {
            state.id = Some(i);
        }

        self.output
    }

    fn add_state(&mut self, item_set: ItemSet) -> StateId {
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

    fn populate_state(&mut self, item_set: ItemSet, state_id: StateId) {
        let mut transitions: HashMap<PropertyTransitionJSON, u32> = HashMap::new();
        let mut selector_matches = Vec::new();

        // First, compute all of the possible state transition predicates for
        // this state, and all of the rules that are currently matching.
        for item in &item_set {
            let rule = &self.rules[item.rule_id as usize];
            let selector = &rule.selectors[item.selector_id as usize];
            let next_step = selector.0.get(item.step_id as usize);

            // If this item has more elements remaining in its selector, then
            // add a state transition based on the next step.
            if let Some(step) = next_step {
                transitions
                    .entry(PropertyTransitionJSON {
                        kind: step.kind.clone(),
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
                    specificity: selector_specificity(selector),
                });
            }
        }

        // Ensure that for a given node type, more specific transitions are tried
        // first, and in the event of a tie, transitions corresponding to later rules
        // in the cascade are tried first.
        let mut transition_list: Vec<(PropertyTransitionJSON, u32)> =
            transitions.into_iter().collect();
        transition_list.sort_by(|a, b| {
            a.0.kind
                .cmp(&b.0.kind)
                .then_with(|| a.0.named.cmp(&b.0.named))
                .then_with(|| transition_specificity(&b.0).cmp(&transition_specificity(&a.0)))
                .then_with(|| b.1.cmp(&a.1))
        });

        // For eacy possible state transition, compute the set of items in that transition's
        // destination state.
        for (transition, _) in transition_list.iter_mut() {
            let mut next_item_set = ItemSet::new();
            for item in &item_set {
                let rule = &self.rules[item.rule_id as usize];
                let selector = &rule.selectors[item.selector_id as usize];
                let next_step = selector.0.get(item.step_id as usize);

                if let Some(step) = next_step {
                    // If the next step of the item's selector satisfies this transition,
                    // advance the item to the next part of its selector and add the
                    // resulting item to this transition's destination state.
                    if step_matches_transition(step, &transition) {
                        next_item_set.insert(Item {
                            rule_id: item.rule_id,
                            selector_id: item.selector_id,
                            step_id: item.step_id + 1,
                        });
                    }

                    // If the next step of the item is not an immediate child, then
                    // include this item in this transition's destination state, because
                    // the next step of the item might match a descendant node.
                    if !step.is_immediate {
                        next_item_set.insert(*item);
                    }
                }
            }

            transition.state_id = self.add_state(next_item_set);
        }

        // Compute the merged properties that apply in the current state.
        // Sort the matching property sets by ascending specificity and by
        // their order in the sheet. This way, more specific selectors and later
        // rules will override less specific selectors and earlier rules.
        let mut properties = PropertySet::new();
        selector_matches.sort_unstable_by(|a, b| {
            a.specificity
                .cmp(&b.specificity)
                .then_with(|| a.rule_id.cmp(&b.rule_id))
        });
        selector_matches.dedup();
        for selector_match in selector_matches {
            let rule = &self.rules[selector_match.rule_id as usize];
            for (property, value) in &rule.properties {
                properties.insert(property.clone(), value.clone());
            }
        }

        // Compute the default successor item set - the item set that
        // we should advance to if the next element doesn't match any
        // of the next elements in the item set's selectors.
        let mut default_next_item_set = ItemSet::new();
        for item in &item_set {
            let rule = &self.rules[item.rule_id as usize];
            let selector = &rule.selectors[item.selector_id as usize];
            let next_step = selector.0.get(item.step_id as usize);
            if let Some(step) = next_step {
                if !step.is_immediate {
                    default_next_item_set.insert(*item);
                }
            }
        }

        self.output.states[state_id].default_next_state_id = self.add_state(default_next_item_set);
        self.output.states[state_id].property_set_id = self.add_property_set(properties);
        self.output.states[state_id]
            .transitions
            .extend(transition_list.into_iter().map(|i| i.0));
    }

    fn remove_duplicate_states(&mut self) {
        let mut state_replacements = BTreeMap::new();
        let mut done = false;
        while !done {
            done = true;
            for (i, state_i) in self.output.states.iter().enumerate() {
                if state_replacements.contains_key(&i) {
                    continue;
                }
                for (j, state_j) in self.output.states.iter().enumerate() {
                    if j == i {
                        break;
                    }
                    if state_replacements.contains_key(&j) {
                        continue;
                    }
                    if state_i == state_j {
                        info!("replace state {} with state {}", i, j);
                        state_replacements.insert(i, j);
                        done = false;
                        break;
                    }
                }
            }
            for state in self.output.states.iter_mut() {
                for transition in state.transitions.iter_mut() {
                    if let Some(replacement) = state_replacements.get(&transition.state_id) {
                        transition.state_id = *replacement;
                    }
                }
            }
        }

        let final_state_replacements = (0..self.output.states.len())
            .into_iter()
            .map(|state_id| {
                let replacement = state_replacements
                    .get(&state_id)
                    .cloned()
                    .unwrap_or(state_id);
                let prior_removed = state_replacements
                    .iter()
                    .take_while(|i| *i.0 < replacement)
                    .count();
                replacement - prior_removed
            })
            .collect::<Vec<_>>();

        for state in self.output.states.iter_mut() {
            for transition in state.transitions.iter_mut() {
                transition.state_id = final_state_replacements[transition.state_id];
            }
        }

        let mut i = 0;
        self.output.states.retain(|_| {
            let result = !state_replacements.contains_key(&i);
            i += 1;
            result
        });
    }
}

fn selector_specificity(selector: &Selector) -> u32 {
    let mut result = selector.0.len() as u32;
    for step in &selector.0 {
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
    if transition.index.is_some() {
        result += 1;
    }
    if transition.text.is_some() {
        result += 1;
    }
    result
}

fn step_matches_transition(step: &SelectorStep, transition: &PropertyTransitionJSON) -> bool {
    step.kind == transition.kind
        && step.is_named == transition.named
        && (step.child_index == transition.index || step.child_index.is_none())
        && (step.text_pattern == transition.text || step.text_pattern.is_none())
}

impl fmt::Debug for SelectorStep {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "(")?;
        if self.is_named {
            write!(f, "{}", self.kind)?;
        } else {
            write!(f, "\"{}\"", self.kind)?;
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
        write!(f, "]")?;
        Ok(())
    }
}

pub fn generate_property_sheets_in_directory(repo_path: &Path) -> Result<()> {
    let src_dir_path = repo_path.join("src");
    let properties_dir_path = repo_path.join("properties");

    if let Ok(entries) = fs::read_dir(properties_dir_path) {
        for entry in entries {
            let css_path = entry?.path();
            let css = fs::read_to_string(&css_path)?;
            let sheet = generate_property_sheet(&css_path, &css)?;
            let property_sheet_json_path = src_dir_path
                .join(css_path.file_name().unwrap())
                .with_extension("json");
            let property_sheet_json_file = File::create(&property_sheet_json_path)
                .map_err(|e| format!("Failed to create {:?}: {}", property_sheet_json_path, e))?;
            let mut writer = BufWriter::new(property_sheet_json_file);
            serde_json::to_writer_pretty(&mut writer, &sheet)?;
        }
    }

    Ok(())
}

pub fn generate_property_sheet_string(path: impl AsRef<Path>, css: &str) -> Result<String> {
    let sheet = generate_property_sheet(path, css)?;
    Ok(serde_json::to_string(&sheet)?)
}

fn generate_property_sheet(path: impl AsRef<Path>, css: &str) -> Result<PropertySheetJSON> {
    let rules = parse_property_sheet(path.as_ref(), &css)?;
    Ok(Builder::new(rules).build())
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
                    let mut part_string = String::new();
                    let mut next_step_is_immediate = false;
                    for selector in &selectors.s {
                        let mut prefix = prefix.clone();
                        for part in &selector.0 {
                            part_string.clear();
                            write!(&mut part_string, "{}", part).unwrap();
                            let part_string = part_string.trim();
                            if !part_string.is_empty() {
                                if part_string == "&" {
                                    continue;
                                } else if part_string.starts_with(":nth-child(") {
                                    if let Some(last_step) = prefix.last_mut() {
                                        if let Ok(index) = usize::from_str_radix(
                                            &part_string[11..(part_string.len() - 1)],
                                            10,
                                        ) {
                                            last_step.child_index = Some(index);
                                        }
                                    }
                                } else if part_string.starts_with("[text=") {
                                    if let Some(last_step) = prefix.last_mut() {
                                        last_step.text_pattern = Some(
                                            part_string[7..(part_string.len() - 2)].to_string(),
                                        )
                                    }
                                } else if part_string == ">" {
                                    next_step_is_immediate = true;
                                } else if part_string.starts_with("[token=") {
                                    prefix.push(SelectorStep {
                                        kind: part_string[8..(part_string.len() - 2)].to_string(),
                                        is_named: false,
                                        child_index: None,
                                        text_pattern: None,
                                        is_immediate: next_step_is_immediate,
                                    });
                                    next_step_is_immediate = false;
                                } else {
                                    prefix.push(SelectorStep {
                                        kind: part_string.to_string(),
                                        is_named: true,
                                        child_index: None,
                                        text_pattern: None,
                                        is_immediate: next_step_is_immediate,
                                    });
                                    next_step_is_immediate = false;
                                }
                            }
                        }
                        full_selectors.push(prefix);
                    }
                }
                parse_sass_items(items, &full_selectors, result)?;
            }
            _ => return Err(Error(format!("Unsupported syntax type {:?}", item))),
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
                    return Err(Error("@import arguments must be strings".to_string()));
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
                        return Err(Error("@schema arguments must be strings".to_string()));
                    }
                }
                _ => return Err(Error(format!("Unsupported at-rule '{}'", name))),
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
                Err(Error("String interpolation is not supported".to_string()))
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
                Err(Error("String interpolation is not supported".to_string()))
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
        Value::True => Ok(PropertyValue::String("true".to_string())),
        Value::False => Ok(PropertyValue::String("false".to_string())),
        _ => Err(Error(format!(
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
    Err(Error(format!("Could not resolve import path `{}`", p)))
}

#[cfg(test)]
mod tests {
    use super::*;
    use regex::Regex;
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
        )
        .unwrap();

        assert_eq!(
            *query(&sheet, vec![("f1", true, 0)], "abc"),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", true, 0)], "Abc"),
            props(&[("color", string("green"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", true, 0)], "AB_CD"),
            props(&[("color", string("blue"))])
        );
        assert_eq!(*query(&sheet, vec![("f2", true, 0)], "Abc"), props(&[]));
        assert_eq!(
            *query(&sheet, vec![("f2", true, 0)], "ABC"),
            props(&[("color", string("purple"))])
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
        )
        .unwrap();

        assert_eq!(
            *query(&sheet, vec![("f1", true, 0), ("f2", true, 0)], "x"),
            props(&[])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", true, 0), ("f2", true, 1)], "x"),
            props(&[("color", string("red"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", true, 1), ("f2", true, 1)], "x"),
            props(&[("color", string("green"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", true, 1), ("f2", true, 1)], "a"),
            props(&[("color", string("blue"))])
        );
        assert_eq!(
            *query(&sheet, vec![("f1", true, 1), ("f2", true, 1)], "ab"),
            props(&[("color", string("violet"))])
        );
    }

    #[test]
    fn test_property_sheet_with_function_calls() {
        let sheet = generate_property_sheet(
            "foo.css",
            "
                a {
                  b: f();
                  c: f(g(h), i, \"j\", 10);
                }
            ",
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
            node_stack.into_iter().map(|s| (s, true, 0)).collect(),
            "",
        )
    }

    fn query<'a>(
        sheet: &'a PropertySheetJSON,
        node_stack: Vec<(&'static str, bool, usize)>,
        leaf_text: &str,
    ) -> &'a PropertySet {
        let mut state_id = 0;
        for (kind, is_named, child_index) in node_stack {
            let state = &sheet.states[state_id];
            state_id = state
                .transitions
                .iter()
                .find(|transition| {
                    transition.kind == kind
                        && transition.named == is_named
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
