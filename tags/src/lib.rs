pub mod c_lib;

use memchr::memchr;
use regex::Regex;
use std::ops::Range;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::{char, fmt, mem, str};
use tree_sitter::{
    Language, Parser, Point, Query, QueryCursor, QueryError, QueryPredicateArg, Tree,
};

const MAX_LINE_LEN: usize = 180;
const CANCELLATION_CHECK_INTERVAL: usize = 100;

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
    local_scope_capture_index: Option<u32>,
    local_definition_capture_index: Option<u32>,
    tags_pattern_index: usize,
    pattern_info: Vec<PatternInfo>,
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
    pub utf16_column_range: Range<usize>,
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

#[derive(Debug, PartialEq)]
pub enum Error {
    Query(QueryError),
    Regex(regex::Error),
    Cancelled,
    InvalidLanguage,
}

#[derive(Debug, Default)]
struct PatternInfo {
    docs_adjacent_capture: Option<u32>,
    local_scope_inherits: bool,
    name_must_be_non_local: bool,
    doc_strip_regex: Option<Regex>,
}

#[derive(Debug)]
struct LocalDef<'a> {
    name: &'a [u8],
    value_range: Range<usize>,
}

#[derive(Debug)]
struct LocalScope<'a> {
    inherits: bool,
    range: Range<usize>,
    local_defs: Vec<LocalDef<'a>>,
}

struct TagsIter<'a, I>
where
    I: Iterator<Item = tree_sitter::QueryMatch<'a>>,
{
    matches: I,
    _tree: Tree,
    source: &'a [u8],
    config: &'a TagsConfiguration,
    cancellation_flag: Option<&'a AtomicUsize>,
    iter_count: usize,
    tag_queue: Vec<(Tag, usize)>,
    scopes: Vec<LocalScope<'a>>,
}

impl TagsConfiguration {
    pub fn new(language: Language, tags_query: &str, locals_query: &str) -> Result<Self, Error> {
        let query = Query::new(language, &format!("{}{}", locals_query, tags_query))?;

        let tags_query_offset = locals_query.len();
        let mut tags_pattern_index = 0;
        for i in 0..(query.pattern_count()) {
            let pattern_offset = query.start_byte_for_pattern(i);
            if pattern_offset < tags_query_offset {
                tags_pattern_index += 1;
            }
        }

        let mut call_capture_index = None;
        let mut class_capture_index = None;
        let mut doc_capture_index = None;
        let mut function_capture_index = None;
        let mut method_capture_index = None;
        let mut module_capture_index = None;
        let mut name_capture_index = None;
        let mut local_scope_capture_index = None;
        let mut local_definition_capture_index = None;
        for (i, name) in query.capture_names().iter().enumerate() {
            let index = match name.as_str() {
                "call" => &mut call_capture_index,
                "class" => &mut class_capture_index,
                "doc" => &mut doc_capture_index,
                "function" => &mut function_capture_index,
                "method" => &mut method_capture_index,
                "module" => &mut module_capture_index,
                "name" => &mut name_capture_index,
                "local.scope" => &mut local_scope_capture_index,
                "local.definition" => &mut local_definition_capture_index,
                _ => continue,
            };
            *index = Some(i as u32);
        }

        let pattern_info = (0..query.pattern_count())
            .map(|pattern_index| {
                let mut info = PatternInfo::default();
                for (property, is_positive) in query.property_predicates(pattern_index) {
                    if !is_positive && property.key.as_ref() == "local" {
                        info.name_must_be_non_local = true;
                    }
                }
                info.local_scope_inherits = true;
                for property in query.property_settings(pattern_index) {
                    if property.key.as_ref() == "local.scope-inherits"
                        && property
                            .value
                            .as_ref()
                            .map_or(false, |v| v.as_ref() == "false")
                    {
                        info.local_scope_inherits = false;
                    }
                }
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
            tags_pattern_index,
            local_scope_capture_index,
            local_definition_capture_index,
            pattern_info,
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
        cancellation_flag: Option<&'a AtomicUsize>,
    ) -> Result<impl Iterator<Item = Result<Tag, Error>> + 'a, Error> {
        self.parser
            .set_language(config.language)
            .map_err(|_| Error::InvalidLanguage)?;
        self.parser.reset();
        unsafe { self.parser.set_cancellation_flag(cancellation_flag) };
        let tree = self.parser.parse(source, None).ok_or(Error::Cancelled)?;

        // The `matches` iterator borrows the `Tree`, which prevents it from being moved.
        // But the tree is really just a pointer, so it's actually ok to move it.
        let tree_ref = unsafe { mem::transmute::<_, &'static Tree>(&tree) };
        let matches = self
            .cursor
            .matches(&config.query, tree_ref.root_node(), move |node| {
                &source[node.byte_range()]
            });
        Ok(TagsIter {
            _tree: tree,
            matches,
            source,
            config,
            cancellation_flag,
            tag_queue: Vec::new(),
            iter_count: 0,
            scopes: vec![LocalScope {
                range: 0..source.len(),
                inherits: false,
                local_defs: Vec::new(),
            }],
        })
    }
}

impl<'a, I> Iterator for TagsIter<'a, I>
where
    I: Iterator<Item = tree_sitter::QueryMatch<'a>>,
{
    type Item = Result<Tag, Error>;

    fn next(&mut self) -> Option<Self::Item> {
        loop {
            // Periodically check for cancellation, returning `Cancelled` error if the
            // cancellation flag was flipped.
            if let Some(cancellation_flag) = self.cancellation_flag {
                self.iter_count += 1;
                if self.iter_count >= CANCELLATION_CHECK_INTERVAL {
                    self.iter_count = 0;
                    if cancellation_flag.load(Ordering::Relaxed) != 0 {
                        return Some(Err(Error::Cancelled));
                    }
                }
            }

            // If there is a queued tag for an earlier node in the syntax tree, then pop
            // it off of the queue and return it.
            if let Some(last_entry) = self.tag_queue.last() {
                if self.tag_queue.len() > 1
                    && self.tag_queue[0].0.name_range.end < last_entry.0.name_range.start
                {
                    return Some(Ok(self.tag_queue.remove(0).0));
                }
            }

            // If there is another match, then compute its tag and add it to the
            // tag queue.
            if let Some(mat) = self.matches.next() {
                let pattern_info = &self.config.pattern_info[mat.pattern_index];

                if mat.pattern_index < self.config.tags_pattern_index {
                    for capture in mat.captures {
                        let index = Some(capture.index);
                        let range = capture.node.byte_range();
                        if index == self.config.local_scope_capture_index {
                            self.scopes.push(LocalScope {
                                range,
                                inherits: pattern_info.local_scope_inherits,
                                local_defs: Vec::new(),
                            });
                        } else if index == self.config.local_definition_capture_index {
                            if let Some(scope) = self.scopes.iter_mut().rev().find(|scope| {
                                scope.range.start <= range.start && scope.range.end >= range.end
                            }) {
                                scope.local_defs.push(LocalDef {
                                    name: &self.source[range.clone()],
                                    value_range: range,
                                });
                            }
                        }
                    }
                    continue;
                }

                let mut name_node = None;
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
                        name_node = Some(capture.node);
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

                if let (Some(tag_node), Some(name_node)) = (tag_node, name_node) {
                    let name_range = name_node.byte_range();

                    if pattern_info.name_must_be_non_local {
                        let mut is_local = false;
                        for scope in self.scopes.iter().rev() {
                            if scope.range.start <= name_range.start
                                && scope.range.end >= name_range.end
                            {
                                if scope
                                    .local_defs
                                    .iter()
                                    .any(|d| d.name == &self.source[name_range.clone()])
                                {
                                    is_local = true;
                                    break;
                                }
                                if !scope.inherits {
                                    break;
                                }
                            }
                        }
                        if is_local {
                            continue;
                        }
                    }

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
                            let content = if let Some(regex) = &pattern_info.doc_strip_regex {
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
                    let span = name_node.start_position()..name_node.end_position();
                    let utf16_column_range =
                        get_utf16_column_range(self.source, &name_range, &span);
                    let line_range =
                        line_range(self.source, name_range.start, span.start, MAX_LINE_LEN);
                    let tag = Tag {
                        line_range,
                        span,
                        utf16_column_range,
                        kind,
                        range,
                        name_range,
                        docs,
                    };
                    match self.tag_queue.binary_search_by_key(
                        &(tag.name_range.end, tag.name_range.start),
                        |(tag, _)| (tag.name_range.end, tag.name_range.start),
                    ) {
                        Ok(i) => {
                            let (existing_tag, pattern_index) = &mut self.tag_queue[i];
                            if *pattern_index > mat.pattern_index {
                                *pattern_index = mat.pattern_index;
                                *existing_tag = tag;
                            }
                        }
                        Err(i) => self.tag_queue.insert(i, (tag, mat.pattern_index)),
                    }
                }
            }
            // If there are no more matches, then drain the queue.
            else if !self.tag_queue.is_empty() {
                return Some(Ok(self.tag_queue.remove(0).0));
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

pub struct LossyUtf8<'a> {
    bytes: &'a [u8],
    in_replacement: bool,
}

impl<'a> LossyUtf8<'a> {
    pub fn new(bytes: &'a [u8]) -> Self {
        LossyUtf8 {
            bytes,
            in_replacement: false,
        }
    }
}

impl<'a> Iterator for LossyUtf8<'a> {
    type Item = &'a str;

    fn next(&mut self) -> Option<&'a str> {
        if self.bytes.is_empty() {
            return None;
        }
        if self.in_replacement {
            self.in_replacement = false;
            return Some("\u{fffd}");
        }
        match str::from_utf8(self.bytes) {
            Ok(valid) => {
                self.bytes = &[];
                Some(valid)
            }
            Err(error) => {
                if let Some(error_len) = error.error_len() {
                    let error_start = error.valid_up_to();
                    if error_start > 0 {
                        let result =
                            unsafe { str::from_utf8_unchecked(&self.bytes[..error_start]) };
                        self.bytes = &self.bytes[(error_start + error_len)..];
                        self.in_replacement = true;
                        Some(result)
                    } else {
                        self.bytes = &self.bytes[error_len..];
                        Some("\u{fffd}")
                    }
                } else {
                    None
                }
            }
        }
    }
}

fn line_range(
    text: &[u8],
    start_byte: usize,
    start_point: Point,
    max_line_len: usize,
) -> Range<usize> {
    let line_start_byte = start_byte - start_point.column;
    let max_line_len = max_line_len.min(text.len() - line_start_byte);
    let text_after_line_start = &text[line_start_byte..(line_start_byte + max_line_len)];
    let len = if let Some(len) = memchr(b'\n', text_after_line_start) {
        len
    } else {
        match str::from_utf8(text_after_line_start) {
            Ok(s) => s.len(),
            Err(e) => e.valid_up_to(),
        }
    };
    line_start_byte..(line_start_byte + len)
}

fn get_utf16_column_range(
    text: &[u8],
    byte_range: &Range<usize>,
    point_range: &Range<Point>,
) -> Range<usize> {
    let start = byte_range.start - point_range.start.column;
    let preceding_text_on_line = &text[start..byte_range.start];
    let start_col = utf16_len(preceding_text_on_line);
    start_col..(start_col + utf16_len(&text[byte_range.clone()]))
}

fn utf16_len(bytes: &[u8]) -> usize {
    LossyUtf8::new(bytes)
        .flat_map(|chunk| chunk.chars().map(char::len_utf16))
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_line() {
        let text = "abc\ndefg❤hij\nklmno".as_bytes();
        assert_eq!(line_range(text, 5, Point::new(1, 1), 30), 4..14);
        assert_eq!(line_range(text, 5, Point::new(1, 1), 6), 4..8);
        assert_eq!(line_range(text, 17, Point::new(2, 2), 30), 15..20);
        assert_eq!(line_range(text, 17, Point::new(2, 2), 4), 15..19);
    }
}
