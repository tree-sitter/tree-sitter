//! This crate provides TITLE_PARSER_NAME language support for the [tree-sitter] parsing library.
//!
//! Typically, you will use the [`LANGUAGE`] constant to add this language to a
//! tree-sitter [`Parser`], and then use the parser to parse some code:
//!
//! ```
//! let code = r#"
//! "#;
//! let mut parser = tree_sitter::Parser::new();
//! let language = tree_sitter_PARSER_NAME::LANGUAGE;
//! parser
//!     .set_language(&language.into())
//!     .expect("Error loading TITLE_PARSER_NAME parser");
//! let tree = parser.parse(code, None).unwrap();
//! assert!(!tree.root_node().has_error());
//! ```
//!
//! [`Parser`]: https://docs.rs/tree-sitter/RUST_BINDING_VERSION/tree_sitter/struct.Parser.html
//! [tree-sitter]: https://tree-sitter.github.io/

use tree_sitter_language::LanguageFn;

extern "C" {
    fn tree_sitter_PARSER_NAME() -> *const ();
}

/// The tree-sitter [`LanguageFn`] for this grammar.
pub const LANGUAGE: LanguageFn = unsafe { LanguageFn::from_raw(tree_sitter_PARSER_NAME) };

/// The content of the [`node-types.json`] file for this grammar.
///
/// [`node-types.json`]: https://tree-sitter.github.io/tree-sitter/using-parsers/6-static-node-types
pub const NODE_TYPES: &str = include_str!("../../src/node-types.json");

#[cfg(with_highlights_query)]
/// The syntax highlighting query for this grammar.
pub const HIGHLIGHTS_QUERY: &str = include_str!("../../HIGHLIGHTS_QUERY_PATH");

#[cfg(with_injections_query)]
/// The language injection query for this grammar.
pub const INJECTIONS_QUERY: &str = include_str!("../../INJECTIONS_QUERY_PATH");

#[cfg(with_locals_query)]
/// The local variable query for this grammar.
pub const LOCALS_QUERY: &str = include_str!("../../LOCALS_QUERY_PATH");

#[cfg(with_tags_query)]
/// The symbol tagging query for this grammar.
pub const TAGS_QUERY: &str = include_str!("../../TAGS_QUERY_PATH");

#[cfg(test)]
mod tests {
    #[test]
    fn test_can_load_grammar() {
        let mut parser = tree_sitter::Parser::new();
        parser
            .set_language(&super::LANGUAGE.into())
            .expect("Error loading TITLE_PARSER_NAME parser");
    }
}
