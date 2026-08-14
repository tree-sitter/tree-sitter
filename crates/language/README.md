# Tree-sitter Language

This crate provides a `LanguageFn` type for grammars to create `Language` instances from a parser,
without having to worry about the `tree-sitter` crate version not matching.

When targeting `wasm32-unknown-unknown`, this crate also provides the C headers
needed to compile generated parsers and external scanners. The final
`tree-sitter` Rust application supplies the corresponding libc-compatible
implementations.
