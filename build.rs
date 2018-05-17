extern crate cc;

use std::path::Path;


fn main() {
    let dir_path = Path::new("vendor/tree-sitter/src/runtime");

    let source_filenames = [
      "get_changed_ranges.c",
      "language.c",
      "lexer.c",
      "node.c",
      "parser.c",
      "parser.c",
      "stack.c",
      "subtree.c",
      "tree_cursor.c",
      "tree.c",
      "utf16.c",
    ];

    let mut config = cc::Build::new();
    config.include("vendor/tree-sitter/src");
    config.include("vendor/tree-sitter/include");
    config.include("vendor/tree-sitter/externals/utf8proc");
    config.flag_if_supported("-std=c99");
    config.flag_if_supported("-Wno-unused-parameter");

    for source_filename in source_filenames.iter() {
        let source_path = dir_path.join(Path::new(&source_filename));
        config.file(&source_path.to_str().unwrap());
    }

    config.compile("libruntime.a")
}
