extern crate cc;

use std::env;
use std::path::PathBuf;

fn main() {
    let mut config = cc::Build::new();
    let root_path: PathBuf = ["vendor", "tree-sitter"].iter().collect();

    config
        .define("UTF8PROC_STATIC", "")
        .flag_if_supported("-std=c99")
        .flag_if_supported("-Wno-unused-parameter")
        .include(root_path.join("src"))
        .include(root_path.join("include"))
        .include(root_path.join("externals").join("utf8proc"));

    let source_filenames = [
      "get_changed_ranges.c",
      "language.c",
      "lexer.c",
      "node.c",
      "parser.c",
      "stack.c",
      "string_input.c",
      "subtree.c",
      "tree_cursor.c",
      "tree.c",
      "utf16.c",
    ];

    config.files(source_filenames.iter().map(|source_filename| {
        root_path
            .join("src")
            .join("runtime")
            .join(&source_filename)
    }));

    config.file(root_path.join("externals").join("utf8proc").join("utf8proc.c"));

    if env::var("RUST_TREE_SITTER_TEST").is_ok() {
        let parser_dir: PathBuf = ["fixtures", "tree-sitter-rust", "src"].iter().collect();
        config
            .file(parser_dir.join("parser.c"))
            .file(parser_dir.join("scanner.c"));
    }

    config.compile("tree-sitter-runtime");
}
