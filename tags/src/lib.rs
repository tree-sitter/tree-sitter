pub mod c_lib;
pub use c_lib as c;

use memchr::memchr;
use regex::Regex;
use std::collections::HashMap;
use std::ffi::{CStr, CString};
use std::ops::Range;
use std::os::raw::c_char;
use std::sync::{
    atomic::{AtomicUsize, Ordering},
    Arc,
};
use std::{char, fmt, mem, str};
use tree_sitter::{
    Language, LossyUtf8, Parser, Point, Query, QueryCursor, QueryError, QueryPredicateArg, Tree,
};

const MAX_LINE_LEN: usize = 180;
const CANCELLATION_CHECK_INTERVAL: usize = 100;

/// Contains the data neeeded to compute tags for code written in a
/// particular language.
#[derive(Debug)]
pub struct TagsConfiguration {
    pub language: Language,
    pub query: Query,
    syntax_type_names: Vec<Box<[u8]>>,
    c_syntax_type_names: Vec<*const u8>,
    capture_map: HashMap<u32, NamedCapture>,
    doc_capture_index: Option<u32>,
    name_capture_index: Option<u32>,
    ignore_capture_index: Option<u32>,
    local_scope_capture_index: Option<u32>,
    local_definition_capture_index: Option<u32>,
    tags_pattern_index: usize,
    pattern_info: Vec<PatternInfo>,
}

#[derive(Debug)]
pub struct NamedCapture {
    pub syntax_type_id: u32,
    pub is_definition: bool,
}

pub struct TagsContext {
    parser: Parser,
    cursor: QueryCursor,
}

#[derive(Debug, Clone)]
pub struct Tag {
    pub range: Range<usize>,
    pub name_range: Range<usize>,
    pub line_range: Range<usize>,
    pub span: Range<Point>,
    pub utf16_column_range: Range<usize>,
    pub docs: Option<String>,
    pub is_definition: bool,
    pub syntax_type_id: u32,
}

#[derive(Debug, PartialEq)]
pub enum Error {
    Query(QueryError),
    Regex(regex::Error),
    Cancelled,
    InvalidLanguage,
    InvalidCapture(String),
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
    prev_line_info: Option<LineInfo>,
    config: &'a TagsConfiguration,
    cancellation_flag: Option<CancellationVariant<'a>>,
    iter_count: usize,
    tag_queue: Vec<(Tag, usize)>,
    scopes: Vec<LocalScope<'a>>,
}

struct LineInfo {
    utf8_position: Point,
    utf8_byte: usize,
    utf16_column: usize,
    line_range: Range<usize>,
}

// This enum needed to move flag ownership into HighlighIter struct instances
// and to avoid an issue in Highlighter::highlight() that a local reference to
// Arc<AtomicUsize> can't leave long enough to be used inside of HighlighIter::next()
enum CancellationVariant<'c> {
    Value(Arc<AtomicUsize>),
    Borrow(&'c AtomicUsize),
}

impl<'c> CancellationVariant<'c> {
    fn check(&self) -> Option<Error> {
        let flag = match self {
            CancellationVariant::Borrow(f) => f.load(Ordering::Relaxed),
            CancellationVariant::Value(f) => f.as_ref().load(Ordering::Relaxed),
        };
        if flag != 0 {
            return Some(Error::Cancelled);
        }
        None
    }
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

        let mut capture_map = HashMap::new();
        let mut syntax_type_names = Vec::new();
        let mut doc_capture_index = None;
        let mut name_capture_index = None;
        let mut ignore_capture_index = None;
        let mut local_scope_capture_index = None;
        let mut local_definition_capture_index = None;
        for (i, name) in query.capture_names().iter().enumerate() {
            match name.as_str() {
                "" => continue,
                "name" => name_capture_index = Some(i as u32),
                "ignore" => ignore_capture_index = Some(i as u32),
                "doc" => doc_capture_index = Some(i as u32),
                "local.scope" => local_scope_capture_index = Some(i as u32),
                "local.definition" => local_definition_capture_index = Some(i as u32),
                "local.reference" => continue,
                _ => {
                    let mut is_definition = false;

                    let kind = if name.starts_with("definition.") {
                        is_definition = true;
                        name.trim_start_matches("definition.")
                    } else if name.starts_with("reference.") {
                        name.trim_start_matches("reference.")
                    } else {
                        return Err(Error::InvalidCapture(name.to_string()));
                    };

                    if let Ok(cstr) = CString::new(kind) {
                        let c_kind = cstr.to_bytes_with_nul().to_vec().into_boxed_slice();
                        let syntax_type_id = syntax_type_names
                            .iter()
                            .position(|n| n == &c_kind)
                            .unwrap_or_else(|| {
                                syntax_type_names.push(c_kind);
                                syntax_type_names.len() - 1
                            }) as u32;
                        capture_map.insert(
                            i as u32,
                            NamedCapture {
                                syntax_type_id,
                                is_definition,
                            },
                        );
                    }
                }
            }
        }

        let c_syntax_type_names = syntax_type_names.iter().map(|s| s.as_ptr()).collect();

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
            syntax_type_names,
            c_syntax_type_names,
            capture_map,
            doc_capture_index,
            name_capture_index,
            ignore_capture_index,
            tags_pattern_index,
            local_scope_capture_index,
            local_definition_capture_index,
            pattern_info,
        })
    }

    pub fn syntax_type_name(&self, id: u32) -> &str {
        unsafe {
            let cstr =
                CStr::from_ptr(self.syntax_type_names[id as usize].as_ptr() as *const c_char)
                    .to_bytes();
            str::from_utf8(cstr).expect("syntax type name was not valid utf-8")
        }
    }
}

impl<'a> TagsContext {
    pub fn new() -> Self {
        TagsContext {
            parser: Parser::new(),
            cursor: QueryCursor::new(),
        }
    }

    pub fn parser(&mut self) -> &mut Parser {
        &mut self.parser
    }

    pub fn generate_tags(
        &'a mut self,
        config: &'a TagsConfiguration,
        source: &'a [u8],
        cancellation_flag: Option<Arc<AtomicUsize>>,
    ) -> Result<(impl Iterator<Item = Result<Tag, Error>> + 'a, bool), Error> {
        self.parser.reset();
        self.parser
            .set_cancellation_flag(cancellation_flag.clone());
        self.do_generate_tags(
            config,
            source,
            cancellation_flag.and_then(|f| Some(CancellationVariant::Value(f))),
        )
    }

    pub unsafe fn generate_tags_unchecked(
        &'a mut self,
        config: &'a TagsConfiguration,
        source: &'a [u8],
        cancellation_flag: Option<&'a AtomicUsize>,
    ) -> Result<(impl Iterator<Item = Result<Tag, Error>> + 'a, bool), Error> {
        self.parser.reset();
        self.parser
            .set_cancellation_flag_unchecked(cancellation_flag);
        self.do_generate_tags(
            config,
            source,
            cancellation_flag.and_then(|f| Some(CancellationVariant::Borrow(f))),
        )
    }

    fn do_generate_tags(
        &'a mut self,
        config: &'a TagsConfiguration,
        source: &'a [u8],
        cancellation_flag: Option<CancellationVariant<'a>>,
    ) -> Result<(impl Iterator<Item = Result<Tag, Error>> + 'a, bool), Error> {
        self.parser
            .set_language(config.language)
            .map_err(|_| Error::InvalidLanguage)?;
        let tree = self.parser.parse(source, None).ok_or(Error::Cancelled)?;

        // The `matches` iterator borrows the `Tree`, which prevents it from being moved.
        // But the tree is really just a pointer, so it's actually ok to move it.
        let tree_ref = unsafe { mem::transmute::<_, &'static Tree>(&tree) };
        let matches = self
            .cursor
            .matches(&config.query, tree_ref.root_node(), move |node| {
                &source[node.byte_range()]
            });
        Ok((
            TagsIter {
                _tree: tree,
                matches,
                source,
                config,
                cancellation_flag,
                prev_line_info: None,
                tag_queue: Vec::new(),
                iter_count: 0,
                scopes: vec![LocalScope {
                    range: 0..source.len(),
                    inherits: false,
                    local_defs: Vec::new(),
                }],
            },
            tree_ref.root_node().has_error(),
        ))
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
            if let Some(ref cancellation_flag) = self.cancellation_flag {
                self.iter_count += 1;
                if self.iter_count >= CANCELLATION_CHECK_INTERVAL {
                    self.iter_count = 0;
                    if let Some(e) = cancellation_flag.check() {
                        return Some(Err(e));
                    }
                }
            }

            // If there is a queued tag for an earlier node in the syntax tree, then pop
            // it off of the queue and return it.
            if let Some(last_entry) = self.tag_queue.last() {
                if self.tag_queue.len() > 1
                    && self.tag_queue[0].0.name_range.end < last_entry.0.name_range.start
                {
                    let tag = self.tag_queue.remove(0).0;
                    if tag.is_ignored() {
                        continue;
                    } else {
                        return Some(Ok(tag));
                    }
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
                let mut syntax_type_id = 0;
                let mut is_definition = false;
                let mut docs_adjacent_node = None;
                let mut is_ignored = false;

                for capture in mat.captures {
                    let index = Some(capture.index);

                    if index == self.config.ignore_capture_index {
                        is_ignored = true;
                        name_node = Some(capture.node);
                    }

                    if index == self.config.pattern_info[mat.pattern_index].docs_adjacent_capture {
                        docs_adjacent_node = Some(capture.node);
                    }

                    if index == self.config.name_capture_index {
                        name_node = Some(capture.node);
                    } else if index == self.config.doc_capture_index {
                        doc_nodes.push(capture.node);
                    }

                    if let Some(named_capture) = self.config.capture_map.get(&capture.index) {
                        tag_node = Some(capture.node);
                        syntax_type_id = named_capture.syntax_type_id;
                        is_definition = named_capture.is_definition;
                    }
                }

                if let Some(name_node) = name_node {
                    let name_range = name_node.byte_range();

                    let tag;
                    if let Some(tag_node) = tag_node {
                        if name_node.has_error() {
                            continue;
                        }

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
                            if let Ok(content) = str::from_utf8(&self.source[doc_node.byte_range()])
                            {
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

                        let rng = tag_node.byte_range();
                        let range = rng.start.min(name_range.start)..rng.end.max(name_range.end);
                        let span = name_node.start_position()..name_node.end_position();

                        // Compute tag properties that depend on the text of the containing line. If the
                        // previous tag occurred on the same line, then reuse results from the previous tag.
                        let line_range;
                        let mut prev_utf16_column = 0;
                        let mut prev_utf8_byte = name_range.start - span.start.column;
                        let line_info = self.prev_line_info.as_ref().and_then(|info| {
                            if info.utf8_position.row == span.start.row {
                                Some(info)
                            } else {
                                None
                            }
                        });
                        if let Some(line_info) = line_info {
                            line_range = line_info.line_range.clone();
                            if line_info.utf8_position.column <= span.start.column {
                                prev_utf8_byte = line_info.utf8_byte;
                                prev_utf16_column = line_info.utf16_column;
                            }
                        } else {
                            line_range = self::line_range(
                                self.source,
                                name_range.start,
                                span.start,
                                MAX_LINE_LEN,
                            );
                        }

                        let utf16_start_column = prev_utf16_column
                            + utf16_len(&self.source[prev_utf8_byte..name_range.start]);
                        let utf16_end_column =
                            utf16_start_column + utf16_len(&self.source[name_range.clone()]);
                        let utf16_column_range = utf16_start_column..utf16_end_column;

                        self.prev_line_info = Some(LineInfo {
                            utf8_position: span.end,
                            utf8_byte: name_range.end,
                            utf16_column: utf16_end_column,
                            line_range: line_range.clone(),
                        });
                        tag = Tag {
                            line_range,
                            span,
                            utf16_column_range,
                            range,
                            name_range,
                            docs,
                            is_definition,
                            syntax_type_id,
                        };
                    } else if is_ignored {
                        tag = Tag::ignored(name_range);
                    } else {
                        continue;
                    }

                    // Only create one tag per node. The tag queue is sorted by node position
                    // to allow for fast lookup.
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

impl Tag {
    fn ignored(name_range: Range<usize>) -> Self {
        Tag {
            name_range,
            line_range: 0..0,
            span: Point::new(0, 0)..Point::new(0, 0),
            utf16_column_range: 0..0,
            range: usize::MAX..usize::MAX,
            docs: None,
            is_definition: false,
            syntax_type_id: 0,
        }
    }

    fn is_ignored(&self) -> bool {
        self.range.start == usize::MAX
    }
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Error::InvalidCapture(name) => write!(f, "Invalid capture @{}. Expected one of: @definition.*, @reference.*, @doc, @name, @local.(scope|definition|reference).", name),
            _ => write!(f, "{:?}", self)
        }
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

fn line_range(
    text: &[u8],
    start_byte: usize,
    start_point: Point,
    max_line_len: usize,
) -> Range<usize> {
    // Trim leading whitespace
    let mut line_start_byte = start_byte - start_point.column;
    while line_start_byte < text.len() && text[line_start_byte].is_ascii_whitespace() {
        line_start_byte += 1;
    }

    let max_line_len = max_line_len.min(text.len() - line_start_byte);
    let text_after_line_start = &text[line_start_byte..(line_start_byte + max_line_len)];
    let line_len = if let Some(len) = memchr(b'\n', text_after_line_start) {
        len
    } else if let Err(e) = str::from_utf8(text_after_line_start) {
        e.valid_up_to()
    } else {
        max_line_len
    };

    // Trim trailing whitespace
    let mut line_end_byte = line_start_byte + line_len;
    while line_end_byte > line_start_byte && text[line_end_byte - 1].is_ascii_whitespace() {
        line_end_byte -= 1;
    }

    line_start_byte..line_end_byte
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

    #[test]
    fn test_get_line_trims() {
        let text = b"   foo\nbar\n";
        assert_eq!(line_range(text, 0, Point::new(0, 0), 10), 3..6);

        let text = b"\t func foo \nbar\n";
        assert_eq!(line_range(text, 0, Point::new(0, 0), 10), 2..10);

        let r = line_range(text, 0, Point::new(0, 0), 14);
        assert_eq!(r, 2..10);
        assert_eq!(str::from_utf8(&text[r]).unwrap_or(""), "func foo");

        let r = line_range(text, 12, Point::new(1, 0), 14);
        assert_eq!(r, 12..15);
        assert_eq!(str::from_utf8(&text[r]).unwrap_or(""), "bar");
    }
}
