use serde::{Serialize, Serializer};
use std::collections::HashMap;
use std::{ops, str};
use tree_sitter::{Language, Node, Parser, Point, Query, QueryCursor, QueryError};

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
    pub docs: Option<&'a str>,
}

impl TagsConfiguration {
    pub fn new(
        language: Language,
        tags_query: &str,
        locals_query: &str,
    ) -> Result<Self, QueryError> {
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

            let tag_from_node = |node: Node| -> Option<Tag> {
                return None;
            }

            for (optFound, theKind) in [
                (call_node, TagKind::Call),
                (class_node, TagKind::Class),
                (function_node, TagKind::Function),
                (module_node, TagKind::Module),
            ] {
                if let (Some(found), Some(name)) = (optFound, name_node) {
                    match neighbor_map.entry(found) {
                        hash_map::Entry::Occupied(entry) => {
                            let (tag, old_idx) = entry.get_mut();
                            if old_idx > mat.pattern_index {
                                *tag =
                            }
                        }
                    }
            }
            }
        }

        // some computation
        return neighbor_map.into_iter().map(|t| (t.1).0).collect();

        // matches
        //     .filter_map(|mat| {

        //         for capture in mat.captures {
        //
        //

        //         }

        //         let tag_from_node = |kind, name: Node, node| -> Option<Tag> {
        //             if let Ok(name) = str::from_utf8(&source[name.byte_range()]) {
        //                 if let Some((tag, index)) = neighbor_map.get(&node) {
        //                     if index > &mat.pattern_index {
        //                         return Some(tag.clone());
        //                     }
        //                 }

        //                 return Some(Tag {
        //                     name,
        //                     line: "TODO",
        //                     loc: loc_for_node(node),
        //                     kind: kind,
        //                     docs: doc_node
        //                         .and_then(|n| str::from_utf8(&source[n.byte_range()]).ok()),
        //                 });
        //             };
        //             return None;
        //         };

        //         if let (Some(function), Some(name)) = (function_node, name_node) {
        //             return tag_from_node(TagKind::Function, name, function);
        //         } else if let (Some(call), Some(name)) = (call_node, name_node) {
        //             return tag_from_node(TagKind::Call, name, call);
        //         } else if let (Some(class), Some(name)) = (class_node, name_node) {
        //             return tag_from_node(TagKind::Class, name, class);
        //         }

        //         None
        //     })
        //     .collect()
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
