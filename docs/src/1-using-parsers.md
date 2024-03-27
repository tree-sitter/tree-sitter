# Using Parsers

All of Tree-sitter's parsing functionality is exposed through C APIs. Applications written in higher-level languages can use Tree-sitter via binding libraries like [node-tree-sitter](https://github.com/tree-sitter/node-tree-sitter) or the [tree-sitter rust crate](https://github.com/tree-sitter/tree-sitter/tree/master/lib/binding_rust), which have their own documentation.

This document will describe the general concepts of how to use Tree-sitter, which should be relevant regardless of what language you're using. It also goes into some C-specific details that are useful if you're using the C API directly or are building a new binding to a different language.

All of the API functions shown here are declared and documented in the [`tree_sitter/api.h`](https://github.com/tree-sitter/tree-sitter/blob/master/lib/include/tree_sitter/api.h) header file. You may also want to browse the [online Rust API docs](https://docs.rs/tree-sitter), which correspond to the C APIs closely.
