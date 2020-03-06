use serde::{Serialize, Serializer};
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

#[derive(Debug, Serialize)]
pub struct Loc {
    pub byte_range: ops::Range<usize>,
    pub span: ops::Range<Pos>,
}

#[derive(Debug, Serialize)]
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

#[derive(Debug, Serialize)]
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
        matches
            .filter_map(|mat| {
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

                if let (Some(function), Some(name)) = (function_node, name_node) {
                    if let Ok(name) = str::from_utf8(&source[name.byte_range()]) {
                        return Some(Tag {
                            name,
                            line: "",
                            loc: loc_for_node(function),
                            kind: TagKind::Function,
                            docs: doc_node
                                .and_then(|n| str::from_utf8(&source[n.byte_range()]).ok()),
                        });
                    }
                }

                None
            })
            .collect()
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
        span: node.start_position()..node.start_position(),
    }
}
