use crate::error::{Error, Result};
use rsass;
use rsass::sass::Value;
use std::collections::{BTreeMap, BTreeSet, HashMap, VecDeque};
use std::fmt;
use std::fmt::Write;
use std::fs::{self, File};
use std::hash::{Hash, Hasher};
use std::path::{Path, PathBuf};
use tree_sitter::{self, PropertyStateJSON, PropertyTransitionJSON};

#[derive(Debug, PartialEq, Eq, Hash, Serialize)]
#[serde(untagged)]
enum PropertyValue {
    String(String),
    Object(PropertySet),
    Array(Vec<PropertyValue>),
}

type PropertySet = BTreeMap<String, PropertyValue>;
type PropertySheetJSON = tree_sitter::PropertySheetJSON<PropertySet>;
type StateId = u32;
type PropertySetId = u32;

#[derive(Clone, PartialEq, Eq)]
struct SelectorStep {
    kind: String,
    is_named: bool,
    is_immediate: bool,
    child_index: Option<i32>,
    text_pattern: Option<String>,
}

#[derive(PartialEq, Eq)]
struct Selector(Vec<SelectorStep>);

#[derive(Debug, PartialEq, Eq)]
struct Rule {
    selectors: Vec<Selector>,
    properties: PropertySet,
}

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct PropertyItem {
    rule_id: u32,
    selector_id: u32,
    step_id: u32,
}

#[derive(PartialEq, Eq)]
struct PropertyItemSet(BTreeSet<PropertyItem>);

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
struct SelectorMatch {
    specificity: u32,
    rule_id: u32,
    selector_id: u32,
}

struct Builder {
    rules: Vec<Rule>,
    output: PropertySheetJSON,
    ids_by_item_set: HashMap<PropertyItemSet, StateId>,
    ids_by_property_set: HashMap<PropertySet, PropertySetId>,
    item_set_queue: VecDeque<(PropertyItemSet, StateId)>,
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
            ids_by_property_set: HashMap::new(),
            item_set_queue: VecDeque::new(),
        }
    }

    fn build(self) -> PropertySheetJSON {
        let mut start_item_set = PropertyItemSet(BTreeSet::new());

        self.output
    }
}

impl Hash for PropertyItemSet {
    fn hash<H: Hasher>(&self, h: &mut H) {
        h.write_usize(self.0.len());
        for entry in &self.0 {
            entry.hash(h);
        }
    }
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

pub fn generate_property_sheets(repo_path: &Path) -> Result<()> {
    let src_dir_path = repo_path.join("src");
    let properties_dir_path = repo_path.join("properties");

    for entry in fs::read_dir(properties_dir_path)? {
        let property_sheet_css_path = entry?.path();
        let rules = parse_property_sheet(&property_sheet_css_path)?;

        for rule in &rules {
            eprintln!("rule: {:?}", rule);
        }

        let sheet = Builder::new(rules).build();
        let property_sheet_json_path = src_dir_path
            .join(property_sheet_css_path.file_name().unwrap())
            .with_extension("json");
        let mut property_sheet_json_file = File::create(property_sheet_json_path)?;
        serde_json::to_writer_pretty(&mut property_sheet_json_file, &sheet)?;
    }

    Ok(())
}

fn parse_property_sheet(path: &Path) -> Result<Vec<Rule>> {
    let mut i = 0;
    let mut items = rsass::parse_scss_file(path)?;
    while i < items.len() {
        match &items[i] {
            rsass::Item::Import(arg) => {
                if let Some(s) = get_sass_string(arg) {
                    let import_path = resolve_path(path, s)?;
                    let imported_items = rsass::parse_scss_file(&import_path)?;
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
                        eprintln!("schema path: {:?}", schema_path);
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
                properties.insert(name.to_string(), parse_sass_value(&value)?);
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
        Value::True => Ok(PropertyValue::String("true".to_string())),
        Value::False => Ok(PropertyValue::String("false".to_string())),
        _ => Err(Error(
            "Property values must be strings or function calls".to_string(),
        )),
    }
}

fn get_sass_string(value: &Value) -> Option<&str> {
    if let Value::Literal(s) = value {
        s.single_raw()
    } else {
        None
    }
}

fn resolve_path(base: &Path, path: impl AsRef<Path>) -> Result<PathBuf> {
    let mut result = base.to_owned();
    result.pop();
    result.push(path.as_ref());
    if result.exists() {
        Ok(result)
    } else {
        Err(Error(format!(
            "Could not resolve import path {:?}",
            path.as_ref()
        )))
    }
}
