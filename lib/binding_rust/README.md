Rust Tree-sitter
================

[![Build Status](https://travis-ci.org/tree-sitter/tree-sitter.svg?branch=master)](https://travis-ci.org/tree-sitter/tree-sitter)
[![Build status](https://ci.appveyor.com/api/projects/status/vtmbd6i92e97l55w/branch/master?svg=true)](https://ci.appveyor.com/project/maxbrunsfeld/tree-sitter/branch/master)
[![Crates.io](https://img.shields.io/crates/v/tree-sitter.svg)](https://crates.io/crates/tree-sitter)

Rust bindings to the [Tree-sitter][] parsing library.

### Basic Usage

First, create a parser:

```rust
use tree_sitter::{Parser, Language};

// ...

let mut parser = Parser::new();
```

Tree-sitter languages consist of generated C code. To make sure they're properly compiled and linked, you can create a [build script](https://doc.rust-lang.org/cargo/reference/build-scripts.html) like the following (assuming `tree-sitter-javascript` is in your root directory):
```rust
extern crate cc;

use std::path::PathBuf;

fn main() {
    let dir: PathBuf = ["tree-sitter-javascript", "src"].iter().collect();

    cc::Build::new()
        .include(&dir)
        .file(dir.join("parser.c"))
        .file(dir.join("scanner.c"))
        .compile("tree-sitter-javascript");
}
```

To then use languages from rust, you must declare them as `extern "C"` functions and invoke them with `unsafe`. Then you can assign them to the parser. 

```rust
extern "C" { fn tree_sitter_c() -> Language; }
extern "C" { fn tree_sitter_rust() -> Language; }
extern "C" { fn tree_sitter_javascript() -> Language; }

let language = unsafe { tree_sitter_rust() };
parser.set_language(language).unwrap();
```

Now you can parse source code:

```rust
let source_code = "fn test() {}";
let tree = parser.parse(source_code, None).unwrap();
let root_node = tree.root_node();

assert_eq!(root_node.kind(), "source_file");
assert_eq!(root_node.start_position().column, 0);
assert_eq!(root_node.end_position().column, 12);
```

### Editing

Once you have a syntax tree, you can update it when your source code changes. Passing in the previous edited tree makes `parse` run much more quickly:

```rust
let new_source_code = "fn test(a: u32) {}"

tree.edit(InputEdit {
  start_byte: 8,
  old_end_byte: 8,
  new_end_byte: 14,
  start_position: Point::new(0, 8),
  old_end_position: Point::new(0, 8),
  new_end_position: Point::new(0, 14),
});

let new_tree = parser.parse(new_source_code, Some(&tree));
```

### Text Input

The source code to parse can be provided either either as a string, a slice, a vector, or as a function that returns a slice. The text can be encoded as either UTF8 or UTF16:

```rust
// Store some source code in an array of lines.
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
```

[tree-sitter]: https://github.com/tree-sitter/tree-sitter
