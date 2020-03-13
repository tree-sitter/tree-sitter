use regex::Regex;
use serde::{Serialize, Serializer};
use std::{mem, ops, str};
use tree_sitter::{
    Language, Node, Parser, Query, QueryCursor, QueryError, QueryPredicateArg, Tree,
};

/// Contains the data neeeded to compute tags for code written in a
/// particular language.
pub struct TagsConfiguration {
    pub language: Language,
    pub query: Query,
    call_capture_index: Option<u32>,
    class_capture_index: Option<u32>,
    doc_capture_index: Option<u32>,
    function_capture_index: Option<u32>,
    method_capture_index: Option<u32>,
    module_capture_index: Option<u32>,
    name_capture_index: Option<u32>,
    pattern_info: Vec<PatternInfo>,
    _locals_pattern_index: usize,
}

pub struct TagsContext {
    parser: Parser,
    cursor: QueryCursor,
}

#[derive(Default)]
struct PatternInfo {
    docs_adjacent_capture: Option<u32>,
    doc_strip_regex: Option<Regex>,
}

struct TagsIter<'a, I>
where
    I: Iterator<Item = tree_sitter::QueryMatch<'a>>,
{
    matches: I,
    _tree: Tree,
    source: &'a [u8],
    config: &'a TagsConfiguration,
    tag_queue: Vec<(Node<'a>, usize, Tag<'a>)>,
}

#[derive(Debug, Serialize, Clone)]
pub struct Loc {
    pub byte_range: ops::Range<usize>,
    pub span: ops::Range<Pos>,
}

#[derive(Debug, Serialize, Clone)]
pub struct Pos {
    pub line: i64,
    pub column: i64,
}

#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum TagKind {
    Function,
    Method,
    Class,
    Module,
    Call,
}

#[derive(Debug, Serialize, Clone)]
pub struct Tag<'a> {
    pub kind: TagKind,
    pub name: &'a str,
    pub docs: Option<String>,
    pub loc: Loc,
    pub line: &'a str,
}

#[derive(Debug)]
pub enum Error {
    Query(QueryError),
    Regex(regex::Error),
}

impl TagsConfiguration {
    pub fn new(language: Language, tags_query: &str, locals_query: &str) -> Result<Self, Error> {
        let query = Query::new(language, &format!("{}{}", tags_query, locals_query))?;

        let locals_query_offset = tags_query.len();
        let mut locals_pattern_index = 0;
        for i in 0..(query.pattern_count()) {
            let pattern_offset = query.start_byte_for_pattern(i);
            if pattern_offset < locals_query_offset {
                locals_pattern_index += 1;
            }
        }

        let mut call_capture_index = None;
        let mut class_capture_index = None;
        let mut doc_capture_index = None;
        let mut function_capture_index = None;
        let mut method_capture_index = None;
        let mut module_capture_index = None;
        let mut name_capture_index = None;
        for (i, name) in query.capture_names().iter().enumerate() {
            let index = match name.as_str() {
                "call" => &mut call_capture_index,
                "class" => &mut class_capture_index,
                "doc" => &mut doc_capture_index,
                "function" => &mut function_capture_index,
                "method" => &mut method_capture_index,
                "module" => &mut module_capture_index,
                "name" => &mut name_capture_index,
                _ => continue,
            };
            *index = Some(i as u32);
        }

        let pattern_info = (0..query.pattern_count())
            .map(|pattern_index| {
                let mut info = PatternInfo::default();
                if let Some(doc_capture_index) = doc_capture_index {
                    for predicate in query.general_predicates(pattern_index) {
                        if predicate.args.get(0)
                            == Some(&QueryPredicateArg::Capture(doc_capture_index))
                        {
                            match (predicate.operator.as_ref(), predicate.args.get(1)) {
                                ("select-adjacent!", Some(QueryPredicateArg::Capture(index))) => {
                                    info.docs_adjacent_capture = Some(*index);
                                }
                                ("strip!", Some(QueryPredicateArg::String(pattern))) => {
                                    let regex = Regex::new(pattern.as_ref())?;
                                    info.doc_strip_regex = Some(regex);
                                }
                                _ => {}
                            }
                        }
                    }
                }
                return Ok(info);
            })
            .collect::<Result<Vec<_>, Error>>()?;

        Ok(TagsConfiguration {
            language,
            query,
            function_capture_index,
            class_capture_index,
            method_capture_index,
            module_capture_index,
            doc_capture_index,
            call_capture_index,
            name_capture_index,
            pattern_info,
            _locals_pattern_index: locals_pattern_index,
        })
    }
}

impl TagsContext {
    pub fn new() -> Self {
        TagsContext {
            parser: Parser::new(),
            cursor: QueryCursor::new(),
        }
    }

    // TODO: This should return an iterator rather than build up a vector
    pub fn generate_tags<'a>(
        &'a mut self,
        config: &'a TagsConfiguration,
        source: &'a [u8],
    ) -> impl Iterator<Item = Tag<'a>> + 'a {
        self.parser
            .set_language(config.language)
            .expect("Incompatible language");
        let tree = self
            .parser
            .parse(source, None)
            .expect("Parsing failed unexpectedly");

        // The `matches` iterator borrows the `Tree`, which prevents it from being moved.
        // But the tree is really just a pointer, so it's actually ok to move it.
        let tree_ref = unsafe { mem::transmute::<_, &'static Tree>(&tree) };
        let matches = self
            .cursor
            .matches(&config.query, tree_ref.root_node(), move |node| {
                &source[node.byte_range()]
            });
        TagsIter {
            matches,
            source,
            config,
            tag_queue: Vec::new(),
            _tree: tree,
        }
    }
}

impl<'a, I> Iterator for TagsIter<'a, I>
where
    I: Iterator<Item = tree_sitter::QueryMatch<'a>>,
{
    type Item = Tag<'a>;

    fn next(&mut self) -> Option<Tag<'a>> {
        loop {
            // If there is a queued tag for an earlier node in the syntax tree, then pop
            // it off of the queue and return it.
            if let Some(last_entry) = self.tag_queue.last() {
                if self.tag_queue.len() > 1
                    && self.tag_queue[0].0.end_byte() < last_entry.0.start_byte()
                {
                    return Some(self.tag_queue.remove(0).2);
                }
            }

            // If there is another match, then compute its tag and add it to the
            // tag queue.
            if let Some(mat) = self.matches.next() {
                let mut name = None;
                let mut doc_nodes = Vec::new();
                let mut tag_node = None;
                let mut tag_kind = TagKind::Call;
                let mut docs_adjacent_node = None;

                for capture in mat.captures {
                    let index = Some(capture.index);

                    if index == self.config.pattern_info[mat.pattern_index].docs_adjacent_capture {
                        docs_adjacent_node = Some(capture.node);
                    }

                    if index == self.config.name_capture_index {
                        name = str::from_utf8(&self.source[Some(capture.node)?.byte_range()]).ok();
                    } else if index == self.config.doc_capture_index {
                        doc_nodes.push(capture.node);
                    } else if index == self.config.call_capture_index {
                        tag_node = Some(capture.node);
                        tag_kind = TagKind::Call;
                    } else if index == self.config.class_capture_index {
                        tag_node = Some(capture.node);
                        tag_kind = TagKind::Class;
                    } else if index == self.config.function_capture_index {
                        tag_node = Some(capture.node);
                        tag_kind = TagKind::Function;
                    } else if index == self.config.method_capture_index {
                        tag_node = Some(capture.node);
                        tag_kind = TagKind::Method;
                    } else if index == self.config.module_capture_index {
                        tag_node = Some(capture.node);
                        tag_kind = TagKind::Module;
                    }
                }

                if let (Some(tag_node), Some(name)) = (tag_node, name) {
                    // If needed, filter the doc nodes based on their ranges, selecting
                    // only the slice that are adjacent to some specified node.
                    let mut docs_start_index = 0;
                    if let (Some(docs_adjacent_node), false) =
                        (docs_adjacent_node, doc_nodes.is_empty())
                    {
                        docs_start_index = doc_nodes.len();
                        let mut start_row = docs_adjacent_node.start_position().row;
                        while docs_start_index > 0 {
                            let doc_node = &doc_nodes[docs_start_index - 1];
                            let prev_doc_end_row = doc_node.end_position().row;
                            if prev_doc_end_row + 1 >= start_row {
                                docs_start_index -= 1;
                                start_row = doc_node.start_position().row;
                            } else {
                                break;
                            }
                        }
                    }

                    // Generate a doc string from all of the doc nodes, applying any strip regexes.
                    let mut docs = None;
                    for doc_node in &doc_nodes[docs_start_index..] {
                        if let Ok(content) = str::from_utf8(&self.source[doc_node.byte_range()]) {
                            let content = if let Some(regex) =
                                &self.config.pattern_info[mat.pattern_index].doc_strip_regex
                            {
                                regex.replace_all(content, "").to_string()
                            } else {
                                content.to_string()
                            };
                            match &mut docs {
                                None => docs = Some(content),
                                Some(d) => {
                                    d.push('\n');
                                    d.push_str(&content);
                                }
                            }
                        }
                    }

                    let source = &self.source;
                    let tag_from_node = |node: Node, kind: TagKind| -> Option<Tag> {
                        // Slice out the first line of the text corresponding to the node in question.
                        let mut line_range = node.byte_range();
                        line_range.end = line_range.end.min(line_range.start + 180);
                        let line = str::from_utf8(&source[line_range]).ok()?.lines().next()?;
                        Some(Tag {
                            name,
                            line,
                            kind,
                            docs,
                            loc: loc_for_node(node),
                        })
                    };

                    // Only create one tag per node. The tag queue is sorted by node position
                    // to allow for fast lookup.
                    match self.tag_queue.binary_search_by_key(
                        &(tag_node.end_byte(), tag_node.start_byte(), tag_node.id()),
                        |(node, _, _)| (node.end_byte(), node.start_byte(), node.id()),
                    ) {
                        Ok(i) => {
                            let (_, old_idx, tag) = &mut self.tag_queue[i];
                            if *old_idx > mat.pattern_index {
                                if let Some(new_tag) = tag_from_node(tag_node, tag_kind) {
                                    *tag = new_tag;
                                    *old_idx = mat.pattern_index;
                                }
                            }
                        }
                        Err(i) => {
                            if let Some(tag) = tag_from_node(tag_node, tag_kind) {
                                self.tag_queue.insert(i, (tag_node, mat.pattern_index, tag))
                            }
                        }
                    }
                }
            }
            // If there are no more matches, then drain the queue.
            else if !self.tag_queue.is_empty() {
                return Some(self.tag_queue.remove(0).2);
            } else {
                return None;
            }
        }
    }
}

impl Serialize for TagKind {
    fn serialize<S>(&self, s: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        match self {
            TagKind::Call => "Call",
            TagKind::Module => "Module",
            TagKind::Class => "Class",
            TagKind::Method => "Method",
            TagKind::Function => "Function",
        }
        .serialize(s)
    }
}

fn loc_for_node(node: Node) -> Loc {
    Loc {
        byte_range: node.byte_range(),
        span: node.start_position().into()..node.start_position().into(),
    }
}

impl From<tree_sitter::Point> for Pos {
    fn from(point: tree_sitter::Point) -> Self {
        return Pos {
            line: point.row as i64,
            column: point.column as i64,
        };
    }
}

impl From<regex::Error> for Error {
    fn from(error: regex::Error) -> Self {
        Error::Regex(error)
    }
}

impl From<QueryError> for Error {
    fn from(error: QueryError) -> Self {
        Error::Query(error)
    }
}
