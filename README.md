# tree-sitter

[![CICD badge]][CICD]
[![DOI](https://zenodo.org/badge/14164618.svg)](https://zenodo.org/badge/latestdoi/14164618)

[CICD badge]: https://github.com/tree-sitter/tree-sitter/actions/workflows/CICD.yml/badge.svg
[CICD]: https://github.com/tree-sitter/tree-sitter/actions/workflows/CICD.yml

Tree-sitter is a parser generator tool and an incremental parsing library. It can build a concrete syntax tree for a source file and efficiently update the syntax tree as the source file is edited. Tree-sitter aims to be:

- **General** enough to parse any programming language
- **Fast** enough to parse on every keystroke in a text editor
- **Robust** enough to provide useful results even in the presence of syntax errors
- **Dependency-free** so that the runtime library (which is written in pure C) can be embedded in any application

## Links

- [Documentation](https://tree-sitter.github.io)
- [Rust binding](lib/binding_rust/README.md)
- [WASM binding](lib/binding_web/README.md)
- [Command-line interface](cli/README.md)// Store some source code in an array of lines.
let lines = &[
    "pub fn foo() {",
    "  1",
    "}",
];

// Parse the source code using a custom callback. The callback is called
// with both a byte offset and a row/column offset.
let tree = parser.parse_with(&mut |_byte: u32, position: Point| -> &[u8] {
    let row = position.row as usize;
    let column = position.column as usize;
    if row < lines.len() {
        if column < lines[row].as_bytes().len() {
            &lines[row].as_bytes()[column..]
        } else {
            "\n".as_bytes()
        }
    } else {
        &[]
    }
}, None).unwrap();

assert_eq!(
  tree.root_node().to_sexp(),
  "(source_file (function_item (visibility_modifier) (identifier) (parameters) (block (number_literal))))"
);
