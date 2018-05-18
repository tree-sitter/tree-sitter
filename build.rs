extern crate cc;

use std::env;
use std::path::Path;

fn main() {
    let root_path = Path::new("vendor/tree-sitter");

    let mut config = cc::Build::new();
    config.flag_if_supported("-std=c99");
    config.flag_if_supported("-Wno-unused-parameter");
    config.include(root_path.join(Path::new("src")));
    config.include(root_path.join(Path::new("include")));
    config.include(root_path.join(Path::new("externals/utf8proc")));

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
        config.flag_if_supported("-Wno-typedef-redefinition");
        config.file(parser_dir.join("parser.c"));
        config.file(parser_dir.join("scanner.c"));
    }

    config.compile("treesitter")
}
