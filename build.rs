extern crate cc;

use std::env;
use std::path::Path;

fn main() {
    let mut config = cc::Build::new();
    let root_path = Path::new("vendor/tree-sitter");

    config
        .flag("-std=c99")
        .flag("-Wno-unused-parameter")
        .static_flag(true)
        .include(root_path.join(Path::new("src")))
        .include(root_path.join(Path::new("include")))
        .include(root_path.join(Path::new("externals/utf8proc")));

    let source_filenames = [
      "get_changed_ranges.c",
      "language.c",
      "lexer.c",
      "node.c",
      "parser.c",
      "stack.c",
      "subtree.c",
      "tree_cursor.c",
      "tree.c",
      "utf16.c",
    ];

    config.files(source_filenames.iter().map(|source_filename| {
        root_path
            .join(Path::new(&"src/runtime"))
            .join(Path::new(&source_filename))
    }));

    config.file(root_path.join(Path::new("externals/utf8proc/utf8proc.c")));

    if env::var("RUST_TREE_SITTER_TEST").is_ok() {
        let parser_dir = Path::new("fixtures/tree-sitter-rust/src");
        config
            .file(parser_dir.join("parser.c"))
            .file(parser_dir.join("scanner.c"));
    }

    config.compile("treesitter_ffi");
}
