//! This crate provides PARSER_NAME language support for the [tree-sitter][] parsing library.
//!
//! Typically, you will use the [library][library func] function to access the language library
//! and make from it the [Language] instance with the [Language::new][new func] method
//! to add this language to a tree-sitter [Parser][], and then use the parser to parse some code:
//!
//! ```
//! let code = "";
//! let mut parser = tree_sitter::Parser::new();
//! let language = tree_sitter::Language::new(tree_sitter_PARSER_NAME::library()).expect("Error loading language library");
//! parser.set_language(language).expect("Error loading PARSER_NAME grammar");
//! let tree = parser.parse(code, None).unwrap();
//! ```
//!
//! [Language]: https://docs.rs/tree-sitter/*/tree_sitter/struct.Language.html
//! [new func]: https://docs.rs/tree-sitter/*/tree_sitter/struct.Language.html#method.new
//! [library func]: fn.library.html
//! [Parser]: https://docs.rs/tree-sitter/*/tree_sitter/struct.Parser.html
//! [tree-sitter]: https://tree-sitter.github.io/

extern "C" {
    fn tree_sitter_PARSER_NAME() -> *const ();
}

/// Get a pointer to the tree-sitter [Language][] library for this grammar.
/// The library needs to be loaded with the `Language::new` method.
///
/// [Language]: https://docs.rs/tree-sitter/*/tree_sitter/struct.Language.html
pub fn library() -> *const () {
    unsafe { tree_sitter_PARSER_NAME() }
}

/// The content of the [`node-types.json`][] file for this grammar.
///
/// [`node-types.json`]: https://tree-sitter.github.io/tree-sitter/using-parsers#static-node-types
pub const NODE_TYPES: &'static str = include_str!("../../src/node-types.json");

// Uncomment these to include any queries that this grammar contains

// pub const HIGHLIGHTS_QUERY: &'static str = include_str!("../../queries/highlights.scm");
// pub const INJECTIONS_QUERY: &'static str = include_str!("../../queries/injections.scm");
// pub const LOCALS_QUERY: &'static str = include_str!("../../queries/locals.scm");
// pub const TAGS_QUERY: &'static str = include_str!("../../queries/tags.scm");

#[cfg(test)]
mod tests {
    #[test]
    fn test_can_load_grammar() {
        let mut parser = tree_sitter::Parser::new();
        let language = tree_sitter::Language::new(super::library()).unwrap();
        parser
            .set_language(language)
            .expect("Error loading PARSER_NAME language");
    }
}
