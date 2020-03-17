mod c_lib;

use memchr::{memchr, memrchr};
use regex::Regex;
use std::ops::Range;
use std::{fmt, mem, str};
use tree_sitter::{
    Language, Node, Parser, Point, Query, QueryCursor, QueryError, QueryPredicateArg, Tree,
};

const MAX_LINE_LEN: usize = 180;

/// Contains the data neeeded to compute tags for code written in a
/// particular language.
#[derive(Debug)]
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

#[derive(Debug, Clone)]
pub struct Tag {
    pub kind: TagKind,
    pub range: Range<usize>,
    pub name_range: Range<usize>,
    pub line_range: Range<usize>,
    pub span: Range<Point>,
    pub docs: Option<String>,
}

#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum TagKind {
    Function,
    Method,
    Class,
    Module,
    Call,
}

#[derive(Debug)]
pub enum Error {
    Query(QueryError),
    Regex(regex::Error),
}

#[derive(Debug, Default)]
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
    tag_queue: Vec<(Node<'a>, usize, Tag)>,
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

    pub fn generate_tags<'a>(
        &'a mut self,
        config: &'a TagsConfiguration,
        source: &'a [u8],
    ) -> impl Iterator<Item = Tag> + 'a {
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
    type Item = Tag;

    fn next(&mut self) -> Option<Tag> {
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
                let mut name_range = None;
                let mut doc_nodes = Vec::new();
                let mut tag_node = None;
                let mut kind = TagKind::Call;
                let mut docs_adjacent_node = None;

                for capture in mat.captures {
                    let index = Some(capture.index);

                    if index == self.config.pattern_info[mat.pattern_index].docs_adjacent_capture {
                        docs_adjacent_node = Some(capture.node);
                    }

                    if index == self.config.name_capture_index {
                        name_range = Some(capture.node.byte_range());
                    } else if index == self.config.doc_capture_index {
                        doc_nodes.push(capture.node);
                    } else if index == self.config.call_capture_index {
                        tag_node = Some(capture.node);
                        kind = TagKind::Call;
                    } else if index == self.config.class_capture_index {
                        tag_node = Some(capture.node);
                        kind = TagKind::Class;
                    } else if index == self.config.function_capture_index {
                        tag_node = Some(capture.node);
                        kind = TagKind::Function;
                    } else if index == self.config.method_capture_index {
                        tag_node = Some(capture.node);
                        kind = TagKind::Method;
                    } else if index == self.config.module_capture_index {
                        tag_node = Some(capture.node);
                        kind = TagKind::Module;
                    }
                }

                if let (Some(tag_node), Some(name_range)) = (tag_node, name_range) {
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

                    // Only create one tag per node. The tag queue is sorted by node position
                    // to allow for fast lookup.
                    let range = tag_node.byte_range();
                    match self.tag_queue.binary_search_by_key(
                        &(range.end, range.start, tag_node.id()),
                        |(node, _, _)| (node.end_byte(), node.start_byte(), node.id()),
                    ) {
                        Ok(i) => {
                            let (_, pattern_index, tag) = &mut self.tag_queue[i];
                            if *pattern_index > mat.pattern_index {
                                *pattern_index = mat.pattern_index;
                                *tag = Tag {
                                    line_range: line_range(self.source, range.start, MAX_LINE_LEN),
                                    span: tag_node.start_position()..tag_node.start_position(),
                                    kind,
                                    range,
                                    name_range,
                                    docs,
                                };
                            }
                        }
                        Err(i) => self.tag_queue.insert(
                            i,
                            (
                                tag_node,
                                mat.pattern_index,
                                Tag {
                                    line_range: line_range(self.source, range.start, MAX_LINE_LEN),
                                    span: tag_node.start_position()..tag_node.start_position(),
                                    kind,
                                    range,
                                    name_range,
                                    docs,
                                },
                            ),
                        ),
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

impl fmt::Display for TagKind {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            TagKind::Call => "Call",
            TagKind::Module => "Module",
            TagKind::Class => "Class",
            TagKind::Method => "Method",
            TagKind::Function => "Function",
        }
        .fmt(f)
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

fn line_range(text: &[u8], index: usize, max_line_len: usize) -> Range<usize> {
    let start = memrchr(b'\n', &text[0..index]).map_or(0, |i| i + 1);
    let max_line_len = max_line_len.min(text.len() - start);
    let end = start + memchr(b'\n', &text[start..(start + max_line_len)]).unwrap_or(max_line_len);
    start..end
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_line() {
        let text = b"abc\ndefg\nhijkl";
        assert_eq!(line_range(text, 0, 10), 0..3);
        assert_eq!(line_range(text, 1, 10), 0..3);
        assert_eq!(line_range(text, 2, 10), 0..3);
        assert_eq!(line_range(text, 3, 10), 0..3);
        assert_eq!(line_range(text, 1, 2), 0..2);
        assert_eq!(line_range(text, 4, 10), 4..8);
        assert_eq!(line_range(text, 5, 10), 4..8);
        assert_eq!(line_range(text, 11, 10), 9..14);
    }
}
