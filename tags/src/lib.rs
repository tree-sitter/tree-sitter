use regex::Regex;
use serde::{Serialize, Serializer};
use std::collections::{hash_map, HashMap};
use std::{ops, str};
use tree_sitter::{Language, Node, Parser, Query, QueryCursor, QueryError};

/// Contains the data neeeded to compute tags for code written in a
/// particular language.
pub struct TagsConfiguration {
    pub language: Language,
    pub query: Query,
    call_capture_index: Option<u32>,
    class_capture_index: Option<u32>,
    doc_capture_index: Option<u32>,
    function_capture_index: Option<u32>,
    locals_pattern_index: usize,
    module_capture_index: Option<u32>,
    name_capture_index: Option<u32>,
    doc_strip_regexes: Vec<Option<Regex>>,
}

pub struct TagsContext {
    parser: Parser,
    cursor: QueryCursor,
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
    pub loc: Loc,
    pub name: &'a str,
    pub line: &'a str,
    pub docs: Option<String>,
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
        let mut module_capture_index = None;
        let mut name_capture_index = None;
        for (i, name) in query.capture_names().iter().enumerate() {
            let index = match name.as_str() {
                "call" => &mut call_capture_index,
                "class" => &mut class_capture_index,
                "doc" => &mut doc_capture_index,
                "function" => &mut function_capture_index,
                "module" => &mut module_capture_index,
                "name" => &mut name_capture_index,
                _ => continue,
            };
            *index = Some(i as u32);
        }

        let doc_strip_regexes = (0..query.pattern_count())
            .map(|pattern_index| {
                let properties = query.property_settings(pattern_index);
                for property in properties {
                    if property.key.as_ref() == "strip"
                        && property.capture_id.map(|id| id as u32) == doc_capture_index
                    {
                        if let Some(value) = &property.value {
                            let regex = Regex::new(value.as_ref())?;
                            return Ok(Some(regex));
                        }
                    }
                }
                return Ok(None);
            })
            .collect::<Result<Vec<_>, Error>>()?;

        Ok(TagsConfiguration {
            language,
            query,
            locals_pattern_index,
            function_capture_index,
            class_capture_index,
            module_capture_index,
            doc_capture_index,
            call_capture_index,
            name_capture_index,
            doc_strip_regexes,
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
        &mut self,
        config: &TagsConfiguration,
        source: &'a [u8],
    ) -> Vec<Tag<'a>> {
        self.parser
            .set_language(config.language)
            .expect("Incompatible language");
        let tree = self
            .parser
            .parse(source, None)
            .expect("Parsing failed unexpectedly");
        let matches = self
            .cursor
            .matches(&config.query, tree.root_node(), |node| {
                &source[node.byte_range()]
            });
        let mut neighbor_map: HashMap<tree_sitter::Node, (Tag<'a>, usize)> = HashMap::new();

        for mat in matches {
            let mut call_node = None;
            let mut doc_node = None;
            let mut class_node = None;
            let mut function_node = None;
            let mut module_node = None;
            let mut name_node = None;

            for capture in mat.captures {
                let index = Some(capture.index);
                let node = Some(capture.node);
                if index == config.call_capture_index {
                    call_node = node;
                } else if index == config.class_capture_index {
                    class_node = node;
                } else if index == config.doc_capture_index {
                    doc_node = node;
                } else if index == config.function_capture_index {
                    function_node = node;
                } else if index == config.module_capture_index {
                    module_node = node;
                } else if index == config.name_capture_index {
                    name_node = node;
                }
            }

            let tag_from_node = |node: Node, kind: TagKind| -> Option<Tag> {
                let name = str::from_utf8(&source[name_node?.byte_range()]).ok()?;
                let docs = doc_node
                    .and_then(|n| str::from_utf8(&source[n.byte_range()]).ok())
                    .map(|s| {
                        if let Some(regex) = &config.doc_strip_regexes[mat.pattern_index] {
                            regex.replace_all(s, "").to_string()
                        } else {
                            s.to_string()
                        }
                    });
                Some(Tag {
                    name,
                    line: "TODO",
                    loc: loc_for_node(node),
                    kind: kind,
                    docs,
                })
            };

            for (tag_node, tag_kind) in [
                (call_node, TagKind::Call),
                (class_node, TagKind::Class),
                (function_node, TagKind::Function),
                (module_node, TagKind::Module),
            ]
            .iter()
            .cloned()
            {
                if let Some(found) = tag_node {
                    match neighbor_map.entry(found) {
                        hash_map::Entry::Occupied(mut entry) => {
                            let (tag, old_idx) = entry.get_mut();
                            if *old_idx > mat.pattern_index {
                                if let Some(new_tag) = tag_from_node(found, tag_kind) {
                                    *tag = new_tag;
                                    *old_idx = mat.pattern_index;
                                }
                            }
                        }
                        hash_map::Entry::Vacant(entry) => {
                            if let Some(tag) = tag_from_node(found, tag_kind) {
                                entry.insert((tag, mat.pattern_index));
                            }
                        }
                    }
                }
            }
        }

        return neighbor_map.into_iter().map(|t| (t.1).0).collect();
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
