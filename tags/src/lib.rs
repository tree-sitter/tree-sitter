use serde::{Serialize, Serializer};
use tree_sitter::{Language, Parser, Query, QueryCursor, QueryError};

/// Contains the data neeeded to compute tags for code written in a
/// particular language.
pub struct TagsConfiguration {
    pub language: Language,
    pub query: Query,
    locals_pattern_index: usize,
}

pub struct TagsContext {
    parser: Parser,
    cursor: QueryCursor,
}

#[derive(Debug, Serialize)]
pub struct Range {
    pub start: i64,
    pub end: i64,
}

#[derive(Debug, Serialize)]
pub struct Loc {
    pub byte_range: Range,
    pub span: Span,
}

#[derive(Debug, Serialize)]
pub struct Span {
    pub start: Pos,
    pub end: Pos,
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

        Ok(TagsConfiguration {
            language,
            query,
            locals_pattern_index,
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

    pub fn generate_tags(&mut self, config: &TagsConfiguration, source: &[u8]) -> Vec<Tag> {
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
            .map(|mat| {
                for capture in mat.captures {}
                unimplemented!();
            })
            .collect()
    }
}
