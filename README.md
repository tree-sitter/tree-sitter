Rust Tree-sitter
===========================

[![Build Status](https://travis-ci.org/tree-sitter/rust-tree-sitter.svg)](https://travis-ci.org/tree-sitter/rust-tree-sitter)
[![Build status](https://ci.appveyor.com/api/projects/status/d0f6vqq3rflxx3y6/branch/master?svg=true)](https://ci.appveyor.com/project/maxbrunsfeld/rust-tree-sitter/branch/master)
[![Crates.io](https://img.shields.io/crates/v/tree-sitter.svg)](https://crates.io/crates/tree-sitter)

Rust bindings to the [Tree-sitter][] parsing library.

### Basic Usage

First, create a parser:

```rust
let parser = Parser::new();
```

Then assign a language to the parser. Tree-sitter languages consist of generated C code. To use them from rust, you must declare them as `extern "C"` functions and invoke them with `unsafe`:

```rust
extern "C" fn tree_sitter_c() -> Language;
extern "C" fn tree_sitter_rust() -> Language;
extern "C" fn tree_sitter_javascript() -> Language;

parser.set_language(unsafe { tree_sitter_rust() }).unwrap();
```

Now you can parse source code:

```rust
let source_code = "fn test() {}";

let tree = parser.parse_str(source_code, None);
let root_node = tree.root_node();
assert_eq!(root_node.kind(), "source_file");
assert_eq!(root_node.start_position().column, 0);
assert_eq!(root_node.end_position().column, 12);
```

### Editing

Once you have a syntax tree, you can update it when your source code changes:

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
let new_tree = parser.parse_str(new_source_code, Some(tree));
```

### Text Input


The code can be provided either as a simple string or by any type that implements Tree-sitter's `Utf8Input` or `Utf16Input` traits:

```rust
struct LineWiseInput {
    lines: &'static [&'static str],
    row: usize,
    column: usize,
}

impl tree_sitter::Utf8Input for LineWiseInput {
    fn read(&mut self) -> &[u8] {
        if self.row < self.lines.len() {
            let result = &self.lines[self.row].as_bytes()[self.column..];
            self.row += 1;
            self.column = 0;
            result
        } else {
            &[]
        }
    }

    fn seek(&mut self, _byte: u32, position: Point) {
        self.row = position.row as usize;
        self.column = position.column as usize;
    }
}

let mut input = LineBasedInput {
    lines: &[
        "pub fn main() {",
        "}",
    ],
    row: 0,
    column: 0
};

let tree = parser.parse_utf8(&mut input, None).unwrap();
```

[tree-sitter]: https://github.com/tree-sitter/tree-sitter
