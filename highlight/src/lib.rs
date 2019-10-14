pub mod c_lib;
pub mod util;

pub use c_lib as c;
use serde::{Deserialize, Deserializer, Serialize, Serializer};
use serde_derive::*;
use std::mem::transmute;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::{cmp, fmt, str, usize};
use tree_sitter::{Language, Node, Parser, Point, PropertySheet, Range, Tree, TreePropertyCursor};

const CANCELLATION_CHECK_INTERVAL: usize = 100;

#[derive(Debug, PartialEq, Eq)]
pub enum Error {
    Cancelled,
    InvalidLanguage,
    Unknown,
}

#[derive(Debug)]
enum TreeStep {
    Child {
        index: isize,
        kinds: Option<Vec<u16>>,
    },
    Children {
        kinds: Option<Vec<u16>>,
    },
    Next {
        kinds: Option<Vec<u16>>,
    },
}

#[derive(Debug)]
enum InjectionLanguage {
    Literal(String),
    TreePath(Vec<TreeStep>),
}

#[derive(Debug)]
struct Injection {
    language: InjectionLanguage,
    content: Vec<TreeStep>,
    includes_children: bool,
}

#[derive(Debug)]
pub struct Properties {
    highlight: Option<Highlight>,
    highlight_nonlocal: Option<Highlight>,
    injections: Vec<Injection>,
    local_scope: Option<bool>,
    local_definition: bool,
    local_reference: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
#[repr(u16)]
pub enum Highlight {
    Attribute,
    Comment,
    Constant,
    ConstantBuiltin,
    Constructor,
    ConstructorBuiltin,
    Embedded,
    Escape,
    Function,
    FunctionBuiltin,
    Keyword,
    Number,
    Operator,
    Property,
    PropertyBuiltin,
    Punctuation,
    PunctuationBracket,
    PunctuationDelimiter,
    PunctuationSpecial,
    String,
    StringSpecial,
    Tag,
    Type,
    TypeBuiltin,
    Variable,
    VariableBuiltin,
    VariableParameter,
    Unknown,
}

#[derive(Debug)]
struct Scope<'a> {
    inherits: bool,
    local_defs: Vec<(&'a str, Highlight)>,
}

struct Layer<'a> {
    _tree: Tree,
    cursor: TreePropertyCursor<'a, Properties>,
    ranges: Vec<Range>,
    at_node_end: bool,
    depth: usize,
    opaque: bool,
    scope_stack: Vec<Scope<'a>>,
    local_highlight: Option<Highlight>,
}

struct Highlighter<'a, T>
where
    T: Fn(&str) -> Option<(Language, &'a PropertySheet<Properties>)>,
{
    injection_callback: T,
    source: &'a [u8],
    source_offset: usize,
    parser: Parser,
    layers: Vec<Layer<'a>>,
    max_opaque_layer_depth: usize,
    operation_count: usize,
    cancellation_flag: Option<&'a AtomicUsize>,
}

#[derive(Copy, Clone, Debug)]
pub enum HighlightEvent {
    Source { start: usize, end: usize },
    HighlightStart(Highlight),
    HighlightEnd,
}

#[derive(Debug, Deserialize)]
#[serde(untagged)]
enum TreePathArgJSON {
    TreePath(TreePathJSON),
    Number(isize),
    String(String),
}

#[derive(Debug, Deserialize)]
#[serde(tag = "name")]
enum TreePathJSON {
    #[serde(rename = "this")]
    This,
    #[serde(rename = "child")]
    Child { args: Vec<TreePathArgJSON> },
    #[serde(rename = "next")]
    Next { args: Vec<TreePathArgJSON> },
    #[serde(rename = "children")]
    Children { args: Vec<TreePathArgJSON> },
}

#[derive(Debug, Deserialize)]
#[serde(untagged)]
enum InjectionLanguageJSON {
    List(Vec<InjectionLanguageJSON>),
    TreePath(TreePathJSON),
    Literal(String),
}

#[derive(Debug, Deserialize)]
#[serde(untagged)]
enum InjectionContentJSON {
    List(Vec<InjectionContentJSON>),
    TreePath(TreePathJSON),
}

#[derive(Debug, Deserialize)]
#[serde(untagged)]
enum InjectionIncludesChildrenJSON {
    List(Vec<bool>),
    Single(bool),
}

#[derive(Debug, Deserialize)]
struct PropertiesJSON {
    highlight: Option<Highlight>,
    #[serde(rename = "highlight-nonlocal")]
    highlight_nonlocal: Option<Highlight>,

    #[serde(rename = "injection-language")]
    injection_language: Option<InjectionLanguageJSON>,
    #[serde(rename = "injection-content")]
    injection_content: Option<InjectionContentJSON>,
    #[serde(default, rename = "injection-includes-children")]
    injection_includes_children: Option<InjectionIncludesChildrenJSON>,

    #[serde(default, rename = "local-scope")]
    local_scope: bool,
    #[serde(default, rename = "local-scope-inherit")]
    local_scope_inherit: bool,
    #[serde(default, rename = "local-definition")]
    local_definition: bool,
    #[serde(default, rename = "local-reference")]
    local_reference: bool,
}

#[derive(Debug)]
pub enum PropertySheetError {
    InvalidJSON(serde_json::Error),
    InvalidRegex(regex::Error),
    InvalidFormat(String),
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Error::Cancelled => write!(f, "Cancelled"),
            Error::InvalidLanguage => write!(f, "Invalid language"),
            Error::Unknown => write!(f, "Unknown error"),
        }
    }
}

impl fmt::Display for PropertySheetError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            PropertySheetError::InvalidJSON(e) => e.fmt(f),
            PropertySheetError::InvalidRegex(e) => e.fmt(f),
            PropertySheetError::InvalidFormat(e) => e.fmt(f),
        }
    }
}

impl<'a> fmt::Debug for Layer<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "Layer {{ at_node_end: {}, node: {:?} }}",
            self.at_node_end,
            self.cursor.node()
        )?;
        Ok(())
    }
}

pub fn load_property_sheet(
    language: Language,
    json: &str,
) -> Result<PropertySheet<Properties>, PropertySheetError> {
    let sheet = PropertySheet::new(language, json).map_err(|e| match e {
        tree_sitter::PropertySheetError::InvalidJSON(e) => PropertySheetError::InvalidJSON(e),
        tree_sitter::PropertySheetError::InvalidRegex(e) => PropertySheetError::InvalidRegex(e),
    })?;
    let sheet = sheet
        .map(|p| Properties::new(p, language))
        .map_err(PropertySheetError::InvalidFormat)?;
    Ok(sheet)
}

impl Highlight {
    pub fn from_usize(i: usize) -> Option<Self> {
        if i <= (Highlight::Unknown as usize) {
            Some(unsafe { transmute(i as u16) })
        } else {
            None
        }
    }
}

impl Properties {
    fn new(json: PropertiesJSON, language: Language) -> Result<Self, String> {
        let injections = match (json.injection_language, json.injection_content) {
            (None, None) => Ok(Vec::new()),
            (Some(_), None) => Err(
                "Must specify an injection-content along with an injection-language".to_string(),
            ),
            (None, Some(_)) => Err(
                "Must specify an injection-language along with an injection-content".to_string(),
            ),
            (Some(language_json), Some(content_json)) => {
                let languages = match language_json {
                    InjectionLanguageJSON::List(list) => {
                        let mut result = Vec::with_capacity(list.len());
                        for element in list {
                            result.push(match element {
                                InjectionLanguageJSON::TreePath(p) => {
                                    let mut result = Vec::new();
                                    Self::flatten_tree_path(p, &mut result, language)?;
                                    InjectionLanguage::TreePath(result)
                                }
                                InjectionLanguageJSON::Literal(s) => InjectionLanguage::Literal(s),
                                InjectionLanguageJSON::List(_) => {
                                    panic!("Injection-language cannot be a list of lists")
                                }
                            })
                        }
                        result
                    }
                    InjectionLanguageJSON::TreePath(p) => vec![{
                        let mut result = Vec::new();
                        Self::flatten_tree_path(p, &mut result, language)?;
                        InjectionLanguage::TreePath(result)
                    }],
                    InjectionLanguageJSON::Literal(s) => vec![InjectionLanguage::Literal(s)],
                };

                let contents = match content_json {
                    InjectionContentJSON::List(l) => {
                        let mut result = Vec::with_capacity(l.len());
                        for element in l {
                            result.push(match element {
                                InjectionContentJSON::TreePath(p) => {
                                    let mut result = Vec::new();
                                    Self::flatten_tree_path(p, &mut result, language)?;
                                    result
                                }
                                InjectionContentJSON::List(_) => {
                                    panic!("Injection-content cannot be a list of lists")
                                }
                            })
                        }
                        result
                    }
                    InjectionContentJSON::TreePath(p) => vec![{
                        let mut result = Vec::new();
                        Self::flatten_tree_path(p, &mut result, language)?;
                        result
                    }],
                };

                let mut includes_children = match json.injection_includes_children {
                    Some(InjectionIncludesChildrenJSON::List(v)) => v,
                    Some(InjectionIncludesChildrenJSON::Single(v)) => vec![v],
                    None => vec![false],
                };

                if languages.len() == contents.len() {
                    includes_children.resize(languages.len(), includes_children[0]);
                    Ok(languages
                        .into_iter()
                        .zip(contents.into_iter())
                        .zip(includes_children.into_iter())
                        .map(|((language, content), includes_children)| Injection {
                            language,
                            content,
                            includes_children,
                        })
                        .collect())
                } else {
                    Err(format!(
                        "Mismatch: got {} injection-language values but {} injection-content values",
                        languages.len(),
                        contents.len(),
                    ))
                }
            }
        }?;

        Ok(Self {
            highlight: json.highlight,
            highlight_nonlocal: json.highlight_nonlocal,
            local_scope: if json.local_scope {
                Some(json.local_scope_inherit)
            } else {
                None
            },
            local_definition: json.local_definition,
            local_reference: json.local_reference,
            injections,
        })
    }

    // Transform a tree path from the format expressed directly in the property sheet
    // (nested function calls), to a flat sequence of steps for transforming a list of
    // nodes. This way, we can evaluate these tree paths with no recursion and a single
    // vector of intermediate storage.
    fn flatten_tree_path(
        p: TreePathJSON,
        steps: &mut Vec<TreeStep>,
        language: Language,
    ) -> Result<(), String> {
        match p {
            TreePathJSON::This => {}
            TreePathJSON::Child { args } => {
                let (tree_path, index, kinds) = Self::parse_args("child", args, language)?;
                Self::flatten_tree_path(tree_path, steps, language)?;
                steps.push(TreeStep::Child {
                    index: index
                        .ok_or_else(|| "The `child` function requires an index".to_string())?,
                    kinds: kinds,
                });
            }
            TreePathJSON::Children { args } => {
                let (tree_path, _, kinds) = Self::parse_args("children", args, language)?;
                Self::flatten_tree_path(tree_path, steps, language)?;
                steps.push(TreeStep::Children { kinds });
            }
            TreePathJSON::Next { args } => {
                let (tree_path, _, kinds) = Self::parse_args("next", args, language)?;
                Self::flatten_tree_path(tree_path, steps, language)?;
                steps.push(TreeStep::Next { kinds });
            }
        }
        Ok(())
    }

    fn parse_args(
        name: &str,
        args: Vec<TreePathArgJSON>,
        language: Language,
    ) -> Result<(TreePathJSON, Option<isize>, Option<Vec<u16>>), String> {
        let tree_path;
        let mut index = None;
        let mut kinds = Vec::new();
        let mut iter = args.into_iter();

        match iter.next() {
            Some(TreePathArgJSON::TreePath(p)) => tree_path = p,
            _ => {
                return Err(format!(
                    "First argument to `{}()` must be a tree path",
                    name
                ));
            }
        }

        for arg in iter {
            match arg {
                TreePathArgJSON::TreePath(_) => {
                    return Err(format!(
                        "Other arguments to `{}()` must be strings or numbers",
                        name
                    ));
                }
                TreePathArgJSON::Number(i) => index = Some(i),
                TreePathArgJSON::String(s) => kinds.push(s),
            }
        }

        if kinds.len() > 0 {
            let mut kind_ids = Vec::new();
            for i in 0..(language.node_kind_count() as u16) {
                if kinds.iter().any(|s| s == language.node_kind_for_id(i))
                    && language.node_kind_is_named(i)
                {
                    kind_ids.push(i);
                }
            }
            if kind_ids.len() == 0 {
                return Err(format!("Non-existent node kinds: {:?}", kinds));
            }

            Ok((tree_path, index, Some(kind_ids)))
        } else {
            Ok((tree_path, index, None))
        }
    }
}

impl<'a, F> Highlighter<'a, F>
where
    F: Fn(&str) -> Option<(Language, &'a PropertySheet<Properties>)>,
{
    fn new(
        source: &'a [u8],
        language: Language,
        property_sheet: &'a PropertySheet<Properties>,
        injection_callback: F,
        cancellation_flag: Option<&'a AtomicUsize>,
    ) -> Result<Self, Error> {
        let mut parser = Parser::new();
        unsafe { parser.set_cancellation_flag(cancellation_flag.clone()) };
        parser
            .set_language(language)
            .map_err(|_| Error::InvalidLanguage)?;
        let tree = parser.parse(source, None).ok_or_else(|| Error::Cancelled)?;
        Ok(Self {
            parser,
            source,
            cancellation_flag,
            injection_callback,
            source_offset: 0,
            operation_count: 0,
            max_opaque_layer_depth: 0,
            layers: vec![Layer::new(
                source,
                tree,
                property_sheet,
                vec![Range {
                    start_byte: 0,
                    end_byte: usize::MAX,
                    start_point: Point::new(0, 0),
                    end_point: Point::new(usize::MAX, usize::MAX),
                }],
                0,
                true,
            )],
        })
    }

    fn emit_source(&mut self, next_offset: usize) -> HighlightEvent {
        let result = HighlightEvent::Source {
            start: self.source_offset,
            end: next_offset,
        };
        self.source_offset = next_offset;
        result
    }

    fn process_tree_step(&self, step: &TreeStep, nodes: &mut Vec<Node>) {
        let len = nodes.len();
        for i in 0..len {
            let node = nodes[i];
            match step {
                TreeStep::Child { index, kinds } => {
                    let index = if *index >= 0 {
                        *index as usize
                    } else {
                        (node.child_count() as isize + *index) as usize
                    };
                    if let Some(child) = node.child(index) {
                        if let Some(kinds) = kinds {
                            if kinds.contains(&child.kind_id()) {
                                nodes.push(child);
                            }
                        } else {
                            nodes.push(child);
                        }
                    }
                }
                TreeStep::Children { kinds } => {
                    for child in node.children() {
                        if let Some(kinds) = kinds {
                            if kinds.contains(&child.kind_id()) {
                                nodes.push(child);
                            }
                        } else {
                            nodes.push(child);
                        }
                    }
                }
                TreeStep::Next { .. } => unimplemented!(),
            }
        }
        nodes.drain(0..len);
    }

    fn nodes_for_tree_path(&self, node: Node<'a>, steps: &Vec<TreeStep>) -> Vec<Node<'a>> {
        let mut nodes = vec![node];
        for step in steps.iter() {
            self.process_tree_step(step, &mut nodes);
        }
        nodes
    }

    // An injected language name may either be specified as a fixed string, or based
    // on the text of some node in the syntax tree.
    fn injection_language_string(
        &self,
        node: &Node<'a>,
        language: &InjectionLanguage,
    ) -> Option<String> {
        match language {
            InjectionLanguage::Literal(s) => Some(s.to_string()),
            InjectionLanguage::TreePath(steps) => self
                .nodes_for_tree_path(*node, steps)
                .first()
                .and_then(|node| {
                    str::from_utf8(&self.source[node.start_byte()..node.end_byte()])
                        .map(|s| s.to_owned())
                        .ok()
                }),
        }
    }

    // Compute the ranges that should be included when parsing an injection.
    // This takes into account three things:
    // * `parent_ranges` - The new injection may be nested inside of *another* injection
    //   (e.g. JavaScript within HTML within ERB). The parent injection's ranges must
    //   be taken into account.
    // * `nodes` - Every injection takes place within a set of nodes. The injection ranges
    //   are the ranges of those nodes.
    // * `includes_children` - For some injections, the content nodes' children should be
    //   excluded from the nested document, so that only the content nodes' *own* content
    //   is reparsed. For other injections, the content nodes' entire ranges should be
    //   reparsed, including the ranges of their children.
    fn intersect_ranges(
        parent_ranges: &Vec<Range>,
        nodes: &Vec<Node>,
        includes_children: bool,
    ) -> Vec<Range> {
        let mut result = Vec::new();
        let mut parent_range_iter = parent_ranges.iter();
        let mut parent_range = parent_range_iter
            .next()
            .expect("Layers should only be constructed with non-empty ranges vectors");
        for node in nodes.iter() {
            let mut preceding_range = Range {
                start_byte: 0,
                start_point: Point::new(0, 0),
                end_byte: node.start_byte(),
                end_point: node.start_position(),
            };
            let following_range = Range {
                start_byte: node.end_byte(),
                start_point: node.end_position(),
                end_byte: usize::MAX,
                end_point: Point::new(usize::MAX, usize::MAX),
            };

            for excluded_range in node
                .children()
                .filter_map(|child| {
                    if includes_children {
                        None
                    } else {
                        Some(child.range())
                    }
                })
                .chain([following_range].iter().cloned())
            {
                let mut range = Range {
                    start_byte: preceding_range.end_byte,
                    start_point: preceding_range.end_point,
                    end_byte: excluded_range.start_byte,
                    end_point: excluded_range.start_point,
                };
                preceding_range = excluded_range;

                if range.end_byte < parent_range.start_byte {
                    continue;
                }

                while parent_range.start_byte <= range.end_byte {
                    if parent_range.end_byte > range.start_byte {
                        if range.start_byte < parent_range.start_byte {
                            range.start_byte = parent_range.start_byte;
                            range.start_point = parent_range.start_point;
                        }

                        if parent_range.end_byte < range.end_byte {
                            if range.start_byte < parent_range.end_byte {
                                result.push(Range {
                                    start_byte: range.start_byte,
                                    start_point: range.start_point,
                                    end_byte: parent_range.end_byte,
                                    end_point: parent_range.end_point,
                                });
                            }
                            range.start_byte = parent_range.end_byte;
                            range.start_point = parent_range.end_point;
                        } else {
                            if range.start_byte < range.end_byte {
                                result.push(range);
                            }
                            break;
                        }
                    }

                    if let Some(next_range) = parent_range_iter.next() {
                        parent_range = next_range;
                    } else {
                        return result;
                    }
                }
            }
        }
        result
    }

    fn add_layer(
        &mut self,
        language_string: &str,
        ranges: Vec<Range>,
        depth: usize,
        includes_children: bool,
    ) -> Option<Error> {
        if let Some((language, property_sheet)) = (self.injection_callback)(language_string) {
            if self.parser.set_language(language).is_err() {
                return Some(Error::InvalidLanguage);
            }
            self.parser.set_included_ranges(&ranges);
            if let Some(tree) = self.parser.parse(self.source, None) {
                let layer = Layer::new(
                    self.source,
                    tree,
                    property_sheet,
                    ranges,
                    depth,
                    includes_children,
                );
                if includes_children && depth > self.max_opaque_layer_depth {
                    self.max_opaque_layer_depth = depth;
                }
                match self.layers.binary_search_by(|l| l.cmp(&layer)) {
                    Ok(i) | Err(i) => self.layers.insert(i, layer),
                };
            } else {
                return Some(Error::Cancelled);
            }
        }
        None
    }

    fn remove_first_layer(&mut self) {
        let layer = self.layers.remove(0);
        if layer.opaque && layer.depth == self.max_opaque_layer_depth {
            self.max_opaque_layer_depth = self
                .layers
                .iter()
                .filter_map(|l| if l.opaque { Some(l.depth) } else { None })
                .max()
                .unwrap_or(0);
        }
    }
}

impl<'a, T> Iterator for Highlighter<'a, T>
where
    T: Fn(&str) -> Option<(Language, &'a PropertySheet<Properties>)>,
{
    type Item = Result<HighlightEvent, Error>;

    fn next(&mut self) -> Option<Self::Item> {
        if let Some(cancellation_flag) = self.cancellation_flag {
            self.operation_count += 1;
            if self.operation_count >= CANCELLATION_CHECK_INTERVAL {
                self.operation_count = 0;
                if cancellation_flag.load(Ordering::Relaxed) != 0 {
                    return Some(Err(Error::Cancelled));
                }
            }
        }

        while !self.layers.is_empty() {
            let mut scope_event = None;
            let first_layer = &self.layers[0];

            // If the current layer is not covered up by a nested layer, then
            // process any scope boundaries and language injections for the layer's
            // current position.
            let first_layer_is_visible = first_layer.depth >= self.max_opaque_layer_depth;
            if first_layer_is_visible {
                let local_highlight = first_layer.local_highlight;
                let properties = &first_layer.cursor.node_properties();

                // Add any injections for the current node.
                if !first_layer.at_node_end {
                    let node = first_layer.cursor.node();
                    let injections = properties
                        .injections
                        .iter()
                        .filter_map(
                            |Injection {
                                 language,
                                 content,
                                 includes_children,
                             }| {
                                if let Some(language) =
                                    self.injection_language_string(&node, language)
                                {
                                    let nodes = self.nodes_for_tree_path(node, content);
                                    let ranges = Self::intersect_ranges(
                                        &first_layer.ranges,
                                        &nodes,
                                        *includes_children,
                                    );
                                    if ranges.len() > 0 {
                                        return Some((language, ranges, *includes_children));
                                    }
                                }
                                None
                            },
                        )
                        .collect::<Vec<_>>();

                    let depth = first_layer.depth + 1;
                    for (language, ranges, includes_children) in injections {
                        if let Some(error) =
                            self.add_layer(&language, ranges, depth, includes_children)
                        {
                            return Some(Err(error));
                        }
                    }
                }

                // Determine if any scopes start or end at the current position.
                let first_layer = &mut self.layers[0];
                if let Some(highlight) = local_highlight
                    .or(properties.highlight_nonlocal)
                    .or(properties.highlight)
                {
                    let next_offset = cmp::min(self.source.len(), first_layer.offset());

                    // Before returning any highlight boundaries, return any remaining slice of
                    // the source code the precedes that highlight boundary.
                    if self.source_offset < next_offset {
                        return Some(Ok(self.emit_source(next_offset)));
                    }

                    scope_event = if first_layer.at_node_end {
                        Some(Ok(HighlightEvent::HighlightEnd))
                    } else {
                        Some(Ok(HighlightEvent::HighlightStart(highlight)))
                    };
                }
            }

            // Advance the current layer's tree cursor. This might cause that cursor to move
            // beyond one of the other layers' cursors for a different syntax tree, so we need
            // to re-sort the layers. If the cursor is already at the end of its syntax tree,
            // remove it.
            if self.layers[0].advance() {
                let mut index = 0;
                while self.layers.get(index + 1).map_or(false, |next| {
                    self.layers[index].cmp(next) == cmp::Ordering::Greater
                }) {
                    self.layers.swap(index, index + 1);
                    index += 1;
                }
            } else {
                self.remove_first_layer();
            }

            if scope_event.is_some() {
                return scope_event;
            }
        }

        if self.source_offset < self.source.len() {
            Some(Ok(self.emit_source(self.source.len())))
        } else {
            None
        }
    }
}

impl<'a, T> fmt::Debug for Highlighter<'a, T>
where
    T: Fn(&str) -> Option<(Language, &'a PropertySheet<Properties>)>,
{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        if let Some(layer) = self.layers.first() {
            let node = layer.cursor.node();
            let position = if layer.at_node_end {
                node.end_position()
            } else {
                node.start_position()
            };
            write!(
                f,
                "{{Highlighter position: {:?}, kind: {}, at_end: {}, props: {:?}}}",
                position,
                node.kind(),
                layer.at_node_end,
                layer.cursor.node_properties()
            )?;
        }
        Ok(())
    }
}

impl<'a> Layer<'a> {
    fn new(
        source: &'a [u8],
        tree: Tree,
        sheet: &'a PropertySheet<Properties>,
        ranges: Vec<Range>,
        depth: usize,
        opaque: bool,
    ) -> Self {
        // The cursor's lifetime parameter indicates that the tree must outlive the cursor.
        // But because the tree is really a pointer to the heap, the cursor can remain
        // valid when the tree is moved. There's no way to express this with lifetimes
        // right now, so we have to `transmute` the cursor's lifetime.
        let cursor = unsafe { transmute(tree.walk_with_properties(sheet, source)) };
        Self {
            _tree: tree,
            cursor,
            ranges,
            depth,
            opaque,
            at_node_end: false,
            scope_stack: vec![Scope {
                inherits: false,
                local_defs: Vec::new(),
            }],
            local_highlight: None,
        }
    }

    fn cmp(&self, other: &Layer) -> cmp::Ordering {
        // Events are ordered primarily by their position in the document. But if
        // one highlight starts at a given position and another highlight ends at that
        // same position, return the highlight end event before the highlight start event.
        self.offset()
            .cmp(&other.offset())
            .then_with(|| other.at_node_end.cmp(&self.at_node_end))
            .then_with(|| self.depth.cmp(&other.depth))
    }

    fn offset(&self) -> usize {
        if self.at_node_end {
            self.cursor.node().end_byte()
        } else {
            self.cursor.node().start_byte()
        }
    }

    fn advance(&mut self) -> bool {
        // Clear the current local highlighting class, which may be re-populated
        // if we enter a node that represents a local definition or local reference.
        self.local_highlight = None;

        // Step through the tree in a depth-first traversal, stopping at both
        // the start and end position of every node.
        if self.at_node_end {
            self.leave_node();
            if self.cursor.goto_next_sibling() {
                self.enter_node();
                self.at_node_end = false;
            } else if !self.cursor.goto_parent() {
                return false;
            }
        } else if self.cursor.goto_first_child() {
            self.enter_node();
        } else {
            self.at_node_end = true;
        }
        true
    }

    fn enter_node(&mut self) {
        let node = self.cursor.node();
        let props = self.cursor.node_properties();
        let node_text = if props.local_definition || props.local_reference {
            node.utf8_text(self.cursor.source()).ok()
        } else {
            None
        };

        // If this node represents a local definition, then record its highlighting class
        // and store the highlighting class in the current local scope.
        if props.local_definition {
            if let (Some(text), Some(inner_scope), Some(highlight)) =
                (node_text, self.scope_stack.last_mut(), props.highlight)
            {
                self.local_highlight = props.highlight;
                if let Err(i) = inner_scope.local_defs.binary_search_by_key(&text, |e| e.0) {
                    inner_scope.local_defs.insert(i, (text, highlight));
                }
            }
        }
        // If this node represents a local reference, then look it up in the current scope
        // stack. If a local definition is found, record its highlighting class.
        else if props.local_reference {
            if let Some(text) = node_text {
                for scope in self.scope_stack.iter().rev() {
                    if let Ok(i) = scope.local_defs.binary_search_by_key(&text, |e| e.0) {
                        self.local_highlight = Some(scope.local_defs[i].1);
                        break;
                    }
                    if !scope.inherits {
                        break;
                    }
                }
            }
        }
        // If this node represents a new local scope, then push it onto the scope stack.
        if let Some(inherits) = props.local_scope {
            self.scope_stack.push(Scope {
                inherits,
                local_defs: Vec::new(),
            });
        }
    }

    fn leave_node(&mut self) {
        let props = self.cursor.node_properties();
        if props.local_scope.is_some() {
            self.scope_stack.pop();
        }
    }
}

impl<'de> Deserialize<'de> for Highlight {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let s = String::deserialize(deserializer)?;
        match s.as_str() {
            "attribute" => Ok(Highlight::Attribute),
            "comment" => Ok(Highlight::Comment),
            "constant" => Ok(Highlight::Constant),
            "constant.builtin" => Ok(Highlight::ConstantBuiltin),
            "constructor" => Ok(Highlight::Constructor),
            "constructor.builtin" => Ok(Highlight::ConstructorBuiltin),
            "embedded" => Ok(Highlight::Embedded),
            "escape" => Ok(Highlight::Escape),
            "function" => Ok(Highlight::Function),
            "function.builtin" => Ok(Highlight::FunctionBuiltin),
            "keyword" => Ok(Highlight::Keyword),
            "number" => Ok(Highlight::Number),
            "operator" => Ok(Highlight::Operator),
            "property" => Ok(Highlight::Property),
            "property.builtin" => Ok(Highlight::PropertyBuiltin),
            "punctuation" => Ok(Highlight::Punctuation),
            "punctuation.bracket" => Ok(Highlight::PunctuationBracket),
            "punctuation.delimiter" => Ok(Highlight::PunctuationDelimiter),
            "punctuation.special" => Ok(Highlight::PunctuationSpecial),
            "string" => Ok(Highlight::String),
            "string.special" => Ok(Highlight::StringSpecial),
            "type" => Ok(Highlight::Type),
            "type.builtin" => Ok(Highlight::TypeBuiltin),
            "variable" => Ok(Highlight::Variable),
            "variable.builtin" => Ok(Highlight::VariableBuiltin),
            "variable.parameter" => Ok(Highlight::VariableParameter),
            "tag" => Ok(Highlight::Tag),
            _ => Ok(Highlight::Unknown),
        }
    }
}

impl Serialize for Highlight {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        match self {
            Highlight::Attribute => serializer.serialize_str("attribute"),
            Highlight::Comment => serializer.serialize_str("comment"),
            Highlight::Constant => serializer.serialize_str("constant"),
            Highlight::ConstantBuiltin => serializer.serialize_str("constant.builtin"),
            Highlight::Constructor => serializer.serialize_str("constructor"),
            Highlight::ConstructorBuiltin => serializer.serialize_str("constructor.builtin"),
            Highlight::Embedded => serializer.serialize_str("embedded"),
            Highlight::Escape => serializer.serialize_str("escape"),
            Highlight::Function => serializer.serialize_str("function"),
            Highlight::FunctionBuiltin => serializer.serialize_str("function.builtin"),
            Highlight::Keyword => serializer.serialize_str("keyword"),
            Highlight::Number => serializer.serialize_str("number"),
            Highlight::Operator => serializer.serialize_str("operator"),
            Highlight::Property => serializer.serialize_str("property"),
            Highlight::PropertyBuiltin => serializer.serialize_str("property.builtin"),
            Highlight::Punctuation => serializer.serialize_str("punctuation"),
            Highlight::PunctuationBracket => serializer.serialize_str("punctuation.bracket"),
            Highlight::PunctuationDelimiter => serializer.serialize_str("punctuation.delimiter"),
            Highlight::PunctuationSpecial => serializer.serialize_str("punctuation.special"),
            Highlight::String => serializer.serialize_str("string"),
            Highlight::StringSpecial => serializer.serialize_str("string.special"),
            Highlight::Type => serializer.serialize_str("type"),
            Highlight::TypeBuiltin => serializer.serialize_str("type.builtin"),
            Highlight::Variable => serializer.serialize_str("variable"),
            Highlight::VariableBuiltin => serializer.serialize_str("variable.builtin"),
            Highlight::VariableParameter => serializer.serialize_str("variable.parameter"),
            Highlight::Tag => serializer.serialize_str("tag"),
            Highlight::Unknown => serializer.serialize_str(""),
        }
    }
}

pub trait HTMLAttributeCallback<'a>: Fn(Highlight) -> &'a str {}

pub fn highlight<'a, F>(
    source: &'a [u8],
    language: Language,
    property_sheet: &'a PropertySheet<Properties>,
    cancellation_flag: Option<&'a AtomicUsize>,
    injection_callback: F,
) -> Result<impl Iterator<Item = Result<HighlightEvent, Error>> + 'a, Error>
where
    F: Fn(&str) -> Option<(Language, &'a PropertySheet<Properties>)> + 'a,
{
    Highlighter::new(
        source,
        language,
        property_sheet,
        injection_callback,
        cancellation_flag,
    )
}

pub fn highlight_html<'a, F1, F2>(
    source: &'a [u8],
    language: Language,
    property_sheet: &'a PropertySheet<Properties>,
    cancellation_flag: Option<&'a AtomicUsize>,
    injection_callback: F1,
    attribute_callback: F2,
) -> Result<Vec<String>, Error>
where
    F1: Fn(&str) -> Option<(Language, &'a PropertySheet<Properties>)>,
    F2: Fn(Highlight) -> &'a str,
{
    let mut renderer = HtmlRenderer::new();
    renderer.render(
        Highlighter::new(
            source,
            language,
            property_sheet,
            injection_callback,
            cancellation_flag,
        )?,
        source,
        &|s| (attribute_callback)(s).as_bytes(),
    )?;
    Ok(renderer
        .line_offsets
        .iter()
        .enumerate()
        .map(|(i, offset)| {
            let offset = *offset as usize;
            let next_offset = renderer
                .line_offsets
                .get(i + 1)
                .map_or(renderer.html.len(), |i| *i as usize);
            String::from_utf8(renderer.html[offset..next_offset].to_vec()).unwrap()
        })
        .collect())
}

pub struct HtmlRenderer {
    pub html: Vec<u8>,
    pub line_offsets: Vec<u32>,
}

impl HtmlRenderer {
    fn new() -> Self {
        HtmlRenderer {
            html: Vec::new(),
            line_offsets: vec![0],
        }
    }

    pub fn reset(&mut self) {
        self.html.clear();
        self.line_offsets.clear();
        self.line_offsets.push(0);
    }

    pub fn render<'a, F>(
        &mut self,
        highlighter: impl Iterator<Item = Result<HighlightEvent, Error>>,
        source: &'a [u8],
        attribute_callback: &F,
    ) -> Result<(), Error>
    where
        F: Fn(Highlight) -> &'a [u8],
    {
        let mut highlights = Vec::new();
        for event in highlighter {
            match event {
                Ok(HighlightEvent::HighlightStart(s)) => {
                    highlights.push(s);
                    self.start_highlight(s, attribute_callback);
                }
                Ok(HighlightEvent::HighlightEnd) => {
                    highlights.pop();
                    self.end_highlight();
                }
                Ok(HighlightEvent::Source { start, end }) => {
                    self.add_text(&source[start..end], &highlights, attribute_callback);
                }
                Err(a) => return Err(a),
            }
        }
        if self.html.last() != Some(&b'\n') {
            self.html.push(b'\n');
        }
        if self.line_offsets.last() == Some(&(self.html.len() as u32)) {
            self.line_offsets.pop();
        }
        Ok(())
    }

    fn start_highlight<'a, F>(&mut self, h: Highlight, attribute_callback: &F)
    where
        F: Fn(Highlight) -> &'a [u8],
    {
        let attribute_string = (attribute_callback)(h);
        self.html.extend(b"<span");
        if !attribute_string.is_empty() {
            self.html.extend(b" ");
            self.html.extend(attribute_string);
        }
        self.html.extend(b">");
    }

    fn end_highlight(&mut self) {
        self.html.extend(b"</span>");
    }

    fn add_text<'a, F>(&mut self, src: &[u8], highlights: &Vec<Highlight>, attribute_callback: &F)
    where
        F: Fn(Highlight) -> &'a [u8],
    {
        for c in util::LossyUtf8::new(src).flat_map(|p| p.bytes()) {
            if c == b'\n' {
                if self.html.ends_with(b"\r") {
                    self.html.pop();
                }
                highlights.iter().for_each(|_| self.end_highlight());
                self.html.push(c);
                self.line_offsets.push(self.html.len() as u32);
                highlights
                    .iter()
                    .for_each(|scope| self.start_highlight(*scope, attribute_callback));
            } else if let Some(escape) = util::html_escape(c) {
                self.html.extend_from_slice(escape);
            } else {
                self.html.push(c);
            }
        }
    }
}
